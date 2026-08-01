# Fluent desktop UI design

## Status

Accepted

## Context

Rapid Session Analyzer is a Qt/QML desktop application that needs a coherent design language across all supported desktop operating systems. We considered following each platform's native conventions or treating UWP styling as a cosmetic theme, but both would produce inconsistent navigation, commands, input, and accessibility behavior.

## Decision

All existing and new desktop UI follows Microsoft's live [Windows app design guidance](https://learn.microsoft.com/windows/apps/design/) and [Fluent Design language](https://fluent2.microsoft.design/), adapted to Qt/QML without adopting Windows-only APIs. This applies to visual design, layout, navigation, commands, controls, typography, color, iconography, motion, keyboard and mouse interaction, and accessibility on every supported desktop operating system. The guidance is the default rather than a rigid copy: a local departure must be documented beside the affected component with the relevant guidance and a user-centered rationale; a cross-cutting or hard-to-reverse departure requires an ADR.
