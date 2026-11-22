/* ite_flash.efi - Legion Y540 keyboard controller (ITE IT8176) firmware tool for UEFI.
 * Talks to the chip through the firmware's own USB stack (EFI_USB_IO_PROTOCOL), where the
 * keyboard still works. Protocol, safety checks and firmware images come from
 * github.com/AMIRSRAD/Legion-Y540-Keyboard-Fix. Experimental, community firmware: use at own risk. */
#include "efi.h"
#include "proto.h"
#include "fw_images.h"
#ifndef ITE_VID
#define ITE_VID 0x048D
#endif
#ifndef PID_NORMAL
#define PID_NORMAL 0xC100
#endif

/* freestanding helpers the compiler may call */
void *memset(void *d, int c, UINTN n) { volatile unsigned char *p = d; while (n--) *p++ = (unsigned char)c; return d; }
void *memcpy(void *d, const void *s, UINTN n) { volatile unsigned char *p = d; const unsigned char *q = s; while (n--) *p++ = *q++; return d; }
int memcmp(const void *a, const void *b, UINTN n) { const unsigned char *x = a, *y = b; for (; n; n--, x++, y++) if (*x != *y) return *x - *y; return 0; }

static EFI_SYSTEM_TABLE *ST;
static EFI_BOOT_SERVICES *BS;
static EFI_HANDLE IMAGE;
static EFI_GUID UsbIoGuid = {0x2B2F68D6, 0x0CD2, 0x44CF, {0x8E, 0x8B, 0xBB, 0xA2, 0x0B, 0x1B, 0x5B, 0x75}};
static EFI_GUID LoadedImageGuid = {0x5B1B31A1, 0x9562, 0x11D2, {0x8E, 0x3F, 0x00, 0xA0, 0xC9, 0x69, 0x72, 0x3B}};
static EFI_GUID SfsGuid = {0x964E5B22, 0x6459, 0x11D2, {0x8E, 0x39, 0x00, 0xA0, 0xC9, 0x69, 0x72, 0x3B}};

/* ---------------- logging ---------------- */
static char logbuf[262144];
static UINTN loglen;
static void put(const char *s) {
  CHAR16 w[256]; UINTN n = 0;
  while (*s) {
    char c = *s++;
    if (loglen < sizeof(logbuf) - 1) logbuf[loglen++] = c;
    if (c == '\n') w[n++] = '\r';
    w[n++] = (unsigned char)c;
    if (n >= 250) { w[n] = 0; ST->ConOut->OutputString(ST->ConOut, w); n = 0; }
  }
  w[n] = 0; if (n) ST->ConOut->OutputString(ST->ConOut, w);
}
static void hex(UINT64 v, int digits) {
  char b[17]; static const char *h = "0123456789ABCDEF";
  if (digits > 16) digits = 16;
  for (int i = digits - 1; i >= 0; i--) { b[i] = h[v & 15]; v >>= 4; }
  b[digits] = 0; put(b);
}
static void dec(UINT64 v) { char b[24]; int i = 23; b[i] = 0; do { b[--i] = '0' + (v % 10); v /= 10; } while (v); put(b + i); }
static void color(UINTN a) { ST->ConOut->SetAttribute(ST->ConOut, a); }
#define C_NORMAL 0x07
#define C_WARN 0x0E
#define C_BAD 0x0C
#define C_GOOD 0x0A

/* ---------------- files on the partition this program was started from ---------------- */
static EFI_FILE *open_root(void) {
  EFI_LOADED_IMAGE *li; EFI_SIMPLE_FILE_SYSTEM *fs; EFI_FILE *root;
  if (BS->HandleProtocol(IMAGE, &LoadedImageGuid, (void **)&li)) return 0;
  if (BS->HandleProtocol(li->DeviceHandle, &SfsGuid, (void **)&fs)) return 0;
  if (fs->OpenVolume(fs, &root)) return 0;
  return root;
}
static int write_file(CHAR16 *name, const void *data, UINTN len, int overwrite) {
  EFI_FILE *root = open_root(), *f;
  if (!root) return 0;
  if (!root->Open(root, &f, name, EFI_FILE_MODE_READ | EFI_FILE_MODE_WRITE, 0)) {
    if (!overwrite) { f->Close(f); root->Close(root); return -1; }   /* exists */
    f->Delete(f);
  }
  if (root->Open(root, &f, name, EFI_FILE_MODE_READ | EFI_FILE_MODE_WRITE | EFI_FILE_MODE_CREATE, 0)) { root->Close(root); return 0; }
  UINTN n = len; EFI_STATUS s = f->Write(f, &n, (void *)data);
  EFI_STATUS s2 = f->Flush(f);
  f->Close(f); root->Close(root);
  return (!s && !s2 && n == len) ? 1 : 0;
}
static void save_log(void) { write_file(u"\\ite_flash.txt", logbuf, loglen, 1); }

