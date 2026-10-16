
byte FUN_CODE_258e(void)

{
  byte bVar1;
  byte bVar2;
  byte bVar3;
  
  bVar3 = DAT_EXTMEM_1d33;
  if ((DAT_EXTMEM_1d33 >> 2 & 1) != 0) {
    bVar2 = 0;
    while (bVar1 = (0xef < DAT_EXTMEM_0081 ^ 0x80U) - (((bVar2 < DAT_EXTMEM_0081 + 0x10) << 7) >> 7)
          , bVar3 = 0x80 - bVar1, 0x80 < bVar1) {
      if (*(byte *)(bVar2 + 0x6d) != 0) {
        _6_7 = 1;
        return *(byte *)(bVar2 + 0x6d);
      }
      bVar2 = bVar2 + 1;
    }
  }
  return bVar3;
}

