
void FUN_CODE_512d(void)

{
  if ((DAT_EXTMEM_2f52 >> 3 & 1) != 0) {
    DAT_EXTMEM_2f52 = 8;
    FUN_CODE_86d6(0xf,0,DAT_EXTMEM_0dea,DAT_EXTMEM_0de9,DAT_EXTMEM_0de8);
    FUN_CODE_85b9(1,0x11);
  }
  return;
}

