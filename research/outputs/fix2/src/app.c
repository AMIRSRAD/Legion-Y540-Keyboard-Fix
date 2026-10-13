#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <commdlg.h>
#include <shellapi.h>
#include "session_log.h"
#include "device_state.h"
#include "core.h"
#include "hid_transport.h"
#include "protocol.h"

#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ID_FIRMWARE 101
#define ID_INI 102
#define ID_PICK_FIRMWARE 103
#define ID_PICK_INI 104
#define ID_VALIDATE 105
#define ID_PLAN 106
#define ID_LIST 107
#define ID_LOG 108
#define ID_UPDATE 109
#define ID_DIAGNOSE 110
#define ID_RECOVER 111
#define ID_LOGDIR 112
#define ID_BOOTPOWER 113
static int boot_power_context;
#define WM_UPDATE_DONE (WM_APP+1)
static int update_running;
#define PATH_CAP 2048

static HWND log_window;
static char firmware_path[PATH_CAP], ini_path[PATH_CAP];

static void output(const char *format, ...)
{
    char buffer[4096];
    va_list args;
    va_start(args, format);
    vsnprintf(buffer, sizeof(buffer), format, args);
    va_end(args);
    y540_logf("%s", buffer);
    if (log_window) {
        int length = GetWindowTextLengthA(log_window);
        SendMessageA(log_window, EM_SETSEL, (WPARAM)length, (LPARAM)length);
        SendMessageA(log_window, EM_REPLACESEL, FALSE, (LPARAM)buffer);
    } else fputs(buffer, stdout);
}

static void native_trace(void *context, const char *line)
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
    if (!y540_log_begin(action,error,sizeof(error))) { output("Log creation failed: %s\r\n",error); return 0; }
    y540_hid_set_trace(native_trace,NULL);
    wide_text(y540_log_path(),path,sizeof(path));
    output("Session log: %s\r\n",path);return 1;
}
static int capture_state(y540_device_state *state, const char *phase)
{
    y540_device_error error={0};
    output("%s: reading device metadata; no firmware commands.\r\n",phase);
    if (!y540_device_state_collect(state,&error)) { output("Device inventory incomplete: %s (code %lu)\r\n",error.message,(unsigned long)error.code); return 0; }
    y540_logf("user_reported_power_at_last_complete_startup=%s (owner selected; not measured at boot)",boot_power_context==1?"AC connected":boot_power_context==2?"battery only":"unknown");
    y540_device_state_log(state,native_trace,NULL);
    output("Power now: %s; battery=%lu%% (255 means unknown).\r\n",
           state->ac_line_status==1?"AC connected":state->ac_line_status==0?"battery":"unknown",(unsigned long)state->battery_percent);
    unsigned normal=0,boot=0,failed=0;
    for(size_t i=0;i<state->count;i++) {
        const y540_device_item *d=&state->items[i];
        if (d->kind==Y540_DEVICE_OTHER) continue;
        char id[4096],location[1024];wide_text(d->instance_id,id,sizeof(id));wide_text(d->location,location,sizeof(location));
        output("%s present=%d problem=%lu location=%s\r\n",id,d->present,(unsigned long)d->problem,location);
        if(d->present && d->cm_result==0 && d->problem==0) {
            if(d->kind==Y540_DEVICE_KEYBOARD_NORMAL)normal++;
            if(d->kind==Y540_DEVICE_KEYBOARD_BOOT)boot++;
        }
        if(d->can_case_recover)failed++;
    }
    output("Healthy normal=%u; boot=%u; exact historical descriptor-failure candidate=%u.\r\n",normal,boot,failed);
    if(!normal && !boot)output("No healthy keyboard USB device is available. Firmware writes are blocked. Try the separate USB recovery action and save both logs.\r\n");
    else if(normal)output("Normal firmware is enumerated. Reflashing 44 is not a proven cure for the observed startup failure.\r\n");
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
    else output("Firmware write refused: need one healthy physical ITE keyboard; found %u. No mode or flash commands sent.\r\n",count);
 done:y540_device_state_free(&state);return ok;
}

