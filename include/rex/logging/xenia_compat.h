/**
 * @file        rex/logging/xenia_compat.h
 * @brief       xenia-shaped logging API (LogLevel, logging::ShouldLog, logging::LoggerBatch)
 *
 * @copyright   Copyright (c) 2026 Rien Gupta <rgupta9@scu.edu>
 *              All rights reserved.
 *
 * @license     BSD 3-Clause License
 *              See LICENSE file in the project root for full license text.
 */

#pragma once

// Exists so code ported from xenia-canary (the GPU subsystem) can keep its
// logging calls verbatim; everything here forwards to the "gpu" log category.

#include <algorithm>
#include <cstddef>
#include <cstdint>
#include <string_view>
#include <utility>

#include <fmt/format.h>
#include <spdlog/spdlog.h>

#include <rex/logging/api.h>
#include <rex/logging/macros.h>

namespace rex {

// xenia's log level enumeration.
enum class LogLevel {
  Disabled = -1,
  Error = 0,
  Warning,
  Info,
  Debug,
  Trace,
};

namespace logging {

constexpr char kPrefixCharError = '!';
constexpr char kPrefixCharWarning = 'w';
constexpr char kPrefixCharInfo = 'i';
constexpr char kPrefixCharDebug = 'd';

inline spdlog::level::level_enum ToSpdlogLevel(LogLevel log_level) {
  switch (log_level) {
    case LogLevel::Error:
      return spdlog::level::err;
    case LogLevel::Warning:
      return spdlog::level::warn;
    case LogLevel::Info:
      return spdlog::level::info;
    case LogLevel::Debug:
      return spdlog::level::debug;
    case LogLevel::Trace:
      return spdlog::level::trace;
    default:
      return spdlog::level::off;
  }
}

// True when the GPU logger would emit a line at log_level.
inline bool ShouldLog(LogLevel log_level, uint32_t /*log_mask*/ = 0) {
  auto* logger = ::rex::GetLoggerRaw(::rex::log::gpu());
  return logger && logger->should_log(ToSpdlogLevel(log_level));
}

namespace internal {

constexpr size_t kThreadBufferSize = 64 * 1024;

// Per-thread scratch buffer that batched log lines are formatted into.
inline std::pair<char*, size_t> GetThreadBuffer() {
  thread_local char buffer[kThreadBufferSize];
  return {buffer, sizeof(buffer)};
}

// Emits the first `written` bytes of the thread buffer as one GPU log line.
inline void AppendLogLine(LogLevel log_level, char /*prefix_char*/, size_t written) {
  auto* logger = ::rex::GetLoggerRaw(::rex::log::gpu());
  if (!logger) {
    return;
  }
  auto buffer = GetThreadBuffer();
  std::string_view line(buffer.first, std::min(written, buffer.second));
  while (!line.empty() && (line.back() == '\n' || line.back() == '\r')) {
    line.remove_suffix(1);
  }
  logger->log(ToSpdlogLevel(log_level), "{}", line);
}

}  // namespace internal

// Accumulates several formatted fragments into the thread buffer and emits
// them as a single log line on submit().
template <LogLevel ll>
struct LoggerBatch {
  char* thrd_buf;       // current position in thread buffer
  size_t thrd_buf_rem;  // num left in thrd buffer
  size_t total_size;

  void reset() {
    auto target = internal::GetThreadBuffer();
    thrd_buf = target.first;
    thrd_buf_rem = target.second;
    total_size = 0;
  }

  LoggerBatch() { reset(); }

  template <size_t fmtlen, typename... Ts>
  void operator()(const char (&fmt)[fmtlen], Ts&&... args) {
    auto tmpres = fmt::format_to_n(thrd_buf, thrd_buf_rem, fmt::runtime(fmt), args...);
    size_t written = std::min(tmpres.size, thrd_buf_rem);
    thrd_buf_rem -= written;
    thrd_buf += written;
    total_size += written;
  }

  void submit(char prefix_char) { internal::AppendLogLine(ll, prefix_char, total_size); }
};

}  // namespace logging
}  // namespace rex
