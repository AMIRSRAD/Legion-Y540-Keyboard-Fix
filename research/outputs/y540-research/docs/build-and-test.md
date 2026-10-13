# Build and test

## Native source build

Run `./build.ps1` in PowerShell. It discovers GCC on PATH or the existing Strawberry MinGW-w64 installation; `-Compiler` selects an explicit GCC path. `windres.exe` must be beside GCC. It creates `build/Y540Updater.exe` and test executables. There are no downloaded build packages, vendor compiler dependencies, or global configuration changes.

Only the supplied firmware and INI are needed for regression fixtures. Build uses C11, optimization O2, warnings as errors, Windows SDK headers from MinGW-w64, and HID/SetupAPI/common-dialog/GDI/User32 import libraries.

For alternate CMake builds:

```powershell
cmake -S . -B work/cmake-build -G "MinGW Makefiles" -DCMAKE_MAKE_PROGRAM=C:/Strawberry/c/bin/mingw32-make.exe -DCMAKE_C_COMPILER=C:/Strawberry/c/bin/gcc.exe -DCMAKE_RC_COMPILER=C:/Strawberry/c/bin/windres.exe
cmake --build work/cmake-build -j 4
ctest --test-dir work/cmake-build --output-on-failure
```

The original EXE is input to static analysis only. It is not linked, executed, loaded as a DLL, or required to build our EXE.

## Interfaces

No arguments opens the GUI. `--verify FIRMWARE INI` validates size and checksum. `--plan FIRMWARE INI OUTPUT.json` exports a staging-only report plan and refuses to overwrite an existing path. It is not a complete flash transcript: reads, boot handoff, erase, error paths and reset are implemented in protocol.c and exercised separately by the emulator.

`--list` opens metadata handles and enumerates accessible HID collections. `--update FIRMWARE INI` performs real feature-report writes and is never invoked by automated tests. GUI update uses a copied background-task input and prevents window closure while that task is active. Default file search first checks beside the EXE, then ../samples.

## Supported reconstruction profile

54 KiB full image; update start 0; UPDATEONLYPARAMETER=0; DOCKINGBURN=0; MAININDEX=0; MAIN/HWID USB\VID_048D&PID_C100; BOOT/HWID USB\VID_048D&PID_89DB; default main report ID decimal90/hex5A; no same-version prohibition; exact VID/PID/page/usage selection. Unexpected or ambiguous devices are rejected. Config validation occurs before boot feature writes. General ITE chip variants, parameter-only, docking, erase-only/read-only special workflows and original wrapper automation are outside this build's claimed support.

Device update tries an existing matching boot collection first. Otherwise it opens the matching normal collection, sends the custom key and boot request, closes it, waits and polls for boot enumeration. It checks boot chip identity before programming. The implemented data path is erase -> nonfirst blocks -> first block -> full readback -> compare -> reset, with configured comparison retries and recovery erase. HID API failures abort. First-block preservation in recovery follows the supplied profile.

## Intentional differences / remaining qualification

- Padding and the original undefined boot-command second byte become deterministic zeros.
- A report-zero handshake fallback exists after the initialized5A attempt; the original falls back toward5A. This extension is tested in simulation, not on a device.
- Readback response address/length echo is checked, although the original code copies its data without that check.
- Duplicate matches and incorrect feature-report lengths fail instead of selecting arbitrary handles.
- Transport failures stop immediately at the update level instead of allowing ignored lower-level failures.
- Reconnect polling replaces device disable/remove/rescan operations; some Windows/hardware combinations may need those original operations.
- Compare-failure readback backups, TVSU wrapper shutdown, version registry writes, and the original GUI/timer implementation are not reproduced.
- The boot-register helper uses transport retries but not the original outer100-failure loop.
- File dialogs and C file I/O currently use Windows ANSI paths. Use a path representable in the active Windows code page.

These choices can affect physical compatibility. Emulator tests validate the implemented reconstruction against recovered packet semantics and supplied fixture bytes; they are not a real keyboard test or a differential execution against the original updater.

## Test coverage

Core checks: actual firmware, checksum corruption, INI fields, report endian/length vectors, 1024/57 staging boundaries and FF padding. Transport checks: report IDs, deterministic bytes, delay/retry limits, unchanged receive outputs on failure. Protocol checks: complete simulated flash identity, first-block-last, skipFF, stage-checksum/API aborts, compare retries/reset, IVT rejection before erase and chip handshake. App checks: sample validation and hidden Win32 control initialization. GUI visual layout and real hardware writes remain unverified.

Build receipts and native import/hash facts are retained in evidence/build-verification.json and evidence/build-log.txt. Build binaries are local outputs and excluded from Git.

## Source archive

The source ZIP includes the firmware and INI regression fixtures, their scoped SHA-256 manifest, source, tests and evidence. It intentionally excludes the original vendor EXEs; those are not build dependencies. To repeat binary reverse engineering, supply the original installer/updater separately and validate their recorded identities. The full local research project retains the preserved originals in its Git-ignored samples folder.
