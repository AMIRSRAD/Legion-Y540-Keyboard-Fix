# Update state machine recovered from the shipped executable

These are static observations of `ITESHFU.exe` SHA-256 `afcca3de209ccfab256aff48b8f7f59dfb6cd6a27b22fc58a41b50f0bd8bb8fa`. They do not establish device acceptance. No hardware operation was performed to derive this document. Function names, globals and control flow are Ghidra reconstructions, not recovered original source.

## Evidence

| File under evidence/decompiled | VA | Evidence ID |
|---|---|---|
| 030-connect.c | 0x4089d0 | ev_7cc3999b3ca15069693099660667a52b139fc83d3c0d50a086eeffb05b426860 |
| 103-update-button.c | 0x40ffc0 | ev_895a0dce07dfe002b129280b0b40b797ed49c9cc171ce5cdb664c231812bb6d1 |
| 110-protocol-409cc0.c | 0x409cc0 | ev_259810e6d186b8f28376c5757e01da78213741ecb2fd2a62f6cefed7d1fd5c84 |
| 111-protocol-40a280.c | 0x40a280 | ev_fd5cef455511f38958e586f0c63ecf627ff68d3d1ca88e0a045f3270e297dd99 |
| 117-protocol-40a910.c | 0x40a910 | ev_3f14e3762bc3984cd60b38146278cceba1bf5b68ae0087f6dcba404a5b5b1ade |
| 033-writeflash.c | 0x40ab30 | ev_0ec97c6a7a23c2807143087e87132b7fd3e110afdcfe39bd3e2930e9f8560e4c |
| 119-protocol-40aef0.c | 0x40aef0 | ev_f0769a257046630fc1bb86097fd64039f7a366f6a7181fa611f08f671c59dbe3 |
| 120-protocol-40b8e0.c | 0x40b8e0 | ev_540c1379522c8ad1d3bdce2018b380face98576398d13818a670c1ee262a3860 |
| 130-formcreate.c | 0x41fb80 | ev_bd2a063ba6a2ef5456a4fcd9720823340cf223b0b0c2d0dc8e021c01b4dfb967 |
| 131-timer-update.c | 0x4107e0 | ev_1fae91709c936fa7b727cbb9a528d32691eb9c35860542a1f11e6fc6f8efb8a4 |
| 132-auto-update.c | 0x412c40 | ev_0359cc80f3ca5ed016cdd2e5474e0816aac312e41a4e2fcf57446b49b58669ce |

`120` has type-propagation and function-boundary problems: after `LAB_0040ebc0` and exception-unwind handling, apparent `ConnectHub` logic is merged into the pseudocode. Its mode-handling tail is useful corroboration with `103`/`131`, but must not be treated as the normal continuation of `load_code_flow`. `131` also contains a bad-instruction tail after the recovered state switch. Assembly should resolve any decisions dependent on these boundaries.

## Discovery and entry to boot mode

The sample requests main HID VID/PID `048D:C100`, usage page/usage `FF89:0010`, and boot HID `048D:89DB`, usage page/usage `FF89:00DB`. The reconstruction matches all four identity fields, keeps the selected interface path, and rejects ambiguous matches. The vendor opens HID interfaces with requested access zero and shared read/write; feature operations are not normal stream reads/writes.

The apparent `ConnectHub(1)` tail first tries main mode, then boot mode if main is absent. Main custom-command initialization (`111`) sends 15 bytes containing `ITE Tech. Inc.` including its terminating NUL, using `ITEReportID`; waits 100 ms; gets 15 bytes; waits 100 ms. When enabling, a nonmatching echo causes one additional send/get exchange. A final comparison must match the key. Disabling uses the same exchange as a toggle and expects the resulting echo not to match. The connection tail retries initialization with report ID `5A` when the initial report ID fails. The ordinary boot flash commands use report ID zero.

Main-to-boot button handler (`103`) sends payload starting `09` with length **two**, using `ITEReportID`, sleeps 1000 ms, disconnects handles, waits `DelayMSec`, optionally removes/rescans the configured boot device, and reconnects. The second payload byte is not initialized in the decompiled scalar declaration: using `00` there is an explicit reconstruction choice pending assembly confirmation. Do not confuse this path with `C4`, which resets from the boot updater.

When boot chip-ID checking is configured (`030`), addresses `F0:20:00` and `F0:20:01` are read. `110` sends `{07, low, middle, high, 03}`, receives eight payload bytes, validates echoed address bytes 1..3 and byte 4 equal to `03`, and returns data bytes 5..7. The first byte from each register read forms the big-endian chip ID. Expected `8171` and `8176` have an explicit interchangeable compatibility branch. There is a decompiler-visible three-byte copy into a two-byte `BootChipID` array; a safe reimplementation uses separate three-byte temporaries and retains the first byte from each. The register helper retries until more than 100 failed transactions. It also has an upper loop bound of 1000 with step 3; the failure-count bound is normally reached first.

