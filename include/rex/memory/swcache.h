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
#include <cstring>

#include <rex/assert.h>
#include <rex/platform.h>

#if REX_ARCH_AMD64
#include <immintrin.h>
#endif

// Software prefetch / cache fence helpers, ported from xenia-canary's
// xenia/base/memory.h (namespace swcache) for the GPU code that was written
// against them (texture binding prefetch, ring buffer prefetched reads, shared
// memory upload fences). Only use these if you're absolutely certain you know
// what you're doing - misuse can easily tank performance, as CPUs have
// excellent automatic prefetchers.

namespace rex::swcache {

#if REX_COMPILER_CLANG == 1 || REX_COMPILER_GNUC == 1
REX_FORCEINLINE static void PrefetchW(const void* addr) {
  __builtin_prefetch(addr, 1, 0);
}
REX_FORCEINLINE static void PrefetchNTA(const void* addr) {
  __builtin_prefetch(addr, 0, 0);
}
REX_FORCEINLINE static void PrefetchL3(const void* addr) {
  __builtin_prefetch(addr, 0, 1);
}
REX_FORCEINLINE static void PrefetchL2(const void* addr) {
  __builtin_prefetch(addr, 0, 2);
}
REX_FORCEINLINE static void PrefetchL1(const void* addr) {
  __builtin_prefetch(addr, 0, 3);
}
#elif REX_ARCH_AMD64 == 1 && REX_COMPILER_MSVC == 1
REX_FORCEINLINE static void PrefetchW(const void* addr) {
  _m_prefetchw(addr);
}
REX_FORCEINLINE static void PrefetchNTA(const void* addr) {
  _mm_prefetch(reinterpret_cast<const char*>(addr), _MM_HINT_NTA);
}
REX_FORCEINLINE static void PrefetchL3(const void* addr) {
  _mm_prefetch(reinterpret_cast<const char*>(addr), _MM_HINT_T2);
}
REX_FORCEINLINE static void PrefetchL2(const void* addr) {
  _mm_prefetch(reinterpret_cast<const char*>(addr), _MM_HINT_T1);
}
REX_FORCEINLINE static void PrefetchL1(const void* addr) {
  _mm_prefetch(reinterpret_cast<const char*>(addr), _MM_HINT_T0);
}
#else
REX_FORCEINLINE static void PrefetchW(const void* /*addr*/) {}
REX_FORCEINLINE static void PrefetchNTA(const void* /*addr*/) {}
REX_FORCEINLINE static void PrefetchL3(const void* /*addr*/) {}
REX_FORCEINLINE static void PrefetchL2(const void* /*addr*/) {}
REX_FORCEINLINE static void PrefetchL1(const void* /*addr*/) {}
#endif

enum class PrefetchTag { Write, Nontemporal, Level3, Level2, Level1 };

template <PrefetchTag tag>
REX_FORCEINLINE static void Prefetch(const void* addr) {
  if constexpr (tag == PrefetchTag::Write) {
    PrefetchW(addr);
  } else if constexpr (tag == PrefetchTag::Nontemporal) {
    PrefetchNTA(addr);
  } else if constexpr (tag == PrefetchTag::Level3) {
    PrefetchL3(addr);
  } else if constexpr (tag == PrefetchTag::Level2) {
    PrefetchL2(addr);
  } else if constexpr (tag == PrefetchTag::Level1) {
    PrefetchL1(addr);
  } else {
    assert_always("Unknown prefetch tag");
  }
}

#if REX_ARCH_AMD64 == 1
union alignas(REX_HOST_CACHE_LINE_SIZE) CacheLine {
  struct {
    __m256 low32;
    __m256 high32;
  };
  struct {
    __m128i xmms[4];
  };
  float floats[REX_HOST_CACHE_LINE_SIZE / sizeof(float)];
};

// Non-temporal (streaming) full cache line store; destination must be
// cache-line-aligned.
REX_FORCEINLINE static void WriteLineNT(CacheLine* REX_RESTRICT destination,
                                        const CacheLine* REX_RESTRICT source) {
  assert_true((reinterpret_cast<uintptr_t>(destination) & 63ULL) == 0);
  __m256 low = _mm256_loadu_ps(&source->floats[0]);
  __m256 high = _mm256_loadu_ps(&source->floats[8]);
  _mm256_stream_ps(&destination->floats[0], low);
  _mm256_stream_ps(&destination->floats[8], high);
}
// Non-temporal full cache line load; source must be cache-line-aligned.
REX_FORCEINLINE static void ReadLineNT(CacheLine* REX_RESTRICT destination,
                                       const CacheLine* REX_RESTRICT source) {
  assert_true((reinterpret_cast<uintptr_t>(source) & 63ULL) == 0);
  __m128i first = _mm_stream_load_si128(const_cast<__m128i*>(&source->xmms[0]));
  __m128i second = _mm_stream_load_si128(const_cast<__m128i*>(&source->xmms[1]));
  __m128i third = _mm_stream_load_si128(const_cast<__m128i*>(&source->xmms[2]));
  __m128i fourth = _mm_stream_load_si128(const_cast<__m128i*>(&source->xmms[3]));
  destination->xmms[0] = first;
  destination->xmms[1] = second;
  destination->xmms[2] = third;
  destination->xmms[3] = fourth;
}
REX_FORCEINLINE static void ReadLine(CacheLine* REX_RESTRICT destination,
                                     const CacheLine* REX_RESTRICT source) {
  assert_true((reinterpret_cast<uintptr_t>(source) & 63ULL) == 0);
  __m256 low = _mm256_loadu_ps(&source->floats[0]);
  __m256 high = _mm256_loadu_ps(&source->floats[8]);
  _mm256_storeu_ps(&destination->floats[0], low);
  _mm256_storeu_ps(&destination->floats[8], high);
}
REX_FORCEINLINE static void WriteLine(CacheLine* REX_RESTRICT destination,
                                      const CacheLine* REX_RESTRICT source) {
  assert_true((reinterpret_cast<uintptr_t>(destination) & 63ULL) == 0);
  __m256 low = _mm256_loadu_ps(&source->floats[0]);
  __m256 high = _mm256_loadu_ps(&source->floats[8]);
  _mm256_storeu_ps(&destination->floats[0], low);
  _mm256_storeu_ps(&destination->floats[8], high);
}

REX_FORCEINLINE static void WriteFence() {
  _mm_sfence();
}
REX_FORCEINLINE static void ReadFence() {
  _mm_lfence();
}
REX_FORCEINLINE static void ReadWriteFence() {
  _mm_mfence();
}
#else
union alignas(REX_HOST_CACHE_LINE_SIZE) CacheLine {
  uint8_t bvals[REX_HOST_CACHE_LINE_SIZE];
};

REX_FORCEINLINE static void WriteLineNT(CacheLine* destination, const CacheLine* source) {
  std::memcpy(destination, source, REX_HOST_CACHE_LINE_SIZE);
}
REX_FORCEINLINE static void ReadLineNT(CacheLine* destination, const CacheLine* source) {
  std::memcpy(destination, source, REX_HOST_CACHE_LINE_SIZE);
}
REX_FORCEINLINE static void WriteLine(CacheLine* destination, const CacheLine* source) {
  std::memcpy(destination, source, REX_HOST_CACHE_LINE_SIZE);
}
REX_FORCEINLINE static void ReadLine(CacheLine* destination, const CacheLine* source) {
  std::memcpy(destination, source, REX_HOST_CACHE_LINE_SIZE);
}

REX_FORCEINLINE static void WriteFence() {}
REX_FORCEINLINE static void ReadFence() {}
REX_FORCEINLINE static void ReadWriteFence() {}
#endif

}  // namespace rex::swcache
