from pathlib import Path
import json
q=Path('outputs/y540-research/work/queue')
for i,addr in enumerate(['0x409cc0','0x40a280','0x40a620','0x40a690','0x40a7a0','0x40a830','0x40a8c0','0x40a910','0x40aa50','0x40aef0','0x40b8e0'],110):
 (q/f'{i:03d}-protocol-{addr[2:]}.json').write_text(json.dumps({'name':'procedure_pseudo_code','arguments':{'procedure':addr}}))
