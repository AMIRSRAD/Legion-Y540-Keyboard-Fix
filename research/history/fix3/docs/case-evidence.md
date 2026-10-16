# Supplied keyboard case: observations and boundaries

This report is an offline analysis of all root-level notes, the collector source, both complete JSON captures, the package metadata/SHFU configuration, and file/archive inventories in `C:/Users/owner/Desktop/KeyboardFirmware-Issue`. The complete parsed comparison and SHA-256 inventory are in [case-comparison.json](../evidence/case-comparison.json). No updater, installer, BoardViewer, BIOS flasher, HID operation, driver change, device restart, or flash operation was run. These JSON/file observations are not REA execution evidence.

Reproduce the comparison from the project directory:

```powershell
python tools/compare_case_snapshots.py --case-dir 'C:\Users\owner\Desktop\KeyboardFirmware-Issue'
```

## What the captures establish

The entire failed snapshot contains 112 device records; the working snapshot contains 122. The capture timestamps **inside** the files are `2026-08-01T17:26:18.3523991+03:30` (failed) and `2026-08-01T17:31:36.1803385+03:30` (working). Filename timestamps differ and must not substitute for those fields.

| Evidence | Working capture | Failed capture |
|---|---|---|
| Normal USB instance | `USB\VID_048D&PID_C100\5&1F456139&0&9` | Same instance retained as nonpresent |
| Normal device state | Present, OK, problem 0 | Nonpresent, Unknown, problem 45 |
| Bus-reported identity | `ITE Device(8910)` | Retained property on the historical normal record |
| Normal hardware ID | `USB\VID_048D&PID_C100&REV_0044` | Retained property on the historical normal record |
| Descriptor-failure instance | `USB\VID_0000&PID_0002\5&1F456139&0&9`, nonpresent/problem 45 | Same instance, present/Error/problem 43 |
| Failed hardware/compatible ID | `USB\DEVICE_DESCRIPTOR_FAILURE` | `USB\DEVICE_DESCRIPTOR_FAILURE` |
| LocationInfo on both USB instances | `Port_#0009.Hub_#0002` | `Port_#0009.Hub_#0002` |
| Parent on both USB instances | `USB\ROOT_HUB30\4&15ed8360&0&0` | Same parent |
| C100 HID children | Five present, OK, problem 0 | Five nonpresent, Unknown, problem 45 |

The five C100 HID collections are `COL01` (vendor usage `FF89:0010`), `COL02` (vendor usage `FF89:00CD`), `COL03` (keyboard `0001:0006`), `COL04` (consumer control `000C:0001`), and `COL05` (system control `0001:0080`). Their parent is the C100 USB instance. Neither snapshot contains a `VID_048D&PID_89DB` boot-device record.

The common parent chain, matched case-insensitively, is:

```text
USB\VID_048D&PID_C100\5&1F456139&0&9
  USB\ROOT_HUB30\4&15ED8360&0&0
    PCI\VEN_8086&DEV_A36D&SUBSYS_380617AA&REV_10\3&11583659&0&A0
      ACPI\PNP0A08\0
        ACPI_HAL\PNP0C08\0
          ROOT\ACPI_HAL\0000
```

The Intel USB host controller and USB root hub are present, OK, problem 0 in both captures. The controller's LocationInfo is `PCI bus 0, device 20, function 0`. **Neither capture contains `DEVPKEY_Device_LocationPaths`.** A LocationInfo display string and instance suffix are available; no full bus location path has been measured. The comparison preserves that distinction.

Nineteen device records differ overall. Seven are the normal/failed USB pair and the five C100 HID collections. The remaining differences are storage snapshots, WAN/VPN software devices, and a Wi-Fi virtual device. Two other present devices have problem 22 in both captures (Fortinet VPN adapter and Realtek Ethernet). The captured recent events concern a PCI WUDFRd-load warning and an older display-removal warning, not an event directly identifying the C100/port-9 failure. These filtered seven-day event lists do not prove that no USB event existed elsewhere.

## Platform and power comparison

