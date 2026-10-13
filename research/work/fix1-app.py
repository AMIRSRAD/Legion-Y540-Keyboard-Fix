from pathlib import Path
p=Path('outputs/fix1/src/app.c');s=p.read_text(encoding='utf8')
s=s.replace('#include <commdlg.h>','#include <commdlg.h>\n#include <shellapi.h>\n#include "session_log.h"\n#include "device_state.h"')
s=s.replace('#define WM_UPDATE_DONE', '#define ID_DIAGNOSE 110\n#define ID_RECOVER 111\n#define ID_LOGDIR 112\n#define WM_UPDATE_DONE')
s=s.replace('    va_end(args);\n    if (log_window)', '    va_end(args);\n    y540_logf("%s", buffer);\n    if (log_window)')
marker='static uint8_t *load_firmware('
insert='''static void native_trace(void *context, const char *line)
{
    (void)context; y540_logf("%s", line);
}
static void wide_text(const wchar_t *value, char *out, size_t cap)
{
    if (!WideCharToMultiByte(CP_UTF8,0,value,-1,out,(int)cap,NULL,NULL))
        snprintf(out,cap,"(text unavailable)");
}
static int begin_session(const char *action)
{
    char error[256], path[8192];
    if (!y540_log_begin(action,error,sizeof(error))) { output("Log creation failed: %s\\r\\n",error); return 0; }
    y540_hid_set_trace(native_trace,NULL);
    wide_text(y540_log_path(),path,sizeof(path));
    output("Session log: %s\\r\\n",path);return 1;
}
static int capture_state(y540_device_state *state, const char *phase)
{
    y540_device_error error={0};
    output("%s: reading device metadata; no firmware commands.\\r\\n",phase);
    if (!y540_device_state_collect(state,&error)) { output("Device inventory incomplete: %s (code %lu)\\r\\n",error.message,(unsigned long)error.code); return 0; }
    y540_device_state_log(state,native_trace,NULL);
    output("Power now: %s; battery=%lu%% (255 means unknown).\\r\\n",
           state->ac_line_status==1?"AC connected":state->ac_line_status==0?"battery":"unknown",(unsigned long)state->battery_percent);
    unsigned normal=0,boot=0,failed=0;
    for(size_t i=0;i<state->count;i++) {
        const y540_device_item *d=&state->items[i];
        if (d->kind==Y540_DEVICE_OTHER) continue;
        char id[4096],location[1024];wide_text(d->instance_id,id,sizeof(id));wide_text(d->location,location,sizeof(location));
        output("%s present=%d problem=%lu location=%s\\r\\n",id,d->present,(unsigned long)d->problem,location);
        if(d->present && d->cm_result==0 && d->problem==0) {
            if(d->kind==Y540_DEVICE_KEYBOARD_NORMAL)normal++;
            if(d->kind==Y540_DEVICE_KEYBOARD_BOOT)boot++;
        }
        if(d->can_case_recover)failed++;
    }
    output("Healthy normal=%u; boot=%u; exact historical descriptor-failure candidate=%u.\\r\\n",normal,boot,failed);
    if(!normal && !boot)output("No healthy keyboard USB device is available. Firmware writes are blocked. Try the separate USB recovery action and save both logs.\\r\\n");
    else if(normal)output("Normal firmware is enumerated. Reflashing 44 is not a proven cure for AC-startup failure.\\r\\n");
    return 1;
}
static int diagnose(void)
{
    y540_device_state state={0};int ok;
    if(!begin_session("diagnose-read-only"))return 0;
    ok=capture_state(&state,"Diagnose");y540_device_state_free(&state);return ok;
}
static int ready_for_flash(void)
{
    y540_device_state state={0};unsigned count=0;int ok=0;
    if(!capture_state(&state,"Firmware preflight"))goto done;
    for(size_t i=0;i<state.count;i++) {
        const y540_device_item *d=&state.items[i];
        if(d->present && d->cm_result==0 && d->problem==0 &&
           (d->kind==Y540_DEVICE_KEYBOARD_NORMAL||d->kind==Y540_DEVICE_KEYBOARD_BOOT))count++;
    }
    if(count==1)ok=1;
    else output("Firmware write refused: need one healthy physical ITE keyboard; found %u. No mode or flash commands sent.\\r\\n",count);
 done:y540_device_state_free(&state);return ok;
}

'''
s=s.replace(marker,insert+marker)
s=s.replace('    size_t size = 0;\n    uint8_t *data = NULL;\n    int ok = 0;','    size_t size = 0;\n    uint8_t *data = NULL;\n    wchar_t backup_path[2048];\n    int ok = 0;')
s=s.replace('    ok = y540_update_device(data, size, cfg, update_progress, NULL, &error);', '''    if(!ready_for_flash())goto done;
    if(!y540_log_backup_path(backup_path,2048)) { output("Cannot allocate an explicit backup destination. No write attempted.\\r\\n");goto done; }
    char backup_text[8192];wide_text(backup_path,backup_text,sizeof(backup_text));
    output("Mandatory pre-erase backup destination: %s\\r\\n",backup_text);
    ok = y540_update_device_with_backup(data, size, cfg, backup_path, update_progress, NULL, &error);''')
