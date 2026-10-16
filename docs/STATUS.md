# Test status

**Plan:** if exp4 is still holding after about a week of normal use (restarts, shutdowns, sleep), it is declared the fix and this page, the README and the download are updated to say so.

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
| — | exp4 | ordinary restarts ×6, sleep/wake, 15 min idle, one week of use | pending |

## Other laptops

None reported yet. Please open an issue with your model, BIOS version and result.
