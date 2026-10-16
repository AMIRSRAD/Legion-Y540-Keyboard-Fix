# Build and test fix1

Run `.\build.ps1` in PowerShell. It discovers MinGW-w64 GCC on PATH or at `C:\Strawberry\c\bin`; `-Compiler` selects another compatible toolchain. `windres.exe` must be beside GCC. Output: `build/Y540Updater.exe`. No vendor EXE, .NET, REA, Ghidra or Java is needed to compile.

C11, O2, `-Wall -Wextra -Werror`; Windows HID/SetupAPI/configuration-manager/GUI imports. Firmware/INI filenames currently use ANSI APIs; use a path representable in the active Windows code page. Logs and flash backups use wide paths.

Alternate CMake build:

```powershell
cmake -S . -B work/cmake-build -G "MinGW Makefiles" -DCMAKE_MAKE_PROGRAM=C:/Strawberry/c/bin/mingw32-make.exe -DCMAKE_C_COMPILER=C:/Strawberry/c/bin/gcc.exe -DCMAKE_RC_COMPILER=C:/Strawberry/c/bin/windres.exe
cmake --build work/cmake-build -j 4
ctest --test-dir work/cmake-build --output-on-failure
```

Both routes run only memory emulators, pure classification, file tests, offline validation and hidden controls. They do not inventory/restart/flash hardware. Emulator-created backups are removed by the tests. App verification creates a session log beside the built executable.

## Interfaces

- No arguments: GUI; recommended hardware test in root README.
- `--verify FIRMWARE INI`: offline size/checksum validation.
- `--plan FIRMWARE INI NEW.json`: staging-only C0/C1/D0/C3 plan; refuses existing output. Boot/reads/erase/reset/errors are not represented.
- `--diagnose [--boot-power ac|battery|unknown]`: current PnP/power metadata without features; startup power marked owner-reported.
- `--list`: HID metadata without feature commands.
- `--update FIRMWARE INI`: deliberate real hardware writes with mandatory backup. No CLI confirmation; invoking this flag is the action. Never run by tests.
- `--gui-smoke`: hidden controls, no hardware.

USB restart is a confirmed GUI action. Device-changing paths hold a named cross-process mutex. Close vendor updaters, which cannot share the guard.

## Profile and sequence

54 KiB image at address0; normal048D:C100/FF89:0010, boot048D:89DB/FF89:00DB, report5A custom handshake, known8171/8176 chip family. Unsupported modes, disabled PID/chip checks and missing/unhealthy/ambiguous devices fail closed.

Reserve a new backup file before custom-mode handoff, poll for boot on the same physical parent/port, check chip, read all flash twice, compare reads, save+flush backup, then erase. Existing boot devices need the same backup. Commit nonfirst blocks before block0, verify full readback, reset only a verified image. Exhausted comparison retries cause no extra erase/reset. Failed handoff attempts normal-mode cleanup; failures after successful handoff leave boot mode for investigation.

## Verification

Core: checksum/config/bounds/staging. Transport: retries, IDs, padding, unchanged failed receive, trace and physical selection. Protocol: durable backup/no overwrite/two-read mismatch, complete flash, first-block-last, FFskip, staging/API failures, compare retries, no final erase/reset, D1 without echo, chip guards, mode cleanup. Device state: ghosts, exact case identity/hardware IDs, hub/controller denial. Logger: unique sessions/backup paths and persisted UTF-8. GUI: controls initialized hidden, layout unverified.

Receipt: `evidence/build-verification.json`. Source ZIP excludes vendor EXEs, build/dist/work, Git and copied raw machine captures. It includes unchanged44/INI fixtures, scoped manifest, source/tests and derived evidence. Raw case captures remain in the supplied case folder and local `evidence/case-inputs` only.
