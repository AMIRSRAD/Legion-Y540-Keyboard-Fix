# Research roadmap and completion status

| Milestone | Status | Evidence / remaining work |
| --- | --- | --- |
| Preserve samples | Complete | SHA-256 manifest verifies |
| Resolve installer/update mismatch | Complete at payload boundary | Independent innoextract output matches all three supplied extracted files; XML external entry differs |
| Identify updater / firmware / driver roles | Complete for replacement build | Userspace updater reconstructed using built-in Windows HID APIs; no custom driver required by new source |
| Recover initialization/defaults | Complete for consumed supplied-profile settings | DWARF/PE values and INI read fallback evidence |
| Recover HID transport and packet format | Complete statically for implemented commands | Feature ID/data byte offsets, C0/C1/C2/C3/C4/D0/D1/07, key handshake |
| Recover checksum | Complete for supplied profile | Native caller + offline C/Python tests |
| Recover normal update state flow | Complete statically for supported-profile implementation | First block last, full readback, retries and reset; deliberate differences documented |
| Build self-compilable updater EXE | Complete | Native source build.ps1 and CMake; source archive rebuilt independently without vendor EXE |
| Test implementation offline | Complete | Five CTest cases plus source-archive build/fixture verification |
| Establish physical equivalence / qualify live update | Outstanding | Requires target keyboard testing; boot second byte, reconnect handling and stricter response checks need physical evidence |
| Rebuild original vendor EXE byte-identically | Not claimed | Missing original proprietary source/toolchain/project/signing materials |
| Rebuild microcontroller firmware from source | Not completed / separate objective | 44.bin remains supplied binary; architecture and descriptor review only |

The requested Windows source-compilation milestone is finished. The current native implementation is explicitly a supported-profile reconstruction. Do not mark hardware qualification complete from emulator results. Broader ITE modes, TVSU installer orchestration, or keyboard-firmware internals require separate scope and evidence.