s=s.replace('    if (!verify_or_plan(firmware_path, ini_path, NULL)) return;','    if (!begin_session("advanced-firmware-write")) return;\n    if (!verify_or_plan(firmware_path, ini_path, NULL)) return;')
s=s.replace('"This source reconstruction has passed offline tests; hardware equivalence is unverified. "\n        "Keep power connected throughout the update.",','"This writes firmware. Diagnose/retry USB first for descriptor failures. "\n        "A complete consistent backup is required before erase. The AC-startup fault is not a proven firmware-corruption case. "\n        "Keep power connected throughout the update.",')
s=s.replace('id <= ID_UPDATE','id <= ID_LOGDIR').replace('if (id != ID_LOG) EnableWindow','if (id != ID_LOG && id != ID_LOGDIR) EnableWindow')
# Explicit recovery task: known device or exact historical case, fresh revalidation occurs in device_state.c.
marker='static int pick_file('
insert='''typedef struct { HWND owner; wchar_t instance[1024]; } recovery_job;
static DWORD WINAPI recovery_worker(void *argument)
{
    recovery_job *job=argument;y540_device_error error={0};y540_device_state after={0};
    output("Attempting one nonpersistent USB devnode restart. No firmware writes.\\r\\n");
    int ok=y540_device_restart_case_target(job->instance,&error);
    if(!ok)output("USB restart failed: %s (CM/Win32 code %lu).\\r\\n",error.message,(unsigned long)error.code);
    else output("Windows accepted restart. Waiting to inspect enumeration; this does not establish a permanent repair.\\r\\n");
    if(ok)Sleep(3000);
    capture_state(&after,"After USB restart");y540_device_state_free(&after);
    PostMessageA(job->owner,WM_UPDATE_DONE,(WPARAM)ok,0);free(job);return 0;
}
static void start_recovery(HWND owner)
{
    y540_device_state before={0};const y540_device_item *chosen=NULL;unsigned count=0;
    if(update_running || !begin_session("usb-restart-no-flash"))return;
    if(!capture_state(&before,"Before USB restart"))goto done;
    for(size_t i=0;i<before.count;i++) {
        const y540_device_item *d=&before.items[i];
        if(d->present && (d->can_recover||d->can_case_recover)){chosen=d;count++;}
    }
    if(count!=1){output("Restart refused: need one unambiguous eligible keyboard devnode; found %u. No change made.\\r\\n",count);goto done;}
    wchar_t prompt[4096];swprintf(prompt,4096,L"Restart only this USB device?\\n\\n%ls\\nParent: %ls\\nLocation: %ls\\n\\nNo firmware will be written. This is a Windows enumeration retry, not a proven cure. Administrator permissions may be required.",chosen->instance_id,chosen->parent_id,chosen->location);
    if(MessageBoxW(owner,prompt,L"Retry keyboard USB device",MB_YESNO|MB_ICONQUESTION|MB_DEFBUTTON2)!=IDYES){output("USB recovery canceled; no change made.\\r\\n");goto done;}
    recovery_job *job=calloc(1,sizeof(*job));if(!job){output("Cannot allocate recovery task.\\r\\n");goto done;}
    job->owner=owner;wcscpy(job->instance,chosen->instance_id);update_running=1;
    for(int id=ID_PICK_FIRMWARE;id<=ID_LOGDIR;id++)if(id!=ID_LOG && id!=ID_LOGDIR)EnableWindow(GetDlgItem(owner,id),FALSE);
    HANDLE thread=CreateThread(NULL,0,recovery_worker,job,0,NULL);
    if(!thread){update_running=0;free(job);for(int id=ID_PICK_FIRMWARE;id<=ID_LOGDIR;id++)if(id!=ID_LOG && id!=ID_LOGDIR)EnableWindow(GetDlgItem(owner,id),TRUE);output("Cannot start recovery task.\\r\\n");}
    else CloseHandle(thread);
 done:y540_device_state_free(&before);
}
static void open_logs(HWND owner)
{
    if(!y540_log_directory()[0] && !begin_session("open-logs"))return;
    ShellExecuteW(owner,L"open",y540_log_directory(),NULL,NULL,SW_SHOWNORMAL);
}

'''
s=s.replace(marker,insert+marker)
s=s.replace('control(window, "BUTTON", "Validate firmware", WS_TABSTOP, 14, 88,','control(window, "BUTTON", "Validate firmware", WS_TABSTOP, 14, 128,')
s=s.replace('control(window, "BUTTON", "Export offline plan", WS_TABSTOP, 176, 88,','control(window, "BUTTON", "Export offline plan", WS_TABSTOP, 176, 128,')
s=s.replace('control(window, "BUTTON", "List HID interfaces", WS_TABSTOP, 338, 88,','control(window, "BUTTON", "List HID interfaces", WS_TABSTOP, 338, 128,')
s=s.replace('control(window, "BUTTON", "Update keyboard", WS_TABSTOP, 500, 88, 150,','control(window, "BUTTON", "Advanced firmware write", WS_TABSTOP, 500, 128, 200,')
s=s.replace('        control(window, "EDIT", "", ES_MULTILINE', '''        control(window,"BUTTON","1. Diagnose + save log",WS_TABSTOP,14,88,200,30,ID_DIAGNOSE);
        control(window,"BUTTON","2. Retry USB (no flash)",WS_TABSTOP,226,88,200,30,ID_RECOVER);
        control(window,"BUTTON","Open logs folder",WS_TABSTOP,438,88,180,30,ID_LOGDIR);
        control(window, "EDIT", "", ES_MULTILINE''')
