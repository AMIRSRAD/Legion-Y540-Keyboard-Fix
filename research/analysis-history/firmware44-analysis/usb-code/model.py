"""Offline arithmetic model of the byte-checked USB response code.

Not firmware execution, emulation, or USB host/hardware validation.
Assumes an accepted C1/7F/0005 request and successful continuation callbacks.
"""
import json
from pathlib import Path

rows = []
for requested in [0, 76, 77, 255]:
    effective = requested if requested else 1
    remaining = effective
    offset = 0
    chunks = []
    while remaining:
        count = min(remaining, 64)
        chunks.append({"source_start": f"0x{0xa1f + offset:04X}",
                       "source_end": f"0x{0xa1f + offset + count - 1:04X}",
                       "count": count})
        offset += count
        remaining -= count
    rows.append({"wLength": requested, "staged_response_length": effective,
                 "descriptor_length": 76,
                 "bytes_beyond_descriptor_if_all_callbacks_complete": max(0, effective-76),
                 "chunks": chunks,
                 "zero_length_caveat": "Host need not fetch staged byte for wLength zero" if requested == 0 else None})
Path(__file__).with_name("model.json").write_text(json.dumps(rows, indent=2)+"\n")
print(json.dumps(rows, indent=2))
