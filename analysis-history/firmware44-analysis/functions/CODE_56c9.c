
byte FUN_CODE_56c9(char param_1,byte param_2,char param_3,byte param_4,char param_5,byte param_6)

{
  byte bVar1;
  
  DAT_EXTMEM_077f = param_5;
  DAT_EXTMEM_0780 = param_6;
  DAT_EXTMEM_0781 = param_3;
  DAT_EXTMEM_0782 = param_4;
  DAT_EXTMEM_0783 = param_1;
  DAT_EXTMEM_0784 = param_2;
  DAT_EXTMEM_0785 = 0;
  DAT_EXTMEM_0786 = 0;
  while( true ) {
    bVar1 = param_1 - (((DAT_EXTMEM_0786 < param_2) << 7) >> 7);
    if (bVar1 <= DAT_EXTMEM_0785) {
      return DAT_EXTMEM_0785 - bVar1;
    }
    bVar1 = *(byte *)CONCAT11(param_5 + (DAT_EXTMEM_0785 -
                                        ((CARRY1(param_6,DAT_EXTMEM_0786) << 7) >> 7)),
                              param_6 + DAT_EXTMEM_0786) ^
            *(byte *)CONCAT11(param_3 + (DAT_EXTMEM_0785 -
                                        ((CARRY1(param_4,DAT_EXTMEM_0786) << 7) >> 7)),
                              param_4 + DAT_EXTMEM_0786);
    if (bVar1 != 0) break;
    DAT_EXTMEM_0786 = DAT_EXTMEM_0786 + 1;
    if (DAT_EXTMEM_0786 == 0) {
      DAT_EXTMEM_0785 = DAT_EXTMEM_0785 + 1;
    }
  }
  return bVar1;
}

