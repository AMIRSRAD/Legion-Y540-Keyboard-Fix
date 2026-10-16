
/* WARNING: Instruction at (CODE,0x35b8) overlaps instruction at (CODE,0x35b6)
    */

byte FUN_CODE_3601(undefined1 param_1,char *param_2,undefined1 param_3,undefined1 param_4,
                  byte param_5,byte param_6)

{
  byte bVar1;
  char cVar2;
  char *pcVar3;
  
  DAT_EXTMEM_0779 = 0;
  DAT_EXTMEM_0763 = param_4;
  DAT_EXTMEM_0764 = param_3;
  DAT_EXTMEM_0765 = param_2;
  DAT_EXTMEM_0766 = param_5;
  if (DAT_EXTMEM_0767 == '\x01') {
    FUN_CODE_8850(0x769);
    nop();
    nop();
    while( true ) {
      UNK_SFR_ff = uINTMEM7a;
      **(byte **)CONCAT11('\r' - (((0x3aU < (byte)(DAT_EXTMEM_0789 * '\b')) << 7) >> 7),
                          DAT_EXTMEM_0789 * '\b' - 0x3b) = param_6;
      DAT_EXTMEM_078b = DAT_EXTMEM_078b + 1;
      if (DAT_EXTMEM_0788 <= DAT_EXTMEM_078b) break;
      param_6 = FUN_CODE_857a(DAT_EXTMEM_078b,DAT_EXTMEM_0787,DAT_EXTMEM_0786,DAT_EXTMEM_0785);
    }
    return DAT_EXTMEM_078b - DAT_EXTMEM_0788;
  }
  pcVar3 = (char *)0x769;
  cVar2 = FUN_CODE_8850();
  nop();
  nop();
  if (cVar2 + param_6 != 0) {
    *param_2 = *param_2 + '\x01';
    cVar2 = FUN_CODE_8850(cVar2 + param_6 ^ param_5);
    nop();
    nop();
    bVar1 = P1;
    P1 = bVar1 ^ cVar2 + param_6;
    *param_2 = *param_2 + '\x01';
    FUN_CODE_3312();
    nop();
    nop();
    bVar1 = P1;
    P1 = bVar1 ^ 7;
    BANK2_R2 = 0x88;
    nop();
    DAT_INTMEM_50 = param_1;
    *param_2 = *param_2 + '\x01';
    while ((cVar2 = *pcVar3, *pcVar3 = cVar2 + -1, cVar2 != '\0' &&
           ((*(char *)CONCAT11(DAT_EXTMEM_076f,DAT_EXTMEM_0770) != '\0' ||
            (*(char *)CONCAT11(DAT_EXTMEM_0773,DAT_EXTMEM_0774) != '\0'))))) {
      FUN_CODE_85b9(*(undefined1 *)CONCAT11(DAT_EXTMEM_076b,DAT_EXTMEM_076c),DAT_EXTMEM_0779,
                    DAT_EXTMEM_0765,DAT_EXTMEM_0764,DAT_EXTMEM_0763);
      DAT_EXTMEM_0779 = DAT_EXTMEM_0779 + 1;
      pcVar3 = &DAT_EXTMEM_0766;
    }
    return DAT_EXTMEM_0779;
  }
  if ((param_6 >> 2 & 1) != 0) {
    FUN_CODE_39da();
    param_6 = 4;
    DAT_EXTMEM_2f52 = 4;
  }
  return param_6;
}

