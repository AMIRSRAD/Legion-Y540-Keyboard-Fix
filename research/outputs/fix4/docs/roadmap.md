# fix1 status

| Work | Status | Boundary |
|---|---|---|
| Preserve existing source/release | Complete | Separate tree; original hashes retained |
| Read notes and compare full captures | Complete | case-evidence / case-comparison |
| Correct cleanup/backup/compare failure | Implemented and offline-tested | No live feature commands |
| Add diagnostics and targeted USB retry | Implemented; classification tested | Actual enumeration/restart result pending |
| Compile EXE and package independent source | Complete | No vendor executable dependency |
| Qualify on target keyboard | Pending owner test | AC-failed/battery-working logs and typing result |
| Establish permanent AC-startup repair | Unresolved | Initiating USB enumeration cause unknown |
| Rebuild MCU firmware from source | Unresolved/separate work | Supplied44 unchanged; complete source unavailable |

Next: owner diagnoses failed and working states, optionally attempts the logged exact USB restart, and reports typing plus the next AC-startup result. Review logs before considering firmware changes. Emulator success does not establish hardware repair. Other research documents retain historical vendor behavior; current differences are in fix1-changes.md.

## fix2 progress

Resolved normal-mode 17-byte transport rejection demonstrated by update-ones. Remaining: actual boot handoff, observed boot descriptor, chip validation and backup contents on affected hardware. No flash-integrity conclusion yet. Full case summary: ../../update-attempt-analysis/findings.md.

## fix3 readiness

Bootloader command readiness now bounded separately from metadata enumeration. Still requires owner hardware validation. Experiment1 not installed in supplied failed attempt; do not infer efficacy from subsequent stock startup behavior. Underlying error31 cause and keyboard startup repair remain unresolved.

## Final software candidate / stop boundary

fix4 is the owner's last requested software attempt. Pending: actual bootRWqualification, whether experimental1 installs, and ordinary restart/shutdown outcome. If qualification or backup fails, stop without bypass. If the final candidate fails, retain its USBtrace/logs and pursue qualified power/reset/USB measurement; do not automatically create another software release.
