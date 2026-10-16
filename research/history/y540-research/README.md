# Y540 keyboard updater — source reconstruction

This project builds a native Windows x64 EXE from readable C11 source. It reconstructs the supplied Lenovo Y540 / ITE updater profile using retained REA/Ghidra evidence. The original proprietary source was not recovered, and this is not a byte-identical vendor build.

## Build your EXE

From this folder in PowerShell:

```powershell
.\build.ps1
```

Output: `build/Y540Updater.exe`. The script compiles resources and source, runs core/transport/protocol-emulator tests, validates the supplied firmware, and initializes the GUI invisibly. It does not connect to or write hardware.

Build dependencies: Windows x64, MinGW-w64 GCC and `windres` (already available on this machine at `C:\Strawberry\c\bin`). To choose another compatible toolchain:

```powershell
.\build.ps1 -Compiler C:\path\to\gcc.exe
```

The application uses Windows system DLLs; it needs neither .NET nor the original VCL runtime. Python/REA/Ghidra/Java are investigation dependencies, not build dependencies. An alternate CMake build is documented in `docs/build-and-test.md`.

## Use

Double-click the EXE to open its GUI, choose firmware and INI, validate, preview the staging plan, or list HID metadata. `Update keyboard` performs actual device writes after its confirmation. The GUI and CLI update path are implemented for the supplied 54 KiB, start-address-zero, normal full-image profile. Hardware behavior has not been validated on a keyboard.

```powershell
.\build\Y540Updater.exe --verify samples/44.bin samples/SHFU.ini
.\build\Y540Updater.exe --plan samples/44.bin samples/SHFU.ini work/plan.json
.\build\Y540Updater.exe --help
```

`--list` enumerates HID metadata without feature reports. `--update FIRMWARE INI` initiates the implemented boot/erase/write/verify/reset workflow; it is not run by the build or tests. Keep power connected throughout any deliberate device update.

## Verified offline

- Source builds with `-Wall -Wextra -Werror` using GCC 13.2.
- C and Python checksum reconstructions validate supplied `44.bin`: stored `5622`, residual `0000`.
- Emulator reproduces all 55,296 bytes: 54 blocks, 35 committed non-FF blocks, 19 FF blocks skipped, 630 C1 data packets.
- First 1 KiB block is committed last; readback comparison precedes reset.
- Corruption, staging-checksum failure, transport failure, retry exhaustion, successful retry, IVT mismatch, chip identity, and handshake report IDs are covered by offline tests.
- Preserved sample hashes verify. Independent installer extraction confirms the extracted updater is exactly its embedded payload, despite different external-file XML metadata.

## Completion boundary

The self-compilation milestone is complete. Keyboard hardware qualification remains outstanding. This build deliberately uses zero padding, exact device identity checks, fail-fast API handling and reconnect polling; some original device-removal, installer/TVSU, GUI timer and registry behaviors are not reproduced. The boot command's second payload byte was uninitialized/stack-adjacent in the original; this build explicitly sends zero. These differences and the untested physical behavior prevent claiming full vendor equivalence.

The firmware remains the supplied prebuilt `44.bin`; its own source was not recovered. We can compile the Windows updater, not regenerate the microcontroller firmware from source.

## Project map

- `src/`: native application, checksum/config core, Windows HID adapter, protocol/state implementation.
- `tests/`: hardware-free feature-report emulator and transport tests; `src/core_tests.c` covers core behavior.
- `docs/build-and-test.md`: build/run instructions and verification limits.
- `docs/update-state-machine.md`: recovered original state sequence and Evidence IDs.
- `docs/reconstruction-scope.md`: artifact roles and original symbol map.
- `docs/initial-globals.md`: initialization/default evidence.
- `docs/package-identity.md`: independent static extraction and identity resolution.
- `docs/findings.md`, `docs/roadmap.md`: research status and remaining questions.
- `evidence/`: complete REA records, derived pseudocode, original COFF/DWARF facts and test/build receipts.
- `samples/`: preserved inputs and SHA-256 manifest. Vendor binaries remain excluded from Git.

Original artifacts were never executed. Tests execute only the newly built source programs with memory-only backends. Analysis sessions were closed with saved evidence snapshots. Nothing was flashed during development.
