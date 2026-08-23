# Codex Audit Protocol

Codex must execute this protocol for every non-trivial Field Lab task.

## Pre-task gate

Before editing code, record:

1. What requirement ID(s) does this task satisfy?
2. Is the requirement ACTIVE, DEPENDENT, DEFERRED, REJECTED, or PROPOSED?
3. What artist workflow does it improve?
4. Has Krita already solved part or all of it?
5. Has FastNoise2 already solved part or all of it?
6. If it is generic raster processing, has G'MIC been checked?
7. Is a mature small C++ implementation available?
8. Does the task alter an architectural invariant?
9. Does it add a dependency?
10. What license applies?
11. What is the Windows impact?
12. What is the Android ARM64 / S Pen / touch impact?
13. What is the smallest reversible implementation?
14. How will it be tested?
15. What evidence will prove completion?

If #8 is yes, stop unless the change is already explicitly approved. Write:

**PROPOSED CHANGE — REQUIRES USER APPROVAL**

## During implementation

- Keep changes small and reversible.
- Do not edit `master`.
- Do not force-push.
- Do not silently add large dependencies.
- Keep semantic graph state independent of the visual editor.
- Preserve testability without launching the whole UI where practical.
- Prefer existing Krita infrastructure to parallel subsystems.
- Preserve Android compatibility in interfaces even when Android cannot be
  tested in the current task.
- Do not build a beautiful node editor before evaluation, persistence, preview,
  and bake fundamentals are proven.

## Post-task record

Append/update an audit entry with:

- Task
- Date/commit
- Requirement IDs
- Requirement state
- Implementation state
- Files changed
- Reuse source
- New dependency/license
- Architecture changed? yes/no
- Windows build/test
- Android build/test
- Unit/integration tests
- Performance implications
- Known limitations
- What remains uncertain
- Next dependency
- Rollback note

Example:

Task: 2D scalar preview  
Requirements: FL-SCALAR, FL-PREVIEW  
Requirement state: ACTIVE  
Implementation: PARTIAL  
Windows: TESTED  
Android: NOT TESTED  
Reuse: Qt/Krita UI; native prototype evaluator  
Architecture changed: No  
Known limitation: reference sampler is per-pixel and must not become production
batch architecture  
Next: FastNoise metadata + backend batch interface

## Scope erosion check

At the end of every milestone verify that these still exist in the ledger:

- Passing-point curves
- Smart Fill
- Color Harmony
- Tablet workspace
- fractals
- procedural baking
- scalar fields
- vector fields
- distance fields
- line-art distance
- SDF
- domain warping
- contours
- streamlines
- hatching
- field flow
- intelligent coloring
- pressure/input modulation

A task is not allowed to redefine Field Lab as only a noise generator.

## Deferred-feature check

Do not spend implementation time on deferred/rejected families merely because
they are interesting.

If a deferred feature influences an interface, preserve an architectural
landing point and continue the current task.
