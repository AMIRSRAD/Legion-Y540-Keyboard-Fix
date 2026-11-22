/* Host-side test of proto.h against an in-memory model of the ITE bootloader
 * (port of FakeBoot from the author's y540_linux_rescue.py --selftest). */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "proto.h"
#include "fw_images.h"

typedef struct {
  u8 flash[IMAGE_SIZE]; u8 upper[0x2800]; u8 stage[BLOCK]; u8 reply[63];
  unsigned order[BLOCKS * 2]; int norder; int reset; int erases; int bad_c3;
  int fail_every;   /* make every Nth get fail once (stall simulation) */
  int calls;
} fake;

static int f_set(void *c, const u8 d[63]) {
  fake *f = c; u8 cmd = d[0];
  if (cmd == 7) { u8 j = d[1]; memset(f->reply, 0, 63); u8 r[6] = {7, j, 0x20, 0xF0, 3, j ? 0x71 : 0x81}; memcpy(f->reply, r, 6); }
  else if (cmd == 0xD1) {
    unsigned a = d[1] | d[2] << 8 | d[3] << 16, n = d[4];
    memset(f->reply, 0, 63); memcpy(f->reply, d, 5);
    for (unsigned i = 0; i < n; i++) { unsigned x = a + i; f->reply[5 + i] = x < IMAGE_SIZE ? f->flash[x] : f->upper[x - IMAGE_SIZE]; }
  }
  else if (cmd == 0xC2) { memset(f->flash, 0xFF, IMAGE_SIZE); f->erases++; }
  else if (cmd == 0xC0) memset(f->stage, 0xFF, BLOCK);
  else if (cmd == 0xC1) { unsigned o = d[1] | d[2] << 8, n = d[3]; memcpy(f->stage + o, d + 4, n); }
  else if (cmd == 0xD0) { unsigned s = 0; for (unsigned i = 0; i < BLOCK; i++) s += f->stage[i]; memset(f->reply, 0, 63); f->reply[0] = 0xD0; f->reply[1] = s & 255; f->reply[2] = (s >> 8) & 255; }
  else if (cmd == 0xC3) {
    unsigned a = d[1] | d[2] << 8 | d[3] << 16;
    for (unsigned i = 0; i < BLOCK; i++) if (f->flash[a + i] != 0xFF) f->bad_c3 = 1;
    memcpy(f->flash + a, f->stage, BLOCK); f->order[f->norder++] = a;
  }
  else if (cmd == 0xC4) f->reset = 1;
  return 1;
}
static int f_get(void *c, u8 p[63]) {
  fake *f = c; f->calls++;
  if (f->fail_every && f->calls % f->fail_every == 0) return 0;
  memcpy(p, f->reply, 63); return 1;
}
static void f_sleep(void *c, unsigned ms) { (void)c; (void)ms; }
static void lg(const char *s) { fputs(s, stdout); }
static void lh(unsigned long long v, int d) { printf("%0*llX", d, v); }
static void ld(unsigned long long v) { printf("%llu", v); }
static int saved;
static int save_ok(void *c, const u8 *d, int known) { (void)c; (void)d; (void)known; saved++; return 1; }
static int save_fail(void *c, const u8 *d, int known) { (void)c; (void)d; (void)known; return 0; }

static fake *mk(const u8 *start) {
  fake *f = calloc(1, sizeof(fake));
  memcpy(f->flash, start, IMAGE_SIZE); memset(f->upper, 0xFF, sizeof(f->upper));
  memcpy(f->upper + 0xF12C - IMAGE_SIZE, DEP_F12C, sizeof(DEP_F12C));
  memcpy(f->upper + 0xF455 - IMAGE_SIZE, DEP_F455, sizeof(DEP_F455));
  return f;
}
#define CHECK(x) do { if (!(x)) { printf("\nFAIL line %d: %s\n", __LINE__, #x); exit(1); } } while (0)
static u8 A[IMAGE_SIZE], B[IMAGE_SIZE];

