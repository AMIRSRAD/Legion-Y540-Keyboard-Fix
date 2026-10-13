
void FUN_CODE_3a8e(char param_1,char param_2,char param_3,char param_4)

{
  char cVar1;
  
  cVar1 = DAT_EXTMEM_2f42;
  DAT_EXTMEM_0796 = param_3;
  DAT_EXTMEM_0797 = param_2;
  DAT_EXTMEM_0798 = param_1;
  if ((param_1 != '\0' || param_2 != '\0') || param_3 != '\0') {
    FUN_CODE_85a7(0,param_1);
  }
  if (param_4 == cVar1) {
    return;
  }
  if ((cVar1 == '\0') &&
     ((DAT_EXTMEM_0798 != '\0' || DAT_EXTMEM_0797 != '\0') || DAT_EXTMEM_0796 != '\0')) {
    FUN_CODE_85a7(1,DAT_EXTMEM_0798,0);
  }
  return;
}

