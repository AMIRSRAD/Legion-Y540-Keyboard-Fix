
void FUN_CODE_13fe(undefined1 param_1,undefined1 param_2,undefined1 param_3,undefined1 param_4)

{
  DAT_EXTMEM_0097 = DAT_EXTMEM_0786;
  DAT_EXTMEM_0095 = param_2;
  DAT_EXTMEM_0096 = param_1;
  DAT_EXTMEM_009b = param_3;
  DAT_EXTMEM_009c = param_4;
  FUN_CODE_059d();
  FUN_CODE_0fc9(0x12,100);
  DAT_EXTMEM_1000 = DAT_EXTMEM_1000 | 0x80;
  FUN_CODE_0f7f();
  DAT_EXTMEM_1000 = DAT_EXTMEM_1000 & 0x7f;
  FUN_CODE_05a4();
  return;
}

