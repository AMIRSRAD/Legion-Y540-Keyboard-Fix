
void FUN_CODE_76f5(char param_1)

{
  DAT_EXTMEM_0754 = param_1;
  DAT_EXTMEM_0756 = FUN_CODE_8561();
  FUN_CODE_7b31(0,0,DAT_EXTMEM_0756);
  if (((DAT_INTMEM_8c >> 6 & 1) == 1) || (DAT_EXTMEM_08af == '\x01')) {
    if ((DAT_EXTMEM_0756 == '%') && (DAT_EXTMEM_0754 != '\x02')) {
      FUN_CODE_2d4a(DAT_EXTMEM_0754 == '\x01',0x40,2);
    }
    if (DAT_EXTMEM_084a != '\0') {
      if ((DAT_EXTMEM_0756 == '\x1c') && (DAT_EXTMEM_0754 == '\0')) {
        if ((DAT_EXTMEM_088d >> 6 & 1) != 0) {
          FUN_CODE_1b56(1,0x11);
          DAT_EXTMEM_088d = DAT_EXTMEM_088d & 0xbf;
        }
        FUN_CODE_1b56(0,0x14);
        FUN_CODE_1b56(0,0x1c);
        FUN_CODE_1b56(1,0x1c);
        DAT_EXTMEM_088d = DAT_EXTMEM_088d | 0x20;
      }
      if ((DAT_EXTMEM_0756 == '+') && (DAT_EXTMEM_0754 == '\0')) {
        if ((DAT_EXTMEM_088d >> 6 & 1) != 0) {
          FUN_CODE_1b56(1,0x11);
          DAT_EXTMEM_088d = DAT_EXTMEM_088d & 0xbf;
        }
        FUN_CODE_1b56(0,0x14);
        FUN_CODE_1b56(0,0x2b);
        FUN_CODE_1b56(1,0x2b);
        DAT_EXTMEM_088d = DAT_EXTMEM_088d | 0x20;
      }
      if ((DAT_EXTMEM_0756 == '\x1a') && (DAT_EXTMEM_0754 == '\0')) {
        if ((DAT_EXTMEM_088d >> 6 & 1) != 0) {
          FUN_CODE_1b56(1,0x11);
          DAT_EXTMEM_088d = DAT_EXTMEM_088d & 0xbf;
        }
        FUN_CODE_1b56(0,0x14);
        FUN_CODE_1b56(0,0x1a);
        FUN_CODE_1b56(1,0x1a);
        DAT_EXTMEM_088d = DAT_EXTMEM_088d | 0x20;
      }
      if ((DAT_EXTMEM_0756 == '\"') && (DAT_EXTMEM_0754 == '\0')) {
        if ((DAT_EXTMEM_088d >> 6 & 1) != 0) {
          FUN_CODE_1b56(1,0x11);
          DAT_EXTMEM_088d = DAT_EXTMEM_088d & 0xbf;
        }
        FUN_CODE_1b56(0,0x14);
        FUN_CODE_1b56(0,0x22);
        FUN_CODE_1b56(1,0x22);
        DAT_EXTMEM_088d = DAT_EXTMEM_088d | 0x20;
      }
      if ((DAT_EXTMEM_0756 == '!') && (DAT_EXTMEM_0754 == '\0')) {
        if ((DAT_EXTMEM_088d >> 6 & 1) != 0) {
          FUN_CODE_1b56(1,0x11);
          DAT_EXTMEM_088d = DAT_EXTMEM_088d & 0xbf;
        }
        FUN_CODE_1b56(0,0x14);
        FUN_CODE_1b56(0,0x21);
        FUN_CODE_1b56(1,0x21);
        DAT_EXTMEM_088d = DAT_EXTMEM_088d | 0x20;
      }
      if ((DAT_EXTMEM_0756 == '*') && (DAT_EXTMEM_0754 == '\0')) {
        if ((DAT_EXTMEM_088d >> 6 & 1) != 0) {
          FUN_CODE_1b56(1,0x11);
          DAT_EXTMEM_088d = DAT_EXTMEM_088d & 0xbf;
        }
        FUN_CODE_1b56(0,0x14);
        FUN_CODE_1b56(0,0x2a);
        FUN_CODE_1b56(1,0x2a);
        DAT_EXTMEM_088d = DAT_EXTMEM_088d | 0x20;
      }
      if ((DAT_EXTMEM_0756 == '\x1d') && (DAT_EXTMEM_0754 == '\0')) {
        if ((DAT_EXTMEM_088d >> 6 & 1) != 0) {
          FUN_CODE_1b56(1,0x11);
          DAT_EXTMEM_088d = DAT_EXTMEM_088d & 0xbf;
        }
        FUN_CODE_1b56(0,0x14);
        FUN_CODE_1b56(0,0x1d);
        FUN_CODE_1b56(1,0x1d);
        DAT_EXTMEM_088d = DAT_EXTMEM_088d | 0x20;
      }
      if ((DAT_EXTMEM_0756 == '5') && (DAT_EXTMEM_0754 == '\0')) {
        if ((DAT_EXTMEM_088d >> 6 & 1) != 0) {
          FUN_CODE_1b56(1,0x11);
          DAT_EXTMEM_088d = DAT_EXTMEM_088d & 0xbf;
        }
        FUN_CODE_1b56(0,0x14);
        FUN_CODE_1b56(0,0x35);
        FUN_CODE_1b56(1,0x35);
        DAT_EXTMEM_088d = DAT_EXTMEM_088d | 0x20;
      }
    }
  }
  return;
}

