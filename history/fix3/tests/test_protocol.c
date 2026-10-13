/* Offline emulator: all feature reports stay in memory. No HID handles opened. */
#include "../src/protocol.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define WIN32_LEAN_AND_MEAN
#include <windows.h>

static unsigned failures;
#define CHECK(x) do { if (!(x)) { fprintf(stderr, "FAIL %d: %s\n", __LINE__, #x); ++failures; } } while(0)
#define IMAGE_SIZE 55296u

typedef struct {
    uint8_t flash[IMAGE_SIZE], staging[1024], request[64];
    uint32_t commit_address[256];
    unsigned commits, c0, chunks, erases, resets, reads, sleeps, commands;
    unsigned bad_packets, stage_corrupt, read_corrupt, fail_c1, failed_calls;
    unsigned commands_after_failure, handshake_zero, handshake_alt;
    uint8_t last_command, handshake_id;
    int custom_enabled, fail_boot, fail_handshake_read, mismatch_handshake;
    int no_d1_echo, backup_change, fail_backup_read, fail_chip_write;
    uint16_t chip;
} emulator;

static uint32_t address(const uint8_t *p)
{
    return (uint32_t)p[0] | ((uint32_t)p[1] << 8) | ((uint32_t)p[2] << 16);
}

static int emu_fail(emulator *e, y540_hid_error *error, const char *why)
{
    ++e->bad_packets;
    error->code = 123;
    snprintf(error->message, sizeof(error->message), "%s", why);
    return 0;
}

static int feature(void *context, int write, uint8_t report[64], size_t report_bytes, y540_hid_error *error)
{
    CHECK(report_bytes == (report[0] == 0x5a ? 17u : 64u));
    emulator *e = context;
    uint8_t cmd = write ? report[1] : e->request[1];
    uint32_t addr;
    size_t len, i;
    uint16_t sum;
    if (write && cmd == 7 && e->fail_chip_write) {
        --e->fail_chip_write;
        error->code = ERROR_GEN_FAILURE;
        strcpy(error->message, "injected boot not responsive");
        return 0;
    }
    if (write && e->fail_boot && cmd == 9) {
        error->code = 457;
        strcpy(error->message, "injected boot handoff failure");
        return 0;
    }
    if (!write && e->fail_handshake_read && e->request[1] == 'I') {
        --e->fail_handshake_read;
        error->code = 458;
        strcpy(error->message, "injected handshake read failure");
        return 0;
    }
    if (write && e->fail_c1 && cmd == 0xc1) {
        ++e->failed_calls;
        error->code = 456;
        strcpy(error->message, "injected permanent C1 transport failure");
        return 0;
    }
    if (e->failed_calls) ++e->commands_after_failure;
    if (write) {
        ++e->commands;
        e->last_command = cmd;
        memcpy(e->request, report, 64);
        if (!memcmp(report + 1, "ITE Tech. Inc.", 15)) {
            e->custom_enabled = !e->custom_enabled;
            e->handshake_id = report[0];
            if (report[0] == 0) ++e->handshake_zero;
            else if (report[0] == 0x5a) ++e->handshake_alt;
            else return emu_fail(e, error, "invalid handshake report ID");
            return 1;
        }
        if (cmd == 9) {
            if (report[0] != e->handshake_id || report[2] != 0)
                return emu_fail(e, error, "invalid boot handoff");
            return 1;
        }
        if (report[0]) return emu_fail(e, error, "nonzero boot report ID");
        switch (cmd) {
        case 0xc0: memset(e->staging, 0xff, sizeof(e->staging)); ++e->c0; return 1;
        case 0xc1:
            addr = (uint32_t)report[2] | ((uint32_t)report[3] << 8);
            len = report[4];
            if (!len || len > 57 || addr + len > 1024) return emu_fail(e, error, "invalid C1 bounds");
            memcpy(e->staging + addr, report + 5, len); ++e->chunks; return 1;
        case 0xc2:
            addr = address(report + 2);
            len = ((size_t)report[5] | ((size_t)report[6] << 8)) * 1024;
            if (!len || addr + len > IMAGE_SIZE) return emu_fail(e, error, "invalid C2 sector range");
            memset(e->flash + addr, 0xff, len); ++e->erases; return 1;
        case 0xc3:
            addr = address(report + 2);
            if (report[5] != 0 || report[6] != 4 || addr % 1024 || addr + 1024 > IMAGE_SIZE || e->commits >= 256)
                return emu_fail(e, error, "invalid C3 address/length");
            memcpy(e->flash + addr, e->staging, 1024);
            e->commit_address[e->commits++] = addr;
            return 1;
        case 0xd0: return 1;
        case 0xd1:
            addr = address(report + 2); len = report[5];
            if (!len || len > 56 || addr + len > IMAGE_SIZE) return emu_fail(e, error, "invalid D1 range");
            ++e->reads;
            if (e->fail_backup_read && !e->commits) {
                error->code = 459;
                strcpy(error->message, "injected backup read failure");
                return 0;
            }
            return 1;
        case 0xc4: ++e->resets; return 1;
        case 7:
            if (report[2] > 1 || report[3] != 0x20 || report[4] != 0xf0 || report[5] != 3)
                return emu_fail(e, error, "invalid chip query");
            return 1;
        default: return emu_fail(e, error, "unknown command");
        }
    }
    memcpy(report, e->request, 64);
    if (!memcmp(e->request + 1, "ITE Tech. Inc.", 15)) {
        if (!e->custom_enabled || e->mismatch_handshake) memset(report + 1, 0, 15);
        return 1;
    }
    switch (cmd) {
    case 0xd0:
        sum = 0;
        for (i = 0; i < 1024; ++i) sum = (uint16_t)(sum + e->staging[i]);
        if (e->stage_corrupt) sum ^= 1;
        report[2] = (uint8_t)sum; report[3] = (uint8_t)(sum >> 8); return 1;
    case 0xd1:
        addr = address(report + 2); len = report[5];
        memcpy(report + 6, e->flash + addr, len);
        if (e->backup_change && !e->commits && e->reads > (IMAGE_SIZE + 55) / 56)
            report[6] ^= 1;
        if (e->read_corrupt && e->commits && addr == 0) {
            report[6] ^= 1;
            if (e->read_corrupt == 2) e->read_corrupt = 0;
        }
        if (e->no_d1_echo) memset(report + 1, 0, 5);
        return 1;
    case 7: report[6] = e->request[2] ? (uint8_t)e->chip : (uint8_t)(e->chip >> 8); return 1;
    default: return emu_fail(e, error, "unexpected feature read");
    }
}

