#ifndef Y540_CORE_H
#define Y540_CORE_H

#include <stddef.h>
#include <stdint.h>

/* Offline reconstruction only; no device discovery, writes or reset operations. */
#define Y540_REPORT_SIZE 64u
#define Y540_BLOCK_SIZE 1024u
#define Y540_CHUNK_SIZE 57u
#define Y540_CONFIG_MAX_ENTRIES 128u

typedef struct {
    char section[32];
    char key[64];
    /* Raw bytes preserved, including the vendor's non-UTF-8 notification text. */
    char value[1024];
} y540_config_entry;

typedef struct {
    y540_config_entry entries[Y540_CONFIG_MAX_ENTRIES];
    size_t count;
} y540_config;

typedef struct {
    uint32_t start, end, high, low, last_ff;
    int invert;
} y540_checksum_options;

typedef struct {
    uint16_t sum, stored, computed, residual;
} y540_checksum_result;

typedef struct {
    uint32_t address;
    size_t source_offset, source_length, chunk_count;
    int all_ff;
    uint16_t staging_sum;
    uint8_t data[Y540_BLOCK_SIZE];
} y540_block;

/* All fallbacks are explicit reconstruction choices, not verified vendor defaults. */
int y540_config_load(const char *path, y540_config *cfg, char *error, size_t cap);
const char *y540_config_get(const y540_config *cfg, const char *section, const char *key);
/* 1 = explicit valid value, 0 = absent (fallback returned), -1 = malformed. */
int y540_config_number(const y540_config *cfg, const char *section, const char *key,
                       int base, uint32_t fallback, uint32_t *value);
/* Requires explicit range/checksum keys; absent LASTBYTESBEFF models zero. */
int y540_checksum_options_from_config(const y540_config *cfg,
                                      y540_checksum_options *options,
                                      char *error, size_t cap);
int y540_checksum(const uint8_t *data, size_t size,
                  const y540_checksum_options *options,
                  y540_checksum_result *result, char *error, size_t cap);
/* Returns 1 only if configured size and checksum residual both validate. */
int y540_validate_firmware(const uint8_t *data, size_t size, const y540_config *cfg,
                           y540_checksum_result *result, char *error, size_t cap);
/* Full 64-byte feature report, report ID zero. Unused bytes deterministically zero. */
int y540_encode_c1(uint16_t offset, const uint8_t *data, size_t length,
                    uint8_t report[Y540_REPORT_SIZE]);
int y540_encode_c3(uint32_t address, uint8_t report[Y540_REPORT_SIZE]);
size_t y540_block_count(size_t size);
/* Pads final partial staging block with FF; chunk_count sends actual source bytes. */
int y540_plan_block(const uint8_t *data, size_t size, uint32_t start_address,
                     size_t index, y540_block *block);

#endif
