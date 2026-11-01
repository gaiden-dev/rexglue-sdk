/**
 ******************************************************************************
 * Xenia : Xbox 360 Emulator Research Project                                 *
 ******************************************************************************
 * Copyright 2020 Ben Vanik. All rights reserved.                             *
 * Released under the BSD license - see LICENSE in the root for more details. *
 ******************************************************************************
 *
 * @modified    Tom Clay, 2026 - Adapted for ReXGlue runtime
 */

#include <rex/graphics/flags.h>
#include <rex/logging.h>
#include <rex/ui/renderdoc_api.h>

REXCVAR_DEFINE_STRING(trace_gpu_prefix, "scratch/gpu/", "GPU.Debug",
                      "Prefix path for GPU trace files.");
REXCVAR_DEFINE_BOOL(trace_gpu_stream, false, "GPU.Debug", "Trace all GPU packets.");

REXCVAR_DEFINE_STRING(dump_shaders, "", "GPU.Debug",
                      "For shader debugging, path to dump GPU shaders to as they are compiled.");

REXCVAR_DEFINE_BOOL(vsync, true, "GPU", "Enable VSYNC.")
    .lifecycle(rex::cvar::Lifecycle::kHotReload);

REXCVAR_DEFINE_UINT64(framerate_limit, 0, "GPU",
                      "Maximum frames per second. 0 = Unlimited frames.\n"
                      "Defaults to 60, when set to 0, and VSYNC is enabled.");
REXCVAR_DEFINE_BOOL(gpu_allow_invalid_fetch_constants, true, "GPU",
                    "Allow texture and vertex fetch constants with invalid type - generally "
                    "unsafe because the constant may contain completely invalid values, but "
                    "may be used to bypass fetch constant type errors in certain games until "
                    "the real reason why they're invalid is found.");
REXCVAR_DEFINE_BOOL(gpu_allow_invalid_upload_range, false, "GPU",
                    "Allows games to read data from pages that are marked as no access.");

REXCVAR_DEFINE_BOOL(non_seamless_cube_map, true, "GPU.Debug",
                    "Disable filtering between cube map faces near edges where possible "
                    "(Vulkan with VK_EXT_non_seamless_cube_map) to reproduce the Direct3D 9 "
                    "behavior.");

// Extremely bright screen borders in 4D5307E6.
// Reading between texels with half-pixel offset in 58410954.
REXCVAR_DEFINE_BOOL(half_pixel_offset, true, "GPU.Debug",
                    "Enable support of vertex half-pixel offset (D3D9 PA_SU_VTX_CNTL "
                    "PIX_CENTER). Generally games are aware of the half-pixel offset, and "
                    "having this enabled is the correct behavior (disabling this may "
                    "significantly break post-processing in some games), but in certain games "
                    "it might have been ignored, resulting in slight blurriness of UI "
                    "textures, for instance, when they are read between texels rather than "
                    "at texel centers, or the leftmost/topmost pixels may not be fully covered "
                    "when MSAA is used with fullscreen passes.");

REXCVAR_DEFINE_INT32(occlusion_query_fake_lower_threshold, 80, "GPU",
                     "Lower end of the fake sample count value written on "
                     "EVENT_WRITE_ZPD when real occlusion queries are disabled.\n"
                     "-1 writes nothing, resulting in some games that sit and hang.\n"
                     "0 means the fake result stays fully occluded.");
REXCVAR_DEFINE_INT32(occlusion_query_fake_upper_threshold, 100, "GPU",
                     "Upper end of the fake sample count value written on "
                     "EVENT_WRITE_ZPD when real occlusion queries are disabled.\n"
                     "Keep this higher than occlusion_query_fake_lower_threshold.\n"
                     "Ignored if occlusion_query_fake_lower_threshold is -1.");
REXCVAR_DEFINE_INT32(occlusion_query_querybatch_range, 0, "GPU",
                     "Range of fake sample count values to walk for titles using the "
                     "D3D QueryBatch standard before wrapping back to "
                     "occlusion_query_fake_lower_threshold.\n"
                     "This shouldn't be changed from the default value of 0 (disabled) "
                     "unless necessary for a specific title.");
REXCVAR_DEFINE_DOUBLE(occlusion_query_saturation, 1.0, "GPU",
                      "Compress higher occlusion query sample counts before guest writeback.\n"
                      "This can be useful if effects such as lens flares appear too strong.\n"
                      "1.0 = default behavior\n"
                      "0.0 = collapse all nonzero sample counts to 1\n"
                      "Values around 0.90 are a good starting point for subtle tuning.");

REXCVAR_DEFINE_INT32(anisotropic_override, -1, "GPU",
                     "Forces anisotropic filtering (AF) for eligible textures.\n"
                     "Higher values keep textures sharper at oblique angles at the "
                     "cost of GPU bandwidth, though most GPUs handle up to 16x fine.\n"
                     "In rare cases, forcing AF can introduce visual artifacts.\n"
                     " -1 = No override\n"
                     "  0 = Disable anisotropic filtering\n"
                     "  1 = Force 1x anisotropic filtering\n"
                     "  2 = Force 2x anisotropic filtering\n"
                     "  3 = Force 4x anisotropic filtering\n"
                     "  4 = Force 8x anisotropic filtering\n"
                     "  5 = Force 16x anisotropic filtering");

REXCVAR_DEFINE_BOOL(no_discard_stencil_in_transfer_pipelines, false, "GPU.Debug",
                    "Skip stencil bit discard in render target transfer pipelines. "
                    "May improve performance on some GPUs.");

REXCVAR_DEFINE_BOOL(gpu_3d_to_2d_texture, true, "GPU",
                    "Handle shaders that sample 3D textures as 2D by creating a 2D "
                    "texture from slice 0 of the guest memory.");

REXCVAR_DEFINE_BOOL(async_shader_compilation, true, "GPU",
                    "Compile shaders and create pipelines asynchronously in background "
                    "threads. "
                    "Eliminates shader compilation stutter but may cause brief rendering "
                    "artifacts while pipelines are being created. When disabled, pipelines are "
                    "created synchronously which causes stutter but no visual artifacts.");

REXCVAR_DEFINE_BOOL(force_depth_clamp, false, "GPU",
                    "Use host depth clamping instead of near and far plane clipping when "
                    "guest clipping is enabled. X/Y/W clipping is unaffected. On Vulkan, "
                    "this requires depthClamp support.");

// ReXGlue: GPU debug markers for PIX / RenderDoc (auto-enabled under RenderDoc).
REXCVAR_DEFINE_BOOL(gpu_debug_markers, false, "GPU.Debug",
                    "Insert debug markers into GPU command streams for tools "
                    "like PIX and RenderDoc. Automatically enabled when "
                    "RenderDoc is detected.");

bool IsGpuDebugMarkersEnabled() {
  static bool cached = false;
  static bool result = false;
  if (!cached) {
    cached = true;
    if (REXCVAR_GET(gpu_debug_markers)) {
      result = true;
      REXLOG_INFO("GPU debug markers enabled via CVar");
    } else {
      auto renderdoc_api = rex::ui::RenderDocAPI::CreateIfConnected();
      if (renderdoc_api) {
        result = true;
        REXLOG_INFO("GPU debug markers auto-enabled (RenderDoc detected)");
      }
    }
  }
  return result;
}
