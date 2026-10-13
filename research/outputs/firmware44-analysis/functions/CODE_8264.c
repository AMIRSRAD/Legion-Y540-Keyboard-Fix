
void FUN_CODE_8264(void)

{
  char cVar1;
  
  if (DAT_EXTMEM_0800 == '3') {
    if ((DAT_EXTMEM_1601 >> 6 & 1) == 1) {
      cVar1 = '\0';
    }
    else {
      cVar1 = -0x80;
    }
    if ((-1 < cVar1) && ((DAT_EXTMEM_1601 >> 5 & 1) != 1)) {
      DAT_EXTMEM_0800 = 0x30;
      return;
    }
    if (((DAT_EXTMEM_1601 >> 6 & 1) != 1) && ((DAT_EXTMEM_1601 >> 5 & 1) != 1)) {
      DAT_EXTMEM_0800 = 5;
      return;
    }
  }
  else if (DAT_EXTMEM_0800 == 'U') {
    if ((DAT_EXTMEM_1601 >> 6 & 1) == 1) {
      cVar1 = '\0';
    }
    else {
      cVar1 = -0x80;
    }
    if ((-1 < cVar1) && ((DAT_EXTMEM_1601 >> 5 & 1) != 1)) {
      DAT_EXTMEM_0800 = 'P';
      DAT_EXTMEM_0891 = 0x32;
    }
  }
  else if (DAT_EXTMEM_0800 == '\x10') {
    if (((DAT_EXTMEM_1601 >> 5 & 1) != 1) && ((DAT_EXTMEM_1601 >> 6 & 1) != 1)) {
      DAT_EXTMEM_0800 = 5;
      return;
    }
    if ((DAT_EXTMEM_1601 >> 6 & 1) != 1) {
      if ((DAT_EXTMEM_1601 >> 5 & 1) == 1) {
        cVar1 = '\0';
      }
      else {
        cVar1 = -0x80;
      }
      if (-1 < cVar1) {
        DAT_EXTMEM_0800 = 3;
        return;
      }
    }
  }
  return;
}

