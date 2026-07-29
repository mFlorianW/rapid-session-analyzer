# JSON-file-per-session storage

## Status

Accepted

## Context

The Session Library needs a local persistence format before higher-level browsing and analysis features can be built. The local store must keep full Session payloads downloaded from the Laptimer, let the desktop app read and write them without a database bootstrap step, and stay interoperable with the existing rapid-rusty JSON schema and the sibling rapid-android application.

## Decision

Store each downloaded Session as one JSON file in the Session Library directory, using the rapid-rusty Session JSON schema as the file contents and deriving SessionInfo entries from the stored file name plus the parsed Session payload.

## Consequences

- The Session Library stays easy to inspect, back up, and migrate with normal filesystem tools.
- The desktop app can exchange Session files with rapid-rusty and rapid-android without a translation layer.
- Listing sessions requires reading JSON files to derive SessionInfo metadata, which is acceptable for the current small-library foundation and can be optimized later behind the same storage interface if needed.
