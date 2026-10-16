
void FUN_CODE_50ac(void)

{
  DAT_EXTMEM_2033 = DAT_EXTMEM_2033 | 0x80;
  DAT_EXTMEM_1b02 = DAT_EXTMEM_1b02 & 0xbf | 0x80;
  DAT_EXTMEM_1b06 = 0x80;
  DAT_EXTMEM_111c = 0x80;
  DAT_EXTMEM_1b0a = DAT_EXTMEM_1b0a | 0xc0;
  DAT_EXTMEM_0de8 = 1;
  DAT_EXTMEM_0de9 = 0xd;
  DAT_EXTMEM_0dea = 0xd5;
  FUN_CODE_4b29(0);
  FUN_CODE_4b88();
  return;
}

