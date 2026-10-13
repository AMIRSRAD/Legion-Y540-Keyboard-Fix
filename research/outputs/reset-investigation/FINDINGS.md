# Y540 reset investigation — 2026-10-13

## Outcome

There is a reproducible CPU-state bug in exp2's recovery code. Its timer hook selects register bank 2 and its software restart enters original startup without restoring bank 0. Original startup then repeatedly clears its own loop pointer and cannot finish. This establishes an exp2 defect, not the cause of the original keyboard failure or proof that the watchdog actually triggered during the owner's failed restart.

The supplied bootloader dump also reveals a better-grounded reset primitive than jumping into startup: the existing C4 command reaches a terminal register sequence consistent with an ITE hardware watchdog reset. Its precise scope on IT8176 remains unverified. No new firmware based on this primitive is being presented as a repair.

The owner says the affected laptop is still on exp2 or the installed image is uncertain. Therefore the immediate package returns to the previously tested exp1 baseline. Power-policy comparison should happen only after that baseline is confirmed, not while mixing firmware changes with power-policy changes.

## Sources and boundaries

- Repository snapshot: https://github.com/AMIRSRAD/Y540-Keyboard at commit `5f8ac56fcdbb2763222ba038bc6ecbe88c008dd9`.
- Supplied upper-flash dump: `flash-dump-D800-20261013T084901150Z-p3460-3.bin`, 10,240 bytes, SHA-256 `6160ed916d5356c631a5e7939a55d3dae0b863199e0f33ba7e6680fe6f684d2a`.
- Original stock 44: SHA-256 `3afec131c6ed70efa0a3f4b601cb799011a582835d371c57fef68af48519e359`.
- Exact exp1 and exp2 bytes were taken from the owner's existing fix8 ZIP and checked against the handover hashes. No new firmware patch is shipped.
- Raw CODE address equals file offset is an analysis assumption. The 64 KiB combined analysis image contains stock app bytes plus the supplied upper dump. It is an offline analysis carrier, not a firmware release or a claim that both regions were captured together.
- Direct Ghidra export contains 2,135 boot-region instructions and 48 functions. Every exported instruction's bytes match the combined carrier. Automatic analysis misses the inline switch table; C4 dispatch was separately parsed and byte-verified. These are direct Ghidra results, not REA raw-firmware analysis. REA's Windows provider supports native PE; no raw-firmware provider result is claimed.
- No local flash, device reset, BIOS update or real power-policy change was performed. Power-policy tests use a fake native provider.

## Confirmed exp2 defect

The timer hook begins with `MOV PSW,#10h`, selecting bank 2. Its restart tail resets SP and uses RETI to enter CODE 0100 without restoring PSW.

Startup executes `MOV R0,#FF; CLR A; MOV @R0,A; DJNZ R0,...`. In bank 0, R0 lives at IRAM 00, outside the addresses being cleared. In bank 2, R0 lives at IRAM 10. When the clear reaches 10, it clears R0 itself. DJNZ wraps it to FF, restarting the clearing cycle. RETI does not restore PSW.

The extended offline interpreter actually runs these original startup instructions after the restart. Legacy exp2 remains in the loop after 2,000 instructions; the corrected source enters bank 0 and reaches the XRAM-clear entry in 512 instructions. The old test halted immediately at RETI, so it could not detect this defect.

Additional source findings:

- Main heartbeat clears a shared two-byte counter without excluding the timer. An interrupt between the two writes can leave 0100 rather than zero.
- Enumeration arming publishes the armed flag before resetting its old count. An interrupt can evaluate stale timeout state.
- The hook uses bank-2 R2 without saving it. Another ISR also uses bank 2; actual corruption depends on interrupt nesting and is not established.
- No SET_ADDRESS within a timeout can be legitimate when the host is shutting down. The trigger is not a proven fault detector.
- CODE 07C4 drains event queues in a loop. Missing the outer-loop heartbeat does not, by itself, prove the MCU has locked up.
- No direct MOV-DPTR reference to 0FF8..0FFC appeared in the existing 11,703-instruction app export. Indirect access and incomplete coverage prevent proving those bytes are free.

