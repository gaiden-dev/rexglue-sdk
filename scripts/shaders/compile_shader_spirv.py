#!/usr/bin/env python3
# Compiles one shader to a SPIR-V C header, like xenia's `xb buildshaders`.
#
# Usage: compile_shader_spirv.py <input_path> <output_path>
#
# glslangValidator, spirv-opt and spirv-dis are taken from $VULKAN_SDK/bin
# (or Bin) if VULKAN_SDK is set, else from PATH.

import os
import subprocess
import sys
import tempfile

STAGES = {
    "vs": "vert", "hs": "tesc", "ds": "tese",
    "gs": "geom", "ps": "frag", "cs": "comp",
}

# #version and extensions must be before everything else in a GLSL file, can't
# use a language conditional to add them; #include preserves line numbers.
XESL_WRAPPER = (
    "#version 460\n"
    "#extension GL_EXT_control_flow_attributes : require\n"
    "#extension GL_EXT_samplerless_texture_functions : require\n"
    "#extension GL_GOOGLE_include_directive : require\n"
    "#include \"%s\"\n"
)


def _tool(bin_dir, name):
  if bin_dir is None:
    return name
  path = os.path.join(bin_dir, name)
  if sys.platform == "win32" and not os.path.exists(path):
    path += ".exe"
  return path


def find_vulkan_tools():
  """Returns (glslangValidator, spirv-opt, spirv-dis) paths."""
  bin_dir = None
  vulkan_sdk = os.environ.get("VULKAN_SDK")
  if vulkan_sdk:
    for sub in ("bin", "Bin"):
      if os.path.isdir(os.path.join(vulkan_sdk, sub)):
        bin_dir = os.path.join(vulkan_sdk, sub)
        break
  return (_tool(bin_dir, "glslangValidator"), _tool(bin_dir, "spirv-opt"),
          _tool(bin_dir, "spirv-dis"))


def shader_identifier(filename):
  """'foo.cs.xesl' -> 'foo_cs'."""
  return os.path.splitext(os.path.basename(filename))[0].replace(".", "_")


def parse_stage(filename):
  identifier = shader_identifier(filename)
  return STAGES.get(identifier[-2:]) if len(identifier) > 2 else None


def _run(args, stdin_data=None):
  result = subprocess.run(args, input=stdin_data, stdout=subprocess.PIPE,
                          stderr=subprocess.STDOUT)
  return result.returncode, result.stdout.decode("utf-8", "replace").strip()


def write_header(output_path, identifier, spv_path, dis_path):
  with open(dis_path, "r") as dis_file:
    dis_data = dis_file.read()
  with open(spv_path, "rb") as spv_file:
    spv_data = spv_file.read()
  if len(spv_data) % 4 != 0:
    raise ValueError("SPIR-V shader is misaligned")
  with open(output_path, "w", newline="\n") as out:
    out.write("// Generated with `xb buildshaders`.\n#if 0\n")
    if dis_data:
      out.write(dis_data)
      if dis_data[-1] != "\n":
        out.write("\n")
    out.write("#endif\n\nconst uint32_t %s[] = {" % identifier)
    # SPIR-V consists of host-endian 32-bit words, six per line.
    for offset in range(0, len(spv_data), 4):
      out.write("\n    " if offset % 24 == 0 else " ")
      out.write("0x%08X," %
                int.from_bytes(spv_data[offset:offset + 4], sys.byteorder))
    out.write("\n};\n")


def compile_shader(input_path, output_path, tools=None):
  """Compiles one shader. Returns (ok, message)."""
  input_path = os.path.abspath(input_path)
  src_name = os.path.basename(input_path)
  src_dir = os.path.dirname(input_path)
  src_is_xesl = src_name.endswith(".xesl")
  stage = parse_stage(src_name)
  if stage is None:
    return (False, f"cannot determine shader stage from: {src_name}")
  identifier = shader_identifier(src_name)
  glslang, spirv_opt, spirv_dis = tools or find_vulkan_tools()
  os.makedirs(os.path.dirname(os.path.abspath(output_path)), exist_ok=True)

  with tempfile.TemporaryDirectory() as tmp:
    glslang_spv = os.path.join(tmp, identifier + ".glslang.spv")
    opt_spv = os.path.join(tmp, identifier + ".spv")
    dis_txt = os.path.join(tmp, identifier + ".txt")
    # --stdin must be before -S for some reason.
    glslang_args = [
        glslang,
        "--stdin" if src_is_xesl else input_path,
        "-DSHADING_LANGUAGE_GLSL_XE=1",
        "-S", stage,
        "-o", glslang_spv,
        "-V",
    ]
    # When compiling from stdin, there's no directory containing the file.
    if src_is_xesl:
      glslang_args.append("-I" + src_dir)
    try:
      code, output = _run(glslang_args, (XESL_WRAPPER % src_name).encode()
                          if src_is_xesl else None)
    except FileNotFoundError as error:
      return (False, f"could not run {glslang}: {error} (set VULKAN_SDK or "
              "put the Vulkan SDK tools on PATH)")
    if code != 0:
      return (False, f"glslangValidator failed:\n{output}")
    # Optimize, then canonicalize IDs to improve executable compression.
    # Debug information (binding and member names) is kept for RenderDoc.
    code, output = _run([spirv_opt, "-O", "--canonicalize-ids", glslang_spv,
                         "-o", opt_spv])
    if code != 0:
      return (False, f"spirv-opt failed:\n{output}")
    code, output = _run([spirv_dis, "-o", dis_txt, opt_spv])
    if code != 0:
      return (False, f"spirv-dis failed:\n{output}")
    try:
      write_header(output_path, identifier, opt_spv, dis_txt)
    except (OSError, ValueError) as error:
      return (False, f"writing header failed: {error}")
  return (True, "")


def main(argv):
  if len(argv) != 3:
    print(f"Usage: {argv[0]} <input_path> <output_path>", file=sys.stderr)
    return 1
  ok, message = compile_shader(argv[1], argv[2])
  if not ok:
    print(f"ERROR: failed to compile SPIR-V shader "
          f"{os.path.basename(argv[1])}:\n{message}", file=sys.stderr)
    return 1
  return 0


if __name__ == "__main__":
  sys.exit(main(sys.argv))
