// Decompile app firmware 44 (+ bootloader upper dump) around the idle/sleep gate.
import ghidra.app.script.GhidraScript;
import ghidra.app.decompiler.*;
import ghidra.program.model.address.*;
import ghidra.program.model.listing.*;
import java.io.*;
import java.util.*;

public class DecompileApp extends GhidraScript {
    public void run() throws Exception {
        AddressSpace code = currentProgram.getAddressFactory().getDefaultAddressSpace();
        List<Integer> seeds = new ArrayList<>(Arrays.asList(0x0000, 0x26B7, 0x26E2, 0x4BC4, 0x4C68, 0x4D25, 0x4F87, 0x36E0, 0x2630));
        for (int v = 0x03; v <= 0x83; v += 8) seeds.add(v);
        for (int s : seeds) disassemble(code.getAddress(s));
        analyzeAll(currentProgram);
        for (int s : new int[]{0x26B7, 0x26E2, 0x4BC4}) {
            Address a = code.getAddress(s);
            if (getFunctionContaining(a) == null) createFunction(a, null);
        }
        String out = getScriptArgs()[0];
        DecompInterface d = new DecompInterface();
        d.openProgram(currentProgram);
        Set<Function> done = new HashSet<>();
        try (PrintWriter w = new PrintWriter(new FileWriter(out))) {
            int[] want = {0x26B7, 0x26E2, 0x4BC4, 0x4C68, 0x4D25, 0x4D75, 0x4F87, 0x36EB, 0x4BBD, 0x2633, 0x35DF, 0x3A05};
            for (int s : want) {
                Function f = getFunctionContaining(code.getAddress(s));
                if (f == null) { w.println("// no function for " + Integer.toHexString(s)); continue; }
                if (!done.add(f)) continue;
                w.println("// ===== " + f.getName() + " @ " + f.getEntryPoint() + " (contains " + Integer.toHexString(s) + ")");
                for (Function c : f.getCallingFunctions(monitor)) w.println("//   called by " + c.getName());
                DecompileResults r = d.decompileFunction(f, 120, monitor);
                w.println(r.decompileCompleted() ? r.getDecompiledFunction().getC() : "// failed " + r.getErrorMessage());
            }
            w.println("// ===== LISTING");
            int[][] ranges = {{0x26B7, 0x2760}, {0x4BA0, 0x4D00}, {0x4D20, 0x4DE0}, {0x4F80, 0x4FE0}};
            for (int[] rg : ranges) {
                w.println("// --- " + Integer.toHexString(rg[0]));
                InstructionIterator it = currentProgram.getListing().getInstructions(new AddressSet(code.getAddress(rg[0]), code.getAddress(rg[1])), true);
                while (it.hasNext()) { Instruction i = it.next(); w.println(i.getAddress() + "  " + i); }
            }
        }
        println("wrote " + out);
    }
}