`source-review/build_exp2_review.py` corrects the bank selection, atomic updates and scratch-register preservation for review. Its command-line entry deliberately writes no firmware image. `test_review.py` builds only in memory and extends the original test model. The undocumented detach operation, software restart semantics, trigger correctness and scratch-RAM ownership remain unresolved. Do not treat this source review as a deployable fix.

## What C4 actually does

The independently checked path is:

1. EE09 reads the command byte, calls the inline switch helper F35A.
2. Switch record EE22 is `EE 54 C4`, selecting EE54 for C4.
3. EE54 writes XDATA[0F0F]=33 and returns.
4. SET_REPORT processing at E235 checks the flag after dispatch/status handling and calls F455.
5. F455 calls busy delay F12C with argument 5, writes XDATA[2F50]=08, calls that delay with argument 1000, sets XDATA[1058] bit 6, masks SFR[8E] with 3F, writes SFR[D8]=02, then waits forever.

F12C repeatedly writes XDATA[200B]. Delay arguments are verified; their time units are not. No instruction jumps into app startup in the terminal reset sequence.

F896 is a separate helper: it tests XDATA[1F01], conditionally writes 1F07=5C or 1F06=FF, and returns. Its observed caller EF84 is in the USB reset-wait loop. It is not the C4 terminal routine.

ITE's manufacturer-authored IT8511E/TE/G V0.4.1 documentation, available through a [PDF mirror](https://www.fixgen.kz/_ld/8/877_f328fb766207e40.pdf), describes SFR 8E bits 7:6 as watchdog timing and SFR D8 bit 1 as watchdog enable. That supports a family analogy for F455's terminal sequence. It is a different chip: it does not establish IT8176 reset scope, USB reset behavior, timing or the meaning of 1058 bit 6. Exact-chip searches did not yield a usable register manual. This is a bounded documentation gap, not proof that none exists.

## Return-to-exp1 package

The return build derives from the current repository updater. Its hardware command flow retains fast bootloader contact, chip checks, port binding, durable backup and full readback verification. Changes are limited to:

- Default target is the exact existing exp1 image, checksum 5642. Exp2 is not included as a selectable image in the portable package.
- The known-backup hash list additionally recognizes exact exp2 bytes. This permits one complete hash-verified backup read, avoiding the extra read exposure that previously stalled. Unknown contents still require two identical full reads. Recognizing exp2 for backup is not approval of its firmware.
- GUI, log labels and backup explanation identify this purpose correctly.
- A protocol regression test confirms that returning from exact exp2 uses one complete durable backup read plus final target verification.

All seven offline build checks passed. The exp1 payload also passes the compiled app's checksum verification. No affected-laptop result exists for this return build yet. A successful write restores the tested baseline; it does not establish a permanent repair.

## Next decision

First confirm exp1 is installed and typing works. Then, if the suspend-disabled restart test has not already been done, use the supplied reversible comparison script. Keep firmware, AC condition and test sequence fixed. Record each normal restart and shutdown outcome. The script records metadata and changes one power-plan setting only when explicitly run with Disable; it never restarts a device or flashes firmware.

Disabling selective suspend is a diagnostic comparison, not a proven long-term fix. System shutdown can still cause USB power transitions. If the comparison does not change the fault, the next firmware design needs a justified failure detector and evidence that the existing reset sequence recovers the relevant retained state. If software cannot provide that evidence, measuring supply/reset during a working and failed start remains the discriminating hardware test.

References: [Microsoft USB selective suspend](https://learn.microsoft.com/en-us/windows-hardware/drivers/usbcon/usb-selective-suspend), [Arm/Keil software reset limitations](https://www.keil.com/support/docs/307.htm). No guessed EC or board-pin operation is proposed.