static int save_backup(void *ctx, const u8 *data, int known) {
  (void)ctx; (void)known;
  CHAR16 name[] = u"\\ite_bk00.bin";
  for (int i = 1; i < 100; i++) {
    name[7] = u'0' + i / 10; name[8] = u'0' + i % 10;
    int r = write_file(name, data, IMAGE_SIZE, 0);
    if (r == -1) continue;
    if (r != 1) { put("  backup file write FAILED\n"); return 0; }
    /* read back and compare */
    EFI_FILE *root = open_root(), *f; static u8 chk[IMAGE_SIZE]; UINTN n = IMAGE_SIZE;
    if (!root || root->Open(root, &f, name, EFI_FILE_MODE_READ, 0)) { put("  backup reopen FAILED\n"); return 0; }
    EFI_STATUS s = f->Read(f, &n, chk); f->Close(f); root->Close(root);
    if (s || n != IMAGE_SIZE || p_memcmp(chk, data, IMAGE_SIZE)) { put("  backup verify FAILED\n"); return 0; }
    put("Backup saved and verified: ite_bk"); char d2[3] = {(char)('0' + i / 10), (char)('0' + i % 10), 0}; put(d2); put(".bin\n");
    save_log();
    return 1;
  }
  put("  no free backup file name\n"); return 0;
}

/* ---------------- USB ---------------- */
typedef struct { EFI_USB_IO *io; UINT8 ifnum; } usbdev;
static int find_dev(UINT16 pid, usbdev *out) {
  UINTN count = 0; EFI_HANDLE *h = 0; int found = 0;
  if (BS->LocateHandleBuffer(ByProtocol, &UsbIoGuid, 0, &count, &h)) return 0;
  for (UINTN i = 0; i < count && !found; i++) {
    EFI_USB_IO *io; EFI_USB_DEVICE_DESCRIPTOR dd; EFI_USB_INTERFACE_DESCRIPTOR id;
    if (BS->HandleProtocol(h[i], &UsbIoGuid, (void **)&io)) continue;
    if (io->UsbGetDeviceDescriptor(io, &dd) || dd.IdVendor != ITE_VID || dd.IdProduct != pid) continue;
    if (io->UsbGetInterfaceDescriptor(io, &id) || id.InterfaceNumber != 0) continue;
    out->io = io; out->ifnum = id.InterfaceNumber; found = 1;
  }
  BS->FreePool(h);
  return found;
}
static void sleep_ms(void *c, unsigned ms) { (void)c; BS->Stall((UINTN)ms * 1000); }

static int fail_reports;
static void report_fail(const char *what, EFI_STATUS s, UINT32 us) {
  if (fail_reports++ < 12) { put("  [usb] "); put(what); put(" status "); hex(s, 16); put(" usb "); hex(us, 8); put("\n"); }
}
static int ctl(usbdev *d, UINT8 rt, UINT8 rq, UINT16 val, void *buf, UINT16 len, EFI_USB_DATA_DIRECTION dir, const char *what) {
  EFI_USB_DEVICE_REQUEST r = {rt, rq, val, d->ifnum, len}; UINT32 us = 0;
  EFI_STATUS s = d->io->UsbControlTransfer(d->io, &r, dir, 2000, buf, len, &us);
  if (s) report_fail(what, s, us);
  return s == EFI_SUCCESS;
}
/* boot mode (89DB): 63-byte feature report without report ID */
static usbdev bootdev;
static int boot_set(void *c, const u8 p[63]) { (void)c; return ctl(&bootdev, 0x21, 0x09, 0x0300, (void *)p, 63, EfiUsbDataOut, "SET_REPORT"); }
static int boot_get(void *c, u8 p[63]) { (void)c; return ctl(&bootdev, 0xA1, 0x01, 0x0300, p, 63, EfiUsbDataIn, "GET_REPORT"); }
static void lhex(unsigned long long v, int d) { hex(v, d); }
static void ldec(unsigned long long v) { dec(v); }

