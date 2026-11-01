/**
 * @file        rex/graphics/pipeline/texture/replacement.h
 *
 * @brief       Texture dump and replacement pipeline.
 *
 *              Textures are identified by a stable content hash (XXH3 over the
 *              raw guest bytes as seen in physical memory — tiled and
 *              big-endian, exactly as the Xbox GPU would read them).  This
 *              makes the hash address-independent and run-independent.
 *
 *              Dump layout  (relative to the configured textures folder):
 *                  dump/<hash16>_<w>x<h>_<fmt_name>.dds
 *
 *              Replacement layout (scanned once at init, hot-reloaded on demand via Rescan()):
 *                  replace/<hash16>.dds   (RGBA8/BGRA8 or BC1/BC2/BC3)
 *                  replace/<hash16>.png   (RGBA8; loaded via stb_image)
 *
 *              Dump DDS format:
 *                - Compressed formats (DXT1/DXT3/DXT5/DXN/CTX1/DXT3A/DXT5A):
 *                    FOURCC DDS with raw BC blocks — lossless, directly usable
 *                    as a base for replacement authoring.
 *                - Uncompressed formats: RGBA8 unorm after untiling + endian
 *                    swap + channel expansion to 8bpc.
 *
 */
#pragma once

#include <cstddef>
#include <cstdint>
#include <filesystem>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

#include <rex/cvar.h>
#include <rex/graphics/xenos.h>

// CVARs controlling the dump/replace pipeline (defined in cache.cpp).
REXCVAR_DECLARE(bool, texture_dump_enabled);
REXCVAR_DECLARE(bool, texture_replace_enabled);
REXCVAR_DECLARE(std::string, texture_folder);

namespace rex::graphics {

// ---------------------------------------------------------------------------
// Replacement descriptor returned to the injection path
// ---------------------------------------------------------------------------
struct TextureReplacementData {
  // Decoded pixels: RGBA8 unorm, row-major, tightly packed (no row padding).
  std::vector<uint8_t> pixels;
  uint32_t width = 0;
  uint32_t height = 0;
  // Number of mip levels present in the replacement file (>= 1).
  uint32_t mip_levels = 1;
};

// ---------------------------------------------------------------------------
// TextureReplacement
// ---------------------------------------------------------------------------
class TextureReplacement {
 public:
  explicit TextureReplacement(std::filesystem::path textures_dir);
  ~TextureReplacement() = default;

  TextureReplacement(const TextureReplacement&) = delete;
  TextureReplacement& operator=(const TextureReplacement&) = delete;

  // Rescans textures/replace/ and rebuilds the hash→path index.
  void Rescan();

  // ---------------------------------------------------------------------------
  // Dump path
  // ---------------------------------------------------------------------------
  // Untiles, endian-swaps, and writes the guest texture to a DDS file.
  //   guest_bytes  : raw physical memory at base_page << 12
  //   guest_size   : GetGuestBaseSize() bytes
  //   width/height : texel dimensions
  //   pitch_blocks : TextureKey::pitch (pitch in units of 32 texels)
  //   tiled        : TextureKey::tiled
  //   format       : TextureKey::format
  //   endianness   : TextureKey::endianness
  void DumpTexture(uint64_t content_hash, uint32_t width, uint32_t height, uint32_t pitch_blocks,
                   bool tiled, xenos::TextureFormat format, xenos::Endian endianness,
                   const uint8_t* guest_bytes, uint32_t guest_size) const;

  // ---------------------------------------------------------------------------
  // Injection path
  // ---------------------------------------------------------------------------
  // Returns a pointer into the internal cache, or nullptr if not found.
  // The pointer is valid until the next call to Rescan().
  [[nodiscard]] const TextureReplacementData* FindReplacement(uint64_t content_hash) const;

  // ---------------------------------------------------------------------------
  // Hash
  // ---------------------------------------------------------------------------
  static uint64_t HashGuestData(const uint8_t* data, size_t size);

  std::filesystem::path dump_dir() const { return textures_dir_ / "dump"; }
  std::filesystem::path replace_dir() const { return textures_dir_ / "replace"; }

 private:
  std::filesystem::path textures_dir_;
  std::unordered_map<uint64_t, std::filesystem::path> replacements_;

  // Textures that have been loaded from disk are cached here so that
  // FindReplacement never touches the filesystem after the first load.
  mutable std::unordered_map<uint64_t, TextureReplacementData> pixel_cache_;
  // Hashes that failed to load are remembered so we don't retry every frame.
  mutable std::unordered_set<uint64_t> failed_cache_;

  static bool WriteDDS_RGBA8(const std::filesystem::path& path, uint32_t width, uint32_t height,
                             const uint8_t* rgba8_rows, uint32_t row_pitch_bytes);

  static bool WriteDDS_BC(const std::filesystem::path& path, uint32_t width, uint32_t height,
                          const uint8_t* bc_blocks, uint32_t bytes_per_block, uint32_t fourcc);

  static bool ReadDDS(const std::filesystem::path& path, TextureReplacementData& out);

  static bool ReadPNG(const std::filesystem::path& path, TextureReplacementData& out);
};

}  // namespace rex::graphics
