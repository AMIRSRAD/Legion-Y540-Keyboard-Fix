
void FUN_CODE_4b88(void)

{
  DAT_EXTMEM_2fe0 = 2;
  FUN_CODE_0c96(1);
  DAT_EXTMEM_2fe4 = DAT_EXTMEM_2fe4 & 0xef;
  DAT_EXTMEM_2fe8 = DAT_EXTMEM_2fe8 & 0xef;
  DAT_EXTMEM_2fe0 = 0;
  DAT_EXTMEM_2f50 = 0x71;
  DAT_EXTMEM_2f52 = 0xd;
  DAT_EXTMEM_2f53 = 0xd;
  FUN_CODE_34df(DAT_EXTMEM_1106 | 0x40);
  DAT_EXTMEM_0dd2 = 1;
  return;
}

