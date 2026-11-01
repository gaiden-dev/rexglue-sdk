/**
 ******************************************************************************
 * Xenia : Xbox 360 Emulator Research Project                                 *
 ******************************************************************************
 * Copyright 2022 Ben Vanik. All rights reserved.                             *
 * Released under the BSD license - see LICENSE in the root for more details. *
 ******************************************************************************
 *
 * @modified    Tom Clay, 2026 - Adapted for ReXGlue runtime
 */

#include <rex/chrono/clock.h>
#include <rex/dbg.h>
#include <rex/graphics/command_processor.h>
#include <rex/graphics/flags.h>
#include <rex/graphics/graphics_system.h>
// ReXGlue: VdQueryVideoMode provides the guest display mode.
#include <rex/kernel/xboxkrnl/video.h>
#include <rex/logging.h>
#include <rex/math.h>
#include <rex/stream.h>
#include <rex/system/kernel_state.h>
// ReXGlue: GetExecutableModule() needs the complete UserModule type.
#include <rex/system/user_module.h>
#include <rex/thread.h>
#include <rex/ui/graphics_provider.h>
#include <rex/ui/window.h>
#include <rex/ui/windowed_app_context.h>

// ReXGlue: swap post effect selection (xenia exposes it through the UI only).
REXCVAR_DEFINE_STRING(swap_post_effect, "none", "GPU", "Swap post effect: none, fxaa, fxaa_extreme")
    .allowed({"none", "fxaa", "fxaa_extreme"})
    .lifecycle(rex::cvar::Lifecycle::kRequiresRestart);

REXCVAR_DEFINE_UINT32(custom_internal_display_resolution_x, 0, "Video",
                      "Custom width. See internal_display_resolution. Range 1-1920.");
REXCVAR_DEFINE_UINT32(custom_internal_display_resolution_y, 0, "Video",
                      "Custom height. See internal_display_resolution. Range 1-1080.\n");

REXCVAR_DEFINE_BOOL(store_shaders, true, "GPU.Debug",
                    "Store shaders persistently and load them when loading games to avoid "
                    "runtime spikes and freezes when playing the game not for the first time.");

