# Field Lab Canonical Feature Inventory — Preserved Source

This file is a preserved extract from the user-supplied master audit corpus.
It is intentionally not simplified. It exists so that a later implementation
sprint cannot silently lose a feature simply because the working roadmap is
shorter.

Source range in `Text audit.txt`: lines 5897–8469.

# Research Framework Feature Coverage Audit
 
## Purpose
 
Audit the entire research framework for the proposed Krita-based painting application.
 
The goal is **not** to decide whether every feature should be implemented now.
 
The goal is to verify that **every feature, capability, architectural requirement, performance concern, and research direction discussed so far is at least acknowledged somewhere in the research framework**.
 
Search all existing:
 
 
- research prompts
 
- research notes
 
- repository investigations
 
- feature lists
 
- architectural plans
 
- implementation queues
 
- feasibility assessments
 
- licensing notes
 
- source-code investigations
 
- Android-performance notes
 
- AI-assisted development plans
 

 
For every item below, mark:
 
 
- **ACKNOWLEDGED** — clearly represented in the research framework.
 
- **PARTIAL** — related concept exists, but an important part is missing.
 
- **MISSING** — not currently represented.
 
- **DUPLICATE / MERGED** — represented under another feature or broader architecture.
 
- **DEFERRED BUT TRACKED** — deliberately postponed but explicitly retained for later research.
 

 
For every PARTIAL or MISSING item, state exactly what should be added to the research framework.
 
Do not remove an item simply because another system could theoretically implement it.
 
The framework should explicitly acknowledge the artistic use case.
  
# A. Core Product Identity
 
Verify acknowledgement of:
 
 
1. Painting and drawing remain the application's primary purpose.
 
2. The application is not intended to become a general-purpose Blender replacement.
 
3. Advanced mathematical/procedural functionality is optional.
 
4. Simple default interface.
 
5. Advanced controls exposed only when requested.
 
6. ibisPaint-like immediacy and accessibility.
 
7. Krita-level extensibility underneath the simplified interface.
 
8. Desktop support.
 
9. Android tablet support.
 
10. Drawing-tablet support.
 
11. Samsung Galaxy Tab S9 Ultra as an important performance target.
 
12. Touch-first controls.
 
13. S Pen/stylus-friendly interaction.
 
14. Large touch targets.
 
15. Simple and Advanced workspace modes.
 
16. Tablet-specific workspace.
 
17. Desktop-specific workspace.
 
18. Ability to paint normally without ever opening procedural systems.
 

  
# B. Core Raster Painting
 
Verify:
 
 
1. Raster painting canvas.
 
2. Normal brush painting.
 
3. Eraser.
 
4. Fill tools.
 
5. Transform tools.
 
6. Selection tools.
 
7. Undo/redo.
 
8. Large-canvas support.
 
9. Layered document support.
 
10. Color management.
 
11. Existing Krita brush compatibility.
 
12. Existing Krita document/file infrastructure.
 
13. Existing Krita compositing infrastructure.
 
14. Reference images.
 
15. Fast pan.
 
16. Fast zoom.
 
17. Canvas rotation.
 
18. Canvas mirroring.
 
19. Touch gestures.
 

  
# C. Layer System
 
Verify:
 
 
1. Simple ibisPaint-like layer management.
 
2. Layer groups.
 
3. Layer roles.
 
4. Semantic layer roles such as:
 

 
 
- Sketch
 
- Line art
 
- Reference
 
- Flats
 
- Shading
 
- Lighting
 
- Normal
 

 
 
1. Layer tags independent of folder hierarchy.
 
2. Multiple tags per layer.
 
3. Procedural queries based on layer tags.
 
4. Reference-layer groups.
 
5. Current-layer sampling.
 
6. Selected-layer sampling.
 
7. All-visible-layer sampling.
 
8. Tagged-layer sampling.
 
9. Ability for masks/fills/brushes to ignore sketch layers.
 
10. Non-destructive procedural layers where practical.
 

  
# D. Stylus and Pressure System
 
Verify:
 
 
1. Pressure input.
 
2. Tilt input.
 
3. Pen/barrel rotation.
 
4. Stroke direction.
 
5. Stroke velocity.
 
6. Stroke acceleration.
 
7. Stroke distance.
 
8. Stroke duration/time.
 
9. Canvas position as an input.
 
10. Perspective depth as a possible input.
 
11. Randomness as an input.
 

 
Pressure and other sensors should be capable of controlling:
 
 
1. Brush diameter.
 
2. Opacity.
 
3. Flow.
 
4. Hardness.
 
5. Brush rotation.
 
6. Pigment quantity.
 
7. Wetness.
 
8. Smudging.
 
9. Bristle spread.
 
10. Texture penetration.
 
11. Color variation.
 
12. Procedural parameters.
 

 
Verify that multiple outputs may respond to one pressure input simultaneously.
  
# E. Brush System
 
Verify:
 
 
1. Procedural brush behavior.
 
2. Node-controlled brush behavior.
 
3. Pressure curves.
 
4. Custom mathematical pressure mappings.
 
5. Texture-controlled brushes.
 
6. Field-controlled brushes.
 
7. Image-controlled brushes.
 
8. Random/noise-controlled brushes.
 
9. Brush orientation following vector fields.
 
10. Brush behavior based on distance from line art.
 
