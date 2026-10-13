# Y540 keyboard firmware: investigation and updater fixes

Lenovo Legion Y540-15IRH (81SX). After Lenovo's keyboard firmware 44 update, the internal keyboard (USB 048D:C100, ITE IT8176 family) stops enumerating after an ordinary restart or shutdown; a ~10 s forced power-off restores it.

Start with [HANDOVER-SUMMARY.md](HANDOVER-SUMMARY.md) (full progress, evidence, what worked and what did not, open questions). [FIX5-README.md](FIX5-README.md) explains the first fix in simple terms.

## Key result so far
The updater (and Lenovo's own tool) idled the freshly enumerated bootloader (048D:89DB) for 6 s; Windows suspended it and it never answered again. The updater here contacts the bootloader immediately. A no-sleep firmware variant (two bytes changed) improved but did not cure the restart fault; a self-recovery watchdog variant made it worse. See `analysis/`.

## Layout
- `updater/`: C source of the reconstructed updater (fix8, includes a read-only flash dump mode), tests, launcher scripts.
- `analysis/`: USB-trace timeline script and write-up, a small 8051 disassembler, bootloader dump findings.
- `firmware-exp2/`: build script and emulator test for the self-recovery experiment (exp2).

## Not included on purpose
Lenovo's installer/payload (`ite1fw11s.exe`, `ITESHFU.exe`, `44.bin`, `SHFU.ini`), firmware images derived from it, flash dumps, USB traces and device logs. Obtain Lenovo's package yourself; hashes are in the summary. The build script and tests expect `samples/44.bin` and `samples/SHFU.ini` from that package.

## Warning
Experimental research code written without access to chip documentation. It writes keyboard-controller firmware. Use only on a machine you are prepared to lose the keyboard on, with the original image backed up. Nothing here is a confirmed repair.

Build: `updater/build.ps1 -Compiler <path to MinGW-w64 gcc.exe>` (needs `samples/` as above).