namespace rex::graphics {

// Nvidia Optimus/AMD PowerXpress support.
// These exports force the process to trigger the discrete GPU in multi-GPU
// systems.
// https://developer.download.nvidia.com/devzone/devcenter/gamegraphics/files/OptimusRenderingPolicies.pdf
// https://stackoverflow.com/questions/17458803/amd-equivalent-to-nvoptimusenablement
#if REX_PLATFORM_WIN32
extern "C" {
__declspec(dllexport) uint32_t NvOptimusEnablement = 0x00000001;
__declspec(dllexport) uint32_t AmdPowerXpressRequestHighPerformance = 1;
}  // extern "C"
#endif  // REX_PLATFORM_WIN32

GraphicsSystem::GraphicsSystem() : frame_limiter_worker_running_(false) {
  register_file_ = reinterpret_cast<RegisterFile*>(
      memory::AllocFixed(nullptr, sizeof(RegisterFile), memory::AllocationType::kReserveCommit,
                         memory::PageAccess::kReadWrite));
}

GraphicsSystem::~GraphicsSystem() = default;

// ReXGlue: xenia's Setup() is split into SetupPresentation() and SetupGuestGpu().
X_STATUS GraphicsSystem::SetupPresentation(ui::WindowedAppContext* app_context) {
  if (presenter_) {
    return X_STATUS_SUCCESS;
  }

  scaled_aspect_x_ = 16;
  scaled_aspect_y_ = 9;

  if (!provider_) {
    CreateProvider(true);
    if (!provider_) {
      REXGPU_ERROR("Unable to create graphics provider");
      return X_STATUS_UNSUCCESSFUL;
    }
    provider_supports_presentation_ = true;
  } else if (!provider_supports_presentation_) {
    // A headless provider from SetupGuestGpu can't be upgraded in place.
    REXGPU_ERROR("SetupPresentation called after headless SetupGuestGpu; call order is reversed");
    return X_STATUS_UNSUCCESSFUL;
  }

  app_context_ = app_context;

  // Safe if either the UI thread call or the presenter creation fails.
  if (app_context_) {
    app_context_->CallInUIThreadSynchronous([this]() {
      presenter_ =
          provider_->CreatePresenter([this](bool is_responsible, bool statically_from_ui_thread) {
            OnHostGpuLossFromAnyThread(is_responsible);
          });
    });
  } else {
    // May be needed for offscreen use, such as capturing the guest output
    // image.
    presenter_ =
        provider_->CreatePresenter([this](bool is_responsible, bool statically_from_ui_thread) {
          OnHostGpuLossFromAnyThread(is_responsible);
        });
  }

  if (!presenter_) {
    REXGPU_ERROR("Unable to create presenter");
    return X_STATUS_UNSUCCESSFUL;
  }
  return X_STATUS_SUCCESS;
}

X_STATUS GraphicsSystem::SetupGuestGpu(runtime::FunctionDispatcher* function_dispatcher,
                                       system::KernelState* kernel_state) {
  memory_ = function_dispatcher->memory();
  function_dispatcher_ = function_dispatcher;
  kernel_state_ = kernel_state;

  if (!provider_) {
    CreateProvider(false);
    provider_supports_presentation_ = false;
  }

  // Create command processor. This will spin up a thread to process all
  // incoming ringbuffer packets.
  command_processor_ = CreateCommandProcessor();
  if (!command_processor_->Initialize()) {
    REXGPU_ERROR("Unable to initialize command processor");
    return X_STATUS_UNSUCCESSFUL;
  }
  // ReXGlue: swap_post_effect cvar (values are validated by the cvar itself).
  const std::string& swap_post_effect = REXCVAR_GET(swap_post_effect);
  command_processor_->SetDesiredSwapPostEffect(
      swap_post_effect == "fxaa"           ? CommandProcessor::SwapPostEffect::kFxaa
      : swap_post_effect == "fxaa_extreme" ? CommandProcessor::SwapPostEffect::kFxaaExtreme
                                           : CommandProcessor::SwapPostEffect::kNone);

  // Let the processor know we want register access callbacks.
  memory_->AddVirtualMappedRange(0x7FC80000, 0xFFFF0000, 0x0000FFFF, this,
                                 reinterpret_cast<runtime::MMIOReadCallback>(ReadRegisterThunk),
                                 reinterpret_cast<runtime::MMIOWriteCallback>(WriteRegisterThunk));

  // Frame limiter thread.
  frame_limiter_worker_running_ = true;
  frame_limiter_worker_thread_ = system::object_ref<system::XHostThread>(
      new system::XHostThread(kernel_state_, 128 * 1024, 0, [this]() {
        uint64_t normalized_framerate_limit = std::max<uint64_t>(0, REXCVAR_GET(framerate_limit));

        // If VSYNC is enabled, but frames are not limited,
        // lock framerate at default value of 60
        if (normalized_framerate_limit == 0 && REXCVAR_GET(vsync)) {
          // ReXGlue: use the guest video mode refresh rate (VdQueryVideoMode).
          system::X_VIDEO_MODE video_mode;
          kernel::xboxkrnl::VdQueryVideoMode(&video_mode);
          normalized_framerate_limit = std::max<uint64_t>(1, uint64_t(video_mode.refresh_rate));
        }

        const double vsync_duration_d =
            REXCVAR_GET(vsync)
                ? std::max<double>(5.0, 1000.0 / static_cast<double>(normalized_framerate_limit))
                : 1.0;
        uint64_t last_frame_time = chrono::Clock::QueryGuestTickCount();
    // Sleep for 90% of the vblank duration on Windows, spin for 10%
    // Linux uses full sleep duration due to scheduler quantum issues
#if REX_PLATFORM_WIN32
        constexpr double duration_scalar = 0.90;
#endif

        while (frame_limiter_worker_running_) {
          // If there is no title running then there is no need for guest
          // frame limiter thread.
          // ReXGlue: no is_title_open(); a loaded executable module means a title.
          if (!kernel_state_->GetExecutableModule()) {
            rex::thread::Sleep(std::chrono::milliseconds(100));
            continue;
          }

          register_file()->values[XE_GPU_REG_D1MODE_V_COUNTER] += GetResolution().second;

#if REX_PLATFORM_WIN32
          if (REXCVAR_GET(vsync)) {
            const uint64_t current_time = chrono::Clock::QueryGuestTickCount();
            const uint64_t tick_freq = chrono::Clock::guest_tick_frequency();
            const uint64_t time_delta = current_time - last_frame_time;
            const double elapsed_d =
                static_cast<double>(time_delta) / (static_cast<double>(tick_freq) / 1000.0);
            if (elapsed_d >= vsync_duration_d) {
              last_frame_time = current_time;

              MarkVblank();
              const uint64_t estimated_nanoseconds = static_cast<uint64_t>(
                  (vsync_duration_d * 1000000.0) * duration_scalar);  // 1000 microseconds = 1 ms

              thread::NanoSleep(estimated_nanoseconds);
            }
          }

          if (!REXCVAR_GET(vsync)) {
            MarkVblank();
            if (normalized_framerate_limit > 0) {
              // framerate_limit is over 0, vsync disabled
              //  - No VSYNC + limited frames defined by user
              uint64_t framerate_limited_sleep_time = 1000000000 / normalized_framerate_limit;
              rex::thread::NanoSleep(framerate_limited_sleep_time);
            } else {
              // framerate_limit is 0, vsync disabled
              //  - No VSYNC + unlimited frames
              rex::thread::Sleep(std::chrono::milliseconds(1));
            }
          }
#else
          // ReXGlue: also macOS.
          // Linux: Use simplified timing logic to avoid oversleeping
          MarkVblank();

          if (REXCVAR_GET(vsync) || normalized_framerate_limit > 0) {
            uint64_t sleep_duration_ns = static_cast<uint64_t>(vsync_duration_d * 1000000.0);
            if (!REXCVAR_GET(vsync) && normalized_framerate_limit > 0) {
              sleep_duration_ns = 1000000000 / normalized_framerate_limit;
            }
            thread::NanoSleep(sleep_duration_ns);
          } else {
            rex::thread::Sleep(std::chrono::milliseconds(1));
          }
#endif
        }
        return 0;
      }));
  frame_limiter_worker_thread_->set_name("GPU Frame limiter");
  frame_limiter_worker_thread_->Create();
  frame_limiter_worker_thread_->thread()->set_priority(thread::ThreadPriority::kLowest);
  if (REXCVAR_GET(trace_gpu_stream)) {
    BeginTracing();
  }

  return X_STATUS_SUCCESS;
}

void GraphicsSystem::Shutdown() {
  if (command_processor_) {
    EndTracing();
    command_processor_->Shutdown();
    command_processor_.reset();
  }

  if (frame_limiter_worker_thread_) {
    frame_limiter_worker_running_ = false;
    frame_limiter_worker_thread_->Wait(0, 0, 0, nullptr);
    frame_limiter_worker_thread_.reset();
  }

  if (presenter_) {
    if (app_context_) {
      app_context_->CallInUIThreadSynchronous([this]() { presenter_.reset(); });
    }
    // If there's no app context (thus the presenter is owned by the thread that
    // initialized the GraphicsSystem) or can't be queueing UI thread calls
    // anymore, shutdown anyway.
    presenter_.reset();
  }

  provider_.reset();
}

void GraphicsSystem::OnHostGpuLossFromAnyThread([[maybe_unused]] bool is_responsible) {
  // TODO(Triang3l): Somehow gain exclusive ownership of the Provider (may be
  // used by the command processor, the presenter, and possibly anything else,
  // it's considered free-threaded, except for lifetime management which will be
  // involved in this case) and reset it so a new host GPU API device is
  // created. Then ask the command processor to reset itself in its thread, and
  // ask the UI thread to reset the Presenter (the UI thread manages its
  // lifetime - but if there's no WindowedAppContext, either don't reset it as
  // in this case there's no user who needs uninterrupted gameplay, or somehow
  // protect it with a mutex so any thread can be considered a UI thread and
  // reset).
  if (host_gpu_loss_reported_.test_and_set(std::memory_order_relaxed)) {
    return;
  }

  rex::FatalError("Graphics device lost (probably due to an internal error)");
}

uint32_t GraphicsSystem::ReadRegisterThunk(void* ppc_context, GraphicsSystem* gs, uint32_t addr) {
  return gs->ReadRegister(addr);
}

void GraphicsSystem::WriteRegisterThunk(void* ppc_context, GraphicsSystem* gs, uint32_t addr,
                                        uint32_t value) {
  gs->WriteRegister(addr, value);
}

uint32_t GraphicsSystem::ReadRegister(uint32_t addr) {
  uint32_t r = (addr & 0xFFFF) / 4;

  switch (r) {
    case 0x0F00:  // RB_EDRAM_TIMING
      return 0x08100748;
    case 0x0F01:  // RB_BC_CONTROL
      return 0x0000200E;
    case 0x1951:    // interrupt status
      return 1;     // vblank
    case 0x1961: {  // AVIVO_D1MODE_VIEWPORT_SIZE
      // ReXGlue: screen res from the guest video mode (VdQueryVideoMode).
      // maximum [width(0x0FFF), height(0x0FFF)]
      system::X_VIDEO_MODE video_mode;
      kernel::xboxkrnl::VdQueryVideoMode(&video_mode);
      return (std::min(uint32_t(video_mode.display_width), uint32_t(0x0FFF)) << 16) |
             std::min(uint32_t(video_mode.display_height), uint32_t(0x0FFF));
    }
    default:
      if (!register_file()->IsValidRegister(r)) {
        REXGPU_ERROR("GPU: Read from unknown register ({:04X})", r);
      }
  }

  assert_true(r < RegisterFile::kRegisterCount);
  return register_file()->values[r];
}

void GraphicsSystem::WriteRegister(uint32_t addr, uint32_t value) {
  uint32_t r = (addr & 0xFFFF) / 4;

  switch (r) {
    case 0x01C5:  // CP_RB_WPTR
      command_processor_->UpdateWritePointer(value);
      break;
    case 0x1844:  // AVIVO_D1GRPH_PRIMARY_SURFACE_ADDRESS
      break;
    default:
      REXGPU_WARN("Unknown GPU register {:04X} write: {:08X}", r, value);
      break;
  }

  assert_true(r < RegisterFile::kRegisterCount);
  this->register_file()->values[r] = value;
}

void GraphicsSystem::InitializeRingBuffer(uint32_t ptr, uint32_t size_log2) {
  command_processor_->InitializeRingBuffer(ptr, size_log2);
}

void GraphicsSystem::EnableReadPointerWriteBack(uint32_t ptr, uint32_t block_size_log2) {
  command_processor_->EnableReadPointerWriteBack(ptr, block_size_log2);
}

void GraphicsSystem::SetInterruptCallback(uint32_t callback, uint32_t user_data) {
  interrupt_callback_ = callback;
  interrupt_callback_data_ = user_data;
  REXGPU_INFO("SetInterruptCallback({:08X}, {:08X})", callback, user_data);
}

void GraphicsSystem::DispatchInterruptCallback(uint32_t source, uint32_t cpu) {
  // ReXGlue: no EmulateCPInterruptDPC; call the guest interrupt handler directly.
  if (!interrupt_callback_) {
    return;
  }

  auto thread = system::XThread::GetCurrentThread();
  assert_not_null(thread);

  // Pick a CPU, if needed. We're going to guess 2. Because.
  if (cpu == 0xFFFFFFFF) {
    cpu = 2;
  }
  thread->SetActiveCpu(cpu);

  uint64_t args[] = {source, interrupt_callback_data_};
  function_dispatcher_->ExecuteInterrupt(thread->thread_state(), interrupt_callback_, args,
                                         rex::countof(args));
}

void GraphicsSystem::MarkVblank() {
  SCOPE_profile_cpu_f("gpu");

  // Increment vblank counter (so the game sees us making progress).
  // ReXGlue: command_processor_ may be null during shutdown.
  if (command_processor_) {
    command_processor_->increment_counter();
  }

  // TODO(benvanik): we shouldn't need to do the dispatch here, but there's
  //     something wrong and the CP will block waiting for code that
  //     needs to be run in the interrupt.
  DispatchInterruptCallback(0, 2);
}

void GraphicsSystem::ClearCaches() {
  command_processor_->CallInThread([&]() { command_processor_->ClearCaches(); });
}

void GraphicsSystem::InvalidateGpuMemory() {
  command_processor_->CallInThread([&]() { command_processor_->InvalidateGpuMemory(); });
}

void GraphicsSystem::InitializeShaderStorage(const std::filesystem::path& cache_root,
                                             uint32_t title_id, bool blocking) {
  InitializeShaderStorage(cache_root, title_id, blocking, nullptr);
}

void GraphicsSystem::InitializeShaderStorage(const std::filesystem::path& cache_root,
                                             uint32_t title_id, bool blocking,
                                             std::function<void()> completion_callback) {
  if (!REXCVAR_GET(store_shaders)) {
    if (completion_callback) {
      completion_callback();
    }
    return;
  }
  if (blocking) {
    if (command_processor_->is_paused()) {
      // Safe to run on any thread while the command processor is paused, no
      // race condition.
      command_processor_->InitializeShaderStorage(cache_root, title_id, true,
                                                  std::move(completion_callback));
    } else {
      rex::thread::Fence fence;
      command_processor_->CallInThread(
          [this, cache_root, title_id, &fence,
           completion_callback = std::move(completion_callback)]() mutable {
            command_processor_->InitializeShaderStorage(cache_root, title_id, true,
                                                        std::move(completion_callback));
            fence.Signal();
          });
      fence.Wait();
    }
  } else {
    command_processor_->CallInThread(
        [this, cache_root, title_id,
         completion_callback = std::move(completion_callback)]() mutable {
          command_processor_->InitializeShaderStorage(cache_root, title_id, false,
                                                      std::move(completion_callback));
        });
  }
}

void GraphicsSystem::RequestFrameTrace() {
  command_processor_->RequestFrameTrace(REXCVAR_GET(trace_gpu_prefix));
}

void GraphicsSystem::BeginTracing() {
  command_processor_->BeginTracing(REXCVAR_GET(trace_gpu_prefix));
}

void GraphicsSystem::EndTracing() {
  command_processor_->EndTracing();
}

void GraphicsSystem::Pause() {
  paused_ = true;

  command_processor_->Pause();
}

void GraphicsSystem::Resume() {
  paused_ = false;

  command_processor_->Resume();
}

bool GraphicsSystem::Save(stream::ByteStream* stream) {
  stream->Write<uint32_t>(interrupt_callback_);
  stream->Write<uint32_t>(interrupt_callback_data_);

  return command_processor_->Save(stream);
}

bool GraphicsSystem::Restore(stream::ByteStream* stream) {
  interrupt_callback_ = stream->Read<uint32_t>();
  interrupt_callback_data_ = stream->Read<uint32_t>();

  return command_processor_->Restore(stream);
}

std::pair<uint32_t, uint32_t> GraphicsSystem::GetResolution() const {
  if (!kernel_state_) {
    return {1280, 720};
  }

  if (REXCVAR_GET(custom_internal_display_resolution_x) != 0 &&
      REXCVAR_GET(custom_internal_display_resolution_y) != 0) {
    return {REXCVAR_GET(custom_internal_display_resolution_x),
            REXCVAR_GET(custom_internal_display_resolution_y)};
  }

  // ReXGlue: no xconfig; use the guest video mode (VdQueryVideoMode).
  system::X_VIDEO_MODE video_mode;
  kernel::xboxkrnl::VdQueryVideoMode(&video_mode);
  if (!video_mode.display_width || !video_mode.display_height) {
    return {1280, 720};
  }
  return {uint32_t(video_mode.display_width), uint32_t(video_mode.display_height)};
}

}  // namespace rex::graphics
