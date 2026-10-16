
undefined1 FUN_CODE_3501(undefined1 param_1,undefined1 param_2,undefined1 param_3)

{
  char cVar1;
  
  FUN_CODE_5600(param_1,0,0x10,param_3,param_2,0xc,0x2f);
  if (DAT_EXTMEM_0c2e == '\0') {
    cVar1 = '0';
    FUN_CODE_56c9(0,0xf,0xc,0x1f,0xc);
    if (cVar1 == '\0') {
      DAT_EXTMEM_0c2e = '\x01';
    }
  }
  else if (DAT_EXTMEM_0c30 == '\x06') {
    FUN_CODE_3335();
  }
  else if (DAT_EXTMEM_0c30 == '\b') {
    FUN_CODE_348d();
  }
  else if (DAT_EXTMEM_0c30 == '\t') {
    FUN_CODE_7f2f();
    FUN_CODE_31ec();
  }
  else if (5 < DAT_EXTMEM_0c30 - 5U) {
    DAT_EXTMEM_0c2e = '\0';
  }
  return 0;
}

