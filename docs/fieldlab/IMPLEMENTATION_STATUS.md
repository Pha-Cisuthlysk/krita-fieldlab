# Current Implementation Status

Audit date: 2026-08-23

Audited branch: `fieldlab`

Audited baseline commit:
`2ec9495a7fc0811345ab72361ce45053f98ce65c`
(`Separate Field Lab semantic core target`)

Initial audit scope: documentation and repository inspection only.

Implementation update: the batch-evaluation task was started from commit
`1f1abd81288e905efed9182fc9fd23a96fc74a01` after the audit completed.

Primary requirement IDs reviewed: `FL-PROD`, `FL-PLAT`, `FL-GRAPH`,
`FL-PREVIEW`, `FL-SCALAR`, `FL-OPS`, plus the protected near-term families.

Requirement state: ACTIVE

Overall implementation state: PARTIAL / TESTED WINDOWS / ANDROID NOT TESTED

Audit basis: current `fieldlab` branch as inspected after the source corpus was
received.

## Summary

The repository is in the semantic graph and product-scaffolding stage. The
native prototype exposes batch position and grid evaluation as its primary
field contracts while retaining single-sample evaluation for debugging and
tests. Five host-neutral interchange types and a catalog covering all 38
canonical requirement families now preserve extension points without claiming
their algorithms are implemented. Field Lab has not become a noise-only
system, and the semantic core remains separate from the docker.

## Implemented/partial

| Component | Status | Audit note |
|---|---|---|
| Field Lab Krita docker/plugin | IMPLEMENTED / TESTED WINDOWS | Contained `kritafieldlab` module; user demonstrated the preview before the latest core-only refactors |
| `NodeDescriptor` scaffold | PARTIAL | Five manual native prototype nodes only: Constant, Position X/Y, Add, Multiply |
| Core interchange types | SCAFFOLDED | UI-independent `ScalarField2D`, `VectorField2D`, `RasterSource`, `PointSet`, and `PathSet` value containers; no Krita adapters or algorithms yet |
| Capability catalog | IMPLEMENTED AS ACCOUNTABILITY SCAFFOLD | All 38 ledger families have unique stable IDs, requirement states, and current stages; catalog entries are not executable features |
| Capability browser | SCAFFOLDED / RUNTIME LOADED WINDOWS | UI-only searchable and state-filterable Systems tab groups all catalog entries into eight visible areas; no visual nodes or feature execution controls yet |
| `FieldGraph` semantic model | PARTIAL | Nodes, connections, parameter mutation, input disconnection, and node removal exist; persistence and undo integration do not |
| Scalar evaluator | PROTOTYPE / DEBUG | Recursive single-sample arithmetic/position convenience path with hard-coded native type dispatch |
| Batch evaluator | IMPLEMENTED FOR NATIVE SCAFFOLD | `evaluatePositions(...)` and normalized `evaluateGrid(...)` evaluate and cache each reachable node once per batch |
| FastNoise2 dependency | SPIKE / TESTED WINDOWS | Exact v1.1.1 package and metadata/batch probe pass with one recorded FastSIMD llvm-mingw patch; normal builds remain unlinked |
| Graph validation | PARTIAL | Checks known types, ports, value types, required inputs, and cycles |
| 2D preview | PARTIAL / BATCHED | Auto-updating normalized 128x128 grayscale prototype consumes `evaluateGrid(...)` |
| Scalar reference sampler | DEBUG/TEST ONLY | `FieldGraphReferenceSampler::sampleScalarReference()` preserves the old per-pixel loop as an oracle and has no production caller |
| Unit tests | PARTIAL / TESTED WINDOWS | One guiless CTest target with 15 focused test methods |
| Semantic-core build target | IMPLEMENTED | `kritafieldlabcore` is a Qt-Core-only static target shared by plugin and tests |

## Evidence inspected

- `plugins/dockers/fieldlab/CMakeLists.txt` separates `kritafieldlabcore` from
  the `kritafieldlab` UI module.
