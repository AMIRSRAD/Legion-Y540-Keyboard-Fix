# Research roadmap

| Milestone | State | Acceptance evidence |
| --- | --- | --- |
| Preserve target identity and baseline | Complete | Sample manifest verifies; baseline REA overview linked |
| Classify updater/firmware/driver roles | Partial | Native updater and raw firmware identified; separate driver dependency remains unverified |
| Trace USB discovery and report transport | Partial: wrapper and selection recovered | HID import xrefs, decompiled wrappers, callers, report length and handle selection |
| Recover version/checksum routines | Partial: checksum model validated on supplied image | Addressed functions, byte ranges, integer widths and comparison behavior; offline tests against supplied firmware |
| Recover update state machine | Open | Entry/config parsing through boot transition, erase/write/verify/reset, retry and error edges |
| Resolve package mismatch | Open | Independent extraction of preserved installer without executing it; hashes compared with current extracted updater |
| Establish firmware CPU/memory model | Open | Verified Ghidra language choice, reset/vector map, code/data separation and representative disassembly |
| Map keyboard behavior | Open | USB descriptors, scan matrix and debounce/HID paths linked to firmware code |
| Build offline protocol model | Open | Pure encoding/decoding and checksum fixtures; no device writes |

Current next step: recover GetHIDDevicePath vendor/path filtering, INI defaults, and the main update-button state machine. The first function trace and offline checksum model are documented in updater-trace.md. Hardware experiments are a later, separately scoped phase; this project currently performs static analysis only.