static uint8_t *load_firmware(const char *path, size_t *size)
{
    FILE *file = fopen(path, "rb");
    long length;
    uint8_t *data;
    if (!file) { output("Cannot open firmware: %s\r\n", path); return NULL; }
    if (fseek(file, 0, SEEK_END) || (length = ftell(file)) <= 0 || length > 16 * 1024 * 1024 ||
        fseek(file, 0, SEEK_SET)) {
        output("Firmware must be between 1 byte and 16 MiB.\r\n"); fclose(file); return NULL;
    }
    data = malloc((size_t)length);
    if (!data || fread(data, 1, (size_t)length, file) != (size_t)length) {
        output("Cannot read firmware.\r\n"); free(data); fclose(file); return NULL;
    }
    fclose(file);
    *size = (size_t)length;
    return data;
}

static void hex_report(FILE *file, const uint8_t report[64])
{
    size_t i;
    fputc('"', file);
    for (i = 0; i < 64; ++i) fprintf(file, "%02X", report[i]);
    fputc('"', file);
}

static int export_plan(FILE *file, const uint8_t *data, size_t size, const y540_config *cfg,
                       const y540_checksum_result *checksum)
{
    size_t i, count = y540_block_count(size), written = 0, skipped = 0;
    uint32_t start;
    int fallback;
    uint8_t report[64];
    y540_block block;
    if (y540_config_number(cfg, "NEWVERSION", "UPDATESTARTADDRESS", 16, 0, &start) != 1) {
        output("Missing or invalid UPDATESTARTADDRESS.\r\n"); return 0;
    }
    /* Validate every address before generating any packet stream. */
    for (i = 0; i < count; ++i) {
        if (!y540_plan_block(data, size, start, i, &block)) {
            output("Block address exceeds supported 24-bit flash range.\r\n"); return 0;
        }
    }
    fallback = y540_config_get(cfg, "NEWVERSION", "CHECKSUMLASTBYTESBEFF") == NULL;
    fprintf(file, "{\n  \"format\": \"y540-offline-staging-plan-v1\",\n"
                  "  \"scope\": \"C0/C1/D0/C3 staging only; erase, boot, status and reset are not represented\",\n"
                  "  \"report_padding\": \"zero (reconstruction choice)\",\n"
                  "  \"trailing_ff_default_unverified\": %s,\n"
                  "  \"firmware_bytes\": %lu,\n  \"checksum_stored\": %u,\n"
                  "  \"checksum_residual\": %u,\n  \"blocks\": [\n",
            fallback ? "true" : "false", (unsigned long)size, checksum->stored, checksum->residual);
    for (i = 0; i < count; ++i) {
        size_t offset, packets = 0;
        y540_plan_block(data, size, start, i, &block);
        fprintf(file, "%s    {\"index\": %lu, \"address\": %lu, \"source_bytes\": %lu, "
                      "\"all_ff\": %s, \"staging_checksum\": %u, \"reports\": [",
                i ? ",\n" : "", (unsigned long)i, (unsigned long)block.address,
                (unsigned long)block.source_length, block.all_ff ? "true" : "false", block.staging_sum);
        if (!block.all_ff) {
            ++written;
            memset(report, 0, sizeof(report)); report[1] = 0xc0;
            hex_report(file, report);
            for (offset = 0; offset < block.source_length; ) {
                size_t length = block.source_length - offset;
                if (length > Y540_CHUNK_SIZE) length = Y540_CHUNK_SIZE;
                y540_encode_c1((uint16_t)offset, block.data + offset, length, report);
                fputs(", ", file); hex_report(file, report);
                offset += length; ++packets;
            }
            memset(report, 0, sizeof(report)); report[1] = 0xd0;
            fputs(", ", file); hex_report(file, report);
            y540_encode_c3(block.address, report);
            fputs(", ", file); hex_report(file, report);
        } else ++skipped;
        fprintf(file, "], \"c1_chunks\": %lu}", (unsigned long)packets);
    }
    fprintf(file, "\n  ],\n  \"staged_blocks\": %lu,\n  \"skipped_ff_blocks\": %lu\n}\n",
            (unsigned long)written, (unsigned long)skipped);
    if (ferror(file)) { output("Error writing plan.\r\n"); return 0; }
    output("Offline plan: %lu blocks staged, %lu all-FF blocks skipped.\r\n",
           (unsigned long)written, (unsigned long)skipped);
    return 1;
}

