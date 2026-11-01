#pragma once
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

#include <atomic>
#include <cstdint>
#include <functional>
#include <memory>
#include <mutex>
#include <string>
#include <thread>

#include <rex/graphics/register_file.h>
#include <rex/memory.h>
#include <rex/system/function_dispatcher.h>
#include <rex/system/xthread.h>
// ReXGlue: plugin interface implemented by GraphicsSystem.
#include <rex/system/interfaces/graphics.h>
#include <rex/system/xtypes.h>
#include <rex/ui/graphics_provider.h>
#include <rex/ui/presenter.h>
#include <rex/ui/windowed_app_context.h>

namespace rex::stream {
class ByteStream;
}  // namespace rex::stream

namespace rex::graphics {

class CommandProcessor;

class GraphicsSystem : public system::IGraphicsSystem {
 public:
  virtual ~GraphicsSystem();

  virtual std::string name() const = 0;

  memory::Memory* memory() const { return memory_; }
  runtime::FunctionDispatcher* function_dispatcher() const { return function_dispatcher_; }
  system::KernelState* kernel_state() const { return kernel_state_; }
  ui::GraphicsProvider* provider() const override { return provider_.get(); }
  ui::Presenter* presenter() const override { return presenter_.get(); }

  // ReXGlue: xenia's Setup() is split into the two IGraphicsSystem stages.
  X_STATUS SetupPresentation(ui::WindowedAppContext* app_context) override;
  X_STATUS SetupGuestGpu(runtime::FunctionDispatcher* function_dispatcher,
                         system::KernelState* kernel_state) override;
  bool has_presentation() const override { return presenter_ != nullptr; }
  void Shutdown() override;

  // May be called from any thread any number of times, even during recovery
  // from a device loss.
  void OnHostGpuLossFromAnyThread(bool is_responsible);

  RegisterFile* register_file() { return register_file_; }
  CommandProcessor* command_processor() const { return command_processor_.get(); }

  void InitializeRingBuffer(uint32_t ptr, uint32_t size_log2) override;
  void EnableReadPointerWriteBack(uint32_t ptr, uint32_t block_size_log2) override;

  void SetInterruptCallback(uint32_t callback, uint32_t user_data) override;
  void DispatchInterruptCallback(uint32_t source, uint32_t cpu);

  virtual void ClearCaches();
  // ReXGlue: drops host-side caches of guest memory (see CommandProcessor).
  virtual void InvalidateGpuMemory();

  // ReXGlue: IGraphicsSystem override, forwards to the xenia-style overload below.
  void InitializeShaderStorage(const std::filesystem::path& cache_root, uint32_t title_id,
                               bool blocking) override;
  void InitializeShaderStorage(const std::filesystem::path& cache_root, uint32_t title_id,
                               bool blocking, std::function<void()> completion_callback);

  void RequestFrameTrace();
  void BeginTracing();
  void EndTracing();

  bool is_paused() const { return paused_; }
  void Pause();
  void Resume();

  bool Save(stream::ByteStream* stream);
  bool Restore(stream::ByteStream* stream);

  std::pair<uint32_t, uint32_t> GetResolution() const;

  std::pair<uint32_t, uint32_t> GetScaledAspectRatio() const {
    return {scaled_aspect_x_, scaled_aspect_y_};
  };
  void SetScaledAspectRatio(uint32_t x, uint32_t y) {
    scaled_aspect_x_ = x;
    scaled_aspect_y_ = y;
  };

 protected:
  GraphicsSystem();

  // ReXGlue: backends create provider_ here (lazily, from either setup stage).
  virtual void CreateProvider(bool with_presentation) = 0;

  virtual std::unique_ptr<CommandProcessor> CreateCommandProcessor() = 0;

  static uint32_t ReadRegisterThunk(void* ppc_context, GraphicsSystem* gs, uint32_t addr);
  static void WriteRegisterThunk(void* ppc_context, GraphicsSystem* gs, uint32_t addr,
                                 uint32_t value);
  uint32_t ReadRegister(uint32_t addr);
  void WriteRegister(uint32_t addr, uint32_t value);

  void MarkVblank();

  memory::Memory* memory_ = nullptr;
  runtime::FunctionDispatcher* function_dispatcher_ = nullptr;
  system::KernelState* kernel_state_ = nullptr;
  ui::WindowedAppContext* app_context_ = nullptr;
  std::unique_ptr<ui::GraphicsProvider> provider_;
  // ReXGlue: whether provider_ was created with presentation support.
  bool provider_supports_presentation_ = false;

  uint32_t interrupt_callback_ = 0;
  uint32_t interrupt_callback_data_ = 0;

  std::atomic<bool> frame_limiter_worker_running_;
  system::object_ref<system::XHostThread> frame_limiter_worker_thread_;

  RegisterFile* register_file_;
  std::unique_ptr<CommandProcessor> command_processor_;

  bool paused_ = false;

  uint32_t scaled_aspect_x_ = 0;
  uint32_t scaled_aspect_y_ = 0;

 private:
  std::unique_ptr<ui::Presenter> presenter_;

  std::atomic_flag host_gpu_loss_reported_;
};

}  // namespace rex::graphics