11. Brush behavior based on masks.
 
12. Brush behavior based on color.
 
13. Brush behavior based on gradients.
 
14. Brush behavior based on underlying texture.
 
15. Exposed simplified parameters over complex internal graphs.
 
16. Ability to open a preset's internal graph.
 
17. Ability to save/share procedural brush presets.
 

  
# F. Natural Media
 
Verify:
 
 
1. Watercolor-style painting.
 
2. Wet paint.
 
3. Smudging.
 
4. Paint dragging.
 
5. Color pickup.
 
6. Pigment loading.
 
7. Pigment mixing.
 
8. Brush bristle behavior.
 
9. Granulation.
 
10. Canvas/paper texture.
 
11. Local wetness field.
 
12. Limited pigment diffusion.
 
13. Drying.
 
14. Rewetting.
 
15. Edge accumulation.
 
16. Lightweight pigment advection.
 
17. Realistic-enough behavior without requiring full Rebelle-level fluid simulation.
 
18. Performance-conscious approximation rather than unnecessary full physical simulation.
 

  
# G. Passing-Point Curve System
 
Verify:
 
 
1. ibisPaint-inspired passing-point curve creation.
 
2. Curves pass through artist-placed points.
 
3. Automatic smooth interpolation.
 
4. Editable points.
 
5. Pressure-sensitive rendering along curves.
 
6. Applying normal brushes to generated curves.
 
7. Individual segment behavior.
 
8. Straight/rigid segments.
 
9. Automatic spline segments.
 
10. Traditional Bézier segments.
 
11. Circular/arc segments.
 
12. Different interpolation types within one path.
 
13. Sharp/corner nodes.
 
14. Smooth nodes.
 
15. Symmetric nodes.
 
16. Tangent locking.
 
17. G0-like sharp continuity.
 
18. G1-like smooth continuity.
 
19. G2-like very-smooth continuity.
 
20. Generated curves remain editable.
 
21. Procedurally generated curves may later be manually overridden.
 

  
# H. Universal Procedural Node System
 
Verify:
 
 
1. Blender-like comfortable visual node UI.
 
2. Nodes remain optional.
 
3. Common procedural graph used by multiple systems.
 
4. Brush nodes.
 
5. Mask nodes.
 
6. Fill nodes.
 
7. Shading nodes.
 
8. Texture nodes.
 
9. Compositing nodes.
 
10. Field nodes.
 
11. Fractal nodes.
 
12. Animation nodes.
 
13. Geometry/stroke nodes.
 

 
Basic node categories should include:
 
 
1. Inputs.
 
2. Outputs.
 
3. Math.
 
4. Logic.
 
5. Image processing.
 
6. Color.
 
7. Fields.
 
8. Noise.
 
9. Geometry.
 
10. Curve processing.
 
11. Animation/time.
 
12. Sampling.
 
13. Compositing.
 

  
# I. Node Representation Modes
 
Verify that compatible procedural systems can be represented as:
 
 
1. Visual nodes.
 
2. Plain mathematical expressions.
 
3. Rendered mathematical notation.
 
4. LaTeX.
 
5. Source/code representation.
 
6. Interactive mathematical visualization.
 

 
Verify:
 
 
1. Common AST/intermediate representation.
 
2. Nodes are not necessarily the sole source of truth.
 
3. Equation and node representations should remain synchronized where possible.
 
4. Editing variables in math view can update the graph.
 
5. Editing node parameters updates mathematical representation.
 
6. Parameters may automatically become sliders.
 
7. Parameters may have artist-friendly renamed labels.
 
8. Symbolic operations may display proper equations.
 
9. Algorithmic operations may display functional/pseudocode notation instead.
 
10. System should not fabricate meaningless equations for non-symbolic algorithms.
 

  
# J. Interactive Mathematical Visualization
 
Verify:
 
 
1. Vector-arrow overlay.
 
2. Streamline overlay.
 
3. Scalar heatmap.
 
4. Contour visualization.
 
5. Magnitude visualization.
 
6. Gradient visualization.
 
7. Optional critical-point visualization.
 
8. Optional direction-field visualization.
 
9. Optional 3D height-field visualization for z=f(x,y).
 
10. Interactive sliders for equation parameters.
 
11. Immediate canvas preview when mathematical variables change.
 
12. Visualization is an assistant overlay and not automatically rendered into final artwork.
 

  
# K. Scalar Fields
 
Verify:
 
 
1. Generic scalar-field abstraction.
 
2. f(x,y) fields.
 
3. Optional f(x,y,t) fields.
 

 
Scalar fields should be usable for:
 
 
1. Opacity.
 
2. Masks.
 
3. Density.
 
4. Brush influence.
 
5. Shading intensity.
 
6. Wetness.
 
7. Height.
 
8. Scatter probability.
 
9. Texture strength.
 
10. Fractal output.
 
11. Procedural fill.
 

  
# L. Vector Fields
 
Verify:
 
 
1. Generic 2D vector-field node.
 
2. User-entered vector equations.
 
3. Visually created vector fields.
 
4. Field combinations.
 
5. Weighted field blending.
 

 
Uses:
 
 
1. Brush orientation.
 
2. Hatching direction.
 
3. Fur direction.
 
4. Hair flow.
 
5. Smudge direction.
 
6. Pigment movement.
 
