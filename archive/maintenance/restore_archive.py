"""Verify or restore the complete Y540 preservation archive using Python 3.11+.

No firmware or archived program is executed. Existing files are never overwritten.
"""
import argparse
import collections
import gzip
import hashlib
import json
import os
import pathlib
import time
import zipfile


def safe_target(destination, root, relative):
    root_path, rel = pathlib.PurePosixPath(root), pathlib.PurePosixPath(relative)
    for p in (root_path, rel):
        if p.is_absolute() or '..' in p.parts or any(':' in s for s in p.parts):
            raise ValueError('Unsafe archive path')
    target = destination.joinpath(*root_path.parts, *rel.parts)
    if not target.resolve().is_relative_to(destination.resolve()):
        raise ValueError('Path escapes restore directory')
    return target


def restore(archive_dir, destination=None, selected_roots=None, prefix=''):
    with gzip.open(archive_dir / 'object-index.json.gz', 'rt', encoding='utf8') as f:
        catalog = json.load(f)
    if catalog['format'] != 'y540-content-archive-v1':
        raise ValueError('Unsupported archive format')
    with gzip.open(archive_dir / 'file-index.jsonl.gz', 'rt', encoding='utf8') as f:
        records = [json.loads(line) for line in f]
    selected = [r for r in records if
                (not selected_roots or r['root'] in selected_roots) and
                (not prefix or r['path'].startswith(prefix))]
    if selected_roots and any(r not in catalog['roots'] for r in selected_roots):
        raise ValueError('Unknown root selector')
    if not selected:
        raise ValueError('No matching files or directories')
    objects = catalog['objects']
    needed = {objects[b]['part'] for r in selected if r['kind'] == 'file' for b in r['blocks']}
    for part in catalog['parts']:
        if part['name'] not in needed:
            continue
        path = archive_dir / part['name']
        if path.stat().st_size != part['bytes']:
            raise ValueError('Part size mismatch: ' + part['name'])
        with path.open('rb') as f:
            if hashlib.file_digest(f, 'sha256').hexdigest() != part['sha256']:
                raise ValueError('Part checksum mismatch: ' + part['name'])
    opened = collections.OrderedDict()
    full_hashes = {}
    verified_objects = set()
    count = total = 0
    started = time.monotonic()

    def get_zip(name):
        if name in opened:
            opened.move_to_end(name)
            return opened[name]
        if len(opened) >= 8:
            _, old = opened.popitem(last=False)
            old.close()
        opened[name] = zipfile.ZipFile(archive_dir / name)
        return opened[name]

    try:
        for record in selected:
            target = safe_target(destination or pathlib.Path.cwd(), record['root'], record['path'])
            if record['kind'] == 'directory':
                if destination:
                    target.mkdir(parents=True, exist_ok=True)
                continue
            if record['kind'] == 'symlink':
                if destination:
                    # Preserve link metadata without creating a link to outside data.
                    target.parent.mkdir(parents=True, exist_ok=True)
                    with target.with_name(target.name + '.symlink.json').open('x', encoding='utf8') as f:
                        json.dump(record, f, indent=2)
                continue
            signature = (record['bytes'], tuple(record['blocks']))
            known = full_hashes.get(record['sha256'])
            if known is not None and known != signature:
                raise ValueError('Inconsistent duplicate file index')
            if not destination and known is not None:
                count += 1
                total += record['bytes']
                continue
            stream = None
            if destination:
                target.parent.mkdir(parents=True, exist_ok=True)
                stream = target.open('xb')
            file_hash, size = hashlib.sha256(), 0
            try:
                for block in record['blocks']:
                    item = objects[block]
                    with get_zip(item['part']).open('objects/' + block) as f:
                        block_hash, block_size = hashlib.sha256(), 0
                        while data := f.read(1024 * 1024):
                            file_hash.update(data)
                            block_hash.update(data)
                            size += len(data)
                            block_size += len(data)
                            if stream:
                                stream.write(data)
                    if block_size != item['bytes'] or block_hash.hexdigest() != block:
                        raise ValueError('Object checksum mismatch: ' + block)
                    verified_objects.add(block)
            finally:
                if stream:
                    stream.close()
            if size != record['bytes'] or file_hash.hexdigest() != record['sha256']:
                raise ValueError('File checksum mismatch: ' + record['root'] + '/' + record['path'])
            if destination:
                os.utime(target, ns=(record['mtime_ns'], record['mtime_ns']))
            full_hashes[record['sha256']] = signature
            count += 1
            total += size
            if count % 1000 == 0 or size > 64 * 1024 * 1024:
                print('Verified', count, 'files; represented GiB', round(total / 2**30, 2), flush=True)
    finally:
        for f in opened.values():
            f.close()
    result = {'status': 'passed', 'files': count, 'represented_bytes': total,
              'unique_file_hashes_checked': len(full_hashes),
              'objects_content_checked': len(verified_objects), 'parts_checked': len(needed),
              'mode': 'restore' if destination else 'verify-only',
              'roots': selected_roots or list(catalog['roots']),
              'seconds': round(time.monotonic() - started, 1),
              'archived_target_execution': False}
    print(json.dumps(result, indent=2), flush=True)
    return result


if __name__ == '__main__':
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('--archive-dir', type=pathlib.Path, required=True)
    parser.add_argument('--destination', type=pathlib.Path)
    parser.add_argument('--verify-only', action='store_true')
    parser.add_argument('--root', action='append')
    parser.add_argument('--prefix', default='')
    args = parser.parse_args()
    if bool(args.destination) == bool(args.verify_only):
        parser.error('Choose --destination NEW_DIRECTORY or --verify-only')
    restore(args.archive_dir, args.destination, args.root, args.prefix)
