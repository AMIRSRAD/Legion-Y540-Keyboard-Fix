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
