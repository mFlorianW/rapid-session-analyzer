# Platform UI fonts

## Status

Accepted

## Context

ADR-0003 adopts Fluent desktop UI guidance across every supported desktop operating system. Fluent typography commonly uses Segoe UI, but bundling or requiring that Windows-specific font would weaken the application's cross-platform behavior.

## Decision

Use the host platform's default UI font throughout the shared Fluent controls. The shared theme provides hierarchy, spacing, contrast, and interaction states without selecting or bundling a font family.
