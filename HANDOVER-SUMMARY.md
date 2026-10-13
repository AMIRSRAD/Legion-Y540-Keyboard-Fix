# Y540 keyboard case: progress since the handoff

Written 2026-10-13 for the previous owner of the investigation. It picks up from `outputs/fix4/CASE-RECORD.md` and the fix4 final recording, and says what was found, what was built, what the hardware said, and what is still open. Observed, inferred and unknown are kept apart.

## 1. Where it started

Affected laptop: Legion Y540-15IRH (81SX), BIOS BHCN35WW, Windows 11 build 26200. Ordinary restart or shutdown/power-on kills the internal keyboard (USB 048D:C100 on xHCI port 9); a ~10 s forced power-off restores it. Fn keys keep working. Stock firmware 44 had been rewritten successfully once (fix2) without effect. fix3 and fix4 could not get a chip answer from the bootloader (048D:89DB): 120 failed queries, USBD 0xC0000011, no erase or write.

## 2. Finding 1: why every bootloader attempt failed (observed)

The fix4 ETW trace shows, on the boot device:

| Time | Event |
|---|---|
| +0.0 s | `09` handoff; C100 disconnects |
| +0.5 s | 89DB enumerates; descriptors, SET_CONFIGURATION, SET_IDLE, report descriptor all succeed |
| +6.0 s | USBHUB3 puts the idle device into its low-power state (updater is in its fixed `Sleep(6000)`, the `[DELAY] MSEC=6000` from Lenovo's SHFU.ini) |
| +6.5 s | updater opens the HID interface, Windows resumes the device |
| +6.5 s onward | the first transfer after resume and every later one (121 total) fail, USBD 0xC0000011, 0 bytes |

Lenovo's own `ITESHFU.exe` does the same: send `09`, `Sleep(1000)`, then spin for `DelayMSec` (6000) before touching the boot device (decompiled `103-update-button.c`; the remove/rescan branch is skipped because the code compares the first three characters of the boot HWID with the string `USB`). So an idle bootloader that does not survive Windows' selective suspend is a plausible reason the vendor tool fails. Read/write open mode (fix4), 12 reopen rounds (fix3) and retries were irrelevant: the device was already silent.

Extract: `outputs/fix5-analysis/ROOT-CAUSE.md`, `suspend-resume-timeline.txt`, `suspend_resume_timeline.py`.

## 3. What was built (all offline-tested; sources under `outputs/fix5..fix8`)

| Build | Change | Hardware result |
|---|---|---|
| fix5 | Poll for the boot device every 40 ms and query it as soon as it enumerates; boot interface back to access 0 | Bootloader answered on the first try (15 ms after enumeration), first full 54 KiB read worked (31 s). Second confirming read hung at flash address 0x8068, ~51 s in, with continuous traffic and no suspend, resume or port event. Nothing erased. |
| fix6 | If the first full read equals a known image (SHA-256), skip the second read; log read progress and the failing address | Backup read, erase, 54 blocks written, full readback matched, reset accepted. **First successful write of the experimental no-sleep image (exp1, checksum 5642).** |
| fix7 | Read-only dump of flash 0xD800..0xFFFF (only D1 reads and a final C4; no erase/write commands in that code path) | Clean run, keyboard still working afterwards (section 5). |
| fix8 | exp2: exp1 plus a software watchdog (section 6) | No improvement; restarts got worse (section 6). |

Also reverted along the way: fix4's read/write HID open (no evidence it matters).

## 4. Hardware results with exp1 (the best state so far)

- Restarts #1 and #2 after a forced power-off work; #3 fails. Repeated a second time: failed on #3 again.
- Shutdown, wait 30 s, power on: failed on the first try.
- 10 to 15 minutes idle, then typing: works.
- Fn keys always work; the keyboard chip itself is the dead part. In the failed state Device Manager shows "Unknown USB Device (Device Descriptor Request Failed)", code 43, with the keyboard HID entries greyed (code 45).
- A 10 s forced power-off always restores it.

Before exp1 essentially every restart failed. Interpretation (inferred): removing the firmware's deep-sleep entry fixed one contributor but not the fault.

## 5. Finding 2: the flash above the firmware, and what the bootloader is (observed)

Dump `outputs/fix7-analysis/flash-dump-D800-...bin` (10240 bytes, SHA-256 `6160ed91...684d2a`), re-read of the first KiB identical:
- `D800..D8FF`: 256 non-FF bytes: `19 78 03 05` then 252 zero bytes. Nothing in the app or the bootloader loads this block through a DPTR constant. Purpose unknown. `D900..DFFF`: all FF.
- `E000..F9CB`: bootloader, 6.6 KB, string `IT8171-bbk--v1.0` at E04E, USB device descriptor VID 048D PID 89DB at F90A. It decodes as complete, ordinary 8051 code. Entry `LJMP E003`; the application's checksum-failure path (`0130`) jumps to E000.
- `F9CC..FFFF`: FF.
- The bootloader has **no write to PCON** (no software sleep or idle), polls USB status registers (2F40/2F41/2F52) instead of using interrupts, and touches 1F01/1F06/1F07 only in one small routine called from its bus-reset wait loop (`F896`; looks like a watchdog feed: `1F07 = 5C`).

Inference: a bootloader that never sleeps in software, and that the 44 update does not touch, still (a) stopped answering after a Windows suspend/resume and (b) hung once mid-read. So the "chip stops answering" fault exists below firmware 44's sleep code.

Correction to my own earlier note: the application has four `MOV PCON,#02` sites, not three. The fourth is at `0978` inside an unreferenced function at `0966` (it changes 1E06, sets 1E03=1, disables interrupts via 059D, then power-down). No caller found by LCALL/LJMP/ACALL/AJMP or address constant. The three live sites (`263F`, `2659`, `2672`) are all reachable only through `26F7 -> 4BC4 -> 4CB0 -> 813C`, which exp1 blocks at `4C79`.

## 6. exp2 (self-recovery watchdog) and its result

156 bytes at `0x8A00`, hooks at `2249` (main loop kick), `330A` (timer-0 ISR tick), `35E6` (bus-reset handler arm) and `4034` (SET_ADDRESS disarm). Triggers: main loop silent for 8000 ticks, or bus reset not followed by SET_ADDRESS within 3000 ticks. Recovery: CLR EA, write 0 to 2F40 (assumed USB attach control), ~0.4 s delay, RETI to 0100. Tested on a minimal 8051 emulator (logic, thresholds, stack discipline). The 1 ms tick, the meaning of 2F40 and bit 2 of 2F52 as "bus reset" are inferences from the init code and the bootloader.

Result: written and verified, the keyboard enumerated 1.4 s after the reset, but the fault was not cured and restart #1 now fails (exp1 survived two). exp2 is worse than exp1. Recommended state: back on exp1.

## 7. Other observations worth knowing

- Every time the keyboard switches into boot mode, the camera on port 6 (VID 30C9 PID 001B) disconnects and reconnects about 77 ms after port 9 drops. Seen in fix4, fix5 and fix8 traces. Cause unknown; may only be a shared reset or power event.
- Hardware-level facts from the earlier board analysis (`outputs/platform-reset-analysis/board-connectivity.md`): keyboard controller U22 IT8176, supply switch U23 SY6288 feeding +3VALW_AG, enable AGKB_PWR_EN# tied through 0 ohm RE102 to PCH_PWR_EN, reset network R376/C276/D44. Not measured on this laptop.

## 8. What I think, and how sure I am

- Fairly sure (trace evidence): the updater failures were the bootloader dying after Windows suspended it during the 6 s wait. Fixed by fast contact.
- Fairly sure: the sleep-entry path contributed to the restart fault (restart #1 and #2 now survive; idle is fine).
- Not established: the remaining fault. Candidate explanations I cannot separate from software: the chip's USB/clock block, its supply/reset network, board wiring, or an interaction with how the host/BIOS resets the port. Counting behaviour (fails on restart #3 twice) suggests something accumulates across host resets between power losses; shutdown with a 30 s wait fails at once, so the chip is not losing power at shutdown.

## 9. Questions and ideas for the previous owner

1. What was the keyboard firmware version before the Lenovo update (43?), and did the laptop ever fail restart/shutdown before? Is any pre-update dump or `ite1fw` older package available? A 56 KB working dump (`it8176Work_56k.bin`) is mentioned on Vinafix; its layout reaches E000, so the pre-44 image may have used D800..DFFF. Does the 256-byte block at D800 look like something an older firmware or the Lenovo tool writes?
2. Does the original Lenovo flow write anything outside 0..D7FF (e.g. a flag or parameter page)? The `UPDATEONLYPARAMETER` / `OEMVEROFFSET` settings suggest a parameter mode.
3. Any documentation for IT8176/IT8171 registers 2F40, 2F41, 2F52, 2F50, 1E03, 1F01, 1F06, 1F07? Without it the sleep and reset code can only be read, not understood.
4. Did you or anyone measure D+/D-, the U22 supply, AG_WRST# or KB_PWR_EN# during a failed restart on a real board? A scope trace at failure is the one measurement that would settle chip versus supply versus reset.
5. Would a BIOS or EC update change anything? BHCN35WW is installed; the earlier analysis found no change to the relevant ACPI methods between 35, 36 and 45, but the native BIOS/SMM and EC firmware were not compared. Untried and not recommended without a reason.
6. Does anyone have experience with this failure on other Y540 units after a successful write of firmware 44 (i.e. is it the chip/board of this unit, or does 44 itself break the platform)?

## 10. Where things are

All under `D:\Projects\Y540-Keyboard`:
- `FIX5-README.md`, this file.
- `Y540Updater-fix5/6/7/8-portable.zip` (fix8 contains exp1, exp2, stock and the dump function; CLI `--dump-flash`).
- `handoff/02-Y540-Development/outputs/`: `fix5..fix8` (source, tests, dist), `fix5-analysis`, `fix6-analysis` (`dis8051.py` mini disassembler), `fix7-analysis` (dump, logs, `findings.md`, `boot_region_image.bin`), `firmware-selfheal-exp2` (`build_exp2.py`, `test_exp2.py`, image, manifest).
- Raw run logs and traces are on the owner's Desktop (`logs`, `fix5/6/8-recording-*.zip`) and copies of the fix7 dump logs are in `fix7-analysis`.

Images and hashes:
- stock 44: `3afec131c6ed70efa0a3f4b601cb799011a582835d371c57fef68af48519e359`
- exp1 (no-sleep, 2 bytes): `2b34b6d59db8443831a7e0387ae65970307f516e816dd481f1ba513d3f9de773`
- exp2 (self-recovery): `82c94fd50191a3ad8b4f9760ebf588b911b193450dd7edeeec06bacba338e1b8`

Nothing was flashed to any machine other than the owner's affected laptop. The development PC never ran a flash, USB reset or vendor tool.
