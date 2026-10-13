/* Offline emulator: all feature reports stay in memory. No HID handles opened. */
#include "../src/protocol.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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
    int fallback_handshake;
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

static int feature(void *context, int write, uint8_t report[64], y540_hid_error *error)
{
    emulator *e = context;
    uint8_t cmd = write ? report[1] : e->request[1];
    uint32_t addr;
    size_t len, i;
    uint16_t sum;
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
            ++e->reads; return 1;
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
        if (e->fallback_handshake && e->request[0] == 0x5a) memset(report + 1, 0, 15);
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
        if (e->read_corrupt && e->commits && addr == 0) {
            report[6] ^= 1;
            if (e->read_corrupt == 2) e->read_corrupt = 0;
        }
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

static void handshake_tests(void)
{
    emulator *e = malloc(sizeof(*e));
    y540_hid_transport t;
    y540_hid_error error;
    if (!e) { CHECK(e != NULL); return; }
    setup(e, &t);
    CHECK(y540_check_boot_chip(&t, 0x8171, &error));
    e->chip = 0x8176;
    CHECK(y540_check_boot_chip(&t, 0x8171, &error));
    e->chip = 0x9999;
    CHECK(!y540_check_boot_chip(&t, 0x8171, &error));
    setup(e, &t);
    CHECK(y540_enter_boot(&t, &error));
    CHECK(e->handshake_zero == 0 && e->handshake_alt == 1 && e->last_command == 9);
    setup(e, &t); e->fallback_handshake = 1;
    CHECK(y540_enter_boot(&t, &error));
    CHECK(e->handshake_zero == 1 && e->handshake_alt == 2 && e->last_command == 9);
    CHECK(!e->bad_packets);
    free(e);
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
    setup(e, &t);
    CHECK(y540_boot_program(&t, firmware, IMAGE_SIZE, cfg, NULL, NULL, &error));
    CHECK(!memcmp(e->flash, firmware, IMAGE_SIZE));
    CHECK(e->commits == 35 && e->c0 == 35 && e->chunks == 630 && e->erases == 1);
    CHECK(e->resets == 1 && e->last_command == 0xc4 && e->commit_address[e->commits - 1] == 0);
    for (i = 0; i + 1 < e->commits; ++i) CHECK(e->commit_address[i] != 0);
    CHECK(!e->bad_packets && e->reads > 900);

    setup(e, &t); e->stage_corrupt = 1;
    CHECK(!y540_boot_program(&t, firmware, IMAGE_SIZE, cfg, NULL, NULL, &error));
    CHECK(e->commits == 0 && e->resets == 0 && e->c0 == 1 && e->chunks == 18);
    CHECK(strstr(error.message, "staging checksum") != NULL);

    setup(e, &t); e->read_corrupt = 1;
    CHECK(!y540_boot_program(&t, firmware, IMAGE_SIZE, cfg, NULL, NULL, &error));
    CHECK(e->commits == 70 && e->erases == 4);
    /* Supplied PROGRAMFAILERASETHENRESET=1 explicitly resets after final cleanup. */
    CHECK(e->resets == 1 && e->last_command == 0xc4);
    CHECK(strstr(error.message, "readback differs") != NULL);

    setup(e, &t); e->fail_c1 = 1;
    CHECK(!y540_boot_program(&t, firmware, IMAGE_SIZE, cfg, NULL, NULL, &error));
    CHECK(e->failed_calls == 10 && e->commits == 0 && e->resets == 0 && e->chunks == 0);
    CHECK(e->commands_after_failure == 0 && !e->bad_packets);

    setup(e, &t); e->read_corrupt = 2;
    CHECK(y540_boot_program(&t, firmware, IMAGE_SIZE, cfg, NULL, NULL, &error));
    CHECK(e->commits == 70 && e->erases == 3 && e->resets == 1);
    CHECK(!memcmp(e->flash, firmware, IMAGE_SIZE));

    setup(e, &t); firmware[0x1000] ^= 1;
    CHECK(!y540_boot_program(&t, firmware, IMAGE_SIZE, cfg, NULL, NULL, &error));
    CHECK(e->commands == 0);
    firmware[0x1000] ^= 1;
    /* Enabling the IVT guard must reject incompatible existing vectors before erase. */
    for (i = 0; i < cfg->count; ++i)
        if (!strcmp(cfg->entries[i].key, "NOCHECKIVT")) strcpy(cfg->entries[i].value, "0");
    setup(e, &t);
    CHECK(!y540_boot_program(&t, firmware, IMAGE_SIZE, cfg, NULL, NULL, &error));
    CHECK(e->reads > 0 && !e->erases && !e->commits && !e->resets);
    CHECK(strstr(error.message, "interrupt-vector") != NULL);
    handshake_tests();
    free(e); free(firmware); free(cfg);
    if (failures) { fprintf(stderr, "%u protocol checks failed\n", failures); return 1; }
    puts("PASS: complete firmware emulator, first-block-last ordering, FF skip, retry cleanup, aborts, chip identity and handshake report IDs");
    return 0;
}
