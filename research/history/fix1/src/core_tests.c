#include "core.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static int failures;
#define CHECK(expr) do { if (!(expr)) { \
    fprintf(stderr, "FAIL line %d: %s\n", __LINE__, #expr); ++failures; \
} } while (0)

static void packet_tests(void)
{
    uint8_t report[64], data[57];
    size_t i;
    for (i = 0; i < sizeof(data); ++i) data[i] = (uint8_t)(0x80 + i);
    CHECK(y540_encode_c1(0x123, data, 57, report));
    CHECK(report[0] == 0 && report[1] == 0xc1 && report[2] == 0x23 &&
          report[3] == 1 && report[4] == 57);
    CHECK(!memcmp(report + 5, data, 57));
    CHECK(report[62] == 0 && report[63] == 0);
    CHECK(y540_encode_c1(1023, data, 1, report));
    CHECK(report[2] == 0xff && report[3] == 3 && report[5] == 0x80);
    CHECK(!y540_encode_c1(1023, data, 2, report));
    CHECK(!y540_encode_c1(0, data, 58, report));
    CHECK(!y540_encode_c1(0, data, 0, report));
    CHECK(y540_encode_c3(0x123456, report));
    CHECK(report[0] == 0 && report[1] == 0xc3 && report[2] == 0x56 &&
          report[3] == 0x34 && report[4] == 0x12 && report[5] == 0 && report[6] == 4);
    for (i = 7; i < sizeof(report); ++i) CHECK(report[i] == 0);
    CHECK(!y540_encode_c3(0x1000000, report));
}

static void block_tests(void)
{
    uint8_t data[1025], report[64], rebuilt[1024];
    y540_block block;
    size_t offset, length, packets;
    memset(data, 0xff, sizeof(data));
    CHECK(y540_block_count(0) == 0 && y540_block_count(1024) == 1 &&
          y540_block_count(1025) == 2);
    CHECK(y540_plan_block(data, sizeof(data), 0x400, 0, &block));
    CHECK(block.all_ff && block.address == 0x400 && block.source_length == 1024 &&
          block.chunk_count == 18 && block.staging_sum == 0xfc00);
    data[1024] = 0x12;
    CHECK(y540_plan_block(data, sizeof(data), 0x400, 1, &block));
    CHECK(!block.all_ff && block.address == 0x800 && block.source_offset == 1024 &&
          block.source_length == 1 && block.chunk_count == 1 && block.data[0] == 0x12);
    CHECK(block.data[1] == 0xff && block.data[1023] == 0xff);
    CHECK(block.staging_sum == (uint16_t)(0xfc00 - 0xff + 0x12));
    CHECK(!y540_plan_block(data, sizeof(data), 0, 2, &block));
    CHECK(!y540_plan_block(data, sizeof(data), 0xffffff, 0, &block));
    for (offset = 0; offset < 1024; ++offset) data[offset] = (uint8_t)offset;
    CHECK(y540_plan_block(data, sizeof(data), 0, 0, &block));
    memset(rebuilt, 0xff, sizeof(rebuilt));
    packets = 0;
    for (offset = 0; offset < block.source_length; offset += length) {
        length = block.source_length - offset;
        if (length > 57) length = 57;
        CHECK(y540_encode_c1((uint16_t)offset, block.data + offset, length, report));
        CHECK(((size_t)report[2] | ((size_t)report[3] << 8)) == offset);
        memcpy(rebuilt + offset, report + 5, report[4]);
        ++packets;
    }
    CHECK(packets == block.chunk_count && packets == 18 && length == 55);
    CHECK(!memcmp(rebuilt, data, 1024));
}

