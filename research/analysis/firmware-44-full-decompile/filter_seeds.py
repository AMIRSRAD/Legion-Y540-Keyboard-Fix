"""Merge seeds.txt into seeds-all.txt, dropping heuristic seeds that start a MOVC data table
or a USB descriptor (evidence recomputed from the current listing)."""
import re, importlib.util, sys
spec = importlib.util.spec_from_file_location('cu', 'classify_unreached.py')
sys.argv = ['x', 'full/coverage-log.txt']
cu = importlib.util.module_from_spec(spec); spec.loader.exec_module(cu)
lines = {}
for fn in ('seeds-all.txt', 'seeds.txt'):
    try:
        for l in open(fn):
            l = l.rstrip('\n')
            if l: lines.setdefault(l[:4], l)
    except FileNotFoundError: pass
keep = []; dropped = []
for a, l in sorted(lines.items()):
    x = int(a, 16)
    if 'heuristic' in l and (x in cu.dptr_data or cu.descriptor_like(cu.d[x:x + 64])):
        dropped.append(l); continue
    keep.append(l)
open('seeds-all.txt', 'w').write('\n'.join(keep) + '\n')
print('seeds kept', len(keep), 'dropped', len(dropped))
for l in dropped: print('  drop', l)
