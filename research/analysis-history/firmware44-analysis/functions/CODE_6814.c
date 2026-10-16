
void FUN_CODE_6814(char param_1,undefined1 param_2)

{
  DAT_EXTMEM_1c21 = 0x20;
  DAT_EXTMEM_1c1d = 0xf;
  DAT_EXTMEM_1c19 = param_2;
  if (param_1 != '\0') {
    DAT_EXTMEM_1c44 = param_1 + -0x80;
  }
  DAT_EXTMEM_1c12 = 0;
  DAT_EXTMEM_1c11 = 0xff;
  DAT_EXTMEM_1c1c = 0xff;
  return;
}

