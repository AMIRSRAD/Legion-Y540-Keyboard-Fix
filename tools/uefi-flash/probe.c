/* ite_probe.efi - READ-ONLY probe for the Lenovo Legion Y540 keyboard controller (ITE IT8176).
 * Lists every USB device the firmware knows (EFI_USB_IO_PROTOCOL): VID/PID/bcdDevice, interface,
 * strings and device path. For ITE devices (VID 048D) it also reads the HID report descriptor.
 * Only standard GET_DESCRIPTOR requests are sent. Nothing is written to the keyboard chip.
 * The log is shown on screen and saved as \ite_probe.txt on the partition the program was started from. */
#include "efi.h"
#ifndef ITE_VID
#define ITE_VID 0x048D
#endif

static EFI_SYSTEM_TABLE *ST;
static EFI_BOOT_SERVICES *BS;
static EFI_GUID UsbIoGuid = {0x2B2F68D6, 0x0CD2, 0x44CF, {0x8E, 0x8B, 0xBB, 0xA2, 0x0B, 0x1B, 0x5B, 0x75}};
static EFI_GUID DevicePathGuid = {0x09576E91, 0x6D3F, 0x11D2, {0x8E, 0x39, 0x00, 0xA0, 0xC9, 0x69, 0x72, 0x3B}};
static EFI_GUID DpToTextGuid = {0x8B843E20, 0x8132, 0x4852, {0x90, 0xCC, 0x55, 0x1A, 0x4E, 0x4A, 0x7F, 0x1C}};
static EFI_GUID LoadedImageGuid = {0x5B1B31A1, 0x9562, 0x11D2, {0x8E, 0x3F, 0x00, 0xA0, 0xC9, 0x69, 0x72, 0x3B}};
static EFI_GUID SfsGuid = {0x964E5B22, 0x6459, 0x11D2, {0x8E, 0x39, 0x00, 0xA0, 0xC9, 0x69, 0x72, 0x3B}};

/* ---- tiny logging: screen (UTF-16) + ASCII buffer saved to a file ---- */
static char logbuf[65536];
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
static void putw(const CHAR16 *s) {  /* UTF-16 string -> ASCII (non-ASCII as '?') */
  char b[2] = {0, 0};
  if (!s) { put("(null)"); return; }
  for (; *s; s++) { b[0] = (*s < 128 && *s >= 32) ? (char)*s : '?'; put(b); }
}
static void hex(UINT64 v, int digits) {
  char b[17]; static const char *h = "0123456789ABCDEF";
  if (digits > 16) digits = 16;
  for (int i = digits - 1; i >= 0; i--) { b[i] = h[v & 15]; v >>= 4; }
  b[digits] = 0; put(b);
}
static void dec(UINT64 v) {
  char b[24]; int i = 23; b[i] = 0;
  do { b[--i] = '0' + (v % 10); v /= 10; } while (v);
  put(b + i);
}

static void save_log(EFI_HANDLE image) {
  EFI_LOADED_IMAGE *li; EFI_SIMPLE_FILE_SYSTEM *fs; EFI_FILE *root, *f;
  if (BS->HandleProtocol(image, &LoadedImageGuid, (void **)&li)) { put("[log] no LoadedImage\n"); return; }
  if (BS->HandleProtocol(li->DeviceHandle, &SfsGuid, (void **)&fs)) { put("[log] no file system\n"); return; }
  if (fs->OpenVolume(fs, &root)) { put("[log] OpenVolume failed\n"); return; }
  CHAR16 name[] = u"\\ite_probe.txt";
  /* delete an old log first so a shorter new log does not keep stale tail bytes */
  if (!root->Open(root, &f, name, EFI_FILE_MODE_READ | EFI_FILE_MODE_WRITE, 0)) f->Delete(f);
  if (root->Open(root, &f, name, EFI_FILE_MODE_READ | EFI_FILE_MODE_WRITE | EFI_FILE_MODE_CREATE, 0)) {
    put("[log] cannot create \\ite_probe.txt\n"); root->Close(root); return;
  }
  UINTN n = loglen;
  EFI_STATUS s = f->Write(f, &n, logbuf);
  f->Flush(f); f->Close(f); root->Close(root);
  put(s ? "[log] write FAILED\n" : "Log saved to \\ite_probe.txt on this partition.\n");
}