## Timer states

The following interpretation of button enabled-state tests is supported by the connection tail: Button2 identifies main mode and Button3 boot mode.

| FlashState | Observed action / transition |
|---|---|
| 0 | Clear status, call ConnectHub(1), advance to 1. |
| 1 | Repeated discovery and increment TimerCunt. Main present/boot absent advances to 2; boot present/main absent advances directly to 4. Exceeding MaxStateCunt stops with ReturnValue 01. At halfway+1, non-docking mode performs disconnect, configured wait and optional rescan, then ConnectHub(2). Docking mode instead invokes Timer4Timer after halfway. |
| 2 | Update version display, stop discovery timer, reset TimerCunt, invoke Button2Click to enter boot mode, then advance to 3. |
| 3 | Wait for boot identity; boot present advances to 4. Exceeding MaxStateCunt stops with ReturnValue 03. At halfway+1 repeat disconnect/wait/optional boot-device removal/rescan/ConnectHub(2). |
| 4 | Stop update timer, run load_code_flow. ReturnValue 10 restarts discovery; zero displays completion. Docking mode advances to 5 and enables timer again. The decompiler shows fallthrough into case 5 even outside docking mode. |
| 5 | Refresh main connection, waiting until no relevant device is present; then reset FlashState and TimerCunt to zero. |

The timer interval itself is not recovered here; `MAXSTATECUNT=15` is a count, not an established 15-second deadline.

## Normal load-code flow (SpecialFlow zero)

1. Require a nonempty in-memory firmware stream. With `UPDATEONLYPARAMETER=0`, calculate sector count as `ceil(image_size/1024) - UPDATESTARTADDRESS/1024`; reject a negative result with ReturnValue `A1`. Firmware file size and checksum validation occur in the file-load path described in `updater-trace.md`.
2. Read 32 current firmware bytes at `OEMVEROFFSET` and retain the corresponding image bytes for version display. Read device flash `[0,0x800)` into a second buffer. Unless `NOCHECKIVT` is enabled, compare image and device offsets 4..0x7FF, excluding `87`, `8D`, `1D`, `1E`, `1F`; mismatch exits with ReturnValue `A3` before erase/write.
3. Attempt the complete erase/write/compare sequence `PROGRAMFAILRETRY + 1` times. With the supplied value 1, that is two attempts.
4. If `NEEDERASE` is nonzero, send `C2, address_le24, sector_count_le16`, then wait 5 ms.
5. For a normal image, call write_flash with `PassOrWriteFirst1K=1` to skip block zero, then with `=2` to write only block zero; restore zero. Thus the first 1 KiB is committed **last**. These indices are relative to the requested update start, not necessarily absolute address zero.
6. Each non-FF staging block: clear with `C0`; send `C1` chunks of at most 57 bytes; request `D0`, read three bytes and compare little-endian checksum bytes 1/2 against the 16-bit sum of the local 1024-byte staging buffer; commit with `C3, address_le24, 00,04`; wait 5 ms. Optional `WRITEFLASHDATADELAY` follows each C1. An all-FF block is skipped.
7. Read back the entire requested range through `D1` transactions of at most 56 bytes. Payload is `D1,address_le24,length,data...`; send and receive lengths are `length+5`. Copy data from payload offset 5. Compare byte-for-byte against the image, including blocks skipped because they were all FF.
8. On mismatch, save the current readback as a backup and issue a recovery C2 erase. If `PROGRAMFAILERASESKIPFIRST1K=0`, erase the original range. Otherwise erase from `UPDATESTARTADDRESS+0x400` for `total_sector-1` sectors. Wait 5 ms. This recovery erase happens even after the last allowed failed comparison. Continue the next complete attempt if one remains.
9. On success, always send C4 reset. When `REMOVERESCAN` is enabled wait approximately 1001 ms, disconnect, wait `DelayMSec`, remove configured main identities, wait half-delay, rescan, wait half-delay, reconnect main. The vendor global result becomes zero.
10. After all failed comparisons, send C4 only if `PROGRAMFAILERASETHENRESET` is nonzero and wait approximately 1001 ms. Result is `10`. The erase in this option's name was already performed by mismatch recovery; the terminal branch itself sends reset only.

For `UPDATEONLYPARAMETER=1`, total sectors are `ceil(image_size/1024)` and the entire source image is mapped at UPDATESTARTADDRESS. The OEM/IVT precheck is skipped and the special first-block-last two-pass write is not used.

## Other SpecialFlow modes

