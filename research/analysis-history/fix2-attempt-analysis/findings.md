# fix2 hardware attempt: successful programming and identical pre-update image

The supplied Desktop/logs files are preserved in evidence/. analyze.py reconstructs the three complete D1 read passes from logged successful transactions, checks contiguous addresses and response/request headers, and compares each with the saved backup and original 44.bin. Results and input hashes are in verification.json.

Observed sequence (log UTC timestamps):
- 12:51:23: boot interface 048D:89DB, FF89:00DB, feature size 64. Chip response bytes identify 8176.
- Two independent reads of 55,296 bytes, followed by saved/flushed backup at 12:52:26.759.
- One C2 erase command; 35 C3 block commits (other planned blocks are all FF and skipped); no failed feature transactions in the supplied log.
- Third complete read after programming exactly matches original image.
- 12:53:13.774: C4 reset command accepted. The log does not verify subsequent normal USB enumeration or actual typing.

All three reconstructed reads, the pre-erase backup, and original firmware 44 have SHA-256:
3afec131c6ed70efa0a3f4b601cb799011a582835d371c57fef68af48519e359

This establishes that the readable update region 0x0000–0xD7FF already matched firmware 44 before this attempt, and matched again after it. There is no evidence of missing/corrupted bytes within this region at the time of backup. It does not establish historical installation success, integrity of memory outside this region, or absence of a logic bug in firmware 44. It also does not prove that the keyboard startup fault is repaired.

The fix2 transport correction has now allowed one observed hardware update sequence to complete, including readback verification. Further updater changes or repeated flashing are not justified by a new failure in this log.

Next: owner reports whether typing works after the update, then tests one ordinary Windows Restart and one ordinary Windows Shut down followed by power-on, recording typing/boot-menu behavior for each. Save work first. If failure returns, use the known forced-power-off recovery after saving work through an external keyboard. Do not repeat the flash. These results distinguish successful programming from a successful symptom repair.

## Owner follow-up: startup fault persists

The owner confirms typing continued after the update, but both ordinary Windows Restart and ordinary shutdown/power-on still fail. Forced power-off still restores operation. The successful rewrite therefore did not repair the symptom. Consolidated interpretation and proposed repair direction: case-summary-and-repair-proposal.md.
