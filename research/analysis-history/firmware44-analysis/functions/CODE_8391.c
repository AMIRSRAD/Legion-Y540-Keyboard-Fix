
void FUN_CODE_8391(void)

{
  byte bVar1;
  
  if (DAT_EXTMEM_0928 != '\0') {
    DAT_EXTMEM_0901 = (DAT_EXTMEM_0918 & 1) != 0;
    DAT_EXTMEM_0902 = (DAT_EXTMEM_0918 >> 1 & 1) != 0;
    if ((bool)DAT_EXTMEM_0902) {
      DAT_EXTMEM_08ae = 4;
    }
    if ((DAT_EXTMEM_0918 >> 6 & 1) == 0) {
      DAT_EXTMEM_0e10 = 0;
    }
    else {
      DAT_EXTMEM_0e10 = 0x14;
    }
    FUN_CODE_7994();
    DAT_EXTMEM_084a = (char)DAT_EXTMEM_0918 < '\0';
    bVar1 = 0;
    do {
      *(undefined1 *)CONCAT11('\t' - (((0xe7 < bVar1) << 7) >> 7),bVar1 + 0x18) =
           *(undefined1 *)CONCAT11('\t' - (((0xe6 < bVar1) << 7) >> 7),bVar1 + 0x19);
      bVar1 = bVar1 + 1;
    } while (bVar1 != 7);
    DAT_EXTMEM_091f = 0;
    DAT_EXTMEM_0928 = DAT_EXTMEM_0928 + -1;
  }
  return;
}

