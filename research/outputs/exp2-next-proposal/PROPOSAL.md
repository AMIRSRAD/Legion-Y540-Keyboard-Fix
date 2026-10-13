# Exp2 recovery revision: proposal after the return recording

## What this recording establishes

The return to exp1 succeeded. This is independently confirmed from the actual D1 read responses, not just the updater's success message:

- The full pre-erase read reconstructs exp2 exactly: SHA-256 `82c94fd50191a3ad8b4f9760ebf588b911b193450dd7edeeec06bacba338e1b8`.
- The full final read reconstructs exp1 exactly: SHA-256 `2b34b6d59db8443831a7e0387ae65970307f516e816dd481f1ba513d3f9de773`.
- Both reads cover all 55,296 bytes; 1,976 successful D1 request/response pairs, zero logged failed application transfers.
- C4 was accepted at 10:00:06.289 UTC. The trace shows the boot-mode device disconnecting and a fresh normal-mode C100 interface on port 9 approximately 1.73 seconds after that disconnect.
- The trace has 14,453 events and zero lost events/buffers. One decoding warning affects trace metadata, not a USB-provider record.

The later comparison snapshots show USB selective suspend set to zero for both AC and battery before the Disable action and after the first ordinary restart. Disable therefore made no setting change. After restart, all captured normal C100 interfaces have problem 45 (not currently present), whereas they were healthy before restart. The owner reports the built-in keyboard failed on that first restart. That report overrides the last JSON's manually supplied `working` label, which conflicts with the report and the interface disappearance.

Conclusion: the previously observed two-successful-restarts behavior of exp1 did not repeat here. The active power-plan setting being disabled did not prevent this failure. This does not prove that no USB power transition happened during restart: the comparison files are metadata snapshots, and the ETW recording ended before that restart. There is no reason to repeat the same suspend-setting comparison now.

## Proposed recovery change

The next exp2 revision should replace its software jump to startup with the bootloader's existing C4 terminal reset-request path. Keep the unchanged exp1 no-sleep branch as the base.

The candidate trampoline is eight bytes:

```asm
CLR EA           ; exclude interrupts during the terminal transition
MOV PSW,#00h     ; bank 0, as expected by the bootloader routine
LJMP F455h       ; existing C4 terminal reset routine, not app startup
```

Hex: `C2 AF 75 D0 00 02 F4 55`.

The byte-verified F455 routine performs its existing delays, writes XDATA[2F50]=08, sets XDATA[1058] bit 6, masks SFR[8E] with 3F, writes SFR[D8]=02 and waits. This is consistent with an ITE hardware watchdog reset by family analogy. The return trace confirms that using C4 in a functioning bootloader session causes a fresh normal-device enumeration. It does not prove that this reset resets the USB block in the original failed condition or duplicates the power-button shutdown.

This removes exp2's guessed write of zero to 2F40, guessed software detach delay, stack fabrication and RETI-to-0100 path. The previous bank-2 startup lock cannot occur through that removed path. It also incorporates the reviewed fixes for atomic shared-counter updates and saving/restoring the bank-2 scratch register.

## Concrete prototype and offline result

`source/build_candidate.py` constructs the revision in memory from hash-checked stock and upper-dump bytes. It deliberately emits no firmware file through its command-line entry.

`source/test_candidate.py` follows both existing timeout triggers through the trampoline and the actual supplied C4 routine bytes, up to its terminal wait. The model verifies the writes and delay-loop counts. It does **not** simulate a physical reset or invent a successful re-enumeration.

The in-memory prototype has 155 bytes of inserted code, checksum 0F6C, and SHA-256 `640977c04dab76176d485221d172ae4fd08b8942d09966944625d2869d646e56`. These identify the offline prototype, not an approved release.

Tests pass for both trigger paths, all 256 values of the scratch register on the normal path, and rejection of a changed bootloader dump. The prototype retains the earlier timeout triggers only for model comparison; that does not validate those triggers as reliable fault detectors.

Run offline:

```powershell
python source/test_candidate.py PATH_TO_STOCK_44.bin evidence/upper-flash-dump.bin
```

## Conditions before an installable candidate

1. The programmer must freshly read and compare the target's F455..F477 and F12C..F149 bytes before erase; an old dump supplied to the generator is not enough to qualify an absolute cross-region jump on another controller. These checks need only two short reads. The upper flash is never written.
2. The trigger must distinguish a firmware failure from intentional host inactivity. In particular, no SET_ADDRESS after a bus reset can be normal during shutdown. The existing three-thousand-tick trigger is not accepted as a proven detector. Merely changing the reset routine leaves false-trigger behavior unresolved.
3. Scratch-RAM ownership and timer/clock behavior must be established or the design must avoid depending on them. The absence of direct references is insufficient proof that 0FF8..0FFC are free.

If the USB block stops responding while the firmware still runs and no detectable USB event reaches it, the present watchdog may not notice. If the timer stops too, a timer-ISR detector cannot run. The proposal is a better-grounded recovery mechanism, not evidence that the original fault has been repaired.

No further flash or power-policy change was performed to produce this proposal. Existing firmware and builds were preserved. Evidence and receipts are retained beside this file.