Both captures identify Lenovo model `81SX`, family `Legion Y540-15IRH`, BIOS `BHCN35WW`, Windows 11 Enterprise `10.0.26200`/build `26200`, and the Balanced power scheme. Both record `HiberbootEnabled=1`, available S3/hibernate/Fast Startup states, and no returned USB power-setting entries. An empty `UsbSettings` array does not establish the actual selective-suspend policy.

Both battery records show `BatteryStatus=2`, 100%, `Status=OK`. The collector does not record a direct AC-line-status API result or the power-source condition **at startup**. It therefore cannot independently assign these captures to AC-connected versus AC-disconnected boot. The last-boot timestamps differ: failed `2026-08-01T04:17:00.5Z`, working `2026-08-01T13:57:13.5Z`.

The owner's repeatable observations remain separate evidence: complete shutdown then boot without AC restores Windows typing; boot with AC attached fails; Fn functions still work; ordinary keys work in BIOS. The owner also reports a later successful erase/write/read/compare of firmware 44 under BIOS 35. The working `REV_0044` value is consistent with version 44 being enumerated; it is not a dump/readback proving every flash byte or proving that the firmware is free of bugs.

Fast Startup being enabled is worth recording in future controlled tests, but does not disprove the owner's reported complete shutdown. There is no evidence that toggling it is a confirmed repair. The observations also do not identify a specific physical power rail, component, BIOS routine, or firmware instruction.

## Diagnosis supported by this evidence

**Observed:** ordinary Windows keyboard failure coincides with descriptor failure on the same USB parent/port/instance suffix where a working C100 keyboard previously enumerated. The normal HID collections are not present in that failed state. The vendor screenshot's “Can not Find Device! - 1” is consistent with no normal HID target being available, but the screenshot alone does not establish what earlier updater stage ran.

**Inference:** this failure is at USB device enumeration, before the normal keyboard HID interfaces can be used. A firmware updater searching only for enumerated C100 or 89DB HID devices cannot communicate with the descriptor-failure placeholder. Selecting the placeholder as if it were an authenticated ITE HID device is invalid. Another installation of a keyboard function driver cannot be assumed to repair descriptor enumeration.

**Unknown:** whether the initiating fault is firmware USB initialization, AC-related controller state/power sequencing, host-controller interaction, platform firmware, a physical fault, or a combination. BIOS typing and surviving Fn functions demonstrate retained keyboard functionality in some environments; they do not by themselves reveal the exact input path. A successful same-image compare and a later recurrence mean “rewrite 44 and declare fixed” is not a supported conclusion. There is no authenticated replacement keyboard image in the supplied case.

## A bounded failed-devnode selector

The offline comparison finds exactly one historical candidate using all of these conditions:

1. A working normal **USB** C100 devnode is present/problem 0 in the historical working capture.
2. The candidate is a present **USB** `VID_0000&PID_0002` devnode with problem 43 and hardware ID `USB\DEVICE_DESCRIPTOR_FAILURE`.
3. Its nonempty parent and LocationInfo equal the historical normal USB device's values, case-insensitively.
4. Its instance suffix equals `5&1F456139&0&9` from that normal device.
5. There is exactly one qualifying known normal device and exactly one candidate; ambiguity or missing evidence fails closed.

This is a topology correlation, not cryptographic identity: a failed descriptor contains no valid ITE VID/PID. It can justify identifying one candidate for **an explicit, logged devnode restart attempt**, subject to fresh live evidence and the user's runtime action. It does not justify flashing, replacing its driver with a forced class driver, selecting every error-43 device, restarting the root hub/controller, removing a driver package, or touching a device based on `Port_#0009` alone. A devnode restart is a recovery experiment; success would not prove a permanent firmware repair.

For live use, first verify machine context and re-read the current target's parent, LocationInfo, hardware IDs, present state and problem code immediately before the change. Require the same topology plus one unambiguous candidate. New captures should add `DEVPKEY_Device_LocationPaths` for both normal and failed states and direct AC-line status. Match these paths too when historical evidence contains them; do not synthesize a path from a hub number. If Windows re-enumeration changes the instance identity, collect a new working anchor rather than broadening to all unknown USB devices.

