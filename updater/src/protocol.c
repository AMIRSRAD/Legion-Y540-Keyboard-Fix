#define WIN32_LEAN_AND_MEAN
#include "protocol.h"
#include "sha256.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>

static int fail(y540_hid_error *e, const char *s) {
  if (e) {
    e->code = 1;
    snprintf(e->message, sizeof(e->message), "%s", s);
  }
  return 0;
}
static void delay(y540_hid_transport *t, uint32_t n) {
  if (t->sleep)
    t->sleep(t->context, n);
}
static void note(y540_progress_fn p, void *c, const char *s, size_t i,
                 size_t n) {
  if (p)
    p(c, s, i, n);
}
static int number(const y540_config *c, const char *s, const char *k, int base,
                  uint32_t def, uint32_t *v, y540_hid_error *e) {
  if (y540_config_number(c, s, k, base, def, v) < 0) {
    return fail(e, "Invalid numeric setting");
  }
  return 1;
}
static int send(y540_hid_transport *t, const uint8_t *p, size_t n,
                y540_hid_error *e) {
  return y540_hid_send(t, p, n, e);
}
/* Known-good images (all from this package): original 44, and the no-sleep experiment 1.
 * A complete bootloader read that equals one of them exactly needs no second confirming
 * read: a corrupted read cannot hash to a known image. */
#define KNOWN_IMAGES 2
static const uint8_t KNOWN_IMAGE_SHA256[KNOWN_IMAGES][32] = {
    {0x3a, 0xfe, 0xc1, 0x31, 0xc6, 0xed, 0x70, 0xef, 0xa0, 0xa3, 0xf4, 0xb6, 0x01, 0xcb, 0x79, 0x90, 0x11, 0xa5, 0x82, 0x83, 0x5d, 0x37, 0x1c, 0x57, 0xfe, 0xf6, 0x8a, 0xf4, 0x85, 0x19, 0xe3, 0x59},
    {0x2b, 0x34, 0xb6, 0xd5, 0x9d, 0xb8, 0x44, 0x38, 0x31, 0xa7, 0xe0, 0x38, 0x7a, 0xe6, 0x59, 0x70, 0x30, 0x7f, 0x51, 0x6e, 0x81, 0x6d, 0xd4, 0x81, 0xf1, 0xba, 0x51, 0x3d, 0x3f, 0x9d, 0xe7, 0x73}};
