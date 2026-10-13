# Keyboard power/reset connectivity — 2026-10-13

## Result and scope

The supplied **NM-C221 REV0.1 reference boardview** contains a specific keyboard power switch and a supply-derived reset network. Its component/pin connections are now decoded using direct part-to-layer pad handles, not inferred from nearby coordinates. This is reference-board evidence; the affected laptop's exact board revision and live signals remain unverified.

The first coordinate-based decoder produced wrong pin numbers, including a 24-pin rotation of U22 and a wrong U23 mapping. Those provisional assignments are rejected. Do not use `work/board-connectivity-model.json` for repair. The accepted mapping is `board-evidence/direct-pin-net.tsv` and `verified-connectivity.json`.

## Method and validation

The open-source [eagleview TVW reader](https://github.com/nitrocaster/eagleview) at commit `37bb831c8db04fe408632d92434971bf9b7eaa30` reads each part's pin handle and resolves it to the explicitly stored layer's pad index (`handle / 8`). The target header differs from the supported header, so the reader was adapted to start layer parsing at file offset 0x4E, with 22 layers; these values were checked against raw header bytes. The file begins with SILKSCREEN_TOP, SOLDERMASK_TOP, and TOP layer objects, consistent with layer index 2 used by U22/U23. Remaining parser assertions were retained. A diagnostic print was added. The patch, dump program, parser log, and resulting 16,521 pin rows are retained.

U23's five pins independently agree with the exact-part manufacturer's [SY6288C20/D20 datasheet](https://www.silergy.com/zh/download/downloadFile?ftype=note&id=4371&type=product), pages 1–2. The earlier geometric decoder failed this cross-check. The datasheet identifies D20 as active-low enable and specifies output discharge when disabled. This validates the interpreted power-switch pins, not actual board behavior.

## Accepted reference-board connections

| Component/pin | Net | Interpretation |
|---|---|---|
| U23.5 | +3VALW_IN | Switch input |
| U23.1 | +3VALW_AG | Switched keyboard supply |
| U23.2 | GND | Ground |
| U23.4 | AGKB_PWR_EN# | Active-low switch enable |
| U23.3 | AGKB_PWR_OCB | Open-drain fault output |
| RE102.1 / RE102.2 | AGKB_PWR_EN# / PCH_PWR_EN | Boardview value 0 ohms |
| UE1.126 | PCH_PWR_EN | Main EC IT8226E connection; direction/register unverified |
| U22.8, U22.18 | +3VALW_AG | IT8176 keyboard controller supply connections |
| U22.32 | AVCC3.3V_AG | Additional keyboard-controller supply net |
| U22.48 | AG_WRST# | Keyboard reset net by board name |
| U22.19 / U22.20 | USB20_N9_AGKB / USB20_P9_AGKB | Keyboard USB pair |
| R376.1 / R376.2 | AG_WRST# / +3VALW_AG | 10K resistor |
| C276.1 / C276.2 | AG_WRST# / GND | 1U capacitor |
| D44.1 / D44.2 | +3VALW_AG / AG_WRST# | RB751V-40 diode; polarity not inferred solely from net names |

All decoded AG_WRST# connections are U22.48, R376.1, C276.1, D44.2. In this reference file it is not directly connected to a separately named EC GPIO. That does not rule out chip-internal/software resets. PCH_PWR_EN also connects to Q30 and other platform components; it is not a proven keyboard-only control. See the complete net membership in the JSON evidence.

## Meaning for the failure

The supply/reset topology provides a plausible explanation for why a sufficiently deep power-off could clear keyboard state while a normal restart does not. It does **not** establish that the switch, capacitor, diode, or EC is defective. A normal restart can legitimately retain peripheral power; compatible firmware must still handle the USB transition.

No verified user-mode command or isolated EC register has been found to toggle this supply safely. An updater-level HID reset is not demonstrated to be equivalent to removing the keyboard rail. Do not manipulate PCH_PWR_EN based on this document: it is shared with other circuitry.

## Focused measurement handoff

A qualified technician should first confirm board revision and component identities against the actual laptop. Compare ordinary failed restart/shutdown with forced-off recovery while observing:

1. U23 input and output supply behavior.
2. U23 enable and fault signals.
3. AG_WRST# at the reset network, and the additional analog supply where appropriate.
4. USB reset/setup traffic if supply/reset measurements do not distinguish the fault.

Capture transitions; a steady-state multimeter reading alone can miss the relevant pulse/ramp. These are measurement targets, not instructions to short, drive, remove, or replace parts.

If the rail/reset waveforms are abnormal, the corresponding power/reset circuit or EC sequencing becomes a concrete repair target. If they are valid and repeatable, firmware/USB state handling remains the target. Existing evidence cannot yet choose between those outcomes.