7. Water currents.
 
8. Smoke.
 
9. Particle movement.
 
10. Distortion.
 
11. Texture deformation.
 

 
Field primitives:
 
 
1. Uniform flow.
 
2. Source.
 
3. Sink.
 
4. Attractor.
 
5. Repulsor.
 
6. Vortex.
 
7. Custom equation.
 

  
# M. Calculus / Differential-Equation Operations
 
Verify:
 
 
1. Gradient.
 
2. Divergence.
 
3. Curl.
 
4. Laplacian.
 
5. Partial derivatives where useful.
 
6. Vector normalization.
 
7. Vector rotation.
 
8. Field mixing.
 
9. Streamline integration.
 
10. Differential-equation-derived direction fields.
 
11. Integral curves converted into editable drawing curves.
 
12. Mathematical experimentation retained as an optional/fun capability.
 

  
# N. Artwork as Mathematical Input
 
Verify that existing art can become procedural data.
 
Sources:
 
 
1. Points.
 
2. Lines.
 
3. Polylines.
 
4. Splines.
 
5. Curves.
 
6. Shapes.
 
7. Circles.
 
8. Polygons.
 
9. Selections.
 
10. Masks.
 
11. Raster layers.
 
12. Images.
 
13. Opacity maps.
 
14. Brightness maps.
 
15. Hue maps.
 
16. Saturation maps.
 
17. Color channels.
 
18. Edge maps.
 
19. Distance maps.
 

 
These sources can function as:
 
 
1. Attractors.
 
2. Repulsors.
 
3. Flow guides.
 
4. Warp guides.
 
5. Barriers.
 
6. Singularities.
 
7. Density sources.
 
8. Direction sources.
 
9. Placement-probability fields.
 

  
# O. Distance Fields and SDFs
 
Verify:
 
 
1. Distance from line art.
 
2. Distance from selected shape.
 
3. Distance transform.
 
4. Signed-distance fields.
 
5. SDF geometric primitives.
 
6. SDF circles.
 
7. SDF boxes.
 
8. SDF lines.
 
9. SDF combinations.
 
10. Distance-controlled shading.
 
11. Distance-controlled hatching.
 
12. Distance-controlled masks.
 
13. Distance-controlled procedural placement.
 

  
# P. Intelligent Masks
 
Verify:
 
 
1. Live procedural masks.
 
2. Masks defined by rules rather than permanently selected pixels.
 
3. Masks update if their reference artwork changes.
 
4. Current-layer source.
 
5. Visible-layer source.
 
6. Tagged-layer source.
 
7. Specific-reference-layer source.
 
8. Image-derived masks.
 
9. Color-derived masks.
 
10. Alpha-derived masks.
 
11. Mathematical masks.
 
12. Boolean mask combinations.
 
13. AND.
 
14. OR.
 
15. NOT.
 
16. XOR.
 

  
# Q. Intelligent Fill
 
Verify:
 
 
1. Smart fill.
 
2. Enclosed-region detection.
 
3. Gap closing.
 
4. Adjustable gap tolerance.
 
5. Grow/expand fill.
 
6. Deliberate underfill beneath line art.
 
7. Reference line art on another layer.
 
8. All-visible-layer reference.
 
9. Tagged-reference-layer support.
 
10. Similar-color regions.
 
11. Boundary-color filling.
 
12. Adaptive stopping at dark/opaque linework.
 
13. Ability to ignore sketch layers.
 
14. Non-destructive/live fill possibility.
 
15. Animation-frame-range fill later.
 

  
# R. Feature-Based / Calculus-Based Selection
 
Verify ability to select based on:
 
 
1. Exact/approximate color.
 
2. Color-distance threshold.
 
3. Hue.
 
4. Saturation.
 
5. Value.
 
6. Alpha.
 
7. Local contrast.
 
8. Gradient magnitude.
 
9. Gradient direction.
 
10. Rate of color change.
 
11. Regions with similar variation.
 
12. Regions of high change.
 
13. Regions of low change.
 
14. Edge proximity.
 
15. Ridge-like structures.
 
16. Valley-like structures.
 
17. Curvature-like image structures.
 
18. Mathematical inequalities.
 
19. Combined logical conditions.
 

 
Examples should include ideas equivalent to:
 
 
- select colors within a tolerance,
 
- select only smooth portions of those colors,
 
- select transition zones,
 
- select particular edge strengths,
 
- select only regions within a particular distance of line art.
 

  
# S. Procedural Shading / Intelligent Shader
 
Verify:
 
 
1. Selected region used as a shading domain.
 
2. Forced/custom gradient inside the selected domain.
 
3. Linear gradient.
 
4. Radial gradient.
 
5. Spherical/form gradient.
 
6. Noise-controlled gradient.
 
7. Image-controlled gradient.
 
8. Mathematical gradient.
 
9. Basic approximate form shading.
 
10. Sphere-like shading.
 
11. Cylinder-like shading.
 
12. Box/plane-like shading.
 
13. Custom-contour approximation.
 
14. Adjustable light direction.
 
15. General shading assistant rather than authoritative physical simulation.
 
16. Basic contour indication showing where a form would plausibly be shaded.
 

 
Outputs may include:
 
 
1. Soft raster shading.
 
2. Cel shading.
 
3. Hatching.
 
4. Cross-hatching.
 