static int verify_or_plan(const char *firmware, const char *ini, const char *plan)
{
    y540_config *cfg = calloc(1, sizeof(*cfg));
    y540_checksum_result checksum;
    char error[256];
    uint8_t *data;
    size_t size = 0;
    FILE *file;
    int ok = 0;
    if (!cfg) { output("Out of memory.\r\n"); return 0; }
    if (!y540_config_load(ini, cfg, error, sizeof(error))) {
        output("Configuration error: %s\r\n", error); free(cfg); return 0;
    }
    data = load_firmware(firmware, &size);
    if (!data) { free(cfg); return 0; }
    if (!y540_validate_firmware(data, size, cfg, &checksum, error, sizeof(error))) {
        output("Validation failed: %s\r\n", error); goto done;
    }
    output("Validated %lu bytes. Sum=%04X stored=%04X residual=%04X.\r\n",
           (unsigned long)size, checksum.sum, checksum.stored, checksum.residual);
    if (!y540_config_get(cfg, "NEWVERSION", "CHECKSUMLASTBYTESBEFF"))
        output("Absent CHECKSUMLASTBYTESBEFF uses recovered zero initialization/default.\r\n");
    if (!plan) { ok = 1; goto done; }
    if (!_stricmp(plan, firmware) || !_stricmp(plan, ini)) {
        output("Plan path must differ from firmware and INI.\r\n"); goto done;
    }
    /* Never overwrite an existing file or a preserved input via alternate spelling. */
    if (GetFileAttributesA(plan) != INVALID_FILE_ATTRIBUTES) {
        output("Plan destination already exists; choose a new file.\r\n"); goto done;
    }
    file = fopen(plan, "wb");
    if (!file) { output("Cannot create plan: %s\r\n", plan); goto done; }
    ok = export_plan(file, data, size, cfg, &checksum);
    if (fclose(file)) ok = 0;
    if (!ok) DeleteFileA(plan);
    else output("Saved plan: %s\r\n", plan);
done:
    free(data); free(cfg); return ok;
}

static int list_visit(void *context, const y540_hid_device *device)
{
    unsigned long *count = context;
    char path[4096];
    ++*count;
    if (!WideCharToMultiByte(CP_UTF8, 0, device->path, -1, path, sizeof(path), NULL, NULL))
        strcpy(path, "(path unavailable)");
    output("VID:%04X PID:%04X UsagePage:%04X Usage:%04X FeatureBytes:%u\r\n%s\r\n",
           device->vid, device->pid, device->usage_page, device->usage,
           device->feature_report_bytes, path);
    return 1;
}

static int list_devices(void)
{
    unsigned long count = 0;
    y540_hid_error error;
    if (!y540_hid_enumerate(list_visit, &count, &error)) {
        output("HID enumeration failed: %s (code %lu)\r\n", error.message, (unsigned long)error.code);
        return 0;
    }
    output("%lu HID interfaces. Metadata enumeration only; no feature commands sent.\r\n", count);
    return 1;
}

static void update_progress(void *context, const char *phase, size_t complete, size_t total)
{
    (void)context;
    output("%s: %lu/%lu\r\n", phase, (unsigned long)complete, (unsigned long)total);
}

static HANDLE acquire_device_action(void)
{
    HANDLE guard = CreateMutexW(NULL, FALSE, L"Global\\Y540Updater-fix1-device-action-v1");
    if (!guard) {
        output("Cannot acquire device-operation guard (Win32 %lu); nothing changed.\r\n",
               (unsigned long)GetLastError());
        return NULL;
    }
    DWORD result = WaitForSingleObject(guard, 0);
    if (result != WAIT_OBJECT_0 && result != WAIT_ABANDONED) {
        output("Another fix2 process is using the keyboard, or the operation guard is unavailable. Nothing changed.\r\n");
        CloseHandle(guard);
        return NULL;
    }
    if (result == WAIT_ABANDONED)
        output("Previous device operation ended unexpectedly; fresh identity and backup checks are required.\r\n");
    return guard;
}

static void release_device_action(HANDLE guard)
{
    if (guard) { ReleaseMutex(guard); CloseHandle(guard); }
}

