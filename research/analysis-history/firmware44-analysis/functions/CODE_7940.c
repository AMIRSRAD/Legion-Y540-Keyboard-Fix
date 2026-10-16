
void FUN_CODE_7940(char param_1,char param_2,char param_3)

{
  DAT_EXTMEM_074e = param_3;
  DAT_EXTMEM_074f = param_2;
  if (param_1 == '\x01') {
    DAT_EXTMEM_0894 = 0;
    if ((param_3 == '\x03') && (param_2 == '\r')) {
      DAT_EXTMEM_0893 = 200;
      DAT_EXTMEM_0892 = 0;
    }
  }
  else {
    DAT_EXTMEM_0894 = 1;
    if ((param_3 == '\x03') && (param_2 == '\r')) {
      FUN_CODE_7ac1(8);
      DAT_EXTMEM_1603 = DAT_EXTMEM_1603 | 2;
      return;
    }
  }
  return;
}