5. Stippling.
 
6. Contour strokes.
 
7. Natural-media marks.
 

  
# T. Procedural Hatching and Contour Fields
 
Verify:
 
 
1. Intensity field controls shade density.
 
2. Direction field controls stroke direction.
 
3. Follow shape boundary.
 
4. Cross contour.
 
5. Follow manually drawn guide.
 
6. Follow vector field.
 
7. Follow perspective plane.
 
8. Eventually follow 3D/form information.
 
9. Multiple hatching families.
 
10. Cross-hatching triggered by shading intensity.
 
11. Stippling.
 
12. Engraving-like rendering.
 
13. Textile/weave patterns.
 
14. Woodgrain.
 
15. Scale-like patterns.
 

  
# U. Contour Array
 
Verify:
 
 
1. One master stroke.
 
2. Repeated stroke array.
 
3. Repeated lines follow a contour/field.
 
4. Adjustable count.
 
5. Adjustable spacing.
 
6. Density controlled by gradient.
 
7. Width interpolation.
 
8. Opacity interpolation.
 
9. Color interpolation.
 
10. Brush-property interpolation.
 
11. Wetness interpolation.
 
12. Curvature interpolation.
 
13. Random variation.
 
14. Local noise.
 
15. Individual generated lines remain editable.
 
16. Individual generated lines may be overridden.
 
17. Unedited lines remain procedural.
 
18. Procedural changes preserve local overrides where possible.
 

  
# V. Procedural Generators vs Modifiers
 
Verify distinction between:
 
### Generators
 
 
1. Create new procedural content.
 

 
Examples: 382. Trees. 383. Mountains. 384. Contours. 385. Fur. 386. Lightning. 387. Particle fields.
 
### Modifiers
 
 
1. Transform existing artwork.
 

 
Examples: 389. Warp. 390. Attract. 391. Repel. 392. Smooth. 393. Distort. 394. Taper. 395. Scatter. 396. Rotate according to field. 397. Noise warp.
  
# W. Color Theory
 
Verify:
 
 
1. Toggleable color-theory assistance.
 
2. Normal wheel with assistance off.
 
3. Complementary.
 
4. Split complementary.
 
5. Analogous.
 
6. Triadic.
 
7. Tetradic.
 
8. Monochromatic.
 
9. Custom gamut.
 
10. Harmony handles displayed on wheel.
 
11. Harmony handles rotate together.
 
12. Suggestion-only mode.
 
13. Soft snapping.
 
14. Strict gamut constraint.
 
15. Harmony-strength control.
 

  
# X. Light vs Pigment Color
 
Verify acknowledgement of distinct modes for:
 
 
1. RGB/additive light.
 
2. Pigment/subtractive mixing.
 
3. Traditional artist color-wheel terminology.
 
4. Custom gamut.
 
5. Possible later integration between pigment model and natural-media engine.
 

  
# Y. Color Analysis
 
Verify:
 
 
1. Gamut visualization.
 
2. Value analysis.
 
3. Warm/cool balance.
 
4. Saturation analysis.
 
5. Palette analysis.
 
6. Color relationships.
 
7. Lighting-color suggestions.
 
8. Local-color to light/shadow relationships.
 

  
# Z. Advanced Perspective
 
Verify:
 
 
1. One-point perspective.
 
2. Two-point perspective.
 
3. Three-point perspective.
 
4. Curvilinear perspective.
 
5. Fisheye.
 
6. Four-/five-point perspective where practical.
 
7. Axonometric/orthographic construction.
 
8. Perspective planes.
 
9. Automatic vanishing-point generation.
 
10. Perspective-aware procedural/hatching tools.
 

  
# AA. Lightweight 3D Reference System
 
Verify:
 
 
1. 3D is for painting/reference, not a full Blender replacement.
 
2. Import GLB/glTF.
 
3. Import OBJ.
 
4. Optional additional formats later.
 
5. Simple mesh viewport.
 
6. Wireframe.
 
7. Silhouette.
 
8. Flat shading.
 
9. Lit mode.
 
10. X-ray/reference mode.
 
11. Contour mode.
 
12. 3D reference layer.
 
13. Project 3D camera perspective into drawing guides.
 
14. Automatically derive horizon.
 
15. Automatically derive vanishing points.
 
16. Ability to hide/remove 3D reference after guides are generated.
 

  
# AB. Simple 3D Construction
 
Verify:
 
 
1. Cube.
 
2. Sphere.
 
3. Cylinder.
 
4. Cone.
 
5. Plane.
 
6. Stairs.
 
7. Arch.
 
8. Room.
 
9. Simple extrusion.
 
10. Artist-friendly controls instead of Blender-like transform complexity.
 

  
# AC. 3D Drawing/Projection Ideas
 
Verify acknowledgement of:
 
 
1. Drawing/projecting art onto simple 3D surfaces.
 
2. Perspective-correct projected signage.
 
3. Graffiti.
 
4. Windows.
 
5. Floor tiles.
 
6. Repeating patterns.
 
7. Tattoos/clothing references where useful.
 

 
These may be deferred but should remain tracked.
  
# AD. Anatomy Mannequins
 
Verify:
 
 
1. Toggleable anatomy dummies.
 
2. Poseable figures.
 
3. Custom height.
 
4. Head size.
 