s=s.replace('14, 132, 752, 315, ID_LOG','14, 170, 752, 315, ID_LOG')
old='''        output("Y540 updater reconstruction - source build\\r\\n"
               "Validate firmware, export staging reports, or inspect HID metadata.\\r\\n"
               "Update keyboard performs boot handoff, erase/write/readback and reset for the supplied profile.\\r\\n"
               "Hardware behavior is unverified; inspect firmware and target before choosing Update.\\r\\n\\r\\n");'''
new='''        output("Y540 fix1 - diagnose USB enumeration before firmware writes\\r\\n"
               "Start with Diagnose + save log. Retry USB is separate and never flashes firmware.\\r\\n"
               "A failed device descriptor has no usable keyboard HID interface.\\r\\n"
               "Advanced firmware writing requires healthy identity and a saved full backup.\\r\\n\\r\\n");'''
s=s.replace(old,new)
s=s.replace('        if (HIWORD(wparam) != BN_CLICKED) break;','        if (HIWORD(wparam) != BN_CLICKED) break;\n        if(update_running && LOWORD(wparam)!=ID_LOGDIR)return 0;')
s=s.replace('        case ID_VALIDATE: verify_or_plan','        case ID_DIAGNOSE: diagnose(); break;\n        case ID_RECOVER: start_recovery(window); break;\n        case ID_LOGDIR: open_logs(window); break;\n        case ID_VALIDATE: verify_or_plan')
s=s.replace('798, 500,','798, 540,').replace('Y540 Firmware Research - Source Reconstruction','Y540 fix1 - USB Recovery and Firmware Updater')
s=s.replace('GetDlgItem(window, ID_LIST) && GetDlgItem(window, ID_UPDATE) && log_window','GetDlgItem(window, ID_LIST) && GetDlgItem(window, ID_UPDATE) &&\n                 GetDlgItem(window, ID_DIAGNOSE) && GetDlgItem(window,ID_RECOVER) && GetDlgItem(window,ID_LOGDIR) && log_window')
# CLI update remains explicit, but now begins an auditable session and captures metadata before feature I/O.
s=s.replace('    if (!strcmp(argv[1], "--update") && argc == 4)\n        return update_firmware(argv[2], argv[3]) ? 0 : 1;', '    if (!strcmp(argv[1], "--diagnose") && argc == 2) return diagnose()?0:1;\n    if (!strcmp(argv[1], "--update") && argc == 4)\n        return begin_session("cli-advanced-firmware-write") && update_firmware(argv[2], argv[3]) ? 0 : 1;')
s=s.replace('Y540Updater - native source reconstruction','Y540 fix1 - USB recovery and source updater')
s=s.replace('  Y540Updater.exe --list ', '  Y540Updater.exe --diagnose                Save read-only PnP/power diagnostics\\r\\n"\n           "  Y540Updater.exe --list ')
s=s.replace('Supported: supplied Y540 full-image profile. Hardware equivalence and other ITE modes are unverified.','Use Diagnose first. USB recovery is an explicit GUI action. No recovery is claimed verified on hardware.')
s=s.replace('    return 0;\n}\n\nint main(', '    y540_log_close();\n    return 0;\n}\n\nint main(')
p.write_text(s,encoding='utf8')
