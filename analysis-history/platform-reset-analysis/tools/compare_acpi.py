from pathlib import Path
import json
root=Path(__file__).resolve().parents[1]
prior=json.loads((root/'bios35-36-acpi-inventory.json').read_text())
new=json.loads((root/'acpi/bios45-index.json').read_text())
result={}
for version in ['35','36']:
    hashes={x['sha256'] for x in prior[version]['tables']}
    result[version+'-to-45']={
        'bios45_table_count':len(new),
        'byte_identical_count':sum(x['sha256'] in hashes for x in new),
        'different_bios45_tables':[x['name'] for x in new if x['sha256'] not in hashes]}
(root/'acpi/comparison.json').write_text(json.dumps(result,indent=2))
print(json.dumps(result,indent=2))
