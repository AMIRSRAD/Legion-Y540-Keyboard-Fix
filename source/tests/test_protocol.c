/* Offline emulator: all feature reports stay in memory. No HID handles opened. */
#include "../src/protocol.h"
#include "../src/sha256.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define WIN32_LEAN_AND_MEAN
#include <windows.h>

static unsigned failures;
#define CHECK(x) do { if (!(x)) { fprintf(stderr, "FAIL %d: %s\n", __LINE__, #x); ++failures; } } while(0)
#define IMAGE_SIZE 55296u

typedef struct {
    uint8_t flash[IMAGE_SIZE], upper[0x2800], staging[1024], request[64];
    int upper_valid, fail_upper;
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
            if (!len || len > 56 || addr + len > 0x10000u ||
                (addr < IMAGE_SIZE && addr + len > IMAGE_SIZE))
                return emu_fail(e, error, "invalid D1 range");
            if (addr >= IMAGE_SIZE && (!e->upper_valid || e->fail_upper)) {
                error->code = 459;
                strcpy(error->message, "injected upper-flash read failure");
                return 0;
            }
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
        if (addr >= IMAGE_SIZE) memcpy(report + 6, e->upper + addr - IMAGE_SIZE, len);
        else memcpy(report + 6, e->flash + addr, len);
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

/* Simulated bus + clock for boot-device discovery. The model encodes the one
 * behaviour the 2026-10-13 ETW recording proved: a boot device left idle for
 * more than about 5 s after enumeration is suspended by Windows and never
 * answers again. */
#define SIM_IDLE_LIMIT_MS 5000u
typedef struct {
    uint64_t now, appear_at, enumerated_at, contact_at;
    unsigned finds, sleeps;
    uint32_t transient_code, transient_count, hard_code;
    uint32_t longest_sleep;
} sim_bus;
static uint64_t sim_clock(void *context) { return ((sim_bus *)context)->now; }
static void sim_sleep(void *context, uint32_t ms)
{
    sim_bus *b = context;
    b->now += ms; ++b->sleeps;
    if (ms > b->longest_sleep) b->longest_sleep = ms;
}
static int sim_find(void *context, y540_hid_transport *t, y540_hid_error *e)
{
    sim_bus *b = context;
    (void)t;
    ++b->finds;
    b->now += 90; /* cost of one HID metadata scan */
    if (b->hard_code) { e->code = b->hard_code; strcpy(e->message, "injected hard open error"); return 0; }
    if (b->transient_count) {
        --b->transient_count; e->code = b->transient_code;
        strcpy(e->message, "injected transient open error"); return 0;
    }
    if (b->now < b->appear_at) { e->code = ERROR_NOT_FOUND; strcpy(e->message, "not enumerated"); return 0; }
    b->contact_at = b->now;
    return 1;
}
static int sim_device_dead(const sim_bus *b)
{
    return b->contact_at - b->enumerated_at > SIM_IDLE_LIMIT_MS;
}
static void boot_discovery_tests(void)
{
    y540_hid_transport t = {0};
    y540_hid_error error = {0};
    sim_bus b;
    /* Trace-shaped case: device enumerates 490 ms after the handoff returns. */
    memset(&b, 0, sizeof(b)); b.appear_at = b.enumerated_at = 490;
    CHECK(y540_wait_boot_device(sim_find, &b, &t, sim_sleep, sim_clock, &b, 40, 30000, NULL, NULL, &error));
    CHECK(!sim_device_dead(&b) && b.contact_at - b.enumerated_at < 500);
    /* Regression model of fix2..fix4: fixed 6000 ms sleep, then one scan. */
    memset(&b, 0, sizeof(b)); b.appear_at = b.enumerated_at = 490;
    sim_sleep(&b, 6000);
    CHECK(sim_find(&b, &t, &error));
    CHECK(sim_device_dead(&b)); /* the old behaviour leaves the device idle >5 s */
    /* Slow enumeration still works and never sleeps long between scans. */
    memset(&b, 0, sizeof(b)); b.appear_at = b.enumerated_at = 12000;
    CHECK(y540_wait_boot_device(sim_find, &b, &t, sim_sleep, sim_clock, &b, 40, 30000, NULL, NULL, &error));
    CHECK(!sim_device_dead(&b) && b.longest_sleep <= 40);
    /* Device still starting: transient errors are retried. */
    memset(&b, 0, sizeof(b)); b.transient_code = ERROR_DEVICE_NOT_CONNECTED; b.transient_count = 3;
    CHECK(y540_wait_boot_device(sim_find, &b, &t, sim_sleep, sim_clock, &b, 40, 30000, NULL, NULL, &error));
    CHECK(b.finds == 4 && b.sleeps == 3);
    /* A real error (rights, profile mismatch) stops immediately; no polling storm. */
    memset(&b, 0, sizeof(b)); b.hard_code = ERROR_ACCESS_DENIED;
    CHECK(!y540_wait_boot_device(sim_find, &b, &t, sim_sleep, sim_clock, &b, 40, 30000, NULL, NULL, &error));
    CHECK(error.code == ERROR_ACCESS_DENIED && b.finds == 1 && b.sleeps == 0);
    memset(&b, 0, sizeof(b)); b.hard_code = ERROR_BAD_LENGTH;
    CHECK(!y540_wait_boot_device(sim_find, &b, &t, sim_sleep, sim_clock, &b, 40, 30000, NULL, NULL, &error));
    CHECK(error.code == ERROR_BAD_LENGTH && b.finds == 1);
    /* Never appears: bounded by the budget and reported as NOT_FOUND. */
    memset(&b, 0, sizeof(b)); b.appear_at = (uint64_t)1 << 40;
    CHECK(!y540_wait_boot_device(sim_find, &b, &t, sim_sleep, sim_clock, &b, 40, 2000, NULL, NULL, &error));
    CHECK(error.code == ERROR_NOT_FOUND && b.now >= 2000 && b.now < 2000 + 200);
    CHECK(strstr(error.message, "did not reappear") != NULL);
    /* Invalid arguments are refused without touching the bus. */
    memset(&b, 0, sizeof(b));
    CHECK(!y540_wait_boot_device(NULL, &b, &t, sim_sleep, sim_clock, &b, 40, 1000, NULL, NULL, &error));
    CHECK(!y540_wait_boot_device(sim_find, &b, &t, sim_sleep, sim_clock, &b, 0, 1000, NULL, NULL, &error));
    CHECK(b.finds == 0);
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

static void known_image_tests(const uint8_t *stock, const y540_config *cfg)
{
    emulator *e = malloc(sizeof(*e));
    y540_hid_transport t;
    y540_hid_error error;
    unsigned reads_known, reads_unknown;
    static const uint8_t empty_digest[4] = {0xe3, 0xb0, 0xc4, 0x42};
    static const uint8_t abc_digest[4] = {0xba, 0x78, 0x16, 0xbf};
    uint8_t digest[32], file_image[IMAGE_SIZE];
    FILE *backup;
    if (!e) { CHECK(e != NULL); return; }
    y540_sha256((const uint8_t *)"", 0, digest);
    CHECK(!memcmp(digest, empty_digest, 4));
    y540_sha256((const uint8_t *)"abc", 3, digest);
    CHECK(!memcmp(digest, abc_digest, 4));
    /* 55-, 56- and 64-byte inputs cross the padding boundaries. */
    {
        uint8_t buf[200];
        memset(buf, 'a', sizeof(buf));
        y540_sha256(buf, 56, digest);   /* 56 'a' = b35439a4... */
        CHECK(digest[0] == 0xb3 && digest[1] == 0x54 && digest[2] == 0x39 && digest[3] == 0xa4);
        y540_sha256(buf, 64, digest);   /* 64 'a' = ffe054fe... */
        CHECK(digest[0] == 0xff && digest[1] == 0xe0 && digest[2] == 0x54 && digest[3] == 0xfe);
    }
    /* Device already holds the exact original: one backup read, no second one. */
    setup(e, &t); memcpy(e->flash, stock, IMAGE_SIZE);
    CHECK(program(&t, stock, IMAGE_SIZE, cfg, &error));
    reads_known = e->reads;
    CHECK(e->resets == 1 && !memcmp(e->flash, stock, IMAGE_SIZE));
    backup = _wfopen(last_backup, L"rb");
    CHECK(backup != NULL);
    if (backup) {
        CHECK(fread(file_image, 1, IMAGE_SIZE, backup) == IMAGE_SIZE);
        CHECK(!memcmp(file_image, stock, IMAGE_SIZE));
        fclose(backup);
    }
    delete_backup();
    /* Anything else keeps the two-read rule: 3 reads (2 backup + verify) vs 2. */
    setup(e, &t); memcpy(e->flash, stock, IMAGE_SIZE); e->flash[0x1234] ^= 1;
    CHECK(program(&t, stock, IMAGE_SIZE, cfg, &error));
    reads_unknown = e->reads;
    CHECK(reads_known * 3 == reads_unknown * 2);
    delete_backup();
    free(e);
}

static void reset_dependency_tests(const char *directory, const char *candidate_name, const uint8_t *stock, y540_config *cfg)
{
    emulator *e = malloc(sizeof(*e));
    uint8_t *candidate = malloc(IMAGE_SIZE), *upper = malloc(0x2800);
    y540_hid_transport t;
    y540_hid_error error;
    char path[2048];
    FILE *f;
    CHECK(e && candidate && upper);
    if (!e || !candidate || !upper) { free(e); free(candidate); free(upper); return; }
    snprintf(path, sizeof(path), "%s/%s", directory, candidate_name);
    f = fopen(path, "rb"); CHECK(f != NULL);
    if (!f) { free(e); free(candidate); free(upper); return; }
    CHECK(fread(candidate, 1, IMAGE_SIZE, f) == IMAGE_SIZE); fclose(f);
    snprintf(path, sizeof(path), "%s/upper-flash-dump.bin", directory);
    f = fopen(path, "rb"); CHECK(f != NULL);
    if (!f) { free(e); free(candidate); free(upper); return; }
    CHECK(fread(upper, 1, 0x2800, f) == 0x2800); fclose(f);
    int old_skip_ivt = 1;
    for (unsigned i = 0; i < cfg->count; ++i)
        if (!strcmp(cfg->entries[i].key, "NOCHECKIVT")) {
            old_skip_ivt = atoi(cfg->entries[i].value);
            strcpy(cfg->entries[i].value, "1");
        }

    /* Matching on-device dependency: two short reads, one known backup, verify. */
    setup(e, &t); memcpy(e->flash, stock, IMAGE_SIZE);
    memcpy(e->upper, upper, 0x2800); e->upper_valid = 1;
    CHECK(program(&t, candidate, IMAGE_SIZE, cfg, &error));
    CHECK(e->reads == 2u + 2u * ((IMAGE_SIZE + 55u) / 56u));
    CHECK(e->resets == 1 && e->erases == 1 && !memcmp(e->flash, candidate, IMAGE_SIZE));
    CHECK(!memcmp(e->upper, upper, 0x2800));
    for (unsigned i = 0; i < e->commits; ++i) CHECK(e->commit_address[i] + 1024 <= IMAGE_SIZE);
    delete_backup();

    /* fix10: resume after a write interrupted at block 0x5800 (block 0 blank). */
    {
        uint8_t *partial = malloc(IMAGE_SIZE);
        CHECK(partial != NULL);
        if (partial) {
            memset(partial, 0xff, IMAGE_SIZE);
            memcpy(partial + 0x400, candidate + 0x400, 0x5800 - 0x400);
            setup(e, &t); memcpy(e->flash, partial, IMAGE_SIZE);
            memcpy(e->upper, upper, 0x2800); e->upper_valid = 1;
            CHECK(program(&t, candidate, IMAGE_SIZE, cfg, &error));
            CHECK(e->reads == 2u + 2u * ((IMAGE_SIZE + 55u) / 56u));
            CHECK(e->resets == 1 && !memcmp(e->flash, candidate, IMAGE_SIZE));
            delete_backup();
            partial[0x1234] ^= 0x01; /* not a clean interrupted write: two reads again */
            setup(e, &t); memcpy(e->flash, partial, IMAGE_SIZE);
            memcpy(e->upper, upper, 0x2800); e->upper_valid = 1;
            CHECK(program(&t, candidate, IMAGE_SIZE, cfg, &error));
            CHECK(e->reads == 2u + 3u * ((IMAGE_SIZE + 55u) / 56u));
            CHECK(e->resets == 1 && !memcmp(e->flash, candidate, IMAGE_SIZE));
            delete_backup();
            free(partial);
        }
    }

    /* A mismatch in either dependency must stop before backup or erase. */
    for (unsigned which = 0; which < 2; ++which) {
        setup(e, &t); memcpy(e->flash, stock, IMAGE_SIZE);
        memcpy(e->upper, upper, 0x2800); e->upper_valid = 1;
        e->upper[(which ? 0xf455 : 0xf12c) - IMAGE_SIZE] ^= 1;
        CHECK(!program(&t, candidate, IMAGE_SIZE, cfg, &error));
        CHECK(!e->erases && !e->commits && !e->resets);
        CHECK(e->reads == which + 1);
        CHECK(strstr(error.message, "dependency differs") != NULL);
        CHECK(!memcmp(e->flash, stock, IMAGE_SIZE));
        delete_backup();
    }
    setup(e, &t); memcpy(e->flash, stock, IMAGE_SIZE);
    e->fail_upper = 1;
    CHECK(!program(&t, candidate, IMAGE_SIZE, cfg, &error));
    CHECK(!e->erases && !e->commits && !e->resets && !e->reads);
    delete_backup();

    /* exp1 rollback does not depend on the external reset routine. */
    uint8_t *return_image = malloc(IMAGE_SIZE);
    snprintf(path, sizeof(path), "%s/exp2-backup-test.bin", directory);
    f = fopen(path, "rb"); CHECK(f && return_image);
    if (f && return_image) {
        CHECK(fread(return_image, 1, IMAGE_SIZE, f) == IMAGE_SIZE);
        setup(e, &t);
        CHECK(!program(&t, return_image, IMAGE_SIZE, cfg, &error));
        CHECK(!e->commands && !e->erases && !e->commits && !e->resets);
        CHECK(strstr(error.message, "withdrawn/unknown") != NULL);
        delete_backup();
    }
    if (f) fclose(f);
    snprintf(path, sizeof(path), "%s/44-nosleep-exp1.bin", directory);
    f = fopen(path, "rb"); CHECK(f && return_image);
    if (f && return_image) {
        CHECK(fread(return_image, 1, IMAGE_SIZE, f) == IMAGE_SIZE);
        setup(e, &t); memcpy(e->flash, candidate, IMAGE_SIZE);
        CHECK(program(&t, return_image, IMAGE_SIZE, cfg, &error));
        CHECK(e->reads == 2u * ((IMAGE_SIZE + 55u) / 56u));
        CHECK(e->resets == 1 && !memcmp(e->flash, return_image, IMAGE_SIZE));
        delete_backup();
    }
    if (f) fclose(f);
    free(return_image);
    for (unsigned i = 0; i < cfg->count; ++i)
        if (!strcmp(cfg->entries[i].key, "NOCHECKIVT"))
            strcpy(cfg->entries[i].value, old_skip_ivt ? "1" : "0");
    free(e); free(candidate); free(upper);
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
    /* Regression: returning FROM exact exp2 must use one durable backup read,
     * followed by target verification. It does not qualify exp2 as a good image. */
    snprintf(path, sizeof(path), "%s/exp2-backup-test.bin", directory);
    file = fopen(path, "rb");
    CHECK(file != NULL);
    if (file) {
        setup(e, &t);
        CHECK(fread(e->flash, 1, IMAGE_SIZE, file) == IMAGE_SIZE);
        fclose(file);
        CHECK(program(&t, firmware, IMAGE_SIZE, cfg, &error));
        CHECK(e->reads == 2u * ((IMAGE_SIZE + 55u) / 56u));
        CHECK(e->resets == 1 && !memcmp(e->flash, firmware, IMAGE_SIZE));
        { FILE *saved = _wfopen(last_backup, L"rb");
          uint8_t *original = malloc(IMAGE_SIZE);
          CHECK(saved && original);
          if (saved && original) {
              CHECK(fread(original, 1, IMAGE_SIZE, saved) == IMAGE_SIZE);
              uint8_t hash[32]; y540_sha256(original, IMAGE_SIZE, hash);
              CHECK(hash[0] == 0x82 && hash[1] == 0xc9 && hash[31] == 0xb8);
          }
          if (saved) fclose(saved);
          free(original); }
        delete_backup();
    }
    reset_dependency_tests(directory, "44-recovery-exp3.bin", firmware, cfg);
    reset_dependency_tests(directory, "44-reset-exp4.bin", firmware, cfg);
    known_image_tests(firmware, cfg);
    boot_discovery_tests();
    readiness_tests();
    handshake_tests();
    free(e); free(firmware); free(cfg);
    if (failures) { fprintf(stderr, "%u protocol checks failed\n", failures); return 1; }
    puts("PASS: offline protocol model; durable backup, no final erase/reset on failure, aborts, chip identity, key cleanup, report 5A only and payload-only D1 responses");
    return 0;
}