static void sleep_callback(void *context, uint32_t milliseconds)
{
    emulator *e = context;
    (void)milliseconds;
    ++e->sleeps;
}

static void setup(emulator *e, y540_hid_transport *t)
{
    y540_hid_error error;
    memset(e, 0, sizeof(*e));
    memset(e->flash, 0x55, sizeof(e->flash));
    e->chip = 0x8171;
    memset(t, 0, sizeof(*t));
    CHECK(y540_hid_init_custom(t, e, feature, sleep_callback, 5, &error));
}

typedef struct { unsigned calls; uint32_t fail_code; } reopen_test;
static int fake_reopen(void *context, y540_hid_transport *t, y540_hid_error *error)
{
    reopen_test *r = context;
    (void)t;
    ++r->calls;
    if (r->fail_code) {
        error->code = r->fail_code;
        strcpy(error->message, "injected reopen error");
        if (r->fail_code == ERROR_NOT_FOUND) r->fail_code = 0;
        return 0;
    }
    return 1;
}
static void readiness_tests(void)
{
    emulator *e = malloc(sizeof(*e));
    y540_hid_transport t;
    y540_hid_error error;
    reopen_test r = {0};
    if (!e) { CHECK(e != NULL); return; }
    setup(e, &t); e->fail_chip_write = 10;
    CHECK(y540_wait_boot_chip(&t,0x8171,fake_reopen,&r,NULL,NULL,&error));
    CHECK(r.calls == 1 && e->commands == 2 && !e->erases && !e->commits && !e->resets);
    setup(e, &t); e->fail_chip_write = 120; r.calls = 0;
    CHECK(!y540_wait_boot_chip(&t,0x8171,fake_reopen,&r,NULL,NULL,&error));
    CHECK(r.calls == 11 && !e->commands && !e->erases && !e->commits && !e->resets);
    CHECK(strstr(error.message,"within 12 checks") != NULL);
    setup(e, &t); e->chip = 0x9999; r.calls = 0;
    CHECK(!y540_wait_boot_chip(&t,0x8171,fake_reopen,&r,NULL,NULL,&error));
    CHECK(r.calls == 0 && !e->erases);
    setup(e, &t); e->fail_chip_write = 10; r.calls = 0; r.fail_code = ERROR_ACCESS_DENIED;
    CHECK(!y540_wait_boot_chip(&t,0x8171,fake_reopen,&r,NULL,NULL,&error));
    CHECK(r.calls == 1 && error.code == ERROR_ACCESS_DENIED && !e->erases);
    setup(e, &t); e->fail_chip_write = 10; r.calls = 0; r.fail_code = ERROR_NOT_FOUND;
    CHECK(y540_wait_boot_chip(&t,0x8171,fake_reopen,&r,NULL,NULL,&error));
    CHECK(r.calls == 2 && !e->erases && !e->commits && !e->resets);
    free(e);
}

