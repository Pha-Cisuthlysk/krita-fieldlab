# FastNoise2 Dependency Record

Record date: 2026-08-23

Status: WINDOWS SPIKE PASSED / ANDROID NOT TESTED / NOT A MANDATORY DEPENDENCY

## Exact upstream sources

FastNoise2:

- Repository: <https://github.com/Auburn/FastNoise2>
- Version: `v1.1.1`
- Commit: `903c1f2d2f9d53ddce94cd223f32727d9ab3aeaa`
- License: MIT, copyright Jordan Peck

FastSIMD, pinned by FastNoise2 `v1.1.1`:

- Repository: <https://github.com/Auburn/FastSIMD>
- Commit: `16450dae9528727e500e7254f635a671f9c7ee2d`
- License: MIT, copyright Jordan Peck

The Field Lab repository does not vendor either source tree. The local spike
used exact Git checkouts under `C:/Dev/cache` and `C:/Dev/_build`.

## Classification and reason

Classification: DIRECT/ADAPT

FastNoise2 is already the canonical default backend for scalar noise,
fractals, domain math, and contiguous FastNoise islands. It saves Field Lab
from maintaining its own SIMD noise algorithms, runtime dispatch, graph
serialization, and node reflection.

Krita supplies SIMD and raster infrastructure, but does not supply the same
runtime-configurable procedural-noise graph or metadata catalog. Replacing
FastSIMD with Krita's xsimd dependency during this spike would diverge from
FastNoise2 upstream and expand maintenance risk.

## Runtime files and APIs inspected

Primary headers:

- `FastNoise/FastNoise.h`
- `FastNoise/Metadata.h`
- `FastNoise/Generators/Generator.h`
- `FastSIMD/Utility/FeatureEnums.h`

Primary APIs:

- `FastNoise::Metadata::GetAll()`
- `FastNoise::Metadata::FormatMetadataNodeName(...)`
- `FastNoise::Metadata::CreateNode(...)`
- `FastNoise::Metadata::SerialiseNodeData(...)`
- `FastNoise::Metadata::DeserialiseNodeData(...)`
- `FastNoise::Generator::GenUniformGrid2D(...)`
- `FastNoise::Generator::GenPositionArray2D(...)`
- `FastNoise::Generator::GetActiveFeatureSet()`

The spike enumerates metadata and dynamically creates nodes. It does not
hand-author a production FastNoise descriptor catalog.

## Windows build evidence

Toolchain:

- Windows x86-64
- llvm-mingw Clang/Clang++ `21.1.6`
- Ninja
- CMake `3.31.12`
- `RelWithDebInfo`
- static library
- FastNoise tools, tests, and utilities disabled
- relaxed/default floating-point mode

The unmodified dependency failed because FastSIMD adds
`-Wa,-muse-unaligned-vector-move` to every MinGW build. Clang's integrated
assembler rejects that GNU assembler option.

The minimal compatibility patch is:

`plugins/dockers/fieldlab/fastnoise2/patches/0001-FastSIMD-limit-MinGW-assembler-flag-to-GNU.patch`

It limits the workaround to GNU/MinGW and leaves Android, MSVC, and non-MinGW
builds unchanged.

After applying the patch:

- FastNoise2 and FastSIMD compiled successfully.
- The package installed to the isolated
  `C:/Dev/_install/FastNoise2-v1.1.1` prefix.
- Exported CMake targets loaded successfully from `find_package`.
- `FastNoise2Probe` compiled inside the existing Krita build tree.
- CTest passed 1/1.
- QtTest passed 4/4 cases.
- Runtime metadata discovery found 47 unique node types.
- Every discovered metadata type created a runtime node successfully.
- Uniform-grid and arbitrary-position batch generation produced finite output.
- Repeated same-seed uniform-grid generation was deterministic on this machine.
- Runtime dispatch selected AVX2.

Local static archive:

- Size: 24,414,188 bytes (`RelWithDebInfo`)
- SHA-256:
  `444E276E3FB938AB0BF8C26B632844AAE93448A54E5D009855DFC11344CC62A5`

This archive size includes debug information and is not a release or APK size
claim.

## Android ARM64 status

Build: NOT TESTED

Runtime/device: NOT TESTED

The upstream project declares Android, AArch64, and NEON support, and the
inspected FastSIMD source contains AArch64/NEON feature selection. That is
upstream capability evidence only.

No Android SDK, NDK, Krita Android dependency prefix, or Android Krita build
tree is available in the local environment. Therefore this task provides no
Android compile, packaging, Galaxy Tab S9 FE+, thermal, memory, or S Pen
evidence.

The MinGW patch is not active on Android because `MINGW` is false there.

## Build-system cost

Recommended production route:

1. Add a pinned `ext_fastnoise2` recipe to
   `krita-deps-management`, not an online download in Krita's main build.
2. Pin both upstream commits and apply the recorded FastSIMD patch.
3. Disable FastNoise2 tools, tests, and utilities.
4. Build/install a static package for each supported platform.
5. Add FastNoise2 to the Windows and Android dependency seed files.
6. Make the production Field Lab core consume `FastNoise2::FastNoise` only
   after both dependency builds are reproducible.

Current repository integration is intentionally opt-in through
`FIELDLAB_ENABLE_FASTNOISE2_SPIKE=ON`. Normal builds do not find or link
FastNoise2.

## Maintenance and product risks

- Maintenance risk: medium. The API fit is strong, but a downstream compiler
  patch is currently required.
- Floating-point risk: default SIMD levels can differ slightly across CPUs.
  `FASTNOISE2_STRICT_FP` and feature-set locking need a product-level
  reproducibility/performance decision before serialized output guarantees are
  promised.
- Packaging risk: release and Android binary-size impact is unmeasured.
- Android risk: upstream support is not a substitute for an NDK build and
  device test.
- Metadata risk: presentation names, grouping, allowlists, and semantic IDs
  must be adapted without making upstream metadata the serialized Field Lab
  graph format.

## Smallest useful subset

The inspected FastNoise2 runtime `include` and `src` trees contain 37 files and
518,815 bytes. The inspected FastSIMD `include`, `src`, and `dispatch` trees
contain 41 files and 228,006 bytes.

Do not vendor a hand-pruned source copy yet. Prefer exact upstream commits plus
the one recorded patch so metadata registration and SIMD dispatch remain
internally consistent.

## Estimated engineering time saved

Reusing FastNoise2 avoids implementing and maintaining dozens of coherent
noise, fractal, blend, domain-warp, runtime-dispatch, metadata, and
serialization components. The expected saving is measured in months rather
than days, provided the dependency pipeline and Android build are validated.

## Rollback

- Configure with `FIELDLAB_ENABLE_FASTNOISE2_SPIKE=OFF` or omit the option.
- Revert the spike commit.
- No production Field Lab target currently links FastNoise2.
- No serialized document depends on FastNoise2 metadata or node IDs.
