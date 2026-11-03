// Full decompile of keyboard firmware 44 (CODE 0000-D7FF) + bootloader (D800-FFFF).
// Follows Keil switch tables (?C?CCASE 890A / ?C?ISWITCH 8930 / boot F35A) to a fixpoint,
// then writes: all functions as C, the full listing, and a function table.
import ghidra.app.script.GhidraScript;
import ghidra.app.decompiler.*;
import ghidra.program.model.address.*;
import ghidra.program.model.listing.*;
import ghidra.program.model.symbol.*;
import ghidra.program.model.mem.*;
import java.io.*;
import java.util.*;

public class DecompileAll extends GhidraScript {
    AddressSpace code;
    Memory mem;
    Set<Long> tableBytes = new HashSet<>();
    PrintWriter tlog;

    int u8(long a) throws Exception { return mem.getByte(code.getAddress(a)) & 0xFF; }
    Address A(long a) { return code.getAddress(a); }

    void seed(long a, String why) throws Exception {
        if (a < 0 || a > 0xFFFF || u8(a) == 0xFF) return;
        if (getInstructionAt(A(a)) == null) { disassemble(A(a)); tlog.println(String.format("seed %04X %s", a, why)); }
        if (getFunctionAt(A(a)) == null && getFunctionContaining(A(a)) == null) createFunction(A(a), null);
    }

    // returns number of new seeds
    int followTables() throws Exception {
        int added = 0;
        long[][] helpers = {{0x890A, 3}, {0x8930, 4}, {0xF35A, 3}};
        InstructionIterator it = currentProgram.getListing().getInstructions(true);
        List<Instruction> calls = new ArrayList<>();
        while (it.hasNext()) { Instruction i = it.next(); if (i.getMnemonicString().equals("LCALL")) calls.add(i); }
        for (Instruction i : calls) {
            long site = i.getAddress().getOffset();
            long tgt = ((u8(site + 1) << 8) | u8(site + 2));
            for (long[] h : helpers) {
                if (tgt != h[0]) continue;
                long p = site + 3; int n = 0;
                while (true) {
                    int hi = u8(p), lo = u8(p + 1);
                    if (hi == 0 && lo == 0) {
                        long def = (u8(p + 2) << 8) | u8(p + 3);
                        for (long b = site + 3; b < p + 4; b++) tableBytes.add(b);
                        Instruction bogus = getInstructionContaining(A(site + 3));
                        if (bogus != null) { clearListing(A(site + 3), A(p + 3)); added++; }
                        tlog.println(String.format("table at %04X helper %04X entries %d default %04X", site, h[0], n, def));
                        if (getInstructionAt(A(def)) == null) { seed(def, "switch default from " + Long.toHexString(site)); added++; }
                        break;
                    }
                    long t = (hi << 8) | lo;
                    if (getInstructionAt(A(t)) == null) { seed(t, "switch case from " + Long.toHexString(site)); added++; }
                    p += h[1]; n++;
                    if (n > 200) { tlog.println("table too long at " + Long.toHexString(site)); break; }
                }
            }
        }
        return added;
    }

    Set<Long> heuristic = new HashSet<>();
    void seedFile() throws Exception {
        if (getScriptArgs().length > 1) {
            for (String line : java.nio.file.Files.readAllLines(java.nio.file.Paths.get(getScriptArgs()[1]))) {
                if (line.trim().isEmpty()) continue;
                long a = Long.parseLong(line.substring(0, 4), 16);
                if (getInstructionContaining(A(a)) != null) continue;
                Data dd = getDataContaining(A(a));
                if (dd != null && dd.isDefined()) clearListing(dd.getMinAddress(), dd.getMaxAddress());
                disassemble(A(a));
                if (getInstructionAt(A(a)) == null) { tlog.println("seed FAILED " + line); continue; }
                int ei = line.indexOf("END=");
                if (ei > 0) {   // linear sweep through the whole heuristic region
                    long end = Long.parseLong(line.substring(ei + 4, ei + 8), 16), p = a;
                    while (p <= end) {
                        Instruction ii = getInstructionContaining(A(p));
                        if (ii == null) { disassemble(A(p)); ii = getInstructionContaining(A(p)); }
                        p = ii == null ? p + 1 : ii.getMaxAddress().getOffset() + 1;
                    }
                }
                if (line.contains("heuristic") || line.contains("target")) {
                    if (getFunctionContaining(A(a)) == null) {
                        Function hf = createFunction(A(a), null);
                        if (hf != null && line.contains("heuristic")) { hf.setName("H_" + String.format("%04X", a), SourceType.USER_DEFINED); heuristic.add(a); }
                    }
                }
                tlog.println("extra seed " + line);
            }
        }
    }

