# Updater trace — first focused pass

Target: `ITESHFU.exe`, SHA-256 `afcca3de209ccfab256aff48b8f7f59dfb6cd6a27b22fc58a41b50f0bd8bb8fa`. Addresses are Ghidra virtual addresses at image base `0x400000`. Source is recovered pseudocode/assembly, not original source or runtime observations. Complete raw MCP responses are in `evidence/rea`; the evidence index maps files to full IDs.

## Located functions

| VA | Recovered name | Evidence file |
| --- | --- | --- |
| 0x407A40 | GetHIDDevicePath | 010-procedures.json (name/address only) |
| 0x407D10 | CheckIfOurDevice | 031-checkdevice.json |
| 0x4089D0 | ConnectHIDDevice | 030-connect.json |
| 0x409E80 | HidRequests | 040-hidrequests.json, 051-hidrequests-assembly.json |
| 0x40AB30 | write_flash | 033-writeflash.json |
| 0x40B260 | CalculateWordCheckSum | 032-checksum.json |
| 0x40FCC0 | TForm1::Button1Click | 050-checksum-validation.json |

Pseudocode copies are stored under `evidence/decompiled/`; they retain decompiler warnings and must not be treated as buildable source.

## HID transport: established from static code

`HidRequests` allocates a 64-byte buffer, writes the report ID at offset zero, and copies payload at offset one. Assembly confirms `ADD RAX, 0x1` before copies and length `0x40` at both feature-report API calls. WriteFlag selects `HidD_SetFeature` versus `HidD_GetFeature`. The wrapper retries at most ten attempts and sleeps 100 ms after API failures; a configured `AllHidCommandDelay` applies before the loop. Captured flash command callers pass report ID zero.

Evidence: `ev_fc31ea46a52a64ee982df8d42de6b3992d98c9c41b92d270ce8d982dbc356626` (pseudocode), `ev_c1e2256612790474ac0108d8787fe4ebd5e1ad37ea7851f50df021b981d3fcb8` (assembly). This describes static API construction; device acceptance and exact unused padding bytes are not established. The buffer is allocated with malloc, so unused bytes should not be assumed zero-filled.

`CheckIfOurDevice` queries preparsed data/caps, requires the requested UsagePage and Usage, and compares the configured PID unless `NoCheckPID` is enabled. VendorID is logged in this function, but no VendorID equality test was recovered here; do not conclude the entire discovery path lacks a vendor filter without tracing GetHIDDevicePath and its callers. `ConnectHIDDevice` enumerates up to MaxScanDevice and calls this selector. Boot mode additionally reads chip-ID bytes and includes an 8171/8176 compatibility branch.

Evidence: `ev_14567034c8a2e4fcf6488306689f3124d73505c8a498851db4f37871a5921d22`, `ev_7cc3999b3ca15069693099660667a52b139fc83d3c0d50a086eeffb05b426860`.

## Flash-transfer skeleton

The recovered `write_flash` loop works in 1024-byte blocks, has first-block policy branches, and skips all-FF blocks. It sends command C0, fills a staging buffer via cmd_set_data using at most 57 firmware bytes per call, requests the staging-buffer checksum, then sends command C3 with a three-byte address and size bytes 00 04. This is a recovered transfer skeleton; full erase/retry/reset state control remains open.

`cmd_set_data` constructs payload C1, little-endian 16-bit offset, one-byte length, then data. `cmd_get_buffer_checksum` sends D0, sums the local 1024-byte staging buffer into a 16-bit accumulator, reads three payload bytes, and compares against bytes 1/2 interpreted little endian.

Evidence: `ev_0ec97c6a7a23c2807143087e87132b7fd3e110afdcfe39bd3e2930e9f8560e4c`, `ev_95995aceca788b8d7995f1143ffdbab2c4b25eedad86ea29fb90a3a414715457`, `ev_d6b395e7a2528f17bdf7b487ad26640e37356c66b788bc7a2ebad85bc9dd54f4`.

## Firmware checksum: advanced from candidate to code-supported model

CalculateWordCheckSum at 0x40B260:

1. Accumulates bytes over the half-open range [start,end) using a 16-bit sum.
2. Excludes offsets 0x80–0x8F when those offsets fall in range.
3. Substitutes FF at the configured high/low checksum offsets.
4. Optionally substitutes FF in a configured trailing range (CheckSum_LastBytesBeFF).
5. Negates the sum modulo 65536 when InvertCheckSum is enabled.
6. Adds the stored big-endian high/low checksum and returns the 16-bit residual.

The caller at 0x40FCC0 checks file size against Update_FileSizeKB * 1024 and accepts a zero checksum return, otherwise emitting Checksum Error. Its pseudocode has a type-propagation warning; verify individual ABI/types before reimplementing the full GUI workflow.

Evidence: `ev_d7d8a962af833b8fbaa710f84a02e240eaa96b25126558ce9c456da0bbfdac4f`, `ev_8aee45406c44b2ebef5aae274cbe2756f0768c09a788965aaec74e7ec72b5ac1`.

With supplied INI settings and absent trailing-FF option modeled as zero, the offline model yields sum 5622, stored 5622, negated sum A9DE and residual 0000. This supports the supplied firmware's checksum consistency under the recovered routine. The actual initialization default for the absent trailing-FF key still needs tracing; no claim about authenticity or hardware compatibility follows from checksum consistency.

`tools/checksum_model.py` reconstructs the pure calculation. Four regression checks cover the supplied image, payload corruption, stored-checksum corruption, and bytes outside the configured range. These checks run only the offline model, not the vendor executable, and do not establish equivalence for all inputs.

## Next pass

Trace GetHIDDevicePath for VID/path filtering; recover INI defaults; trace the main update-button path around 0x40FFC0; establish erase/write/verify/reset ordering and error propagation. Independently extract the preserved installer to resolve the current updater mismatch. Keep firmware microcontroller disassembly as a separate track.