static int update_firmware(const char *firmware, const char *ini)
{
    y540_config *cfg = calloc(1, sizeof(*cfg));
    y540_hid_error error = {0};
    char config_error[256];
    size_t size = 0;
    uint8_t *data = NULL;
    wchar_t backup_path[2048];
    int ok = 0;
    HANDLE guard = acquire_device_action();
    if (!guard) { free(cfg); return 0; }
    if (!cfg) { output("Cannot allocate configuration.\r\n"); release_device_action(guard); return 0; }
    if (!y540_config_load(ini, cfg, config_error, sizeof(config_error))) {
        output("Configuration error: %s\r\n", config_error); goto done;
    }
    data = load_firmware(firmware, &size);
    if (!data) goto done;
    if(!ready_for_flash())goto done;
    if(!y540_log_backup_path(backup_path,2048)) { output("Cannot allocate an explicit backup destination. No write attempted.\r\n");goto done; }
    char backup_text[8192];wide_text(backup_path,backup_text,sizeof(backup_text));
    output("Mandatory pre-erase backup destination: %s\r\n",backup_text);
    ok = y540_update_device_with_backup(data, size, cfg, backup_path, update_progress, NULL, &error);
    if (ok) output("Firmware readback matched; reset command accepted. Verify keyboard operation.\r\n");
    else output("Update stopped: %s (code %lu).\r\n", error.message, (unsigned long)error.code);
 done:
    free(data); free(cfg); release_device_action(guard); return ok;
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
    if (!begin_session("advanced-firmware-write")) return;
    if (!verify_or_plan(firmware_path, ini_path, NULL)) return;
    if (MessageBoxA(owner,
        "Write selected firmware to the Lenovo Y540 keyboard (048D:C100 / boot 048D:89DB)?\n\n"
        "This writes firmware. Diagnose/retry USB first for descriptor failures. "
        "A complete consistent backup is required before erase. The AC-startup fault is not a proven firmware-corruption case. "
        "Keep power connected throughout the update.",
        "Update keyboard firmware", MB_YESNO | MB_ICONQUESTION | MB_DEFBUTTON2) != IDYES) return;
    job = calloc(1, sizeof(*job));
    if (!job) { output("Cannot allocate update task.\r\n"); return; }
    job->owner = owner;
    strcpy(job->firmware, firmware_path); strcpy(job->ini, ini_path);
    update_running = 1;
    for (int id = ID_PICK_FIRMWARE; id <= ID_BOOTPOWER; ++id)
        if (id != ID_LOG && id != ID_LOGDIR) EnableWindow(GetDlgItem(owner, id), FALSE);
    thread = CreateThread(NULL, 0, update_worker, job, 0, NULL);
    if (!thread) {
        update_running = 0; free(job);
        for (int id = ID_PICK_FIRMWARE; id <= ID_BOOTPOWER; ++id)
            if (id != ID_LOG && id != ID_LOGDIR) EnableWindow(GetDlgItem(owner, id), TRUE);
        output("Cannot start update task.\r\n");
    } else CloseHandle(thread);
}

typedef struct { HWND owner; wchar_t instance[1024]; } recovery_job;
static DWORD WINAPI recovery_worker(void *argument)
{
    recovery_job *job=argument;y540_device_error error={0};y540_device_state after={0};
    HANDLE guard=acquire_device_action();
    if(!guard){PostMessageA(job->owner,WM_UPDATE_DONE,0,0);free(job);return 0;}
    output("Attempting one nonpersistent USB devnode restart. No firmware writes.\r\n");
    int ok=y540_device_restart_case_target(job->instance,&error);
    if(!ok)output("USB restart failed: %s (CM/Win32 code %lu).\r\n",error.message,(unsigned long)error.code);
    else output("Windows accepted restart. Waiting to inspect enumeration; this does not establish a permanent repair.\r\n");
    if(ok)Sleep(3000);
    capture_state(&after,"After USB restart");y540_device_state_free(&after);
    release_device_action(guard);
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
    if(count!=1){output("Restart refused: need one unambiguous eligible keyboard devnode; found %u. No change made.\r\n",count);goto done;}
    wchar_t prompt[4096];swprintf(prompt,4096,L"Restart only this USB device?\n\n%ls\nParent: %ls\nLocation: %ls\n\nNo firmware will be written. This is a Windows enumeration retry, not a proven cure. Administrator permissions may be required.",chosen->instance_id,chosen->parent_id,chosen->location);
    if(MessageBoxW(owner,prompt,L"Retry keyboard USB device",MB_YESNO|MB_ICONQUESTION|MB_DEFBUTTON2)!=IDYES){output("USB recovery canceled; no change made.\r\n");goto done;}
    recovery_job *job=calloc(1,sizeof(*job));if(!job){output("Cannot allocate recovery task.\r\n");goto done;}
    job->owner=owner;wcscpy(job->instance,chosen->instance_id);update_running=1;
    for(int id=ID_PICK_FIRMWARE;id<=ID_BOOTPOWER;id++)if(id!=ID_LOG && id!=ID_LOGDIR)EnableWindow(GetDlgItem(owner,id),FALSE);
    HANDLE thread=CreateThread(NULL,0,recovery_worker,job,0,NULL);
    if(!thread){update_running=0;free(job);for(int id=ID_PICK_FIRMWARE;id<=ID_BOOTPOWER;id++)if(id!=ID_LOG && id!=ID_LOGDIR)EnableWindow(GetDlgItem(owner,id),TRUE);output("Cannot start recovery task.\r\n");}
    else CloseHandle(thread);
 done:y540_device_state_free(&before);
}
static void open_logs(HWND owner)
{
    if(!y540_log_directory()[0] && !begin_session("open-logs"))return;
    ShellExecuteW(owner,L"open",y540_log_directory(),NULL,NULL,SW_SHOWNORMAL);
}

