# Y540 fix4 — final experimental candidate

Read CASE-RECORD.md for the complete evidence record and START-HERE.txt for the one-attempt procedure. This is an independent host-updater reconstruction with an explicitly experimental two-byte firmware44 patch. The startup fault is unresolved; no guaranteed repair or recovery is claimed.

Build on Windows x64 with MinGW-w64 GCC and windres: run ./build.ps1. Tests use memory backends and fixtures. Vendor installers, Windows device operations, firmware writes and drivers are not executed by the test suite. The hidden GUI test creates controls only. tools/test_capture_wrapper.py uses mock launch/trace behavior and inert fixtures.

samples/44.bin is the preserved original test fixture. experiment/44-nosleep-exp1.bin is the modified payload; its builder and exact manifest are included. Rebuilding the host EXE does not rebuild the MCU firmware from C. Source/release fix1–fix3 and the original research baseline remain separate.

The final packaged GUI defaults to the experimental filename. Its two-read saved backup and chip qualification remain mandatory. The recorder launcher verifies hashes, records USB events and opens the interactive GUI; it never starts the write automatically. Use only on the affected owner-identified laptop for the final authorized experiment.