int main(void) {
  ite_link l = {0, f_set, f_get, f_sleep, lg, lh, ld};
  CHECK(known_index(FW_EXP7) == 7 && known_index(FW_STOCK44) == 0);

  puts("== 1. stock 44 -> exp7");
  fake *f = mk(FW_STOCK44); l.ctx = f; saved = 0;
  CHECK(ite_program(&l, FW_EXP7, A, B, save_ok, 0, 0) == R_OK_WRITTEN);
  CHECK(!memcmp(f->flash, FW_EXP7, IMAGE_SIZE) && f->reset && f->erases == 1 && !f->bad_c3 && saved == 1);
  CHECK(f->order[f->norder - 1] == 0 && f->order[0] == BLOCK);

  puts("== 2. backup only");
  f = mk(FW_STOCK44); l.ctx = f; saved = 0;
  CHECK(ite_program(&l, 0, A, B, save_ok, 0, 0) == R_OK_BACKUP_ONLY);
  CHECK(!f->erases && f->reset && saved == 1 && !memcmp(f->flash, FW_STOCK44, IMAGE_SIZE));

  puts("== 3. bootloader dependency mismatch");
  f = mk(FW_STOCK44); f->upper[0xF455 - IMAGE_SIZE] ^= 1; l.ctx = f;
  CHECK(ite_program(&l, FW_EXP7, A, B, save_ok, 0, 0) == R_FAIL_NO_ERASE);
  CHECK(!f->erases && !f->reset && !memcmp(f->flash, FW_STOCK44, IMAGE_SIZE));

  puts("== 4. unknown current firmware -> refuse erase");
  static u8 odd[IMAGE_SIZE]; memcpy(odd, FW_STOCK44, IMAGE_SIZE); odd[0x4C7B] ^= 0x55;
  f = mk(odd); l.ctx = f;
  CHECK(ite_program(&l, FW_EXP7, A, B, save_ok, 0, 0) == R_FAIL_NO_ERASE);
  CHECK(!f->erases);

  puts("== 5. interrupted write -> resume");
  static u8 part[IMAGE_SIZE]; memset(part, 0xFF, IMAGE_SIZE); memcpy(part + 5 * BLOCK, FW_EXP7 + 5 * BLOCK, 10 * BLOCK);
  f = mk(part); l.ctx = f;
  CHECK(ite_program(&l, FW_EXP7, A, B, save_ok, 0, 1) == R_OK_WRITTEN);
  CHECK(!memcmp(f->flash, FW_EXP7, IMAGE_SIZE) && f->reset);

  puts("== 6. blank -> resume; complete known image in auto mode -> just reset");
  f = mk(B); memset(f->flash, 0xFF, IMAGE_SIZE); l.ctx = f;
  CHECK(ite_program(&l, FW_EXP7, A, B, save_ok, 0, 1) == R_OK_WRITTEN);
  f = mk(FW_STOCK44); l.ctx = f;
  CHECK(ite_program(&l, FW_EXP7, A, B, save_ok, 0, 1) == R_OK_BACKUP_ONLY && !f->erases);

  puts("== 7. backup cannot be saved -> no erase");
  f = mk(FW_STOCK44); l.ctx = f;
  CHECK(ite_program(&l, FW_EXP7, A, B, save_fail, 0, 0) == R_FAIL_NO_ERASE && !f->erases);

  puts("== 8. intermittent stalls (every 7th GET fails) still succeed");
  f = mk(FW_STOCK44); f->fail_every = 7; l.ctx = f;
  CHECK(ite_program(&l, FW_EXP7, A, B, save_ok, 0, 0) == R_OK_WRITTEN && !memcmp(f->flash, FW_EXP7, IMAGE_SIZE));

  puts("\nALL HOST TESTS PASSED");
  return 0;
}
