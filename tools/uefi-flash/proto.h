/* ITE IT8176 (Legion Y540 keyboard) bootloader protocol.
 * Ported from the open-source updater at github.com/AMIRSRAD/Legion-Y540-Keyboard-Fix
 * (source/src/protocol.c, tools/linux-rescue/y540_linux_rescue.py). Platform independent:
 * the caller supplies feature-report I/O, sleep and logging through ite_link. */
#pragma once
#include "sha256.h"

typedef unsigned char u8;
#define IMAGE_SIZE 0xD800u
#define BLOCK 1024u
#define BLOCKS (IMAGE_SIZE / BLOCK) /* 54 */
#define CHUNK 57u
#define READ_CHUNK 56u
#define CMD_DELAY_MS 5u   /* SHFU.ini ALLHIDCOMMANDDELAY=5 */
#define ATTEMPTS 3u

typedef struct {
  void *ctx;
  int (*set)(void *ctx, const u8 payload[63]);   /* boot-mode feature report, no report ID; 1 = ok */
  int (*get)(void *ctx, u8 payload[63]);
  void (*sleep_ms)(void *ctx, unsigned ms);
  void (*log)(const char *s);
  void (*loghex)(unsigned long long v, int digits);
  void (*logdec)(unsigned long long v);
} ite_link;

static void p_memset(u8 *d, u8 v, unsigned n) { for (unsigned i = 0; i < n; i++) d[i] = v; }
static void p_memcpy(u8 *d, const u8 *s, unsigned n) { for (unsigned i = 0; i < n; i++) d[i] = s[i]; }
static int p_memcmp(const u8 *a, const u8 *b, unsigned n) { for (unsigned i = 0; i < n; i++) if (a[i] != b[i]) return 1; return 0; }

/* ---- known images (sha256) ---- */
typedef struct { const char *name; u8 sha[32]; int writable; } known_img;
#define H(...) {__VA_ARGS__}
static const known_img KNOWN[] = {
  {"stock 44", H(0x3a,0xfe,0xc1,0x31,0xc6,0xed,0x70,0xef,0xa0,0xa3,0xf4,0xb6,0x01,0xcb,0x79,0x90,0x11,0xa5,0x82,0x83,0x5d,0x37,0x1c,0x57,0xfe,0xf6,0x8a,0xf4,0x85,0x19,0xe3,0x59), 1},
  {"exp1", H(0x2b,0x34,0xb6,0xd5,0x9d,0xb8,0x44,0x38,0x31,0xa7,0xe0,0x38,0x7a,0xe6,0x59,0x70,0x30,0x7f,0x51,0x6e,0x81,0x6d,0xd4,0x81,0xf1,0xba,0x51,0x3d,0x3f,0x9d,0xe7,0x73), 0},
  {"exp2", H(0x82,0xc9,0x4f,0xd5,0x01,0x91,0xa3,0xad,0x8b,0x4f,0x97,0x60,0xeb,0xf5,0x88,0xb9,0x11,0xb1,0x93,0x45,0x0d,0xd7,0xed,0xee,0xec,0x06,0xba,0xcb,0xa3,0x38,0xe1,0xb8), 0},
  {"exp3", H(0xe0,0xa9,0x59,0xa6,0x3d,0xce,0xad,0xa1,0xf5,0xfa,0xd6,0x84,0x64,0x51,0x37,0x22,0x71,0xe2,0x66,0xec,0x17,0x6c,0xfd,0x25,0xbb,0x32,0x2a,0x69,0x19,0x9b,0x54,0x57), 0},
  {"exp4", H(0x27,0x43,0x8b,0xf4,0x39,0x76,0x69,0x26,0x42,0x00,0x47,0xb4,0xcb,0x65,0xfc,0xfc,0xa2,0x41,0x7c,0x7d,0x6a,0x36,0xf7,0x80,0x2d,0x82,0x4f,0x1f,0x7f,0x27,0xca,0x34), 0},
  {"exp5", H(0x39,0x31,0x58,0xdb,0x23,0x65,0xd3,0xc9,0x87,0x92,0x20,0x69,0xe7,0x96,0xe4,0x43,0x17,0x03,0x66,0x0f,0xb6,0x3f,0xb7,0xb5,0x36,0xe1,0xa3,0x02,0x59,0x6b,0x16,0x20), 0},
  {"exp6", H(0x46,0x52,0x10,0x59,0xf3,0xee,0x79,0x65,0x16,0xdc,0xcc,0xab,0x0f,0x7a,0xda,0x0b,0x29,0x05,0x7d,0x17,0xc1,0x83,0x13,0x11,0x66,0x45,0xcd,0xf9,0x85,0x99,0xf9,0x98), 0},
  {"exp7", H(0xfc,0x0d,0x01,0x41,0xe9,0x46,0x82,0x88,0xf1,0x1d,0x76,0x2f,0x69,0x82,0x00,0x22,0xe2,0x93,0x6f,0x7b,0x9c,0xcb,0xf4,0x2c,0xff,0x14,0x7e,0xa2,0x4e,0x8a,0x28,0xc0), 1},
  {"exp8", H(0x5d,0x03,0x12,0xa6,0x20,0x86,0x6d,0x20,0x9d,0x5a,0x77,0xd0,0xc2,0x64,0x7e,0x27,0xdf,0xf2,0x7e,0x95,0x4e,0xdd,0x67,0xe2,0x02,0xef,0xf1,0x72,0x27,0xde,0xa2,0xb8), 0},
  {"exp9", H(0xa7,0x29,0x7b,0xe9,0xc4,0x54,0xbf,0x8b,0x4b,0xe7,0x49,0x88,0x95,0xaf,0x3e,0x13,0x60,0x47,0x9c,0x4b,0xeb,0xe0,0x62,0x21,0xdc,0xef,0x55,0xdc,0xd0,0xdf,0x1f,0x68), 0},
};
#define N_KNOWN ((int)(sizeof(KNOWN) / sizeof(KNOWN[0])))
static int known_index(const u8 *img) {
  u8 d[32]; sha256(img, IMAGE_SIZE, d);
  for (int i = 0; i < N_KNOWN; i++) if (!p_memcmp(d, KNOWN[i].sha, 32)) return i;
  return -1;
}
static int needs_reset_deps(int idx) {   /* exp3/exp4/exp6/exp7/exp9 jump into the bootloader reset routine */
  return idx == 3 || idx == 4 || idx == 6 || idx == 7 || idx == 9;
}
static const u8 DEP_F12C[] = {0xe4,0xfd,0xfc,0xc3,0xed,0x9f,0xec,0x9e,0x50,0x13,0xe4,0xfb,0xe4,0x90,0x20,0x0b,0xf0,0x0b,0xeb,0xb4,0x42,0xf6,0x0d,0xbd,0x00,0x01,0x0c,0x80,0xe6,0x22};
static const u8 DEP_F455[] = {0x7f,0x05,0x7e,0x00,0x12,0xf1,0x2c,0x90,0x2f,0x50,0x74,0x08,0xf0,0x7f,0xe8,0x7e,0x03,0x12,0xf1,0x2c,0x90,0x10,0x58,0xe0,0x44,0x40,0xf0,0x53,0x8e,0x3f,0x75,0xd8,0x02,0x80,0xfe};

