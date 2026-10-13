from pathlib import Path
p=Path('outputs/y540-research/README.md');s=p.read_text(encoding='utf-8-sig').replace('python tools/firmware_review.py\n','python tools/firmware_review.py samples/44.bin --ini samples/SHFU.ini > firmware-review.json\n');p.write_text(s,encoding='utf8')
