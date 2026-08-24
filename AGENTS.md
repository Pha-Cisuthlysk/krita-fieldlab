# Field Lab Agent Instructions

These instructions govern coding-agent work in this repository.

## Read first

Before modifying Field Lab, read:

- `docs/fieldlab/CANONICAL_REQUIREMENTS.md`
- `docs/fieldlab/ARCHITECTURE_GUARDRAILS.md`
- `docs/fieldlab/FEATURE_LEDGER.md`
- `docs/fieldlab/REUSE_LEDGER.md`
- `docs/fieldlab/FASTNOISE2_DEPENDENCY.md`
- `docs/fieldlab/IMPLEMENTATION_STATUS.md`
- `docs/fieldlab/DECISIONS_AND_CONFLICTS.md`
- `docs/fieldlab/CODEX_AUDIT_PROTOCOL.md`

The preserved exhaustive historical inventory is:
`docs/fieldlab/CANONICAL_FEATURE_INVENTORY_SOURCE.md`.

## Non-negotiable rules

1. Work on `fieldlab`, not `master`.
2. Do not force-push, merge, or delete substantial architecture without user approval.
3. Krita remains a painting application first.
4. Keep the semantic Field Lab graph independent of visual node-editor libraries.
5. Search before build: Krita → FastNoise2 → G'MIC → small mature C++ library →
   proven adaptable source → original implementation.
6. Do not hand-author the production FastNoise2 node catalog; use metadata.
7. Production scalar evaluation must be batch/tile oriented.
8. Reuse Krita sensor/curve, fill/colorize, layer, undo, and document machinery.
9. Windows and Android ARM64 are first-class targets.
10. Canonical Android device is Samsung Galaxy Tab S9 FE+.
11. A proposed architectural change must be labeled:
    `PROPOSED CHANGE — REQUIRES USER APPROVAL`.
12. Update `docs/fieldlab/IMPLEMENTATION_STATUS.md` after meaningful work.

## Product drift warning

Field Lab is not merely a noise generator.

The active vision includes scalar/vector/distance fields, SDF, fractals, domain
warping, line-art distance, contours, streamlines, hatching, flow, procedural
baking, intelligent coloring, and input modulation.

The broader fork also protects Passing-Point Curves, Smart Fill, Color Harmony,
and a Tablet Workspace.

## Current performance warning

The present `FieldGraphReferenceSampler::sampleScalarReference()` per-pixel loop
is acceptable only as a test/debug oracle. Do not build or route a production
backend API around it.
