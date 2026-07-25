# Rapid Session Analyzer

A Qt/QML desktop application for downloading, browsing, and analyzing driving sessions recorded by the [rapid-rusty](https://github.com/mFlorianW/rapid-rusty) laptimer.

## Language

**Laptimer**:
The external hardware device running the rapid-rusty firmware/software. It records Sessions and exposes them over its network API for this application to connect to and download from.
_Avoid_: Device, timer

**Session**:
A single recorded outing on a Track, consisting of the date, start time, the Track driven, and an ordered list of Laps. Downloaded in full from the Laptimer, including all Telemetry.
_Avoid_: Run, outing

**Session Library**:
The local collection of Sessions this application has downloaded from the Laptimer and retains for browsing and analysis. Navigation between downloaded Sessions happens within the Session Library.
_Avoid_: Session store, archive, database

**Lap**:
One completed circuit of the Track within a Session, made up of Sector times and the Telemetry recorded during that circuit.
_Avoid_: Circuit

**Sector**:
A split segment of a Track, bounded by consecutive checkpoint positions (start/finish line and any intermediate split points). Used both for the checkpoint position itself and, in the context of a Lap, for the timed duration between two consecutive checkpoints.
_Avoid_: Split, segment (as a standalone term — use Sector)

**Laptime**:
The total duration of a Lap, computed as the sum of its Sector times.
_Avoid_: Lap duration (use Laptime)

**Track**:
The racetrack a Session was driven on, defined by a name, a start line, an optional finish line, and its Sector checkpoint positions.
_Avoid_: Circuit, course

**Telemetry**:
The time-ordered series of GPS position, speed, and timestamp samples recorded throughout a single Lap. Used to render the speed-over-distance/time graph.
_Avoid_: Log points, GNSS data, track log

**Lap Comparison**:
A side-by-side analysis of two or more Laps, overlaying their Telemetry (e.g. speed graphs) to compare performance. Laps being compared must share the same Track but may come from different Sessions.
_Avoid_: Session comparison (comparison is between Laps, not whole Sessions)

## Session Overview

Within a Session, the application presents an overview of all Laps: their Laptimes and Sector times, enabling quick scanning of performance across the Session before drilling into a Lap Comparison.
