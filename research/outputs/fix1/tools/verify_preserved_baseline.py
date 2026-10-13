"""Read-only verification of the neighboring baseline and previous archives."""
from pathlib import Path
import hashlib
import json
import subprocess

root = Path(__file__).resolve().parents[1]
outputs = root.parent
baseline = outputs/'y540-research'
record = json.loads((root/'evidence/baseline-preservation.json').read_text())
for entry in record['files']:
    digest = hashlib.sha256((baseline/entry['path']).read_bytes()).hexdigest()
    assert digest == entry['sha256'], 'Baseline changed: '+entry['path']
head = subprocess.check_output(['git', '-C', str(baseline), 'rev-parse', 'HEAD'], text=True).strip()
assert head == record['baseline_git_commit']
status = subprocess.check_output(['git', '-C', str(baseline), 'status', '--porcelain'], text=True).strip()
assert not status, 'Baseline checkout is not clean'
release = json.loads((outputs/'y540-release-manifest.json').read_text())
for entry in release['files']:
    digest = hashlib.sha256((outputs/entry['name']).read_bytes()).hexdigest()
    assert digest == entry['sha256'], 'Old release changed: '+entry['name']
fixtures = json.loads((root/'samples/manifest.json').read_text(encoding='utf-8-sig'))
for entry in fixtures['files']:
    digest = hashlib.sha256((root/'samples'/entry['name']).read_bytes()).hexdigest()
    assert digest.lower() == entry['sha256'].lower(), 'Input changed: '+entry['name']
result = {'baseline_commit': head, 'baseline_source_files': len(record['files']),
          'baseline_git_status': 'clean', 'previous_release_archives_unchanged': len(release['files']),
          'preserved_inputs_verified': len(fixtures['files']), 'firmware_modified': False}
(root/'evidence/baseline-preservation-result.json').write_text(json.dumps(result, indent=2), encoding='utf8')
print(json.dumps(result, indent=2))
