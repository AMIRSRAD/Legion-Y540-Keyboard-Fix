
void FUN_CODE_08c8(void)

{
  bool bVar1;
  char cVar2;
  byte bVar3;
  
  if ((byte)-(((DAT_EXTMEM_00f5 == '\0') << 7) >> 7) <= DAT_EXTMEM_00f4) {
    bVar1 = DAT_EXTMEM_00f5 != '\0';
    DAT_EXTMEM_00f5 = DAT_EXTMEM_00f5 + -1;
    DAT_EXTMEM_00f4 = DAT_EXTMEM_00f4 + (-1 - ((bVar1 << 7) >> 7));
  }
  if ((byte)-(((DAT_EXTMEM_00f9 == '\0') << 7) >> 7) <= DAT_EXTMEM_00f8) {
    bVar1 = DAT_EXTMEM_00f9 != '\0';
    DAT_EXTMEM_00f9 = DAT_EXTMEM_00f9 + -1;
    DAT_EXTMEM_00f8 = DAT_EXTMEM_00f8 + (-1 - ((bVar1 << 7) >> 7));
  }
  cVar2 = ((DAT_EXTMEM_00f7 == '\0') << 7) >> 7;
  bVar3 = DAT_EXTMEM_00f6 + cVar2;
  if ((byte)-cVar2 <= DAT_EXTMEM_00f6) {
    bVar1 = DAT_EXTMEM_00f7 != '\0';
    DAT_EXTMEM_00f7 = DAT_EXTMEM_00f7 + -1;
    bVar3 = DAT_EXTMEM_00f6 + (-1 - ((bVar1 << 7) >> 7));
    DAT_EXTMEM_00f6 = bVar3;
  }
  FUN_CODE_6ee1(bVar3);
  return;
}

