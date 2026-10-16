
char FUN_CODE_1f4e(void)

{
  byte bVar1;
  char cVar2;
  
  cVar2 = ((DAT_EXTMEM_00f7 == '\0') << 7) >> 7;
  if ((byte)-cVar2 <= DAT_EXTMEM_00f6) {
    return DAT_EXTMEM_00f6 + cVar2;
  }
  if (DAT_INTMEM_30 == DAT_INTMEM_31) {
    cVar2 = '\0';
  }
  else {
    bVar1 = DAT_INTMEM_30 + 1;
    cVar2 = DAT_INTMEM_30 + 0x81;
    DAT_INTMEM_30 = bVar1;
    if (0x7f < bVar1) {
      DAT_INTMEM_30 = 0;
    }
  }
  return cVar2;
}

