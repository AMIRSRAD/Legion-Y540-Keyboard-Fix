
void FUN_CODE_3b43(char param_1)

{
  byte bVar1;
  
  DAT_EXTMEM_0789 = 0;
  DAT_EXTMEM_078a = param_1 != '\0';
  FUN_CODE_3563();
  if (DAT_EXTMEM_0784 == '\0') {
    bVar1 = DAT_EXTMEM_2f40 & 0xfb | 1;
  }
  else {
    bVar1 = DAT_EXTMEM_2f40 | 5;
  }
  DAT_EXTMEM_2f40 = bVar1 | 2;
  return;
}

