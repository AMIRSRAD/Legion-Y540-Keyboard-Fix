# USB control-response code review

Read-only static review of firmware 44, SHA-256 `3afec131c6ed70efa0a3f4b601cb799011a582835d371c57fef68af48519e359`. Evidence is the existing standalone Ghidra export, plus direct comparison of selected instruction byte strings to the original image: zero mismatches; the exact count is recorded in `evidence.json`. `assembly.txt` and `evidence.json` preserve these anchors. The assumed architecture is 8051 and raw file offset equals CODE address. Hardware mapping, banking, and actual execution are not established. No hardware was touched and no firmware was changed.

## Concrete candidate: vendor descriptor response uses unchecked host length

The assembly supports a real length-handling defect candidate, rather than only a decompiler expression error. The vendor handler at CODE:493D recognizes bmRequestType C1, bRequest 7F and wIndex 0005. CODE:49B8..49C5 constructs generic pointer (space 1, address 0A1F), and CODE:49C6..49D2 initially selects the length byte at XRAM:0A1F. The table is the 76-byte OS extended properties descriptor identified independently in the descriptor review. The separate initializer decoder replay maps file 53CA, length 76, to XDATA 0A1F (`../initializer.json`); this is a modeled initialization state, not a live RAM dump.

However, CODE:49E3..49FA unconditionally replaces the selected response length with the host's setup wLength, read from setup bytes 7 and 6 at CODE:496B..497E. No comparison against the table length occurs. CODE:49FB..4A04 changes a zero length to one. CODE:4A20..4A23 then invokes the sender with this pointer and length.

The dispatcher has an explicit static path: CODE:4AAD..4AB4 handles standard requests, CODE:4AC9..4AD2 handles class requests, and CODE:4AE7..4AF0 sends vendor-type requests to CODE:493D. This is a code path, not evidence of an observed vendor request.

## Downstream sender does not repair the bound

CODE:3CF0 loads the source generic pointer; CODE:3CF9 loads the two-byte count. CODE:3D0A..3D38 saves the source and count to a transfer context. CODE:3DF4..3DFA reloads that source and calls CODE:3BB9.

CODE:3BDA..3BF0 chooses **min(remaining length, 64)**. This is a packet-size limit, not a descriptor-object-size bound. CODE:3BFB..3C10 copies that many bytes from the source to XRAM:0C3F through CODE:5600. CODE:5643 reads source XRAM and CODE:565C writes destination XRAM; its loop only checks the supplied count. There is no second descriptor length bound in this copy routine.

The continuation path is also present: CODE:4F11..4F32 reloads source and remaining count, CODE:4F34..4F42 clears the initial flag and calls the shared sender at CODE:3D04. That path subtracts the previous packet size at CODE:3D77..3D9D and advances the source at CODE:3DAB..3DB9 before another min(remaining,64) packet. Thus the 64-byte packet clamp does not prevent a multi-packet read past the descriptor.

An offline arithmetic model is in `model.py` / `model.json`. Assuming the host fetches all staged packets and hardware callbacks succeed:

| Host wLength | Staged count | Packet sizes | Bytes read beyond 76-byte descriptor |
|---:|---:|---|---:|
| 0 | 1 | 1 | 0 |
| 76 | 76 | 64,12 | 0 |
| 77 | 77 | 64,13 | 1 |
| 255 | 255 | 64,64,64,63 | 179 |

For 77 bytes the extra read is XRAM:0A6B; for 255 bytes the modeled read reaches XRAM:0B1D. This means adjacent runtime RAM can be included in the staged response; its actual contents and actual bus transmission have not been measured. For wLength=0, a byte is staged internally but a compliant host need not issue an IN data transaction, so this is not proof a byte is transmitted. There is no buffer-write overflow established here: packets remain at most 64 bytes.

## Relevance to the owner's failure

This is a vendor extended-properties request, not the standard GET_DESCRIPTOR(Device) request that failed in the owner's trace. The observed failed requests were 80/06/0100 with wLength=64 and returned zero bytes. The vendor handler cannot directly explain those failures. Earlier successful vendor requests could hypothetically affect retained state, but no such sequence, RAM effect, or causal chain is demonstrated.

The generic sender has a distinct continuation entry at CODE:3D04. Ghidra's pseudocode marks continuation blocks unreachable when decompiling the initialization entry CODE:3CF0; the external caller CODE:4F42 proves that global conclusion would be wrong. The P0/P1 writes shown in the invalid-request branch of CODE:493D are also not trusted: CODE:8850 consumes four inline constant bytes and resumes after them. The reported overlap near CODE:49E3 is a compiler-inline-data artifact, whereas the valid-request branch directly jumps to the unambiguous CODE:49E3 instruction stream.

Status: high confidence in unchecked response-count assignment and packet-only downstream limit under the stated 8051 mapping; candidate protocol/RAM-read flaw. Not dynamically reproduced, not a proven startup-fault cause, and not a basis for a flashable patch.
