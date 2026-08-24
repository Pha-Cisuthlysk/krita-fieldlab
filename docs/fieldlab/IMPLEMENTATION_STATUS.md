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

The repository is still in the semantic-graph skeleton stage. The native
prototype now exposes batch position and grid evaluation as its primary field
contracts while retaining single-sample evaluation for debugging and tests.
Field Lab has not become a noise-only system, and the semantic core remains
separate from the docker.

## Implemented/partial

| Component | Status | Audit note |
|---|---|---|
| Field Lab Krita docker/plugin | IMPLEMENTED / TESTED WINDOWS | Contained `kritafieldlab` module; user demonstrated the preview before the latest core-only refactors |
| `NodeDescriptor` scaffold | PARTIAL | Five manual native prototype nodes only: Constant, Position X/Y, Add, Multiply |
| `FieldGraph` semantic model | PARTIAL | Nodes, connections, parameter mutation, input disconnection, and node removal exist; persistence and undo integration do not |
| Scalar evaluator | PROTOTYPE / DEBUG | Recursive single-sample arithmetic/position convenience path with hard-coded native type dispatch |
| Batch evaluator | IMPLEMENTED FOR NATIVE SCAFFOLD | `evaluatePositions(...)` and normalized `evaluateGrid(...)` evaluate and cache each reachable node once per batch |
| Graph validation | PARTIAL | Checks known types, ports, value types, required inputs, and cycles |
| 2D preview | PARTIAL / BATCHED | Auto-updating normalized 128x128 grayscale prototype consumes `evaluateGrid(...)` |
| Scalar reference sampler | DEBUG/TEST ONLY | `FieldGraphReferenceSampler::sampleScalarReference()` preserves the old per-pixel loop as an oracle and has no production caller |
| Unit tests | PARTIAL / TESTED WINDOWS | One guiless CTest target with 13 focused test methods |
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
- No FastNoise2 source, metadata adapter, `Metadata::GetAll`, FastNoise node
  catalog, or FastNoise build integration exists in Field Lab.
- `FieldGraphTest` covers graph connections, mutation, scalar and batch
  arithmetic, arbitrary positions, normalized grids, evaluator errors, cycles,
  descriptors, validation, finite output, repeatability, and reference parity.
- The local build tree is `RelWithDebInfo`, uses llvm-mingw Clang, and has
  `BUILD_TESTING=ON`.

## Not implemented yet

- FastNoise2 integration
- FastNoise2 metadata descriptor adapter
- FastNoise island compiler
- batch FastNoise evaluator
- graph persistence/versioning in `.kra`
- RasterSource
- bake to Krita layer/generator
- sensor/curve adapter
- exact EDT/SDF
- bounded line-art distance adapter
- vector fields
- contours
- streamlines
- hatching
- PointSet/PathSet
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
| FastNoise2 metadata catalog | NOT STARTED | Only five native prototype descriptors exist; no FastNoise catalog has been hand-authored |
| Batch/tile evaluation primary | PASS FOR CURRENT SCOPE | Docker uses batch grid/position contracts; scalar loop is isolated as a test/debug oracle |
| Krita preview/bake lifecycle | UNRESOLVED | No permanent `KisProcessingApplicator` vs generator-layer decision has been made |
| Android as first-class target | NOT TESTED | No Android ARM64 build, device test, S Pen test, or thermal/memory evidence exists |
| Architecture changes require approval | PASS | This audit introduces governance documentation only |

## Platform and test status

### Windows

- `FieldGraphTest`: PASS in the existing Windows build tree.
- `kritafieldlab`: PASS when built as the focused target.
- Current batch-evaluation DLL was copied to the dev install and verified
  byte-for-byte at SHA-256
  `574F91A9875972A87133FF7B263C302793BEE8F55D2C380AC5B972C3E3050B80`.
- Built and dev-installed plugin DLLs were verified with matching SHA-256
  hashes at the audited baseline.
- The user demonstrated the auto-updating preview at commit `cb467ff4d2`.
- Fresh runtime smoke: the dev Krita process remained running after startup and
  loaded the exact installed `kritafieldlab.dll`. Preview pixels were not
  independently inspected in this task.

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
- FastNoise2 is not present in the repository or local Field Lab build inputs.
- Any FastNoise2 addition must first record the exact version, license, used
  API/files, Windows viability, Android ARM64 viability, build cost,
  maintenance risk, and rollback path required by `REUSE_LEDGER.md`.

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

Task 1 from the audit is complete. The remaining recommendations have not been
started.

1. Prepare the required FastNoise2 dependency record and a minimal isolated
   Windows/Android build-and-metadata spike; do not add a handwritten production
   node catalog.
2. Add versioned semantic graph persistence with round-trip and malformed-input
   tests, independent of any visual node editor or permanent Krita bake
   lifecycle choice.
3. After the dependency spike passes, adapt FastNoise2 metadata into semantic
   descriptors and connect a minimal FastNoise island to the batch contracts;
   do not hand-author the production catalog.

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
