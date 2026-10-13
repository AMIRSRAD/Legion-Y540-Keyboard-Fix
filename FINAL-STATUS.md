# Final case status — 2026-10-13

## Final owner report

The keyboard was **not reliably fixed**. After verified installation of fix9/exp3, the owner initially reported several successful ordinary restarts and shutdowns, then failure after Shift + Shutdown. The owner later corrected that report: normal restart again causes the nonworking state and the apparent improvement did not last. The final statement was that the fix did not work. This correction supersedes earlier success/improvement claims.

No reliable long-term repair, proven physical root cause or demonstrated automatic watchdog recovery was established.

## Symptoms reported by the owner

- Lenovo Legion Y540-15IRH / 81SX, built-in keyboard USB 048D:C100 on port 9; bootloader 048D:89DB.
- Approximately ten seconds holding the power button fully off, then powering on, can restore operation. Ordinary OS restart/shutdown can leave it nonworking.
- Initially thought AC-specific; later reports distinguished forced power-off from OS-controlled transitions on either AC or battery. Connecting AC after a working start did not stop typing.
- Fn keys reportedly still work. BIOS setup input reportedly works; the F12 boot menu can fail after ordinary shutdown.
- Mint live USB after a forced-off start: keyboard worked in BIOS and the Mint selector, but failed at the Mint desktop.
- Fast Startup was reported off. i8042prt was Start=3/RUNNING in both states; a suggested registry change did not cure it.
- The owner recalls no successful original Lenovo update and supplied its “Can not Find Device! - 1” screenshot. Original vendor-attempt logs were unavailable; do not claim a proven causal installation history.

## Attempt chronology

- Baseline reconstruction/fix1: report-size problem prevented update communication; no firmware erase/write in the failed attempts.
- Fix2: mode-specific report lengths corrected. Stock44 was successfully written/read back, but did not repair the symptom. The successful pre-erase backup already matched stock44 exactly.
- Exp1: two-byte no-sleep change, SHA-256 `2b34b6d59db8443831a7e0387ae65970307f516e816dd481f1ba513d3f9de773`.
- Fix3/fix4: longer/reopened access and read/write HID access did not get past chip qualification; exp1 was not installed in those attempts. Final fix4 trace showed 120 failing chip queries, no erase/write.
- Fix5: later investigation identified bootloader idle/suspend during the six-second wait. Fast contact got a first chip answer and a complete read; the second confirming read later stalled during continuous traffic.
- Fix6: a complete backup matching a known image by SHA-256 could use one read. Exp1 was successfully written and verified. Initial reported restart improvement was incomplete.
- Fix7: read-only upper-flash dump recovered the bootloader and parameter area. Raw dump retained; exact register semantics remain partly undocumented.
- Fix8 / exp2: software watchdog attempt made the reported behavior worse. Later instruction-model audit found its bank-2 RETI-to-startup path can trap the original RAM-clearing loop. Counter races, scratch-register and trigger limitations were also identified.
- Return-to-exp1: the supplied 09:58 UTC recording independently reconstructed exact exp2 backup and exact exp1 readback; a later first ordinary restart still failed with the power-plan suspend setting already disabled.
- Fix9 / exp3: corrected CPU/counter handling, improved heartbeat/deadline and used existing C4 terminal reset path. The host verified its dependency bytes before erase. Full readback matched exp3 SHA-256 `e0a959a63dceada1f5fad6846451372271e266ec176cfd25bb322a69199b5457`, checksum 0699. Hardware outcome remained unreliable; see final owner correction above.

## What the evidence does and does not show

The host updater and verification can program the intended image. They do not prove that the MCU timeout fired, that its physical reset covers the failed USB state, or that an electrical/EC/BIOS fault is absent. The C4 path's terminal register sequence is consistent with an ITE watchdog reset, but exact-chip reset scope, clocks and scratch-RAM ownership remain incompletely documented.

Static Ghidra observations, offline models, owner reports, application logs and host USB traces are distinct evidence types. Historical speculative findings and failed approaches are retained for provenance, not promoted to established causes. Review original raw evidence independently before continuing.

## Preservation request

The owner asked to stop local project work, preserve all source/attempts/important evidence on GitHub, and remove local research copies after verification. The Desktop REA folder was explicitly retained and made self-contained with Ghidra, Java and Node. Shared installed tools and unrelated Desktop data were outside the cleanup scope.
