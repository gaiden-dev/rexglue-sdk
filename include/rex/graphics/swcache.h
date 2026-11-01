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

#include <rex/memory/swcache.h>

// The GPU code (like xenia's) refers to the software cache helpers as
// `swcache::` from inside rex::graphics; the implementation lives in the base
// library (rex::swcache) so that rex::memory::RingBuffer can use it as well.
namespace rex::graphics {
namespace swcache = ::rex::swcache;
}  // namespace rex::graphics
