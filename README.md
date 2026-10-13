# Lenovo Y540 keyboard investigation — preserved, unresolved

**Final outcome (2026-10-13): no reliable keyboard repair was achieved.** The owner withdrew the initial exp3 success report: ordinary restart again leaves the built-in keyboard nonworking. Do not treat any experimental firmware here as a confirmed fix.

This repository preserves the original investigation, updater reconstructions, experimental firmware generators, tests, findings and owner-supplied evidence. The local research copies were archived before cleanup; a portable REA/Ghidra folder was kept separately for the owner.

## Start here

- [Final case status and chronology](FINAL-STATUS.md)
- [Complete preservation archive and restore instructions](ARCHIVE.md)
- [GitHub release containing all raw files and portable tools](https://github.com/AMIRSRAD/Y540-Keyboard/releases/tag/preservation-2026-10-13)
- [Latest fix9/exp3 source and limitations](research/outputs/fix9/README.md)
- [Last hardware attempt and corrected outcome](research/outputs/fix9-attempt1/findings.md)
- [Original handover](HANDOVER-SUMMARY.md) — historical; superseded where FINAL-STATUS says otherwise.

## Source layout

- `updater/`: latest fix9 reconstructed host updater C source and offline tests.
- `history/`: the earlier published updater source history; fix8 preserved before updating the main view.
- `firmware-exp2/`: historical exp2 generator/model, with a known recovery defect. Do not deploy it.
- `analysis/` and `analysis-history/`: previous analyses, retained with their uncertainty and historical conclusions.
- `research/outputs/`: project source, scripts, reports and receipts from the local investigation, including fix1–fix4, reset audits, proposals and fix9.
- `research/work/`: project-authored scratch analysis/build scripts and parser work that contributed to the investigation.
- `archive/`: lossless archive builder/restorer, complete file indexes, checksums and verification receipts.

Binary firmware samples, raw USB ETLs, flash backups/dumps, original installers/BIOS/board files, portable releases, handoff folders, REA/Ghidra runtimes and the original large handoff RAR are preserved in the release's content-addressed archive. They are not silently omitted because of `.gitignore` or Git file-size limits. See ARCHIVE.md for exact scope and reconstruction.

## Build and interpretation

The host updater is a reconstruction, not Lenovo's original source. The MCU images are binary patches, not a complete recovered firmware source tree. Successful programming/readback did not establish successful keyboard repair.

For a complete reproducible local snapshot, restore the archive's `workspace` root and use `workspace/outputs/fix9/build.ps1`. That snapshot includes the exact samples, upper-flash dependency bytes, generators and verification receipts. The default Git checkout intentionally keeps binary payloads in release assets; the C build expects samples restored beside its build script.

All device actions belong on the affected Lenovo, not the development PC. Archived executable files are historical artifacts, not instructions to run them. No further firmware experiment is endorsed by this preservation commit.
