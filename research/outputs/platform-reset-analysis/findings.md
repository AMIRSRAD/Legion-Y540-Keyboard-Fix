# Platform reset investigation — 2026-10-13

The BIOS comparison did not reveal a verified keyboard reset fix. Decoding the supplied reference board did identify the keyboard power switch and reset network, providing specific measurement targets instead of another speculative firmware write.

## BIOS/ACPI comparison

All three supplied Lenovo packages (BHCN35WW, BHCN36WW, BHCN45WW) have valid Authenticode signatures on the analysis host. Hashes are in package-manifest.json. Inno/7z extraction and firmware-volume parsing were static; installers and flash utilities were not executed.

38 unique checksum-valid DSDT/SSDT tables were recovered per package. BIOS35 vs36: 37 identical, including the DSDT; only NvdPegTb differs. BIOS36 vs45: 37 identical, with the DSDT differing. The disassembled 35-to45 DSDT change is confined to BAT0 battery code: additional SystemMemory fields and guarded accesses using a SystemIO index/data pair. HS09, _PTS and _WAK have no changes in that diff. Diff and table inventories are in acpi/.

The DSDT's HS09 device declares address, capabilities and physical location, without a local reset/power method. This does not prove no platform reset method exists elsewhere. Firmware can patch/load tables at runtime; these are package templates, not live ACPI dumps. Standalone iASL disassembly has external-name warnings retained in work; no recompiled AML or ACPI override is supplied. No independently verified main-EC firmware payload was identified in this bounded extraction. EC=0/UpdateEC Flag=0 in update configuration is not proof that EC-related code is absent from BIOS modules.

Thus there is no evidence here to recommend BIOS35/36/45 flashing as a demonstrated keyboard repair. SMM/native firmware behavior was not exhaustively compared.

## New board evidence

The accepted direct-handle TVW decode places IT8176 at U22 and a SY6288D20AAC power switch at U23. U23 supplies the keyboard rail, controlled through zero-ohm RE102 by PCH_PWR_EN, which also connects to main EC UE1.126 and other platform circuitry. The keyboard reset net connects to a 10K/1U/diode network tied to its supply. Exact reference-board connections, parser provenance, and limitations are in board-connectivity.md.

The first coordinate-based parser's pin mapping was rejected after a datasheet mismatch. A second parser using direct pin/pad references resolved it; all five switch pins agree with the manufacturer's exact-part datasheet. This correction matters: do not use provisional coordinate pin numbers.

## Repair status

fix2's successful reflash and identical pre-update image remain established. The startup failure persists. We now have a concrete circuit to test, but no confirmed failed component or firmware instruction. An automatic software power-cycle tool is not justified: the identified enable is shared, and its EC access semantics are unknown.

Next evidence must distinguish a bad supply/reset transition from valid electrical conditions with failed controller USB processing. The focused measurement handoff in board-connectivity.md specifies this. Repeating the same flash or software inventory does not resolve that question.

No BIOS/EC/keyboard firmware image was patched or flashed in this investigation. The actual repair remains unresolved.
