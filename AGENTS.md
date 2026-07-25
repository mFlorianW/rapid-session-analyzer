## Agent skills

### Issue tracker

Issues and PRDs live as GitHub issues; use the `gh` CLI (no external-PR triage). See `docs/agents/issue-tracker.md`.

### Triage labels

Default label vocabulary: `needs-triage`, `needs-info`, `ready-for-agent`, `ready-for-human`, `wontfix`. See `docs/agents/triage-labels.md`.

### Domain docs

Single-context layout — `CONTEXT.md` + `docs/adr/` at the repo root. See `docs/agents/domain.md`.

### Commit granularity

When `/implement` works a ticket, commit at the level of a logical unit within
the ticket — coarser than a single red-green TDD cycle, finer than "the whole
ticket in one commit". A logical unit is a cohesive piece of behavior that
stands on its own (e.g. one new type + its tests, one interface + its first
implementation) — not every individual test/implementation pair, and not the
entire ticket squashed into a single commit.
