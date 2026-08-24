# Field Lab Feature-Family Ledger

This compact ledger is an index. The exhaustive preserved inventory is in
`CANONICAL_FEATURE_INVENTORY_SOURCE.md`.

Every row below is also represented in the UI-independent
`FieldCapabilityCatalog`. Catalog presence means the scope is retained and has
a stable semantic identifier; it does not mean the feature is implemented.

| ID | Requirement family | Requirement state | Current coverage |
|---|---|---|---|
| FL-PROD | Painting-first Krita application; simple by default | ACTIVE | Krita baseline / guardrail |
| FL-PLAT | Windows + Android ARM64 first-class | ACTIVE | Windows plugin and FastNoise dependency spikes tested; Android not tested |
| FL-UI | Accessible/customizable desktop+tablet UI | ACTIVE | NOT STARTED |
| FL-CURVE | Passing-point curve system | ACTIVE / protected near-term | NOT STARTED |
| FL-SMARTFILL | Smart Fill UI/presets over Krita fill machinery | ACTIVE / protected near-term | REUSE IDENTIFIED |
| FL-COLOR | Color Harmony controls | ACTIVE / protected near-term | REUSE IDENTIFIED |
| FL-TABLET | Tablet-oriented workspace | ACTIVE / protected near-term | NOT STARTED |
| FL-GRAPH | Authoritative typed semantic graph | ACTIVE | PARTIAL |
| FL-PREVIEW | Live/reduced-resolution procedural preview | ACTIVE | PARTIAL |
| FL-BAKE | Procedural bake to Krita layer/data | ACTIVE | NOT STARTED |
| FL-SCALAR | Scalar fields | ACTIVE / very important | PARTIAL evaluator and interchange type; FastNoise2 Windows spike passed |
| FL-VECTOR | Vector fields | ACTIVE / very important | INTERCHANGE TYPE SCAFFOLDED; evaluation not started |
| FL-DIST | Distance fields | ACTIVE / important | RESEARCHED |
| FL-LINE-DIST | Distance from line art | ACTIVE / very important | REUSE IDENTIFIED |
| FL-SDF | SDF/geometric distance primitives | ACTIVE / important | RESEARCHED |
| FL-FRACTAL | Fractals | ACTIVE / very important | FastNoise2 reuse validated on Windows; not integrated |
| FL-WARP | Domain warping | ACTIVE / important | FastNoise2 reuse validated on Windows; not integrated |
| FL-CONTOUR | Contours | ACTIVE / important | RESEARCHED |
| FL-STREAM | Streamlines | ACTIVE / important | RESEARCHED |
| FL-HATCH | Procedural hatching | ACTIVE / important | RESEARCHED |
| FL-FLOW | Field-flow artistic tools | ACTIVE / important | DEPENDENT on vector/path |
| FL-OPS | Procedural operators | ACTIVE / important | PARTIAL architecture |
| FL-ICOLOR | Intelligent coloring | ACTIVE / important | REUSE IDENTIFIED |
| FL-PARAM | Pressure/stylus/key parameter modulation | ACTIVE | REUSE IDENTIFIED |
| FL-RASTER | RasterSource / image-driven field inputs | ACTIVE foundation | SEMANTIC REFERENCE SCAFFOLDED; Krita adapter not started |
| FL-POINT | PointSet/scatter interchange | ACTIVE foundation | INTERCHANGE TYPE SCAFFOLDED; processing not started |
| FL-PATH | PathSet procedural geometry | ACTIVE foundation | INTERCHANGE TYPE SCAFFOLDED; processing not started |
| FL-MASK | Image-derived/live masks | DEPENDENT / not headline-required | REUSE IDENTIFIED |
| FL-MATH-IR | Future math/expression semantic representation | DEFERRED but architectural placeholder | PARTIAL |
| FL-MATH-VIZ | Field/math visualization overlays | DEFERRED but tracked | NOT STARTED |
| FL-EXPR | KSeExpr expression backend | DEFERRED / retained | RESEARCHED |
| FL-GMIC | G'MIC raster backend prototype | DEFERRED/RESEARCH | RESEARCHED |
| FL-3DREF | Lightweight 3D reference/construction | DEFERRED OPTIONAL | RESEARCHED |
| FL-3DRIG | Character rigging/IK advanced animation workflow | REJECTED AS CURRENT REQUIREMENT | No work |
| FL-EROSION | Advanced erosion simulation | REJECTED AS CURRENT REQUIREMENT | No work |
| FL-WET | Full physical wet-media simulation | DEFERRED / not required | No work |
| FL-ANIM | Advanced procedural animation automation/tracking | DEFERRED | No work |
| FL-GPU | General GPU graph compiler | DEFERRED pending profiling | No work |

## Artistic-recipe rule

Clouds, bark, veins, frost, fur, feathers, stars, woodgrain, mountains,
crystallization, cracks, water, and similar named outcomes are artistic recipes.

They should map onto reusable primitives (fields, paths, scatter, transforms,
distance, raster operators) unless evidence shows a genuinely new subsystem is
required.
