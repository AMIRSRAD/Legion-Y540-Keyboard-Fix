"""Offline regression checks, including original startup after the exp2 jump.

The in-memory CPU does not model USB, clocks, electrical reset or an IT8176.
No image is saved and no device API is used.
"""
import importlib.util
import json
import pathlib
import sys
import types

import build_exp2_review as reviewed

ROOT = pathlib.Path(__file__).resolve().parents[1]


def load_file(name, path):
    spec = importlib.util.spec_from_file_location(name, path)
    module = importlib.util.module_from_spec(spec)
    spec.loader.exec_module(module)
    return module


upstream = load_file('upstream_builder', ROOT / 'evidence/upstream-build_exp2.py')
sys.modules['build_exp2'] = upstream
test_source = (ROOT / 'evidence/upstream-test_exp2.py').read_text()
test_source = test_source[:test_source.rfind('\nmain()')]
original_test = types.ModuleType('original_test')
exec(compile(test_source, 'upstream-test_exp2.py', 'exec'), original_test.__dict__)


class CPU(original_test.CPU):
    def __init__(self, image):
        super().__init__(image)
        self.ie = 0x8a

    def rd_dir(self, address):
        if address == 0xa8:
            return (self.ie & 0x7f) | (0x80 if self.ea else 0)
        if address == 0xd0:
            return (self.psw_bank << 3) | (0x80 if self.c else 0)
        if address < 0x80:
            return self.iram[address]
        return super().rd_dir(address)

    def wr_dir(self, address, value):
        if address == 0xa8:
            self.ie = value
            self.ea = bool(value & 0x80)
            return
        if address == 0xd0:
            self.psw_bank = (value >> 3) & 3
            self.c = bool(value & 0x80)
            return
        if address < 0x80:
            self.iram[address] = value
            return
        return super().wr_dir(address, value)

    def step(self):
        # Implement the actual original startup instruction the old test never ran.
        if self.code[self.pc] == 0xf6:  # MOV @R0,A
            self.pc += 1
            self.iram[self.reg(0)] = self.a
            return
        return super().step()


def make(builder, stock):
    image, asm, checksum = builder.build(stock)
    full = bytearray(0x10000)
    full[:len(image)] = image
    return bytes(full), asm, checksum


def reach_startup(builder, stock):
    image, asm, _ = make(builder, stock)
    cpu = CPU(image)
    cpu.xram[builder.VAR_MAIN] = (builder.T1 - 1) >> 8
    cpu.xram[builder.VAR_MAIN + 1] = (builder.T1 - 1) & 255
    assert original_test.call(cpu, asm.labels['tick']) == 'reti'
    assert cpu.pc == 0x100
    bank_at_start = cpu.psw_bank
    for steps in range(2000):
        if cpu.pc == 0x106:
            return {'bank': bank_at_start, 'iram_clear_completed': True, 'instructions': steps}
        cpu.step()
    return {'bank': bank_at_start, 'iram_clear_completed': False, 'instructions': 2000}


def inject_timer(cpu, tick):
    # Equivalent preservation of A/DPTR/PSW around the timer ISR's reviewed hook.
    saved = (cpu.a, cpu.dptr, cpu.psw_bank, cpu.c, cpu.pc)
    result = original_test.call(cpu, tick)
    assert result == 'sentinel', 'Unexpected timeout during atomic-operation check'
    cpu.a, cpu.dptr, cpu.psw_bank, cpu.c, cpu.pc = saved


def main(stock_path):
    stock = stock_path.read_bytes()
    legacy = reach_startup(upstream, stock)
    corrected = reach_startup(reviewed, stock)
    assert legacy['bank'] == 2 and not legacy['iram_clear_completed']
    assert corrected['bank'] == 0 and corrected['iram_clear_completed']

    image, asm, checksum = make(reviewed, stock)
    # Verify the normal tick keeps its newly used bank-2 scratch register intact.
    for scratch in range(256):
        cpu = CPU(image)
        cpu.iram[0x12] = scratch
        start_sp = cpu.sp
        assert original_test.call(cpu, asm.labels['tick']) == 'sentinel'
        assert cpu.iram[0x12] == scratch and cpu.sp == start_sp

    # Exhaust interrupt delivery at each instruction boundary of kick/arm.
    # Shared word resets are protected; restored IE must retain its exact value.
    injections = 0
    for label, target in [('kick', 0x07c4), ('arm', 0x39da)]:
        for entry_ie in (0x0a, 0x8a):
            for boundary in range(32):
                cpu = CPU(image)
                cpu.ie = entry_ie
                cpu.ea = bool(entry_ie & 0x80)
                cpu.xram[reviewed.VAR_MAIN] = 0
                cpu.xram[reviewed.VAR_MAIN + 1] = 0xff
                cpu.xram[reviewed.VAR_ARM] = 0
                cpu.xram[reviewed.VAR_ENUM] = (reviewed.T2 - 1) >> 8
                cpu.xram[reviewed.VAR_ENUM + 1] = (reviewed.T2 - 1) & 255
                cpu.push(original_test.SENT & 255)
                cpu.push(original_test.SENT >> 8)
                cpu.pc = asm.labels[label]
                step = 0
                while cpu.pc != target:
                    if step == boundary and cpu.ea:
                        inject_timer(cpu, asm.labels['tick'])
                        injections += 1
                    cpu.step()
                    step += 1
                    assert step < 40
                assert cpu.rd_dir(0xa8) == entry_ie
                if label == 'kick':
                    value = (cpu.xram[reviewed.VAR_MAIN] << 8) | cpu.xram[reviewed.VAR_MAIN + 1]
                else:
                    assert cpu.xram[reviewed.VAR_ARM] == 1
                    value = (cpu.xram[reviewed.VAR_ENUM] << 8) | cpu.xram[reviewed.VAR_ENUM + 1]
                assert value in (0, 1), (label, boundary, value)

    # Retain the original bounded logic suite, with the extended interpreter.
    original_test.CPU = CPU
    original_test.B = reviewed
    old_args = sys.argv[:]
    sys.argv = ['upstream-test_exp2.py', str(stock_path)]
    try:
        try:
            original_test.main()
        except SystemExit as result:
            assert result.code == 0
    finally:
        sys.argv = old_args

    print(json.dumps({
        'legacy_startup': legacy, 'reviewed_startup': corrected,
        'scratch_values_tested': 256, 'atomic_operation_cases': 128,
        'delivered_interrupt_injections': injections,
        'reviewed_code_bytes': len(asm.build()), 'reviewed_checksum': hex(checksum),
        'limits': 'CPU instruction models only; no hardware reset, USB, clock, RAM-ownership or trigger validation',
        'firmware_file_written': False,
    }, indent=2))


if __name__ == '__main__':
    if len(sys.argv) != 2:
        raise SystemExit('Usage: python test_review.py STOCK_44_BIN')
    main(pathlib.Path(sys.argv[1]))