static int read_flash(y540_hid_transport *t, uint32_t addr, uint8_t *out,
                      size_t size, y540_progress_fn progress, void *ctx,
                      y540_hid_error *e) {
  size_t done = 0, next_note = 0x2000;
  while (done < size) {
    uint8_t p[63] = {0};
    size_t n = size - done;
    if (n > 56)
      n = 56;
    uint32_t a = addr + (uint32_t)done;
    p[0] = 0xd1;
    p[1] = (uint8_t)a;
    p[2] = (uint8_t)(a >> 8);
    p[3] = (uint8_t)(a >> 16);
    p[4] = (uint8_t)n;
    if (!send(t, p, n + 5, e) || !y540_hid_receive(t, p, n + 5, e)) {
      char previous[96];
      snprintf(previous, sizeof(previous), "%.90s", e->message);
      snprintf(e->message, sizeof(e->message),
               "%s at flash 0x%04X (%u/%u bytes read): bootloader stopped answering; "
               "hold power ~10 s to restore the keyboard",
               previous, (unsigned)a, (unsigned)done, (unsigned)size);
      return 0;
    }
    /* 0x40AA50 copies payload[5..]; header echo semantics are unestablished.
     * Keep API/bounds checks and validate the complete returned image instead. */
    memcpy(out + done, p + 5, n);
    done += n;
    if (done >= next_note) {
      note(progress, ctx, "Flash read progress", done, size);
      next_note += 0x2000;
    }
  }
  return 1;
}
static int erase(y540_hid_transport *t, uint32_t addr, uint16_t blocks,
                 y540_hid_error *e) {
  uint8_t p[6] = {0xc2,
                  (uint8_t)addr,
                  (uint8_t)(addr >> 8),
                  (uint8_t)(addr >> 16),
                  (uint8_t)blocks,
                  (uint8_t)(blocks >> 8)};
  if (!y540_hid_validate_current(t, e) || !send(t, p, 6, e)) {
    return 0;
  }
  delay(t, 5);
  return 1;
}
static int reset(y540_hid_transport *t, y540_hid_error *e) {
  uint8_t p = 0xc4;
  return y540_hid_validate_current(t, e) && send(t, &p, 1, e);
}
static int write_block(y540_hid_transport *t, const y540_block *b,
                       uint32_t write_delay, y540_hid_error *e) {
  uint8_t p[64] = {0};
  size_t i;
  if (b->all_ff) {
    return 1;
  }
  p[0] = 0xc0;
  if (!send(t, p, 1, e)) {
    return 0;
  }
  for (i = 0; i < b->source_length;) {
    size_t n = b->source_length - i;
    if (n > 57)
      n = 57;
    if (!y540_encode_c1((uint16_t)i, b->data + i, n, p)) {
      return fail(e, "C1 encoding failed");
    }
    if (!send(t, p + 1, n + 4, e)) {
      return 0;
    }
    delay(t, write_delay);
    i += n;
  }
  memset(p, 0, sizeof(p));
  p[0] = 0xd0;
  if (!send(t, p, 1, e) || !y540_hid_receive(t, p, 3, e)) {
    return 0;
  }
  if (((uint16_t)p[1] | ((uint16_t)p[2] << 8)) != b->staging_sum) {
    return fail(e, "Device staging checksum differs from source block");
  }
  if (!y540_encode_c3(b->address, p)) {
    return fail(e, "C3 encoding failed");
  }
  if (!y540_hid_validate_current(t, e) || !send(t, p + 1, 6, e)) {
    return 0;
  }
  delay(t, 5);
  return 1;
}
int y540_check_boot_chip(y540_hid_transport *t, uint16_t expected,
                         y540_hid_error *e) {
  if (expected != 0x8171 && expected != 0x8176) {
    return fail(e, "Unsupported boot chip profile; chip check cannot be disabled");
  }
  uint8_t chip[2] = {0};
  unsigned j;
  for (j = 0; j < 2; j++) {
    uint8_t p[8] = {7, (uint8_t)j, 0x20, 0xf0, 3, 0, 0, 0};
    if (!send(t, p, 5, e) || !y540_hid_receive(t, p, 8, e)) {
      return 0;
    }
    if (p[1] != j || p[2] != 0x20 || p[3] != 0xf0 || p[4] != 3) {
      return fail(e, "Boot chip response address mismatch");
    }
    chip[j] = p[5];
  }
  uint16_t got = (uint16_t)((chip[0] << 8) | chip[1]);
  if (got == expected) {
    return 1;
  }
  if ((expected == 0x8171 || expected == 0x8176) &&
      (got == 0x8171 || got == 0x8176)) {
    return 1;
  }
  return fail(e, "Boot chip ID does not match profile");
}
static int transient_open_error(uint32_t code) {
  return code == ERROR_NOT_FOUND || code == ERROR_FILE_NOT_FOUND ||
         code == ERROR_PATH_NOT_FOUND || code == ERROR_DEVICE_NOT_CONNECTED;
}
int y540_wait_boot_device(y540_boot_find_fn find, void *find_context,
                          y540_hid_transport *t, y540_hid_sleep_fn sleep,
                          y540_clock_fn clock, void *time_context,
                          uint32_t poll_ms, uint32_t budget_ms,
                          y540_progress_fn progress, void *progress_context,
                          y540_hid_error *e) {
  y540_hid_error local = {0};
  if (!e) e = &local;
  if (!find || !t || !sleep || !clock || !poll_ms || !budget_ms)
    return fail(e, "Boot discovery requires finder, transport, clock and positive timings");
  uint64_t start = clock(time_context);
  unsigned polls = 0;
  for (;;) {
    ++polls;
    if (find(find_context, t, e)) {
      uint64_t elapsed = clock(time_context) - start;
      note(progress, progress_context,
           "Boot-mode interface opened (ms since handoff, polls)",
           (size_t)elapsed, polls);
      return 1;
    }
    if (!transient_open_error(e->code)) return 0;
    if (clock(time_context) - start >= budget_ms) {
      fail(e, "Keyboard did not reappear on the same USB port in boot mode");
      e->code = ERROR_NOT_FOUND;
      return 0;
    }
    sleep(time_context, poll_ms);
  }
}
int y540_wait_boot_chip(y540_hid_transport *t, uint16_t expected,
                       y540_boot_reopen_fn reopen, void *reopen_ctx,
                       y540_progress_fn progress, void *ctx,
                       y540_hid_error *e) {
  y540_hid_error local = {0};
  if (!e) e = &local;
  if (!t || !reopen) return fail(e, "Boot readiness requires transport and reopen callback");
  for (unsigned round = 0; round < 12; ++round) {
    if (round) {
      Sleep(500);
      if (!reopen(reopen_ctx, t, e)) {
        note(progress, ctx, "Boot readiness reopen failed", e->code, round + 1);
        if (e->code == ERROR_NOT_FOUND) continue;
        return 0;
      }
    }
    note(progress, ctx, "Check bootloader readiness (no erase)", round + 1, 12);
    if (y540_check_boot_chip(t, expected, e)) {
      note(progress, ctx, "Bootloader chip response validated", round + 1, 12);
      return 1;
    }
    note(progress, ctx, "Boot readiness chip request failed", e->code, round + 1);
    /* Observed code31 is generic, not proof of timing. Retry it cautiously;
     * do not reinterpret chip/address mismatches or access errors as readiness. */
    if (e->code != ERROR_GEN_FAILURE) return 0;
  }
  char previous[256];
  snprintf(previous, sizeof(previous), "%s", e->message);
  snprintf(e->message, sizeof(e->message),
           "Bootloader did not become responsive within 12 checks; no erase/write. "
           "Enumerated-but-silent = suspend/resume dead state; hold power 10 s: %.60s",
           previous);
  return 0;
}

