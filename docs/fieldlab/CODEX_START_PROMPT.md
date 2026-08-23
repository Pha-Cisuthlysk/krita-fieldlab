# Prompt to give Codex

Use the following instructions before continuing implementation:

---

You are taking over the `fieldlab` branch of `Pha-Cisuthlysk/krita-fieldlab`.

First, install/read the Field Lab accountability package under
`docs/fieldlab/` and the Field Lab `AGENTS.md`. Treat those files as governing
requirements.

Do not start a new feature until you have audited the current branch against
them.

Your first task is documentation/audit only:

1. Confirm the current branch and latest commit.
2. Inspect `plugins/dockers/fieldlab`.
3. Update `docs/fieldlab/IMPLEMENTATION_STATUS.md` with what is actually present.
4. Verify that the semantic graph remains independent of the docker/UI.
5. Explicitly flag the current per-pixel `FieldGraphSampler` as a reference/
   prototype path that must not become the production batch interface.
6. Confirm that no handwritten FastNoise2 catalog has been started.
7. Confirm Android status is still untested unless there is concrete evidence otherwise.
8. List the next three smallest implementation tasks that satisfy the canonical
   architecture, but DO NOT start them until the audit report is complete.

For every later non-trivial task, execute the pre-task and post-task gates in
`docs/fieldlab/CODEX_AUDIT_PROTOCOL.md`.

Do not modify `master`.
Do not force-push.
Do not merge.
Do not silently change architecture.
Any architectural change must be written as:

PROPOSED CHANGE — REQUIRES USER APPROVAL

The product is painting-first, dual-target Windows + Android ARM64, with the
Samsung Galaxy Tab S9 FE+ as the canonical tablet performance target.

---