/* normal mode (C100): report 5A, 17 bytes incl. ID */
static int n_set(usbdev *d, const u8 *payload, unsigned n) {
  u8 r[17]; p_memset(r, 0, 17); r[0] = 0x5A; p_memcpy(r + 1, payload, n);
  BS->Stall(CMD_DELAY_MS * 1000);
  return ctl(d, 0x21, 0x09, 0x035A, r, 17, EfiUsbDataOut, "5A SET");
}
static int n_get(usbdev *d, u8 r[17]) {
  p_memset(r, 0, 17);
  BS->Stall(CMD_DELAY_MS * 1000);
  return ctl(d, 0xA1, 0x01, 0x035A, r, 17, EfiUsbDataIn, "5A GET");
}
static const u8 ITE_KEY[15] = {'I','T','E',' ','T','e','c','h','.',' ','I','n','c','.',0};

static void dump17(const char *tag, const u8 *r) {
  put(tag); for (int i = 0; i < 17; i++) { hex(r[i], 2); put(i == 16 ? "\n" : " "); }
}
static int enter_boot(usbdev *kb) {
  u8 r[17]; int echoed = 0;
  /* Sending the key TOGGLES the controller's custom mode (Windows updater: at most two toggles
     until the echo matches). Up to 4 tries here, logging every reply for diagnosis. */
  /* UEFI keyboard drivers put HID keyboards into BOOT protocol, where report IDs (and the
     vendor report 5A) are not used. Windows/Linux use REPORT protocol. Switch before the handshake. */
  u8 proto = 0xFF;
  if (ctl(kb, 0xA1, 0x03, 0, &proto, 1, EfiUsbDataIn, "GET_PROTOCOL")) { put("  HID protocol now: "); put(proto == 0 ? "boot (0)\n" : proto == 1 ? "report (1)\n" : "?\n"); }
  if (ctl(kb, 0x21, 0x0B, 1, 0, 0, EfiUsbNoData, "SET_PROTOCOL(report)")) put("  switched to report protocol\n");
  BS->Stall(50000);
  proto = 0xFF;
  if (ctl(kb, 0xA1, 0x03, 0, &proto, 1, EfiUsbDataIn, "GET_PROTOCOL")) { put("  HID protocol now: "); put(proto == 0 ? "boot (0)\n" : proto == 1 ? "report (1)\n" : "?\n"); }
  p_memset(r, 0, 17);
  if (n_get(kb, r)) dump17("  5A before: ", r); else put("  5A before: GET failed\n");
  for (int a = 0; a < 4 && !echoed; a++) {
    put("  try "); dec(a + 1); put(": send key -> ");
    if (!n_set(kb, ITE_KEY, 15)) { put("SET failed\n"); BS->Stall(200000); continue; }
    BS->Stall(100000);
    if (!n_get(kb, r)) { put("GET failed\n"); BS->Stall(200000); continue; }
    dump17("reply ", r);
    BS->Stall(100000);
    echoed = r[0] == 0x5A && !p_memcmp(r + 1, ITE_KEY, 14);
    if (!echoed && r[0] != 0x5A && !p_memcmp(r, ITE_KEY, 14)) { put("  (echo without report ID byte - accepted)\n"); echoed = 1; }
  }
  if (!echoed) {
    put("STOP: keyboard did not echo the ITE key. Nothing changed.\n");
    ctl(kb, 0x21, 0x0B, 0, 0, 0, EfiUsbNoData, "SET_PROTOCOL(boot)");   /* give the UEFI keyboard driver its boot protocol back */
    return 0;
  }
  put("ITE key handshake OK. Switching keyboard to update mode (5A/09)...\n");
  BS->Stall(100000);
  u8 boot[2] = {9, 0};
  n_set(kb, boot, 2);              /* the device may disconnect before acknowledging */
  BS->Stall(1000000);
  return 1;
}
static int wait_boot(unsigned seconds) {
  for (unsigned t = 0; t < seconds * 10; t++) {
    if (find_dev(0x89DB, &bootdev)) return 1;
    BS->Stall(100000);
  }
  return 0;
}


