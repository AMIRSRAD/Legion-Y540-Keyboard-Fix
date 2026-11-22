"""Generate fw_images.h (FW_EXP7, FW_STOCK44) from the official download ZIP, after checking SHA-256.
Usage: python gen_fw_images.py Y540-Keyboard-Fix.zip   (writes fw_images.h next to this script)"""
import hashlib, sys, zipfile, pathlib
WANT = {'FW_EXP7': ('44-reset-exp7.bin', 'fc0d0141e9468288f11d762f69820022e2936f7b9ccbf42cff147ea24e8a28c0'),
        'FW_STOCK44': ('other-firmware/44-original-lenovo.bin', '3afec131c6ed70efa0a3f4b601cb799011a582835d371c57fef68af48519e359')}
z = zipfile.ZipFile(sys.argv[1]); names = {n.replace(chr(92), '/'): n for n in z.namelist()}
out = ''
for var, (rel, sha) in WANT.items():
    key = next(k for k in names if k.endswith('/' + rel) or k == rel)
    data = z.read(names[key])
    assert len(data) == 55296 and hashlib.sha256(data).hexdigest() == sha, 'hash mismatch for ' + rel
    out += 'static const unsigned char %s[55296] = {%s};\n' % (var, ','.join(str(b) for b in data))
(pathlib.Path(__file__).parent / 'fw_images.h').write_text(out)
print('wrote fw_images.h (exp7 and original 44 verified)')
