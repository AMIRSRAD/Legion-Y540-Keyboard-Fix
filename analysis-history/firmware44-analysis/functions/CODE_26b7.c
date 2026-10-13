
void FUN_CODE_26b7(void)

{
  DAT_EXTMEM_0746 = '\0';
  if (DAT_EXTMEM_00cf != '\0') {
    DAT_EXTMEM_00cf = '\0';
    FUN_CODE_26e2();
    DAT_EXTMEM_00df = 1;
    if (DAT_EXTMEM_0746 == '\0') {
      FUN_CODE_6d7b();
    }
    DAT_EXTMEM_00df = 0;
    DAT_EXTMEM_00da = DAT_EXTMEM_00da + '\x01';
  }
  return;
}

