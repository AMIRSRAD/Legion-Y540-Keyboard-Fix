
void FUN_CODE_39da(void)

{
  char cVar1;
  
  cVar1 = FUN_CODE_857a(3,DAT_EXTMEM_0dea,DAT_EXTMEM_0de9,DAT_EXTMEM_0de8);
  if (cVar1 == '\0') {
    FUN_CODE_4b29(0);
    DAT_EXTMEM_2f64 = 1;
    DAT_EXTMEM_2f74 = 1;
    DAT_EXTMEM_2f84 = 1;
    FUN_CODE_34df(0x2f94);
    DAT_EXTMEM_2f52 = 0x18;
    FUN_CODE_85b9(1,3,DAT_EXTMEM_0dea,DAT_EXTMEM_0de9,DAT_EXTMEM_0de8);
    return;
  }
  return;
}