static void checksum_boundary_tests(void)
{
    uint8_t bytes[256] = {0};
    y540_checksum_options options = {0, 256, 254, 255, 0, 0};
    y540_checksum_result result;
    char error[256];
    bytes[0x80] = 0xaa;
    bytes[0x8f] = 0xbb;
    bytes[0x90] = 2;
    CHECK(y540_checksum(bytes, sizeof(bytes), &options, &result, error, sizeof(error)));
    CHECK(result.sum == 512 && result.computed == 512 && result.stored == 0);
    options.last_ff = 4;
    CHECK(y540_checksum(bytes, sizeof(bytes), &options, &result, error, sizeof(error)));
    CHECK(result.sum == 1022);
    options.invert = 1;
    CHECK(y540_checksum(bytes, sizeof(bytes), &options, &result, error, sizeof(error)));
    CHECK(result.computed == (uint16_t)(0u - 1022u));
    options.end = 257;
    CHECK(!y540_checksum(bytes, sizeof(bytes), &options, &result, error, sizeof(error)));
    options.end = 256;
    options.high = options.low;
    CHECK(!y540_checksum(bytes, sizeof(bytes), &options, &result, error, sizeof(error)));
}

static void sample_tests(const char *directory)
{
    y540_config *cfg = calloc(1, sizeof(*cfg));
    y540_checksum_result result;
    y540_checksum_options options;
    uint8_t *data = NULL;
    char ini_path[2048], image_path[2048], error[256];
    FILE *image;
    uint32_t value;
    size_t size = 55296;
    if (!cfg) { CHECK(cfg != NULL); return; }
    snprintf(ini_path, sizeof(ini_path), "%s/SHFU.ini", directory);
    snprintf(image_path, sizeof(image_path), "%s/44.bin", directory);
    if (!y540_config_load(ini_path, cfg, error, sizeof(error))) {
        fprintf(stderr, "%s: %s\n", ini_path, error);
        CHECK(0); free(cfg); return;
    }
    CHECK(cfg->count == 36);
    CHECK(!strcmp(y540_config_get(cfg, "main", "hwid"), "USB\\VID_048D&PID_C100"));
    CHECK(y540_config_get(cfg, "OPTION", "POPUPSFORNOTIFICATIONS") != NULL);
    CHECK(y540_config_number(cfg, "NEWVERSION", "MAINDEVICEUPID", 16, 0, &value) == 1 && value == 0xff89);
    CHECK(y540_config_number(cfg, "NEWVERSION", "UPDATEFILESIZEKB", 10, 0, &value) == 1 && value == 54);
    CHECK(y540_config_number(cfg, "NEWVERSION", "MISSING", 10, 123, &value) == 0 && value == 123);
    CHECK(y540_config_number(cfg, "MAIN", "HWID", 16, 0, &value) == -1);
    CHECK(y540_checksum_options_from_config(cfg, &options, error, sizeof(error)));
    CHECK(options.last_ff == 0 && options.start == 1024 && options.end == 55296);
    image = fopen(image_path, "rb");
    if (!image) { CHECK(image != NULL); free(cfg); return; }
    data = malloc(size);
    if (!data) { CHECK(data != NULL); fclose(image); free(cfg); return; }
    CHECK(fread(data, 1, size, image) == size);
    CHECK(fgetc(image) == EOF);
    fclose(image);
    CHECK(y540_validate_firmware(data, size, cfg, &result, error, sizeof(error)));
    CHECK(result.sum == 0x5622 && result.stored == 0x5622 && result.computed == 0xa9de && result.residual == 0);
    data[0x1000] ^= 1;
    CHECK(!y540_validate_firmware(data, size, cfg, &result, error, sizeof(error)) && result.residual != 0);
    data[0x1000] ^= 1;
    data[0x7ffe] ^= 1;
    CHECK(!y540_validate_firmware(data, size, cfg, &result, error, sizeof(error)) && result.residual != 0);
    data[0x7ffe] ^= 1;
    data[0] ^= 1;
    CHECK(y540_validate_firmware(data, size, cfg, &result, error, sizeof(error)));
    CHECK(!y540_validate_firmware(data, size - 1, cfg, &result, error, sizeof(error)));
    free(data);
    free(cfg);
}

int main(int argc, char **argv)
{
    packet_tests();
    block_tests();
    checksum_boundary_tests();
    sample_tests(argc > 1 ? argv[1] : "samples");
    if (failures) { fprintf(stderr, "%d checks failed\n", failures); return 1; }
    puts("PASS: real firmware checksum/corruption, INI fields, C1/C3 wire bytes, staging boundaries and partial padding");
    return 0;
}
