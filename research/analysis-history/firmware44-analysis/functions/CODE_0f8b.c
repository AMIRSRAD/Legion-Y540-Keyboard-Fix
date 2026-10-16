
undefined1 FUN_CODE_0f8b(char param_1,char param_2,char param_3,char param_4,char param_5)

{
  DAT_INTMEM_55 = param_4;
  DAT_INTMEM_56 = param_5;
  DAT_INTMEM_87 = param_1;
  DAT_INTMEM_88 = param_2;
  for (; param_3 != '\0'; param_3 = param_3 + -1) {
    *(undefined1 *)CONCAT11(DAT_INTMEM_87,DAT_INTMEM_88) =
         *(undefined1 *)CONCAT11(DAT_INTMEM_55,DAT_INTMEM_56);
    DAT_INTMEM_88 = DAT_INTMEM_88 + '\x01';
    if (DAT_INTMEM_88 == '\0') {
      DAT_INTMEM_87 = DAT_INTMEM_87 + '\x01';
    }
    DAT_INTMEM_56 = DAT_INTMEM_56 + '\x01';
    if (DAT_INTMEM_56 == '\0') {
      DAT_INTMEM_55 = DAT_INTMEM_55 + '\x01';
    }
  }
  return 0xff;
}

