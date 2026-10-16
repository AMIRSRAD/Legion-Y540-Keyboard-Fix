
void FUN_CODE_2c5b(undefined1 param_1,undefined1 param_2,undefined1 param_3,byte param_4,
                  byte param_5,char param_6)

{
  byte bVar1;
  
  DAT_EXTMEM_0779 = param_6;
  DAT_EXTMEM_077a = param_4;
  DAT_EXTMEM_077b = param_5;
  DAT_EXTMEM_077c = param_3;
  DAT_EXTMEM_077d = param_2;
  DAT_EXTMEM_077e = param_1;
  if ((param_6 != '\x01') && (DAT_EXTMEM_0973 != '\0')) {
    if (param_6 == -0x33) {
      FUN_CODE_3812(param_1,param_2,param_3);
      return;
    }
    FUN_CODE_3501(param_1,param_2,param_3,0);
    return;
  }
  if (param_4 == 0) {
    param_4 = param_5 ^ 1;
  }
  if (param_4 == 0) {
    DAT_EXTMEM_0a6d = FUN_CODE_8561(param_1,param_2,param_3);
  }
  else {
    DAT_EXTMEM_0a6d = FUN_CODE_857a(1,param_1,param_2,param_3);
  }
  bVar1 = (DAT_EXTMEM_0a6d & 4) >> 2 |
          (DAT_EXTMEM_0a6d & 2) * '\x02' | (DAT_EXTMEM_0a6d & 1) * '\x02';
  FUN_CODE_6e2a(bVar1,bVar1);
  _9_0 = _8_1 & 1;
  return;
}

