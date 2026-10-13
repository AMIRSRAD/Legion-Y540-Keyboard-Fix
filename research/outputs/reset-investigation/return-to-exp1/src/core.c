#include "core.h"

#include <ctype.h>
#include <errno.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static int fail(char *error, size_t cap, const char *message)
{
    if (error && cap) snprintf(error, cap, "%s", message);
    return 0;
}

static int equal_ci(const char *a, const char *b)
{
    while (*a && *b) {
        if (toupper((unsigned char)*a++) != toupper((unsigned char)*b++)) return 0;
    }
    return *a == *b;
}

static char *trim(char *s)
{
    char *end;
    while (isspace((unsigned char)*s)) ++s;
    end = s + strlen(s);
    while (end > s && isspace((unsigned char)end[-1])) --end;
    *end = '\0';
    return s;
}

int y540_config_load(const char *path, y540_config *cfg, char *error, size_t cap)
{
    FILE *file;
    char line[1200], section[32] = "";
    size_t line_no = 0;
    if (!path || !cfg) return fail(error, cap, "Missing configuration argument");
    memset(cfg, 0, sizeof(*cfg));
    file = fopen(path, "rb");
    if (!file) return fail(error, cap, "Cannot open configuration");
    while (fgets(line, sizeof(line), file)) {
        char *p, *eq, *key, *value;
        y540_config_entry *entry;
        ++line_no;
        if (!strchr(line, '\n') && !feof(file)) goto bad_line;
        p = trim(line);
        if (!*p || *p == ';' || *p == '#') continue;
        if (*p == '[') {
            char *close = strchr(p + 1, ']');
            if (!close || *trim(close + 1)) goto bad_line;
            *close = '\0';
            p = trim(p + 1);
            if (!*p || strlen(p) >= sizeof(section)) goto bad_line;
            strcpy(section, p);
            continue;
        }
        eq = strchr(p, '=');
        if (!eq || !*section) goto bad_line;
        *eq = '\0';
        key = trim(p);
        value = trim(eq + 1);
        if (!*key || strlen(key) >= sizeof(cfg->entries[0].key) ||
            strlen(value) >= sizeof(cfg->entries[0].value) ||
            cfg->count == Y540_CONFIG_MAX_ENTRIES) goto bad_line;
        entry = &cfg->entries[cfg->count++];
        strcpy(entry->section, section);
        strcpy(entry->key, key);
        strcpy(entry->value, value);
    }
    if (ferror(file)) {
        fclose(file);
        return fail(error, cap, "Cannot read configuration");
    }
    fclose(file);
    if (error && cap) *error = '\0';
    return 1;
bad_line:
    fclose(file);
    if (error && cap) snprintf(error, cap, "Invalid or oversized INI line %lu", (unsigned long)line_no);
    return 0;
}

const char *y540_config_get(const y540_config *cfg, const char *section, const char *key)
{
    size_t i;
    if (!cfg || !section || !key) return NULL;
    /* Retain all entries; the last duplicate wins in this reconstruction. */
    for (i = cfg->count; i > 0; --i) {
        const y540_config_entry *e = &cfg->entries[i - 1];
        if (equal_ci(e->section, section) && equal_ci(e->key, key)) return e->value;
    }
    return NULL;
}

int y540_config_number(const y540_config *cfg, const char *section, const char *key,
                       int base, uint32_t fallback, uint32_t *value)
{
    const char *text = y540_config_get(cfg, section, key);
    char *end;
    unsigned long number;
    if (!value || (base != 10 && base != 16)) return -1;
    *value = fallback;
    if (!text) return 0;
    if (!*text || *text == '-' || *text == '+') return -1;
    errno = 0;
    number = strtoul(text, &end, base);
    if (errno || *end || number > UINT32_MAX) return -1;
    *value = (uint32_t)number;
    return 1;
}

int y540_checksum_options_from_config(const y540_config *cfg,
                                      y540_checksum_options *o,
                                      char *error, size_t cap)
{
    uint32_t invert;
    if (!cfg || !o) return fail(error, cap, "Missing checksum configuration");
    memset(o, 0, sizeof(*o));
    if (y540_config_number(cfg, "NEWVERSION", "CHECKSUMSTARTADDRESS", 16, 0, &o->start) != 1 ||
        y540_config_number(cfg, "NEWVERSION", "CHECKSUMENDADDRESS", 16, 0, &o->end) != 1 ||
        y540_config_number(cfg, "NEWVERSION", "CHECKSUMVALUEHIGHADDRESS", 16, 0, &o->high) != 1 ||
        y540_config_number(cfg, "NEWVERSION", "CHECKSUMVALUELOWADDRESS", 16, 0, &o->low) != 1 ||
        y540_config_number(cfg, "NEWVERSION", "CHECKSUMINVERT", 10, 0, &invert) != 1)
        return fail(error, cap, "Required checksum option missing or malformed");
    if (y540_config_number(cfg, "NEWVERSION", "CHECKSUMLASTBYTESBEFF", 10, 0, &o->last_ff) < 0)
        return fail(error, cap, "Malformed trailing FF option");
    o->invert = invert != 0;
    return 1;
}

