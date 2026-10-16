# Why every bootloader contact failed, and what fix5 changes

Written 2026-10-13 from the owner's fix4 recording (`outputs/fix4-final-analysis/`). Everything below is marked **Observed**, **Inferred** or **Unknown**. No hardware was touched to produce it; the development PC has no keyboard controller.

## One-paragraph result

The updater fails because it lets the bootloader sit idle. After the `09` handoff the keyboard re-enumerates as 048D:89DB in about half a second, the updater then sleeps a fixed 6 s (`[DELAY] MSEC=6000` in Lenovo's own `SHFU.ini`), Windows selectively suspends the idle device, and **the device never answers again after Windows resumes it**. Every later transfer ends with `USBD_STATUS_XACT_ERROR` and zero bytes. The previous attempts (longer retries, reopening, read/write access) all happened after that point, so none of them could work.

## Observed (fix4 recording, `suspend-resume-timeline.txt` is the extract)

| Time (laptop clock, +03:29 label ignored) | Event |
|---|---|
| 08:31:08.632 | Updater sends the `09` boot command to 048D:C100; the device disconnects from port 9 five milliseconds later |
| 08:31:09.123 | 048D:89DB enumerates on port 9, bound to the expected device; descriptors, SET_CONFIGURATION, SET_IDLE and the 85-byte HID report descriptor all succeed with USBD status 0 |
| 08:31:09.130 | Last successful transfer. The updater is asleep in `Sleep(6000)` |
| 08:31:15.157 | USBHUB3 puts the idle boot device into its low-power state (`TargetState=0x4`), 6.03 s after the last transfer |
| 08:31:15.648 | The updater opens the HID interface; Windows cancels the idle request and requests D0 (`TargetState=0x1`) |
| 08:31:15.698 | Port 9 reports a suspend/resume change (`PortChange=0x4`) |
| 08:31:15.709 | The first transfer after resume (SET_IDLE) completes with `0xC0000011`, zero bytes. 121 transfers on this device fail the same way, none succeed. |

So the device was healthy for the first 5 ms of its life as 89DB and dead after one suspend/resume.

The updater source confirms the idle: `protocol.c` slept `wait_ms` (default 6000, and `SHFU.ini` ships `MSEC=6000`) between the handoff and the first poll, then polled every 500 ms. All logged failures (`fix2` attempt 1, `fix3`, `fix4`) show the same ~7 s gap between the `09` command and the first chip query.

## Inferred

- The failure is the device not recovering from USB suspend/resume, not a rights, framing, or timing-of-retry problem. Read/write access (fix4), 12 reopen rounds (fix3) and 10 retries per round (fix2) are irrelevant to a device that stopped responding.
- Lenovo's own updater has the same idle. Observed in the decompiled `ITESHFU.exe` button handler (`evidence/decompiled/103-update-button.c`): send `09`, `Sleep(1000)`, `ConnectHub(0x80)`, then spin for `DelayMSec` (6000) before reconnecting. Its remove/rescan branch is skipped for this device: the code compares the first three characters of the boot hardware ID with the string `USB` (read from `ITESHFU.exe` `.rodata`, file offset `0x2DF1D9`) and only rescans when they differ. So on a system whose Windows idles the freshly enumerated 89DB device, the vendor tool can strand the keyboard in boot mode in the same way. The original Lenovo failure logs are not available, so this is a plausible explanation for failed official updates, not a proven one.

## Unknown

- **Why the first fix2 session succeeded.** It had the same ~7 s gap and still read, erased, wrote and verified. A plausible cause is that this was the first time Windows enumerated the 89DB identity (driver install keeps it busy), so no idle suspend happened. That is not verified; fix5 does not depend on it.
- **Whether the daily symptom is the same defect.** After a normal restart/shutdown the app-mode device (C100) also fails to answer its first descriptor request, and a 10 s forced power-off cures it. That has the same shape (device dead after a power-state transition, cured only by power loss) and the bootloader, which is not part of the 54 KiB update image, shows it too. This is a hypothesis; only a hardware test of the no-sleep image can confirm it.
- Whether the suspend failure comes from the controller, the board's supply/reset network or something else.

## Why the no-sleep image remains the right candidate

`outputs/firmware-reset-analysis/power-state.md` found a sleep entry (`4BC4` ... `813C` ... `PCON=02`). Independent byte scan of the stock image (this session):

- `MOV PCON,#02` (`75 87 02`) occurs only at `263F`, `2659` and `2672`, the tails of the three helpers `2633`, `264B` and `2665`.
- Those helpers are reached only from `813C` (`LCALL` at `8175`, `817A`, `817F`), `813C` is called only from `4CB0`, which is inside `4BC4`, called only from `26F7`. No other `LCALL/LJMP/ACALL/AJMP` to any of them exists.
- Experimental image 1 turns `JZ 4CE1` (`60 66`) at `4C79` into `SJMP 4CE1` (`80 66`) and fixes the checksum (`7FFF`: 22 to 42). `4CE1` is the function's `RET`. Verified again here: two bytes differ, `0x4C79` and `0x7FFF`, sum over `0400..D7FF` with the two checksum slots read as `FF` is `5642`, matching the stored value, and the stock image gives `5622`.

So the image removes the only found route to `PCON=02` without touching any hardware register. Computed jumps (`JMP @A+DPTR`) are not excluded by this scan. It remains an untested hypothesis about the daily symptom.

## What fix5 changes (and what it does not)

Changed:
1. The fixed `Sleep(wait_ms)` after the handoff is gone. The updater polls for the 89DB interface every 40 ms (budget 30 s) and queries the chip the moment it is enumerated and started. New function `y540_wait_boot_device`.
2. Read/write access on the boot interface (fix4) is reverted to access 0, the setting of the only complete write. Evidence: access never mattered.
3. The final failure message names the enumerated-but-silent state and its recovery (10 s power hold).
4. The GUI logs the active power plan's "USB selective suspend" setting. Optional reversible scripts turn it off for the session.
5. Offline tests: a simulated bus where the device dies after 5 s idle. The fast path contacts it at ~0.5 s; a model of the old behaviour is dead at 6 s.

Unchanged on purpose: mandatory chip qualification, two complete matching backup reads flushed to disk before erase, no erase after failed verify, global operation mutex, topology binding to the same USB port, and the default no-sleep image.

## How to tell whether the diagnosis was right

Run `RUN-FIX5.cmd`. It records the same USB trace. After it finishes:

```
toolchain\python\python.exe -I outputs\fix5-analysis\suspend_resume_timeline.py decoded.json
```

If the boot device now answers its first chip query before any `HUB3 53` low-power line, the idle theory is confirmed. If it still goes silent without a preceding suspend, the cause is elsewhere and that timeline says where to look next.
