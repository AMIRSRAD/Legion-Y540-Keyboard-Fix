"""Read-only, standard-library review of the supplied Y540 firmware.

Run: python tools/firmware_review.py PATH_TO_44_BIN --ini PATH_TO_SHFU_INI
Offsets are file offsets, not verified mapped MCU addresses. No device I/O.
"""
import argparse
import binascii
import configparser
import hashlib
import json
from pathlib import Path


def review(path, ini=None):
    d = Path(path).read_bytes()
    r = {"source": str(Path(path).resolve()), "size": len(d),
         "sha256": hashlib.sha256(d).hexdigest(), "offset_kind": "file"}
    if ini:
        raw = Path(ini).read_bytes()
        cfg = configparser.ConfigParser()
        # Non-ASCII notification text is not interpreted in this review.
        cfg.read_string(raw.decode("ascii", errors="replace"))
        r["ini"] = {"sha256": hashlib.sha256(raw).hexdigest(), "size": len(raw),
                    "sections": {s: dict(cfg[s]) for s in cfg.sections()}}
    vectors = []
    for off in [0, 3, 11, 19, 27, 35, 43]:
        chunk = d[off:off+3]
        target = int.from_bytes(chunk[1:3], "big") if len(chunk) == 3 and chunk[0] == 2 else None
        vectors.append({"offset": hex(off), "bytes": chunk.hex(" "),
                        "candidate_8051_ljmp_target": hex(target) if target is not None else None,
                        "target_bytes": d[target:target+16].hex(" ") if target is not None else None})
    r["candidate_8051_vectors"] = vectors
    r["candidate_reset_code"] = {"offset": "0x100", "bytes": d[0x100:0x120].hex(" ")}
    descriptors = []
    # Exact descriptor boundaries recovered from this image; keep raw evidence.
    for off in [0x5307, 0x531d, 0x5326, 0x532f, 0x5338, 0x5342, 0x5349, 0x536b, 0x5391]:
        n = d[off]
        entry = {"offset": hex(off), "length": n, "type": d[off+1],
                 "bytes": d[off:off+n].hex(" ")}
        if d[off+1] == 3 and off != 0x5342:
            entry["utf16le"] = d[off+2:off+n].decode("utf-16le")
        descriptors.append(entry)
    r["descriptors"] = descriptors
    start, end = 0x400, 0xd800
    a = d[start:end]
    stored = int.from_bytes(d[0x7ffe:0x8000], "big")
    hypotheses = {}
    for field_mode in ["included", "omitted", "zeroed", "ff_filled"]:
        b = bytearray(a)
        rel = 0x7ffe-start
        if field_mode == "omitted":
            del b[rel:rel+2]
        elif field_mode == "zeroed":
            b[rel:rel+2] = b"\x00\x00"
        elif field_mode == "ff_filled":
            b[rel:rel+2] = b"\xff\xff"
        vals = {"byte_sum": sum(b) & 0xffff,
                "big_endian_word_sum": sum(int.from_bytes(b[i:i+2], "big") for i in range(0, len(b), 2)) & 0xffff,
                "little_endian_word_sum": sum(int.from_bytes(b[i:i+2], "little") for i in range(0, len(b), 2)) & 0xffff,
                "crc_hqx_init0": binascii.crc_hqx(b, 0),
                "crc_hqx_initffff": binascii.crc_hqx(b, 0xffff)}
        expanded = {}
        for name, val in vals.items():
            for suffix, value in [("", val), ("_ones_complement", val ^ 0xffff), ("_twos_complement", -val & 0xffff)]:
                expanded[name+suffix] = {"value": f"0x{value:04x}", "matches_stored_be": value == stored,
                                         "matches_stored_le": value == int.from_bytes(d[0x7ffe:0x8000], "little")}
        hypotheses[field_mode] = expanded
    r["checksum"] = {"range": "[0x0400,0xd800)", "range_semantics": "candidate exclusive end; d800 is EOF",
                     "stored_offsets": ["0x7ffe", "0x7fff"], "stored_bytes": d[0x7ffe:0x8000].hex(" "),
                     "stored_be": f"0x{stored:04x}", "hypotheses": hypotheses,
                     "limit": "Numerical matches alone do not verify an algorithm; updater code and/or more samples are required."}
    return r


if __name__ == "__main__":
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("firmware")
    parser.add_argument("--ini")
    args = parser.parse_args()
    print(json.dumps(review(args.firmware, args.ini), indent=2, ensure_ascii=True))
