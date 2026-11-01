#!/usr/bin/env python3
"""Regenerates the precompiled GPU shader headers under src/graphics/shaders,
mirroring xenia's `xb buildshaders`.

Every stage-suffixed source (name.<stage>.<ext>, stage in vs/hs/ds/gs/ps/cs):
  .xesl / .hlsl -> bytecode/d3d12_5_1/<id>.h   (DXBC SM 5.1, fxc)
  .xesl / .glsl -> vulkan_spirv/<id>.h         (SPIR-V, glslangValidator)
where <id> is the file name with dots replaced by underscores and the
extension dropped (resolve_full_8bpp.cs.xesl -> resolve_full_8bpp_cs).

Usage:
  python scripts/shaders/build_gpu_shaders.py [--dxbc-only | --spirv-only]
      [--filter SUBSTR] [--jobs N] [--shader-dir DIR] [--list] [--verbose]
"""

import argparse
import concurrent.futures
import os
import sys
import time

SCRIPT_DIR = os.path.dirname(os.path.abspath(__file__))
sys.path.insert(0, SCRIPT_DIR)

import compile_shader_dxbc  # noqa: E402
import compile_shader_spirv  # noqa: E402

REPO_ROOT = os.path.abspath(os.path.join(SCRIPT_DIR, "..", ".."))
DEFAULT_SHADER_DIR = os.path.join(REPO_ROOT, "src", "graphics", "shaders")

STAGES = ("vs", "hs", "ds", "gs", "ps", "cs")
BACKENDS = {
    # name: (source extensions, output subdirectory, compile function)
    "dxbc": ((".xesl", ".hlsl"), os.path.join("bytecode", "d3d12_5_1"),
             compile_shader_dxbc.compile_shader),
    "spirv": ((".xesl", ".glsl"), "vulkan_spirv",
              compile_shader_spirv.compile_shader),
}


def identifier_of(filename):
  return os.path.splitext(filename)[0].replace(".", "_")


def stage_of(filename):
  identifier = identifier_of(filename)
  stage = identifier[-2:]
  if len(identifier) < 3 or stage not in STAGES:
    return None
  return stage


def collect_jobs(shader_dir, backends, name_filter):
  """Returns (jobs, warnings); jobs are (backend, source, output, id)."""
  jobs = []
  warnings = []
  sources = sorted(os.listdir(shader_dir))
  for backend in backends:
    extensions, out_subdir, _ = BACKENDS[backend]
    out_dir = os.path.join(shader_dir, out_subdir)
    by_id = {}
    for name in sources:
      ext = os.path.splitext(name)[1]
      if ext not in extensions or stage_of(name) is None:
        continue
      by_id.setdefault(identifier_of(name), []).append(name)
    for identifier, names in sorted(by_id.items()):
      if name_filter and name_filter not in identifier:
        continue
      chosen = names[0]
      if len(names) > 1:
        # Prefer the cross-backend .xesl source over a legacy single-backend
        # .hlsl/.glsl one.
        xesl = [n for n in names if n.endswith(".xesl")]
        chosen = xesl[0] if xesl else names[0]
        skipped = [n for n in names if n != chosen]
        warnings.append(f"[{backend}] {identifier}: multiple sources "
                        f"{names}; using {chosen}, ignoring {skipped}")
      jobs.append((backend, os.path.join(shader_dir, chosen),
                   os.path.join(out_dir, identifier + ".h"), identifier))
  return jobs, warnings


def run_job(job):
  backend, source, output, identifier = job
  compile_fn = BACKENDS[backend][2]
  start = time.monotonic()
  ok, message = compile_fn(source, output)
  return (job, ok, message, time.monotonic() - start)


def main():
  parser = argparse.ArgumentParser(
      description="Regenerates the precompiled GPU shader headers.")
  group = parser.add_mutually_exclusive_group()
  group.add_argument("--dxbc-only", action="store_true",
                     help="only build DXBC headers (bytecode/d3d12_5_1)")
  group.add_argument("--spirv-only", action="store_true",
                     help="only build SPIR-V headers (vulkan_spirv)")
  parser.add_argument("--filter", metavar="SUBSTR", default="",
                      help="only build shaders whose identifier contains "
                      "SUBSTR (e.g. texture_load_, resolve_full_8bpp)")
  parser.add_argument("--jobs", "-j", type=int, default=os.cpu_count() or 1,
                      help="parallel compiler processes (default: CPU count)")
  parser.add_argument("--shader-dir", default=DEFAULT_SHADER_DIR,
                      help="shader source directory (default: "
                      "src/graphics/shaders)")
  parser.add_argument("--list", action="store_true",
                      help="list what would be built and exit")
  parser.add_argument("--verbose", "-v", action="store_true",
                      help="print every successfully built header")
  args = parser.parse_args()

  shader_dir = os.path.abspath(args.shader_dir)
  if not os.path.isdir(shader_dir):
    print(f"ERROR: shader directory not found: {shader_dir}", file=sys.stderr)
    return 2

  backends = ["dxbc", "spirv"]
  if args.dxbc_only:
    backends = ["dxbc"]
  elif args.spirv_only:
    backends = ["spirv"]

  jobs, warnings = collect_jobs(shader_dir, backends, args.filter)
  for warning in warnings:
    print(f"WARNING: {warning}")
  if not jobs:
    print("Nothing to build.")
    return 0
  if args.list:
    for backend, source, output, identifier in jobs:
      print(f"[{backend}] {os.path.basename(source)} -> "
            f"{os.path.relpath(output, shader_dir)}")
    print(f"{len(jobs)} header(s) would be built.")
    return 0

  # Fail early with a clear message if a compiler is missing.
  if "dxbc" in backends and not compile_shader_dxbc.find_fxc():
    print("ERROR: fxc not found. Set FXC_PATH or install the Windows SDK; "
          "use --spirv-only to skip DXBC.", file=sys.stderr)
    return 2

  counts = {backend: 0 for backend in backends}
  failures = []
  start = time.monotonic()
  with concurrent.futures.ThreadPoolExecutor(
      max_workers=max(1, args.jobs)) as pool:
    for job, ok, message, seconds in pool.map(run_job, jobs):
      backend, source, output, identifier = job
      if ok:
        counts[backend] += 1
        if args.verbose:
          print(f"[{backend}] {identifier} ({seconds:.1f}s)")
      else:
        failures.append((job, message))
        print(f"FAILED [{backend}] {os.path.basename(source)}")

  elapsed = time.monotonic() - start
  print()
  for backend in backends:
    print(f"{backend}: {counts[backend]} header(s) built into "
          f"{os.path.join(shader_dir, BACKENDS[backend][1])}")
  if warnings:
    print(f"{len(warnings)} warning(s) (see above).")
  if failures:
    print(f"\n{len(failures)} shader(s) FAILED to compile "
          f"({elapsed:.1f}s total):")
    for (backend, source, output, identifier), message in failures:
      print(f"\n--- [{backend}] {os.path.basename(source)} -> "
            f"{os.path.relpath(output, shader_dir)}")
      print(message or "(no compiler output)")
    return 1
  print(f"All {len(jobs)} shader(s) compiled successfully in "
        f"{elapsed:.1f}s.")
  return 0


if __name__ == "__main__":
  sys.exit(main())
