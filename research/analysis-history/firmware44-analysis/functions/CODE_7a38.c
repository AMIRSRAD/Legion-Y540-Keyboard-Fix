
void FUN_CODE_7a38(void)

{
  if ((DAT_EXTMEM_08a1 & 1) != 0) {
    if ((DAT_EXTMEM_08a0 < 6) << 7 < '\0') {
      DAT_EXTMEM_08a0 = DAT_EXTMEM_08a0 + 1;
    }
    else {
      DAT_EXTMEM_08a0 = 0;
      FUN_CODE_1b56(0,0x14);
      FUN_CODE_1b56(0,0x12);
      FUN_CODE_1b56(0,0x50);
      DAT_EXTMEM_08a1 = DAT_EXTMEM_08a1 & 0xfe | 2;
    }
  }
  if ((DAT_EXTMEM_08a1 >> 1 & 1) != 0) {
    if (2 < DAT_EXTMEM_08a0) {
      DAT_EXTMEM_08a0 = 0;
      FUN_CODE_1b56(1,0x14);
      FUN_CODE_1b56(1,0x12);
      FUN_CODE_1b56(1,0x50);
      DAT_EXTMEM_08a1 = DAT_EXTMEM_08a1 & 0xfd;
      return;
    }
    DAT_EXTMEM_08a0 = DAT_EXTMEM_08a0 + 1;
  }
  return;
}

