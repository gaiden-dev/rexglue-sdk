#!/usr/bin/env python3
# Compiles one shader to a DXBC C header with FXC, like xenia's `xb buildshaders`.
#
# Usage: compile_shader_dxbc.py <input_path> <output_path>
#
# FXC is taken from FXC_PATH, else from the newest Windows 10/11 SDK
# (Windows Kits\10\bin\<version>\x64\fxc.exe); on non-Windows hosts it is run
# through wine.

import os
import re
import subprocess
import sys
from glob import glob

STAGES = ("vs", "hs", "ds", "gs", "ps", "cs")


def _sdk_version(path):
  match = re.search(r"[\\/](\d+(?:\.\d+)*)[\\/]x64[\\/]fxc\.exe$", path, re.I)
  return tuple(int(p) for p in match.group(1).split(".")) if match else ()


def find_fxc():
  fxc = os.environ.get("FXC_PATH")
  if fxc:
    return fxc
  program_files = os.environ.get("ProgramFiles(x86)",
                                 r"C:\Program Files (x86)")
  candidates = glob(os.path.join(program_files, "Windows Kits", "10", "bin",
                                 "*", "x64", "fxc.exe"))
  return max(candidates, key=_sdk_version) if candidates else None


def shader_identifier(filename):
  """'foo.cs.xesl' -> 'foo_cs'."""
  return os.path.splitext(os.path.basename(filename))[0].replace(".", "_")


def parse_stage(filename):
  identifier = shader_identifier(filename)
  stage = identifier[-2:]
  return stage if len(identifier) > 2 and stage in STAGES else None


def compile_shader(input_path, output_path, fxc=None):
  """Compiles one shader. Returns (ok, message)."""
  fxc = fxc or find_fxc()
  if not fxc:
    return (False, "could not find fxc: set FXC_PATH or install the Windows "
            "SDK (Windows Kits\\10\\bin\\<ver>\\x64\\fxc.exe)")
  input_path = os.path.abspath(input_path)
  stage = parse_stage(input_path)
  if stage is None:
    return (False, f"cannot determine shader stage from: {input_path}")
  args = [] if sys.platform == "win32" else ["wine"]
  args += [
      fxc,
      "/D", "SHADING_LANGUAGE_HLSL_XE=1",
      "/I", os.path.dirname(input_path),
      "/Fh", output_path,
      "/T", f"{stage}_5_1",
      "/Vn", shader_identifier(input_path),
      "/nologo",
      input_path,
  ]
  os.makedirs(os.path.dirname(os.path.abspath(output_path)), exist_ok=True)
  # FXC writes errors and warnings to stderr; stdout only carries status noise.
  result = subprocess.run(args, stdout=subprocess.DEVNULL,
                          stderr=subprocess.PIPE)
  if result.returncode != 0:
    return (False, result.stderr.decode("utf-8", "replace").strip())
  # FXC writes CRLF; the repository stores text files with LF.
  with open(output_path, "rb") as header:
    data = header.read()
  with open(output_path, "wb") as header:
    header.write(data.replace(b"\r\n", b"\n"))
  return (True, "")


def main(argv):
  if len(argv) != 3:
    print(f"Usage: {argv[0]} <input_path> <output_path>", file=sys.stderr)
    return 1
  ok, message = compile_shader(argv[1], argv[2])
  if not ok:
    print(f"ERROR: failed to compile DXBC shader "
          f"{os.path.basename(argv[1])}:\n{message}", file=sys.stderr)
    return 1
  return 0


if __name__ == "__main__":
  sys.exit(main(sys.argv))
