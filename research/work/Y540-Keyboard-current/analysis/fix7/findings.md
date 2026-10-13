# fix7 read-only dump of flash 0xD800..0xFFFF (2026-10-13 08:49 UTC)

Input: `flash-dump-D800-20261013T084901150Z-p3460-3.bin` (10240 bytes, SHA-256 `6160ed916d5356c631a5e7939a55d3dae0b863199e0f33ba7e6680fe6f684d2a`), logs `fix7-...-1.log`, `-2.log`. Keyboard was running the experimental no-sleep image 5642.

## Observed
- Run was clean: bootloader opened 16 ms after enumeration, chip answered, 10 KiB read in about 6 s, re-read of the first KiB matched, C4 reset sent, owner reports keyboard still works.
- Layout of the region above the firmware:
  - `D800..D8FF`: 256 non-FF bytes: `19 78 03 05` then 252 zero bytes. Nothing in the app image or the bootloader addresses this block through a DPTR load. Purpose unknown.
  - `D900..DFFF`: all FF.
  - `E000..F9CB`: bootloader code, 6.6 KB. Entry `LJMP E003` at E000 (the application's checksum-failure path jumps there). String `IT8171-bbk--v1.0` at E04E. USB device descriptor with VID 048D PID 89DB at F90A..F91x.
  - `F9CC..FFFF`: FF (a 570-byte tail of F800..FBFF block is FF, FC00..FFFF all FF).
- The bootloader code decodes as ordinary, complete 8051 code with intact strings and descriptors. No sign of damage.
- The bootloader contains **no write to PCON** (no software sleep or idle at all). It polls USB event registers (2F40/2F41/2F52) instead of using interrupt-driven sleep.
- It writes the 1F01/1F06/1F07 registers once (F896..F8AB), consistent with its reset command; not confirmed.

## Inferred
- The bootloader, which the 44 update does not touch and which never sleeps in software, still stopped answering after Windows suspended and resumed it (fix4 trace), and once hung mid-stream (fix5). So the "device stops answering" fault is not caused by firmware 44's sleep code. It points at the chip's USB/clock/power behaviour or the board around it.
- The no-sleep image removes one real contributor (restarts 1 and 2 now work, idle is fine) but cannot remove a fault that exists below the firmware.

## Unknown
- What the D800 block is and whether the Lenovo update ever wrote it.
- Whether the remaining fault is the chip, its supply/reset network, its clock, or the USB wiring.
