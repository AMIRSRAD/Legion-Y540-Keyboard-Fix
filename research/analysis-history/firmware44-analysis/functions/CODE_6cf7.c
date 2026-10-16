
void FUN_CODE_6cf7(void)

{
  DAT_EXTMEM_1106 = DAT_EXTMEM_1106 & 0xbf;
  nop();
  nop();
  nop();
  nop();
  FUN_CODE_4f66();
  DAT_EXTMEM_1106 = DAT_EXTMEM_1106 | 0x40;
  return;
}