static int pick_file(HWND owner, int save, char *path, const char *filter)
{
    OPENFILENAMEA ofn;
    memset(&ofn, 0, sizeof(ofn));
    ofn.lStructSize = sizeof(ofn); ofn.hwndOwner = owner;
    ofn.lpstrFile = path; ofn.nMaxFile = PATH_CAP; ofn.lpstrFilter = filter;
    ofn.Flags = OFN_EXPLORER | OFN_NOCHANGEDIR | OFN_PATHMUSTEXIST;
    if (!save) ofn.Flags |= OFN_FILEMUSTEXIST;
    if (save) { ofn.lpstrDefExt = "json"; return GetSaveFileNameA(&ofn); }
    return GetOpenFileNameA(&ofn);
}

static void control(HWND window, const char *type, const char *text, DWORD style,
                    int x, int y, int width, int height, int id)
{
    HWND child = CreateWindowExA(!strcmp(type, "EDIT") ? WS_EX_CLIENTEDGE : 0,
                                type, text, WS_CHILD | WS_VISIBLE | style,
                                x, y, width, height, window, (HMENU)(INT_PTR)id,
                                GetModuleHandleA(NULL), NULL);
    SendMessageA(child, WM_SETFONT, (WPARAM)GetStockObject(DEFAULT_GUI_FONT), TRUE);
}

