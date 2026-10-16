
void FUN_CODE_1b56(char param_1,char param_2)

{
  DAT_EXTMEM_0790 = param_2;
  DAT_EXTMEM_0791 = param_1;
  FUN_CODE_21f9();
  if ((param_2 == '\0') || (DAT_EXTMEM_0791 != '\x02')) {
    if (DAT_EXTMEM_0791 == '\x01') {
      FUN_CODE_1f93(0xf0);
    }
    FUN_CODE_1f93(DAT_EXTMEM_0790);
  }
  return;
}

