
byte FUN_CODE_3120(undefined1 param_1,undefined1 param_2,undefined1 param_3,byte param_4,
                  byte param_5)

{
  byte bVar1;
  
  bVar1 = DAT_EXTMEM_0775;
  if (DAT_EXTMEM_0775 == 0) {
    bVar1 = DAT_EXTMEM_0776;
  }
  DAT_EXTMEM_0771 = param_5;
  DAT_EXTMEM_0772 = param_3;
  DAT_EXTMEM_0773 = param_2;
  DAT_EXTMEM_0774 = param_1;
  if (bVar1 == 0) {
    FUN_CODE_305f(0,0,1);
    if (((param_4 ^ 0x80) < 0x80) << 7 < '\0') {
      return 0;
    }
    bVar1 = DAT_EXTMEM_0771;
    FUN_CODE_2db4(DAT_EXTMEM_0774,DAT_EXTMEM_0773,DAT_EXTMEM_0772);
    bVar1 = bVar1 | param_4;
    if (bVar1 == 0) {
      bVar1 = FUN_CODE_2eb7(DAT_EXTMEM_0774,DAT_EXTMEM_0773,DAT_EXTMEM_0772,DAT_EXTMEM_0771);
    }
  }
  return bVar1;
}

