
byte FUN_CODE_3a24(void)

{
  char cVar1;
  byte bVar2;
  
  cVar1 = '\0';
  bVar2 = DAT_EXTMEM_2f44;
  if (((DAT_EXTMEM_2f44 >> 1 & 1) != 1) &&
     (bVar2 = (DAT_EXTMEM_2f45 & 0x50) - 1, (DAT_EXTMEM_2f45 & 0x50) != 0)) {
    DAT_EXTMEM_0768 = 1;
    DAT_EXTMEM_0769 = 0xc;
    DAT_EXTMEM_076a = 0x3f;
    DAT_EXTMEM_076b = 0;
    DAT_EXTMEM_076c = 0;
    DAT_EXTMEM_076d = 0;
    DAT_EXTMEM_076e = 0;
    DAT_EXTMEM_076f = 0;
    FUN_CODE_3201(0,0,0,0);
    bVar2 = cVar1 - 1;
    if (cVar1 != '\0') {
      DAT_EXTMEM_0751 = DAT_EXTMEM_0dd4;
      DAT_EXTMEM_0752 = 1;
      FUN_CODE_3ae1(0x3f,0xc,1,0,cVar1);
      bVar2 = DAT_EXTMEM_0dd4 != '\x01';
      DAT_EXTMEM_0dd4 = bVar2;
    }
  }
  return bVar2;
}

