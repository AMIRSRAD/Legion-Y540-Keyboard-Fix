
byte FUN_CODE_305f(undefined1 param_1)

{
  byte bVar1;
  
  DAT_EXTMEM_0777 = param_1;
  bVar1 = DAT_INTMEM_30 ^ DAT_INTMEM_31;
  if ((bVar1 != 0) || (bVar1 = DAT_EXTMEM_0a84 ^ DAT_EXTMEM_0a85, bVar1 != 0)) {
    return bVar1;
  }
  if ((DAT_EXTMEM_0740 < (byte)-(((DAT_EXTMEM_0741 == '\0') << 7) >> 7)) << 7 < '\0') {
    return 0;
  }
  if (DAT_EXTMEM_073d == '\0') {
    return 0xff;
  }
  return DAT_EXTMEM_073d - 1;
}