5. Shoulder width.
 
6. Torso length.
 
7. Hip width.
 
8. Arm length.
 
9. Leg length.
 
10. Hand size.
 
11. Foot size.
 
12. Muscularity.
 
13. Body mass.
 
14. Realistic preset.
 
15. Heroic preset.
 
16. Manga preset.
 
17. Chibi preset.
 
18. Fully custom proportions.
 

  
# AE. IK and Posing
 
Verify:
 
 
1. Touch-friendly posing.
 
2. Drag hand to position.
 
3. Arm solves itself with inverse kinematics.
 
4. Natural joint limits.
 
5. Keep feet on floor.
 
6. Mirror pose.
 
7. Preserve hand direction.
 
8. Attach hands to objects.
 
9. Multiple-character interaction.
 
10. Prop constraints.
 
11. Hand-on-character constraints.
 

  
# AF. Hands and Faces
 
Verify:
 
 
1. Hand presets.
 
2. Open hand.
 
3. Fist.
 
4. Grip.
 
5. Point.
 
6. Relaxed hand.
 
7. Individual finger adjustment.
 
8. Face posing.
 
9. Jaw.
 
10. Brows.
 
11. Eyelids.
 
12. Eye direction.
 
13. Lips/mouth.
 
14. Facial-expression reference.
 

  
# AG. 3D Lighting Reference
 
Verify:
 
 
1. Directional lights.
 
2. Point lights.
 
3. Area lights.
 
4. Lighting reference for anatomy/models.
 
5. Potential connection to procedural shading.
 
6. Potential connection to color-theory assistance.
 

  
# AH. Asset Libraries
 
Verify:
 
 
1. Local asset library.
 
2. User-created/custom meshes.
 
3. Optional online asset database.
 
4. Poly Haven investigation.
 
5. Sketchfab investigation.
 
6. Licensing/attribution metadata preserved.
 
7. Searchable props.
 
8. Furniture.
 
9. Architecture.
 
10. Nature.
 
11. Vehicles.
 
12. Character/anatomy references.
 

  
# AI. Reference Board
 
Verify:
 
 
1. Pinned reference images.
 
2. References independent of canvas zoom/rotation.
 
3. Touch-friendly positioning.
 
4. Multiple references.
 
5. Color palettes.
 
6. Notes.
 
7. Video frames.
 
8. 3D references where practical.
 

  
# AJ. Fractal Engine
 
Verify:
 
 
1. Fractal engine is an optional artistic generator.
 
2. Fractals may output images.
 
3. Fractals may output masks.
 
4. Fractals may output scalar fields.
 
5. Fractals may output vector fields.
 
6. Fractals may output curves.
 
7. Fractals may output point distributions.
 
8. Fractals may output height fields.
 

  
# AK. Noise / Procedural Texture Family
 
Verify:
 
 
1. Perlin noise.
 
2. Simplex noise.
 
3. FBM/fractal Brownian motion.
 
4. Ridge noise.
 
5. Turbulence.
 
6. Periodic/seamless noise.
 
7. Vector noise.
 
8. Voronoi/Worley noise.
 
9. Cellular patterns.
 
10. Domain warping.
 
11. Noise combinations.
 

  
# AL. Recursive and Growth Systems
 
Verify:
 
 
1. L-systems.
 
2. Recursive branching.
 
3. Tree generation.
 
4. Branch generation.
 
5. Root generation.
 
6. Vine generation.
 
7. Leaf generation.
 
8. Leaf-vein generation.
 
9. Biological vein generation.
 
10. Veins beneath skin as an artistic texture/reference.
 
11. Space-colonization-style growth where useful.
 
12. Hand-drawn contour constraining growth.
 
13. Hand-drawn midrib/guide controlling leaf-vein generation.
 

  
# AM. Crystallization and Organic Pattern Systems
 
Verify:
 
 
1. Diffusion-limited aggregation.
 
2. Frost patterns.
 
3. Metal crystallization.
 
4. Mineral dendrites.
 
5. Corrosion patterns.
 
6. Lightning-like growth.
 
7. Reaction-diffusion.
 
8. Organic stripes.
 
9. Organic spots.
 
10. Coral-like structures.
 
11. Alien/biological textures.
 

  
# AN. Natural Procedural Art Uses
 
Verify explicit acknowledgement of procedural tools for:
 
 
1. Clouds.
 
2. Smoke.
 
3. Trees.
 
4. Leaves.
 
5. Leaf veins.
 
6. Skin veins.
 
7. Fur.
 
8. Feathers.
 
9. Fur/dust floating in air.
 
10. Dust.
 
11. Stars.
 
12. Star fields.
 
13. Planets/space textures.
 
14. Water.
 
15. Ripples.
 
16. Waves.
 
17. Rock.
 
18. Bark.
 
19. Crystals.
 
20. Frost.
 
21. Corrosion.
 
22. Terrain.
 
23. Top-down mountains.
 
24. Rivers.
 
25. Drainage.
 
26. Erosion-like structures.
 

  
# AO. Scatter and Placement
 
Verify:
 
 
1. Point scatter.
 
2. Uniform scatter.
 
3. Poisson-disk/blue-noise-like scatter.
 
4. Gradient-driven density.
 
5. Image-driven density.
 
6. Mask-driven density.
 
7. Fractal-driven density.
 
