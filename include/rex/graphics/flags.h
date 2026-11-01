#pragma once
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

#include <rex/cvar.h>

REXCVAR_DECLARE(std::string, trace_gpu_prefix);
REXCVAR_DECLARE(bool, trace_gpu_stream);

REXCVAR_DECLARE(std::string, dump_shaders);

REXCVAR_DECLARE(bool, vsync);

REXCVAR_DECLARE(uint64_t, framerate_limit);

REXCVAR_DECLARE(bool, gpu_allow_invalid_fetch_constants);

REXCVAR_DECLARE(bool, non_seamless_cube_map);

REXCVAR_DECLARE(bool, half_pixel_offset);

REXCVAR_DECLARE(std::string, occlusion_query);

REXCVAR_DECLARE(bool, viz_query);

REXCVAR_DECLARE(bool, viz_query_log);

REXCVAR_DECLARE(int32_t, occlusion_query_fake_lower_threshold);

REXCVAR_DECLARE(int32_t, occlusion_query_fake_upper_threshold);

REXCVAR_DECLARE(int32_t, occlusion_query_querybatch_range);

REXCVAR_DECLARE(double, occlusion_query_saturation);

REXCVAR_DECLARE(int32_t, anisotropic_override);

REXCVAR_DECLARE(bool, disassemble_pm4);

REXCVAR_DECLARE(bool, no_discard_stencil_in_transfer_pipelines);

REXCVAR_DECLARE(bool, async_shader_compilation);

REXCVAR_DECLARE(bool, gpu_3d_to_2d_texture);

REXCVAR_DECLARE(bool, force_depth_clamp);

// ReXGlue: cross-TU declarations for the remaining GPU cvars (xenia declares
// these locally in each consumer); gpu_debug_markers and swap_post_effect are
// ReXGlue-only.
REXCVAR_DECLARE(bool, gpu_allow_invalid_upload_range);
REXCVAR_DECLARE(bool, gpu_debug_markers);
bool IsGpuDebugMarkersEnabled();
REXCVAR_DECLARE(bool, clear_memory_page_state);
REXCVAR_DECLARE(bool, log_guest_driven_gpu_register_written_values);
REXCVAR_DECLARE(bool, log_ringbuffer_kickoff_initiator_bts);
REXCVAR_DECLARE(std::string, readback_resolve);
REXCVAR_DECLARE(bool, readback_resolve_half_pixel_offset);
REXCVAR_DECLARE(bool, readback_memexport);
REXCVAR_DECLARE(bool, store_shaders);
REXCVAR_DECLARE(std::string, swap_post_effect);
REXCVAR_DECLARE(uint32_t, custom_internal_display_resolution_x);
REXCVAR_DECLARE(uint32_t, custom_internal_display_resolution_y);
REXCVAR_DECLARE(bool, depth_float24_round);
REXCVAR_DECLARE(bool, depth_float24_convert_in_pixel_shader);
REXCVAR_DECLARE(bool, depth_transfer_not_equal_test);
REXCVAR_DECLARE(bool, native_stencil_value_output);
REXCVAR_DECLARE(bool, gamma_render_target_as_unorm16);
REXCVAR_DECLARE(bool, snorm16_render_target_full_range);
REXCVAR_DECLARE(bool, mrt_edram_used_range_clamp_to_min);
REXCVAR_DECLARE(bool, execute_unclipped_draw_vs_on_cpu_for_psi_render_backend);
REXCVAR_DECLARE(bool, draw_resolution_scaled_texture_offsets);
REXCVAR_DECLARE(bool, debug_msaa_2x_as_4x);
REXCVAR_DECLARE(uint32_t, draw_resolution_scale_threshold);
REXCVAR_DECLARE(int32_t, draw_resolution_scale_x);
REXCVAR_DECLARE(int32_t, draw_resolution_scale_y);
REXCVAR_DECLARE(uint32_t, texture_cache_memory_limit_render_to_texture);
REXCVAR_DECLARE(uint32_t, texture_cache_memory_limit_soft);
REXCVAR_DECLARE(uint32_t, texture_cache_memory_limit_hard);
REXCVAR_DECLARE(uint32_t, texture_cache_memory_limit_soft_lifetime);
REXCVAR_DECLARE(bool, tiled_shared_memory);
REXCVAR_DECLARE(bool, resolve_resolution_scale_fill_half_pixel_offset);
REXCVAR_DECLARE(bool, depth_bias_shader_offset);
REXCVAR_DECLARE(bool, execute_unclipped_draw_vs_on_cpu);
REXCVAR_DECLARE(bool, execute_unclipped_draw_vs_on_cpu_with_scissor);
REXCVAR_DECLARE(bool, force_convert_line_loops_to_strips);
REXCVAR_DECLARE(bool, force_convert_quad_lists_to_triangle_lists);
REXCVAR_DECLARE(bool, force_convert_triangle_fans_to_lists);
REXCVAR_DECLARE(bool, ignore_32bit_vertex_index_support);
REXCVAR_DECLARE(int32_t, primitive_processor_cache_min_indices);
REXCVAR_DECLARE(bool, use_fuzzy_alpha_epsilon);
REXCVAR_DECLARE(bool, spirv_disable_rounding_mode_rte);
#if REX_HAS_VULKAN
REXCVAR_DECLARE(bool, vulkan_sparse_shared_memory);
REXCVAR_DECLARE(int32_t, vulkan_pipeline_creation_threads);
REXCVAR_DECLARE(std::string, render_target_path_vulkan);
REXCVAR_DECLARE(bool, vulkan_submit_on_primary_buffer_end);
REXCVAR_DECLARE(bool, vulkan_tessellation_wireframe);
#endif  // REX_HAS_VULKAN
#if REX_HAS_D3D12
REXCVAR_DECLARE(bool, dxbc_switch);
REXCVAR_DECLARE(bool, dxbc_source_map);
REXCVAR_DECLARE(bool, d3d12_bindless);
REXCVAR_DECLARE(bool, d3d12_submit_on_primary_buffer_end);
REXCVAR_DECLARE(bool, d3d12_dxbc_disasm);
REXCVAR_DECLARE(bool, d3d12_dxbc_disasm_dxilconv);
REXCVAR_DECLARE(int32_t, d3d12_pipeline_creation_threads);
REXCVAR_DECLARE(bool, d3d12_tessellation_wireframe);
REXCVAR_DECLARE(bool, native_stencil_value_output_d3d12_intel);
REXCVAR_DECLARE(std::string, render_target_path_d3d12);
#endif  // REX_HAS_D3D12

#define XE_GPU_FINE_GRAINED_DRAW_SCOPES 1