/* ---- transport with pacing and retries ---- */
static int b_send(ite_link *l, const u8 *p, unsigned n) {
  u8 buf[63]; p_memset(buf, 0, 63); p_memcpy(buf, p, n > 63 ? 63 : n);
  for (unsigned a = 0; a < ATTEMPTS; a++) {
    l->sleep_ms(l->ctx, CMD_DELAY_MS);
    if (l->set(l->ctx, buf)) return 1;
    l->sleep_ms(l->ctx, 100);
  }
  return 0;
}
static int b_recv(ite_link *l, u8 out[63]) {
  for (unsigned a = 0; a < ATTEMPTS; a++) {
    l->sleep_ms(l->ctx, CMD_DELAY_MS);
    p_memset(out, 0, 63);
    if (l->get(l->ctx, out)) return 1;
    l->sleep_ms(l->ctx, 100);
  }
  return 0;
}

static int chip_id(ite_link *l, unsigned *id) {
  u8 chip[2];
  for (u8 j = 0; j < 2; j++) {
    u8 p[63] = {7, j, 0x20, 0xF0, 3};
    if (!b_send(l, p, 5) || !b_recv(l, p)) return 0;
    if (p[1] != j || p[2] != 0x20 || p[3] != 0xF0 || p[4] != 3) return 0;
    chip[j] = p[5];
  }
  *id = (unsigned)chip[0] << 8 | chip[1];
  return 1;
}

