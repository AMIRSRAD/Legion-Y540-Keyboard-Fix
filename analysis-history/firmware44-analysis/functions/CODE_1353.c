
void FUN_CODE_1353(void)

{
  FUN_CODE_059d();
  FUN_CODE_0fc9(0x11,0x6d);
  DAT_EXTMEM_1000 = DAT_EXTMEM_1000 | 0x80;
  FUN_CODE_0f7f();
  DAT_EXTMEM_1000 = DAT_EXTMEM_1000 & 0x7f;
  FUN_CODE_05a4();
  return;
}