/* ---------------- fallback: start Windows Boot Manager (mouse-usable recovery with the Windows updater) ---------------- */
static EFI_GUID DevicePathGuid = {0x09576E91, 0x6D3F, 0x11D2, {0x8E, 0x39, 0x00, 0xA0, 0xC9, 0x69, 0x72, 0x3B}};
typedef EFI_STATUS (EFIAPI *LOAD_IMAGE)(BOOLEAN, EFI_HANDLE, EFI_DEVICE_PATH *, void *, UINTN, EFI_HANDLE *);
typedef EFI_STATUS (EFIAPI *START_IMAGE)(EFI_HANDLE, UINTN *, CHAR16 **);
static void start_windows(void) {
  static CHAR16 path[] = u"\\EFI\\Microsoft\\Boot\\bootmgfw.efi";
  UINTN n = 0; EFI_HANDLE *h = 0;
  if (BS->LocateHandleBuffer(ByProtocol, &SfsGuid, 0, &n, &h)) { put("No file systems found.\n"); return; }
  for (UINTN i = 0; i < n; i++) {
    EFI_SIMPLE_FILE_SYSTEM *fs; EFI_FILE *root, *f; EFI_DEVICE_PATH *dp;
    if (BS->HandleProtocol(h[i], &SfsGuid, (void **)&fs) || fs->OpenVolume(fs, &root)) continue;
    int has = !root->Open(root, &f, path, EFI_FILE_MODE_READ, 0);
    if (has) f->Close(f);
    root->Close(root);
    if (!has || BS->HandleProtocol(h[i], &DevicePathGuid, (void **)&dp)) continue;
    /* device path of the volume + file path node + end node */
    UINTN dplen = 0; EFI_DEVICE_PATH *p = dp;
    while (!(p->Type == 0x7F && p->SubType == 0xFF)) { UINTN l = p->Length[0] | p->Length[1] << 8; dplen += l; p = (EFI_DEVICE_PATH *)((UINT8 *)p + l); }
    UINTN plen = sizeof(path), nodelen = 4 + plen;
    static UINT8 buf[1024];
    if (dplen + nodelen + 4 > sizeof(buf)) continue;
    memcpy(buf, dp, dplen);
    UINT8 *q = buf + dplen; q[0] = 4; q[1] = 4; q[2] = (UINT8)nodelen; q[3] = (UINT8)(nodelen >> 8);
    memcpy(q + 4, path, plen);
    q += nodelen; q[0] = 0x7F; q[1] = 0xFF; q[2] = 4; q[3] = 0;
    EFI_HANDLE img = 0;
    LOAD_IMAGE load = (LOAD_IMAGE)BS->LoadImage; START_IMAGE start = (START_IMAGE)BS->StartImage;
    put("Starting Windows Boot Manager...\n"); save_log();
    if (!load(0, IMAGE, (EFI_DEVICE_PATH *)buf, 0, 0, &img)) { start(img, 0, 0); return; }
    put("  LoadImage failed on this volume\n");
  }
  put("Windows Boot Manager not found.\n");
}

/* ---------------- UI ---------------- */
static CHAR16 wait_key(unsigned seconds) {
  EFI_INPUT_KEY k;
  for (unsigned t = 0; t < seconds * 100; t++) {
    if (!ST->ConIn->ReadKeyStroke(ST->ConIn, &k)) return k.UnicodeChar ? k.UnicodeChar : (CHAR16)(0x100 + k.ScanCode);
    BS->Stall(10000);
  }
  return 0;
}
static void finish(int seconds) {
  save_log();
  color(C_NORMAL);
  put("\nLog saved as \\ite_flash.txt on this partition.\nPress any key to return (or wait ");
  dec(seconds); put(" s). Then hold nothing - just restart normally.\n");
  ST->ConIn->Reset(ST->ConIn, 0);
  wait_key(seconds);
}
static int images_ok(void) {
  return known_index(FW_EXP7) == 7 && known_index(FW_STOCK44) == 0;
}

