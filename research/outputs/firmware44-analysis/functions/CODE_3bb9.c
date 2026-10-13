
void FUN_CODE_3bb9(undefined1 param_1,undefined1 param_2,undefined1 param_3,byte param_4,
                  byte param_5)

{
  char cVar1;
  
  DAT_EXTMEM_076e = 0;
  DAT_EXTMEM_076b = param_3;
  DAT_EXTMEM_076c = param_2;
  DAT_EXTMEM_076d = param_1;
  FUN_CODE_85b9(1,1,DAT_EXTMEM_0dea,DAT_EXTMEM_0de9,DAT_EXTMEM_0de8);
  if (param_5 != 0 || param_4 != 0) {
    DAT_EXTMEM_076e = param_5;
    if ((byte)-(((param_5 < 0x40) << 7) >> 7) <= param_4) {
      DAT_EXTMEM_076e = 0x40;
    }
    FUN_CODE_85b9(DAT_EXTMEM_076e,0xb);
    cVar1 = '?';
    FUN_CODE_5600(0,DAT_EXTMEM_076e,DAT_EXTMEM_076c,DAT_EXTMEM_076d,0xc);
    DAT_EXTMEM_0784 =
         FUN_CODE_857a(0xc,DAT_EXTMEM_0dea,DAT_EXTMEM_0de9,DAT_EXTMEM_0de8,DAT_EXTMEM_076e);
    FUN_CODE_3b43(0x3f,0xc,1);
    if (cVar1 == '\0') {
      return;
    }
  }
  return;
}

