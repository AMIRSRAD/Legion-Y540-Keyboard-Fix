# Experimental exp7 generator. Hardware behavior remains to be tested.
"""Build experimental firmware exp7: exp4 + a USB frame-counter watchdog in the timer ISR.

Why: exp4/exp6 hang their reset on stock's suspend gate (2F52 bit3 SOF flag,
16E0 line state, idle counter, main-loop timer task). After normal use none of
that fires at shutdown or at the BIOS->Windows handover.

The 2026-11-02 probe showed 2F55:2F56 is the hardware USB frame number
(11-bit, +1 per 1 ms SOF): two reads 866 ms apart advanced exactly 866, and
852 ms apart exactly 852. exp7 watches its low byte (2F56) from the timer-0
ISR, which runs every tick whatever the main loop or the USB status bits do:

  * frame changed  -> remember it, count towards arming (cap ARM_CHANGES),
                      clear the stall counter
  * frame unchanged and armed -> stall counter += 1; at STALL_TICKS the
                      controller enters the verified C4 reset path (F455)

Arming needs ARM_CHANGES real frame changes since power-on, so a powered-off
host (no SOF) can't make it restart in a loop: after one reset it
never re-arms until a host sends frames again. XDATA 0000-0FFF (variables at
0FF8-0FFB) is zeroed by the stock startup at every reset.

Timer-0 tick: TH0:TL0 reload FD00 (768 counts); stock counts 8 ticks as USB
suspend (3 ms) => ~384 us/tick, so STALL_TICKS 0x0400 ~= 0.4 s of no SOF: well
above a USB bus reset (10-50 ms), well below the BIOS->Windows handover gap.

exp4's changes (4C7B -> stub 8A00 -> F455) are kept unchanged.
"""
import hashlib, json, sys

from build_exp3 import Asm
import build_exp4 as E4

STOCK_SHA = E4.STOCK_SHA
UPPER_SHA = E4.UPPER_SHA
EXP4_SHA = '27438bf439766926420047b4cb65fcfca2417c7d6a36f7802d824f1f7f27ca34'
ISR_HOOK = 0x330A                       # timer-0 ISR: MOV PSW,#10h
ISR_ORIG = bytes.fromhex('75d010')
TICK = 0x8A10
FRAME_LO = 0x2F56
VAR_LAST = 0x0FF8                       # byte: last frame low byte seen
VAR_ARM = 0x0FF9                        # byte: frame changes seen, capped at ARM_CHANGES
VAR_STALL = 0x0FFA                      # word, big-endian: ticks without a frame change while armed
ARM_CHANGES = 16
STALL_TICKS = 0x0400
assert STALL_TICKS & 0xFF == 0


def program():
    a = Asm(TICK)
    a.label('tick')
    a.emit(0x75, 0xD0, 0x10)            # MOV PSW,#10h      (replaced ISR instruction)
    a.mov_dptr(FRAME_LO)
    a.emit(0xE0, 0xF5, 0xF0)            # MOVX A,@DPTR ; MOV B,A
    a.mov_dptr(VAR_LAST)
    a.emit(0xE0)                        # MOVX A,@DPTR
    a.rel(0xB5, 'changed', bytes([0xF0]))   # CJNE A,B,changed
    a.emit(0xA3, 0xE0)                  # INC DPTR ; MOVX A,@DPTR      (arm count)
    a.rel(0xB4, 'done', bytes([ARM_CHANGES]))   # CJNE A,#ARM,done    (not armed)
    a.mov_dptr(VAR_STALL + 1)
    a.emit(0xE0, 0x24, 0x01, 0xF0)      # MOVX A ; ADD A,#1 ; MOVX @DPTR,A
    a.mov_dptr(VAR_STALL)
    a.emit(0xE0, 0x34, 0x00, 0xF0)      # MOVX A ; ADDC A,#0 ; MOVX @DPTR,A
    a.rel(0xB4, 'done', bytes([STALL_TICKS >> 8]))  # CJNE A,#hi,done
    a.emit(0xC2, 0xAF)                  # CLR EA
    a.emit(0x75, 0xD0, 0x00)            # MOV PSW,#00h      (bank 0 for the bootloader delay)
    a.a16(0x02, 0xF455)                 # LJMP F455         (verified C4 detach + watchdog)
    a.label('changed')
    a.emit(0xE5, 0xF0, 0xF0)            # MOV A,B ; MOVX @DPTR,A      (last = frame)
    a.emit(0xA3, 0xE0)                  # INC DPTR ; MOVX A,@DPTR
    a.rel(0xB4, 'arm_inc', bytes([ARM_CHANGES]))
    a.rel(0x80, 'clear')
    a.label('arm_inc')
    a.emit(0x04, 0xF0)                  # INC A ; MOVX @DPTR,A
    a.label('clear')
    a.emit(0xA3, 0xE4, 0xF0, 0xA3, 0xF0)    # stall = 0
    a.label('done')
    a.emit(0x22)                        # RET (ISR continues with PSW=10h as stock)
    return a


def checksum(img):
    work = bytearray(img)
    work[0x7FFE] = work[0x7FFF] = 0xFF
    return sum(work[0x400:0xD800]) & 0xFFFF


def build(stock, upper):
    exp4, _ = E4.build(stock, upper)
    assert hashlib.sha256(exp4).hexdigest() == EXP4_SHA, 'exp4 base differs'
    img = bytearray(exp4)
    code = program().build()
    assert all(b == 0xFF for b in img[TICK:TICK + len(code)]), 'tick area not free'
    assert img[ISR_HOOK:ISR_HOOK + 3] == ISR_ORIG, 'ISR hook bytes differ'
    img[ISR_HOOK:ISR_HOOK + 3] = bytes([0x12, TICK >> 8, TICK & 0xFF])   # LCALL tick
    img[TICK:TICK + len(code)] = code
    s = checksum(img)
    img[0x7FFE], img[0x7FFF] = s >> 8, s & 0xFF
    return bytes(img), s


if __name__ == '__main__':
    from pathlib import Path
    if len(sys.argv) != 4:
        raise SystemExit('Usage: build_exp7.py STOCK_BIN UPPER_DUMP OUTPUT_BIN')
    stock = Path(sys.argv[1]).read_bytes()
    upper = Path(sys.argv[2]).read_bytes()
    image, s = build(stock, upper)
    out = Path(sys.argv[3])
    with out.open('xb') as f:
        f.write(image)
    manifest = {
        'experiment': 'exp7-frame-counter-watchdog',
        'image_sha256': hashlib.sha256(image).hexdigest(),
        'base_exp4_sha256': EXP4_SHA, 'stock_sha256': STOCK_SHA, 'upper_dump_sha256': UPPER_SHA,
        'checksum': '%04X' % s, 'bytes': len(image),
        'tick_code_bytes': len(program().build()),
        'arm_changes': ARM_CHANGES, 'stall_ticks': STALL_TICKS,
        'diffs': [{'offset': hex(i), 'before': a, 'after': b}
                  for i, (a, b) in enumerate(zip(stock, image)) if a != b],
        'hardware_validated': False,
        'limits': ['Restarts whenever the host stops sending frames for ~0.4 s after it had '
                   'been sending them: shutdown, restart, sleep, selective suspend. Keyboard '
                   'wake from sleep is lost (as with exp4).',
                   'Tick period inferred from stock suspend timing, not measured.',
                   'Cannot act if the CPU is halted or interrupts are permanently disabled.'],
    }
    out.with_suffix('.manifest.json').write_text(json.dumps(manifest, indent=2), encoding='utf8')
    print(json.dumps(manifest, indent=2))
