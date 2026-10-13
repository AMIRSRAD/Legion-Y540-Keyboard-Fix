# Finding ledger

## fix1 case and implementation

The original ledger below describes the baseline investigation. Current case observations are in [case-evidence.md](case-evidence.md), and current updater behavior/evidence/limits are in [fix1-changes.md](fix1-changes.md). Working C100/HID nodes become historical while a present problem43 descriptor placeholder appears on the same parent/port. This supports a USB enumeration failure, not a proved erased image or a proved AC-specific component fault. The new updater repairs failure paths, requires a durable consistent backup, correlates physical identity, and adds an explicit targeted USB restart experiment. Offline tests pass; no runtime hardware outcome or permanent repair is claimed.

## Baseline ledger

| ID | Finding | Evidence | Status |
| --- | --- | --- | --- |
| F01 | Supplied updater is native x86-64 PE; 19 segments, 22,976 procedures, 39,151 strings | baseline/updater-rea-evidence.json; `ev_025931690b009c0de7a5e941703e403feba63dbd459d7dbe61c01a2cf79fcc13` | Observed by REA/Ghidra |
| F02 | Firmware is 54 KiB and contains version 00000044 at file offset 0x3100 | baseline/file-facts.json; samples/manifest.json | Observed by byte reads |
| F03 | Embedded USB descriptor specifies 048D:C100; product string ITE Device(8910) | baseline/additional-facts.json; 44.bin offsets 0x5307, 0x536B | Observed by descriptor decoding |
| F04 | HID feature-report APIs and SetupAPI device-discovery APIs are imported | baseline/additional-facts.json | Observed imports; exact callers pending |
| F05 | Installer matches supplied XML digest; extracted updater differs in digest and size | baseline/analysis.md; samples/manifest.json | Observed mismatch, cause unknown |
| F06 | 8051-family firmware is a candidate | baseline/analysis.md, firmware-review.md | Inference; architecture not verified |
| F07 | No separate .sys/.inf appears in the supplied folder | original supplied file inventory and samples/manifest.json | Bounded observation; embedded dependencies not excluded |

## Open questions

- What interface/report lengths and command opcodes does the updater select?
- Which routines implement checksum calculation, storage and validation?
- Does same-version behavior depend on additional config or command-line overrides?
- Does the installer produce the current extracted updater unchanged?
- Are firmware code and parameter regions distinct, and what CPU variant is used?
- Is any separate kernel driver loaded or installed, or does the application use the Windows HID stack exclusively?

No static string or configuration setting alone establishes a runtime sequence. Follow-up findings belong in updater-trace.md with their exact evidence files and addresses.

## First code-level pass

- F08: HidRequests at VA 0x409E80 uses 64-byte feature reports with report ID at byte 0 and payload at byte 1; confirmed by pseudocode and assembly. See updater-trace.md.
- F09: CalculateWordCheckSum at VA 0x40B260 implements a 16-bit byte sum with FF substitutions, optional negation, then addition of stored checksum. A caller accepts zero. Offline supplied-image residual is zero; four model tests pass. INI defaults and broader equivalence remain open.
- F10: write_flash uses 1 KiB blocks and up to 57 data bytes per cmd_set_data call. Exact whole-update state ordering remains open.

The earlier firmware-review.md numerical checksum candidate is now supported by recovered updater code; its original limited-scope conclusions are preserved as a historical pass.

## Source reconstruction checkpoint (0.2.0)

The native source implementation and build/test recipes are complete for the claimed supported profile. See build-and-test.md and update-state-machine.md. Preserve the distinction between offline/model validation and physical keyboard validation; never call emulator success a real-provider hardware result.

Package identity mismatch is resolved at the installer-payload boundary. Missing checksum defaults were recovered from DWARF/PE initialization and the actual INI fallback literal. The original first-block-last ordering, readback, retry and reset behavior is now implemented and exercised offline. Remaining full vendor equivalence questions and hardware qualification are explicit in build-and-test.md. The microcontroller firmware itself is still a supplied binary input.

## fix2: normal-mode report length

The owner-supplied update-ones log identifies a fix1 reconstruction defect: the normal FF89:0010 collection advertises 17 bytes, but open required 64. It stopped before feature I/O; the backup is empty. fix2 uses 17-byte normal transfers with ID 5A, retains 64-byte boot transfers with ID zero, and rejects invalid profiles/payloads. See ../../update-attempt-analysis/findings.md. Offline regression cases cover both profiles and handshake failure cleanup. No hardware success or startup repair is claimed.
