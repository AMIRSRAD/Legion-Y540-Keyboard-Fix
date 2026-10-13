
void FUN_CODE_26e2(char param_1)

{
  char cVar1;
  
  DAT_EXTMEM_1106 = DAT_EXTMEM_1106 & 0xbf;
  nop();
  nop();
  nop();
  nop();
  cVar1 = DAT_EXTMEM_00f4;
  if (DAT_EXTMEM_00f4 == '\0') {
    cVar1 = DAT_EXTMEM_00f5;
  }
  if (cVar1 == '\0') {
    FUN_CODE_4bc4();
  }
  else {
    FUN_CODE_512d();
  }
  FUN_CODE_6d0d();
  FUN_CODE_36eb();
  if (param_1 != '\0') {
    FUN_CODE_510d(2);
  }
  DAT_EXTMEM_1106 = DAT_EXTMEM_1106 | 0x40;
  return;
}

