# fix9 / exp3 recovery experiment

User-facing instructions: START-HERE.md. Previous images and builds were preserved.

## Why this revision exists

The owner's latest return recording proves exp2 was replaced by byte-exact exp1. Exp1 still failed the first ordinary restart with the active power plan's USB selective suspend already disabled. No further repeat of that policy comparison is required for this release.

Exp2's timer hook selected CPU register bank 2, then its recovery fabricated a return into startup without changing bank. Startup's memory-clearing loop clears its own bank-2 R0 pointer and cannot finish. The original emulator stopped at RETI and missed that defect.

The supplied upper-flash dump independently establishes C4 dispatch through EE54 and E235 into F455. F455 uses delays, 2F50=08, 1058|=40, 8E&=3F, D8=02 and a terminal wait. The owner’s return trace observes C4 followed by fresh normal-mode enumeration. Physical reset scope and recovery of the original failed condition remain unproven.

## Firmware changes

- Base is exact stock44 with exp1's no-sleep gate retained.
- Inserted code: 171 bytes at CODE 8A00..8AAA, all originally FF.
- Heartbeat hook at 07C4 replaces four bytes with a jump and padding, faithfully replaying MOV A,26h and its conditional branch. The heartbeat now runs inside the event-drain loop; long legitimate queued work no longer depends solely on returning to the outer loop.
- Bus-reset handler hook at 35E6 starts an enumeration recovery deadline only if not already armed. Repeated reset attempts do not continually postpone it.
- SET_CONFIGURATION handler entry at 4283 disarms the deadline. This includes configuration zero and occurs before handler completion; it is evidence of that host request, not proof the keyboard is operational. SET_ADDRESS is no longer hooked.
- Timer hook at 330A counts 8,000 main-heartbeat ticks or 6,000 enumeration ticks. Tick rate is not independently verified. Shared updates preserve IE and mask interrupts; timer scratch R2 is preserved and protected from nesting during the hook.
- Terminal recovery is `CLR EA; MOV PSW,#0; LJMP F455`. No guessed 2F40 detach, fabricated stack or RETI-to-startup remains.
- Checksum stored at 7FFE..7FFF is 0699. Payload remains exactly 54 KiB. The upper flash is not modified.

Firmware SHA-256: `e0a959a63dceada1f5fad6846451372271e266ec176cfd25bb322a69199b5457`.

## Updater changes

Derived from repository commit `5f8ac56fcdbb2763222ba038bc6ecbe88c008dd9`, plus the prior return-to-exp1 build.

- Defaults to exact exp3 and labels the package fix9/0.9.0.
- Only exact stock44, exp1 and exp3 are permitted flashing targets. Exp2 is recognized solely as possible backup content.
- When exp3 is selected, two fresh D1 reads compare F12C..F149 and F455..F477 on the bound controller against the supplied dump. This occurs before backup/erase. Any mismatch or transfer failure aborts without erase/write/reset.
- Exp1/stock return paths do not depend on those external-code comparisons.
- Keeps fast bootloader contact, mode-specific report sizes, physical-port binding, chip qualification, durable pre-erase backup, block bounds, full target readback and no final erase/reset on failed verification.
- Known exact stock/exp1/exp2/exp3 backups need one full hash-matching read. Unknown contents retain two independent matching reads.

## Verification

All seven updater checks pass: core, in-memory HID, protocol emulator, PnP fixtures, logger, compiled-app checksum verification and hidden GUI initialization. Additional protocol cases cover matching upper code, mismatch in either dependency, failed upper read, unchanged upper flash, exp1 rollback and rejection of exp2 before device I/O.

The firmware CPU model passes both complete recovery paths through the actual F455 and F12C bytes to the terminal wait, 1,260 interrupt-boundary cases, 16 threshold-edge cases and 256 scratch-register values. The model records MMIO operations; it does not simulate actual watchdog expiry, USB or electrical reset.

Direct Ghidra 8051 export of an analysis-only combined image contains 13,059 instructions and 316 functions, with zero instruction-byte mismatches. All 186 changed bytes are confined to the declared hooks, inserted code, exp1 branch and checksum. CODE=file-offset mapping remains an assumption. These are direct Ghidra results, not a REA raw-firmware provider result.

Independent read-only audits found no concrete instruction/stack or host-guard blocker. They retained the same hardware limitations described below. Receipts and original-model evidence are in verification/ and evidence/.

No hardware flash, device restart, BIOS change or real power-policy change was performed on the development computer.

## Reproduce

From this directory, with Python 3 and Windows MinGW GCC available:

```powershell
New-Item -ItemType Directory -Path work -Force
python firmware/build_exp3.py samples/44.bin samples/upper-flash-dump.bin work/rebuilt-exp3.bin
python firmware/test_exp3.py samples/44.bin samples/upper-flash-dump.bin
powershell -NoProfile -ExecutionPolicy Bypass -File build.ps1 -Compiler C:\path\to\gcc.exe
```

The generator refuses to overwrite an existing destination. Compare the rebuilt image with the recorded hash above. Supplied stock and upper-dump identities are checked before building. CMake files are included; the release was built and tested with build.ps1.

## Hardware limits and expected experiment

The deadline is a recovery policy, not a proven fault detector. A host may intentionally leave the device unconfigured, causing a reset. Repeated real host reset events may cause repeated recovery attempts. A clock/timer failure or USB-core wedge invisible to firmware can evade this mechanism. Counter RAM 0FF8..0FFC had no direct references in the bounded app export, but indirect accesses and ROM behavior prevent proving exclusive ownership. Reset scope, register meanings and timeout duration lack exact-chip documentation.

This release tests whether a properly formed request through the already-used reset primitive recovers the warm-start fault. It is not a claim of a permanent repair. On-device dependency checks qualify the observed code, not its hardware outcome. Rollback still needs an accessible update interface.