static int read_flash(ite_link *l, unsigned addr, u8 *out, unsigned size, const char *label) {
  unsigned done = 0, next = 0x2000;
  while (done < size) {
    unsigned n = size - done; if (n > READ_CHUNK) n = READ_CHUNK;
    unsigned a = addr + done; u8 p[63]; int got = 0;
    for (unsigned t = 0; t < 4 && !got; t++) {
      if (t) { l->sleep_ms(l->ctx, 500 * t); l->log("  read stalled, re-requesting block\n"); }
      p_memset(p, 0, 63); p[0] = 0xD1; p[1] = (u8)a; p[2] = (u8)(a >> 8); p[3] = (u8)(a >> 16); p[4] = (u8)n;
      got = b_send(l, p, n + 5) && b_recv(l, p);
    }
    if (!got) { l->log("  bootloader stopped answering at 0x"); l->loghex(a, 4); l->log("\n"); return 0; }
    p_memcpy(out + done, p + 5, n);
    done += n;
    if (label && done >= next) { l->log("  "); l->log(label); l->log(" "); l->logdec(done); l->log("/"); l->logdec(size); l->log("\n"); next += 0x2000; }
  }
  return 1;
}

static int write_block(ite_link *l, const u8 *fw, unsigned index) {
  const u8 *d = fw + index * BLOCK;
  unsigned sum = 0, allff = 1;
  for (unsigned i = 0; i < BLOCK; i++) { sum += d[i]; if (d[i] != 0xFF) allff = 0; }
  if (allff) return 1;
  u8 p[63];
  p_memset(p, 0, 63); p[0] = 0xC0;
  if (!b_send(l, p, 1)) return 0;
  for (unsigned i = 0; i < BLOCK; i += CHUNK) {
    unsigned n = BLOCK - i; if (n > CHUNK) n = CHUNK;
    p_memset(p, 0, 63); p[0] = 0xC1; p[1] = (u8)i; p[2] = (u8)(i >> 8); p[3] = (u8)n;
    p_memcpy(p + 4, d + i, n);
    if (!b_send(l, p, n + 4)) return 0;
  }
  p_memset(p, 0, 63); p[0] = 0xD0;
  if (!b_send(l, p, 1) || !b_recv(l, p)) return 0;
  if ((unsigned)(p[1] | p[2] << 8) != (sum & 0xFFFF)) {
    l->log("  device staging checksum differs at block "); l->logdec(index); l->log("\n"); return 0;
  }
  unsigned off = index * BLOCK;
  p_memset(p, 0, 63); p[0] = 0xC3; p[1] = (u8)off; p[2] = (u8)(off >> 8); p[3] = (u8)(off >> 16); p[4] = 0; p[5] = 4;
  if (!b_send(l, p, 6)) return 0;
  l->sleep_ms(l->ctx, 5);
  return 1;
}

static int interrupted_write_of(const u8 *fw, const u8 *flash) {
  unsigned written = 0;
  for (unsigned i = 0; i < BLOCK; i++) if (flash[i] != 0xFF) return 0;
  for (unsigned o = BLOCK; o < IMAGE_SIZE; o += BLOCK) {
    int same = !p_memcmp(flash + o, fw + o, BLOCK), ff = 1, fwff = 1;
    for (unsigned i = 0; i < BLOCK; i++) { if (flash[o + i] != 0xFF) ff = 0; if (fw[o + i] != 0xFF) fwff = 0; }
    if (same) { if (!fwff) written++; }
    else if (!ff) return 0;
  }
  return written > 0;
}
static int all_blank(const u8 *flash) {
  for (unsigned i = 0; i < IMAGE_SIZE; i++) if (flash[i] != 0xFF) return 0;
  return 1;
}

/* Result codes */
#define R_OK_WRITTEN 1
#define R_OK_BACKUP_ONLY 2
#define R_FAIL_NO_ERASE -1     /* stopped before erase: flash untouched */
#define R_FAIL_AFTER_ERASE -2  /* erase happened, write/verify failed: left in update mode */

/* target == 0: backup only (then C4 reset). Otherwise target must be a known writable image.
 * save_backup(ctx, data) must return 1 only when the backup is safely stored. */