## All supplied file groups considered

All files are hashed in the machine-readable inventory. The root collector and all three Markdown notes were read in full. The two JSON files were parsed in full and every device was compared. The forum note is an owner's archive summary containing anecdotal recovery attempts and links; its instructions and attachments are case data, not authorization or demonstrated fixes.

| Artifact | Size | SHA-256 |
|---|---:|---|
| Official installer `ite1fw11s.exe` | 2,835,096 | `E5863DCD12C40AFB98BD5577C3C9631F8F5F78868BC1B1125355F34637F31834` |
| `44.bin` | 55,296 | `3AFEC131C6ED70EFA0A3F4B601CB799011A582835D371C57FEF68AF48519E359` |
| Extracted `ITESHFU.exe` | 11,485,623 | `AFCCA3DE209CCFAB256AFF48B8F7F59DFB6CD6A27B22FC58A41B50F0BD8BB8FA` |
| `bhcn35ww.exe` | 8,350,344 | `B3F8D741EFFA997D4D94F4F96D014F5473550E9B7A96DBBB2B9C835FA135D305` |
| `bhcn36ww.exe` | 8,351,672 | `EF207E9A8E2507A05B8FC7B47DC9B4B7E0DA6BD25D9C211C8B44B24E161DBAC7` |
| `bhcn45ww.exe` | 7,923,040 | `F934CECC55749D57CDB1C23F77B471769CAD001D5251D697FF05C0E0FAD9CB32` |
| NM-C221 boardview RAR | 2,850,869 | `A3B54B0F6E5850AA578BCA447F5AADA7B797CD872C9F081BF6DB7E2FB5497B2C` |
| `BoardViewer.zip` | 1,447,675 | `3BF261CC55ECF64BBC8E1868C4C9256BE26840E2865A70C4625059D274621E08` |

The package's supplied XML metadata names firmware `00000044`, normal hardware ID `048D:C100` and boot hardware ID `048D:89DB` are in the supplied SHFU configuration. The configuration also includes normal vendor usage `FF89:0010` and boot vendor usage `FF89:00DB`. Package manifest verification for the preserved reconstruction samples passed. The XML's **external** `iteshfu.exe` entry gives a different size/hash from the extracted flasher, a discrepancy already documented in the baseline package identity evidence; the installer and supplied `44.bin` match the baseline. No newer flasher is presumed from that discrepancy.

Archive member inventories were obtained with `tar -tf`, without executing or extracting their programs. `BoardViewer.zip` contains BoardViewer.exe, its configuration, language files and .NET/SharpDX supporting DLLs. The RAR contains two JPEGs, a main NM-C221 boardview `.tvw`, seven `NS-C221` through `NS-C227` auxiliary `.tvw` files, and an `ORGINAL link.txt` member. The inventory is recorded verbatim. No viewer was run and no circuit diagnosis was inferred from filenames. NM-C221 is the archive label; the actual motherboard revision is not established by the captures, and reports discussing NM-C371/NM-C531 do not establish compatibility.

The three BIOS packages were inventoried as input files and hashed, not executed or fully decoded. A read-only `tar -tf` probe of `bhcn35ww.exe` could not recognize it as an archive; no conclusions about its internal modules follow. Existing technical notes describe prior extraction of BIOS45 but explicitly do not claim exhaustive firmware-module analysis. BIOS version numbers and keyboard firmware 44 belong to different namespaces. These BIOS packages are not substituted for the keyboard firmware and no BIOS update/downgrade is prescribed by this project.

## What a useful next runtime log must resolve

Capture the fresh PnP topology, direct AC-line status, process permissions, Windows version, and the exact normal/vendor HID candidates **before** any optional recovery. If a single approved failed devnode is restarted, record the exact instance ID, result/Windows error, and subsequent normal/boot/failed topology over a bounded wait. If the controller returns as C100, record all HID collections and their usage/report metadata. Firmware access and any erase/program action remain separate from a devnode restart. Pair the log with the owner's exact shutdown/AC-at-boot observation. A later log can show whether the recovery helps this machine; the current static evidence cannot establish that result.
