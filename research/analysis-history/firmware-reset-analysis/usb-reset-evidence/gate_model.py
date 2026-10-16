"""Bounded control-flow model, not an MCU or USB emulator.

Models only observed branches; hardware flags, event arrival, 4CE2 internals,
and scheduler delivery are deliberately inputs/unknowns.
"""
import json
from pathlib import Path

def normal_service(dd2, dd3, dd1, reset_pending):
    # 36EB -> R7, then 4DBA.
    if dd2 and dd3:
        return '4CE2 transition' if dd1 else '4F65 return; reset uninspected'
    return '35DD reset handler' if reset_pending else 'normal endpoint service'

def alternate_service(dd2, dd3, reset_pending, ad08):
    # 1F93 calls 4F75 iff 08AD; 4F75 clears flags iff 36EB returns 1.
    if not ad08:
        return {'called': False, 'dd3': dd3, 'ad08': ad08, 'path': 'not called'}
    active = bool(dd2 and dd3)
    return {'called': True, 'dd3': 0 if active else dd3,
            'ad08': 0 if active else ad08,
            'path': '35DD reset handler' if reset_pending else 'other wake/EP0 handling'}

rows = []
for dd2 in (0, 1):
    for dd3 in (0, 1):
        for dd1 in (0, 1):
            rows.append({'dd2': dd2, 'dd3': dd3, 'dd1': dd1,
                         'reset_pending': True,
                         'normal': normal_service(dd2, dd3, dd1, True),
                         'alternate_if_delivered_and_ad08_1': alternate_service(dd2, dd3, True, 1)})
assert normal_service(1, 1, 0, True) == '4F65 return; reset uninspected'
assert normal_service(1, 0, 0, True) == '35DD reset handler'
assert normal_service(1, 1, 1, True) == '4CE2 transition'
assert alternate_service(1, 1, True, 1) == {'called': True, 'dd3': 0, 'ad08': 0, 'path': '35DD reset handler'}
assert not alternate_service(1, 1, True, 0)['called']
out = {'kind': 'bounded static branch model', 'hardware_execution': False,
       'unknowns': ['Can reset event arrive while these state values persist?',
                    'Does wake dispatcher necessarily invoke 1F93?',
                    'Are USB registers accessible before the wake sequence?',
                    'Does 2F52 bit2 mean bus reset on this exact chip?'],
       'rows': rows, 'assertions_passed': 5}
Path(__file__).with_name('gate_model.json').write_text(json.dumps(out, indent=2))
print('5 branch assertions passed; 8 combinations modeled; hardware behavior unverified')
