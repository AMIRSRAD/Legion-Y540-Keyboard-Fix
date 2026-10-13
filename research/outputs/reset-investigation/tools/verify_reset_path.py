"""Offline verification of the supplied IT817x bootloader C4 path.

No USB APIs, target execution, firmware modifications or hardware emulation.
Usage: python tools/verify_reset_path.py [upper_flash_dump.bin]
"""
import hashlib
import json
import pathlib
import sys

ROOT = pathlib.Path(__file__).resolve().parents[1]
DUMP_SHA = '6160ed916d5356c631a5e7939a55d3dae0b863199e0f33ba7e6680fe6f684d2a'


def verify(path):
    data = path.read_bytes()
    assert len(data) == 0x2800, 'Expected D800..FFFF dump (10240 bytes)'
    assert hashlib.sha256(data).hexdigest() == DUMP_SHA, 'Unexpected dump identity'

    def read(address, count):
        assert 0xd800 <= address <= 0x10000 - count
        return data[address - 0xd800:address - 0xd800 + count]

    checks = {
        'command_dispatch': (0xee09, '900544e012f35a'),
        'switch_record_C4_to_EE54': (0xee22, 'ee54c4'),
        'C4_sets_request_flag_33': (0xee54, '900f0f7433f08012'),
        'clear_request_before_dispatch': (0xe1ab, 'e4900f0ff0'),
        'request_flag_consumer': (0xe235, '900f0fe0b4333412f455'),
        'terminal_reset_sequence': (0xf455,
            '7f057e0012f12c902f507408f07fe87e0312f12c'
            '901058e04440f0538e3f75d80280fe'),
        'delay_function': (0xf12c,
            'e4fdfcc3ed9fec9e5013e4fbe490200bf00bebb442f60dbd00010c80e622'),
        'separate_service_helper': (0xf896,
            '901f01e030e607901f07745cf022901f01e020e306901f0674fff022'),
        'service_helper_call': (0xef84, '12f896'),
    }
    for name, (address, hex_bytes) in checks.items():
        expected = bytes.fromhex(hex_bytes)
        assert read(address, len(expected)) == expected, name

    # Independently parse the Keil switch helper's inline table.
    # Each non-default entry is high-address, low-address, selector.
    records = []
    at = 0xee10
    while read(at, 2) != b'\0\0':
        raw = read(at, 3)
        records.append({'command': raw[2], 'destination': int.from_bytes(raw[:2], 'big')})
        at += 3
        assert at <= 0xee2b
    assert [r['destination'] for r in records if r['command'] == 0xc4] == [0xee54]

    # Model ONLY documented byte operations at the terminal tail, not their
    # chip-specific physical effects. Preserve unrelated bits for all inputs.
    for value in range(256):
        assert (value | 0x40) & 0xbf == value & 0xbf
        assert (value & 0x3f) == value % 64
    terminal = read(0xf455, 0x23)
    assert b'\x32' not in terminal, 'C4 tail unexpectedly contains RETI'
    assert terminal[-2:] == bytes.fromhex('80fe'), 'Expected terminal wait loop'

    return {
        'dump_sha256': DUMP_SHA,
        'byte_checks_passed': len(checks),
        'switch_records': records,
        'terminal_delay_arguments': [5, 1000],
        'delay_units': 'unknown; not asserted to be milliseconds',
        'terminal_operations': ['XDATA[2F50]=08', 'XDATA[1058]|=40',
                                'SFR[8E]&=3F', 'SFR[D8]=02', 'infinite wait'],
        'physical_reset_scope': 'unknown without applicable register map or measurement',
        'mode': 'offline byte and branch verification only',
    }


if __name__ == '__main__':
    path = pathlib.Path(sys.argv[1]) if len(sys.argv) > 1 else ROOT / 'evidence/flash-dump-D800-20261013T084901150Z-p3460-3.bin'
    print(json.dumps(verify(path), indent=2))
