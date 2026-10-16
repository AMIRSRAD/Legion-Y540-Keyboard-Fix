"""Lossless content-addressed preservation archive. No source deletion.

Every regular file is indexed with its root, relative path, size, SHA-256,
mtime and ordered content-block hashes. Duplicate bytes are stored once.
"""
import argparse
import gzip
import hashlib
import json
import os
import pathlib
import stat
import time
import zipfile


def digest(path):
    with path.open('rb') as stream:
        return hashlib.file_digest(stream, 'sha256').hexdigest()


def build(config, destination):
    destination.mkdir(parents=True, exist_ok=False)
    block_size = config.get('block_bytes', 64 * 1024 * 1024)
    part_budget = config.get('part_bytes', 384 * 1024 * 1024)
    files, directories, links = [], [], []
    root_summary = {}
    for label, item in config['roots'].items():
        root = pathlib.Path(item['path']).resolve(strict=True)
        assert not destination.resolve().is_relative_to(root), 'Archive would include itself'
        root_summary[label] = {'files': 0, 'bytes': 0, 'directories': 0, 'links': 0}
        if 'include_files' in item:
            candidates = [root / name for name in item['include_files']]
        else:
            candidates = []
            for base, dirs, names in os.walk(root, followlinks=False):
                base = pathlib.Path(base)
                directories.append({'kind': 'directory', 'root': label,
                                    'path': base.relative_to(root).as_posix()})
                root_summary[label]['directories'] += 1
                for name in list(dirs):
                    p = base / name
                    if p.is_symlink():
                        candidates.append(p)
                        dirs.remove(name)
                candidates.extend(base / name for name in names)
        for p in candidates:
            relative = p.relative_to(root).as_posix()
            if p.is_symlink():
                links.append({'kind': 'symlink', 'root': label, 'path': relative,
                              'target': os.readlink(p)})
                root_summary[label]['links'] += 1
                continue
            info = p.stat()
            if not stat.S_ISREG(info.st_mode):
                raise RuntimeError('Non-regular file needs explicit preservation: ' + str(p))
            files.append((label, relative, p, info))
            root_summary[label]['files'] += 1
            root_summary[label]['bytes'] += info.st_size
    # Current source/evidence first, large precompressed containers last.
    files.sort(key=lambda f: (f[3].st_size > block_size,
                             not (f[0] == 'workspace' and f[1].startswith('outputs/fix9')),
                             f[0], f[1]))
    objects, parts = {}, []
    archive, part_path, part_used = None, None, 0
    unique_bytes, processed_bytes = 0, 0
    started = time.monotonic()

    def close_part():
        nonlocal archive
        if archive is not None:
            archive.close()
            parts.append({'name': part_path.name, 'bytes': part_path.stat().st_size,
                          'sha256': digest(part_path)})
            print('Closed', part_path.name, 'MiB', round(part_path.stat().st_size / 2**20, 1), flush=True)
            archive = None

    with gzip.open(destination / 'file-index.jsonl.gz', 'wt', encoding='utf8') as index:
        for entry in directories + links:
            index.write(json.dumps(entry, ensure_ascii=False) + '\n')
        for ordinal, (label, relative, source, original) in enumerate(files, 1):
            file_hash, blocks = hashlib.sha256(), []
            with source.open('rb') as stream:
                while block := stream.read(block_size):
                    file_hash.update(block)
                    sha = hashlib.sha256(block).hexdigest()
                    blocks.append(sha)
                    if sha not in objects:
                        if archive is None or part_used + len(block) > part_budget:
                            close_part()
                            part_path = destination / ('archive-part-%04d.zip' % (len(parts) + 1))
                            archive = zipfile.ZipFile(part_path, 'x', allowZip64=True)
                            part_used = 0
                        compressed = source.suffix.lower() in {'.zip','.rar','.7z','.gz','.xz','.zst','.jar','.whl','.bz2','.png','.jpg','.jpeg'}
                        archive.writestr('objects/' + sha, block,
                                         compress_type=zipfile.ZIP_STORED if compressed else zipfile.ZIP_DEFLATED,
                                         compresslevel=6)
                        objects[sha] = {'part': part_path.name, 'bytes': len(block)}
                        unique_bytes += len(block)
                        part_used += len(block)
            after = source.stat()
            if (after.st_size, after.st_mtime_ns) != (original.st_size, original.st_mtime_ns):
                raise RuntimeError('Source changed while archiving: ' + str(source))
            record = {'kind': 'file', 'root': label, 'path': relative,
                      'bytes': original.st_size, 'sha256': file_hash.hexdigest(),
                      'blocks': blocks, 'mtime_ns': original.st_mtime_ns,
                      'mode': stat.S_IMODE(original.st_mode)}
            index.write(json.dumps(record, ensure_ascii=False) + '\n')
            processed_bytes += original.st_size
            if ordinal % 1000 == 0 or original.st_size > block_size:
                print('Indexed', ordinal, '/', len(files), 'GiB', round(processed_bytes / 2**30, 2),
                      'unique GiB', round(unique_bytes / 2**30, 2), flush=True)
    close_part()
    catalog = {'format': 'y540-content-archive-v1', 'block_bytes': block_size,
               'roots': root_summary, 'parts': parts, 'objects': objects,
               'files': len(files), 'links': len(links), 'directories': len(directories),
               'source_bytes': processed_bytes, 'unique_object_bytes': unique_bytes,
               'content_exclusions': [], 'user_waived_unavailable_artifacts': config.get('user_waived_unavailable_artifacts', []), 'seconds': round(time.monotonic() - started, 1)}
    with gzip.open(destination / 'object-index.json.gz', 'wt', encoding='utf8') as f:
        json.dump(catalog, f, sort_keys=True)
    hashes = {p.name: {'bytes': p.stat().st_size, 'sha256': digest(p)}
              for p in destination.iterdir() if p.is_file()}
    (destination / 'ARCHIVE-SHA256.json').write_text(json.dumps(hashes, indent=2), encoding='utf8')
    summary = {k: v for k, v in catalog.items() if k != 'objects'}
    (destination / 'ARCHIVE-SUMMARY.json').write_text(json.dumps(summary, indent=2), encoding='utf8')
    print(json.dumps(summary, indent=2), flush=True)


if __name__ == '__main__':
    parser = argparse.ArgumentParser()
    parser.add_argument('configuration', type=pathlib.Path)
    parser.add_argument('destination', type=pathlib.Path)
    args = parser.parse_args()
    build(json.loads(args.configuration.read_text(encoding='utf8')), args.destination)