`1` and `3` skip erase/write and dump readback to `flashbin.000`. Mode 1 still compares with the source image; mode 3 does not compare and reports success. Mode 2 performs erase when enabled, skips writing, skips readback, and sets success. The shared final success branch sends C4 even for these modes. These observations explain modes but do not justify exposing or silently selecting them in a normal updater.

## Sample configuration values that affect behavior

| Section / key | Supplied value | Meaning in the recovered path |
|---|---|---|
| MAIN/HWID; BOOT/HWID | 048D:C100;048D:89DB | Device identity strings |
| NEWVERSION/MAINDEVICEUPID,MAINDEVICEUID | FF89,0010 | Main usage page/usage, hexadecimal |
| NEWVERSION/BOOTDEVICEUPID,BOOTDEVICEUID,BOOTDEVICECHIPID | FF89,00DB,8171 | Boot selector and chip-ID check, hexadecimal |
| NEWVERSION/UPDATESTARTADDRESS,UPDATEFILESIZEKB,UPDATEONLYPARAMETER | 0,54,0 | Full 54-KiB image beginning at zero |
| NEWVERSION/CHECKSUMSTARTADDRESS,CHECKSUMENDADDRESS | 0400,D800 | Half-open checksum interval |
| NEWVERSION/CHECKSUMVALUEHIGHADDRESS,CHECKSUMVALUELOWADDRESS,CHECKSUMINVERT | 7FFE,7FFF,1 | Stored big-endian checksum and negation |
| DEVICE/NEEDERASE,PROGRAMFAILRETRY | 1,1 | Erase and two total attempts |
| OPTION/PROGRAMFAILERASESKIPFIRST1K,PROGRAMFAILERASETHENRESET | 1,1 | Preserve first sector during mismatch recovery, reset after final failure |
| OPTION/NOCHECKIVT | 1 | Skip IVT comparison, but original still performs initial flash reads |
| OPTION/OEMVEROFFSET | 3100 | Offset of 32-byte version field, hexadecimal |
| OPTION/ALLHIDCOMMANDDELAY,WRITEFLASHDATADELAY | 5,0 | Milliseconds before feature operation / after C1 |
| DELAY/MSEC; OPTION/MAXSTATECUNT,MAXSCANDEVICE | 6000;15,100 | Reconnection delay; timer-count/discovery limits |
| DEVICE/REMOVERESCAN,DOCKINGBURN,MAININDEX | 1,0,0 | Vendor rescan enabled; single-unit workflow; selected main handle index |

`SpecialFlow`, `CheckSum_LastBytesBeFF`, and `ITEReportID` are absent from the supplied INI. Separate PE/DWARF analysis locates SpecialFlow at `8CB9C0` and CheckSum_LastBytesBeFF at `8CBBB4` in the loader-zero-filled portion of .data, and ITEReportID at `8AD5D0` with initialized value `5A`. See `evidence/initial-globals.json` and package identity documentation for the mapping evidence. `132` reads REPORTID with the current global's decimal string as fallback, so the supplied profile retains `5A`; the exact supplied-profile handshake should start with `5A`. It reads CHECKSUMLASTBYTESBEFF with default literal at `6E09BF`, verified as ASCII `0` followed by NUL at file offset `2DF5BF`; absent key therefore becomes zero. SpecialFlow modes 1/2/3 are selected by command-line parameter checks in `132`, whose argument literals were not propagated into the pseudocode.

`130` FormCreate only reads MESSAGE/ENABLE and OPTION/TITLENAME, plus requests execution-state `80000043`. `132` Timer4Timer performs the extensive flash-configuration loading. With CHECKSUMMODE=1 and UPDATEONLYPARAMETER=0 it validates both the checksum residual and exact UPDATEFILESIZEKB before enabling Timer1. DONOTUPDATETHESAMEVERSION=1 additionally compares current/image OEM version strings in main mode; the supplied value zero bypasses that policy. This automatic-selection routine also contains project/file-selection and optional Chicony/docking branches that are not part of the normal supplied single-image profile. Its decompiler warnings and lost argument expressions preclude claiming complete GUI or command-line equivalence from this view alone.

## Intentional reconstruction differences and unresolved equivalence

The original often ignores HidRequests return values. A reimplementation should propagate transport errors rather than treat an old/zeroed buffer as a successful read. Zero-initialized report padding, explicit bound checks, safe chip-ID buffers, explicit duplicate-device selection, and padding a final partial block are reconstruction choices. In particular the vendor read/write helper return behavior does not prove that an ignored API error results in a valid device transaction. GUI rescan and docking automation also depend on additional Windows device-management helpers. A compiled executable and offline fake tests demonstrate buildability and modeled control flow, not physical flashing equivalence or recovery safety.
