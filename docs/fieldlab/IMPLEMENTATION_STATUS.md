# Current Implementation Audit

Audit date: 2026-08-23

Audited branch: `fieldlab`

Audited baseline commit:
`2ec9495a7fc0811345ab72361ce45053f98ce65c`
(`Separate Field Lab semantic core target`)

Audit scope: documentation and repository inspection only. No implementation
work was started as part of this audit.

Primary requirement IDs reviewed: `FL-PROD`, `FL-PLAT`, `FL-GRAPH`,
`FL-PREVIEW`, `FL-SCALAR`, `FL-OPS`, plus the protected near-term families.

Requirement state: ACTIVE

Overall implementation state: PARTIAL / TESTED WINDOWS / ANDROID NOT TESTED

Audit basis: current `fieldlab` branch as inspected after the source corpus was
received.

## Summary

The repository is still in the semantic-graph skeleton stage. That is
appropriate. The current work has not yet turned Field Lab into a noise-only
system, and separating the semantic core from the docker is directionally
consistent with the architecture.

## Implemented/partial

| Component | Status | Audit note |
|---|---|---|
| Field Lab Krita docker/plugin | IMPLEMENTED / TESTED WINDOWS | Contained `kritafieldlab` module; user demonstrated the preview before the latest core-only refactors |
| `NodeDescriptor` scaffold | PARTIAL | Five manual native prototype nodes only: Constant, Position X/Y, Add, Multiply |
| `FieldGraph` semantic model | PARTIAL | Nodes, connections, parameter mutation, input disconnection, and node removal exist; persistence and undo integration do not |
| Scalar evaluator | PROTOTYPE | Recursive single-sample arithmetic/position evaluator with hard-coded native type dispatch |
| Graph validation | PARTIAL | Checks known types, ports, value types, required inputs, and cycles |
| 2D preview | PARTIAL | Auto-updating normalized 128x128 grayscale prototype exists in the docker |
| Scalar grid sampler | PROTOTYPE / RED FLAG | Functional per-pixel reference path; not a production batch contract |
| Unit tests | PARTIAL / TESTED WINDOWS | One guiless CTest target with 11 focused test methods |
| Semantic-core build target | IMPLEMENTED | `kritafieldlabcore` is a Qt-Core-only static target shared by plugin and tests |

## Evidence inspected

- `plugins/dockers/fieldlab/CMakeLists.txt` separates `kritafieldlabcore` from
  the `kritafieldlab` UI module.
- Core graph, evaluator, sampler, validator, and descriptor sources include
  Qt Core facilities only; QWidget/QDockWidget/QImage use remains in the docker.
- `FieldGraphSampler::sampleScalar()` contains nested width/height loops and
  calls `evaluateScalar()` once for every sample.
- `NodeDescriptor::builtInScalarNodes()` contains exactly five handwritten
  native scaffold descriptors.
- No FastNoise2 source, metadata adapter, `Metadata::GetAll`, FastNoise node
  catalog, or FastNoise build integration exists in Field Lab.
- `FieldGraphTest` covers graph connections, mutation, arithmetic, coordinates,
  evaluator errors, cycles, descriptors, validation, and grid sampling.
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

## Important audit finding: current sampler is temporary only

The current `FieldGraphSampler::sampleScalar()` loops over each preview pixel and
calls `evaluateScalar()` separately.

That is acceptable as a **tiny native prototype scaffold** for the present
128×128 preview.

It is **not** acceptable as the production field-evaluation architecture.

Before FastNoise2 or large procedural graphs are built on top of it, Codex must
preserve the batch-evaluation invariant:

- `evaluateGrid(...)`
- `evaluatePositions(...)`
- single-sample evaluation for convenience/debugging only

The current sampler should be documented or named as a prototype/CPU reference
path, or later replaced/routed through a backend batch interface.

Do not optimize this trivial evaluator prematurely, but do not let its API
silently become the permanent execution contract.

## Architecture guardrail verdict

| Guardrail | Verdict | Evidence |
|---|---|---|
| Painting-first Krita host | PASS | Work is contained in a docker/plugin; no Krita core rewrite was introduced |
| Semantic graph authoritative and UI-independent | PASS | Graph state and services live in `kritafieldlabcore`; the docker consumes them |
| FastNoise2 metadata catalog | NOT STARTED | Only five native prototype descriptors exist; no FastNoise catalog has been hand-authored |
| Batch/tile evaluation primary | NOT YET SATISFIED | Current `sampleScalar()` is explicitly a per-pixel reference path |
| Krita preview/bake lifecycle | UNRESOLVED | No permanent `KisProcessingApplicator` vs generator-layer decision has been made |
| Android as first-class target | NOT TESTED | No Android ARM64 build, device test, S Pen test, or thermal/memory evidence exists |
| Architecture changes require approval | PASS | This audit introduces governance documentation only |

## Platform and test status

### Windows

- `FieldGraphTest`: PASS in the existing Windows build tree.
- `kritafieldlab`: PASS when built as the focused target.
- Built and dev-installed plugin DLLs were verified with matching SHA-256
  hashes at the audited baseline.
- The user demonstrated the auto-updating preview at commit `cb467ff4d2`.
- A fresh GUI smoke test has not been recorded after the later validator,
  sampler, mutation, and shared-core refactors.

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
- Do not generalize the per-pixel prototype sampler.
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

These are recommendations only. They were not started during this audit.

1. Define backend-neutral batch contracts for `evaluateGrid(...)` and
   `evaluatePositions(...)`, retain the current scalar sampler as an explicitly
   named reference/debug adapter, and add contract tests.
2. Prepare the required FastNoise2 dependency record and a minimal isolated
   Windows/Android build-and-metadata spike; do not add a handwritten production
   node catalog.
3. Add versioned semantic graph persistence with round-trip and malformed-input
   tests, independent of any visual node editor or permanent Krita bake
   lifecycle choice.

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
