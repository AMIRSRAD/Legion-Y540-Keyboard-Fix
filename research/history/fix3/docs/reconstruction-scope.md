# What the self-compiled executable replaces

The reconstruction target is a Windows userspace keyboard firmware updater. The supplied artifacts do not contain original project source, a standalone kernel driver, or firmware source. Building our own updater EXE is achievable without reproducing the original compiler output. Recompiling the original EXE byte for byte, rebuilding the keyboard firmware from source, and proving hardware-equivalent operation are separate outcomes and are not established by the current work.

## Original artifact roles

| Original artifact | Observed role | Reconstruction boundary |
| --- | --- | --- |
| `ite1fw11s.exe` | Inno Setup installer; embeds updater, INI, firmware, wrapper and launcher | Packaging is optional for a portable self-compiled updater; original installation logic is not recovered |
| `IT/ITESHFU.exe` | Native x64 Windows GUI program; VCL/System and Clang runtime symbol names; HID/SetupAPI imports | Implement protocol and supported workflows in readable native source; original VCL GUI/runtime is not copied |
| `TVSU.exe` | Additional 20,480-byte PE program invoked by launcher | Internal orchestration remains unknown; not equivalent to XML-listed `tvsu_check.exe` |
| `Update_FW.bat` | Invokes TVSU; text contains immediate system shutdown on success branch | Original launcher is not required for compiling the replacement |
| `IT/SHFU.ini` | External update settings | Preserve documented parsing/default behavior for supported settings; trace defaults before claiming parity |
| `IT/44.bin` | Supplied 54 KiB device firmware image | Treat as input bytes; no firmware source reconstruction or firmware rebuild is claimed |
| Lenovo XML | Describes package and separately listed external files | Installer identity matches; some external entries differ from embedded contents |

`docs/package-identity.md` and `evidence/package-identity.json` provide static extraction inventory and exact hashes. Innoextract reported two launcher entries, retaining the later one. The original installer was not executed. This inventory does not recover installation scripts or all conditional installer actions.

## Source replacement acceptance boundaries

The repository's native implementation is a replacement assembled from recovered behavior and explicit implementation choices. The baseline for calling it self-compilable is a documented build producing a Windows EXE from local readable source with declared dependencies. The baseline for protocol correctness is offline byte-exact command fixtures, checksum checks, and state/error-path tests tied to static evidence. Compilation alone does not establish safe hardware flashing or equivalence to all original branches.

The original application includes device enable/disable/remove/rescan functions, hub handling, GUI timers, version registry writes, configuration defaults, retry policies, and multiple update paths. Their presence is demonstrated by retained symbols; exact semantics require decompiled callers and control-flow evidence. A replacement can initially support the supplied Y540 profile without claiming compatibility with every ITE chip/profile accepted by the original.

An exact original rebuild would additionally require the missing original source and resources, project/compiler settings, link dependencies, and signing material. Debug symbols and decompiled pseudocode help reconstruct behavior but are not the original source tree. The original's VCL/System symbols and `__clang_call_terminate` are consistent with a Clang-based C++Builder/VCL build; the exact toolchain/version is not established here.

## Original symbol map

`tools/coff_symbols.py` reads the PE's COFF table and resolves long section names, original symbol strings, section-relative values, RVAs, virtual addresses and raw file offsets. It never executes the target and has no third-party dependencies. Its output is `evidence/coff-symbols.json`, bound to SHA-256 `afcca3de209ccfab256aff48b8f7f59dfb6cd6a27b22fc58a41b50f0bd8bb8fa`.

The PE contains 20,262 symbol records, all without auxiliary records in this sample. Seventy-seven symbols map to executable-section addresses in `[0x400000,0x420000)`, including runtime symbols. Symbol type values are zero in the relevant records, so executable-section membership alone is not proof of a callable function; the functional labels below are identifiable original mangled names and should be corroborated with native analysis. Names are displayed in a shortened readable form; exact originals remain in JSON.

