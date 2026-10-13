# Lenovo Y540 keyboard case — complete findings and final software candidate

Updated 2026-10-13, owner timezone Asia/Tehran. Source timestamps below are retained as logged UTC; laptop clock accuracy is not independently established.

## Outcome so far

The startup fault is unresolved. The reconstructed updater has completed one stock firmware44 write with full matching readback, but that write did not fix ordinary restart/shutdown behavior. Two attempts to install a modified no-sleep image stopped before any erase/write. The modified image has therefore not yet been tested on hardware.

Fix4 is the owner's requested final software attempt. It changes bootloader HID handle access, retains all qualification/backup requirements, selects the existing experimental no-sleep image by default, and adds recording around the attempt. It is an experimental candidate, not a confirmed repair. If it fails, this record should support later professional diagnosis without repeating the same flashes or inventing further patches.

## Scope and provenance

- Affected machine: owner reports Legion Y540-15IRH, machine type81SX, BIOSBHCN35WW. Supplied Windows inventories report Windows11 build26200. The analysis/development computer is a different machine.
- Initial case repository: `C:\Users\owner\Desktop\KeyboardFirmware-Issue`.
- Original keyboard package: Lenovo `ite1fw11s.exe`; payload44.bin is55296bytes (0xD800).
- Original image SHA256: `3afec131c6ed70efa0a3f4b601cb799011a582835d371c57fef68af48519e359`.
- The updater is an independent C reconstruction based on disassembly; it is not recovered Lenovo source. It can be compiled locally. A buildable C source reconstruction of the MCU firmware has not been achieved.
- Baseline research, fix1, fix2, fix3, original fixtures, earlier archives and backups are preserved separately. Experiments modify copies only.
- Firmware analysis used saved direct-Ghidra8051 evidence after REA's raw-image route rejected the format. No successful REA raw-firmware Evidence ID or MCU execution is claimed. Decoded instruction bytes were checked against the input, with stated coverage limits. Chip-specific MMIO and banking remain incompletely documented.

## Owner observations and corrections

Latest observations supersede the earlier AC-only explanation:

1. Holding the power button about10seconds until fully off, then powering on, restores ordinary keyboard input in the boot menu and can restore working Windows input.
2. Ordinary Windows Restart and ordinary Windows Shut down followed by power-on fail, on both AC and battery. Fast Startup is already off.
3. After ordinary Windows shutdown, the keyboard can already fail in F12 boot manager, before the next OS loads. After forced-off recovery it works in the boot manager.
4. In a Mint live boot explicitly started after forced-off recovery, the keyboard worked in BIOS and Mint's boot selector, then failed in the live desktop.
5. Earlier working-state tests showed connecting AC after typing was working did not stop it working. Fn functions remain available in owner-reported failed states. These reports do not identify which controller implements each function.
6. The owner initially clarified that no original Lenovo firmware installation was remembered as successful; those historical attempts produced errors. An older case note claiming successful erase/write/compare was therefore treated as unconfirmed. Later, our supplied fix2 stock update has a complete successful log, which is separate evidence and does not reconstruct the historical attempts.
7. Original failed Lenovo updater logs are unavailable. Do not ask the owner to recreate them by rerunning the original utility.

The term “bricked” describes severe loss of usable keyboard input. Forced-off recovery is observed, so permanent physical destruction is not established. This does not diminish the fault or prove a software-only cause.

## Windows evidence

Working inventories show USB048D:C100 revision0044 on internalport9, with five healthy HID collections. Failed inventories show the same location occupied by USB0000:0002 / USB_DEVICE_DESCRIPTOR_FAILURE / problem43; cached normal/HID records are absent/nonpresent. Physical path includes `PCIROOT(0)#PCI(1400)#USBROOT(0)#USB(9)` and ACPIHS09.

Failed USB recording13:50:23 session:3201events,18buffers, no reported events/buffers lost. Four standard GET_DESCRIPTOR(Device) transactions requesting64bytes complete with USB transaction error0xC0000011 and0received bytes. Hub retries end in enumeration failure on Intel controller8086:A36D at00:14.0, port9. Cached048D:C100/revision44 data in a failure event is not a fresh descriptor read.

Matching fix1 logs show the targeted unknown-device retry was accepted and a fresh enumeration began approximately11ms later, but the same failure returned. Owner reports only Diagnose and USB retry were performed in that recording. No firmware writes occurred in these diagnostics.

Working recording14:12:55 session:653events,4buffers, no reported loss. Four successful33-byte keyboard-related interrupt completions occur on the healthy port9 device. Packet contents were not captured, so key/report identity is not inferred. Working-state USB retry was refused with CONFIGRET40 /0x28 CR_NOT_DISABLEABLE, not access denied. Keyboard kept typing; no completed disable/enable cycle occurred in that working test.

An incidental camera onport6 reconnects/resets near some failed sequences. Cause and relationship are unknown; do not infer an operator action or a failed host controller from temporal proximity.