static LRESULT CALLBACK window_proc(HWND window, UINT message, WPARAM wparam, LPARAM lparam)
{
    switch (message) {
    case WM_CREATE:
        control(window, "STATIC", "Firmware:", 0, 14, 17, 65, 22, 0);
        control(window, "EDIT", firmware_path, ES_AUTOHSCROLL | WS_TABSTOP, 82, 12, 572, 25, ID_FIRMWARE);
        control(window, "BUTTON", "Browse...", WS_TABSTOP, 665, 12, 100, 25, ID_PICK_FIRMWARE);
        control(window, "STATIC", "SHFU.ini:", 0, 14, 52, 65, 22, 0);
        control(window, "EDIT", ini_path, ES_AUTOHSCROLL | WS_TABSTOP, 82, 47, 572, 25, ID_INI);
        control(window, "BUTTON", "Browse...", WS_TABSTOP, 665, 47, 100, 25, ID_PICK_INI);
        control(window, "BUTTON", "Validate firmware", WS_TABSTOP, 14, 128, 150, 30, ID_VALIDATE);
        control(window, "BUTTON", "Export offline plan", WS_TABSTOP, 176, 128, 150, 30, ID_PLAN);
        control(window, "BUTTON", "List HID interfaces", WS_TABSTOP, 338, 128, 150, 30, ID_LIST);
        control(window, "BUTTON", "Advanced firmware write", WS_TABSTOP, 500, 128, 200, 30, ID_UPDATE);
        control(window,"BUTTON","1. Diagnose + save log",WS_TABSTOP,14,88,200,30,ID_DIAGNOSE);
        control(window,"BUTTON","2. Retry USB (no flash)",WS_TABSTOP,226,88,200,30,ID_RECOVER);
        control(window,"BUTTON","Open logs folder",WS_TABSTOP,438,88,180,30,ID_LOGDIR);
        control(window,"COMBOBOX","",CBS_DROPDOWNLIST|WS_TABSTOP,630,90,136,120,ID_BOOTPOWER);
        SendDlgItemMessageA(window,ID_BOOTPOWER,CB_ADDSTRING,0,(LPARAM)"Boot: unknown");
        SendDlgItemMessageA(window,ID_BOOTPOWER,CB_ADDSTRING,0,(LPARAM)"Boot: AC power");
        SendDlgItemMessageA(window,ID_BOOTPOWER,CB_ADDSTRING,0,(LPARAM)"Boot: battery");
        SendDlgItemMessageA(window,ID_BOOTPOWER,CB_SETCURSEL,0,0);
        control(window, "EDIT", "", ES_MULTILINE | ES_READONLY | ES_AUTOVSCROLL | WS_VSCROLL,
                14, 170, 752, 315, ID_LOG);
        log_window = GetDlgItem(window, ID_LOG);
        SendMessageA(log_window, EM_SETLIMITTEXT, 1024 * 1024, 0);
        output("Y540 fix2 - diagnose USB enumeration before firmware writes\r\n"
               "Start with Diagnose + save log. Retry USB is separate and never flashes firmware.\r\n"
               "A failed device descriptor has no usable keyboard HID interface.\r\n"
               "Advanced firmware writing requires healthy identity and a saved full backup.\r\n\r\n");
        return 0;
    case WM_COMMAND:
        if(LOWORD(wparam)==ID_BOOTPOWER && HIWORD(wparam)==CBN_SELCHANGE){boot_power_context=(int)SendDlgItemMessageA(window,ID_BOOTPOWER,CB_GETCURSEL,0,0);return 0;}
        if (HIWORD(wparam) != BN_CLICKED) break;
        if(update_running && LOWORD(wparam)!=ID_LOGDIR)return 0;
        GetDlgItemTextA(window, ID_FIRMWARE, firmware_path, sizeof(firmware_path));
        GetDlgItemTextA(window, ID_INI, ini_path, sizeof(ini_path));
        switch (LOWORD(wparam)) {
        case ID_PICK_FIRMWARE:
            if (pick_file(window, 0, firmware_path, "Firmware (*.bin)\0*.bin\0All files\0*.*\0"))
                SetDlgItemTextA(window, ID_FIRMWARE, firmware_path);
            break;
        case ID_PICK_INI:
            if (pick_file(window, 0, ini_path, "INI configuration\0*.ini\0All files\0*.*\0"))
                SetDlgItemTextA(window, ID_INI, ini_path);
            break;
        case ID_DIAGNOSE: diagnose(); break;
        case ID_RECOVER: start_recovery(window); break;
        case ID_LOGDIR: open_logs(window); break;
        case ID_VALIDATE: verify_or_plan(firmware_path, ini_path, NULL); break;
        case ID_PLAN: {
            char plan[PATH_CAP] = "";
            if (pick_file(window, 1, plan, "JSON plan\0*.json\0All files\0*.*\0"))
                verify_or_plan(firmware_path, ini_path, plan);
            break;
        }
        case ID_LIST: list_devices(); break;
        case ID_UPDATE: start_update(window); break;
        }
        return 0;
    case WM_UPDATE_DONE:
        update_running = 0;
        for (int id = ID_PICK_FIRMWARE; id <= ID_BOOTPOWER; ++id)
            if (id != ID_LOG && id != ID_LOGDIR) EnableWindow(GetDlgItem(window, id), TRUE);
        return 0;
    case WM_CLOSE:
        if (update_running) { output("Update in progress; wait for the task to settle before closing.\r\n"); return 0; }
        DestroyWindow(window); return 0;
    case WM_DESTROY: PostQuitMessage(0); return 0;
    }
    return DefWindowProcA(window, message, wparam, lparam);
}

static void default_paths(void)
{
    char executable[PATH_CAP], *slash;
    GetModuleFileNameA(NULL, executable, sizeof(executable));
    slash = strrchr(executable, '\\');
    if (slash) *slash = 0;
    if (strlen(executable) > PATH_CAP - 32) return;
    strcpy(firmware_path, executable); strcat(firmware_path, "/44.bin");
    strcpy(ini_path, executable); strcat(ini_path, "/SHFU.ini");
    if (GetFileAttributesA(firmware_path) == INVALID_FILE_ATTRIBUTES) {
        strcpy(firmware_path, executable); strcat(firmware_path, "/../samples/44.bin");
    }
    if (GetFileAttributesA(ini_path) == INVALID_FILE_ATTRIBUTES) {
        strcpy(ini_path, executable); strcat(ini_path, "/../samples/SHFU.ini");
    }
}

