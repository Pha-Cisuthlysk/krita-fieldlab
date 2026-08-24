# Field Lab UI Asset Brief

## Goal

Field Lab should read as a native Krita workspace with a distinct procedural
vocabulary. Reuse Krita icons for generic actions. Create custom icons only for
concepts that Krita does not already express.

## Delivery format

- SVG with a `0 0 22 22` view box
- transparent background
- separate light-background and dark-background variants
- strong silhouette at 16 px and comfortable reading at 22 px
- one-color first; do not depend on hue to communicate meaning
- no embedded raster images, fonts, text labels, gradients, or filters
- keep fine strokes at least 1.5 px at the 22 px design size
- include an SPDX license declaration; `CC0-1.0` is preferred for UI icons

Proposed filenames use `light_` and `dark_` prefixes and will eventually live
in a plugin-local Field Lab icon resource. Do not add files to Krita's global
icon collection until the set is stable.

## Tier 1 Icons

These establish the first useful visual language. Draw these first.

| Filename stem | Concept | Suggested motif |
|---|---|---|
| `fieldlab` | Field Lab docker/workspace | A small coordinate grid crossed by one flowing curve |
| `fieldlab-scalar` | Scalar field | Three nested value bands or isolines |
| `fieldlab-vector` | Vector field | A compact 2x2 flow-arrow lattice |
| `fieldlab-distance` | Distance field / SDF | A shape with two evenly spaced offset contours |
| `fieldlab-fractal` | Fractal/noise family | A branching self-similar mark, not a cloud icon |
| `fieldlab-warp` | Domain warp | A square grid bending through a wave |
| `fieldlab-contour` | Contours | Clean stacked isolines with one emphasized level |
| `fieldlab-streamline` | Streamlines / field flow | Three curved parallel paths with one arrowhead |
| `fieldlab-hatching` | Procedural hatching | Directional hatch strokes wrapping a simple form |
| `fieldlab-raster-source` | RasterSource | A picture frame feeding into a field grid |
| `fieldlab-point-set` | PointSet / scatter | Uneven dots with one origin marker |
| `fieldlab-path-set` | PathSet | Two connected Bezier segments with control points |
| `fieldlab-modulation` | Stylus/key modulation | A pen nib crossing a parameter curve |
| `fieldlab-bake` | Bake to Krita | A field grid resolving into a paint-layer sheet |

Each stem needs `light_<stem>.svg` and `dark_<stem>.svg`.

## Tier 2 Icons

These cover the protected artist workflows after the core Field Lab set is
visually coherent.

| Filename stem | Concept | Suggested motif |
|---|---|---|
| `fieldlab-passing-curve` | Passing-point curves | A curve constrained through three distinct points |
| `fieldlab-smart-fill` | Smart Fill | A fill drop entering a bounded region with a small gap bridge |
| `fieldlab-color-harmony` | Color Harmony | Three linked swatches on a partial color-wheel arc |
| `fieldlab-tablet-workspace` | Tablet workspace | A landscape tablet with pen and compact side rail |
| `fieldlab-line-distance` | Distance from line art | A drawn line with a measured offset band |
| `fieldlab-intelligent-color` | Intelligent coloring | Two bounded regions with coordinated fill marks |

## Reuse Existing Krita Icons

Do not redraw generic search, clear, expand/collapse, eye/visibility, settings,
add/remove, warning, or document/layer symbols. Field Lab should use Krita's
theme-aware icon lookup for those actions.

## Texture Guidance

No raster UI texture is required for the current scaffold.

- Keep docker panels, tabs, fields, and lists native to the active Krita theme.
- Reuse Krita's transparency checker where transparency must be shown.
- Generate a future node-canvas grid in code so it scales cleanly and adapts to
  theme, zoom, DPI, and tablet display density.
- Generate procedural preview thumbnails from the graph; do not ship static
  noise or field textures as substitutes.

An optional empty-state illustration may be useful later, but it should be a
theme-aware vector illustration rather than a tiled texture. Do not create it
until the visual node workflow and empty-state copy are settled.

## Review Checklist

- recognizable at 16 px without a label
- distinguishable in grayscale
- readable on both Krita light and dark themes
- no collision with an existing Krita action meaning
- comfortable at 100%, 150%, and 200% display scaling
- large touch target supplied by the UI; artwork itself remains 22 px
