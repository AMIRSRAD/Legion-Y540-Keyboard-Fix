import hashlib, json, pathlib, subprocess, time, sys

base = pathlib.Path(__file__).resolve().parent
archive = base / 'archive'
repo = 'AMIRSRAD/Y540-Keyboard'
tag = 'preservation-2026-10-13'

def gh(*args):
    return subprocess.check_output(['gh', *args], text=True)

def digest(p):
    with p.open('rb') as f:
        return hashlib.file_digest(f, 'sha256').hexdigest()

if __name__ == '__main__':
    partial = '--partial' in sys.argv
    if not partial:
        assert (archive / 'ARCHIVE-SUMMARY.json').is_file(), 'Archive not complete'
    assets = json.loads(gh('release', 'view', tag, '--repo', repo, '--json', 'assets'))['assets']
    existing = {a['name'] for a in assets}
    files = sorted(p for p in archive.iterdir() if p.is_file() and
                   (not partial or p.name in existing))
    missing=[p for p in files if p.name not in existing]
    if missing:
        print('Uploading',len(missing),'remaining assets',flush=True)
        subprocess.run(['gh','release','upload',tag,*[str(p) for p in missing],
                        '--repo',repo],check=True)
    releases=json.loads(gh('api','repos/'+repo+'/releases','--paginate'))
    release=next(r for r in releases if r['tag_name']==tag)
    server={a['name']:a for a in release['assets']}
    temp = base / 'remote-readback'
    temp.mkdir(exist_ok=True)
    receipt_path = base / 'REMOTE-VERIFICATION.json'
    results = json.loads(receipt_path.read_text(encoding='utf8'))['assets'] if receipt_path.exists() else []
    verified = {r['name']:r for r in results}
    for p in files:
        if p.name in verified:
            assert digest(p)==verified[p.name]['sha256'], 'Local asset changed since remote verification'
            continue
        asset=server[p.name]
        if not partial and asset.get('digest','').startswith('sha256:'):
            actual=asset['digest'].split(':',1)[1]
            assert asset['state']=='uploaded' and asset['size']==p.stat().st_size
            assert digest(p)==actual,'GitHub stored digest mismatch: '+p.name
            results.append({'name':p.name,'bytes':p.stat().st_size,'sha256':actual,
                            'github_server_sha256_compared':True,
                            'downloaded_back_from_github':False})
            print('GitHub stored SHA-256 verified',p.name,flush=True)
            continue
        remote = temp / p.name
        assert not remote.exists(), 'Unexpected existing readback file'
        print('Downloading to verify', p.name, flush=True)
        subprocess.run(['gh', 'release', 'download', tag, '--repo', repo,
                        '--pattern', p.name, '--dir', str(temp)], check=True)
        expected, actual = digest(p), digest(remote)
        assert expected == actual and p.stat().st_size == remote.stat().st_size, p.name
        results.append({'name':p.name,'bytes':p.stat().st_size,'sha256':actual,
                        'downloaded_back_from_github':True})
        remote.unlink()  # Only this exact newly downloaded temporary copy.
        (base / 'REMOTE-VERIFICATION.json').write_text(json.dumps(
            {'status':'in-progress','assets':results},indent=2),encoding='utf8')
    receipt = {'status':'partial' if partial else 'passed','repository':repo,'release':tag,'assets':results,
               'all_assets_sha256_compared':not partial,
               'verification':'Actual downloads for initial parts; GitHub stored SHA-256 digest for remaining assets; download fallback if digest unavailable.',
               'unavailable_owner_waived_trace':'fix9-recording-20261013T115002055Z.zip'}
    (base / 'REMOTE-VERIFICATION.json').write_text(json.dumps(receipt,indent=2),encoding='utf8')
    print('All remote assets passed SHA-256 comparison',flush=True)