- Core graph, evaluator, sampler, validator, and descriptor sources include
  Qt Core facilities only; QWidget/QDockWidget/QImage use remains in the docker.
- `FieldGraphEvaluator::evaluatePositions()` and `evaluateGrid()` are Qt-Core-
  only contracts; the current native implementation caches one vector per
  reachable node for each batch.
- `FieldGraphReferenceSampler::sampleScalarReference()` contains the preserved
  per-pixel scalar loop and is referenced only by its parity test.
- `NodeDescriptor::builtInScalarNodes()` contains exactly five handwritten
  native scaffold descriptors.
- No FastNoise2 source is vendored and no production adapter or node catalog
  exists. An opt-in probe exercises `Metadata::GetAll` and batch generation
  against an isolated local package.
- `FieldGraphTest` covers graph connections, mutation, scalar and batch
  arithmetic, arbitrary positions, normalized grids, evaluator errors, cycles,
  descriptors, validation, finite output, repeatability, and reference parity.
- The local build tree is `RelWithDebInfo`, uses llvm-mingw Clang, and has
  `BUILD_TESTING=ON`.

## Not implemented yet

- production FastNoise2 integration and dependency recipe
- FastNoise2 metadata descriptor adapter
- FastNoise island compiler
- batch FastNoise evaluator
- graph persistence/versioning in `.kra`
- RasterSource Krita adapter and sampling
- bake to Krita layer/generator
- sensor/curve adapter
- exact EDT/SDF
- bounded line-art distance adapter
- vector-field evaluation and operators
- contours
- streamlines
- hatching
- PointSet/PathSet processing and Krita geometry adapters
- Android build/test
- tablet workspace
- passing-point curves
- Smart Fill UI
- Color Harmony UI

## Batch evaluation status

The primary native prototype contracts are now:

- `FieldGraphEvaluator::evaluateGrid(...)`
- `FieldGraphEvaluator::evaluatePositions(...)`

They resolve each reachable graph node once per batch and cache its output
vector. The docker preview uses the grid contract, and its center readout uses a
one-position batch.

The old nested scalar loop remains as
`FieldGraphReferenceSampler::sampleScalarReference()` for correctness
comparison and debugging only. It has no docker or production caller and must
not regain one.

This satisfies the batch invariant for the five-node native scaffold. A future
FastNoise2 backend must implement these batch contracts without routing through
the reference sampler.

## Architecture guardrail verdict

| Guardrail | Verdict | Evidence |
|---|---|---|
| Painting-first Krita host | PASS | Work is contained in a docker/plugin; no Krita core rewrite was introduced |
| Semantic graph authoritative and UI-independent | PASS | Graph state and services live in `kritafieldlabcore`; the docker consumes them |
| FastNoise2 metadata catalog | SPIKE ONLY | Probe discovered 47 metadata types dynamically; only five native prototype descriptors exist and no production FastNoise catalog has been hand-authored |
| Batch/tile evaluation primary | PASS FOR CURRENT SCOPE | Docker uses batch grid/position contracts; scalar loop is isolated as a test/debug oracle |
| Krita preview/bake lifecycle | UNRESOLVED | No permanent `KisProcessingApplicator` vs generator-layer decision has been made |
| Android as first-class target | NOT TESTED | No Android ARM64 build, device test, S Pen test, or thermal/memory evidence exists |
| Architecture changes require approval | PASS | This audit introduces governance documentation only |

## Platform and test status

### Windows

- `FieldGraphTest`: PASS in the existing Windows build tree.
- `kritafieldlab`: PASS when built as the focused target.
- Current product-scaffold DLL was copied to the dev install and verified
  byte-for-byte at SHA-256
  `636322824DEA0F472F2AC921BDBE07CB5DD286904F9531CEF53BE85A57082A11`.
- Built and dev-installed plugin DLLs were verified with matching SHA-256
  hashes at the audited baseline.
