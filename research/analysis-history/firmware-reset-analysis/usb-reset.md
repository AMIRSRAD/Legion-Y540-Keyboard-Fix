# Firmware 44 USB reset and endpoint-zero audit

2026-10-12. Static analysis only; no image was patched or hardware operated.

## Result

The image contains an explicit reset path that clears the device-address register candidate and resets endpoint state. A blanket claim that firmware 44 simply forgets to reset its USB address is contradicted by the instructions. Two narrower state-management candidates deserve further investigation, but neither is a demonstrated explanation for the owner's zero-byte descriptor failures.

Evidence: existing direct Ghidra 8051 export `../firmware44-analysis/ghidra-static-inline-aware.json`, checked against `../fix2/samples/44.bin`, SHA-256 `3afec131c6ed70efa0a3f4b601cb799011a582835d371c57feF68af48519e359` (case immaterial). Selected 991 instructions have zero byte mismatches; see `usb-reset-evidence/verification.json`, `instructions.json`, and `assembly.txt`. This is reused direct Ghidra evidence, not a successful REA raw-image session. Generic pseudocode incorrectly treats some R7-return helpers as void; conclusions below use assembly.

## Reset initialization is present

Cold USB initialization at CODE 50E3..50F3 establishes a generic XDATA pointer in 0DE8..0DEA, bytes `01 0D D5`, referring to context 0DD5. It calls cleanup 4B29 then hardware initialization 4B88. The library at 85B9 writes through that generic pointer plus DPTR offset.

In the normal service routine, CODE 4DCC..4DD3 tests XDATA 2F52 bit 2 and jumps to 35DD when set. CODE 35DD..35EC checks the same bit, calls 39DA, then writes 04 to 2F52. This is a strong bus-reset-handler candidate based on its effects, but register names and write-one-to-clear semantics still need an applicable chip document.

CODE 39DA..3A23 checks context offset 3 (XDATA 0DD8); if zero it:

- Calls 4B29 to clear context fields 3, 2, 4, 2, 1, 5, word 0F, 11, and optionally 12.
- Writes 1 to hardware locations 2F64, 2F74, 2F84, and through helper 34DF to 2F94.
- Helper 34DF explicitly writes zero to 2F54, writes 1 to 2F40 through 32D3, writes 21 to 2F44, and clears 0DD4.
- Writes 18 to 2F52, then sets context offset 3 to 1.

2F54 is a strong device-address-register candidate because the SET_ADDRESS handler 4034 stores the pending value in context offset 0, and completion paths 4EF3..4F00 and 505x write that value to 2F54. Its clearing on reset is therefore meaningful evidence. The reset-once latch at context +3 is cleared on the non-reset normal-service path 4DE1..4DE5. Without hardware timing/bit semantics this latch is not itself a demonstrated defect.

## Candidate A: normal reset polling is bypassed in the suspended-state branch

CODE 36EB..36FB returns R7=1 if both XDATA 0DD2 and 0DD3 are nonzero; otherwise it returns R7=0. This is obscured in the pseudocode.

CODE 4DBA..4DD3 calls that helper. If R7 is nonzero, it tests 0DD1 and either returns or enters 4CE2. It does **not** inspect 2F52 bit 2 through the normal reset branch in that case. Thus a hypothetical state with 0DD2=1, 0DD3=1, 0DD1=0 can bypass reset handling on that service invocation even if the event bit is pending.

However, CODE 4F75 has an alternative path: after calling 36EB it separately checks 2F52 bit 2, writes 1 to 2F53, and calls 35DD. Its known caller is 1FA2, guarded by 08AD in 1F93. The cold/wake event dispatcher and interrupt enable semantics must therefore be resolved before claiming that a reset is actually missed. Moving the reset check earlier could conflict with clock/power prerequisites in the suspended state. No such patch is justified yet.

The parent's independent caller audit supplies additional contrary evidence: after the 4BC4 sleep routine returns, wrapper 26E2 calls 6D0D at 26FF, then 36EB at 2702; if active, 2708 sets R7=2 and 270A calls 510D, which can set 0DD1=1 and queue an event. Therefore the bypass state may be transient and intentionally followed by a scheduled transition. Calling it a stable trap requires proof that this transition or the alternate wake event is lost.

`usb-reset-evidence/gate_model.py` models eight Boolean combinations of 0DD2/0DD3/0DD1 with the reset event pending. Five assertions passed, including normal-path bypass and alternate-path handling. This verifies the written branch interpretation only, not physical reachability or timing. If 1F93 is actually delivered with 08AD nonzero, 4F75 clears 0DD3/08AD when 36EB reports active and services the reset candidate. The model explicitly excludes scheduler and hardware semantics.

## Candidate B: reported configuration value survives this cleanup

The raw standard-request jump table at 4647 maps bRequest 8 to 46E5, which calls 4256; it maps bRequest 9 to 46FD, which calls 4283. These are GET_CONFIGURATION and SET_CONFIGURATION by their standard request numbers and one-byte/zero-length behavior.

CODE 4256..426A reads context offset 0E (XDATA 0DE3) and stages it as the one-byte GET_CONFIGURATION reply. CODE 4283..42A3 reads wValue and writes its low byte to context offset 0E. Cleanup 4B29 does not clear that field. Its terminal helper 2D36 sets 0973 and has no configuration-context write. Consequently the local cleanup can preserve a nonzero reported configuration across its reset sequence, unlike the cold RAM clearing.

This is a concrete stale-state candidate in the examined functions, with an important coverage limit: indirect writes elsewhere or hardware/lifecycle initialization outside this path could change the context. It needs a dynamic post-reset GET_CONFIGURATION observation or complete context-write proof before being classified as a confirmed device-level failure.

There is no established causal path from the stale +0E value to the failed initial GET_DESCRIPTOR transactions. GET_DESCRIPTOR at 468C..46AD gates on context +2, which cleanup does clear; descriptor selection and size clipping have previously been audited. Correcting a possible configuration reporting violation would not establish a startup repair.

## What would resolve these candidates

1. An applicable IT8176/IT8171 register map or equivalent vendor source to establish 2F52/2F53 event and mask semantics, power prerequisites, and address-register behavior.
2. Resolve dispatch into 1F93/4F75 across suspend/resume/reset: prove whether a pending reset can be stranded when 0DD3 remains set.
3. A controlled full-speed USB protocol capture across BIOS-to-OS handoff, showing whether reset signaling is followed by no device response, corrupted transactions, or valid request handling. The existing host logs do not reveal MCU flags or handler execution.
4. After normal enumeration is available, observe configuration reporting across an actual bus reset. Do not infer this from a Windows cached descriptor or VID/PID.

No executable firmware fix is established by this pass. Existing updater transport success and byte-perfect flash verification do not validate either speculative firmware change.