8. Vector-field orientation.
 
9. Procedural size variation.
 
10. Procedural rotation.
 
11. Procedural color variation.
 

 
Uses should include:
 
 
1. Stars.
 
2. Dust.
 
3. Fur.
 
4. Feathers.
 
5. Leaves.
 
6. Debris.
 
7. Freckles.
 
8. Environmental texture.
 

  
# AP. Terrain and Top-Down Mountains
 
Verify:
 
 
1. Height-field terrain.
 
2. z=H(x,y) representation.
 
3. Mountain generation.
 
4. Ridge generation.
 
5. Valley generation.
 
6. Contour extraction.
 
7. Slope.
 
8. Shading.
 
9. River/drainage path generation.
 
10. Approximate erosion.
 
11. Stylized map output.
 
12. Procedural topographic lines.
 

  
# AQ. Mathematical Image Transformations
 
Verify:
 
 
1. Complex-number/image-transform experimentation.
 
2. M.C. Escher Print Gallery inspiration.
 
3. Complex logarithm.
 
4. Complex exponential.
 
5. Power transforms.
 
6. Möbius transforms.
 
7. Inversion.
 
8. Polar mapping.
 
9. Log-polar mapping.
 
10. Recursive/Droste transforms.
 
11. Spiral transforms.
 
12. Mathematical transforms applicable to existing images.
 

  
# AR. Tiling and Tessellation
 
Verify:
 
 
1. Seamless rectangular tiling.
 
2. Wrapped coordinates.
 
3. Tileable noise.
 
4. Hexagonal repetition.
 
5. Rotation-based tiling.
 
6. Reflection-based tiling.
 
7. Wallpaper symmetry groups.
 
8. Kaleidoscopic patterns.
 
9. Radial repetition.
 
10. Tessellated imagery.
 
11. Recursive tiling.
 
12. Non-periodic/quasicrystalline patterns as experimental possibilities.
 
13. Existing images used as repeating tiles.
 
14. Procedural textures used as repeating tiles.
 

  
# AS. Game Texture Creation
 
Verify:
 
 
1. Seamless game textures.
 
2. Wrapped painting mode.
 
3. Procedural generation across tile boundaries.
 
4. Block/environment textures.
 
5. Repeating materials.
 
6. Animated procedural textures.
 
7. Time-dependent seamless textures.
 
8. Export/bake workflow for game assets.
 

  
# AT. Animation
 
Verify:
 
 
1. Raster animation.
 
2. Stroke/vector-like animation where appropriate.
 
3. Grease-Pencil-inspired workflow concepts.
 
4. Timeline.
 
5. Onion skin.
 
6. Keyframes.
 
7. Multiframe editing.
 
8. Procedural modifiers applied to frame ranges.
 
9. Time as a node input.
 
10. t=current frame/time.
 
11. Animated noise.
 
12. Animated fractals.
 
13. Animated gradients.
 
14. Animated masks.
 
15. Animated warps.
 
16. Procedural growth animation.
 
17. Cloud movement.
 
18. Water/ripple movement.
 
19. Star twinkling.
 
20. Frost/crystal growth.
 

  
# AU. Procedural Animation Fill and Masking
 
Verify:
 
 
1. Smart fill across selected frames.
 
2. Procedural masking across selected frames.
 
3. Line-art-based automatic flats across frames.
 
4. Gap closing across frames.
 
5. Underfill across frames.
 
6. Procedural texturing across multiple frames.
 
7. Parameters restricting which frames receive an effect.
 
8. Texture tracking/following moving regions.
 
9. Region/stroke identity where feasible.
 
10. Caching unchanged frames.
 

  
# AV. Performance and Mobile Constraints
 
Verify:
 
 
1. Samsung Galaxy Tab S9 Ultra target.
 
2. Android ARM64.
 
3. Vulkan/GPU compute investigation.
 
4. GPU acceleration where appropriate.
 
5. Tile-based processing.
 
6. Dirty-region recomputation.
 
7. Dependency tracking.
 
8. Node-result caching.
 
9. Lazy evaluation.
 
10. Reduced-resolution interactive previews.
 
11. Full-resolution refinement after interaction.
 
12. Adjustable procedural quality.
 
13. Recursion/iteration limits.
 
14. Bounding-box-limited evaluation.
 
15. Frame caching.
 
16. Node fusion/optimization where worthwhile.
 
17. Thermal monitoring.
 
18. Battery impact.
 
19. RAM usage.
 
20. GPU workload.
 
21. CPU workload.
 
22. S Pen latency has higher priority than procedural-preview latency.
 
23. Procedural content may refine after the brush stroke.
 
24. Avoid full-canvas recomputation where possible.
 

  
# AW. Live / Quality / Bake Workflow
 
Verify:
 
 
1. Live mode.
 
2. Fast interactive previews.
 
3. Quality mode.
 
4. Full-resolution evaluation.
 
5. Bake/freeze operation.
 
6. Rasterize expensive results.
 
7. Vectorize generated results where applicable.
 
8. Cached/frozen procedural nodes.
 
9. Ability to resume/edit procedural source when retained.
 

  
# AX. Open-Source Reuse Strategy
 
Verify that research actively checks:
 
 
1. Existing Krita functionality first.
 
2. KDE/Krita dependencies.
 
3. KSeExpr.
 
