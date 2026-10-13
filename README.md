# Y540 keyboard firmware: investigation and updater fixes

Lenovo Legion Y540-15IRH (81SX). After Lenovo's keyboard firmware 44 update, the internal keyboard (USB 048D:C100, ITE IT8176 family) stops enumerating after an ordinary restart or shutdown; a ~10 s forced power-off restores it.

Start with [HANDOVER-SUMMARY.md](HANDOVER-SUMMARY.md) (full progress, evidence, what worked and what did not, open questions). [FIX5-README.md](FIX5-README.md) explains the first fix in simple terms.

## Key result so far
The updater (and Lenovo's own tool) idled the freshly enumerated bootloader (048D:89DB) for 6 s; Windows suspended it and it never answered again. The updater here contacts the bootloader immediately. A no-sleep firmware variant (two bytes changed) improved but did not cure the restart fault; a self-recovery watchdog variant made it worse. See `analysis/`.

## Layout
- `updater/`: C source of the reconstructed updater (fix8, includes a read-only flash dump mode), tests, launcher scripts.
- `analysis/`: USB-trace timeline script and write-up, a small 8051 disassembler, bootloader dump findings.
- `firmware-exp2/`: build script and emulator test for the self-recovery experiment (exp2).
- `history/`: source, tests, docs and scripts of every earlier updater revision (`y540-research`, `fix1` to `fix7`), without binaries or samples.
- `analysis-history/`: all earlier write-ups and scripts (firmware static audit, reset/power-path analysis, board mapping, Linux and Windows trace analysis, update-attempt analyses, no-sleep experiment).

## Not included on purpose
Lenovo's installer/payload (`ite1fw11s.exe`, `ITESHFU.exe`, `44.bin`, `SHFU.ini`), every firmware image (stock, exp1, exp2), flash dumps, USB traces (`.etl`), raw device logs and the portable build zips (they contain device identifiers or Lenovo code). Usernames in text files were replaced by `owner`/`user`. Obtain Lenovo's package yourself; hashes are in the summary. The build script and tests expect `samples/44.bin` and `samples/SHFU.ini` from that package. Exp1 is reproducible with `history/fix7/experiment/build_patch.py`, exp2 with `firmware-exp2/build_exp2.py`, both from the stock 44.bin.

## Warning
Experimental research code written without access to chip documentation. It writes keyboard-controller firmware. Use only on a machine you are prepared to lose the keyboard on, with the original image backed up. Nothing here is a confirmed repair.

Build: `updater/build.ps1 -Compiler <path to MinGW-w64 gcc.exe>` (needs `samples/` as above).
