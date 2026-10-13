# Complete preservation archive

The final outcome is **unresolved**. See [FINAL-STATUS.md](FINAL-STATUS.md) for the corrected owner report. This archive preserves unsuccessful work for independent review; it is not an endorsement to flash an experimental image.

## Where the bytes live

Browsable source, documentation and attempt history are in this repository. Full original files, including firmware binaries, executables, logs, USB traces, Ghidra projects, toolchains, previous handoff packages and duplicate directory layouts, are preserved as release assets:

https://github.com/AMIRSRAD/Y540-Keyboard/releases/tag/preservation-2026-10-13

The release uses content-addressed ZIP parts. They are blocks of an archive, not individually reconstructed folder trees. Download all assets into one directory and use the supplied Python script. Identical content is stored once, while every original file path has its own indexed record.

The archive includes the entire research workspace, Desktop KeyboardFirmware-Issue, Tries, logs, original Lenovo updater folder, retained portable REA folder, Desktop BIOS installer and return-to-exp1 recording ZIP. `archive/ARCHIVE-SUMMARY.json` supplies exact counts and root aliases. `archive/file-index.jsonl.gz` lists every file with its SHA-256, original relative path, size and ordered blocks. `archive/object-index.json.gz` maps blocks to release parts. Raw records retain original device identifiers and Windows paths.

## Verify or recover

Use Python 3.11 or newer. No archived executable or firmware is run by these commands.

```powershell
gh release download preservation-2026-10-13 --repo AMIRSRAD/Y540-Keyboard --dir .\y540-archive
python .\y540-archive\restore_archive.py --archive-dir .\y540-archive --verify-only
python .\y540-archive\restore_archive.py --archive-dir .\y540-archive --destination .\y540-recovered
```

The destination must be new. Recovery checks part, block and complete-file hashes, preserves empty directories and file timestamps, and refuses to overwrite files. Symlinks are recorded as metadata files rather than recreated as pointers. Windows ACLs, installed services and operating-system settings are not claimed to be preserved.

To recover only the latest attempt, add `--root workspace --prefix outputs/fix9` to the restore command. Directory root aliases prevent similarly named source folders from overwriting each other.

## Scope and exception

No regular file in the selected available roots was intentionally omitted from the content archive. The smaller browsable `research/` tree is curated; its filters do not apply to release assets. Existing Git history is retained without rewriting it.

The owner explicitly waived the unavailable `E:\Sala\fix9-recording-20261013T115002055Z.zip`. It is **not preserved**. Its Desktop application logs and pre-erase backup are preserved. See [PRESERVATION-EXCEPTIONS.md](archive/PRESERVATION-EXCEPTIONS.md).

Local cleanup is conditional on complete archive reconstruction verification and comparison of every asset's SHA-256 with its GitHub-stored digest (with download/readback fallback). Initial parts are also downloaded back and compared. Receipts distinguish actual downloads from server-reported digests. The Desktop `rea-rea-agents-6.4.0` is retained with Ghidra, Java, Node and relative-path launchers. Cleanup covers the named research copies, not unrelated Desktop files or shared installed tools.
