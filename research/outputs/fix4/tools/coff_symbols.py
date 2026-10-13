"""Read PE COFF symbols without dependencies or target execution.

Section-relative values are mapped to RVA/VA; file offsets are reported only
when backed by bytes in a raw section. Names remain exact original strings.
Auxiliary records are retained as hex rather than guessed interpretations.
"""
import argparse
import hashlib
import json
from pathlib import Path
import struct


def parse(data):
    def check(offset, size):
        if offset < 0 or size < 0 or offset + size > len(data):
            raise ValueError(f"Range outside file: {offset}+{size}")
    def unpack(fmt, offset):
        check(offset, struct.calcsize(fmt))
        return struct.unpack_from(fmt, data, offset)
    if data[:2] != b"MZ":
        raise ValueError("Not an MZ/PE file")
    pe, = unpack("<I", 0x3c)
    check(pe, 24)
    if data[pe:pe + 4] != b"PE\0\0":
        raise ValueError("Invalid PE signature")
    machine, section_count, timestamp, sym_offset, sym_count, optional_size, flags = unpack("<HHIIIHH", pe + 4)
    optional = pe + 24
    check(optional, optional_size)
    magic, = unpack("<H", optional)
    if magic == 0x20b:
        image_base, = unpack("<Q", optional + 24)
    elif magic == 0x10b:
        image_base, = unpack("<I", optional + 28)
    else:
        raise ValueError("Unsupported PE optional header")
    check(sym_offset, sym_count * 18)
    string_offset = sym_offset + sym_count * 18
    string_size = 0
    if sym_offset:
        string_size, = unpack("<I", string_offset)
        if string_size < 4:
            raise ValueError("Invalid COFF string table size")
        check(string_offset, string_size)
    def string_at(offset):
        if offset < 4 or offset >= string_size:
            raise ValueError("Invalid COFF string offset")
        start = string_offset + offset
        end = data.find(b"\0", start, string_offset + string_size)
        if end < 0:
            raise ValueError("Unterminated COFF string")
        return data[start:end].decode("utf-8", "replace")
    sections = []
    for number in range(1, section_count + 1):
        offset = optional + optional_size + (number - 1) * 40
        check(offset, 40)
        raw_name = data[offset:offset + 8].rstrip(b"\0").decode("ascii", "replace")
        name = string_at(int(raw_name[1:])) if raw_name.startswith("/") and raw_name[1:].isdigit() else raw_name
        virtual_size, rva, raw_size, raw_offset = unpack("<IIII", offset + 8)
        characteristics, = unpack("<I", offset + 36)
        sections.append({"number": number, "name": name, "rva": rva,
                         "va": hex(image_base + rva), "virtual_size": virtual_size,
                         "raw_offset": raw_offset, "raw_size": raw_size,
                         "characteristics": hex(characteristics),
                         "executable": bool(characteristics & 0x20000000)})
    symbols = []
    index = 0
    while index < sym_count:
        offset = sym_offset + index * 18
        zero, string_index = unpack("<II", offset)
        name = string_at(string_index) if zero == 0 else data[offset:offset + 8].rstrip(b"\0").decode("utf-8", "replace")
        value, section_number, symbol_type, storage_class, aux_count = unpack("<IhHBB", offset + 8)
        if index + aux_count >= sym_count:
            raise ValueError("Auxiliary records exceed symbol table")
        item = {"index": index, "record_file_offset": offset, "name": name,
                "value": value, "section_number": section_number,
                "type": symbol_type, "storage_class": storage_class,
                "aux_count": aux_count,
                "aux_records_hex": [data[offset + 18 * j:offset + 18 * (j + 1)].hex()
                                    for j in range(1, aux_count + 1)]}
        if 1 <= section_number <= section_count:
            section = sections[section_number - 1]
            item.update({"section_name": section["name"], "rva": section["rva"] + value,
                         "va": hex(image_base + section["rva"] + value),
                         "file_offset": section["raw_offset"] + value if value < section["raw_size"] else None,
                         "executable_section": section["executable"]})
        symbols.append(item)
        index += 1 + aux_count
    candidates = [s for s in symbols if s.get("executable_section") and
                  0x400000 <= int(s["va"], 16) < 0x420000]
    return {"method": "Offline Python PE/COFF parsing; names are observations, executable-section labels do not prove function boundaries",
            "mapping_limit": "Merged BSS subsection symbols in this sample retain subsection-relative COFF values. Naive section-RVA mapping is correct for observed text/initialized symbols but unreliable for BSS globals. Use DWARF DW_OP_addr and evidence/initial-globals.json for global addresses.",
            "sha256": hashlib.sha256(data).hexdigest(), "size": len(data),
            "machine": hex(machine), "image_base": hex(image_base),
            "symbol_table_offset": sym_offset, "symbol_record_count_including_aux": sym_count,
            "symbol_count_without_aux": len(symbols), "string_table_offset": string_offset,
            "string_table_size": string_size, "sections": sections,
            "application_range_candidates": candidates, "symbols": symbols}


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("path", type=Path)
    parser.add_argument("--output", type=Path)
    args = parser.parse_args()
    result = parse(args.path.read_bytes())
    result["path"] = str(args.path.resolve())
    text = json.dumps(result, indent=2) + "\n"
    if args.output:
        args.output.write_text(text, encoding="utf-8")
    else:
        print(text, end="")


if __name__ == "__main__":
    main()
