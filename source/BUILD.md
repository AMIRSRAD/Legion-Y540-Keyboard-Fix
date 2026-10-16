# Building the updater and firmware from source

This is only needed if you want to check or change the code. Normal users should use the ZIP in [`download/`](../download/).

## Requirements

- Windows 10/11, Python 3, and a MinGW-w64 GCC with `windres` (tested with WinLibs GCC 16.2.0 UCRT x86_64).
- Lenovo's firmware package `ite1fw11s.exe` (Y540 keyboard firmware 00000044). Extract it statically (for example with innoextract) to get `44.bin` and `SHFU.ini`.
- The keyboard's upper-flash dump `upper-flash-dump.bin` (`0xD800–0xFFFF`, SHA-256 `6160ed91…684d2a`), preserved in the research archive (restore instructions in [research/ARCHIVE.md](../research/ARCHIVE.md)). It is only used offline to check the bootloader bytes exp3/exp4 depend on; the updater checks the real chip itself before erasing.

Put them in `source/samples/` (ignored by git): `44.bin`, `SHFU.ini`, `upper-flash-dump.bin`, and `44-nosleep-exp1.bin` (from the release, or rebuild with `research/analysis-history/firmware-nosleep-exp1/build_patch.py`) and `exp2-backup-test.bin` (exp2 image, used only by a rejection test).

## Firmware

```powershell
cd source
python firmware/build_exp3.py samples/44.bin samples/upper-flash-dump.bin samples/44-recovery-exp3.bin
python firmware/build_exp4.py samples/44.bin samples/upper-flash-dump.bin samples/44-reset-exp4.bin
python firmware/test_exp4.py  samples/44.bin samples/upper-flash-dump.bin
python firmware/test_exp3.py  samples/44.bin samples/upper-flash-dump.bin
```

Expected SHA-256: exp4 `27438bf439766926420047b4cb65fcfca2417c7d6a36f7802d824f1f7f27ca34` (checksum 506A), exp3 `e0a959a63dceada1f5fad6846451372271e266ec176cfd25bb322a69199b5457` (0699).

## Updater

```powershell
powershell -NoProfile -ExecutionPolicy Bypass -File build.ps1 -Compiler C:\path\to\mingw64\bin\gcc.exe
```

This builds `build/Y540Updater.exe` with `-Werror` and runs every offline test: checksum/config, HID transport, the protocol emulator (backup, dependency check, interrupted-write resume, rollback, failure paths), device-state fixtures, session log and a hidden GUI start-up. No test touches a real device.

The download ZIP's `Y540Updater.exe` (SHA-256 `e0ff85d3…6c0483`) was built this way; see `SHA256SUMS.txt` inside the ZIP.

## Source map

| Path | Purpose |
|---|---|
| `src/protocol.c` | Bootloader protocol: handoff, chip check, backup, dependency check, erase/write/verify, known-image allowlist |
| `src/hid_transport.c` | Windows HID access and physical-port binding |
| `src/app.c` | GUI and command line |
| `src/device_state.c`, `src/session_log.c`, `src/power_policy.c` | Diagnostics and logging |
| `firmware/build_exp4.py`, `test_exp4.py` | exp4 generator and 8051-model test |
| `firmware/build_exp3.py`, `test_exp3.py`, `instruction_model.py`, `evidence/` | exp3 and the shared CPU model |
| `tests/` | Offline updater tests |

The updater is a reconstruction of Lenovo's ITESHFU flash protocol, not Lenovo's source.
