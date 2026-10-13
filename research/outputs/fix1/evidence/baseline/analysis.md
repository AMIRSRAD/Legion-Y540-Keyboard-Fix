# Lenovo Y540 keyboard firmware 00000044 — static analysis

Analyzed on 2026-10-12. The updater was not executed and no hardware was flashed. REA 6.4.0 with Ghidra 12.1.4 was used for the native updater inspection; separate Python/PowerShell reads supplied the file-level observations below.

## Files and identity

- `ite1fw11s.exe`: 2,835,096 bytes, 32-bit PE installer. SHA-256 `e5863dcd12c40afb98bd5577c3c9631f8f5f78868bc1b1125355f34637f31834` matches the installer digest recorded in the supplied Lenovo metadata. This comparison does not verify the XML signature.
- `extracted-IT/ITESHFU.exe`: 11,485,623 bytes, x64 native PE updater. SHA-256 `afcca3de209ccfab256aff48b8f7f59dfb6cd6a27b22fc58a41b50f0bd8bb8fa`. The metadata instead lists an 11,492,728-byte updater with digest `96b2a9aa3f71bcd94995c337a12a389c8f3fd6b36e9d7219413b0d6bff34b8e5`. The cause of this discrepancy is unknown. Windows reports the supplied extracted updater as unsigned.
- `extracted-IT/44.bin`: 55,296 bytes (54 KiB), SHA-256 `3afec131c6ed70efa0a3f4b601cb799011a582835d371c57fef68af48519e359`.
- `extracted-IT/SHFU.ini`: updater settings, 890 bytes. The metadata and configuration identify a Lenovo Y540 keyboard update, version `00000044`; the metadata records release date 2023-03-28.

## Firmware observations

At file offset `0x3100`, the image contains `Firmware Version : 00000044`. This agrees with `OEMVEROFFSET=3100` in the configuration.

A USB device descriptor at `0x5307` specifies VID `048D`, PID `C100`, and device revision `0044`. USB string descriptors contain `ITE Tech. Inc.` at `0x5349`, `ITE Device(8910)` at `0x536B`, and `I8380689FA08` at `0x5391`. These are embedded descriptor facts, not observations of a connected device.

Additional ASCII markers include `UUIT817x-Dock-v1.0` near `0x4E` and `IT891x-BBK-56-32-v1.01.01` at `0x2E0`. These identify embedded labels; they do not independently establish the exact installed silicon.

The image begins `02 01 00 02 32 00`, followed by additional similar vectors. Interpreting `02` as an 8051 long-jump opcode yields a plausible reset jump to `0x0100` and interrupt-vector jumps. An 8051-family architecture is therefore a candidate, not a verified architecture selection or decompilation result.

The firmware contains 20,793 `FF` bytes and 1,954 zero bytes; byte entropy is approximately 5.054 bits/byte. These measures do not by themselves establish compression, encryption, or correctness.

## Updater configuration and communication

`MAIN/HWID` is `USB\VID_048D&PID_C100`, matching the firmware's embedded device descriptor. `BOOT/HWID` is `USB\VID_048D&PID_89DB`. The settings also declare chip identifier `8171`, update start address `0`, and update size `54` KiB.

The executable imports `HidD_GetFeature`, `HidD_SetFeature`, `HidD_GetAttributes`, `HidP_GetCaps`, Windows SetupAPI device-enumeration functions, and file/device-handle APIs. These imports support USB HID feature reports as a communication candidate; exact report layouts and executed command sequences remain unverified.

Strings describe old/new firmware versions, entering/exiting flash mode, reading/writing eFlash, checksum errors, comparison failure followed by erase, and completion messages. Combined with the settings, these suggest a version-check / boot-mode / erase-write / validation workflow. This is an inference from static strings and configuration, not a recovered call graph or runtime trace.

Relevant settings include `NEEDERASE=1`, `CHECKSUMMODE=1`, `PROGRAMFAILRETRY=1`, `PROGRAMFAILERASESKIPFIRST1K=1`, `PROGRAMFAILERASETHENRESET=1`, `NOCHECKPID=0`, and `DONOTUPDATETHESAMEVERSION=0`. Their exact conditional behavior requires code tracing.

Checksum settings name range `0400`–`D800`, high/low storage addresses `7FFE`/`7FFF`, and inversion enabled. Stored bytes at those two addresses are `56 22`. A naive byte sum over `[0x0400,0xD800)` is `0x549C` and does not immediately explain those bytes. The checksum algorithm is unresolved; no patching recommendation follows from this calculation.

The complete `44.bin` byte sequence and its first 64 bytes were not found verbatim in the updater. This bounded search does not rule out compressed, transformed, or externally loaded firmware.

## Scope and remaining questions

This is an initial static assessment. Exact HID commands, checksum computation, flash geometry, keyboard scanning/debounce logic, and the metadata/updater mismatch remain unresolved. REA's Windows Ghidra provider supports native x86/x64 PE targets; raw microcontroller firmware was inspected as bytes and descriptors, not decompiled through that provider.

Companion JSON files preserve file facts and offsets. The REA result is saved separately when the native inspection completes.

## Completed REA inspection

REA completed `binary_overview` successfully through Ghidra 12.1.4. Evidence ID: `ev_025931690b009c0de7a5e941703e403feba63dbd459d7dbe61c01a2cf79fcc13`.

REA identifies the supplied updater as a native x86-64 PE application with SHA-256 matching the separately computed file hash. It reports 19 mapped segments, 22,976 discovered procedures, and 39,151 defined strings. The segment inventory includes DWARF `.debug_info`, `.debug_line`, `.debug_str`, and related sections. This is useful for future function tracing, although Ghidra logged DWARF import errors and decompiler warnings during analysis, so debug/type recovery and individual functions should be verified as they are used.

`updater-rea-evidence.json` preserves the complete overview record. This successful overview does not establish the checksum algorithm, exact HID report protocol, or full firmware control flow. No target runtime execution was performed.
