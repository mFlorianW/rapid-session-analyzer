# Independent repo, no shared code with rapid-android

This repo has its own `common/` domain model and `RapidControls` QML module,
duplicated rather than shared with `rapid-android` via a git submodule/subtree,
even though both apps model the same rapid-rusty domain (Session, Lap, Track,
GnssPosition) and could share UI primitives. We considered depending on
rapid-android's libraries directly, but rejected it: the two apps target
different platforms (this one is desktop-only; rapid-android also targets
Android) and evolve independently, so cross-repo coupling would trade a small
amount of duplication for ongoing submodule/versioning overhead. Each repo
owns its own copy of the domain model and controls.
