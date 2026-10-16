
void FUN_CODE_13d4(undefined1 param_1,undefined1 param_2,undefined1 param_3)

{
  DAT_EXTMEM_0095 = param_3;
  DAT_EXTMEM_0096 = param_2;
  DAT_EXTMEM_0097 = param_1;
  FUN_CODE_059d();
  FUN_CODE_0fc9(0x10,0xdb);
  DAT_EXTMEM_1000 = DAT_EXTMEM_1000 | 0x80;
  FUN_CODE_0f7f();
  DAT_EXTMEM_1000 = DAT_EXTMEM_1000 & 0x7f;
  FUN_CODE_05a4();
  return;
}

