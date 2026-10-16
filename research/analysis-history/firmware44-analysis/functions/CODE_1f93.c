
undefined1 FUN_CODE_1f93(undefined1 param_1)

{
  DAT_EXTMEM_0794 = 1;
  DAT_EXTMEM_0793 = param_1;
  if (DAT_EXTMEM_08ad != '\0') {
    FUN_CODE_4f75();
  }
  *(undefined1 *)CONCAT11(4,DAT_INTMEM_31) = DAT_EXTMEM_0793;
  DAT_INTMEM_31 = DAT_INTMEM_31 + 1;
  if (0x7f < DAT_INTMEM_31) {
    DAT_INTMEM_31 = 0;
  }
  if (DAT_INTMEM_31 == DAT_INTMEM_30) {
    DAT_INTMEM_31 = DAT_INTMEM_32;
    *(undefined1 *)CONCAT11(4,DAT_INTMEM_32) = 0;
    DAT_EXTMEM_0794 = 0;
  }
  return DAT_EXTMEM_0794;
}