static int gui(int smoke)
{
    WNDCLASSA cls;
    HWND window;
    MSG message;
    default_paths();
    memset(&cls, 0, sizeof(cls));
    cls.lpfnWndProc = window_proc; cls.hInstance = GetModuleHandleA(NULL);
    cls.hCursor = LoadCursor(NULL, IDC_ARROW); cls.hbrBackground = (HBRUSH)(COLOR_BTNFACE + 1);
    cls.lpszClassName = "Y540ResearchUpdater";
    if (!RegisterClassA(&cls)) return 1;
    window = CreateWindowA(cls.lpszClassName, "Y540 fix2 - USB Recovery and Firmware Updater",
                           WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX,
                           CW_USEDEFAULT, CW_USEDEFAULT, 798, 540, NULL, NULL, cls.hInstance, NULL);
    if (!window) return 1;
    if (smoke) {
        int ok = GetDlgItem(window, ID_FIRMWARE) && GetDlgItem(window, ID_INI) &&
                 GetDlgItem(window, ID_VALIDATE) && GetDlgItem(window, ID_PLAN) &&
                 GetDlgItem(window, ID_LIST) && GetDlgItem(window, ID_UPDATE) &&
                 GetDlgItem(window, ID_DIAGNOSE) && GetDlgItem(window,ID_RECOVER) && GetDlgItem(window,ID_LOGDIR) && GetDlgItem(window,ID_BOOTPOWER) && log_window;
        DestroyWindow(window); log_window = NULL;
        puts(ok ? "GUI controls initialized (hidden; no device access)" : "GUI initialization failed");
        return ok ? 0 : 1;
    }
    ShowWindow(window, SW_SHOW); UpdateWindow(window);
    while (GetMessageA(&message, NULL, 0, 0) > 0) {
        if (!IsDialogMessageA(window, &message)) {
            TranslateMessage(&message); DispatchMessageA(&message);
        }
    }
    y540_log_close();
    return 0;
}

int main(int argc, char **argv)
{
    if (argc == 1) {
        begin_session("gui-fix2");
        HWND console = GetConsoleWindow();
        DWORD processes[2];
        if (console && GetConsoleProcessList(processes, 2) == 1) ShowWindow(console, SW_HIDE);
        return gui(0);
    }
    if (!strcmp(argv[1], "--gui-smoke") && argc == 2) return gui(1);
    if (!strcmp(argv[1], "--verify") && argc == 4)
        return begin_session("cli-verify") && verify_or_plan(argv[2], argv[3], NULL) ? 0 : 1;
    if (!strcmp(argv[1], "--plan") && argc == 5)
        return begin_session("cli-plan") && verify_or_plan(argv[2], argv[3], argv[4]) ? 0 : 1;
    if (!strcmp(argv[1],"--diagnose") && argc==4 && !strcmp(argv[2],"--boot-power")) {
        if(!strcmp(argv[3],"ac"))boot_power_context=1;
        else if(!strcmp(argv[3],"battery"))boot_power_context=2;
        else if(strcmp(argv[3],"unknown"))return 2;
        return diagnose()?0:1;
    }
    if (!strcmp(argv[1], "--diagnose") && argc == 2) return diagnose()?0:1;
    if (!strcmp(argv[1], "--update") && argc == 4)
        return begin_session("cli-advanced-firmware-write") && update_firmware(argv[2], argv[3]) ? 0 : 1;
    if (!strcmp(argv[1], "--list") && argc == 2) return begin_session("cli-hid-metadata") && list_devices() ? 0 : 1;
    output("Y540 fix2 - USB recovery and source updater\r\n\r\n"
           "  Y540Updater.exe                          Open GUI\r\n"
           "  Y540Updater.exe --verify FIRMWARE INI     Validate size and checksum\r\n"
           "  Y540Updater.exe --plan FIRMWARE INI JSON  Export staging-only packet plan\r\n"
           "  Y540Updater.exe --update FIRMWARE INI     Write keyboard firmware (hardware unverified)\r\n"
           "  Y540Updater.exe --diagnose                Save read-only PnP/power diagnostics\r\n"
           "  Y540Updater.exe --list                    Enumerate HID metadata\r\n"
           "  Y540Updater.exe --help                    Show this help\r\n\r\n"
           "Use Diagnose first. USB recovery is an explicit GUI action. No recovery is claimed verified on hardware.\r\n");
    return argc == 2 && !strcmp(argv[1], "--help") ? 0 : 2;
}