typedef struct {
  y540_hid_selector selector;
  uint32_t delay_ms;
} boot_reopen_context;
static int reopen_boot(void *context, y540_hid_transport *t, y540_hid_error *e) {
  boot_reopen_context *r = context;
  y540_hid_close(t);
  return y540_hid_open(t, &r->selector, r->delay_ms, e);
}

typedef struct {
  const y540_hid_selector *selector;
  uint32_t delay_ms;
} boot_find_context;
static int find_boot(void *context, y540_hid_transport *t, y540_hid_error *e) {
  boot_find_context *f = context;
  return y540_hid_open(t, f->selector, f->delay_ms, e);
}
static void real_sleep(void *context, uint32_t milliseconds) {
  (void)context;
  Sleep(milliseconds);
}
static uint64_t real_clock(void *context) {
  (void)context;
  return GetTickCount64();
}

static int custom_mode(y540_hid_transport *t, int enable, y540_hid_error *e) {
  const uint8_t key[15] = "ITE Tech. Inc.";
  uint8_t got[15] = {0};
  unsigned attempt;
  /* HidCustomCmdInit toggles with the key at most twice until echo/no echo
   * matches the requested mode. It does not change report ID to zero. */
  for (attempt = 0; attempt < 2; ++attempt) {
    if (!y540_hid_send_report(t, 0x5a, key, sizeof(key), e)) return 0;
    delay(t, 100);
    if (!y540_hid_receive_report(t, 0x5a, got, sizeof(got), e)) return 0;
    delay(t, 100);
    if ((!memcmp(key, got, sizeof(key))) == !!enable) return 1;
  }
  return fail(e, enable ? "Custom HID handshake did not echo ITE key" :
                         "Custom HID mode cleanup could not be confirmed");
}
int y540_exit_custom_mode(y540_hid_transport *t, y540_hid_error *e) {
  return custom_mode(t, 0, e);
}
static void cleanup_mode(y540_hid_transport *t, y540_hid_error *e) {
  y540_hid_error original = {0}, cleanup = {0};
  if (e) original = *e;
  if (!y540_exit_custom_mode(t, &cleanup)) {
    if (e) {
      *e = original;
      snprintf(e->message, sizeof(e->message), "%.135s; mode cleanup failed: %.85s",
               original.message, cleanup.message);
    }
  } else if (e) {
    *e = original;
  }
}
int y540_enter_boot(y540_hid_transport *t, y540_hid_error *e) {
  uint8_t boot[2] = {9, 0};
  y540_hid_error local = {0};
  if (!e) e = &local;
  if (!custom_mode(t, 1, e)) {
    cleanup_mode(t, e);
    return 0;
  }
  delay(t, 100);
  if (!y540_hid_send_report(t, 0x5a, boot, sizeof(boot), e)) {
    cleanup_mode(t, e);
    return 0;
  }
  delay(t, 1000);
  return 1;
}
static int preflight(const uint8_t *fw, size_t size, const y540_config *c,
                     y540_hid_error *e) {
  y540_checksum_result r;
  char msg[256];
  uint32_t start, mode, docking;
  if (!y540_validate_firmware(fw, size, c, &r, msg, sizeof(msg))) {
    return fail(e, msg);
  }
  if (!number(c, "NEWVERSION", "UPDATESTARTADDRESS", 16, 0, &start, e) ||
      !number(c, "NEWVERSION", "UPDATEONLYPARAMETER", 10, 0, &mode, e) ||
      !number(c, "DEVICE", "DOCKINGBURN", 10, 0, &docking, e)) {
    return 0;
  }
  uint32_t same, pidcheck, report, retry, wait, wd, oem, page, usage, chip;
  struct numeric_option {
    const char *section;
    const char *key;
    int base;
    uint32_t fallback, max;
  } options[] = {{"DEVICE", "NEEDERASE", 10, 1, 1},
                 {"OPTION", "NOCHECKIVT", 10, 0, 1},
                 {"OPTION", "PROGRAMFAILERASESKIPFIRST1K", 10, 0, 1},
                 {"OPTION", "PROGRAMFAILERASETHENRESET", 10, 0, 1},
                 {"OPTION", "ALLHIDCOMMANDDELAY", 10, 5, 60000},
                 {"DEVICE", "MAININDEX", 10, 0, 0},
                 {"NEWVERSION", "MAINDEVICEUPID", 16, 0xff89, 0xffff},
                 {"NEWVERSION", "MAINDEVICEUID", 16, 0x0010, 0xffff}};
  for (size_t oi = 0; oi < sizeof(options) / sizeof(options[0]); oi++) {
    uint32_t value;
    if (!number(c, options[oi].section, options[oi].key, options[oi].base,
                options[oi].fallback, &value, e)) {
      return 0;
    }
    if (value > options[oi].max) {
      return fail(e, "Unsupported profile option range");
    }
  }

  if (!number(c, "CHECKVERSION", "DONOTUPDATETHESAMEVERSION", 10, 0, &same,
              e) ||
      !number(c, "OPTION", "NOCHECKPID", 10, 0, &pidcheck, e) ||
      !number(c, "MAIN", "REPORTID", 10, 0x5a, &report, e) ||
      !number(c, "DEVICE", "PROGRAMFAILRETRY", 10, 1, &retry, e) ||
      !number(c, "DELAY", "MSEC", 10, 6000, &wait, e) ||
      !number(c, "OPTION", "WRITEFLASHDATADELAY", 10, 0, &wd, e) ||
      !number(c, "OPTION", "OEMVEROFFSET", 16, 0x3100, &oem, e) ||
      !number(c, "NEWVERSION", "BOOTDEVICEUPID", 16, 0xff89, &page, e) ||
      !number(c, "NEWVERSION", "BOOTDEVICEUID", 16, 0x00db, &usage, e) ||
      !number(c, "NEWVERSION", "BOOTDEVICECHIPID", 16, 0x8171, &chip, e)) {
    return 0;
  }
  if (same || pidcheck || report != 0x5a || retry > 100 || wait > 120000 ||
      wd > 60000 || oem > size - 32 || page > 0xffff || usage > 0xffff ||
      (chip != 0x8171 && chip != 0x8176)) {
    return fail(e, "Unsupported or invalid update profile option");
  }
  if (start || mode || docking || size != 54u * 1024u) {
    return fail(e, "Only the supplied 54 KiB full-image Y540 profile at "
                   "address zero is implemented");
  }
  return 1;
}
static int boot_program(y540_hid_transport *t, const uint8_t *fw, size_t size,
                      const y540_config *c, HANDLE backup, y540_progress_fn progress,
                      void *ctx, y540_hid_error *e) {
  uint32_t need_erase, retries, skip_ivt, write_delay,
      oem;
  size_t blocks = y540_block_count(size), i;
  unsigned attempt;
  uint8_t *readback, *second;
  int ok = 0;
  if (!preflight(fw, size, c, e)) {
    return 0;
  }
  if (!number(c, "DEVICE", "NEEDERASE", 10, 1, &need_erase, e) ||
      !number(c, "DEVICE", "PROGRAMFAILRETRY", 10, 1, &retries, e) ||
      !number(c, "OPTION", "NOCHECKIVT", 10, 0, &skip_ivt, e) ||
      !number(c, "OPTION", "WRITEFLASHDATADELAY", 10, 0, &write_delay, e) ||
      !number(c, "OPTION", "OEMVEROFFSET", 16, 0x3100, &oem, e)) {
    return 0;
  }
  if (retries > 100 || oem > size - 32 || write_delay > 60000) {
    return fail(e, "Profile retry/delay/version range invalid");
  }
  readback = malloc(size * 2);
  if (!readback) {
    return fail(e, "Cannot allocate readback buffer");
  }
  second = readback + size;
  note(progress, ctx, "Read complete update region for backup", 0, size);
  if (!read_flash(t, 0, readback, size, progress, ctx, e))
    goto done;
  {
    uint8_t digest[32];
    y540_sha256(readback, size, digest);
    int known = 0;
    for (int ki = 0; ki < KNOWN_IMAGES; ++ki)
      if (!memcmp(digest, KNOWN_IMAGE_SHA256[ki], sizeof(digest))) known = 1;
    if (size == 54u * 1024u && known) {
      /* fix6: shorter exposure. The device still holds the exact original
       * firmware 44 (SHA-256 matches a packaged image), so the saved backup is that known
       * file; a second read would only add ~30 s of bootloader traffic. */
      note(progress, ctx, "Read equals a known image (original 44 or no-sleep exp1) exactly; second read not needed", size, size);
    } else {
      note(progress, ctx, "Confirm backup with second independent read", 0, size);
      if (!read_flash(t, 0, second, size, progress, ctx, e))
        goto done;
      if (memcmp(readback, second, size)) {
        fail(e, "Current firmware changed between backup reads; no erase performed");
        goto done;
      }
    }
  }
  DWORD written = 0;
  if (!WriteFile(backup, readback, (DWORD)size, &written, NULL) ||
      written != size || !FlushFileBuffers(backup)) {
    fail(e, "Unable to save and flush firmware backup; no erase performed");
    goto done;
  }
  note(progress, ctx, "Firmware backup saved and flushed", size, size);
  if (!skip_ivt) {
    for (i = 4; i < 2048; i++) {
      if (i == 0x87 || i == 0x8d || i == 0x1d || i == 0x1e || i == 0x1f)
        continue;
      if (fw[i] != readback[i]) {
        fail(e,
             "Existing interrupt-vector region differs from selected firmware");
        goto done;
      }
    }
  }
  for (attempt = 0; attempt <= retries; attempt++) {
    note(progress, ctx, "Erase image region", attempt, retries + 1);
    if (need_erase && !erase(t, 0, (uint16_t)blocks, e))
      goto done;
    /* Original writes all blocks except first, then writes first last. */
    for (i = 1; i <= blocks; i++) {
      size_t index = i == blocks ? 0 : i;
      y540_block b;
      if (!y540_plan_block(fw, size, 0, index, &b) ||
          !write_block(t, &b, write_delay, e))
        goto done;
      note(progress, ctx, "Write firmware", i, blocks);
    }
    note(progress, ctx, "Read back and compare", 0, size);
    if (!read_flash(t, 0, readback, size, progress, ctx, e))
      goto done;
    if (!memcmp(fw, readback, size)) {
      ok = 1;
      break;
    }
    /* Keep the failed image readable in boot mode. A retry, if configured,
     * starts with exactly one erase; never erase after final failed verify. */
    fail(e, "Flash readback differs from selected firmware");
  }
  if (ok) {
    note(progress, ctx, "Reset verified firmware", blocks, blocks);
    ok = reset(t, e);
  } else {
    fail(e, "Flash readback differs after all attempts; left in boot mode, no reset or final erase");
  }
done:
  free(readback);
  return ok;
}
static HANDLE backup_create(const wchar_t *path, y540_hid_error *e) {
  HANDLE backup;
  if (!path || !*path) {
    fail(e, "An explicit new backup destination is required before device I/O");
    return INVALID_HANDLE_VALUE;
  }
  backup = CreateFileW(path, GENERIC_WRITE, 0, NULL, CREATE_NEW,
                       FILE_ATTRIBUTE_NORMAL | FILE_FLAG_WRITE_THROUGH, NULL);
  if (backup == INVALID_HANDLE_VALUE) {
    DWORD code = GetLastError();
    fail(e, "Cannot create new backup file; existing backups are never overwritten");
    if (e) e->code = code;
  }
  return backup;
}
int y540_boot_program_with_backup(y540_hid_transport *t, const uint8_t *fw,
                      size_t size, const y540_config *c, const wchar_t *path,
                      y540_progress_fn progress, void *ctx, y540_hid_error *e) {
  HANDLE backup;
  int ok;
  if (!preflight(fw, size, c, e)) return 0;
  backup = backup_create(path, e);
  if (backup == INVALID_HANDLE_VALUE) return 0;
  ok = boot_program(t, fw, size, c, backup, progress, ctx, e);
  CloseHandle(backup);
  return ok;
}
int y540_boot_program(y540_hid_transport *t, const uint8_t *fw, size_t size,
                      const y540_config *c, y540_progress_fn progress,
                      void *ctx, y540_hid_error *e) {
  return y540_boot_program_with_backup(t, fw, size, c, NULL, progress, ctx, e);
}
static int update_device(const uint8_t *fw, size_t size, const y540_config *c,
                       HANDLE backup,
                       y540_progress_fn progress, void *ctx,
                       y540_hid_error *e) {
  y540_hid_error local_error = {0};
  if (!e)
    e = &local_error;
  y540_hid_transport t = {0};
  y540_hid_selector sel = {0};
  y540_hid_device main_device = {0};
  int handed_off = 0;
  uint32_t delay_ms, wait_ms, chip, page, usage;
  int ok = 0;
  if (!preflight(fw, size, c, e)) {
    return 0;
  }
  if (!number(c, "OPTION", "ALLHIDCOMMANDDELAY", 10, 5, &delay_ms, e) ||
      !number(c, "DELAY", "MSEC", 10, 6000, &wait_ms, e) ||
      !number(c, "NEWVERSION", "BOOTDEVICECHIPID", 16, 0x8171, &chip, e)) {
    return 0;
  }
  if (delay_ms > 60000 || wait_ms > 120000) {
    return fail(e, "Delay outside supported profile range");
  }
  /* Supported target identity is explicit; arbitrary NoCheckPID profiles are
   * rejected. */
  const char *mainid = y540_config_get(c, "MAIN", "HWID");
  const char *bootid = y540_config_get(c, "BOOT", "HWID");
  if (!mainid || !bootid || _stricmp(mainid, "USB\\VID_048D&PID_C100") ||
      _stricmp(bootid, "USB\\VID_048D&PID_89DB")) {
    return fail(e, "Only the supplied Y540 hardware identity is supported");
  }
  sel.vid = 0x048d;
  sel.pid = 0x89db;
  if (!number(c, "NEWVERSION", "BOOTDEVICEUPID", 16, 0xff89, &page, e) ||
      !number(c, "NEWVERSION", "BOOTDEVICEUID", 16, 0x00db, &usage, e)) {
    return 0;
  }
  if (page > 0xffff || usage > 0xffff || chip > 0xffff) {
    return fail(e, "HID profile values exceed 16 bits");
  }
  sel.usage_page = (uint16_t)page;
  sel.usage = (uint16_t)usage;
  note(progress, ctx, "Find keyboard boot interface", 0, 1);
  if (!y540_hid_open(&t, &sel, delay_ms, e)) {
    if (e && e->code != ERROR_NOT_FOUND) {
      return 0;
    }
    sel.pid = 0xc100;
    if (!number(c, "NEWVERSION", "MAINDEVICEUPID", 16, 0xff89, &page, e) ||
        !number(c, "NEWVERSION", "MAINDEVICEUID", 16, 0x0010, &usage, e)) {
      return 0;
    }
    if (page > 0xffff || usage > 0xffff || chip > 0xffff) {
      return fail(e, "HID profile values exceed 16 bits");
    }
    sel.usage_page = (uint16_t)page;
    sel.usage = (uint16_t)usage;
    note(progress, ctx, "Find keyboard normal interface", 0, 1);
    if (!y540_hid_open(&t, &sel, delay_ms, e)) {
      return 0;
    }
    main_device = t.device;
    if (!main_device.usb_parent_id[0] || !main_device.usb_location[0]) {
      y540_hid_close(&t);
      return fail(e, "Cannot correlate keyboard USB port across boot handoff; no mode change performed");
    }
    note(progress, ctx, "Enter keyboard boot mode", 0, 1);
    if (!y540_enter_boot(&t, e)) {
      y540_hid_close(&t);
      return 0;
    }
    y540_hid_close(&t);
    handed_off = 1;
    /* fix2-fix4 slept SHFU.ini DELAY MSEC (6000) here. Windows idles the
     * freshly enumerated boot device in that time, and it does not wake. Poll
     * instead and talk to it the moment it is enumerated and started. */
    sel.pid = 0x89db;
    number(c, "NEWVERSION", "BOOTDEVICEUPID", 16, 0xff89, &page, e);
    number(c, "NEWVERSION", "BOOTDEVICEUID", 16, 0x00db, &usage, e);
    if (page > 0xffff || usage > 0xffff || chip > 0xffff) {
      return fail(e, "HID profile values exceed 16 bits");
    }
    sel.usage_page = (uint16_t)page;
    sel.usage = (uint16_t)usage;
    sel.usb_parent_id = main_device.usb_parent_id;
    sel.usb_location = main_device.usb_location;
    note(progress, ctx, "Poll for boot-mode interface (no fixed wait)", 0, 1);
    {
      boot_find_context find_context = {&sel, delay_ms};
      /* DELAY MSEC is now only a floor for the discovery budget. */
      uint32_t budget = wait_ms < 30000 ? 30000 : wait_ms;
      if (!y540_wait_boot_device(find_boot, &find_context, &t, real_sleep,
                                 real_clock, NULL, 40, budget, progress, ctx,
                                 e)) {
        goto handoff_failed;
      }
    }
  }
  /* Bind every retry to the physical topology that was just validated. Copy
   * identity outside t, since reopening clears t's device storage. */
  y540_hid_device boot_device = t.device;
  boot_reopen_context reopen_context = {0};
  reopen_context.selector.vid = boot_device.vid;
  reopen_context.selector.pid = boot_device.pid;
  reopen_context.selector.usage_page = boot_device.usage_page;
  reopen_context.selector.usage = boot_device.usage;
  reopen_context.selector.usb_parent_id = boot_device.usb_parent_id;
  reopen_context.selector.usb_location = boot_device.usb_location;
  reopen_context.delay_ms = delay_ms;
  if (y540_wait_boot_chip(&t, (uint16_t)chip, reopen_boot, &reopen_context,
                          progress, ctx, e))
    ok = boot_program(&t, fw, size, c, backup, progress, ctx, e);
  y540_hid_close(&t);
  return ok;
handoff_failed:
  if (handed_off) {
    y540_hid_error primary = *e, cleanup = {0};
    /* A successful 09 may have switched mode; never send the normal-mode key
     * to a boot interface. Reopen only the same, exact normal interface. */
    sel.pid = 0xc100;
    sel.usage_page = main_device.usage_page;
    sel.usage = main_device.usage;
    sel.path = main_device.path;
    note(progress, ctx, "Try cleanup on original normal interface", 0, 1);
    if (y540_hid_open(&t, &sel, delay_ms, &cleanup)) {
      *e = primary;
      cleanup_mode(&t, e);
      y540_hid_close(&t);
    } else {
      *e = primary;
      snprintf(e->message, sizeof(e->message), "%.170s; original normal interface unavailable for cleanup",
               primary.message);
    }
  }
  return 0;
}
int y540_update_device_with_backup(const uint8_t *fw, size_t size,
                       const y540_config *c, const wchar_t *path,
                       y540_progress_fn progress, void *ctx,
                       y540_hid_error *e) {
  HANDLE backup;
  int ok;
  if (!preflight(fw, size, c, e)) return 0;
  backup = backup_create(path, e);
  if (backup == INVALID_HANDLE_VALUE) return 0;
  ok = update_device(fw, size, c, backup, progress, ctx, e);
  CloseHandle(backup);
  return ok;
}
int y540_update_device(const uint8_t *fw, size_t size, const y540_config *c,
                       y540_progress_fn progress, void *ctx,
                       y540_hid_error *e) {
  return y540_update_device_with_backup(fw, size, c, NULL, progress, ctx, e);
}