The Reddit i8042 suggestion was examined. i8042prt Start=3 and RUNNING were measured in both Windows states; the owner's startup-setting test did not fix the fault. Restoration of that setting to3 was advised, but completion was not independently confirmed. A PS/2 service being RUNNING does not establish successful internal USB keyboard enumeration.

## Mint evidence

Kernel6.14.0-37-generic enumerates Intel controller00:14.0 as bus1. Device1-9 fails16descriptor reads with error-71, eight address-acceptance attempts, and four complete enumeration sequences. Linux logs four attempted port power cycles without recovery. The keyboard048D:C100 is absent from the supplied lsusb inventory and USB tree.

Camera, Bluetooth, live USB storage and external3554:FA09 receiver enumerate. The external receiver is not the internal keyboard. i8042 registration also appears but does not prove working input through that interface.

This demonstrates a failure before normal HID operation in an independent OS. A Windows-only keyboard driver explanation is insufficient. Linux errorEPROTO and Windows transaction errors do not uniquely identify firmware corruption, power instability, wiring, controller state, or a host/device interaction. A logged logical port-power-cycle attempt is not proof that the physical keyboard supply was removed.

## Updater and firmware experiment history

| Stage | Observed result | What it establishes |
|---|---|---|
| Baseline research updater | Source reconstructed and compiled offline | Host-side reconstruction, not validated MCU source |
| fix1 update-ones | Normal collection17bytes rejected by unconditional64-byte requirement; empty backup | Confirmed reconstruction defect; stopped before feature I/O |
| fix2 stock update | Normal17-byte handshake; boot64-byte interface; chip response8176; two matching backup reads; erase/program/readback/reset accepted | One complete stock update sequence succeeded |
| Owner after fix2 | Typing remained working immediately; ordinary restart/shutdown still failed | Reinstalling stock44 did not repair startup behavior |
| No-sleep experiment1 via fix2 | Normal handshake/handoff succeeded; first boot chip query failed10times, error31; empty backup | Modified firmware not installed; no erase/write |
| Same experiment via fix3 | Boot metadata opens; all12rounds/120chip-query transmissions fail31, including reopen attempts | Longer qualification/reopening did not recover this session; no erase/write |
| Owner after first failed experiment | Forced-off recovery restored input | Recovery remained available after that failed handoff |
| fix4 | Offline build/tests only at report publication | Final candidate; hardware result pending |

The first copy of fix3's update log was0bytes; a later completed copy was100441bytes. Both received snapshots are retained. Conclusions about the stopped update use the completed copy, not the empty one.

### The strongest flash-content result

The saved pre-erase backup from the successful fix2 attempt is byte-identical to the original44 image. Independently reconstructed D1responses from each of two pre-erase reads and the post-program read all match that same55296-byte image and SHA256. Thus missing/corrupt bytes in addresses0000..D7FF at that time are not supported. This does not establish integrity outside that range, historical update success, or freedom from a logic bug in firmware44.

Revision0044 alone never established flash integrity. The complete matching readbacks do establish integrity of the measured region at that test.

### Safeguards retained

Normal/boot VID, PID, usage, report size and physical topology are validated. Normal report5A uses17bytes, boot report0 uses64. Chip qualification remains mandatory for the known8171/8176 family. Two complete matching reads must be saved/flushed before erase. A global device-operation mutex is shared across builds. Failed final verification does not trigger an extra erase/unverified reset. Normal custom-command cleanup uses report5A on the same normal interface only. No hub/controller restart or guessed EC write is used.

## Static firmware audit

Normal device/configuration/HID descriptors are structurally consistent. The standard device-descriptor path clamps response length to the descriptor size and host request. No malformed standard descriptor explains the observed zero-byte transactions.

A vendor OS-properties handler has a concrete response-length candidate: the76-byte property object can be sent using unchecked hostwLength, potentially reading beyond that object. It is a separate request path from the failed standard device-descriptor requests. No causal connection to this laptop's failure is established; it was not patched as a claimed repair.

The firmware advertises SelectiveSuspendEnabled=1 in an OS property. This is a supported power-management feature, not itself proof of a bug or of the Windows policy actually applied. Linux failure also limits a Windows-only selective-suspend explanation.

Reset-handling code exists at35DD/39DA and clears address/endpoint/protocol state. A claim that firmware simply omits address reset is contradicted. A sleep-state guard can defer normal reset polling, but scheduled cleanup and an alternate wake path exist. No permanent stuck-latch defect was proven. GET_CONFIGURATION's context value appears omitted by the examined reset cleanup, but complete indirect-write coverage and runtime relevance remain unresolved; it does not gate the initial descriptor path in the examined code.

Deep-sleep entry through4BC4->813C prepares peripherals and timer state, then normally reaches264B. Wake code restores state and schedules cleanup without requiring key input. Exact ITE register behavior and execution during failure are unknown. CODEE000/FE00 targets are outside the supplied image; they are missing evidence, not proof of invalid vendor code. The checksum gate's alternate interval depends on an undocumented hardware value and was not bypassed.

## Experimental firmware1

