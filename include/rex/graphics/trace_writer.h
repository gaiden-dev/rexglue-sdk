/**
 ******************************************************************************
 * Xenia : Xbox 360 Emulator Research Project                                 *
 ******************************************************************************
 * Copyright 2022 Ben Vanik. All rights reserved.                             *
 * Released under the BSD license - see LICENSE in the root for more details. *
 ******************************************************************************
 *
 * @modified    Rien Gupta, 2026 - Adapted for ReXGlue runtime
 */

#pragma once

#include <cstdint>
#include <filesystem>

#include <rex/graphics/registers.h>

// ReXGlue does not ship the GPU trace capture system (use Xenia for that), but
// the command processor is instrumented with trace writer calls that are kept
// in place so the code stays aligned with xenia-canary. This header provides
// the no-op variant of xenia's TraceWriter so those call sites compile to
// nothing.
#define REX_ENABLE_TRACE_WRITER_INSTRUMENTATION 0

namespace rex::graphics {

struct EventCommand {
  // Identifies the event that occurred.
  enum class Type {
    kSwap,
  };
};

class TraceWriter {
 public:
  constexpr explicit TraceWriter(uint8_t* /*membase*/) {}

  static constexpr bool is_open() { return false; }

  static constexpr bool Open(const std::filesystem::path& /*path*/, uint32_t /*title_id*/) {
    return false;
  }
  static constexpr void Flush() {}
  static constexpr void Close() {}

  static constexpr void WritePrimaryBufferStart(uint32_t /*base_ptr*/, uint32_t /*count*/) {}
  static constexpr void WritePrimaryBufferEnd() {}
  static constexpr void WriteIndirectBufferStart(uint32_t /*base_ptr*/, uint32_t /*count*/) {}
  static constexpr void WriteIndirectBufferEnd() {}
  static constexpr void WritePacketStart(uint32_t /*base_ptr*/, uint32_t /*count*/) {}
  static constexpr void WritePacketEnd() {}
  static constexpr void WriteMemoryRead(uint32_t /*base_ptr*/, size_t /*length*/,
                                        const void* /*host_ptr*/ = nullptr) {}
  static constexpr void WriteMemoryReadCached(uint32_t /*base_ptr*/, size_t /*length*/) {}
  static constexpr void WriteMemoryReadCachedNop(uint32_t /*base_ptr*/, size_t /*length*/) {}
  static constexpr void WriteMemoryWrite(uint32_t /*base_ptr*/, size_t /*length*/,
                                         const void* /*host_ptr*/ = nullptr) {}
  static constexpr void WriteEdramSnapshot(const void* /*snapshot*/) {}
  static constexpr void WriteEvent(EventCommand::Type /*event_type*/) {}
  static constexpr void WriteRegisters(uint32_t /*first_register*/,
                                       const uint32_t* /*register_values*/,
                                       uint32_t /*register_count*/,
                                       bool /*execute_callbacks_on_play*/) {}
  static constexpr void WriteGammaRamp(const reg::DC_LUT_30_COLOR* /*gamma_ramp_256_entry_table*/,
                                       const reg::DC_LUT_PWL_DATA* /*gamma_ramp_pwl_rgb*/,
                                       uint32_t /*gamma_ramp_rw_component*/) {}
};

}  // namespace rex::graphics
