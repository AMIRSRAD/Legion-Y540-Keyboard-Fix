from pathlib import Path
p=Path('outputs/y540-research/src/app.c');s=p.read_text(encoding='utf8').replace('static int gui(void)','static int gui(int smoke)');s=s.replace('    ShowWindow(window, SW_SHOW); UpdateWindow(window);', '''    if (smoke) {
        int ok = GetDlgItem(window, ID_FIRMWARE) && GetDlgItem(window, ID_INI) &&
                 GetDlgItem(window, ID_VALIDATE) && GetDlgItem(window, ID_PLAN) &&
                 GetDlgItem(window, ID_LIST) && GetDlgItem(window, ID_UPDATE) && log_window;
        DestroyWindow(window); log_window = NULL;
        puts(ok ? "GUI controls initialized (hidden; no device access)" : "GUI initialization failed");
        return ok ? 0 : 1;
    }
    ShowWindow(window, SW_SHOW); UpdateWindow(window);''');s=s.replace('return gui();','return gui(0);');s=s.replace('    if (!strcmp(argv[1], "--verify")', '    if (!strcmp(argv[1], "--gui-smoke") && argc == 2) return gui(1);\n    if (!strcmp(argv[1], "--verify")');p.write_text(s,encoding='utf8')
p=Path('outputs/y540-research/build.ps1');s=p.read_text(encoding='utf8').replace("        if ($LASTEXITCODE -ne 0) { throw 'Compiled application sample verification failed.' }", "        if ($LASTEXITCODE -ne 0) { throw 'Compiled application sample verification failed.' }\n        & ./build/Y540Updater.exe --gui-smoke\n        if ($LASTEXITCODE -ne 0) { throw 'GUI initialization failed.' }");p.write_text(s,encoding='utf8')
p=Path('outputs/y540-research/CMakeLists.txt');s=p.read_text(encoding='utf8').replace('    add_executable(protocol-tests', '    add_test(NAME app-verify COMMAND Y540Updater --verify "${CMAKE_CURRENT_SOURCE_DIR}/samples/44.bin" "${CMAKE_CURRENT_SOURCE_DIR}/samples/SHFU.ini")\n    add_test(NAME app-gui-hidden COMMAND Y540Updater --gui-smoke)\n    add_executable(protocol-tests');p.write_text(s,encoding='utf8')