static void handshake_tests(void)
{
    emulator *e = malloc(sizeof(*e));
    y540_hid_transport t;
    y540_hid_error error;
    if (!e) { CHECK(e != NULL); return; }
    setup(e, &t);
    CHECK(!y540_check_boot_chip(&t, 0, &error));
    CHECK(e->commands == 0);
    CHECK(!y540_check_boot_chip(&t, 0x9999, &error));
    CHECK(e->commands == 0);
    CHECK(y540_check_boot_chip(&t, 0x8171, &error));
    e->chip = 0x8176;
    CHECK(y540_check_boot_chip(&t, 0x8171, &error));
    e->chip = 0x9999;
    CHECK(!y540_check_boot_chip(&t, 0x8171, &error));
    setup(e, &t); t.device.vid=0x048d; t.device.pid=0xc100; t.device.usage_page=0xff89; t.device.usage=0x10; t.device.feature_report_bytes=17;
    CHECK(y540_enter_boot(&t, &error));
    CHECK(e->handshake_zero == 0 && e->handshake_alt == 1 && e->last_command == 9);
    setup(e, &t); t.device.vid=0x048d; t.device.pid=0xc100; t.device.usage_page=0xff89; t.device.usage=0x10; t.device.feature_report_bytes=17; e->custom_enabled = 1;
    CHECK(y540_enter_boot(&t, &error));
    CHECK(e->handshake_zero == 0 && e->handshake_alt == 2 && e->last_command == 9);
    setup(e, &t); t.device.vid=0x048d; t.device.pid=0xc100; t.device.usage_page=0xff89; t.device.usage=0x10; t.device.feature_report_bytes=17; e->fail_boot = 1;
    CHECK(!y540_enter_boot(&t, &error));
    CHECK(!e->custom_enabled && e->handshake_zero == 0);
    CHECK(strstr(error.message, "boot handoff failure") != NULL);
    setup(e, &t); t.device.vid=0x048d; t.device.pid=0xc100; t.device.usage_page=0xff89; t.device.usage=0x10; t.device.feature_report_bytes=17; e->fail_handshake_read = 10;
    CHECK(!y540_enter_boot(&t, &error));
    CHECK(!e->custom_enabled && e->handshake_zero == 0);
    CHECK(strstr(error.message, "handshake read failure") != NULL);
    setup(e, &t); t.device.vid=0x048d; t.device.pid=0xc100; t.device.usage_page=0xff89; t.device.usage=0x10; t.device.feature_report_bytes=17; e->fail_handshake_read = 20;
    CHECK(!y540_enter_boot(&t, &error));
    CHECK(e->handshake_zero == 0 && e->last_command != 9);
    CHECK(strstr(error.message, "handshake read failure") != NULL);
    CHECK(strstr(error.message, "mode cleanup failed") != NULL);
    setup(e, &t); t.device.vid=0x048d; t.device.pid=0xc100; t.device.usage_page=0xff89; t.device.usage=0x10; t.device.feature_report_bytes=17; e->mismatch_handshake = 1;
    CHECK(!y540_enter_boot(&t, &error));
    CHECK(e->last_command != 9 && e->handshake_zero == 0);
    setup(e, &t); t.device.vid=0x048d; t.device.pid=0xc100; t.device.usage_page=0xff89; t.device.usage=0x10; t.device.feature_report_bytes=17; e->custom_enabled = 1;
    CHECK(y540_exit_custom_mode(&t, &error));
    CHECK(!e->custom_enabled && e->handshake_alt == 1);
    setup(e, &t); t.device.vid=0x048d; t.device.pid=0xc100; t.device.usage_page=0xff89; t.device.usage=0x10; t.device.feature_report_bytes=17;
    CHECK(y540_exit_custom_mode(&t, &error));
    CHECK(!e->custom_enabled && e->handshake_alt == 2);
    CHECK(!e->bad_packets);
    free(e);
}

