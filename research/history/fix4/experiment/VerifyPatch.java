import ghidra.app.script.GhidraScript;
import ghidra.program.model.address.*;
import ghidra.program.model.listing.*;
import java.nio.file.*;
public class VerifyPatch extends GhidraScript {
 public void run() throws Exception {
  AddressSpace code=currentProgram.getAddressFactory().getDefaultAddressSpace();
  Address branch=code.getAddress(0x4c79), target=code.getAddress(0x4ce1);
  disassemble(branch);disassemble(target);
  Instruction b=getInstructionAt(branch), t=getInstructionAt(target);
  if(b==null||t==null||!b.getMnemonicString().equals("SJMP")||!t.getMnemonicString().equals("RET")||b.getLength()!=2)
   throw new Exception("Unexpected patch disassembly");
  Address[] flows=b.getFlows();
  if(flows.length!=1||!flows[0].equals(target))throw new Exception("Unexpected branch target");
  String result="PASS: "+branch+" "+b+" (2 bytes) -> "+target+" "+t+"\nStatic disassembly only; no firmware execution.\n";
  Files.writeString(Paths.get(getScriptArgs()[0]),result);println(result);
 }
}
