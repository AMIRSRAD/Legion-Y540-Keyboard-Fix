# UEFI keyboard flasher (community tool by adameq)

For laptops where the built-in keyboard is dead **even after a 10-second power hold, battery drain or battery removal**, and no OS can enumerate it (`device descriptor read/64, error -71`), but it still works in the BIOS or boot menu. Then the Windows updater and the Linux rescue can't reach the chip, but the firmware's own USB stack (UEFI) can. This tool talks to the chip from UEFI and writes exp7.

**Author and license:** written by [adameq](https://github.com/adameq) (reported in [issue #7](https://github.com/AMIRSRAD/Legion-Y540-Keyboard-Fix/issues/7)), released into the public domain (CC0 / Unlicense / MIT-0, no attribution required) as stated in that issue. Included here unmodified. The protocol and safety checks are ported from this project's updater.

**Confirmed working** on two laptops (Legion Y540-15IRH, BIOS BHCN45WW): [#7](https://github.com/AMIRSRAD/Legion-Y540-Keyboard-Fix/issues/7) (adameq, from Limine) and [#6](https://github.com/AMIRSRAD/Legion-Y540-Keyboard-Fix/issues/6) (bajuszadam23, from GRUB, Docker-built, Windows fallback removed).

## What it does
- `ite_probe.efi` (**read-only**): lists the USB devices UEFI sees and shows whether `048D:C100` is visible. Run this first.
- `ite_flash.efi`: menu 1 = backup only, 2 = backup + install exp7, 3 = backup + restore original Lenovo 44. Stops without erasing unless the chip is 8171/8176, its reset routine matches the tested chip, and the current firmware is a known image (or a blank/interrupted write). Saves and verifies a backup on the EFI partition first (`ite_bk01.bin`, `ite_flash.txt`), writes block 0 last, reads everything back, and asks for **Y** before erasing.

## Build (no prebuilt binary is provided: you compile it yourself)
1. Generate the firmware images header from the official ZIP (it verifies the SHA-256 of both images):
   `python gen_fw_images.py Y540-Keyboard-Fix.zip`
2. Build with clang + lld as in [BUILD.txt](BUILD.txt) (an Ubuntu Docker container works).
3. Copy `ite_flash.efi` and `ite_probe.efi` to `\EFI\ite\` on a FAT32 USB stick.
4. Start it from your boot loader or the GRUB console (Secure Boot must be off), for example:
   `search --no-floppy --file --set=root /EFI/ite/ite_flash.efi`, `chainloader /EFI/ite/ite_flash.efi`, `boot`.

Host test of the protocol logic (no hardware): `python gen_fw_images.py ...` then `gcc -O1 -o host_test host_test.c && ./host_test`.

## Notes and warnings
- Experimental and hardware-tested on two laptops only. It erases and rewrites the keyboard firmware. Read the source first.
- The "start Windows Boot Manager" fallback after a failed write assumes the author's desktop layout (`Desktop\ITE-fix\...`); you may want to remove it, as bajuszadam23 did.
- Keep the charger connected. During the operation the built-in keyboard doesn't work; if it stops partway, hold the power button ~10 s and run the tool again (it resumes).
- Reviewed by this project's maintainer on 2026-11-22: protocol bytes, known-image hashes and bootloader dependency bytes match `source/src/protocol.c`, the Linux rescue and the offline tests; the host test (8 scenarios) passes and `flash.c` and `probe.c` compile cleanly. Not run on hardware by the maintainer.
