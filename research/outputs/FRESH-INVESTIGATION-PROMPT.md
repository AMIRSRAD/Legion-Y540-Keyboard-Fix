# Lenovo Legion Y540 keyboard — independent investigation

Please investigate this keyboard problem from the beginning and work toward a repair based on your own understanding. This document contains owner-reported observations and test outcomes, not a diagnosis.

Do not treat previous agents' explanations, patches, or proposed fixes as established facts. Examine original artifacts and raw recordings independently. Existing development work is available as reference material, but you do not need to adopt its approach.

## Goal and environment

The owner wants the built-in keyboard to work reliably after normal startup, restart, and shutdown. If an updater change is necessary, the owner also wants understandable source code and a reproducible executable build.

The development computer is **not the affected Lenovo laptop**. Hardware testing must happen on the affected laptop with the owner's participation. Preserve original files and existing work; put your investigation and changes in a separate folder.

The affected machine is a Lenovo Legion Y540. The owner supplied the Lenovo keyboard firmware updater package named `Y540-keyboard-firmware-00000044`.

## Owner's account of the original updater

- The owner recalls never successfully installing the original Lenovo keyboard firmware update.
- The updater displayed an error shown in the supplied screenshot: **“Can not Find Device! - 1”**, followed by **“Please shutdown Tablet PC then retry”** and instructions to close and reopen the tool.
- The owner associates the updater attempts with the keyboard becoming unusable after restart. This is the owner's account of the sequence, not proof of what caused the fault.
- Logs from those original Lenovo updater attempts are not available.

## Power and startup observations

- Holding the laptop power button for approximately **10 seconds**, until it is completely off, then pressing the button to turn it on can restore keyboard operation.
- An ordinary Windows **Restart** does not produce the same recovery.
- An ordinary Windows **Shutdown**, followed by turning the laptop on, also does not reliably restore operation.
- The owner explicitly confirmed that both ordinary restart and ordinary shutdown exhibit the problem.
- Windows **Fast Startup is off**.
- Initially the owner associated recovery with starting on battery and failure with AC connected. Later testing revised that observation: the important distinction appears to be the forced power-button shutdown versus a Windows-controlled shutdown/restart, **on either AC or battery**.
- When the keyboard was already working after startup on battery, connecting AC without restarting did **not** stop it from working.

## BIOS and boot-menu observations

- The owner reports that the keyboard works in BIOS, including when it does not work in the operating system.
- The owner reports that **Fn keys continue to work** during the keyboard failure. Exactly which Fn combinations were tested was not recorded.
- After an ordinary Windows shutdown, pressing F12 can bring up the boot menu, but the built-in keyboard does not work inside that menu.
- The owner reports that this boot-menu failure does not occur after the approximately 10-second forced power-button shutdown.
- Keep BIOS setup, the F12 boot menu, the Linux boot selector, and the operating-system desktop as separate observations; they did not all behave the same way.

## Linux Mint live-boot experiment

- The owner used a Linux Mint live USB.
- The owner explicitly confirmed that the test started after the approximately **10-second forced power-off**.
- The built-in keyboard worked in BIOS and in the Linux boot selector, where Mint and compatibility-mode options were shown.
- It did **not** work once the Mint live desktop loaded.
- On reboot, Mint displayed **“Please remove the installation medium then press Enter.”** The owner did not explicitly report whether the built-in keyboard could respond at that screen.
- Linux evidence was supplied in the `y540-linux` folder. Inspect it independently; this document does not interpret it.

## Windows checks and previous test outcomes

- In both working and nonworking states, the owner reported `i8042prt` with registry `Start = 0x3` and service state **RUNNING**.
- The owner tried the suggested registry/service-related change and reported that it **did not work**. Independently establish the current setting before drawing conclusions or changing it.
- During one supplied recording, the owner confirmed using only **Diagnose** and **USB retry**, without Device Manager changes, AC connection changes, or restarting other devices.
- During a working-state USB-retry test, the owner confirmed that the built-in keyboard **kept typing normally** afterward.
- After a later updater test performed while the keyboard was working, the owner reported that it still worked immediately afterward, but the underlying ordinary restart/shutdown problem remained. Forced power-button shutdown still restored operation.
- After another later attempt, the owner confirmed that the forced power-button shutdown **brought the keyboard back**.
- Several updater variants and recordings exist. Their existence does not establish that a particular firmware image was installed. Determine what actually happened from the original logs yourself.

## Available material

The supplied handoff has two folders:

1. `01-REA-Toolkit` — REA and Ghidra tooling.
2. `02-Y540-Development` — original material, source code, previous work, documents, and recordings.

Original locations used by the owner are listed below as provenance. These were on the development computer; find their copied equivalents in the handoff rather than assuming those absolute paths exist on your computer.

- `C:\Users\a.saberi\Desktop\KeyboardFirmware-Issue`
- `C:\Users\a.saberi\Desktop\Y540-keyboard-firmware-00000044`
- `C:\Users\a.saberi\Desktop\workingstate`
- `C:\Users\a.saberi\Desktop\nonworking`
- `C:\Users\a.saberi\Desktop\y540-linux`
- `C:\Users\a.saberi\Desktop\logs`
- `C:\Users\a.saberi\Desktop\New folder (2)`
- `C:\Users\a.saberi\Desktop\New folder (3)`
- `C:\Users\a.saberi\Desktop\New folder (4)`
- `C:\Users\a.saberi\Desktop\recording-20261012T135023471Z.zip`
- `C:\Users\a.saberi\Desktop\recording-20261012T141255304Z.zip`
- `C:\Users\a.saberi\Desktop\final-recording-20261013T050036127Z.zip`

The final recording was supplied after the initial handoff was prepared; its copied evidence is under `02-Y540-Development/outputs/fix4-final-analysis`. You can inspect the recording and raw logs there without adopting the previous analysis beside them.

## How to proceed

Start with the owner's observations and original evidence. Form your own hypotheses, explain what supports each one, and distinguish direct observations from inference. Prioritize tests that distinguish possible causes over repeating previous attempts.

Use existing captures before asking the owner to repeat tests. If a new test is necessary, explain what unanswered question it addresses and give clear instructions. Do not run laptop-specific hardware actions on the development computer.

Do not assume flashing is required or that an existing patch is correct. If you propose a repair, explain why it addresses the observed behavior, what evidence supports it, how success will be checked across ordinary restart and shutdown, and what recovery options actually exist. Be explicit about uncertainty and do not promise a cure before it has been demonstrated.

Please deliver your independent assessment, the most useful next step, and—if the evidence supports one—a repair with reproducible source/build instructions. The owner has already spent substantial effort on unsuccessful attempts and wants a fresh investigation, not a continuation of the previous agent's theory.
