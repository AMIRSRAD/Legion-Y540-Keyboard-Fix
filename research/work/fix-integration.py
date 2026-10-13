from pathlib import Path
p=Path('outputs/y540-research/src/protocol.c');s=p.read_text(encoding='utf8')
s=s.replace('if(!memcmp(key,got,15)){uint8_t boot[2]={9,0};','if(!memcmp(key,got,15)){uint8_t boot[2]={9,0};delay(t,100);')
s=s.replace('else if(failreset){y540_hid_error reset_error={0};reset(t,&reset_error);}', 'else {\n  if(failreset){y540_hid_error reset_error={0};reset(t,&reset_error);}\n  fail(e,"Flash readback differs from selected firmware after all attempts");\n }')
s=s.replace('for(pass=0;pass<30;pass++){if(y540_hid_open(&t,&sel,delay_ms,e)){break;}Sleep(500);}', 'for(pass=0;pass<30;pass++){if(y540_hid_open(&t,&sel,delay_ms,e)){break;}if(e && e->code!=ERROR_NOT_FOUND){return 0;}Sleep(500);}')
# All profile validation occurs before any hardware state transition.
needle='if(start||mode||docking||size!=54u*1024u)'
addition='''uint32_t same,pidcheck,report,retry,wait,wd,oem,page,usage,chip;
 if(!number(c,"CHECKVERSION","DONOTUPDATETHESAMEVERSION",10,0,&same,e)||
    !number(c,"OPTION","NOCHECKPID",10,0,&pidcheck,e)||
    !number(c,"OPTION","REPORTID",16,0x5a,&report,e)||
    !number(c,"DEVICE","PROGRAMFAILRETRY",10,1,&retry,e)||
    !number(c,"DELAY","MSEC",10,6000,&wait,e)||
    !number(c,"OPTION","WRITEFLASHDATADELAY",10,0,&wd,e)||
    !number(c,"OPTION","OEMVEROFFSET",16,0x3100,&oem,e)||
    !number(c,"NEWVERSION","BOOTDEVICEUPID",16,0xff89,&page,e)||
    !number(c,"NEWVERSION","BOOTDEVICEUID",16,0x00db,&usage,e)||
    !number(c,"NEWVERSION","BOOTDEVICECHIPID",16,0x8171,&chip,e)){return 0;}
 if(same||pidcheck||report!=0x5a||retry>100||wait>120000||wd>60000||oem>size-32||page>0xffff||usage>0xffff||chip>0xffff){return fail(e,"Unsupported or invalid update profile option");}
 '''
s=s.replace(needle,addition+needle)
p.write_text(s,encoding='utf8')
p=Path('outputs/y540-research/CMakeLists.txt');s=p.read_text(encoding='utf-8-sig').replace('add_executable(Y540Updater src/app.c src/app.rc)', 'add_library(y540_protocol STATIC src/protocol.c)\n    target_link_libraries(y540_protocol PUBLIC y540_core y540_hid)\n    add_executable(Y540Updater src/app.c src/app.rc)').replace('y540_core y540_hid comdlg32','y540_protocol comdlg32');s=s.replace('    endif()\nendif()', '''    endif()
    add_executable(protocol-tests tests/test_protocol.c)
    target_link_libraries(protocol-tests PRIVATE y540_protocol)
    add_test(NAME protocol-emulator COMMAND protocol-tests "${CMAKE_CURRENT_SOURCE_DIR}/samples")
endif()''');p.write_text(s,encoding='utf8')
p=Path('outputs/y540-research/build.ps1');s=p.read_text(encoding='utf-8-sig');needle='        & ./build/Y540Updater.exe --verify samples/44.bin samples/SHFU.ini';new='''        & $Compiler -std=c11 -O2 -Wall -Wextra -Werror -D_WIN32_WINNT=0x0601 src/core.c src/hid_transport.c src/protocol.c tests/test_protocol.c -o build/protocol-tests.exe -lsetupapi -lhid
        if ($LASTEXITCODE -ne 0) { throw 'Protocol test compilation failed.' }
        & ./build/protocol-tests.exe samples
        if ($LASTEXITCODE -ne 0) { throw 'Protocol emulator tests failed.' }
'''+needle;s=s.replace(needle,new);p.write_text(s,encoding='utf8')