- The user demonstrated the auto-updating preview at commit `cb467ff4d2`.
- Fresh runtime smoke: `krita.com --nosplash` produced a visible responsive
  Krita window, constructed `FieldLabDocker`, and loaded the exact installed
  `kritafieldlab.dll`. The minimized docker's child controls were not exposed
  to Windows UI Automation, so tab-level interaction was not independently
  automated in this task.

### Android ARM64 / Samsung Galaxy Tab S9 FE+

- Build: NOT TESTED
- Runtime: NOT TESTED
- S Pen/touch interaction: NOT TESTED
- Memory, NEON, thermal, battery, suspend/resume, and document-reopen behavior:
  NOT TESTED

No Android claim should be upgraded without concrete build and device evidence.

## Dependency and license status

- No new mandatory code dependency is present in Field Lab.
- Current Field Lab sources use Qt/Krita infrastructure and are marked
  `GPL-2.0-or-later`.
- FastNoise2 v1.1.1 and pinned FastSIMD are MIT-licensed and present only in an
  isolated local cache/install prefix.
- The complete version, license, API, Windows, Android, build-cost,
  maintenance-risk, subset, and rollback record is in
  `FASTNOISE2_DEPENDENCY.md`.
- Normal Field Lab targets do not find or link FastNoise2. The probe is gated
  by `FIELDLAB_ENABLE_FASTNOISE2_SPIKE`, which defaults to `OFF`.

## Current Codex-direction verdict

### Good

- Semantic model is being kept independent of the docker.
- A dedicated core target has been separated from the plugin UI.
- Tests and validation are being added before a large node editor.
- Preview work is happening before visual graph polish.

### Watch

- Do not grow a large handwritten built-in scalar catalog.
- Keep the reference sampler out of production call paths.
- Do not choose a permanent Krita preview/bake lifecycle without comparing the
  researched native options and obtaining approval for an architectural lock.
- Do not start QtNodes integration before the Android touch/S Pen spike.
- Do not let current Field Lab work erase Passing-Point Curves, Smart Fill,
  Color Harmony, or Tablet Workspace from the protected roadmap.

## Scope erosion check

PASS. The ledgers still explicitly retain:

- Passing-point curves, Smart Fill, Color Harmony, and Tablet Workspace
- fractals and procedural baking
- scalar, vector, and distance fields
- line-art distance and SDF
- domain warping and contours
- streamlines, hatching, and field flow
- intelligent coloring
- pressure/stylus/input modulation

Field Lab remains a multi-domain procedural system, not only a noise generator.

## Next three smallest canonical tasks

The batch task and Windows portion of the dependency spike are complete.
Android dependency validation remains blocked by the absent local toolchain.

1. Reproduce the pinned FastNoise2 package in `krita-deps-management` for
   Windows and Android ARM64, including the recorded FastSIMD patch and package
   size evidence.
2. Add versioned semantic graph persistence with round-trip and malformed-input
   tests, independent of any visual node editor or permanent Krita bake
   lifecycle choice.
3. After Android dependency validation passes, adapt FastNoise2 metadata into
   semantic descriptors and connect a minimal FastNoise island to the batch
   contracts; do not hand-author the production catalog.

## Audit task record

Task: Install the Field Lab accountability package and audit the current branch

Date/baseline: 2026-08-23 / `2ec9495a7f`

Requirements: `FL-PROD`, `FL-PLAT`, `FL-GRAPH`, `FL-PREVIEW`, `FL-SCALAR`,
`FL-OPS`, and scope-preservation governance

Requirement state: ACTIVE

Implementation state: ACCOUNTABILITY PACKAGE INSTALLED / AUDIT COMPLETE

Files changed: root `AGENTS.md` and `docs/fieldlab/` accountability documents

Reuse source: current Krita/Field Lab repository, existing build artifacts, and
the user-supplied historical audit package

New dependency/license: none

Architecture changed: No

