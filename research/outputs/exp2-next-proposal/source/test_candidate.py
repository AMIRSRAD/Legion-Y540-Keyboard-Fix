"""Execute the candidate through the actual C4 byte sequence, offline only.

Memory writes are captured in a Python model, never sent to a real device.
The test ends at the terminal wait and does not pretend to model watchdog reset.
"""
import hashlib
import json
import pathlib
import sys

import build_candidate as B
import instruction_model as M


class CPU(M.CPU):
    def __init__(self, image):
        super().__init__(image)
        self.sfr = {0x8e: 0xab, 0xd8: 0}

    def rd_dir(self, d):
        if d in self.sfr:
            return self.sfr[d]
        return super().rd_dir(d)

    def wr_dir(self, d, value):
        if d in self.sfr:
            self.sfr[d] = value
            return
        return super().wr_dir(d, value)

    def step(self):
        op = self.code[self.pc]
        if 0xe8 <= op <= 0xef:
            self.pc += 1
            self.a = self.reg(op - 0xe8)
        elif 0xf8 <= op <= 0xff:
            self.pc += 1
            self.setreg(op - 0xf8, self.a)
        elif 0x08 <= op <= 0x0f:
            self.pc += 1
            n = op - 8
            self.setreg(n, self.reg(n) + 1)
        elif 0x98 <= op <= 0x9f:
            self.pc += 1
            value = self.a - self.reg(op - 0x98) - self.c
            self.a = value & 255
            self.c = value < 0
        elif op == 0x50:
            self.pc += 1
            offset = self.rel()
            if not self.c:
                self.pc += offset
        elif 0xb8 <= op <= 0xbf:
            self.pc += 1
            value = self.fetch()
            offset = self.rel()
            register = self.reg(op - 0xb8)
            self.c = register < value
            if register != value:
                self.pc += offset
        elif op == 0x53:
            self.pc += 1
            direct = self.fetch()
            value = self.fetch()
            self.wr_dir(direct, self.rd_dir(direct) & value)
        elif op == 0x44:
            self.pc += 1
            self.a |= self.fetch()
        else:
            super().step()


def main(stock_path, upper_path):
    stock, upper = stock_path.read_bytes(), upper_path.read_bytes()
    image, asm, checksum = B.build(stock, upper)
    full = image + upper
    assert len(full) == 65536
    reset_bytes = image[asm.labels['restart']:asm.labels['done']]
    assert reset_bytes == bytes.fromhex('c2af75d00002f455')
    assert sum(image[0x400:0x7ffe] + b'\xff\xff' + image[0x8000:0xd800]) & 65535 == checksum

    results = []
    for trigger in ('main', 'enumeration'):
        cpu = CPU(full)
        cpu.xram[0x1058] = 0x85
        if trigger == 'main':
            cpu.xram[B.VAR_MAIN] = (B.T1 - 1) >> 8
            cpu.xram[B.VAR_MAIN + 1] = (B.T1 - 1) & 255
        else:
            cpu.xram[B.VAR_ARM] = 1
            cpu.xram[B.VAR_ENUM] = (B.T2 - 1) >> 8
            cpu.xram[B.VAR_ENUM + 1] = (B.T2 - 1) & 255
        cpu.push(M.original_test.SENT & 255)
        cpu.push(M.original_test.SENT >> 8)
        cpu.pc = asm.labels['tick']
        assert cpu.run(until_pc=0xf455) == 'sentinel'
        assert not cpu.ea and cpu.psw_bank == 0
        assert cpu.run(until_pc=0xf476) == 'sentinel'
        assert cpu.xram[0x2f50] == 8
        assert cpu.xram[0x1058] == 0xc5
        assert cpu.sfr[0x8e] == 0x2b and cpu.sfr[0xd8] == 2
        assert sum(addr == 0x200b for addr, _ in cpu.xw) == (5 + 1000) * 66
        assert all(addr != 0x2f40 for addr, _ in cpu.xw)
        assert cpu.reti_to is None
        results.append({'trigger': trigger, 'bank_at_reset_entry': 0,
                        'terminal_pc': hex(cpu.pc), 'delay_inner_writes': 66330,
                        'physical_reset_modeled': False})

    # The normal path preserves the scratch register and returns, without MMIO.
    for scratch in range(256):
        cpu = CPU(full)
        cpu.iram[0x12] = scratch
        assert M.original_test.call(cpu, asm.labels['tick']) == 'sentinel'
        assert cpu.iram[0x12] == scratch
        assert all(addr < 0x1000 for addr, _ in cpu.xw)

    bad_upper = bytearray(upper)
    bad_upper[0xf455 - 0xd800] ^= 1
    rejected = False
    try:
        B.build(stock, bytes(bad_upper))
    except AssertionError:
        rejected = True
    assert rejected

    print(json.dumps({
        'in_memory_image_sha256': hashlib.sha256(image).hexdigest(),
        'new_code_bytes': len(asm.build()), 'checksum': '%04X' % checksum,
        'reset_trampoline_hex': reset_bytes.hex(), 'trigger_models': results,
        'normal_scratch_values_tested': 256, 'wrong_bootloader_rejected': rejected,
        'firmware_image_written': False,
        'unresolved': ['timeout trigger correctness', 'XRAM ownership',
                       'hardware reset scope', 'USB-core recovery', 'clock failure'],
    }, indent=2))


if __name__ == '__main__':
    if len(sys.argv) != 3:
        raise SystemExit('Usage: python test_candidate.py STOCK_44_BIN UPPER_DUMP')
    main(pathlib.Path(sys.argv[1]), pathlib.Path(sys.argv[2]))
