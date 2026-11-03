# Test status

**Current state (3 Nov):** a full decompile of firmware 44 found the likely root cause: the keyboard obeys only the first USB bus reset after power-on and ignores later ones until it has slept, so after a restart it can keep a stale USB address and Windows can't find it. **exp8** (stock firmware + a 2-byte fix so every reset is obeyed) is being tested — [download/Y540-Keyboard-Fix-exp8-TEST.zip](../download/Y540-Keyboard-Fix-exp8-TEST.zip), details in [the firmware map](../research/analysis/firmware-44-full-decompile/README.md). The release (exp4) stays the recommended download until exp8 is confirmed.

## Author's laptop

Lenovo Legion Y540-15IRH (81SX), BIOS BHCN35WW, Windows 11 26200.

| Date (2026) | Firmware | Test | Result |
|---|---|---|---|
| 13 Oct | exp3 | ordinary restarts | initially seemed better, then failed again |
| 16 Oct | exp3 | ordinary restart, boot trace | **failed** — keyboard silent, no self-recovery ([trace findings](boot-trace-1-findings.md)) |
| 16 Oct | exp4 install, attempt 1 | — | write stopped part-way (bootloader stopped answering); no damage |
| 16 Oct | exp4 install, attempt 2 | — | written and verified |
| 16 Oct | exp4 | ordinary shutdown, boot trace | **works** — keyboard enumerates on first attempt |
| 16 Oct | exp4 | Shift + shutdown, boot trace | **works** — keyboard enumerates on first attempt |
| 16 Oct | exp4 | several further shutdowns / Shift+shutdowns | **works**; backlight flashes once at power-off |
| about 2 days later | exp4 | ordinary shutdown | **failed once** — no backlight flash at power-off; reinstall on 2 Nov showed the chip still held exactly exp4, so exp4's reset simply did not fire that time |
| 2 Nov | exp5 (exp4 + idle-gate vetoes removed) | install | **withdrawn** — keyboard restarted every 1.6 s and could not be reached from Windows; the removed hardware check (`16E0`) is the chip's real "bus suspended" signal |
| 2 Nov | exp4 restored | Linux live-USB rescue ([tools/linux-rescue](../tools/linux-rescue/)) | **recovered**, keyboard working again |
| 2 Nov | exp6 (exp4 without activity vetoes) | normal shutdown | **failed** — no flash, dead in Windows |
| 2 Nov | exp4/exp6 | read-only probe | found the USB frame counter (2F55:2F56) |
| 3 Nov | exp7 (exp4 + frame-counter watchdog) | built | kept as fallback, not tested |
| 3 Nov | **exp8** (stock + bus-reset fix) | installing | testing |

## Other laptops

None reported yet. Please open an issue with your model, BIOS version and result.
