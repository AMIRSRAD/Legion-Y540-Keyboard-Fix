from pathlib import Path
p=Path('outputs/y540-research/src/app.c');s=p.read_text(encoding='utf-8-sig').replace('#include "hid_transport.h"','#include "hid_transport.h"\n#include "protocol.h"')
s=s.replace('#define ID_LOG 108','#define ID_LOG 108\n#define ID_UPDATE 109\n#define WM_UPDATE_DONE (WM_APP+1)\nstatic int update_running;')
s=s.replace('Absent CHECKSUMLASTBYTESBEFF modeled as zero; vendor default unverified.','Absent CHECKSUMLASTBYTESBEFF uses recovered zero initialization/default.')
marker='static int pick_file('
insert='''static void update_progress(void *context, const char *phase, size_t complete, size_t total)
{
    (void)context;
    output("%s: %lu/%lu\\r\\n", phase, (unsigned long)complete, (unsigned long)total);
}

static int update_firmware(const char *firmware, const char *ini)
{
    y540_config *cfg = calloc(1, sizeof(*cfg));
    y540_hid_error error = {0};
    char config_error[256];
    size_t size = 0;
    uint8_t *data = NULL;
    int ok = 0;
    if (!cfg) { output("Cannot allocate configuration.\\r\\n"); return 0; }
    if (!y540_config_load(ini, cfg, config_error, sizeof(config_error))) {
        output("Configuration error: %s\\r\\n", config_error); goto done;
    }
    data = load_firmware(firmware, &size);
    if (!data) goto done;
    ok = y540_update_device(data, size, cfg, update_progress, NULL, &error);
    if (ok) output("Firmware readback matched; reset command accepted. Verify keyboard operation.\\r\\n");
    else output("Update stopped: %s (code %lu).\\r\\n", error.message, (unsigned long)error.code);
 done:
    free(data); free(cfg); return ok;
}

typedef struct { HWND owner; char firmware[PATH_CAP]; char ini[PATH_CAP]; } update_job;
static DWORD WINAPI update_worker(void *argument)
{
    update_job *job = argument;
    int ok = update_firmware(job->firmware, job->ini);
    PostMessageA(job->owner, WM_UPDATE_DONE, (WPARAM)ok, 0);
    free(job); return 0;
}
static void start_update(HWND owner)
{
    HANDLE thread;
    update_job *job;
    if (update_running) return;
    if (!verify_or_plan(firmware_path, ini_path, NULL)) return;
    if (MessageBoxA(owner,
        "Write selected firmware to the Lenovo Y540 keyboard (048D:C100 / boot 048D:89DB)?\\n\\n"
        "This source reconstruction has passed offline tests; hardware equivalence is unverified. "
        "Keep power connected throughout the update.",
        "Update keyboard firmware", MB_YESNO | MB_ICONQUESTION | MB_DEFBUTTON2) != IDYES) return;
    job = calloc(1, sizeof(*job));
    if (!job) { output("Cannot allocate update task.\\r\\n"); return; }
    job->owner = owner;
    strcpy(job->firmware, firmware_path); strcpy(job->ini, ini_path);
    update_running = 1;
    for (int id = ID_PICK_FIRMWARE; id <= ID_UPDATE; ++id)
        if (id != ID_LOG) EnableWindow(GetDlgItem(owner, id), FALSE);
    thread = CreateThread(NULL, 0, update_worker, job, 0, NULL);
    if (!thread) {
        update_running = 0; free(job);
        for (int id = ID_PICK_FIRMWARE; id <= ID_UPDATE; ++id)
            if (id != ID_LOG) EnableWindow(GetDlgItem(owner, id), TRUE);
        output("Cannot start update task.\\r\\n");
    } else CloseHandle(thread);
}

'''
s=s.replace(marker,insert+marker)
s=s.replace('control(window, "EDIT", "", ES_MULTILINE', 'control(window, "BUTTON", "Update keyboard", WS_TABSTOP, 500, 88, 150, 30, ID_UPDATE);\n        control(window, "EDIT", "", ES_MULTILINE')
s=s.replace('Y540 updater reconstruction - offline research build','Y540 updater reconstruction - source build')
s=s.replace('Full boot/erase/verify/reset workflow is not implemented in this build.','Update keyboard performs boot handoff, erase/write/readback and reset for the supplied profile.')
s=s.replace('Checksum consistency does not prove hardware compatibility.','Hardware behavior is unverified; inspect firmware and target before choosing Update.')
s=s.replace('case ID_LIST: list_devices(); break;', 'case ID_LIST: list_devices(); break;\n        case ID_UPDATE: start_update(window); break;')
s=s.replace('case WM_DESTROY: PostQuitMessage(0); return 0;', '''case WM_UPDATE_DONE:
        update_running = 0;
        for (int id = ID_PICK_FIRMWARE; id <= ID_UPDATE; ++id)
            if (id != ID_LOG) EnableWindow(GetDlgItem(window, id), TRUE);
        return 0;
    case WM_CLOSE:
        if (update_running) { output("Update in progress; wait for the task to settle before closing.\\r\\n"); return 0; }
        DestroyWindow(window); return 0;
    case WM_DESTROY: PostQuitMessage(0); return 0;''')
s=s.replace('if (!strcmp(argv[1], "--list")', 'if (!strcmp(argv[1], "--update") && argc == 4)\n        return update_firmware(argv[2], argv[3]) ? 0 : 1;\n    if (!strcmp(argv[1], "--list")')
s=s.replace('Y540Updater - offline native source reconstruction','Y540Updater - native source reconstruction')
s=s.replace('  Y540Updater.exe --list ', '  Y540Updater.exe --update FIRMWARE INI     Write keyboard firmware (hardware unverified)\\r\\n"\n           "  Y540Updater.exe --list ')
s=s.replace('No flashing command is exposed. This build is not a complete vendor replacement.', 'Supported: supplied Y540 full-image profile. Hardware equivalence and other ITE modes are unverified.')
p.write_text(s,encoding='utf8')
# Preserve original pathnames in build output, with experimental live engine linked explicitly.
p=Path('outputs/y540-research/build.ps1');s=p.read_text(encoding='utf-8-sig').replace('src/app.c src/core.c src/hid_transport.c','src/app.c src/core.c src/hid_transport.c src/protocol.c');p.write_text(s,encoding='utf8')
p=Path('outputs/y540-research/CMakeLists.txt');s=p.read_text(encoding='utf-8-sig').replace('src/app.c src/core.c src/hid_transport.c','src/app.c src/core.c src/hid_transport.c src/protocol.c');p.write_text(s,encoding='utf8')
