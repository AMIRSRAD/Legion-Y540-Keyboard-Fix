
void FUN_CODE_3c58(undefined1 param_1,undefined1 param_2,undefined1 param_3,byte param_4,
                  byte param_5,char param_6)

{
  undefined1 uVar1;
  
  DAT_EXTMEM_0763 = param_3;
  DAT_EXTMEM_0764 = param_2;
  DAT_EXTMEM_0765 = param_1;
  FUN_CODE_85b9(0,0xb,DAT_EXTMEM_0dea,DAT_EXTMEM_0de9,DAT_EXTMEM_0de8);
  FUN_CODE_85b9(2,1);
  if (param_5 != 0 || param_4 != 0) {
    if ((byte)-(((param_5 < 0x40) << 7) >> 7) <= param_4) {
      param_5 = 0x40;
    }
    FUN_CODE_85b9(param_5,0xb,DAT_EXTMEM_0dea,DAT_EXTMEM_0de9,DAT_EXTMEM_0de8);
    uVar1 = FUN_CODE_857a(0xb,DAT_EXTMEM_0dea,DAT_EXTMEM_0de9,DAT_EXTMEM_0de8);
    FUN_CODE_3c3e(DAT_EXTMEM_0765,DAT_EXTMEM_0764,DAT_EXTMEM_0763,uVar1);
    if (param_6 == '\0') {
      return;
    }
  }
  return;
}

