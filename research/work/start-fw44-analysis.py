from pathlib import Path
import json
q=Path('outputs/firmware44-analysis/work/queue')
(q/'001-open.json').write_text(json.dumps({'name':'open_binary','arguments':{'path':str(Path('outputs/y540-research/samples/44.bin').resolve()),'provider_id':'ghidra'}}),encoding='utf-8')