    public void run() throws Exception {
        code = currentProgram.getAddressFactory().getDefaultAddressSpace();
        mem = currentProgram.getMemory();
        String outDir = getScriptArgs()[0];
        tlog = new PrintWriter(new FileWriter(outDir + "/coverage-log.txt"));
        long[] roots = {0x0000, 0x0003, 0x000B, 0x0013, 0x001B, 0x0023, 0x002B, 0xE000, 0xE003};
        // switch helpers pop their return address and never return to the call site
        for (long h : new long[]{0x890A, 0x8930, 0xF35A}) {
            disassemble(A(h));
            Function hf = getFunctionAt(A(h));
            if (hf == null) hf = createFunction(A(h), null);
            if (hf != null) hf.setNoReturn(true);
        }
        for (long r : roots) seed(r, "vector/root");
        analyzeAll(currentProgram);
        for (int round = 0; round < 20; round++) {
            int n = followTables();
            tlog.println("round " + round + " new seeds " + n);
            if (n == 0) break;
            analyzeAll(currentProgram);
        }
        seedFile();
        analyzeAll(currentProgram);
        tlog.println("post-seed table pass " + followTables());
        analyzeAll(currentProgram);
        tlog.println("second seed pass");
        seedFile();
        // coverage
        long codeBytes = 0, appNonFF = 0;
        for (long a = 0; a < 0x10000; a++) {
            if (u8(a) != 0xFF && a < 0xD800) appNonFF++;
            Instruction ins = getInstructionContaining(A(a));
            if (ins != null) codeBytes++;
        }
        tlog.println("instruction bytes total " + codeBytes + " app non-FF " + appNonFF + " table bytes " + tableBytes.size());
        // unreached non-FF runs
        long runStart = -1;
        for (long a = 0; a <= 0x10000; a++) {
            boolean un = a < 0x10000 && u8(a) != 0xFF && getInstructionContaining(A(a)) == null && !tableBytes.contains(a);
            if (un && runStart < 0) runStart = a;
            if (!un && runStart >= 0) { if (a - runStart >= 4) tlog.println(String.format("unreached %04X-%04X (%d bytes)", runStart, a - 1, a - runStart)); runStart = -1; }
        }
        tlog.close();
        // listing
        try (PrintWriter w = new PrintWriter(new FileWriter(outDir + "/full-listing.asm"))) {
            InstructionIterator it = currentProgram.getListing().getInstructions(true);
            Function last = null;
            while (it.hasNext()) {
                Instruction i = it.next();
                Function f = getFunctionContaining(i.getAddress());
                if (f != null && f != last && f.getEntryPoint().equals(i.getAddress())) w.println("\n; ===== " + f.getName());
                last = f;
                w.println(i.getAddress() + "  " + i);
            }
        }
        // functions
        DecompInterface d = new DecompInterface();
        d.openProgram(currentProgram);
        try (PrintWriter w = new PrintWriter(new FileWriter(outDir + "/full-decompiled.c"));
             PrintWriter t = new PrintWriter(new FileWriter(outDir + "/functions.tsv"))) {
            t.println("entry\tbytes\tregion\tcallers\tcallees");
            for (Function f : currentProgram.getFunctionManager().getFunctions(true)) {
                StringBuilder cs = new StringBuilder(), ce = new StringBuilder();
                for (Function c : f.getCallingFunctions(monitor)) cs.append(c.getEntryPoint()).append(' ');
                for (Function c : f.getCalledFunctions(monitor)) ce.append(c.getEntryPoint()).append(' ');
                long e = f.getEntryPoint().getOffset();
                t.println(f.getEntryPoint() + "\t" + f.getBody().getNumAddresses() + "\t" + (e >= 0xD800 ? "boot" : "app") + "\t" + cs.toString().trim() + "\t" + ce.toString().trim());
                w.println("// ===== " + f.getName() + "  [" + (e >= 0xD800 ? "bootloader" : "app") + "]  callers: " + cs.toString().trim());
                DecompileResults r = d.decompileFunction(f, 120, monitor);
                w.println(r.decompileCompleted() ? r.getDecompiledFunction().getC() : "// decompile failed: " + r.getErrorMessage());
            }
        }
        println("done");
    }
}
