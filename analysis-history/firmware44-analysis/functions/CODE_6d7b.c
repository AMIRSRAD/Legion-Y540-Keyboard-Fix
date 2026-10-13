
void FUN_CODE_6d7b(void)

{
  if (DAT_EXTMEM_00d6 == '\x01') {
    DAT_EXTMEM_00d6 = 2;
    return;
  }
  if (DAT_EXTMEM_00d6 != '\x02') {
    if (DAT_EXTMEM_00d6 == '\0') {
      FUN_CODE_6cb3();
      DAT_EXTMEM_00d6 = 1;
      return;
    }
    DAT_EXTMEM_00d6 = 0;
    return;
  }
  FUN_CODE_6cf7();
  return;
}

