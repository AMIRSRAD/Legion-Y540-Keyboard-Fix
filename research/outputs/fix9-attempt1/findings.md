# fix9 attempt 1

The supplied fix9 log confirms exact exp1 backup, both expected bootloader dependencies, successful exp3 write and full 54 KiB readback matching release SHA-256. C4 was accepted. No application transfer failures were logged.

The accompanying ZIP is the older return-to-exp1 capture, not a fix9 USB trace. This log does not establish typing or restart recovery. Owner outcome is recorded below.

## Owner outcome after exp3 â€” 2026-10-13

The owner reports that normal Restart now always works in the performed tests and normal Shutdown/power-on also works, both repeated multiple times. A subsequent Shift + Shutdown/power-on failed. Exact trial counts, typing recovery time and recovery method after that failure are not supplied yet.

This is a reported partial improvement after byte-verified exp3 installation, not a complete repair or direct evidence that the watchdog fired. The supplied USB ZIP is still the old exp1-return recording; it does not capture the improved restarts or the Shift-shutdown failure.

The owner earlier reported Fast Startup off. Do not assume the normal shutdowns were hybrid or that Fast Startup explains the difference without current settings and transition evidence. Microsoft's [system power-state documentation](https://learn.microsoft.com/en-us/windows/win32/power/system-power-states) distinguishes hybrid startup from full shutdown, but it does not establish this laptop's actual transition from the reported key combination alone.

Preserve exp3 as the best reported state. The next discriminating fact is whether an ordinary Restart recovers typing after the Shift-shutdown failure or whether the known 10-second power-button shutdown remains necessary. No new image has been built or flashed in response to this report.

## Final owner correction — 2026-10-13

The owner subsequently withdrew the earlier success report: a normal restart again leaves the keyboard nonworking; any period of working restarts did not last. The owner explicitly states exp3 did not fix it. Treat this as the current outcome. No reliable repair was achieved. Successful programming and readback remain verified; no automatic watchdog recovery or permanent symptom improvement is established.

The owner requested a complete GitHub preservation archive and local project cleanup. No further firmware experiment is being pursued in this project.
