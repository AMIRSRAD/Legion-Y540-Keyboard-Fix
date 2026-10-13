
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

char FUN_CODE_2cf0(byte param_1,char param_2)

{
  char cVar1;
  
  cVar1 = param_2 + -1;
  if (param_2 == '\0') {
    _DAT_EXTMEM_0740 = (ushort)param_1 * 4;
    cVar1 = (char)_DAT_EXTMEM_0740;
  }
  return cVar1;
}