static unsigned backup_serial;
static wchar_t last_backup[MAX_PATH];
static int program(y540_hid_transport *t, const uint8_t *fw, size_t size,
                   const y540_config *cfg, y540_hid_error *error)
{
    wchar_t temp[MAX_PATH];
    CHECK(GetCurrentDirectoryW(MAX_PATH, temp) > 0);
    swprintf(last_backup, MAX_PATH, L"%ls\\y540-fix1-test-%lu-%u.bin", temp,
             (unsigned long)GetCurrentProcessId(), ++backup_serial);
    return y540_boot_program_with_backup(t, fw, size, cfg, last_backup, NULL, NULL, error);
}

static void delete_backup(void)
{
    if (GetFileAttributesW(last_backup) != INVALID_FILE_ATTRIBUTES)
        CHECK(DeleteFileW(last_backup));
}

static void check_backup(void)
{
    uint8_t data[IMAGE_SIZE];
    DWORD got = 0;
    HANDLE h = CreateFileW(last_backup, GENERIC_READ, FILE_SHARE_READ, NULL,
                            OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
    CHECK(h != INVALID_HANDLE_VALUE);
    if (h == INVALID_HANDLE_VALUE) return;
    CHECK(ReadFile(h, data, sizeof(data), &got, NULL) && got == sizeof(data));
    for (size_t i = 0; i < sizeof(data); ++i) CHECK(data[i] == 0x55);
    CloseHandle(h);
}

int main(int argc, char **argv)
{
    const char *directory = argc > 1 ? argv[1] : "samples";
    y540_config *cfg = malloc(sizeof(*cfg));
    uint8_t *firmware = malloc(IMAGE_SIZE);
    emulator *e = malloc(sizeof(*e));
    y540_hid_transport t;
    y540_hid_error error;
    char path[2048], config_error[256];
    FILE *file;
    unsigned i;
    if (!cfg || !firmware || !e) { fprintf(stderr, "Allocation failure\n"); return 1; }
    snprintf(path, sizeof(path), "%s/SHFU.ini", directory);
    if (!y540_config_load(path, cfg, config_error, sizeof(config_error))) {
        fprintf(stderr, "%s\n", config_error); return 1;
    }
    snprintf(path, sizeof(path), "%s/44.bin", directory);
    file = fopen(path, "rb");
    if (!file) { fprintf(stderr, "Missing firmware sample\n"); return 1; }
    CHECK(fread(firmware, 1, IMAGE_SIZE, file) == IMAGE_SIZE);
    fclose(file);
    /* A modified profile cannot disable chip qualification. */
    for (i = 0; i < cfg->count; ++i)
        if (!strcmp(cfg->entries[i].key, "BOOTDEVICECHIPID")) strcpy(cfg->entries[i].value, "0");
    setup(e, &t);
    CHECK(!program(&t, firmware, IMAGE_SIZE, cfg, &error));
    CHECK(e->commands == 0 && e->erases == 0);
    delete_backup();
    for (i = 0; i < cfg->count; ++i)
        if (!strcmp(cfg->entries[i].key, "BOOTDEVICECHIPID")) strcpy(cfg->entries[i].value, "8171");
    /* Legacy APIs cannot flash without an explicit backup destination. */
    setup(e, &t);
    CHECK(!y540_boot_program(&t, firmware, IMAGE_SIZE, cfg, NULL, NULL, &error));
    CHECK(e->commands == 0 && strstr(error.message, "backup destination"));
    CHECK(!y540_update_device(firmware, IMAGE_SIZE, cfg, NULL, NULL, &error));
    CHECK(e->commands == 0 && strstr(error.message, "backup destination"));
    CHECK(program(&t, firmware, IMAGE_SIZE, cfg, &error));
    check_backup();
    /* Refusing an existing backup must happen before feature I/O. */
    setup(e, &t);
    CHECK(!y540_boot_program_with_backup(&t, firmware, IMAGE_SIZE, cfg,
              last_backup, NULL, NULL, &error));
    CHECK(e->commands == 0);
    delete_backup();
    setup(e, &t);
    CHECK(program(&t, firmware, IMAGE_SIZE, cfg, &error));
    CHECK(!memcmp(e->flash, firmware, IMAGE_SIZE));
    CHECK(e->commits == 35 && e->c0 == 35 && e->chunks == 630 && e->erases == 1);
    CHECK(e->resets == 1 && e->last_command == 0xc4 && e->commit_address[e->commits - 1] == 0);
    for (i = 0; i + 1 < e->commits; ++i) CHECK(e->commit_address[i] != 0);
    CHECK(!e->bad_packets && e->reads > 900);
    delete_backup();

    setup(e, &t); e->stage_corrupt = 1;
    CHECK(!program(&t, firmware, IMAGE_SIZE, cfg, &error));
    CHECK(e->commits == 0 && e->resets == 0 && e->c0 == 1 && e->chunks == 18);
    CHECK(strstr(error.message, "staging checksum") != NULL);
    delete_backup();

    setup(e, &t); e->read_corrupt = 1;
    CHECK(!program(&t, firmware, IMAGE_SIZE, cfg, &error));
    CHECK(e->commits == 70 && e->erases == 2);
    CHECK(e->resets == 0 && e->last_command == 0xd1);
    CHECK(strstr(error.message, "readback differs") != NULL);
    delete_backup();

    for (i = 0; i < cfg->count; ++i)
        if (!strcmp(cfg->entries[i].key, "PROGRAMFAILRETRY")) strcpy(cfg->entries[i].value, "0");
    setup(e, &t); e->read_corrupt = 1;
    CHECK(!program(&t, firmware, IMAGE_SIZE, cfg, &error));
    CHECK(e->commits == 35 && e->erases == 1 && e->resets == 0 && e->last_command == 0xd1);
    delete_backup();
    for (i = 0; i < cfg->count; ++i)
        if (!strcmp(cfg->entries[i].key, "PROGRAMFAILRETRY")) strcpy(cfg->entries[i].value, "1");

    setup(e, &t); e->fail_c1 = 1;
    CHECK(!program(&t, firmware, IMAGE_SIZE, cfg, &error));
    CHECK(e->failed_calls == 10 && e->commits == 0 && e->resets == 0 && e->chunks == 0);
    CHECK(e->commands_after_failure == 0 && !e->bad_packets);
    delete_backup();

    setup(e, &t); e->read_corrupt = 2;
    CHECK(program(&t, firmware, IMAGE_SIZE, cfg, &error));
    CHECK(e->commits == 70 && e->erases == 2 && e->resets == 1);
    CHECK(!memcmp(e->flash, firmware, IMAGE_SIZE));
    delete_backup();

    setup(e, &t); e->no_d1_echo = 1;
    CHECK(program(&t, firmware, IMAGE_SIZE, cfg, &error));
    CHECK(e->resets == 1 && !memcmp(e->flash, firmware, IMAGE_SIZE));
    delete_backup();

    setup(e, &t); e->backup_change = 1;
    CHECK(!program(&t, firmware, IMAGE_SIZE, cfg, &error));
    CHECK(!e->erases && !e->commits && !e->resets);
    CHECK(strstr(error.message, "between backup reads") != NULL);
    delete_backup();

    setup(e, &t); e->fail_backup_read = 1;
    CHECK(!program(&t, firmware, IMAGE_SIZE, cfg, &error));
    CHECK(!e->erases && !e->commits && !e->resets);
    CHECK(strstr(error.message, "backup read failure") != NULL);
    delete_backup();

    setup(e, &t); firmware[0x1000] ^= 1;
    CHECK(!program(&t, firmware, IMAGE_SIZE, cfg, &error));
    CHECK(e->commands == 0);
    delete_backup();
    firmware[0x1000] ^= 1;
    /* Enabling the IVT guard must reject incompatible existing vectors before erase. */
    for (i = 0; i < cfg->count; ++i)
        if (!strcmp(cfg->entries[i].key, "NOCHECKIVT")) strcpy(cfg->entries[i].value, "0");
    setup(e, &t);
    CHECK(!program(&t, firmware, IMAGE_SIZE, cfg, &error));
    CHECK(e->reads > 0 && !e->erases && !e->commits && !e->resets);
    CHECK(strstr(error.message, "interrupt-vector") != NULL);
    delete_backup();
    readiness_tests();
    handshake_tests();
    free(e); free(firmware); free(cfg);
    if (failures) { fprintf(stderr, "%u protocol checks failed\n", failures); return 1; }
    puts("PASS: offline protocol model; durable backup, no final erase/reset on failure, aborts, chip identity, key cleanup, report 5A only and payload-only D1 responses");
    return 0;
}
