# Troubleshooting and undo

## The updater refuses to start writing

**`Firmware write refused: need one healthy physical ITE keyboard; found 0`**
The keyboard is in its broken state, so the updater cannot reach it. Get it typing again first — hold the power button about 10 seconds until fully off and turn on, let the battery drain completely, or use whatever method works for you — then try again.

**`This keyboard does not hold firmware 44 or a known patch of it`** — your keyboard runs other firmware (for example the Y545's version 43). Nothing was changed. exp7 is only for firmware 44; please open an issue.

**`Bootloader reset dependency differs; exp3/exp4/exp6/exp7/exp9 not installed, no erase performed`**
Your keyboard chip's built-in recovery code is not the one this fix was tested on. Nothing was changed. Do not try to force it; open a GitHub issue with the log from the `logs` folder.

**`... permits only exact stock44, exp1, exp3, exp4, exp6, exp7, exp8 or exp9 ...`**
You selected a firmware file that is not one of the known files. Use the files from the download only.

## The backup or write stopped part-way

Example: `Update stopped: HidD_SetFeature failed (code 31).` or `HidD_GetFeature failed at flash 0x…: bootloader stopped answering (code 31)`.

The keyboard's update mode sometimes stops answering during a long transfer. Since fix14 the updater re-requests a stalled read up to three times by itself. If it still stops:

- **If it stopped during "Read complete update region for backup", nothing was erased.** Hold the power button 10 seconds, turn on, and the keyboard types normally again.
- Turn off USB selective suspend for the install: right-click `optional-usb-power\DISABLE-USB-SELECTIVE-SUSPEND.cmd` → **Run as administrator** (undo afterwards with `RESTORE-USB-SELECTIVE-SUSPEND.cmd`). Keep the charger connected.

- The keyboard will **not type** until a write completes, but its **recovery (boot) area is never erased**, so it can always be written again.
- Run `INSTALL THE FIX.cmd` again and write again. The updater recognises a half-finished write and continues safely.
- If it cannot find the keyboard: hold the power button 10 seconds, turn on, and try again. The keyboard comes up in update mode by itself because the half-written firmware falls through into the recovery program.
- If it fails three times in a row, stop and open an issue with the `logs` folder.

## The keyboard still dies after a restart with exp7

1. Wait 30 seconds without touching anything — note whether it comes back by itself.
2. Hold power 10 seconds to recover it.
3. Run the [boot trace kit](https://github.com/AMIRSRAD/Legion-Y540-Keyboard-Fix/raw/main/download/Y540-boot-trace-kit.zip) on the next restart and attach the ZIP it makes to a GitHub issue.

## The keyboard restarts over and over and the updater can never catch it

If the backlight flashes every second or two and the updater keeps saying `found 0` (this happened with a withdrawn test build, exp5), Windows is too slow to reach the keyboard between restarts. Use the **Linux rescue**: boot a Linux Mint live USB and run one command. It catches the keyboard, switches it to update mode and writes exp4 back with the same safety checks. Download [Y540-Linux-Rescue.zip](https://github.com/AMIRSRAD/Legion-Y540-Keyboard-Fix/raw/main/download/Y540-Linux-Rescue.zip) and follow its `READ ME.txt`; details in [tools/linux-rescue](../tools/linux-rescue/).

## Undo / go back

Get the keyboard typing first (10-second power hold, battery drain, or whatever works for you). Run `INSTALL THE FIX.cmd`, click **Browse…** next to the firmware box, open `other-firmware` and choose:

| File | What it is | Validate shows |
|---|---|---|
| `44-original-lenovo.bin` | Lenovo's original firmware 44 | `Sum=5622` |
| `44-recovery-exp3.bin` | Earlier experiment exp3 | `Sum=0699` |
| `44-nosleep-exp1.bin` | Earlier experiment exp1 | `Sum=5642` |

Then **Validate firmware → Advanced firmware write → Yes**, as in the install guide. Your own pre-install backup is in the `logs` folder (`before-flash-….bin`), for reference.

## Known side effects of exp7

- Keyboard backlight flashes once at power-off: normal.
- The built-in keyboard cannot wake the laptop from Sleep. Use the power button or lid.
- If Windows is allowed to switch the keyboard off when idle, the first key after a long idle may be lost while it reconnects. To avoid it: Device Manager → *Universal Serial Bus controllers* → the device on *Port_#0009* → *Power Management* → untick *Allow the computer to turn off this device to save power*.

## Other Legion models (Y545 and similar): read-only firmware dump

exp7 is a patch of **firmware 44** and is only tested on Y540s. If your keyboard reports a different revision (for example `REV_0043` on a Y545), do not flash it. Instead run the read-only dump: [Y540-Firmware-Dump.zip](https://github.com/AMIRSRAD/Legion-Y540-Keyboard-Fix/raw/main/download/Y540-Firmware-Dump.zip). It reads the whole 64 KiB of keyboard flash into a file (no erase, no write) so it can be compared with firmware 44; attach the `logs` folder to an issue.

