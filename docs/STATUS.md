# Test status

**Current state (3 Nov):** **exp7** (frame-counter watchdog) is the recommended fix. On the author's laptop it works through repeated shutdowns and restarts, and the backlight flashes ~0.5 s after power-off each time. It is under longer-term test (exp4 also looked perfect at first and failed days later). exp8 alone did not fix it; exp9 (exp7 + exp8) is an untested spare.

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
| 3 Nov | exp8 (stock + bus-reset fix) | restarts / shutdowns | **failed** — backlight stays on through shutdown, dead in Windows |
| 3 Nov | **exp7** (exp4 + frame-counter watchdog) | repeated restarts and shutdowns | **works** — flash ~0.5 s after power-off, keyboard fine in Windows; long-term test ongoing |

## Other laptops

None reported yet. Please open an issue with your model, BIOS version and result.