/* Exact HID report descriptor length from the configuration descriptor (firmware treats short reads as errors). */
static UINTN hid_report_len(EFI_USB_IO *io, UINT8 ifnum) {
  static UINT8 cfg[1024]; UINT32 us = 0;
  EFI_USB_DEVICE_REQUEST rq = {0x80, 0x06, 0x0200, 0, 9};
  if (io->UsbControlTransfer(io, &rq, EfiUsbDataIn, 1000, cfg, 9, &us)) return 0;
  UINTN total = cfg[2] | (cfg[3] << 8);
  if (total < 9 || total > sizeof(cfg)) return 0;
  rq.Length = (UINT16)total;
  if (io->UsbControlTransfer(io, &rq, EfiUsbDataIn, 1000, cfg, total, &us)) return 0;
  int cur_if = -1;
  for (UINTN p = 0; p + 1 < total && cfg[p] >= 2; p += cfg[p]) {
    if (cfg[p + 1] == 0x04 && p + 2 < total) cur_if = cfg[p + 2];
    if (cfg[p + 1] == 0x21 && cur_if == ifnum && p + 8 < total && cfg[p + 6] == 0x22)
      return cfg[p + 7] | (cfg[p + 8] << 8);
  }
  return 0;
}

/* ---- probe ---- */
static int probe_all(int verbose_hid) {
  UINTN count = 0; EFI_HANDLE *handles = 0; int ite = 0;
  EFI_STATUS s = BS->LocateHandleBuffer(ByProtocol, &UsbIoGuid, 0, &count, &handles);
  if (EFI_ERROR(s)) { put("No USB_IO handles (status "); hex(s, 16); put(")\n"); return 0; }
  EFI_DEVICE_PATH_TO_TEXT *dpt = 0;
  BS->LocateProtocol(&DpToTextGuid, 0, (void **)&dpt);
  put("USB interfaces seen by firmware: "); dec(count); put("\n");
  for (UINTN i = 0; i < count; i++) {
    EFI_USB_IO *io; EFI_USB_DEVICE_DESCRIPTOR dd; EFI_USB_INTERFACE_DESCRIPTOR id;
    if (BS->HandleProtocol(handles[i], &UsbIoGuid, (void **)&io)) continue;
    put("\n#"); dec(i); put(" ");
    if (io->UsbGetDeviceDescriptor(io, &dd)) { put("device descriptor: ERROR\n"); continue; }
    put("VID "); hex(dd.IdVendor, 4); put(" PID "); hex(dd.IdProduct, 4);
    put(" bcdDevice "); hex(dd.BcdDevice, 4); put(" USB "); hex(dd.BcdUSB, 4);
    if (!io->UsbGetInterfaceDescriptor(io, &id)) {
      put(" | if "); dec(id.InterfaceNumber); put(" class "); hex(id.InterfaceClass, 2);
      put("/"); hex(id.InterfaceSubClass, 2); put("/"); hex(id.InterfaceProtocol, 2);
    }
    put("\n");
    EFI_DEVICE_PATH *dp;
    if (dpt && !BS->HandleProtocol(handles[i], &DevicePathGuid, (void **)&dp)) {
      CHAR16 *t = dpt->ConvertDevicePathToText(dp, 0, 0);
      put("   path: "); putw(t); put("\n");
      if (t) BS->FreePool(t);
    }
    CHAR16 *str;
    if (dd.StrManufacturer && !io->UsbGetStringDescriptor(io, 0x0409, dd.StrManufacturer, &str)) {
      put("   manufacturer: "); putw(str); put("\n"); BS->FreePool(str);
    }
    if (dd.StrProduct && !io->UsbGetStringDescriptor(io, 0x0409, dd.StrProduct, &str)) {
      put("   product: "); putw(str); put("\n"); BS->FreePool(str);
    }
    if (dd.IdVendor == ITE_VID) {
      ite++;
      put("   >>> ITE device");
      if (dd.IdProduct == 0xC100) put(" in NORMAL keyboard mode (C100)");
      else if (dd.IdProduct == 0x89DB) put(" in UPDATE / bootloader mode (89DB)");
      put("\n");
      if (verbose_hid && id.InterfaceClass == 0x03) {
        /* GET_DESCRIPTOR (HID report descriptor) - standard, read-only request */
        static UINT8 rd[1024]; UINT32 us = 0;
        UINTN rlen = hid_report_len(io, id.InterfaceNumber);
        put("   HID report descriptor length: "); dec(rlen); put("\n");
        if (rlen == 0 || rlen > sizeof(rd)) continue;
        EFI_USB_DEVICE_REQUEST rq = {0x81, 0x06, 0x2200, id.InterfaceNumber, (UINT16)rlen};
        for (UINTN k = 0; k < sizeof(rd); k++) rd[k] = 0;
        s = io->UsbControlTransfer(io, &rq, EfiUsbDataIn, 1000, rd, rlen, &us);
        put("   HID report descriptor read: status "); hex(s, 16); put(" usb "); hex(us, 8); put("\n");
        if (!EFI_ERROR(s)) {
          UINTN last = rlen;
          put("   bytes ("); dec(last); put("):");
          for (UINTN k = 0; k < last; k++) { if (k % 32 == 0) put("\n    "); hex(rd[k], 2); put(" "); }
          put("\n");
          for (UINTN k = 0; k + 1 < last; k++)       /* report ID items (0x85 xx) */
            if (rd[k] == 0x85) { put("   report ID "); hex(rd[k + 1], 2); put("\n"); }
        }
      }
    }
  }
  BS->FreePool(handles);
  return ite;
}

