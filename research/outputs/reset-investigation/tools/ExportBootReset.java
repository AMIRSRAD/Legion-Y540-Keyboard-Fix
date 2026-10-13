// Offline 8051 listing export; never executes the image.
import ghidra.app.script.GhidraScript;
import ghidra.app.decompiler.*;
import ghidra.program.model.address.*;
import ghidra.program.model.listing.*;
import ghidra.program.model.symbol.*;
import com.google.gson.*;
import java.nio.file.*;

public class ExportBootReset extends GhidraScript {
    public void run() throws Exception {
        AddressSpace code = currentProgram.getAddressFactory().getDefaultAddressSpace();
        int[] seeds = {0xe000,0xe003,0xf520,0xf896,0xef2f};
        for (int offset: seeds) {
            Address a = code.getAddress(offset);
            currentProgram.getSymbolTable().addExternalEntryPoint(a);
            disassemble(a);
            if (currentProgram.getFunctionManager().getFunctionAt(a)==null) createFunction(a,null);
        }
        analyzeAll(currentProgram);
        JsonObject result = new JsonObject();
        result.addProperty("mapping", "stock app bytes at 0000..D7FF combined for analysis with supplied upper-flash dump D800..FFFF; not a flashable release; CODE=file offset assumption");
        result.addProperty("language", currentProgram.getLanguageID().toString());
        JsonArray ins = new JsonArray();
        for (Instruction i: currentProgram.getListing().getInstructions(true)) {
            if (i.getAddress().getOffset()<0xe000) continue;
            JsonObject j = new JsonObject();
            j.addProperty("address", i.getAddress().toString());
            j.addProperty("text",i.toString());
            StringBuilder hex=new StringBuilder();
            for(byte b:i.getBytes()) hex.append(String.format("%02x",b&255));
            j.addProperty("bytes",hex.toString());
            JsonArray refs=new JsonArray();
            for(Reference r:i.getReferencesFrom()) {
                JsonObject q=new JsonObject();q.addProperty("to",r.getToAddress().toString());q.addProperty("type",r.getReferenceType().toString());refs.add(q);
            }
            j.add("references",refs);ins.add(j);
        }
        result.add("instructions",ins);
        DecompInterface d=new DecompInterface();d.openProgram(currentProgram);
        JsonArray fs=new JsonArray();
        for(Function f:currentProgram.getFunctionManager().getFunctions(true)) {
            if(f.getEntryPoint().getOffset()<0xe000)continue;
            JsonObject j=new JsonObject();j.addProperty("entry",f.getEntryPoint().toString());j.addProperty("body",f.getBody().toString());
            DecompileResults dec=d.decompileFunction(f,20,monitor);
            j.addProperty("complete",dec.decompileCompleted());j.addProperty("error",dec.getErrorMessage());
            if(dec.getDecompiledFunction()!=null)j.addProperty("pseudocode",dec.getDecompiledFunction().getC());
            fs.add(j);
        }
        d.dispose();result.add("functions",fs);
        Files.writeString(Paths.get(getScriptArgs()[0]),new GsonBuilder().setPrettyPrinting().create().toJson(result));
        println("BOOT_RESET_EXPORT instructions="+ins.size()+" functions="+fs.size());
    }
}
