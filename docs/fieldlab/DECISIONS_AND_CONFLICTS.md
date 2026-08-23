# Decisions and Historical Conflicts

## 1. Tablet model

Older discussion occasionally used Tab S9 Ultra performance assumptions.

**Canonical:** Samsung Galaxy Tab S9 FE+.

This was an explicit user correction. Performance, RAM, thermal, GPU, and UI
assumptions must target the FE+ class.

## 2. KSeExpr vs FastNoise2

Historical stage A:
Field Lab graph → KSeExpr → Krita Fill Layer.

Later research found FastNoise2 1.x has rich metadata, graph serialization,
custom nodes, Android/NEON support, and SIMD-oriented execution.

**Canonical reconciliation:**

- FieldLabGraph stays authoritative.
- FastNoise2 becomes the preferred scalar/noise/fractal/domain backend.
- KSeExpr remains an optional expression/color/formula backend.
- Native Field Lab handles global/vector/path algorithms.

Do not delete KSeExpr merely because it is no longer the center.

## 3. Scalar sampling API

Older sketches used `sample(x,y)` as the obvious field abstraction.

Later performance research made batch generation a hard requirement.

**Canonical:** batch/tile evaluation is primary; single-sample is convenience
only.

## 4. Preview/bake lifecycle

Historical plans included custom scratch-device/cache scheduling.
Later research identified Krita-native options including
`KisProcessingApplicator` and `KisGeneratorLayer`/generator stroke machinery.

**Current status:** unresolved architectural choice.

Both are approved for small research spikes. Neither should become the
permanent architecture without an explicit user-approved decision.

## 5. Universal node system

The long-term vision allows many systems to expose optional graphs.

This does **not** mean Month One should implement one universal node engine for
brushes, compositing, animation, 3D, masks, fields, and everything else.

**Canonical:** keep the semantic architecture extensible, but implement Field
Lab's required domains first and use adapters for other Krita subsystems.

## 6. 3D and animation scope

Early feature compilations explored extensive 3D references, mannequins, IK,
rigging, and advanced animation.

Later user clarification explicitly said 3D workflow character rigging for
advanced animation is not needed.

**Canonical:**
- lightweight 3D reference/construction may remain deferred optional
- character rigging/IK/advanced 3D animation is not a current requirement
- do not spend current development time on it

## 7. Erosion

Early lists used erosion as an example of procedural possibilities.

Later user clarification explicitly said erosion simulation is not needed.

**Canonical:** not a current requirement. Do not implement merely to satisfy an
old brainstorm entry.

## 8. Natural media

The vision appreciates useful natural-media behavior, but does not require a
Rebelle/ArtRage replacement or full physical fluid simulation.

**Canonical:** defer serious simulation; reuse existing Krita/MyPaint/Color
Smudge capabilities first.

## 9. Blender-like UI

**Canonical meaning:** modern, discoverable, customizable workspaces/panels and
comfortable advanced node interaction.

It does not mean copy Blender visually or turn Krita into Blender.

## 10. Architecture governance

The user explicitly requested that architecture not be changed without asking.

Therefore an assistant/coding-agent proposal remains a proposal even if it is
technically compelling.

Use the label:

**PROPOSED CHANGE — REQUIRES USER APPROVAL**