static void connect_all(void) {
  UINTN n = 0; EFI_HANDLE *h = 0;
  if (BS->LocateHandleBuffer(AllHandles, 0, 0, &n, &h)) return;
  for (UINTN i = 0; i < n; i++) BS->ConnectController(h[i], 0, 0, 1);
  BS->FreePool(h);
}

EFI_STATUS EFIAPI efi_main(EFI_HANDLE image, EFI_SYSTEM_TABLE *st) {
  ST = st; BS = st->BootServices;
  BS->SetWatchdogTimer(0, 0, 0, 0);
  ST->ConOut->ClearScreen(ST->ConOut);
  put("ITE keyboard probe v1 (READ-ONLY: only standard descriptor reads)\n");
  put("Firmware: "); putw(ST->FirmwareVendor); put(" rev "); hex(ST->FirmwareRevision, 8); put("\n");
  int ite = probe_all(1);
  if (!ite) {
    put("\nNo ITE device found yet - asking firmware to connect all drivers and scanning again...\n");
    connect_all();
    BS->Stall(500000);
    ite = probe_all(1);
  }
  put("\nRESULT: ");
  if (ite) { dec(ite); put(" ITE interface(s) found.\n"); }
  else put("no ITE (048D) device visible to firmware.\n");
  save_log(image);
  put("\nPress any key to return (or wait 120 s)...\n");
  EFI_INPUT_KEY k;
  ST->ConIn->Reset(ST->ConIn, 0);
  for (int t = 0; t < 12000; t++) {
    if (!ST->ConIn->ReadKeyStroke(ST->ConIn, &k)) break;
    BS->Stall(10000);
  }
  return EFI_SUCCESS;
}
