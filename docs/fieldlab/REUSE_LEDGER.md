# Field Lab Reuse Ledger

## Mandatory search order

Before implementing a substantial primitive, search in this order:

1. Krita
2. FastNoise2
3. G'MIC for generic raster/image-processing operations
4. Mature small C++ libraries
5. GPL-compatible/adaptable algorithms from established graphics projects
6. Original implementation

The purpose is to minimize code volume and maintenance risk, not to maximize the
number of dependencies.

## Current reuse decisions

| Area | Preferred source | Classification | Current decision |
|---|---|---|---|
| Painting/layers/undo/document lifecycle | Krita | DIRECT/ADAPT | Reuse |
| Stylus sensors and curves | Krita sensor/curve stack | DIRECT/ADAPT | Reuse; do not duplicate |
| Smart Fill / gap closing | Krita fill/selection infrastructure | DIRECT/ADAPT | Reuse |
| Intelligent coloring | Krita Colorize/lazybrush | DIRECT/ADAPT | Reuse first |
| Bounded line-art proximity | `KisGapMap` | ADAPT | Prototype where bounded behavior fits |
| General exact distance/SDF | proper EDT backend | VENDOR/ADAPT | Still required |
| Noise/fractals/domain math | FastNoise2 v1.1.1 (`903c1f2d`) | DIRECT/ADAPT | Primary scalar backend; Windows spike passed with one FastSIMD patch; Android not tested; not mandatory yet |
| FastNoise node definitions | FastNoise2 v1.1.1 metadata | DIRECT/ADAPT | Opt-in probe discovered 47 nodes; production adapter not started; generate, do not hand-author |
| Arbitrary user expressions | KSeExpr | ADAPT | Later/optional backend |
| Generic raster operators | G'MIC | RESEARCH/ADAPT | Audit per operator; not a blanket dependency |
| Hatching conventions/math | Krita hatching paintop | ALGORITHM/ADAPT | Reuse applicable primitives/settings only |
| Path booleans/offset cleanup | Clipper2 | VENDOR/ADAPT | Preferred small C++ path backend |
| Arc-heavy offsets | CavalierContours | DEFER/RESEARCH | Only if true arc preservation justifies added complexity |
| Point distribution | small Poisson/blue-noise implementation | VENDOR | Candidate when PointSet is implemented |
| Early streamline reference | small proven implementation | ALGORITHM/VENDOR | Useful for spike; final semantics remain Field Lab-owned |
| Node editor | QtNodes or alternative | UNRESOLVED | Android S Pen/touch spike first |
| Graph-driven parameter UI patterns | Krita AI Diffusion Custom Workflow | PATTERN/ADAPT | Study architecture, not AI features |
| Developer inspection tooling | Krita Python Plugin Developer Tools | DEV TOOL | Useful optional developer aid |

## Dependency rule

Do not add a new mandatory dependency merely because it contains useful
functions.

Each dependency proposal must record:

- exact repository/version
- license
- files/API used
- reason Krita/FastNoise2 cannot already solve it
- Windows viability
- Android ARM64 viability
- build-system cost
- maintenance risk
- estimated engineering time saved
- smallest vendorable subset

The complete current FastNoise2 record is in `FASTNOISE2_DEPENDENCY.md`.
