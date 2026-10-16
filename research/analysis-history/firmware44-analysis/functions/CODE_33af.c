
void FUN_CODE_33af(undefined1 param_1,undefined1 param_2,undefined1 param_3)

{
  DAT_EXTMEM_077c = param_3;
  DAT_EXTMEM_077d = param_2;
  DAT_EXTMEM_077e = param_1;
  if (DAT_EXTMEM_0c2e == '\0') {
    FUN_CODE_566e(0,0xf,0xff,0xc,0x30);
  }
  else if (DAT_EXTMEM_0c30 == '\a') {
    FUN_CODE_3437();
  }
  else if (DAT_EXTMEM_0c30 == '\x05') {
    FUN_CODE_3701();
  }
  FUN_CODE_5600(0,0x10,0xc,0x2f,DAT_EXTMEM_077d,DAT_EXTMEM_077e);
  return;
}

