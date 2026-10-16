
void FUN_CODE_0fc9(char param_1,char param_2)

{
  char cVar1;
  
  DAT_INTMEM_87 = '\x06';
  DAT_INTMEM_88 = '\0';
  cVar1 = '\0';
  DAT_INTMEM_55 = param_1;
  DAT_INTMEM_56 = param_2;
  do {
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
    cVar1 = cVar1 + '\x01';
  } while (cVar1 != '\0');
  return;
}

