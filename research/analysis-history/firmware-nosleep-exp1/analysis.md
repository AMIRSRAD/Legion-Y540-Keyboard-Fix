# No-deep-sleep experiment 1 — 2026-10-13

This is an explicitly requested experimental firmware variant, not a demonstrated repair or a claim that the sleep code is defective. Original firmware, fix1, and fix2 sources/releases are preserved. No hardware operation was performed here.

## Change

At file/CODE 4C79, `60 66` (JZ 4CE1) becomes `80 66` (SJMP 4CE1). The displacement and two-byte instruction length are unchanged. 4CE1 is the function's existing RET. This final gate lies before writes setting 0DD3/08AD and before peripheral preparation and the 813C sleep call. It retains preceding condition/counter handling and chooses the existing skip-entry outcome regardless of R7 at 4C78.

The only known direct caller of 4BC4 in the retained disassembly is 26F7 in wrapper26E2. On return, it immediately calls6D0D, then36EB before inspectingR7. Thus the original gate's R7 value is not used to select the caller's next operation. This is bounded static-call evidence, not exhaustive indirect-call proof. The main idle instruction at225B, other low-power helpers, USB descriptors, reset handlers and device identifiers are unchanged. Do not describe this as disabling all sleep.

The stored checksum at7FFE/7FFF changes from5622 to5642; only7FFF changes (22->42). Exact total delta: two bytes. Checksum range0400..D800, checksum slots treatedFF, unchanged image size55296. The existing startup branch that chooses a different checksum interval is not altered; its hardware semantics remain unknown.

The 8051 opcode meanings are documented in the [Keil instruction set table](https://www.keil.com/support/man/docs/is51/is51_opcodes.asp?bhcp=1). The hardware-specific sleep register meanings remain unverified; this patch avoids changing those registers and skips the associated entry sequence instead.

## Offline validation

- Input SHA-256 and exact patch-site bytes checked before building; original remains unchanged.
- Diff allowlist enforces exactly4C79 and7FFF changes.
- Local branch model checks all256 accumulator inputs. This is an opcode/target check, not MCU emulation.
- Independent direct-Ghidra8051 import of the patched image confirms `SJMP 4CE1`, instruction length2, targetRET. REA's historical raw-image rejection remains separate; no REA firmware Evidence ID is claimed.
- Existing compiled fix2 checksum validation passes for patched5642 and stock5622.
- Existing offline protocol emulator passes with the patched firmware as its input, including durable backup, programming/readback, aborts and error paths. It models the host updater and flash transport; it does not execute MCU instructions or validate power behavior.

Raw receipts: ghidra-verification.txt, ghidra logs, updater-validation.txt, restore-validation.txt, protocol-emulator.txt. Reproducible patch builder: build_patch.py. Manifest records the original and patched hashes, exact differences and limitations.

## Interpretation of a hardware test

If it installs, verifies, and ordinary restart/shutdown behavior improves, that supports involvement of this entry sequence. It does not yet establish which internal operation failed; increased power use and sleep/resume behavior require later assessment before general distribution.

If programming verifies but the startup symptom remains, this specific bypass was insufficient. Do not infer that all firmware power-state causes have been excluded. If operation worsens, retain logs and restore stock only when the normal updater/boot interface is usable. The presence of a stock image does not guarantee recovery if enumeration is lost.

No blanket claim of safe rollback, repaired hardware, or general Y540 compatibility is made. This package is for the owner's controlled experiment on the already investigated laptop.