4. QtNodes or comparable Qt node editors.
 
5. Material Maker.
 
6. MyPaint.
 
7. libmypaint.
 
8. MyPaint brush collections.
 
9. OpenToonz.
 
10. Tahoma2D.
 
11. Inkscape.
 
12. G'MIC.
 
13. GEGL.
 
14. OpenCV.
 
15. Other GPL-compatible graphics libraries/applications.
 

 
For every candidate verify:
 
 
1. Exact repository.
 
2. Exact source file.
 
3. Exact class/function/module where possible.
 
4. Language/framework.
 
5. Dependencies.
 
6. License.
 
7. GPLv3 compatibility.
 
8. Attribution/license-notice obligations.
 
9. Android compatibility.
 
10. ARM64 viability.
 
11. Integration point in Krita.
 
12. Estimated adaptation hours.
 
13. Performance concerns.
 
14. Maintenance status.
 
15. Whether the code is worth transplanting.
 

  
# AY. Reuse Classification
 
Verify research classifies implementations as:
 
 
1. DIRECT.
 
2. ADAPT.
 
3. ALGORITHM ONLY.
 
4. REJECT.
 

 
Do not confuse "has feature" with "useful implementation."
  
# AZ. Licensing Constraints
 
Verify:
 
 
1. Krita GPLv3 obligations.
 
2. KSeExpr GPL compatibility.
 
3. MIT code reuse requirements.
 
4. BSD code reuse requirements.
 
5. ISC code reuse requirements.
 
6. LGPL implications where applicable.
 
7. Apache-license compatibility where applicable.
 
8. Required copyright notices preserved.
 
9. Required license notices preserved.
 
10. No assumption that public GitHub code without a license is reusable.
 
11. No copying of proprietary application source/assets.
 
12. ibisPaint used only as behavioral/UI inspiration.
 
13. ArtRage used only as behavioral inspiration.
 
14. Rebelle used only as behavioral inspiration.
 
15. Clip Studio used only as behavioral inspiration.
 
16. Photoshop used only as behavioral inspiration.
 
17. No unnecessary royalty-bearing dependencies.
 
18. Preference for free/open-source dependencies.
 

  
# BA. Existing Krita Shortcuts Already Identified
 
Verify research explicitly tracks that Krita already provides or partially provides:
 
 
1. Existing Fill tool.
 
2. Close Gap.
 
3. Grow Selection.
 
4. Adaptive stopping against linework.
 
5. Reference-layer filling.
 
6. Enclose-and-Fill.
 
7. Existing selections.
 
8. Generator/fill layers.
 
9. Gamut masks.
 
10. Advanced/Artistic color selectors.
 
11. Curve/path infrastructure.
 
12. Bézier infrastructure.
 
13. Brush sensor infrastructure.
 
14. Hatching brush.
 
15. Spray brush.
 
16. Particle brush.
 
17. Deformation brush.
 
18. Color-smudge brush.
 
19. MyPaint brush integration.
 
20. Animation infrastructure.
 
21. Tile/update-region infrastructure.
 
22. Existing procedural/simplex-noise facilities.
 

  
# BB. KSeExpr Shortcuts
 
Verify acknowledgement that KSeExpr can potentially provide:
 
 
1. Expression evaluation.
 
2. Variables.
 
3. Artist-exposed controls.
 
4. Noise.
 
5. Vector noise.
 
6. FBM.
 
7. Time/4D-capable FBM where available.
 
8. Turbulence.
 
9. Periodic noise.
 
10. Voronoi.
 
11. Trigonometry.
 
12. Powers.
 
13. Logarithms.
 
14. Comparisons.
 
15. Curves/remapping.
 
16. Procedural fill output.
 

 
Verify that first-generation procedural nodes may:
 
 
1. Generate KSeExpr rather than implementing a new renderer.
 
2. Use KSeExpr as a major time-saving backend.
 
3. Avoid building an original expression engine during Month 1.
 

  
# BC. Month-One Implementation Funnel
 
Verify the research framework preserves the current narrow initial build:
 
 
1. Passing-point curve tool.
 
2. Smart Fill UI/presets.
 
3. Color Harmony controls.
 
4. Procedural Lab v0.
 
5. Tablet-oriented workspace.
 

 
Verify that Procedural Lab v0 starts with a small set such as:
 
 
1. UV.
 
2. Value.
 
3. Color.
 
4. Add.
 
5. Multiply.
 
6. Power.
 
7. Sine.
 
8. Clamp.
 
9. Linear gradient.
 
10. Radial gradient.
 
11. Noise.
 
12. FBM.
 
13. Voronoi.
 
14. Color ramp.
 
15. Procedural Fill output.
 

  
# BD. Features Explicitly Deferred From Month One
 
Verify they are DEFERRED BUT TRACKED rather than lost:
 
 
1. Full 3D system.
 
2. Anatomy mannequins.
 
3. IK.
 
4. Full online mesh library.
 
5. Advanced animation automation.
 
6. Cross-frame procedural tracking.
 
7. Full natural-media simulation.
 
8. Rebelle-like fluid simulation.
 
9. Advanced erosion simulation.
 
10. General GPU graph compiler.
 
11. Complete LaTeX editor.
 
12. Full symbolic algebra system.
 
13. Advanced contour-array editing.
 