static int ite_program(ite_link *l, const u8 *target, u8 *scratch_a, u8 *scratch_b,
                       int (*save_backup)(void *ctx, const u8 *data, int known), void *save_ctx,
                       int allow_auto_resume_only) {
  unsigned id = 0; int ok = 0;
  for (int r = 0; r < 12 && !ok; r++) {
    if (r) { l->log("  bootloader not ready, retry "); l->logdec(r + 1); l->log("/12\n"); l->sleep_ms(l->ctx, 500); }
    ok = chip_id(l, &id);
  }
  if (!ok) { l->log("STOP: bootloader did not answer the chip-ID request. Nothing erased.\n"); return R_FAIL_NO_ERASE; }
  l->log("Bootloader chip ID: "); l->loghex(id, 4); l->log("\n");
  if (id != 0x8171 && id != 0x8176) { l->log("STOP: chip ID is not 8171/8176. Nothing erased.\n"); return R_FAIL_NO_ERASE; }

  int tidx = -1;
  if (target) {
    tidx = known_index(target);
    if (tidx < 0 || !KNOWN[tidx].writable) { l->log("STOP: target image is not a known writable image.\n"); return R_FAIL_NO_ERASE; }
    l->log("Target image: "); l->log(KNOWN[tidx].name); l->log("\n");
  }
  if (target && needs_reset_deps(tidx)) {
    u8 tmp[64];
    if (!read_flash(l, 0xF12C, tmp, sizeof(DEP_F12C), 0) || p_memcmp(tmp, DEP_F12C, sizeof(DEP_F12C)) ||
        !read_flash(l, 0xF455, tmp, sizeof(DEP_F455), 0) || p_memcmp(tmp, DEP_F455, sizeof(DEP_F455))) {
      l->log("STOP: bootloader reset routine differs from the tested chip. Nothing erased.\n"); return R_FAIL_NO_ERASE;
    }
    l->log("Bootloader reset routine matches the tested chip.\n");
  }

  l->log("Reading current firmware (backup)...\n");
  if (!read_flash(l, 0, scratch_a, IMAGE_SIZE, "backup read")) { l->log("STOP: backup read failed. Nothing erased.\n"); return R_FAIL_NO_ERASE; }
  int cidx = known_index(scratch_a), known = cidx >= 0;
  int resume = target && !known && (interrupted_write_of(target, scratch_a) || all_blank(scratch_a));
  if (known) { l->log("Current firmware is exactly: "); l->log(KNOWN[cidx].name); l->log("\n"); }
  else if (resume) l->log("Current firmware is blank or an interrupted write of the target (resume).\n");
  else {
    l->log("Current firmware is NOT a known image. Confirming with a second read...\n");
    if (!read_flash(l, 0, scratch_b, IMAGE_SIZE, "confirm read") || p_memcmp(scratch_a, scratch_b, IMAGE_SIZE)) {
      l->log("STOP: the two backup reads differ. Nothing erased.\n"); return R_FAIL_NO_ERASE;
    }
  }
  if (!save_backup(save_ctx, scratch_a, known)) { l->log("STOP: could not save the backup file. Nothing erased.\n"); return R_FAIL_NO_ERASE; }

  if (!target || (allow_auto_resume_only && !resume)) {
    u8 c4 = 0xC4;
    l->log(target ? "Firmware is complete; no write needed. Sending reset (C4).\n" : "Backup only: sending reset (C4), no erase.\n");
    b_send(l, &c4, 1);
    return R_OK_BACKUP_ONLY;
  }
  if (!known && !resume) {
    l->log("STOP: unknown current firmware; refusing to erase. Backup saved for analysis.\n");
    u8 c4 = 0xC4; b_send(l, &c4, 1);
    return R_FAIL_NO_ERASE;
  }

  for (int attempt = 0; attempt < 2; attempt++) {   /* PROGRAMFAILRETRY=1 */
    l->log("ERASE (attempt "); l->logdec(attempt + 1); l->log(") - do not power off from here on\n");
    u8 e[6] = {0xC2, 0, 0, 0, (u8)BLOCKS, (u8)(BLOCKS >> 8)};
    if (!b_send(l, e, 6)) { l->log("  erase command failed\n"); continue; }
    l->sleep_ms(l->ctx, 5);
    int wok = 1;
    for (unsigned i = 1; i <= BLOCKS && wok; i++) {
      wok = write_block(l, target, i == BLOCKS ? 0 : i);   /* block 0 last */
      if (i % 9 == 0 || i == BLOCKS) { l->log("  write "); l->logdec(i); l->log("/"); l->logdec(BLOCKS); l->log("\n"); }
    }
    if (!wok) { l->log("  write failed\n"); continue; }
    l->log("Verifying (full readback)...\n");
    if (read_flash(l, 0, scratch_b, IMAGE_SIZE, "readback") && !p_memcmp(scratch_b, target, IMAGE_SIZE)) {
      u8 c4 = 0xC4; b_send(l, &c4, 1);
      l->log("SUCCESS: readback matches "); l->log(KNOWN[tidx].name); l->log("; reset sent.\n");
      return R_OK_WRITTEN;
    }
    l->log("  readback differs from target\n");
  }
  l->log("FAILED after erase. Keyboard stays in update mode; run this program again to retry.\n");
  return R_FAIL_AFTER_ERASE;
}