Windows build/test: PASS; fresh focused `FieldGraphTest` and `kritafieldlab`
targets were confirmed up to date, and CTest reported zero failures

Android build/test: NOT TESTED

Unit/integration tests: documentation-only task; `FieldGraphTest` PASS

Performance implications: none from documentation; current per-pixel sampler
is formally recorded as a prototype red flag

Known limitations: no post-refactor GUI smoke test; no Android evidence; no
FastNoise2 integration; no persistence or bake path

What remains uncertain: permanent Krita preview/bake lifecycle and node-editor
choice remain unresolved approval-gated decisions

Next dependency: backend-neutral batch evaluation contract, followed by the
FastNoise2 dependency/metadata spike

Rollback note: revert the accountability-package commit; no production source
or build artifact behavior is changed by this audit

## Batch-evaluation task record

Task: Add backend-neutral batch evaluation and route the docker preview through
it

Date/starting commit: 2026-08-23 / `1f1abd8128`

Requirements: `FL-GRAPH`, `FL-PREVIEW`, `FL-SCALAR`, `FL-PROD`

Requirement state: ACTIVE

Implementation state: IMPLEMENTED / TESTED WINDOWS

Files changed: `FieldGraphEvaluator.*`, `FieldGraphSampler.*`,
`FieldLabDocker.cpp`, `FieldGraphTest.*`, root `AGENTS.md`, and this status
record

Reuse source: existing Field Lab graph/evaluator and Qt Core containers

New dependency/license: none

Architecture changed: No; this implements the already-canonical batch
invariant while preserving UI independence

Windows build/test: PASS; focused `FieldGraphTest` and `kritafieldlab` targets
build in the existing llvm-mingw `RelWithDebInfo` tree, CTest reports 1/1
passing, and the built/dev-installed DLLs match at SHA-256
`574F91A9875972A87133FF7B263C302793BEE8F55D2C380AC5B972C3E3050B80`;
the dev Krita runtime loaded that plugin without an observed startup failure

Android build/test: NOT TESTED

Unit/integration tests: 13 focused methods; new coverage includes arbitrary
position batches, normalized grids, invalid dimensions, oversized grids,
missing/unknown/cyclic graphs, non-finite values, repeatability, and scalar
reference parity

Performance implications: preview graph traversal changes from once per pixel
to once per reachable node per batch; the native scaffold still allocates
Qt vectors and is not a FastNoise performance claim

Known limitations: five hard-coded native prototype nodes only; no FastNoise2,
Android, persistence, bake path, benchmark, or independently inspected
post-change preview pixels

What remains uncertain: future FastNoise island compilation and permanent
Krita preview/bake lifecycle remain unresolved

Next dependency: FastNoise2 dependency/license/build/metadata spike

Rollback note: revert the batch-evaluation commit; the prior scalar reference
implementation remains isolated in `FieldGraphReferenceSampler`

## FastNoise2 dependency-spike task record

Task: Pin and validate FastNoise2 metadata and batch APIs without production
integration

Date/starting commit: 2026-08-23 / `1e50098449`

Requirements: `FL-PLAT`, `FL-GRAPH`, `FL-SCALAR`, `FL-PROD`

Requirement state: ACTIVE

Implementation state: SPIKE / TESTED WINDOWS / ANDROID NOT TESTED

Files changed: opt-in FastNoise2 probe/test CMake, recorded FastSIMD patch,
`FASTNOISE2_DEPENDENCY.md`, root `AGENTS.md`, `FEATURE_LEDGER.md`,
`REUSE_LEDGER.md`, `README.md`, and this status record

Reuse source: FastNoise2 v1.1.1 at
`903c1f2d2f9d53ddce94cd223f32727d9ab3aeaa` and FastSIMD at
`16450dae9528727e500e7254f635a671f9c7ee2d`

New dependency/license: optional spike dependency only; FastNoise2 and FastSIMD
are MIT-licensed and are not vendored or linked by normal Field Lab targets