/* ---- fix7: read-only flash dump -------------------------------------------
 * Same handoff, port binding and chip qualification as update_device, then
 * only D1 (read) commands and a final C4 reset. No erase, no stage, no commit
 * command exists in this path. The front half deliberately duplicates the
 * update path instead of refactoring it, so the proven update code is not
 * touched. Output is written and flushed per KiB so a stall keeps the bytes
 * already read. */
int y540_dump_flash_device(const y540_config *c, const wchar_t *out_path,
                           uint32_t start, uint32_t end,
                           y540_progress_fn progress, void *ctx,
                           y540_hid_error *e) {
  y540_hid_error local_error = {0};
  y540_hid_transport t = {0};
  y540_hid_selector sel = {0};
  y540_hid_device main_device = {0};
  uint32_t delay_ms, wait_ms, chip, page, usage;
  int ok = 0, all = 1;
  HANDLE out = INVALID_HANDLE_VALUE;
  uint8_t *chunk = NULL, *again = NULL;
  uint32_t a;
  if (!e) e = &local_error;
  if (!out_path || !*out_path || start >= end || end > 0x20000u ||
      (start & 0x3ffu) || (end & 0x3ffu))
    return fail(e, "Dump range must be 1 KiB aligned within 0..0x20000 and an output file is required");
  if (!number(c, "OPTION", "ALLHIDCOMMANDDELAY", 10, 5, &delay_ms, e) ||
      !number(c, "DELAY", "MSEC", 10, 6000, &wait_ms, e) ||
      !number(c, "NEWVERSION", "BOOTDEVICECHIPID", 16, 0x8171, &chip, e))
    return 0;
  if (delay_ms > 60000 || wait_ms > 120000)
    return fail(e, "Delay outside supported profile range");
  const char *mainid = y540_config_get(c, "MAIN", "HWID");
  const char *bootid = y540_config_get(c, "BOOT", "HWID");
  if (!mainid || !bootid || _stricmp(mainid, "USB\\VID_048D&PID_C100") ||
      _stricmp(bootid, "USB\\VID_048D&PID_89DB"))
    return fail(e, "Only the supplied Y540 hardware identity is supported");
  if (!number(c, "NEWVERSION", "BOOTDEVICEUPID", 16, 0xff89, &page, e) ||
      !number(c, "NEWVERSION", "BOOTDEVICEUID", 16, 0x00db, &usage, e))
    return 0;
  if (page > 0xffff || usage > 0xffff || chip > 0xffff)
    return fail(e, "HID profile values exceed 16 bits");
  sel.vid = 0x048d;
  sel.pid = 0x89db;
  sel.usage_page = (uint16_t)page;
  sel.usage = (uint16_t)usage;
  note(progress, ctx, "Find keyboard boot interface", 0, 1);
  if (!y540_hid_open(&t, &sel, delay_ms, e)) {
    if (e->code != ERROR_NOT_FOUND) return 0;
    sel.pid = 0xc100;
    if (!number(c, "NEWVERSION", "MAINDEVICEUPID", 16, 0xff89, &page, e) ||
        !number(c, "NEWVERSION", "MAINDEVICEUID", 16, 0x0010, &usage, e))
      return 0;
    sel.usage_page = (uint16_t)page;
    sel.usage = (uint16_t)usage;
    note(progress, ctx, "Find keyboard normal interface", 0, 1);
    if (!y540_hid_open(&t, &sel, delay_ms, e)) return 0;
    main_device = t.device;
    if (!main_device.usb_parent_id[0] || !main_device.usb_location[0]) {
      y540_hid_close(&t);
      return fail(e, "Cannot correlate keyboard USB port across boot handoff; no mode change performed");
    }
    note(progress, ctx, "Enter keyboard boot mode", 0, 1);
    if (!y540_enter_boot(&t, e)) {
      y540_hid_close(&t);
      return 0;
    }
    y540_hid_close(&t);
    sel.pid = 0x89db;
    number(c, "NEWVERSION", "BOOTDEVICEUPID", 16, 0xff89, &page, e);
    number(c, "NEWVERSION", "BOOTDEVICEUID", 16, 0x00db, &usage, e);
    sel.usage_page = (uint16_t)page;
    sel.usage = (uint16_t)usage;
    sel.usb_parent_id = main_device.usb_parent_id;
    sel.usb_location = main_device.usb_location;
    {
      boot_find_context find_context = {&sel, delay_ms};
      uint32_t budget = wait_ms < 30000 ? 30000 : wait_ms;
      if (!y540_wait_boot_device(find_boot, &find_context, &t, real_sleep,
                                 real_clock, NULL, 40, budget, progress, ctx, e))
        return 0;
    }
  }
  {
    y540_hid_device boot_device = t.device;
    boot_reopen_context reopen_context = {0};
    reopen_context.selector.vid = boot_device.vid;
    reopen_context.selector.pid = boot_device.pid;
    reopen_context.selector.usage_page = boot_device.usage_page;
    reopen_context.selector.usage = boot_device.usage;
    reopen_context.selector.usb_parent_id = boot_device.usb_parent_id;
    reopen_context.selector.usb_location = boot_device.usb_location;
    reopen_context.delay_ms = delay_ms;
    if (!y540_wait_boot_chip(&t, (uint16_t)chip, reopen_boot, &reopen_context,
                             progress, ctx, e)) {
      y540_hid_close(&t);
      return 0;
    }
  }
  out = CreateFileW(out_path, GENERIC_WRITE, 0, NULL, CREATE_NEW,
                    FILE_ATTRIBUTE_NORMAL | FILE_FLAG_WRITE_THROUGH, NULL);
  if (out == INVALID_HANDLE_VALUE) {
    DWORD code = GetLastError();
    fail(e, "Cannot create new dump file; existing files are never overwritten");
    e->code = code;
    y540_hid_close(&t);
    return 0;
  }
  chunk = malloc(0x400);
  again = malloc(0x400);
  if (!chunk || !again) {
    free(chunk);
    free(again);
    CloseHandle(out);
    y540_hid_close(&t);
    return fail(e, "Out of memory");
  }
  note(progress, ctx, "Read-only dump (no erase/write commands exist in this mode)", start, end);
  for (a = start; a < end; a += 0x400) {
    DWORD written = 0;
    if (!read_flash(&t, a, chunk, 0x400, NULL, NULL, e)) {
      all = 0;
      break;
    }
    if (!WriteFile(out, chunk, 0x400, &written, NULL) || written != 0x400 ||
        !FlushFileBuffers(out)) {
      fail(e, "Cannot write dump file");
      all = 0;
      break;
    }
    if (!((a - start) & 0x1fff)) note(progress, ctx, "Dump progress (flash address)", a, end);
  }
  CloseHandle(out);
  if (all) {
    /* Stability check: read the first KiB again and compare with the saved copy. */
    DWORD got = 0;
    HANDLE in = CreateFileW(out_path, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, 0, NULL);
    if (in != INVALID_HANDLE_VALUE) {
      if (ReadFile(in, chunk, 0x400, &got, NULL) && got == 0x400) {
        if (!read_flash(&t, start, again, 0x400, NULL, NULL, e)) all = 0;
        else if (memcmp(chunk, again, 0x400))
          note(progress, ctx, "WARNING: re-read of the first KiB differs from the first read (unstable reads)", 1, 1);
        else
          note(progress, ctx, "Re-read of the first KiB matches (reads are stable)", 1, 1);
      }
      CloseHandle(in);
    }
  }
  free(chunk);
  free(again);
  if (all) {
    note(progress, ctx, "Dump complete; returning keyboard to normal mode (C4 reset)", end, end);
    ok = reset(&t, e);
  } else {
    note(progress, ctx, "Dump stopped early; partial file kept; no reset sent. If the keyboard is dead hold power ~10 s", start, end);
  }
  y540_hid_close(&t);
  return ok;
}
