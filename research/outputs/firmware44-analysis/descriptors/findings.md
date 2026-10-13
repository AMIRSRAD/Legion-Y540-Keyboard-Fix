# Firmware 44 USB and HID descriptor review

Read-only analysis of `outputs/y540-research/samples/44.bin` (55,296 bytes), SHA-256 `3afec131c6ed70efa0a3f4b601cb799011a582835d371c57fef68af48519e359`. All offsets below are **file offsets**, not established execution addresses. `evidence.json` preserves every decoded HID item, raw bytes, fields, report lengths, strings and OS property. Reproduce with `python outputs/firmware44-analysis/descriptors/analyze_descriptors.py`.

## Observed structure

The device descriptor at `0x5307` is 18 bytes and declares USB 1.10, VID/PID `048D:C100`, revision `0044`, endpoint-zero maximum packet 64, manufacturer index 1, product index 2, serial index 0, and one configuration. This agrees with the working trace's already-enumerated device snapshot. Serial-like text stored elsewhere in the image does not mean the descriptor advertises a serial number; its serial index is zero.

Configuration `0x531D` totals exactly 34 bytes: configuration 9, interface 9, HID 9, endpoint 7. There is one interface and one interrupt IN endpoint `0x81`, maximum packet 64, interval 4. The interface identifies a boot keyboard (class 3, subclass 1, protocol 1). Configuration attributes `0xE0` include required bit 7, self-powered and remote-wakeup, with reserved lower bits clear. Its maximum power is 100 mA. No length/endpoint-count contradiction was found in this tree.

The HID descriptor at `0x532F` declares **161 bytes**, precisely matching the complete report descriptor at **`0x5184..0x5224`**. A bounded short-item parser consumes all 161 bytes, finds balanced collections and global stacks, no truncated/unknown/reserved items, valid nonzero report IDs, and no reversed logical ranges. This is a structural audit, not full conformance certification.

| Application collection | Report | Direction | Payload bytes | Including report ID |
|---|---|---|---:|---:|
| Vendor page FF89, usage 10 | 5A | Feature | 16 | 17 |
| Vendor page FF89, usage CD | CD | Feature | 2 | 3 |
| Generic Desktop keyboard | 01 | Input | 32 | **33** |
| Same keyboard / LEDs | 01 | Output | 1 | 2 |
| Consumer control | 02 | Input | 2 | 3 |
| Generic Desktop system control | 04 | Input | 1 | 2 |

Five top-level application collections are consistent with the five normal HID collection devnodes in the inventories. Keyboard ID 1 contains 8 modifier bits, 8 reserved bits and thirty 8-bit key array entries. Its **33-byte input report exactly matches the four successful 33-byte keyboard transfers in the working ETW capture**. No input report exceeds the endpoint's declared 64-byte packet size. Payloads were not captured, so this does not prove those transfers carried ID 1 or any particular key.

Boot subclass does not require the report-mode descriptor itself to be the fixed 8-byte BIOS boot format. Whether SET_PROTOCOL correctly switches formats is a separate runtime/code question. The report descriptor alone is not evidence of a BIOS/Windows format defect. The [USB-IF HID specification](https://www.usb.org/sites/default/files/documents/hid1_11.pdf) defines the item and boot/report protocol distinction.

An additional complete 82-byte consumer report descriptor at `0x5229..0x527A` parses as ID 1, 24 one-bit consumer controls, four bytes including ID. It is **not referenced by the one embedded configuration's HID length**, so it is not a second proven active interface. Runtime selection and any alternate device modes remain unknown.

## Concrete power-management lead, not a proven bug

An 18-byte Microsoft OS string at `0x53B4` contains signature `MSFT100`, vendor request code `0x7F`, and zero padding. An internally consistent **76-byte extended properties candidate** at **`0x53CA..0x5415`** contains:

- `dwLength=76`, `bcdVersion=0x0100`, `wIndex=5`, `wCount=1`.
- Property at `0x53D4`: size 66, registry data type 4 (DWORD), name length 48 bytes.
- UTF-16 name `SelectiveSuspendEnabled` with terminating NUL; data length 4; DWORD value **1**.

The size arithmetic is consistent: 10-byte header + 66-byte property = 76; property = 4+4+2+48+4+4. Microsoft describes OS extended properties as a supported method to enable HID USB selective suspend. This gives a specific firmware power-management path worth tracing: suspend entry, remote wake, resume and reset initialization. [Microsoft HID selective suspend documentation](https://learn.microsoft.com/en-us/windows-hardware/drivers/hid/selective-suspend-for-hid-over-usb-devices).

It does **not** establish that Windows requested/accepted this descriptor, that the current registry contains this property, that suspend caused the owner fault, or that changing 1 to 0 in firmware would fix it. Device-wide descriptor-request failures after restart can have several causes. No patch is justified by this property alone.

## Handler leads and limits

The surrounding bytes resemble compiler initialization records, including `60 A1 0A A7` before the primary report, `60 52 0B 48` before the additional report, and `60 4C 0A 1F` before the OS property. Candidate destination addresses are therefore 0AA7, 0B48 and 0A1F, pending independent init-decoder validation. A bounded raw search found bytes `0A 1F` at file `0x49C7` in addition to the initializer's `0x53C8`. Raw patterns `90 51 84`, `90 53 07`, `90 53 1D`, and `90 53 CA` were absent. These searches do not prove references absent: firmware can copy tables to RAM and use different addresses or banks.

No concrete malformed descriptor was identified. This negative result is limited to the extracted structures and parser checks above. It does not audit USB state-machine code, RAM initialization, timeouts, races, suspend/resume registers, reset vector handling, memory safety, interrupt ordering or electrical behavior. The failed ETW capture returns **zero bytes** on four device-descriptor transactions, before the HID descriptor is available. That failure cannot be explained solely by a malformed HID report descriptor.

Original firmware, updater sources and released builds were not changed. No hardware was accessed or flashed.
