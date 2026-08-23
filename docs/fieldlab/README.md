# Field Lab Codex Accountability Package

## Purpose

This package turns the historical Field Lab/Krita research corpus into a
repository-level accountability system for Codex and future coding agents.

The governing principle is:

> Preserve the large artistic vision, but implement it through a small set of
> reusable primitives and adapters. A feature may be deferred, merged into a
> broader primitive, or rejected with a reason, but it must not silently vanish.

## Source corpus reviewed

The supplied master document contains six primary historical chats:

1. FastNoise2 first Field Lab backend plan
2. FastNoise2 and Krita reuse plan streamlined
3. Simplify Field Lab with Krita native processing
4. FastNoise2 could simplify the field architecture
5. Field Lab Planning Watch
6. Python App Customization Feasibility

The corpus also embeds the exhaustive Research Framework Feature Coverage Audit,
the Master Deep-Research Prompt, implementation/reuse reports, and the user's
later scope clarification.

## Files

- `AGENTS.md` — hard rules Codex should read before coding.
- `CANONICAL_REQUIREMENTS.md` — current product vision and priorities.
- `CANONICAL_FEATURE_INVENTORY_SOURCE.md` — preserved exhaustive inventory.
- `ARCHITECTURE_GUARDRAILS.md` — architectural invariants and approval gates.
- `FEATURE_LEDGER.md` — compact feature-family ledger.
- `REUSE_LEDGER.md` — reuse-before-build decisions.
- `IMPLEMENTATION_STATUS.md` — current repository audit.
- `DECISIONS_AND_CONFLICTS.md` — reconciles historical plans without silently rewriting them.
- `CODEX_AUDIT_PROTOCOL.md` — mandatory pre-task and post-task audit procedure.
- `CODEX_START_PROMPT.md` — prompt to give Codex when installing this package.

## Status vocabulary

Requirement state:
- ACTIVE
- DEPENDENT
- DEFERRED
- REJECTED
- PROPOSED / REQUIRES USER APPROVAL

Implementation coverage:
- NOT STARTED
- RESEARCHED
- REUSE IDENTIFIED
- PARTIAL
- IMPLEMENTED
- TESTED WINDOWS
- TESTED ANDROID
- COMPLETE
- BLOCKED

A requirement state and implementation state are separate. For example,
`ACTIVE / NOT STARTED` is valid, as is `DEFERRED / RESEARCHED`.

## Authority order

When historical material conflicts:

1. Explicit later user clarification wins over older brainstorming.
2. Explicit user approval wins over an assistant proposal.
3. An assistant recommendation is not an architectural decision unless approved.
4. A deferred feature remains recorded.
5. A feature implemented through a shared primitive remains an acknowledged
   artistic use case rather than disappearing from the ledger.
