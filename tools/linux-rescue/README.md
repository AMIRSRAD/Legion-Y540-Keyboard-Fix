# Linux rescue for a restart-looping keyboard

`y540_linux_rescue.py` recovers a Y540 keyboard controller that restarts so fast Windows can never set it up (seen with the withdrawn experiment exp5). It runs from a Linux live USB as root and needs only the Python standard library.

**Plain-language steps:** [READ ME.txt](READ%20ME.txt). Ready-made ZIP with the script, exp4 and the instructions: [download/Y540-Linux-Rescue.zip](../../download/Y540-Linux-Rescue.zip).

## How it works

1. Sets `usbcore.old_scheme_first=Y` for the session, so Linux enumerates without the extra reset and pause that let the looping firmware reset the chip mid-setup.
2. Polls the keyboard's port (`/sys/bus/usb/devices/1-9`) and, the moment `048D:C100` appears, opens it through usbfs, keeps it busy with `GET_STATUS`, detaches the HID driver and sends the ITE key handshake plus the `5A/09` bootloader handoff back to back.
3. Once `048D:89DB` is present it disables autosuspend, claims interface 0 and drives the bootloader directly with 63-byte feature reports (no report ID), using the same protocol as the Windows updater: chip ID `8171/8176`, `F12C`/`F455` reset-routine check for exp3/exp4, full backup (second read unless the content is a known image or an interrupted write of the target), erase, `C0/C1/D0/C3` per block with the device's staging checksum, block 0 last, full readback compare, `C4` reset.
4. Only stock 44, exp1, exp3 and exp4 can be written.

`python3 y540_linux_rescue.py --selftest 44-reset-exp4.bin` runs the write sequence against an in-memory bootloader model on any OS.

Tested on the author's Y540-15IRH with Linux Mint 22.3 Xfce live USB (2026-11-02): recovered the keyboard from the exp5 loop and restored exp4.
