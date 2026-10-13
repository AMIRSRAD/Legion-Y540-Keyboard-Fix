# Lenovo keyboard firmware 44: static code audit

**One concrete USB response-length flaw candidate was found. It has not been demonstrated to cause this laptop's keyboard startup failure, and this audit does not produce a firmware repair.** The normal USB descriptors are structurally consistent. Firmware and existing updater sources/builds were preserved.

## Target and method

Original `44.bin`: 55,296 bytes (0xD800), SHA-256 `3afec131c6ed70efa0a3f4b601cb799011a582835d371c57fef68af48519e359`. This pass examined the MCU payload, not only ITESHFU.exe or the reconstructed updater.

REA's installed raw-target `open_binary` operation rejected the image with `target_unavailable / unsupported binary format`; the original result is preserved in `evidence/rea/001-open.json`. No successful REA firmware-decompilation Evidence ID is claimed. The owned REA session was closed, and analysis continued directly in installed Ghidra 12.1.4 using its 8051 processor. No fake executable header was added and no target code ran.

Reset-vector spacing and coherent startup instructions support a classic 8051-family interpretation. Raw file offset = CODE address at base zero is an analysis assumption; exact silicon, banking and hardware registers remain incompletely established. Ghidra exports preserve initial, expanded and inline-aware passes. The last pass recovers 11,703 instructions and 281 function entries. All 11,703 instruction byte strings were compared against the original image with zero mismatches. The 19,326 distinct bytes decoded as instructions are not an exhaustive coverage or correctness claim; computed jumps, absent code and hardware state constrain reachability.

Compiler helper CODE:8850 consumes four inline constant bytes and jumps to the caller's continuation. Its assembly was reviewed and 31 callsites modeled to improve disassembly. Generic decompiler warnings, apparent unreachable continuation blocks and overlapping instructions were checked against assembly rather than treated as firmware defects. The analysis database exists separately under the workspace work directory; input bytes are unchanged.

## Findings ledger

| Finding | Evidence and confidence | Relation to owner fault |
|---|---|---|
| Vendor descriptor count can exceed the descriptor object | High-confidence static assembly/model result under the 8051 mapping; runtime reproduction absent | No causal relation established |
| Firmware advertises HID selective-suspend opt-in | Exact embedded OS property plus request handler/table mapping | Specific power-management lead; normal supported feature, not itself a defect |
| Normal USB/HID structures are consistent | Exact bytes and bounded descriptor parser; report length agrees with live working transfers | No malformed-descriptor explanation found for zero-byte transaction failures |
| Reset entry clears internal/XDATA state and passes a checksum gate | Assembly and offline initializer/checksum calculations | Relevant reset-boundary lead; warm-reset device state unmeasured |
| Chip-specific USB/reset semantics and referenced external code remain missing | Board artifact strings, bounded vendor-document search, unmapped CODE targets | Prevents a validated startup patch or full audit |

## 1. Vendor Microsoft OS descriptor response-length flaw candidate

The handler at CODE:493D accepts bmRequestType C1, vendor bRequest 7F, wIndex 0005. A statically reachable vendor branch in the dispatcher calls it. The original image initializes a 76-byte Microsoft OS extended-properties descriptor into XDATA 0A1F. CODE:49B8..49D2 selects that source and its size, but CODE:49E3..49FA then **overwrites the size with the host's requested wLength**. A zero requested length is internally changed to one.

The shared sender and XDATA copier do not restore the object bound. They limit each packet to 64 bytes, not the total transfer to 76. The continuation callback advances the source pointer and stages further packets. The byte-verified chain and code anchors are in `usb-code/assembly.txt`, `usb-code/evidence.json`, and `usb-code/findings.md`.

| Host requested length | Modeled staged packets | Read beyond the 76-byte object |
|---:|---|---:|
| 76 | 64 + 12 | 0 |
| 77 | 64 + 13 | 1 byte |
| 255 | 64 + 64 + 64 + 63 | 179 bytes |
| 0 | 1 byte staged internally | None; a compliant host need not fetch a data packet |

This supports a candidate protocol/RAM-read flaw. It does **not** establish a write-buffer overflow, actual exposed RAM contents, an observed malformed host request, or transmission of all modeled packets. The arithmetic model is offline, not an emulator of USB hardware or the complete MCU.

Most importantly, the owner's failed trace contains standard `80 / 06 / wValue=0100 / wLength=64` device-descriptor requests. This vendor handler is a different path. The flaw does not directly explain those zero-byte transaction failures. An earlier vendor request affecting state would require an independently established causal sequence; none was captured.

A source-level correction would bound the response count by both descriptor size and wLength, and handle zero length without staging data. This is a review suggestion, **not a validated binary patch**. No patched image was produced for flashing.

## 2. Selective suspend: a real lead, not a proven bug

File 0x53CA..0x5415 contains a consistent Microsoft OS extended-properties structure declaring DWORD `SelectiveSuspendEnabled=1`. The OS string at 0x53B4 advertises vendor code 7F. Independent replay of the constant initializer maps that 76-byte property blob to XDATA 0A1F, matching the vendor handler's source pointer.

