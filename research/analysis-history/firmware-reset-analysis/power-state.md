# Firmware 44 startup and low-power path audit

The binary contains a specific, traceable low-power entry and return sequence. No instruction in that sequence has yet been established as faulty. Replacing firmware 44 with the same verified bytes cannot test this hypothesis.

## Evidence and limits

Reviewed original 55,296-byte image SHA-256 `3afec131c6ed70efa0a3f4b601cb799011a582835d371c57fef68af48519e359`, using the retained direct-Ghidra 8051 export. `tools/power-paths.py` independently compares 952 selected exported instructions against original bytes, with zero mismatches, and writes `power-state-assembly.txt` and `power-state-evidence.json`. CODE addresses assume raw base zero. No device was accessed or patched. REA's earlier raw-format rejection was not repeated. These are direct-Ghidra/static-byte findings, not REA execution evidence.

`firmware44-analysis/chip-docs/findings.md` remains an essential limit: exact ITE MMIO meanings are unavailable; the boardview strings do not establish electrical connectivity. In particular, addresses 1E03, 1E20, 1E40 and 2F52 below have not been assigned fabricated register names.

## Observed control flow

1. Cold/reset entry 0100 and application entry 0400 clear RAM and reach main at 2200. Main at 2209 calls 6000, which returns 33 only if XDATA0045 is 33; this selects a distinct startup branch. Ordinary branch calls 0EC1, 8000 and 05A7. Main idle at 225B writes SFR87=01 after checking internal bytes26/27. These are literal operations; whether a host warm restart resets this MCU is unknown.
2. A periodic path 26E2 calls 4BC4 at 26F7 only when XDATA00F4/00F5 are zero. 4BC4 requires XDATA0DD2 nonzero and 0DD3 zero. Activity/status at 2F52 and counters addressed through the generic pointer at0DE8 gate the next steps; static comparisons use thresholds8 and0x1388. The time units are unknown. Further vetoes inspect0891/0800,08AE/0902 and16E0 bits4/5.
3. Passing that gate writes XDATA0DD3=1 and08AD=1 (4C7B..4C84). It writes1B06 and111C with40 then80, ORs111D withC0, calls7FE5, and writes1E20=C0 before calling813C at4CB0.
4. 813C disables global8051 interrupts through059D and stops/clears timer0 through0CB9→0C42. The condition helper3185 inspects queue-like indices30/31, bit37, XDATA1D04, internal40 bit4 and XDATA0A84/0A85; its true return cannot be inferred from the misleading decompiled parameter alone. If needed, 0CBF/0E30 prepare an additional source. Calls810E/80E3 configure more peripheral bits; XDATA00D7 is cleared and global interrupts enabled at8161.
5. 8164..8169 writes XDATA00A1=1, immediately reads it and normally dispatches264B at8175. Alternative2633 and2665 branches exist, but are not chosen by the local ordinary value1. Generic decompiler "unreachable" remarks here are not a firmware defect.
6. 264B reads XDATA2F52 and masks0F. If nonzero it returns without the following write. If zero, it writes XDATA1E03=3, then SFR87=02 at2659, followed by eight NOPs and RET. Under generic8051 convention SFR87 is PCON and02 selects power-down; the ITE derivative's actual sleep/wake semantics remain unverified. Sibling helpers2633/2665 use1E03 values0/1 respectively.
7. The continuation8182 calls80FC/8121,0E63,0CBC (timer0 restart),2580, sets XDATA00CF=1, bit30, and00F4/00F5=012C. It then iterates pending key-like bitmaps. Returning to4CB3 writes1E20=80 and1E40=03 and reverses the111D wake-looking bits.
8. The entry latches0DD3 and08AD are not cleared in that immediate return sequence. They are cleared in the separate path4CE2 at4D24..4D2C. Crucially, this cleanup is scheduled without needing a key press: wrapper26E2 resumes after4BC4, calls6D0D, tests0DD2 through36EB and invokes510D withR7=2. 510D preserves a pending event, otherwise sets0DD0=2,0DD1=1,0DCF=1 and bit31 via2715. Main07C4 services bit31 through0950→4F66→4DBA→4CE2. Alternate4F75 also clears0DD3/08AD when0DD2 is nonzero. Thus a claim that the firmware simply forgot to clear these latches is contradicted by the code.
9. The cleanup4CE2 may defer at4CF2..4D14: context byte+12 must be nonzero and3185(2) must return something other than1 to proceed to4D24. Helper3185 returns0 when00D7 is nonzero in mode2 (31DB..31E7); otherwise it returns its composite queue/keyboard-activity condition inR6. This makes00D7 nonzero favor continuation rather than block it. Sleep entry clears00D7 at815C..8160. Exact runtime context byte and queue states are unmeasured, so this deferral is not established as a defect.

## What is and is not a candidate defect

The exact candidate is a mismatch between entry, wake and later bus-event cleanup: execution could enter the sequence above yet not regain a usable USB endpoint/clock state. The firmware explicitly schedules later cleanup; a missed-event theory would require evidence of interrupt/event failure despite that scheduling, and cannot rest on absence of cleanup code. Hardware reset/power behavior could produce the same observation without incorrect instructions. No observed trace shows the MCU program counter, register values, or latches during failure, so neither mechanism is confirmed.

There is a short interval between the2F52 condition test and the SFR87 write with global interrupts enabled. This is an ordinary place to audit wake-event races; it is not proof of a race because hardware can latch wake conditions and power-down semantics are undocumented. NOPing that write or forcing unrelated MMIO bits would be speculative and is not justified as a release fix.

The checksum gate at0136 depends on XDATA1080 &05 and can branch to missing CODEE000 on failure. The full-image original-byte match does not establish the live MMIO value or execution branch. However, no evidence currently connects this gate to ordinary restart, and it should not be patched just because one theoretical checksum interval differs.

## Evidence that would distinguish the hypotheses

- A full transition USB capture from the working keyboard through the first failure could distinguish failure immediately after bus reset/address handling from entry after a sustained suspend/idle period. Existing failed-state retries begin too late to establish that order.
- A documented silicon debug/read mechanism could record0DD0..0DD3,08AD,2F52 and the current execution location during failure. Existing HID commands are unavailable after enumeration fails, and undocumented MMIO probes are not a substitute.
- With verified board connectivity, simultaneous keyboard supply, reset, and USB D+/D− measurements during ordinary restart versus forced-off recovery distinguish retained power/reset behavior from a controller that resets and then stops responding. An OS log saying "power cycle" does not prove the internal keyboard rail was physically removed.
- A Linux boot test with USB autosuspend disabled can narrow OS policy involvement, but a negative result does not exclude device autonomous low-power entry. It must not be described as disabling all firmware sleep paths.

This pass identifies precise firmware paths for further work; it does not certify a flashable repair or establish that a driver/updater can repair a device which no longer enumerates.

