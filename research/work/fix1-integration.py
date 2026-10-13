from pathlib import Path
p=Path('outputs/fix1/src/app.c');s=p.read_text(encoding='utf8')
s=s.replace('#define ID_LOGDIR 112','#define ID_LOGDIR 112\n#define ID_BOOTPOWER 113\nstatic int boot_power_context;')
s=s.replace('    y540_device_state_log(state,native_trace,NULL);', '    y540_logf("user_reported_power_at_last_complete_startup=%s (owner selected; not measured at boot)",boot_power_context==1?"AC connected":boot_power_context==2?"battery only":"unknown");\n    y540_device_state_log(state,native_trace,NULL);')
s=s.replace('id <= ID_LOGDIR','id <= ID_BOOTPOWER').replace('id<=ID_LOGDIR','id<=ID_BOOTPOWER')
s=s.replace('        control(window, "EDIT", "", ES_MULTILINE', '''        control(window,"COMBOBOX","",CBS_DROPDOWNLIST|WS_TABSTOP,630,90,136,120,ID_BOOTPOWER);
        SendDlgItemMessageA(window,ID_BOOTPOWER,CB_ADDSTRING,0,(LPARAM)"Boot: unknown");
        SendDlgItemMessageA(window,ID_BOOTPOWER,CB_ADDSTRING,0,(LPARAM)"Boot: AC power");
        SendDlgItemMessageA(window,ID_BOOTPOWER,CB_ADDSTRING,0,(LPARAM)"Boot: battery");
        SendDlgItemMessageA(window,ID_BOOTPOWER,CB_SETCURSEL,0,0);
        control(window, "EDIT", "", ES_MULTILINE''')
s=s.replace('    case WM_COMMAND:\n        if (HIWORD(wparam)', '    case WM_COMMAND:\n        if(LOWORD(wparam)==ID_BOOTPOWER && HIWORD(wparam)==CBN_SELCHANGE){boot_power_context=(int)SendDlgItemMessageA(window,ID_BOOTPOWER,CB_GETCURSEL,0,0);return 0;}\n        if (HIWORD(wparam)')
s=s.replace('GetDlgItem(window,ID_RECOVER) && GetDlgItem(window,ID_LOGDIR) && log_window','GetDlgItem(window,ID_RECOVER) && GetDlgItem(window,ID_LOGDIR) && GetDlgItem(window,ID_BOOTPOWER) && log_window')
s=s.replace('    if (argc == 1) {\n        HWND console', '    if (argc == 1) {\n        begin_session("gui-fix1");\n        HWND console')
s=s.replace('return verify_or_plan(argv[2], argv[3], NULL) ? 0 : 1;', 'return begin_session("cli-verify") && verify_or_plan(argv[2], argv[3], NULL) ? 0 : 1;')
s=s.replace('return verify_or_plan(argv[2], argv[3], argv[4]) ? 0 : 1;', 'return begin_session("cli-plan") && verify_or_plan(argv[2], argv[3], argv[4]) ? 0 : 1;')
s=s.replace('if (!strcmp(argv[1], "--list") && argc == 2) return list_devices() ? 0 : 1;', 'if (!strcmp(argv[1], "--list") && argc == 2) return begin_session("cli-hid-metadata") && list_devices() ? 0 : 1;')
s=s.replace('    if (!strcmp(argv[1], "--diagnose") && argc == 2)', '''    if (!strcmp(argv[1],"--diagnose") && argc==4 && !strcmp(argv[2],"--boot-power")) {
        if(!strcmp(argv[3],"ac"))boot_power_context=1;
        else if(!strcmp(argv[3],"battery"))boot_power_context=2;
        else if(strcmp(argv[3],"unknown"))return 2;
        return diagnose()?0:1;
    }
    if (!strcmp(argv[1], "--diagnose") && argc == 2)''')
p.write_text(s,encoding='utf8')
# Update build dependencies and version only within fix1.
p=Path('outputs/fix1/build.ps1');s=p.read_text(encoding='utf8');s=s.replace('src/protocol.c build/app-res.o','src/protocol.c src/device_state.c src/session_log.c build/app-res.o');s=s.replace('-lsetupapi -lhid','-lsetupapi -lhid -lcfgmgr32');s=s.replace('-lhid\n','-lhid -lcfgmgr32\n')
needle='        & ./build/Y540Updater.exe --verify samples/44.bin samples/SHFU.ini'
s=s.replace(needle,'''        & $Compiler -std=c11 -O2 -Wall -Wextra -Werror -D_WIN32_WINNT=0x0601 src/device_state.c tests/test_device_state.c -o build/device-state-tests.exe -lsetupapi -lcfgmgr32
        if ($LASTEXITCODE -ne 0) { throw 'Device-state test compilation failed.' }
        & ./build/device-state-tests.exe
        if ($LASTEXITCODE -ne 0) { throw 'Device-state fixture tests failed.' }
'''+needle);s=s.replace('-lgdi32 -luser32','-lgdi32 -luser32 -lshell32')
# Protocol fixture backups must remain in an intermediate workspace.
s=s.replace('        & ./build/protocol-tests.exe samples','        New-Item -ItemType Directory -Force work | Out-Null\n        Push-Location work\n        try { & ../build/protocol-tests.exe ../samples } finally { Pop-Location }')
p.write_text(s,encoding='utf8')
p=Path('outputs/fix1/CMakeLists.txt');s=p.read_text(encoding='utf8').replace('VERSION 0.2.0','VERSION 0.3.0').replace('target_link_libraries(y540_hid PUBLIC setupapi hid)','target_link_libraries(y540_hid PUBLIC setupapi hid cfgmgr32)').replace('add_executable(Y540Updater src/app.c src/app.rc)','add_library(y540_state STATIC src/device_state.c)\n    target_include_directories(y540_state PUBLIC src)\n    target_link_libraries(y540_state PUBLIC setupapi cfgmgr32)\n    add_executable(device-state-tests tests/test_device_state.c)\n    target_link_libraries(device-state-tests PRIVATE y540_state)\n    add_test(NAME device-state-fixtures COMMAND device-state-tests)\n    add_executable(Y540Updater src/app.c src/session_log.c src/app.rc)').replace('y540_protocol comdlg32 gdi32 user32','y540_protocol y540_state comdlg32 gdi32 user32 shell32');p.write_text(s,encoding='utf8')
p=Path('outputs/fix1/src/app.rc');s=p.read_text(encoding='utf8').replace('0,2,0,0','0,3,0,0').replace('0.2.0','0.3.0-fix1').replace('Y540 keyboard firmware source reconstruction','Y540 fix1 USB diagnostics and updater');p.write_text(s,encoding='utf8')