[Microsoft documents OS extended properties as a supported way to enable HID selective suspend](https://learn.microsoft.com/en-us/windows-hardware/drivers/hid/selective-suspend-for-hid-over-usb-devices). Therefore this supplies a specific interface between device firmware and Windows power management, rather than a random power-setting guess. Its presence does not establish that the affected Windows installation applied it, that a shutdown failure is selective-suspend related, or that disabling it repairs the issue. The field's runtime registry state and device behavior before shutdown have not been measured in this pass.

## 3. Normal descriptors and the standard device request

The 18-byte device descriptor at file 0x5307 declares 048D:C100, revision 0044, endpoint-zero packet size 64. The 34-byte configuration tree is internally consistent. Its HID descriptor's report length 161 exactly matches the primary HID report at 0x5184. Five top-level collections agree with the five live HID child devices in the working inventory.

The keyboard report-mode layout declares 32 payload bytes plus one report-ID byte, agreeing with four successful 33-byte transfers captured from the working device. Because ETW payloads were not recorded, this is a size agreement, not proof of the exact report ID or keys sent. Full item decoding and bounds are in `descriptors/evidence.json` and `descriptors/findings.md`.

The initializer maps the normal device descriptor to XDATA 0975. The standard GET_DESCRIPTOR dispatch leads through CODE:468C/405D to the device case CODE:40E8, which selects this pointer and its first-byte length (18). Assembly CODE:421E..4244 clamps that length to the host's requested length before calling the sender. Under this static model, a request for 64 bytes selects an 18-byte response. **The unchecked length in the vendor path is not reproduced in this standard path.**

No malformed device/configuration/HID structure or missing standard length clamp was found in this bounded review. Runtime endpoint-zero state, interrupt delivery, power/clock configuration and actual RAM correctness remain unverified. In the failed trace, no descriptor bytes arrive for a parser to reject.

## 4. Startup, initialization and missing execution context

Reset vector file 0000 jumps to 0100. Startup instructions clear internal RAM and XDATA 0000..0FFF; the application startup at 0400 performs another such clear before copying constants. The decoder in `tools/decode_initializer.py`, derived from CODE:0464..04A7, consumes 36 initialization records starting at 5154 and ending at terminator 55FF. It independently validates the OS property, HID report and normal device-descriptor RAM placements. Its XDATA binary is an **offline model**, not a device RAM dump.

The reset checksum gate reads XDATA1080 and tests mask05. A masked value05 selects the checksum interval [0400,D800); other masked values select [0400,8000). Replacing the stored checksum slots with FF yields 5622 for the longer interval, exactly matching stored bytes at7FFE/7FFF, versus3857 for the shorter interval. The branch to the latter interval is not itself a flaw: the register's hardware meaning and the affected device's live value are unknown. Do not assume a flash-size/chip-identity interpretation or claim this branch is taken during a failing Windows startup.

The checksum failure path calls CODE:E000; another path jumps to CODE:FE00. Neither lies in the supplied image ending atD7FF. They might belong to ROM, another mapped area, or a different execution context; this pass cannot decide. Treat decompiler “bad instruction” warnings at those addresses as missing evidence, not evidence that Lenovo shipped invalid instructions.

Low-power-looking paths write8051 SFR87 with01 at225B and02 at263F/2659/2672, with nearby XDATA1E03/2F52 accesses. Generic8051 PCON conventions make them useful investigation candidates, but exact behavior on the ITE derivative and their relation to the USB reset/suspend state machine remain unverified. No MMIO bits were patched or labeled as proven USB reset controls.

The reference NM-C221 REV0.1 boardview names IT8176FN-56A-BX and a separate IT8226 EC, plus USB pair9, reset-looking and keyboard-power net strings. Connectivity and the affected laptop's exact board revision are not established. No applicable public primary-source IT8176/8171 USB/register specification was obtained. See `chip-docs/findings.md`; register maps from unrelated ITE families were not substituted.

## Fit to the latest owner observations

Latest owner report supersedes a simple AC/battery explanation: holding the power button about ten seconds then powering on recovers typing, and typing stays functional in Windows. Windows Restart and Windows Shut down followed by power-on fail; Fast Startup is already off. This is consistent with different reset/state transitions, but does not prove Windows itself, firmware44, the EC, the host controller, or any particular power rail is responsible.

The two existing USB traces begin after boot and do not capture the transition into failure. The pending live Linux test is still useful for determining whether a software-controlled restart reproduces the problem outside Windows. No further random reset or flash is justified by the candidate vendor flaw alone.

## Scope completion and remaining work

- Artifact identity, descriptor structure, constant initializer and selected response-count paths: reviewed with retained byte evidence.
- Startup/checksum and low-power candidates: partially traced; hardware meanings and missing code unresolved.
- Complete USB reset/resume state machine, interrupt/callback coverage, timing/races and all firmware functions: not certified or exhaustively audited.
- Root cause and repair for previously affected keyboards: unresolved; no flashable fix claimed.

The original image hash and instruction provenance are rechecked by `tools/verify_static_evidence.py`; results are in `audit-facts.json`. Existing baseline and fix1 Git working trees remained clean after this audit. No device I/O, target execution, firmware write or firmware alteration occurred.
