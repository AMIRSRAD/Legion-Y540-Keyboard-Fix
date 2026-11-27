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
- After sleep/wake the keyboard backlight starts **off** (the chip restarts); switch it on with the backlight key ([#4](https://github.com/AMIRSRAD/Legion-Y540-Keyboard-Fix/issues/4)).
- The **Num Lock light may be out of sync** after a restart: the light is off while Windows treats Num Lock as on, so the numpad types digits. Press Num Lock twice to resync ([#2](https://github.com/AMIRSRAD/Legion-Y540-Keyboard-Fix/issues/2)). Not yet investigated in the firmware.
- If Windows is allowed to switch the keyboard off when idle, the first key after a long idle may be lost while it reconnects. To avoid it: Device Manager → *Universal Serial Bus controllers* → the device on *Port_#0009* → *Power Management* → untick *Allow the computer to turn off this device to save power*.

## Other Legion models (Y545 and similar): read-only firmware dump

exp7 is a patch of **firmware 44** and is only tested on Y540s. If your keyboard reports a different revision (for example `REV_0043` on a Y545), do not flash it. Instead run the read-only dump: [Y540-Firmware-Dump.zip](https://github.com/AMIRSRAD/Legion-Y540-Keyboard-Fix/raw/main/download/Y540-Firmware-Dump.zip). It reads the whole 64 KiB of keyboard flash into a file (no erase, no write) so it can be compared with firmware 44; attach the `logs` folder to an issue.


## The keyboard is dead even aftera 10-second hold, battery drain, or battery removal

Seen on BIOS BHCN45WW laptops ([#6](https://github.com/AMIRSRAD/Legion-Y540-Keyboard-Fix/issues/6), [#7](https://github.com/AMIRSRAD/Legion-Y540-Keyboard-Fix/issues/7)). The keyboard works in the BIOS and boot menu, but Windows and Linux can't enumerate it (`device descriptor read/64, error -71`). The updater and the Linux rescue can't reach the chip from an OS in this state. Two reporters fixed it by writing exp7 from UEFI, where the firmware's own USB stack can still talk to the chip: see [tools/uefi-flash](../tools/uefi-flash/README.md) (community tool by adameq, public domain; [#7](https://github.com/AMIRSRAD/Legion-Y540-Keyboard-Fix/issues/7), [#6](https://github.com/AMIRSRAD/Legion-Y540-Keyboard-Fix/issues/6)). You compile it yourself; it is tested on two laptops, so read the README and the source first.

## Hardware route: the L23 choke (soldering, last resort)

Some owners fixed the same symptoms in hardware instead of firmware. **L23** is the small common-mode choke on the USB 2.0 lines (USB20_P9) between the chipset and the keyboard controller. Reports:

- A repairer on [vlab.su](https://vlab.su/viewtopic.php?f=58&t=136509) measured USB20_P9 with an oscilloscope, traced the problem to L23, and fixed it by replacing L23; the original controller then worked without reflashing.
- Two users on [Reddit](https://www.reddit.com/r/Lenovo/comments/gswrt6/comment/jtz5mxc/) bridged L23, and their keyboards have survived reboots since.
- A Y540-15IRH-PG0 owner (BIOS BHCN45WW, [#8](https://github.com/AMIRSRAD/Legion-Y540-Keyboard-Fix/issues/8)) removed L23 and replaced it with two wire links; the keyboard works perfectly.

This is not part of this project and I have not tried it. It involves opening the laptop and soldering on a dense board, can damage it, and removes the filter that protects the USB line. Try the firmware fix first (exp7, or the [UEFI tool](../tools/uefi-flash/README.md) if the keyboard is dead even after a full power cut); consider the hardware route only if those do not help, and preferably have a repair shop do it.

## Windows blocks the program (Smart App Control / SmartScreen)

The updater and the dump tool are **not code-signed** (a certificate costs money and this is a hobby project), so Windows 11 *Smart App Control* can block them even though Defender and VirusTotal find nothing. The ZIP contains `SHA256SUMS.txt` so you can verify the files, and the full source is in [`source/`](../source/), so you can build it yourself (also unsigned).

- **SmartScreen** ("Windows protected your PC"): *More info → Run anyway*.
- **Smart App Control** has no "run anyway". Turning it off (Windows Security → App & browser control → Smart App Control) has historically been **permanent until Windows is reinstalled**; check Microsoft's current guidance before doing it.
- **Alternative without touching Windows settings:** use a Linux live USB and the [Linux tool](../tools/linux-rescue/): `sudo python3 y540_linux_rescue.py 44-reset-exp7.bin` (copy `44-reset-exp7.bin` from the download ZIP next to it). It follows the same steps as the updater (chip check, bootloader check, backup, erase, write, verify). It was written for a restart-looping keyboard and has been used on real hardware once; its offline self-test passes (`python3 y540_linux_rescue.py --selftest 44-reset-exp7.bin`). There is no dump-only mode; the backup it saves before writing is a full dump.
- **Other option:** the [UEFI tool](../tools/uefi-flash/README.md) runs outside Windows entirely and has a backup-only mode (compile it yourself).

