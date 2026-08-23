# Canonical Field Lab Requirements

## Product identity

Field Lab is part of a Krita-based painting and drawing application. Painting
remains the primary activity. The advanced procedural and mathematical systems
must be optional rather than prerequisites for ordinary drawing.

The desired experience is:

**Simple by default. Arbitrarily complicated when deliberately expanded.**

The application should preserve Krita's mature raster painting capabilities,
remain approachable enough to open and draw immediately, and expose deeper
procedural systems only when the artist chooses them.

The UI goal is Blender-quality organization, discoverability, customization,
and node interaction where appropriate — not a literal Blender imitation.

Accessibility and customizability are explicit requirements.

## First-class platforms

Both are first-class targets:

- Windows desktop
- Android ARM64 tablet

Canonical tablet target:

**Samsung Galaxy Tab S9 FE+**

Do not substitute Tab S9 Ultra performance assumptions.

Platform compatibility is a gate, not a cleanup phase. Major dependencies and
subsystems must either work on both targets or be cleanly isolated as
development-only/desktop-only tooling.

## Workflow priority

Research and implementation should optimize complete artist workflows before
individual feature novelty.

Relevant workflow families include:

- sketch → cleanup → line art → flats → shading → lighting → effects → export
- reference → composition → block-in → value → color → refinement → export
- line art → region detection → flats → underfill/cleanup → shading masks
- artwork → masks/fields → procedural generator → preview → manual adjustment → bake/live
- form/line art → intensity field → direction field → seeds → hatching → manual correction
- animation frames → fills/masks → procedural effects → correction → export

## Protected near-term deliverables

The historical Month-One protection set remains important as the shortest route
to a usable artist-facing fork:

1. Passing-point curve tool
2. Smart Fill UI/presets
3. Color Harmony controls
4. Procedural Lab / Field Lab v0
5. Tablet-oriented workspace

The current coding focus on Field Lab must not cause the other four to disappear
from the roadmap.

## Field Lab capabilities explicitly important to the user

These are current active requirements, even when not implemented yet:

- fractals
- procedural baking
- scalar fields
- vector fields
- distance fields
- distance from line art
- SDF / geometric distance primitives
- domain warping
- contours
- streamlines
- procedural hatching
- field-flow tools
- procedural operators
- intelligent coloring
- stylus/pressure/input modulation
- keyboard/keybind modulation where appropriate
- artist-accessible experimentation with mathematically unusual systems

Image-derived masks are not a required headline feature, but the architecture
should make them easy to add.

## Core interchange types

The architecture should retain generic interchange types so artistic recipes
compose rather than becoming separate engines:

- ScalarField2D
- VectorField2D
- RasterSource
- PointSet
- PathSet

Geometry/path inputs should eventually be able to become field sources,
barriers, attractors, flow guides, masks, and distance sources.

## Procedural/manual relationship

Procedural systems should support an artist workflow rather than replace manual
painting.

Where feasible:

procedural generation → preview/live result → local/manual intervention → bake
or continued live editing.

Manual overrides should not be designed away merely because preserving them is
hard.

## Mathematical representation

The long-term architecture should preserve a semantic representation capable of
supporting, where meaningful:

- node view
- expression view
- formatted mathematical notation
- LaTeX view/export
- code/algorithm representation
- interactive parameter sliders
- visualization overlays

This is **not** a Month-One implementation requirement. It is an architectural
placeholder so the graph does not become backend-specific in a way that makes
future representation impossible.

## Deferred or non-required scope

Do not spend current implementation time on:

- full character-rigging/advanced 3D animation workflow
- IK/anatomy systems as a current requirement
- full Rebelle/ArtRage-style physical media simulation
- advanced erosion simulation
- general GPU graph compiler
- complete LaTeX editor
- full symbolic algebra system
- advanced differential-equation tooling
- advanced cross-frame procedural tracking
- AI object segmentation
- elaborate contour-array local override editing
- large reaction-diffusion/DLA/L-system suites before the core works

Lightweight 3D reference/construction can remain a deferred optional capability;
it must not turn the application into a Blender replacement.

## Scope-preservation rule

A feature may be:

- implemented directly
- implemented through another primitive
- dependent on a shared subsystem
- deferred
- rejected with a stated reason

It may not simply vanish.