/* REA ev_d7d8a962af833b8fbaa710f84a02e240eaa96b25126558ce9c456da0bbfdac4f,
   CalculateWordCheckSum VA 0x40B260. See docs/updater-trace.md for limitations. */
int y540_checksum(const uint8_t *data, size_t size, const y540_checksum_options *o,
                  y540_checksum_result *r, char *error, size_t cap)
{
    uint32_t i;
    uint16_t sum = 0;
    if (!data || !o || !r) return fail(error, cap, "Missing checksum argument");
    memset(r, 0, sizeof(*r));
    if (o->start > o->end || o->end > size || o->high >= size || o->low >= size ||
        o->high == o->low || o->last_ff > o->end)
        return fail(error, cap, "Invalid checksum range or field offsets");
    for (i = o->start; i < o->end; ++i) {
        uint8_t byte;
        if (i >= 0x80 && i <= 0x8f) continue;
        byte = (i == o->high || i == o->low ||
                (o->last_ff && i >= o->end - o->last_ff)) ? 0xff : data[i];
        sum = (uint16_t)(sum + byte);
    }
    r->sum = sum;
    r->stored = (uint16_t)(((uint16_t)data[o->high] << 8) | data[o->low]);
    r->computed = o->invert ? (uint16_t)(0u - sum) : sum;
    r->residual = (uint16_t)(r->computed + r->stored);
    if (error && cap) *error = '\0';
    return 1;
}

int y540_validate_firmware(const uint8_t *data, size_t size, const y540_config *cfg,
                           y540_checksum_result *r, char *error, size_t cap)
{
    uint32_t kb;
    y540_checksum_options options;
    if (r) memset(r, 0, sizeof(*r));
    if (y540_config_number(cfg, "NEWVERSION", "UPDATEFILESIZEKB", 10, 0, &kb) != 1 || !kb)
        return fail(error, cap, "Required firmware size missing or malformed");
    if ((uint64_t)size != (uint64_t)kb * 1024u)
        return fail(error, cap, "Firmware size does not match configuration");
    if (!y540_checksum_options_from_config(cfg, &options, error, cap) ||
        !y540_checksum(data, size, &options, r, error, cap)) return 0;
    if (r->residual) return fail(error, cap, "Firmware checksum residual is nonzero");
    return 1;
}

/* C1: REA ev_95995aceca788b8d7995f1143ffdbab2c4b25eedad86ea29fb90a3a414715457.
   Report wrapper offset: ev_c1e2256612790474ac0108d8787fe4ebd5e1ad37ea7851f50df021b981d3fcb8.
   Zeroed unused report bytes are a reconstruction choice; original malloc was uninitialized. */
int y540_encode_c1(uint16_t offset, const uint8_t *data, size_t length,
                    uint8_t report[Y540_REPORT_SIZE])
{
    if (!report || !data || !length || length > Y540_CHUNK_SIZE ||
        (size_t)offset + length > Y540_BLOCK_SIZE) return 0;
    memset(report, 0, Y540_REPORT_SIZE);
    report[1] = 0xc1;
    report[2] = (uint8_t)offset;
    report[3] = (uint8_t)(offset >> 8);
    report[4] = (uint8_t)length;
    memcpy(report + 5, data, length);
    return 1;
}

/* C3: REA ev_0ec97c6a7a23c2807143087e87132b7fd3e110afdcfe39bd3e2930e9f8560e4c. */
int y540_encode_c3(uint32_t address, uint8_t report[Y540_REPORT_SIZE])
{
    if (!report || address > 0xffffffu) return 0;
    memset(report, 0, Y540_REPORT_SIZE);
    report[1] = 0xc3;
    report[2] = (uint8_t)address;
    report[3] = (uint8_t)(address >> 8);
    report[4] = (uint8_t)(address >> 16);
    report[5] = 0;
    report[6] = 4;
    return 1;
}

size_t y540_block_count(size_t size)
{
    return size / Y540_BLOCK_SIZE + (size % Y540_BLOCK_SIZE != 0);
}

int y540_plan_block(const uint8_t *data, size_t size, uint32_t start_address,
                     size_t index, y540_block *block)
{
    size_t offset, count, i;
    uint64_t address;
    if (!data || !block || index >= y540_block_count(size)) return 0;
    offset = index * Y540_BLOCK_SIZE;
    address = (uint64_t)start_address + offset;
    if (address > 0xffffffu || address + Y540_BLOCK_SIZE > 0x1000000u) return 0;
    count = size - offset;
    if (count > Y540_BLOCK_SIZE) count = Y540_BLOCK_SIZE;
    memset(block, 0, sizeof(*block));
    block->address = (uint32_t)address;
    block->source_offset = offset;
    block->source_length = count;
    block->chunk_count = count / Y540_CHUNK_SIZE + (count % Y540_CHUNK_SIZE != 0);
    memset(block->data, 0xff, sizeof(block->data));
    memcpy(block->data, data + offset, count);
    block->all_ff = 1;
    for (i = 0; i < Y540_BLOCK_SIZE; ++i) {
        if (block->data[i] != 0xff) block->all_ff = 0;
        block->staging_sum = (uint16_t)(block->staging_sum + block->data[i]);
    }
    return 1;
}
