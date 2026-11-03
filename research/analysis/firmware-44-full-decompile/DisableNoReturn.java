// Pre-script: Keil helper calls (switch/ICALL) confuse Ghidra's non-returning-function discovery,
// which then truncates the callers. Turn it off before auto-analysis.
import ghidra.app.script.GhidraScript;
public class DisableNoReturn extends GhidraScript {
    public void run() throws Exception {
        setAnalysisOption(currentProgram, "Non-Returning Functions - Discovered", "false");
        println("non-returning discovery disabled");
    }
}
