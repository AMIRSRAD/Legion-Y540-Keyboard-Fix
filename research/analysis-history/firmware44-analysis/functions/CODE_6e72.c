
void FUN_CODE_6e72(void)

{
  if ((DAT_EXTMEM_0815 & 1) != 1) {
    if (DAT_EXTMEM_088c != '\0') {
      DAT_EXTMEM_088c = DAT_EXTMEM_088c + -1;
      return;
    }
    if (DAT_EXTMEM_088b == '\x01') {
      DAT_EXTMEM_1806 = 0x4d;
      return;
    }
    if (DAT_EXTMEM_088b == '\x02') {
      DAT_EXTMEM_1806 = 0xff;
      return;
    }
    DAT_EXTMEM_1806 = 0;
  }
  return;
}

