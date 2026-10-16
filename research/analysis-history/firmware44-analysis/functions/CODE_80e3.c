
void FUN_CODE_80e3(void)

{
  DAT_EXTMEM_1b00 = DAT_EXTMEM_1b00 | 0x20;
  DAT_EXTMEM_1b04 = 0x20;
  DAT_EXTMEM_1114 = 0x20;
  DAT_EXTMEM_1115 = DAT_EXTMEM_1115 | 0x20;
  return;
}

