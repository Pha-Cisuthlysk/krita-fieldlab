# Field Lab Architecture Guardrails

## Hard invariants

### 1. Krita remains the host, not something to rewrite casually

Keep Krita upstream-ish. Prefer a contained C++ plugin/module family and
adapters over scattered core modifications.

Core changes require a concrete reason and should be minimized so upstream
merges remain practical.

### 2. The semantic graph is authoritative

`FieldLabGraph` (or its eventual successor) is the source of truth.

A visual node editor is only a view/editor over the semantic model.

Do not allow QtNodes, a custom QGraphicsScene, FastNoise's editor, or any other
UI framework to become the serialized semantic format.

### 3. Backend ownership

Canonical conceptual split:

- FastNoise2: default high-performance scalar/noise/fractal/domain backend
- KSeExpr: optional arbitrary expression/color/formula backend
- Native Field Lab: raster-global, distance, vector, contour, streamline,
  hatching, path, and other algorithms that do not map naturally to the above
- Krita: painting, layers, document lifecycle, undo, sensors, existing fill/
  colorize systems, host-side processing infrastructure

Do not delete KSeExpr from the long-term architecture merely because
FastNoise2 becomes the default scalar backend.

### 4. FastNoise2 metadata, not a handwritten catalog

Do not manually author the production FastNoise node catalog.

Use current FastNoise2 metadata (`Metadata::GetAll`, NodeData,
serialization/deserialization) to create generic `NodeDescriptor`s, then use an
artist-facing allowlist/presentation layer.

### 5. FastNoise islands

When contiguous Field Lab nodes map to FastNoise2, compile/evaluate them as one
FastNoise2 graph/tree rather than materializing a full image after every node.

### 6. Batch evaluation is a performance invariant

Production field evaluation must be batch/tile oriented.

Primary interfaces should resemble:

- evaluateGrid(...)
- evaluatePositions(...)

Single-sample evaluation may exist for convenience, debugging, tests, and tiny
prototype scaffolds, but downstream image algorithms must not be designed
around millions of virtual `sample(x,y)` calls.

Do not loop over FastNoise2 `GenSingle()` to produce images.

### 7. Reuse Krita sensors

Do not create a second tablet-sensor UI, serialization system, curve system, or
multi-sensor combiner.

Adapt existing Krita machinery such as `KisKritaSensorPack`,
`KisCurveOptionDataCommon`, `KisCurveOption`, and the dynamic sensor registry.

### 8. Reuse Krita fill/colorize systems

Smart Fill and intelligent coloring should begin as orchestration, UI, presets,
and adapters around Krita's existing fill, gap handling, selection, Colorize,
and lazy-brush infrastructure.

Do not create a competing region-analysis engine without evidence that Krita
cannot satisfy the requirement.

### 9. Distance from line art is two problems

- Exact/general distance/SDF: retain a proper EDT/SDF implementation.
- Bounded painting-oriented gap/proximity behavior: investigate/use Krita
  `KisGapMap` where appropriate.

Do not mistake `KisGapMap` for a general exact EDT replacement.

### 10. Preview/bake host integration is not fully locked

Historical research surfaced multiple Krita-native host execution candidates,
including:

- `KisProcessingApplicator`
- `KisGenerator` / `KisGeneratorLayer` / `KisGeneratorStrokeStrategy`

These are promising reuse targets, but choosing one as the permanent Field Lab
host lifecycle is an architectural decision.

**PROPOSED CHANGE — REQUIRES USER APPROVAL** before locking one route as the
canonical host lifecycle.

A spike/benchmark comparing them is allowed if it is small and reversible.

### 11. Android is a design constraint now

For every major subsystem record:

- Windows build/test status
- Android ARM64 build/test status
- S Pen/touch implications
- memory/cache implications
- CPU/NEON behavior
- thermal/battery implications where relevant
- suspend/resume or document reopen implications

### 12. UI design

The UI should be seamless across desktop and tablet as far as practical.

Blender-like means modern organization, discoverability, flexible panels,
workspaces, and good node interaction — not copying Blender's appearance.

### 13. Architecture changes require approval

Do not silently change an established architecture or delete a subsystem
because a new library looks attractive.

Write:

**PROPOSED CHANGE — REQUIRES USER APPROVAL**

with:
- reason
- expected labor saved
- migration impact
- Windows impact
- Android impact
- dependency/license impact
- rollback path