The final existing sleep gate at4C79 changes `60 66` (JZ4CE1) to `80 66` (SJMP4CE1), always taking the function's existing RET before sleep flags/peripheral preparation. Checksum7FFF changes22->42; stored checksum5622->5642. Total difference: two bytes. No USB reset-handler rewrite or guessed MMIO change is included. Main idle and other possible low-power mechanisms remain.

Patched image SHA256: `2b34b6d59db8443831a7e0387ae65970307f516e816dd481f1ba513d3f9de773`.

Direct-Ghidra disassembly confirms the branch/RET; an exhaustive local256-accumulator branch check passes; checksum validation and the host updater/flash emulator pass. These do not execute the MCU or validate sleep/power behavior. The image may increase power use, change suspend/wake, or prevent enumeration. Stock is included, but rollback requires an accessible update interface and cannot be guaranteed.

## BIOS and board investigation

Supplied BHCN35WW/36WW/45WW packages have valid Lenovo signatures on the analysis host. Each yields38checksum-valid ACPI tables.35vs36 has37identical tables includingDSDT; onlyNvdPegTb differs.36vs45 has37identical tables; DSDT changes are inBAT0battery code. No change toHS09 or main_PTS/_WAK methods was found in that diff. Package templates are not live tables; native BIOS/SMM behavior was not exhaustively compared. No verified standalone main-EC payload was identified. No BIOS flash is established as a repair.

Reference boardNM-C221REV0.1: direct TVW pin-handle parsing identifies U22 IT8176 and U23 SY6288D20AAC. U23 output supplies+3VALW_AG; enableAGKB_PWR_EN# connects through0-ohmRE102 toPCH_PWR_EN and mainEC UE1.126, also other circuitry. U22resetAG_WRST# connects to10K R376,1U C276 andD44 tied to its supply. The first coordinate-based parser had incorrect pin mappings and was rejected; the accepted direct mapping agrees with all five switch pins in the manufacturer's datasheet. Actual laptop revision and electrical behavior remain unmeasured.

This topology supports a concrete power/reset investigation. It does not prove a bad part or makePCH_PWR_EN a safe keyboard-only software control. No guessed EC register, pin short, capacitor replacement, BIOS override or unsupported bootloader command is proposed.

## Final fix4 hypothesis and stop conditions

fix4's only new communication hypothesis is opening the validated boot vendor collection with GENERIC_READ|GENERIC_WRITE rather than access0. Normal keyboard and metadata opens retain access0. Microsoft's HID sample usesRW, but that does not prove it solves this device's error31; access0 demonstrably succeeded once. There is no silent fallback or bypass ifRW is denied. The12round qualification cap remains; it is a round cap, not a guaranteed wall-clock deadline.

The final launcher validates package hashes, starts a bounded128MBUSBETW recording, and opens the GUI. It never automatically clicks Update. It stops tracing after five minutes if necessary while leaving the updater running. Logs are packaged after the updater exits, reducing the risk of another incomplete copied log. Trace setup failure prevents launch through this wrapper. Trace orchestration is tested offline; no live trace or hardware flash occurred here.

If chip validation or backups fail, stop without erase. If final readback fails, stop without further blind retries. If programming succeeds, only subsequent ordinary restart/shutdown tests determine whether the symptom improved. If the final attempt fails, preserve the logs/trace and proceed to qualified supply/reset/USB measurements, not another speculative software build. Honor the owner's request for this to be the last software attempt.

## Evidence index in the shared outputs folder

| Folder | Retained evidence |
|---|---|
| y540-research | Baseline source, vendor samples, original REA updater evidence |
| fix1, fix2, fix3, fix4 | Separate source/build/test records |
| runtime-test-analysis | Working/failed inventory comparison |
| usb-trace-analysis | Failed/working ETW decoding and log correlation |
| linux-analysis | Mint source logs, hashes and enumeration findings |
| update-attempt-analysis | fix1 report-size failure and raw inputs |
| fix2-attempt-analysis | Successful stock update, backup/read reconstruction, owner symptom follow-up |
| firmware44-analysis | Descriptor/code/initializer audit, raw direct-Ghidra exports, chip-doc limits |
| firmware-reset-analysis | Reset/power-path assembly, byte checks, bounded models |
| platform-reset-analysis | BIOS comparison, accepted board mapping, rejected-map correction |
| firmware-nosleep-exp1 | Patch builder/manifests/receipts, failed attempts and complete input snapshots |

Primary documentation consulted: [Microsoft HID feature API](https://learn.microsoft.com/en-us/windows-hardware/drivers/ddi/hidsdi/nf-hidsdi-hidd_setfeature), [Microsoft HID sample](https://github.com/microsoft/Windows-driver-samples/blob/main/hid/vhidmini2/app/testvhid.c), [Linux USB error documentation](https://www.kernel.org/doc/html/v6.2/driver-api/usb/error-codes.html), [Keil8051 opcode table](https://www.keil.com/support/man/docs/is51/is51_opcodes.asp?bhcp=1), [Silergy switch datasheet](https://www.silergy.com/zh/download/downloadFile?ftype=note&id=4371&type=product). They support API/instruction/component interpretation; none establishes this laptop's root cause.
