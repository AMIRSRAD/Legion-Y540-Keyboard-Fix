from pathlib import Path
p=Path('outputs/y540-research/src/app.c');s=p.read_text(encoding='utf8');s=s.replace('    strcpy(firmware_path, executable);\n    strcat(firmware_path, "/../samples/44.bin");\n    strcpy(ini_path, executable);\n    strcat(ini_path, "/../samples/SHFU.ini");', '''    strcpy(firmware_path, executable); strcat(firmware_path, "/44.bin");
    strcpy(ini_path, executable); strcat(ini_path, "/SHFU.ini");
    if (GetFileAttributesA(firmware_path) == INVALID_FILE_ATTRIBUTES) {
        strcpy(firmware_path, executable); strcat(firmware_path, "/../samples/44.bin");
    }
    if (GetFileAttributesA(ini_path) == INVALID_FILE_ATTRIBUTES) {
        strcpy(ini_path, executable); strcat(ini_path, "/../samples/SHFU.ini");
    }''');p.write_text(s,encoding='utf8')
p=Path('outputs/y540-research/src/app.rc');s=p.read_text(encoding='utf-8-sig').replace('0,1,0,0','0,2,0,0').replace('0.1.0','0.2.0').replace('Y540 firmware research - offline reconstruction','Y540 keyboard firmware source reconstruction').replace('Independent reconstruction. No vendor affiliation. No flashing exposed.','Independent source reconstruction. Hardware validation pending.');p.write_text(s,encoding='utf8')
p=Path('outputs/y540-research/CMakeLists.txt');s=p.read_text(encoding='utf8').replace('VERSION 0.1.0','VERSION 0.2.0');p.write_text(s,encoding='utf8')
