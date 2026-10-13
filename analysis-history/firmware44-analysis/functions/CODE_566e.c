
char FUN_CODE_566e(char param_1,byte param_2,undefined1 param_3,char param_4,byte param_5)

{
  byte bVar1;
  
  DAT_EXTMEM_0784 = 0;
  DAT_EXTMEM_0785 = 0;
  DAT_EXTMEM_077f = param_4;
  DAT_EXTMEM_0780 = param_5;
  DAT_EXTMEM_0781 = param_3;
  DAT_EXTMEM_0782 = param_1;
  DAT_EXTMEM_0783 = param_2;
  while (bVar1 = DAT_EXTMEM_0782 - (((DAT_EXTMEM_0785 < DAT_EXTMEM_0783) << 7) >> 7),
        DAT_EXTMEM_0784 < bVar1) {
    *(undefined1 *)
     CONCAT11(DAT_EXTMEM_077f +
              (DAT_EXTMEM_0784 - ((CARRY1(DAT_EXTMEM_0780,DAT_EXTMEM_0785) << 7) >> 7)),
              DAT_EXTMEM_0780 + DAT_EXTMEM_0785) = DAT_EXTMEM_0781;
    DAT_EXTMEM_0785 = DAT_EXTMEM_0785 + 1;
    if (DAT_EXTMEM_0785 == 0) {
      DAT_EXTMEM_0784 = DAT_EXTMEM_0784 + 1;
    }
  }
  return DAT_EXTMEM_0784 - bVar1;
}

