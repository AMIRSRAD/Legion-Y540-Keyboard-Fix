# Y540 keyboard updater: fix5

**Package to use:** `Y540Updater-fix5-portable.zip` (SHA-256 `9A65681D2F12E210D3CB372133BE3749D9DCA43A2D7B6489CAB23F407F056841`). Extract it on the affected laptop and follow `START-HERE.txt` inside.

## What I found

The earlier updaters did not fail because of access rights, report framing or retry counts. The USB recording from the last attempt (fix4) shows this sequence:

1. The updater sends the boot command. The keyboard re-enumerates as the bootloader (048D:89DB) within about half a second, and all descriptor requests succeed.
2. The updater then sleeps 6 seconds. That value is `[DELAY] MSEC=6000` in Lenovo's own `SHFU.ini`, and Lenovo's `ITESHFU.exe` waits the same way (decompiled handler `103-update-button.c`).
3. At 6.03 s Windows suspends the idle bootloader. When the updater finally opens it, Windows resumes it, and **the bootloader never answers again**: the first transfer after resume and all 121 that follow fail with `USBD 0xC0000011`, zero bytes.

So the 120 failed chip queries, the "Win32 error 31", and the failure of fix3 and fix4's longer retries all happened after the device had already gone silent. That is also a plausible way for Lenovo's own tool to strand a keyboard in boot mode, though Lenovo's original logs are not available to confirm it.

Evidence: `handoff/02-Y540-Development/outputs/fix5-analysis/` (`ROOT-CAUSE.md`, `suspend-resume-timeline.txt`, and the script that regenerates it from the recording).

## What fix5 does

- Polls for the bootloader every 40 ms and queries it as soon as it enumerates, so Windows has no idle window to suspend it.
- Reverts the boot interface to access 0, the setting of the one complete write (fix2). Read/write access (fix4) was irrelevant.
- Keeps every safety gate: chip must answer 8171/8176, two complete matching reads saved and flushed before erase, no erase after a failed verify, one operation at a time.
- Logs the Windows "USB selective suspend" setting and includes optional reversible scripts to turn it off for the session.
- Default image is still `44-nosleep-exp1.bin` (two bytes differ from stock). I re-verified the diff and checksum independently (stock 5622, patched 5642) and that the patched branch sits on the only code path to `PCON=02`, the only power-down write.

## What is verified and what is not

- **Verified here:** it builds with `-Werror`; all offline suites pass (checksum, transport, protocol emulator, device-state fixtures, session log, GUI smoke); the new simulated-bus tests show the fast path contacts the device at about 0.5 s while a model of the old 6 s wait is dead at 6 s; the shipped exe and images match their recorded hashes.
- **Not verified:** nothing has run on your keyboard. This development PC has no keyboard controller and I did not run any flash, USB reset or vendor tool. I cannot tell you the update will complete.
- **Open questions I could not close:** the first fix2 session had the same 7 s gap and still succeeded (my guess is that was the first enumeration of the 89DB identity, unverified). And whether the no-sleep image cures the restart/shutdown fault is still a hypothesis; the new evidence fits it (a device that cannot wake from suspend) but does not prove it.

## If it fails

Do not retry blindly. Hold power about 10 s to recover the keyboard, keep the ZIP that `RUN-FIX5.cmd` prints, and run `suspend_resume_timeline.py` on its trace. If the bootloader answers its first query before any suspend line and then stays alive, the idle theory held and the remaining problem is elsewhere. If it still goes silent without a suspend, this diagnosis is wrong for that run and the timeline shows where.

Source: `handoff/02-Y540-Development/outputs/fix5/` (build with `BUILD-FIX.ps1 -Project fix5` from the development folder, or `build.ps1 -Compiler <gcc>`).
