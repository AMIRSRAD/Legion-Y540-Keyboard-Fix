"""Map original globals using a GNU objdump --dwarf=info text dump.

No target execution. DWARF locations resolve linker COFF BSS subsection offsets.
Produces loader initial values, never claims post-configuration defaults.
"""
import argparse
import hashlib
import json
from pathlib import Path
import re
from coff_symbols import parse


def dwarf_entries(text):
    result = {}
    pattern = r"^\s*<(\d+)><([0-9a-f]+)>: Abbrev Number: [^\n]*"
    matches = list(re.finditer(pattern, text, re.M))
    for index, match in enumerate(matches):
        end = matches[index + 1].start() if index + 1 < len(matches) else len(text)
        block = text[match.start():end]
        name = re.search(r"DW_AT_name\s*:\s*(?:\(indirect string[^\n]*?\):\s*)?([^\n]+)", block)
        type_ref = re.search(r"DW_AT_type\s*:\s*<0x([0-9a-f]+)>", block)
        size = re.search(r"DW_AT_byte_size\s*:\s*(\d+)", block)
        address = re.search(r"DW_OP_addr:\s*([0-9a-f]+)", block)
        frame = re.search(r"DW_OP_fbreg:\s*(-?\d+)", block)
        tag = re.search(r"\((DW_TAG_[^)]+)\)", match.group())
        result[int(match.group(2), 16)] = {
            "name": name.group(1).strip() if name else None,
            "type_ref": int(type_ref.group(1), 16) if type_ref else None,
            "size": int(size.group(1)) if size else None,
            "address": int(address.group(1), 16) if address else None,
            "frame_offset": int(frame.group(1)) if frame else None,
            "tag": tag.group(1) if tag else None,
            "raw": block}
    return result


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--dwarf-info", type=Path, required=True)
    parser.add_argument("--output", type=Path, required=True)
    args = parser.parse_args()
    root = Path(__file__).resolve().parents[1]
    data = (root / "samples/ITESHFU.exe").read_bytes()
    pe = parse(data)
    dump = args.dwarf_info.read_bytes()
    entries = dwarf_entries(dump.decode("utf-8-sig", "replace"))
    wanted = {s["name"]: s for s in pe["symbols"] if s.get("section_name") == ".data"
              and s["name"].isidentifier() and not s["name"].startswith("_")
              and s["value"] < 5000}
    def type_size(offset, seen=None):
        seen = set() if seen is None else seen
        if offset in seen or offset not in entries:
            return None
        seen.add(offset)
        entry = entries[offset]
        if entry["size"] is not None:
            return entry["size"]
        if entry["tag"] == "DW_TAG_array_type":
            return None  # Element size alone is not the array's storage size.
        if entry["tag"] in {"DW_TAG_pointer_type", "DW_TAG_reference_type"}:
            return 8
        return type_size(entry["type_ref"], seen)
    values = []
    locals_8910 = []
    for offset, entry in entries.items():
        if entry["tag"] != "DW_TAG_variable":
            continue
        if entry["name"] in {"Have8910BXBBK", "Is8910BXVersion"}:
            locals_8910.append({"die_offset": hex(offset), **entry})
        if entry["name"] not in wanted or entry["address"] is None:
            continue
        item = {"name": entry["name"], "die_offset": hex(offset),
                "dwarf_raw": entry["raw"], "va": hex(entry["address"]),
                "byte_size": type_size(entry["type_ref"]),
                "coff_naive_va": wanted[entry["name"]]["va"]}
        section = next((s for s in pe["sections"] if
                       int(s["va"], 16) <= entry["address"] < int(s["va"], 16) + s["virtual_size"]), None)
        if section:
            relative = entry["address"] - int(section["va"], 16)
            size = item["byte_size"]
            item["section"] = section["name"]
            item["section_relative_offset"] = relative
            if size is not None and relative + size <= section["raw_size"]:
                start = section["raw_offset"] + relative
                raw = data[start:start + size]
                item.update({"storage": "file-backed", "file_offset": start,
                             "initial_hex": raw.hex()})
                if size <= 8:
                    item["initial_unsigned_little_endian"] = int.from_bytes(raw, "little")
            elif size is not None and relative >= section["raw_size"] and relative + size <= section["virtual_size"]:
                item.update({"storage": "loader-zero-fill", "file_offset": None,
                             "initial_hex": "00" * size,
                             "initial_unsigned_little_endian": 0})
            else:
                item["storage"] = "unresolved"
        values.append(item)
    result = {"method": "Offline GNU objdump 2.42 DWARF dump + Python PE mapping",
              "scope": "PE loader initial bytes only; constructors, config and runtime may override",
              "target_sha256": pe["sha256"], "dwarf_dump_sha256": hashlib.sha256(dump).hexdigest(),
              "sections": pe["sections"], "globals": values, "8910_stack_locals": locals_8910}
    # A focused static follow-up to the INI fallback referenced in Timer4Timer.
    va = 0x6e09bf
    section = next(s for s in pe["sections"] if int(s["va"], 16) <= va < int(s["va"], 16) + s["raw_size"])
    start = section["raw_offset"] + va - int(section["va"], 16)
    result["ini_zero_default_literal"] = {"va": hex(va), "file_offset": start,
                                          "bytes_hex": data[start:start + 2].hex(),
                                          "text": data[start:data.index(0, start)].decode("ascii")}
    args.output.write_text(json.dumps(result, indent=2) + "\n", encoding="utf-8")


if __name__ == "__main__":
    main()