**Global address caveat:** COFF records for merged BSS subsection symbols retain subsection-relative values, so naive `.data RVA + value` addresses can be wrong. The `.text` addresses below agree with native analysis, but globals must use DWARF `DW_OP_addr` or independently corroborated addresses. `evidence/initial-globals.json` and `docs/initial-globals.md` resolve the requested global addresses and initial bytes.

| VA | File offset | Original name, shortened |
| --- | --- | --- |
| `0x404A50` | `0x4250` | `RemoveDevice` |
| `0x405270` | `0x4A70` | `RescanDevice` |
| `0x4055D0` | `0x4DD0` | `GetBcdDeviceNumer` |
| `0x405D60` | `0x5560` | `DisableEnableDevice` |
| `0x406D30` | `0x6530` | `WinMain` |
| `0x407320` | `0x6B20` | `TForm1` constructor |
| `0x4073F0` | `0x6BF0` | `SaveShfuLog` |
| `0x407A40` | `0x7240` | `GetHIDDevicePath` |
| `0x407D10` | `0x7510` | `CheckIfOurDevice` |
| `0x4089D0` | `0x81D0` | `ConnectHIDDevice` |
| `0x409CC0` | `0x94C0` | `WinDebugReadRegByteForBootcode` |
| `0x409E80` | `0x9680` | `HidRequests` |
| `0x40A280` | `0x9A80` | `HidCustomCmdInit` |
| `0x40A620` | `0x9E20` | `cmd_clear_buffer` |
| `0x40A690` | `0x9E90` | `cmd_set_data` |
| `0x40A7A0` | `0x9FA0` | `cmd_erase_flash` |
| `0x40A830` | `0xA030` | `cmd_save_to_flash` |
| `0x40A8C0` | `0xA0C0` | `cmd_wd_reset` |
| `0x40A910` | `0xA110` | `cmd_get_buffer_checksum` |
| `0x40AA50` | `0xA250` | `cmd_read_from_flash` |
| `0x40AB30` | `0xA330` | `write_flash` |
| `0x40AEF0` | `0xA6F0` | `read_flash` |
| `0x40B260` | `0xAA60` | `CalculateWordCheckSum` |
| `0x40B790` | `0xAF90` | `WriteFWVersionToRegistry` |
| `0x40B8E0` | `0xB0E0` | `load_code_flow` |
| `0x40EC20` | `0xE420` | `ConnectHub` |
| `0x40F9A0` | `0xF1A0` | `TForm1::GetBinFileInfo` |
| `0x40FCC0` | `0xF4C0` | `TForm1::Button1Click` |
| `0x40FFC0` | `0xF7C0` | `TForm1::Button2Click` |
| `0x410430` | `0xFC30` | `TForm1::Button3Click` |
| `0x410570` | `0xFD70` | `TForm1::DeviceChange` |
| `0x4105B0` | `0xFDB0` | `TForm1::FormClose` |
| `0x4107E0` | `0xFFE0` | `TForm1::Timer1Timer` |
| `0x412C40` | `0x12440` | `TForm1::Timer4Timer` |
| `0x41FB80` | `0x1F380` | `TForm1::FormCreate` |

These offsets use image base `0x400000`, `.text` RVA `0x1000`, and `.text` raw offset `0x800`. They match the already traced HID/checksum function addresses in `docs/updater-trace.md`. Native REA Evidence IDs for those traced functions remain in that document; this symbol-table extraction is independent Python evidence.

```powershell
python tools/coff_symbols.py samples/ITESHFU.exe --output evidence/coff-symbols.json
```

## Completion still requiring evidence

Full supported-profile parity requires complete initialization defaults, boot handshake, main update ordering, status interpretation, erase behavior, verification, reset, and failure/retry behavior. Device testing would be separate from the current static/offline work. Firmware internals such as keyboard scanning and debounce remain another reverse-engineering track and are not necessary merely to compile a host updater EXE.
