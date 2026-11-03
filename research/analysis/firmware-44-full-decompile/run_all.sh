#!/bin/sh
# Full firmware decompile pipeline (Ghidra headless + seed iteration). Run from analysis/app44.
G=D:/Projects/Rea/tools/ghidra_12.1.4_PUBLIC
export JAVA_HOME=D:/Projects/Rea/tools/jdk-21; export PATH="$JAVA_HOME/bin:$PATH"
OUT=D:/Projects/Y540-Keyboard/analysis/app44/full
run() { cmd //c "$G/support/analyzeHeadless.bat" "$TEMP/ghall" all44 -import app44-full64k.bin -overwrite -processor 8051:BE:16:default -loader BinaryLoader -scriptPath . -preScript DisableNoReturn.java -postScript DecompileAll.java "$OUT" "$@" -deleteProject > full/ghidra-run.log 2>&1; grep 'instruction bytes' full/coverage-log.txt; }
rm -f seeds-all.txt seeds.txt
run
for i in 1 2 3 4 5 6; do
  python -I classify_unreached.py full/coverage-log.txt
  n0=$(cat seeds-all.txt 2>/dev/null | wc -l)
  python -I filter_seeds.py | head -12
  n1=$(wc -l < seeds-all.txt)
  [ "$i" -gt 1 ] && [ "$n0" = "$n1" ] && break
  run D:/Projects/Y540-Keyboard/analysis/app44/seeds-all.txt
done
python -I classify_unreached.py full/coverage-log.txt
