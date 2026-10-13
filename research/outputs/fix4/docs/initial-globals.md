# Original loader initial values and INI fallback

`evidence/initial-globals.json` records original DWARF variable locations and type widths plus PE-backed initial bytes. It covers 70 named application globals, retaining their raw DWARF records, and four local-variable records for the two 8910 flags. Array widths without explicit size remain unresolved; the script does not mistake element size for array size. This is independent offline file evidence, not REA execution evidence.

The installed `C:/Strawberry/c/bin/objdump.exe` is GNU Binutils 2.42. It statically dumped the updater's debug info without executing the updater. `tools/inspect_initial_globals.py` parses the dump and maps absolute `DW_OP_addr` locations through the PE section headers. The complete dump is disposable work data; selected raw records and the dump SHA-256 are retained in the JSON for provenance.

## Confirmed initial values

| Variable | DWARF VA | Width | Initial value | Storage |
| --- | --- | ---: | ---: | --- |
| ITEReportID | `0x8AD5D0` | 1 | `0x5A` | File byte `5A` |
| MainIndex | `0x8CB98C` | 4 | 0 | Loader zero fill |
| NoCheckIVT | `0x8CB9A8` | 4 | 0 | Loader zero fill |
| SpecialFlow | `0x8CB9C0` | 4 | 0 | Loader zero fill |
| AllHidCommandDelay | `0x8CB9CC` | 4 | 0 | Loader zero fill |
| Update_OnlyParameter | `0x8CBB98` | 4 | 0 | Loader zero fill |
| CheckSum_LastBytesBeFF | `0x8CBBB4` | 4 | 0 | Loader zero fill |
| NoCheckPID | `0x8CBBB0` | 4 | 0 | Loader zero fill |
| DelayMSec | `0x8AD5D4` | 4 | 2000 | File bytes |
| PassClose | `0x8AD5D8` | 4 | 1 | File bytes |
| RemoveRescan | `0x8AD5DC` | 4 | 1 | File bytes |
| CheckSumMode | `0x8AD5E8` | 4 | 1 | File bytes |
| NeedErase | `0x8AD5EC` | 4 | 1 | File bytes |
| MaxStateCunt | `0x8AD5F8` | 4 | 10 | File bytes |
| MaxScanDevice | `0x8AD5FC` | 4 | 256 | File bytes |
| OemVerOffset | `0x8AD600` | 4 | 3100 decimal | File bytes |

The last example demonstrates why these are initial values only: the supplied profile parses its `OEMVEROFFSET=3100` as a hex value `0x3100`, while the compiled initial integer is decimal 3100 (`0xC1C`). Constructors, command-line parsing and INI reads can override globals after loading. `ProjectNameIndex` and `MainBootMode` initially contain `FFFFFFFF` (signed -1).

The PE `.data` section spans VA `0x8AD000`, virtual size 335,428 bytes, with 122,368 file-backed bytes at raw offset 4,896,256. Its file-backed range ends at VA `0x8CAE00`; its virtual range ends at `0x8FEE44`. All requested zero-filled globals above lie wholly between these limits, so there are no file initial bytes to read for them. They start zero under PE loader mapping. This does not show their final configured values.

`Have8910BXBBK` and `Is8910BXVersion` are stack locals, each appearing twice in DWARF with `DW_OP_fbreg` locations. They are not global zero-filled storage. Their initialization and branch effects must come from native function analysis, not assumptions about `.bss`.

## LastBytesBeFF absent-key fallback

`TForm1::Timer4Timer` at `0x412C40` uses `DAT006E09BF` as the INI read fallback for LastBytesBeFF. Independent PE bytes at VA `0x6E09BF`, raw file offset `0x2DF5BF`, are `30 00`, ASCII `0` followed by NUL. `evidence/initial-globals.json` retains this focused byte observation; the native call relationship is in `evidence/decompiled/132-auto-update.c` and complete REA Evidence `ev_0359cc80f3ca5ed016cdd2e5474e0816aac312e41a4e2fcf57446b49b58669ce`. This supports numeric zero for the absent-key fallback, beyond the initial loader-zero observation. Later code could still change state; profile interpretation should use the recovered execution path.

## COFF limitation discovered

Many uninitialized symbols retain offsets relative to a BSS subsection merged into `.data`. Applying the initialized `.data` base to every COFF symbol gives misleading addresses and arbitrary file bytes. For the requested globals, DWARF locations show the BSS subsection base `0x8CAC50`; initialized symbols such as ITEReportID use `.data` base `0x8AD000`. Do not use the naive global VAs from `evidence/coff-symbols.json` as default-value evidence. Its text function mappings remain consistent with native analysis.

## Further useful original entry points

The full COFF map locates `CheckParameters` at `0x4227E0`, `TForm1::Timer2Timer` at `0x4205A0`, `Timer3Timer` at `0x422040`, and `Timer5Timer` at `0x4232C0`. Config loading is already found inside the large `Timer4Timer` path. These labels identify candidate code for additional tracing; they do not establish its behavior by themselves.

## Reproduce

From the chat workspace:

```powershell
& 'C:/Strawberry/c/bin/objdump.exe' --dwarf=info outputs/y540-research/samples/ITESHFU.exe > work/package-identity/dwarf-info.txt
python outputs/y540-research/tools/inspect_initial_globals.py --dwarf-info work/package-identity/dwarf-info.txt --output outputs/y540-research/evidence/initial-globals.json
```

The target SHA-256 is `afcca3de209ccfab256aff48b8f7f59dfb6cd6a27b22fc58a41b50f0bd8bb8fa`. No vendor program, firmware, batch script or device operation is executed by these commands.