EFI_STATUS EFIAPI efi_main(EFI_HANDLE image, EFI_SYSTEM_TABLE *st) {
  ST = st; BS = st->BootServices; IMAGE = image;
  BS->SetWatchdogTimer(0, 0, 0, 0);
  ST->ConOut->ClearScreen(ST->ConOut);
  color(C_GOOD);
  put("ITE keyboard firmware tool for Legion Y540 (UEFI) v3\n");
  color(C_NORMAL);
  put("Based on github.com/AMIRSRAD/Legion-Y540-Keyboard-Fix. Experimental - use at own risk.\n\n");
#ifdef TEST_CHAINLOAD
  start_windows(); put("returned from chainload\n"); finish(5); return 0;
#endif
  if (!images_ok()) { color(C_BAD); put("Embedded firmware images failed their SHA-256 check. Aborting.\n"); finish(60); return 0; }
  put("Embedded images verified: exp7 and original Lenovo 44 (SHA-256 OK).\n");

  ite_link L = {0, boot_set, boot_get, sleep_ms, put, lhex, ldec};
  const u8 *last_target = FW_EXP7;
  static u8 A[IMAGE_SIZE], B[IMAGE_SIZE];
  usbdev kb;
  int r;

  if (find_dev(0x89DB, &bootdev)) {
    /* Already in update mode (e.g. an earlier run was interrupted). The keyboard cannot type now,
       so act automatically: a complete known image is just reset; a blank or half-written exp7 is completed. */
    color(C_WARN);
    put("Keyboard controller is ALREADY in update mode (89DB).\n");
    put("Automatic recovery in 10 s: complete firmware -> reset only; blank/interrupted exp7 -> finish writing exp7.\n");
    put("To cancel, power off now (hold the power button 10 s).\n");
    color(C_NORMAL);
    BS->Stall(10000000);
    r = ite_program(&L, FW_EXP7, A, B, save_backup, 0, 1);
  } else {
    if (!find_dev(PID_NORMAL, &kb)) {
      color(C_BAD); put("No ITE keyboard controller (048D:C100) found. Nothing changed.\n"); finish(120); return 0;
    }
    put("Found ITE keyboard controller 048D:C100 (normal mode).\n\n");
    color(C_WARN);
    put("Keep the CHARGER CONNECTED. During the operation the built-in keyboard will not work.\n\n");
    color(C_NORMAL);
    put("  1 = Backup only (read firmware to a file, no erase), then reset\n");
    put("  2 = Backup + install exp7 fix (keyboard restarts itself at boot handover)\n");
    put("  3 = Backup + restore original Lenovo firmware 44\n");
    put("  any other key = exit without changes\n\nChoice: ");
    ST->ConIn->Reset(ST->ConIn, 0);
    CHAR16 c = wait_key(300);
    const u8 *target = 0;
    if (c == u'1') { put("1\n"); }
    else if (c == u'2' || c == u'3') {
      target = c == u'2' ? FW_EXP7 : FW_STOCK44;
      put(c == u'2' ? "2 (exp7)\n" : "3 (original 44)\n");
      color(C_WARN);
      put("\nThis ERASES and rewrites the keyboard controller firmware.\nPress Y to continue, any other key to cancel: ");
      color(C_NORMAL);
      CHAR16 y = wait_key(120);
      if (y != u'y' && y != u'Y') { put("\nCancelled. Nothing changed.\n"); finish(30); return 0; }
      put("Y\n");
    } else { put("\nExit. Nothing changed.\n"); finish(10); return 0; }

    put("\n");
    if (!enter_boot(&kb)) { finish(120); return 0; }
    put("Waiting for update-mode device 048D:89DB...\n");
    if (!wait_boot(15)) {
      color(C_BAD);
      put("STOP: update-mode device did not appear within 15 s. Nothing erased.\n");
      put("Hold the power button ~10 s to restore the keyboard.\n");
      finish(300); return 0;
    }
    put("Update-mode device found.\n");
    save_log();
    if (target) last_target = target;
    r = ite_program(&L, target, A, B, save_backup, 0, 0);
  }

  for (int retry = 1; r == R_FAIL_AFTER_ERASE && retry <= 3; retry++) {
    color(C_WARN); put("\nAutomatic retry "); dec(retry); put("/3 (resume write)...\n"); color(C_NORMAL);
    BS->Stall(3000000);
    if (!wait_boot(15)) { put("  update-mode device not found\n"); continue; }
    r = ite_program(&L, last_target, A, B, save_backup, 0, 1);
  }
  put("\n");
  if (r == R_FAIL_AFTER_ERASE) {
    color(C_BAD);
    put("Write could not be completed. The keyboard controller's recovery area is intact.\n");
    put("Windows will start in 60 s: log in with the mouse (on-screen keyboard) and run\n");
    put("Desktop\\ITE-fix\\Y540-Keyboard-Fix\\INSTALL THE FIX.cmd - it resumes the write.\n");
    color(C_NORMAL); save_log();
    BS->Stall(60000000);
    start_windows();
    finish(600); return 0;
  }
  if (r == R_OK_WRITTEN) { color(C_GOOD); put("DONE: firmware written and verified. The keyboard restarts in a few seconds.\n"); }
  else if (r == R_OK_BACKUP_ONLY) { color(C_GOOD); put("DONE: backup finished, keyboard reset to normal mode.\nIf it does not type, hold the power button ~10 s.\n"); }
  else if (r == R_FAIL_NO_ERASE) { color(C_WARN); put("Stopped before erase - firmware unchanged. Hold the power button ~10 s to restore the keyboard.\n"); }
  else { color(C_BAD); put("FAILED after erase. Do NOT panic: the recovery area is intact.\nRun this program again (it resumes automatically).\n"); }
  finish(r == R_OK_WRITTEN || r == R_OK_BACKUP_ONLY ? 60 : 600);
  return 0;
}