14. AI object segmentation.
 
15. Advanced differential-equation tooling.
 
16. Full complex-transform system.
 

  
# BE. AI-Assisted Development
 
Verify acknowledgement of:
 
 
1. ChatGPT for architecture, mathematics, debugging, algorithms and code review.
 
2. Claude for large-codebase reading/refactoring where useful.
 
3. Gemini for Android/Google ecosystem assistance where useful.
 
4. Coding agents for narrow implementation tickets.
 
5. Computer-algebra systems for symbolic mathematics.
 
6. Python notebooks for algorithm prototypes.
 
7. Translation of successful prototypes into C++/Qt/KSeExpr/shaders.
 
8. AI-generated code must be reviewed.
 
9. Compiler/tests are authoritative over AI claims.
 
10. Real tablet performance is authoritative over AI estimates.
 
11. AI does not eliminate need for C++/Qt/GPU understanding.
 

  
# BF. Development Toolchain
 
Verify research acknowledges usefulness of:
 
 
1. Git.
 
2. Feature branches/worktrees.
 
3. CMake.
 
4. Ninja.
 
5. Qt Creator and/or equivalent C++ IDE.
 
6. clangd.
 
7. ripgrep.
 
8. Android SDK.
 
9. Android NDK.
 
10. ADB.
 
11. Android profiling tools.
 
12. Perfetto or comparable profiling.
 
13. GPU debugging/profiling later.
 
14. Python for mathematical prototypes.
 
15. Automated tests where practical.
 

  
# BG. Vertical-Slice Development Rule
 
Verify every major subsystem is researched and implemented vertically.
 
Example procedural node:
 
 
1. Node exists.
 
2. Produces expression.
 
3. Renders in Krita.
 
4. Supports undo.
 
5. Saves.
 
6. Reloads.
 
7. Builds on Android.
 
8. Runs correctly with S Pen.
 

 
Example curve tool:
 
 
1. Create points.
 
2. Generate curve.
 
3. Edit curve.
 
4. Render brush.
 
5. Undo.
 
6. Save/reload.
 
7. Android test.
 

 
Example Smart Fill:
 
 
1. UI preset.
 
2. Actual fill.
 
3. Undo.
 
4. Save/reload.
 
5. Android test.
 

  
# BH. Research-Funnel Requirements
 
Verify the framework ranks discoveries by:
 
 
1. Time saved.
 
2. Integration difficulty.
 
3. License compatibility.
 
4. Android feasibility.
 
5. Dependency burden.
 
6. GPU impact.
 
7. CPU impact.
 
8. RAM impact.
 
9. Maintenance risk.
 
10. AI leverage.
 
11. User value.
 

 
Every research result should ideally contain:
 
 
1. Feature.
 
2. Candidate implementation.
 
3. Exact source location.
 
4. License.
 
5. Reuse classification.
 
6. Krita integration point.
 
7. Android viability.
 
8. Dependencies.
 
9. Estimated integration hours.
 
10. AI leverage.
 
11. Technical risk.
 
12. Prototype test.
 
13. Recommended priority.
 

  
# Final Audit Output
 
After searching the research framework, produce:
 
## 1. Coverage Score
 
Report:
 
 
- Total canonical features checked.
 
- Number ACKNOWLEDGED.
 
- Number PARTIAL.
 
- Number MISSING.
 
- Number DEFERRED BUT TRACKED.
 
- Number DUPLICATE/MERGED.
 

 
Do not treat deferred features as missing if they are explicitly preserved.
 
## 2. Missing Feature Table
 
Use:
 
| Feature | Status | Existing Related Coverage | What Is Missing | Recommended Addition |
 
## 3. Weakly Represented Areas
 
Identify categories where individual features technically appear but the research framework is too vague to guide implementation.
 
## 4. Scope-Creep Check
 
Identify anything currently consuming research attention that is not relevant to:
 
 
- shortening implementation time,
 
- finding reusable code,
 
- validating Android feasibility,
 
- preserving the long-term architecture.
 

 
## 5. Month-One Protection Check
 
Confirm whether the research framework still protects these immediate deliverables:
 
 
- Passing-point curves
 
- Smart Fill
 
- Color Harmony
 
- Procedural Lab v0
 
- Tablet workspace
 

 
Flag any research activity likely to delay those deliverables.
 
## 6. Architectural Coverage Check
 
Confirm that the framework acknowledges the major reusable abstractions:
 
 
- Stroke system
 
- Curve system
 
- Scalar fields
 
- Vector fields
 
- Distance/SDF system
 
- Smart/live masks
 
- Procedural nodes
 
- KSeExpr backend
 
- Procedural shading
 
- Contour/hatching generation
 
- Fractal/noise generation
 
- Animation/time
 
- 3D reference system
 
- Common intermediate representation / AST
 
- Live/Quality/Bake evaluation
 

 
## 7. Research Priorities
 
Return the next 10 research questions that have the highest expected value in **development time saved per hour of research**.
 
Prioritize reusable primitives over flashy completed applications.
 
## Final Rule
 
The audit is successful only if every feature in this canonical inventory is either:
 
 
- actively researched,
 
- acknowledged as dependent on another subsystem,
 
- explicitly deferred while retained,
 
- or deliberately rejected with a stated reason.
 

 
No feature should disappear merely because it is not part of Month One.
