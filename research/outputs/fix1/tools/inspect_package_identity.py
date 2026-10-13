"""Offline PE/package identity evidence. Never executes a vendor binary.

Pass --extracted-dir after statically extracting the installer with innoextract.
The directory is read only; this tool writes only --output.
"""
import argparse
import hashlib
import json
from pathlib import Path
import struct
import xml.etree.ElementTree as ET


def digest(data):
    return hashlib.sha256(data).hexdigest()


def pe_layout(data):
    if data[:2] != b"MZ":
        return None
    pe = struct.unpack_from("<I", data, 0x3c)[0]
    if data[pe:pe + 4] != b"PE\0\0":
        raise ValueError("Invalid PE signature")
    machine, sections = struct.unpack_from("<HH", data, pe + 4)
    symbol_offset, symbol_count = struct.unpack_from("<II", data, pe + 12)
    strings_offset = symbol_offset + symbol_count * 18
    strings_size = (struct.unpack_from("<I", data, strings_offset)[0]
                    if symbol_offset and strings_offset + 4 <= len(data) else None)
    optional_size = struct.unpack_from("<H", data, pe + 20)[0]
    optional = pe + 24
    magic = struct.unpack_from("<H", data, optional)[0]
    directory = optional + (112 if magic == 0x20b else 96)
    cert_offset, cert_size = struct.unpack_from("<II", data, directory + 32)
    section_table = optional + optional_size
    raw_sections = []
    for i in range(sections):
        pos = section_table + i * 40
        name = data[pos:pos + 8].rstrip(b"\0").decode("ascii", "replace")
        size, offset = struct.unpack_from("<II", data, pos + 16)
        raw_sections.append({"name": name, "offset": offset, "size": size,
                             "end": offset + size})
    end = max(s["end"] for s in raw_sections)
    overlay = data[end:]
    return {"machine": hex(machine), "optional_magic": hex(magic),
            "coff_symbol_offset": symbol_offset, "coff_symbol_count": symbol_count,
            "coff_string_table_offset": strings_offset if symbol_offset else None,
            "coff_string_table_size": strings_size,
            "sections": raw_sections, "last_section_end": end,
            "overlay_size": len(overlay), "overlay_sha256": digest(overlay),
            "overlay_prefix_hex": overlay[:64].hex(),
            "security_directory_offset": cert_offset,
            "security_directory_size": cert_size,
            "certificate_range_within_file": bool(cert_size and cert_offset + cert_size <= len(data)),
            "checksum_offset": optional + 64,
            "checksum_field": struct.unpack_from("<I", data, optional + 64)[0]}


def facts(path):
    data = path.read_bytes()
    item = {"size": len(data), "sha256": digest(data)}
    if data[:2] == b"MZ":
        item["pe"] = pe_layout(data)
    return item


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--extracted-dir", type=Path)
    parser.add_argument("--output", type=Path)
    args = parser.parse_args()
    root = Path(__file__).resolve().parents[1]
    manifest = json.loads((root / "samples/manifest.json").read_text())
    files = {}
    for item in manifest["files"]:
        actual = facts(root / "samples" / item["name"])
        if actual["size"] != item["size"] or actual["sha256"] != item["sha256"]:
            raise ValueError("Sample identity changed: " + item["name"])
        files[item["name"]] = actual
    metadata = {}
    xml = ET.parse(root / "samples/Lenovo-package-metadata.xml")
    for node in xml.findall("./Files/*/File"):
        metadata[node.findtext("Name").lower()] = {
            "size": int(node.findtext("Size")), "sha256": node.findtext("CRC").lower()}
    comparisons = {}
    for name, actual in files.items():
        if name.lower() in metadata:
            expected = metadata[name.lower()]
            comparisons[name] = {"expected": expected,
                                 "size_difference": actual["size"] - expected["size"],
                                 "sha256_matches": actual["sha256"] == expected["sha256"]}
    extracted = {}
    if args.extracted_dir:
        for path in sorted(args.extracted_dir.rglob("*")):
            if not path.is_file():
                continue
            actual = facts(path)
            actual["preserved_sample_matches"] = [name for name, sample in files.items()
                if sample["sha256"] == actual["sha256"] and sample["size"] == actual["size"]]
            if path.suffix.lower() in {".bat", ".ini"}:
                actual["text_utf8_replacement"] = path.read_bytes().decode("utf-8", "replace")
            extracted[path.relative_to(args.extracted_dir).as_posix()] = actual
    evidence = {"method": "Python byte reads and XML parsing; no vendor execution or signature verification",
                "manifest_validated": True, "samples": files,
                "metadata": metadata, "metadata_comparisons": comparisons,
                "extracted_dir": str(args.extracted_dir.resolve()) if args.extracted_dir else None,
                "extracted_files": extracted}
    result = json.dumps(evidence, indent=2) + "\n"
    if args.output:
        args.output.write_text(result, encoding="utf-8")
    else:
        print(result, end="")


if __name__ == "__main__":
    main()
