
char FUN_CODE_25d9(void)

{
  char cVar1;
  
  if ((DAT_INTMEM_30 < DAT_INTMEM_31 + 1U) << 7 < '\0') {
    DAT_EXTMEM_074c = DAT_INTMEM_31 - DAT_INTMEM_30;
  }
  else {
    DAT_EXTMEM_074c = (DAT_INTMEM_31 + -0x80) - DAT_INTMEM_30;
  }
  cVar1 = DAT_EXTMEM_074c - 0x40;
  if (0x3f < DAT_EXTMEM_074c) {
    FUN_CODE_2105(0);
    cVar1 = FUN_CODE_2127();
    DAT_INTMEM_32 = 0;
    DAT_INTMEM_33 = DAT_INTMEM_33 & 0xf0;
  }
  return cVar1;
}

