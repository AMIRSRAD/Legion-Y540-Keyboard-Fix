#ifndef Y540_SHA256_H
#define Y540_SHA256_H
#include <stddef.h>
#include <stdint.h>
/* Portable SHA-256 (FIPS 180-4). Used only to recognise the exact original
 * firmware-44 image in a bootloader read. */
void y540_sha256(const uint8_t *data, size_t size, uint8_t out[32]);
#endif