Architecture changed: No; the spike validates the already-approved FastNoise2
backend direction while keeping the semantic graph and production plugin
independent

Windows build/test: PASS after applying the recorded one-line FastSIMD
llvm-mingw patch; static package installed in an isolated prefix; CTest 1/1 and
QtTest 4/4 pass; 47 metadata nodes discovered; AVX2 selected

Android build/test: NOT TESTED; no local SDK, NDK, dependency prefix, build
tree, or device is available

Unit/integration tests: opt-in `FastNoise2Probe` validates metadata uniqueness,
dynamic node creation, deterministic uniform-grid generation, arbitrary
position generation, finite output, and min/max contracts

Performance implications: FastNoise2 uses fused SIMD batch generation, but no
Field Lab benchmark or production FastNoise island exists yet; local
`RelWithDebInfo` archive is 24,414,188 bytes and is not a release-size claim

Known limitations: downstream compiler patch required; Android and release
packaging untested; strict-FP/reproducibility policy unresolved; no semantic
descriptor adapter, serialization mapping, island compiler, or docker caller

What remains uncertain: Android NDK compatibility, APK size, Galaxy Tab S9 FE+
runtime behavior, strict-FP policy, and long-term disposition of the FastSIMD
patch

Next dependency: reproducible `krita-deps-management` recipes for Windows and
Android ARM64

Rollback note: leave `FIELDLAB_ENABLE_FASTNOISE2_SPIKE` off or revert the spike
commit; no production target or document format depends on FastNoise2

## Product-scaffolding task record

Task: Add a reversible skeleton for the remaining canonical product scope
without adding visual nodes

Date/starting commit: 2026-08-23 / `741553c8d8`

Requirements: all 38 `FEATURE_LEDGER.md` families, with implementation focus on
`FL-GRAPH`, `FL-SCALAR`, `FL-VECTOR`, `FL-RASTER`, `FL-POINT`, and `FL-PATH`

Requirement state: ACTIVE / DEPENDENT / DEFERRED / REJECTED AS RECORDED

Implementation state: SCAFFOLDED / TESTED WINDOWS / ANDROID NOT TESTED

Files changed: UI-independent capability/data contracts, focused tests,
searchable docker Systems view, CMake source list, UI asset brief, and
accountability ledgers

Reuse source: Qt Core containers and the existing Field Lab core/docker split

New dependency/license: none; new source is `GPL-2.0-or-later`

Architecture changed: Yes, explicitly approved by the user as a bounded
scaffolding pass; no execution backend, bake lifecycle, persistence format, or
visual node framework was selected

Windows build/test: focused `kritafieldlab` and `FieldGraphTest` targets build;
CTest 1/1 passes with the existing Krita runtime paths; the 3,603,456-byte
built/dev-installed DLLs match at SHA-256
`636322824DEA0F472F2AC921BDBE07CB5DD286904F9531CEF53BE85A57082A11`;
a visible responsive dev Krita runtime constructed the docker and loaded that
exact module

Android build/test: NOT TESTED; the new contracts use Qt Core only, but no
Android ARM64 compile or device evidence exists

Unit/integration tests: 15 focused methods; new coverage checks all five core
interchange families, all 38 unique requirement IDs, roadmap-state counts, and
the five protected near-term families

Performance implications: one static 38-entry metadata catalog; no new image
algorithm, per-pixel path, backend call, or runtime dependency

Known limitations: catalog entries retain scope but do not implement features;
RasterSource is a semantic host reference only; vector, point, and path
containers have no processing adapters yet; minimized docker child controls
were not exposed to Windows UI Automation for tab-level automation

What remains uncertain: permanent preview/bake lifecycle, document schema,
execution interfaces, node editor, and Android behavior remain unresolved

Next dependency: versioned semantic graph persistence, or an explicitly chosen
small implementation slice from the scaffold

Rollback note: revert the product-scaffolding commit; no document format or
production backend depends on these additive contracts
