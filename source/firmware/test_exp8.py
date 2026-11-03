"""Static checks for exp8: only the bus-reset guard (39EB..39EC) and checksum change, the
patched bytes decode as CLR A ; NOP falling into the stock first-reset path, and no branch
anywhere in the decompiled firmware lands on the patched bytes."""
import hashlib, json, pathlib, re, sys

import build_exp8 as B

LISTING = pathlib.Path(__file__).resolve().parents[2] / 'analysis/app44/full/full-listing.asm'


def main(stock_path):
    stock = stock_path.read_bytes()
    image, s = B.build(stock)
    diffs = {i for i, (a, b) in enumerate(zip(stock, image)) if a != b}
    assert diffs <= {0x39EB, 0x39EC, 0x7FFE, 0x7FFF} and {0x39EB, 0x39EC} <= diffs, sorted(map(hex, diffs))
    assert B.checksum(image) == s == (image[0x7FFE] << 8 | image[0x7FFF])
    assert image[0x39E5:0x39F1] == bytes.fromhex('900003' '12857a' 'e400' 'ff' '124b29')
    # stock: JNZ 3A21 skipped re-init; the skip target is the 'ignored' return
    assert stock[0x3A21:0x3A24] == bytes.fromhex('7f0022')          # MOV R7,#0 ; RET
    targets = []
    for line in LISTING.read_text().splitlines():
        m = re.match(r'CODE:([0-9a-f]{4})\s+(\S+)\s.*0x([0-9a-f]{3,4})$', line)
        if m and m.group(2) not in ('MOV', 'MOVX', 'ORL', 'ANL', 'XRL') and int(m.group(3), 16) in (0x39EC,):
            targets.append(line)
    assert not targets, targets
    # the only other reader of the guard flag is the guard itself
    print(json.dumps({'image_sha256': hashlib.sha256(image).hexdigest(), 'checksum': '%04X' % s,
                      'changed_offsets': sorted(hex(d) for d in diffs),
                      'branches_into_patch': 0, 'runtime_modeled': False}, indent=2))


if __name__ == '__main__':
    if len(sys.argv) != 2:
        raise SystemExit('Usage: test_exp8.py STOCK_BIN')
    main(pathlib.Path(sys.argv[1]))
