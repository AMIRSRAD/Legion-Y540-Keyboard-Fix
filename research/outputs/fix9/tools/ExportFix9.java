// Static raw firmware analysis. Does not execute target code or alter input bytes.
import ghidra.app.script.GhidraScript;
import ghidra.app.decompiler.*;
import ghidra.program.model.address.*;
import ghidra.program.model.listing.*;
import ghidra.program.model.symbol.*;
import com.google.gson.*;
import java.nio.file.*;
import java.util.*;

public class ExportFix9 extends GhidraScript {
    public void run() throws Exception {
        AddressSpace code=currentProgram.getAddressFactory().getDefaultAddressSpace();
        int[] seeds={0x8a00,0x8a23,0x8a46,0x8a55,0x8a9e,0xf455,0xe000,0,3,11,19,27,35,43,0x100,0x3200,0x3300,0x3400,0x3500,0x3600,0x3700,0x46c2,0x46d2,0x4726,0x46b2,0x4665,0x468c,0x46e5,0x46fd,0x40e8,0x4106,0x4141,0x41ac,0x41d9,0x41db,0x41e7,0x4212,0x421e};
        for(int offset:seeds) {
            Address address=code.getAddress(offset);
            currentProgram.getSymbolTable().addExternalEntryPoint(address);
            disassemble(address);
            if(currentProgram.getFunctionManager().getFunctionAt(address)==null) createFunction(address,null);
        }
        analyzeAll(currentProgram);
        // CODE:8850 consumes four inline CODE bytes and jumps to callsite+7.
        // Model that observed helper explicitly; generic autoanalysis treats its
        // computed continuation as non-returning and can decode constants as code.
        JsonArray inlineCalls=new JsonArray();
        Set<String> fixed=new HashSet<>();
        for(int pass=0;pass<4;pass++) {
            Function helper=currentProgram.getFunctionManager().getFunctionAt(code.getAddress(0x8850));
            if(helper!=null) helper.setNoReturn(false);
            ArrayList<Address> calls=new ArrayList<>();
            for(Instruction i:currentProgram.getListing().getInstructions(true)) {
                if(i.getMnemonicString().equals("LCALL")) {
                    for(Address target:i.getFlows()) {
                        if(target.equals(code.getAddress(0x8850)) && !fixed.contains(i.getAddress().toString())) calls.add(i.getAddress());
                    }
                }
            }
            if(calls.isEmpty())break;
            for(Address a:calls) {
                Instruction i=getInstructionAt(a);i.setFallThrough(a.add(7));
                clearListing(a.add(3),a.add(6));
                for(int n=3;n<7;n++)createByte(a.add(n));
                disassemble(a.add(7));fixed.add(a.toString());inlineCalls.add(a.toString());
            }
            analyzeAll(currentProgram);
        }
        JsonObject result=new JsonObject();
        result.addProperty("language",currentProgram.getLanguageID().toString());
        result.addProperty("default_space",code.getName());
        result.addProperty("mapping_assumption","raw file offset equals CODE address at base 0; banking and chip-specific registers unverified");
        result.add("modeled_inline_constant_calls",inlineCalls);
        JsonArray blocks=new JsonArray();
        for(ghidra.program.model.mem.MemoryBlock b:currentProgram.getMemory().getBlocks()) {
            JsonObject j=new JsonObject();j.addProperty("name",b.getName());j.addProperty("start",b.getStart().toString());j.addProperty("end",b.getEnd().toString());j.addProperty("initialized",b.isInitialized());blocks.add(j);
        }
        result.add("memory",blocks);
        JsonArray instructions=new JsonArray();
        for(Instruction i:currentProgram.getListing().getInstructions(true)) {
            JsonObject j=new JsonObject();j.addProperty("address",i.getAddress().toString());j.addProperty("length",i.getLength());j.addProperty("text",i.toString());
            StringBuilder hex=new StringBuilder();for(byte b:i.getBytes())hex.append(String.format("%02x",b&255));j.addProperty("bytes",hex.toString());
            j.addProperty("flow_type",i.getFlowType().toString());
            JsonArray refs=new JsonArray();for(Reference r:i.getReferencesFrom()) {JsonObject q=new JsonObject();q.addProperty("to",r.getToAddress().toString());q.addProperty("type",r.getReferenceType().toString());refs.add(q);}j.add("references",refs);instructions.add(j);
        }
        result.add("instructions",instructions);
        DecompInterface decomp=new DecompInterface();decomp.openProgram(currentProgram);
        JsonArray functions=new JsonArray();
        for(Function f:currentProgram.getFunctionManager().getFunctions(true)) {
            JsonObject j=new JsonObject();j.addProperty("entry",f.getEntryPoint().toString());j.addProperty("name",f.getName());j.addProperty("body",f.getBody().toString());
            DecompileResults d=decomp.decompileFunction(f,20,monitor);j.addProperty("complete",d.decompileCompleted());j.addProperty("error",d.getErrorMessage());
            if(d.getDecompiledFunction()!=null)j.addProperty("pseudocode",d.getDecompiledFunction().getC());
            functions.add(j);
        }
        decomp.dispose();result.add("functions",functions);
        Path output=Paths.get(getScriptArgs()[0]);Files.createDirectories(output.getParent());Files.writeString(output,new GsonBuilder().setPrettyPrinting().create().toJson(result));
        println("FIRMWARE_EXPORT instructions="+instructions.size()+" functions="+functions.size()+" output="+output);
    }
}
