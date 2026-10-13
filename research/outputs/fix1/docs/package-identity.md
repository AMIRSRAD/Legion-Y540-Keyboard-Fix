# Package identity and metadata discrepancy

The preserved updater is byte-for-byte identical to the updater embedded inside the preserved Lenovo installer. The mismatch with the supplied Lenovo XML is therefore present between the installer's actual payload and the XML's external-file listing; it was not introduced by our extraction. This resolves the provenance question sufficiently to continue reverse engineering the supplied updater, while the reason for Lenovo's different external-file listing remains unknown.

## Evidence and method

`evidence/package-identity.json` records independent Python byte reads, PE header parsing, XML comparisons, and hashes of every extracted file. These are offline file observations, not REA Evidence IDs and not observations of execution. All five preserved samples passed `tools/verify_samples.py` before analysis. No installer, updater, batch launcher, firmware, or extracted program was executed; no sample was changed. The XML's digital signature and the installer's Authenticode signature were not cryptographically verified.

The official [innoextract download page](https://constexpr.org/innoextract/) describes static extraction without executing installers. Portable innoextract 1.9 was downloaded from `https://constexpr.org/innoextract/files/innoextract-1.9-windows.zip` into the chat's `work/package-identity/` directory. Its ZIP MD5 `72d0d0dd874b6236eaa44411f4470ee1` matches the official page's published checksum; this is a download consistency check, not signature verification. Nothing was installed globally. The tool reported setup data version `5.5.7 (unicode)` and successfully extracted the installer.

## Observed identities

| File | Actual size | SHA-256 | Result |
| --- | ---: | --- | --- |
| Installer `ite1fw11s.exe` | 2,835,096 | `e5863dcd12c40afb98bd5577c3c9631f8f5f78868bc1b1125355f34637f31834` | Matches supplied Lenovo XML |
| Embedded `IT/ITESHFU.exe` | 11,485,623 | `afcca3de209ccfab256aff48b8f7f59dfb6cd6a27b22fc58a41b50f0bd8bb8fa` | Matches preserved updater exactly |
| Embedded `IT/44.bin` | 55,296 | `3afec131c6ed70efa0a3f4b601cb799011a582835d371c57fef68af48519e359` | Matches preserved firmware exactly |
| Embedded `IT/SHFU.ini` | 890 | `87d8a39d9cb1a107c0d24b5a929d46051c54a089c8042e6b044c02d2ffefb64a` | Matches preserved settings and XML exactly |
| Embedded `TVSU.exe` | 20,480 | `ae3c35a2a468273b67f9ee673d7a54cd4d13f3d3427ce5ae3c7f62115ab50c50` | Additional installer payload |
| Embedded final `Update_FW.bat` | 539 | `3a76b435f9cafdf9b43430f710ae0e925cde13fbb13bbd5f67fded42c099078e` | Additional launcher payload |

The XML expects `iteshfu.exe` to be 11,492,728 bytes with SHA-256 `96b2a9aa3f71bcd94995c337a12a389c8f3fd6b36e9d7219413b0d6bff34b8e5`; the actual payload is 7,105 bytes smaller. It also lists external `tvsu_check.exe` and `fw_version.ini`, neither present in the extracted file inventory. This is an inventory boundary, not a claim that these files cannot exist in a separate distribution. `TVSU.exe` and `tvsu_check.exe` must not be treated as the same file based on their names.

The extractor reported two entries for `Update_FW.bat`, with the earlier entry overwritten by the later one. The evidence inventories the final extracted file only. The earlier overwritten version was not retained or compared.

## PE overlay and signing boundary

The updater's last raw section ends at file offset 9,721,856. Its trailing 1,763,767 bytes are completely accounted for by the COFF symbol table and string table:

- COFF symbol pointer: 9,721,856; 20,262 records × 18 bytes = 364,716 bytes.
- COFF string table: offset 10,086,572; recorded length 1,399,051 bytes, ending exactly at EOF 11,485,623.
- Security directory offset and size: both zero. PE checksum field: zero.

Thus the trailing data is debug/symbol information, rather than an unexplained firmware archive or a present certificate. The installer itself has a nonzero certificate range at offset 2,827,984, length 7,112, ending exactly at its EOF. These are PE structure observations; they do not validate signatures.

The updater size gap is compatible in magnitude with adding a code-signing certificate, but the XML's alternate updater is unavailable and this explanation is **unproven**. Do not claim that stripping a signature caused the discrepancy: direct static extraction from the matching installer yields the unsigned sample exactly.

## Launcher behavior visible in text

The final `Update_FW.bat` invokes `TVSU.exe`, checks its exit status, and contains two `shutdown -s -t 0` commands on the zero-status branch. These statements are visible text; neither the batch file nor `TVSU.exe` was run. The wrapper's internal behavior has not been reverse engineered in this pass. These files are retained only in the disposable extraction directory, not added to samples or substituted for the analyzed updater.

## Reproduce

From the chat workspace, after downloading/extracting the official portable tool:

```powershell
& work/package-identity/innoextract/innoextract.exe --extract --output-dir work/package-identity/extracted outputs/y540-research/samples/ite1fw11s.exe
python outputs/y540-research/tools/inspect_package_identity.py --extracted-dir work/package-identity/extracted --output outputs/y540-research/evidence/package-identity.json
```

From the project directory, `python tools/inspect_package_identity.py` validates preserved identities and reports PE/XML facts without requiring any extraction tool. To repeat the payload comparison, pass `--extracted-dir` pointing to a separately statically extracted package. This Python script never launches executable files.

## Remaining unknowns

Why the XML external-file listing differs; identity and contents of the XML-listed alternate updater; cryptographic authenticity of the XML and installer signatures; and `TVSU.exe`'s orchestration behavior remain unresolved. Original project source, exact compiler flags, and signing credentials are not supplied by this package.
