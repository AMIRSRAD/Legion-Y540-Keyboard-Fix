
void FUN_CODE_6ee1(void)

{
  if ((char)DAT_EXTMEM_0897 < '\0') {
    if ((DAT_EXTMEM_0897 < 0x85) << 7 < '\0') {
      DAT_EXTMEM_0897 = DAT_EXTMEM_0897 + 1;
    }
    else {
      FUN_CODE_7ac1(DAT_EXTMEM_0897 + 0x7b,3);
      DAT_EXTMEM_0897 = 0x80;
    }
  }
  if ((char)DAT_EXTMEM_0898 < '\0') {
    if (0x84 < DAT_EXTMEM_0898) {
      FUN_CODE_7ac1(DAT_EXTMEM_0898 + 0x7b,4);
      DAT_EXTMEM_0898 = 0x80;
      return;
    }
    DAT_EXTMEM_0898 = DAT_EXTMEM_0898 + 1;
  }
  return;
}

