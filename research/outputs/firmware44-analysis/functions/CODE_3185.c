
char FUN_CODE_3185(char param_1)

{
  if (param_1 == '\x02') {
    param_1 = '\0';
    if (DAT_EXTMEM_00d7 != '\0') {
      return DAT_EXTMEM_00d7;
    }
  }
  return param_1;
}

