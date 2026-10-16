
void FUN_CODE_1435(void)

{
  char *pcVar1;
  
  if ((DAT_EXTMEM_00ff >> 6 & 1) == 0) {
    if (DAT_EXTMEM_0020 == '\0') {
      DAT_INTMEM_68 = DAT_EXTMEM_074c >> 4 | (DAT_EXTMEM_074c & 7) << 4;
      pcVar1 = &DAT_EXTMEM_0027;
    }
    else {
      DAT_INTMEM_68 = (DAT_EXTMEM_074c >> 4) + (DAT_EXTMEM_074c & 7) * '\x03';
      pcVar1 = &DAT_EXTMEM_0029;
    }
    DAT_INTMEM_67 =
         *(undefined1 *)
          CONCAT11(*pcVar1 - ((CARRY1(pcVar1[1],DAT_INTMEM_68) << 7) >> 7),pcVar1[1] + DAT_INTMEM_68
                  );
    FUN_CODE_7940(DAT_EXTMEM_074d,DAT_EXTMEM_074c >> 4,DAT_EXTMEM_074c,DAT_EXTMEM_074c & 7);
    if ((DAT_EXTMEM_0811 & 1) == 1) {
      if ((((DAT_EXTMEM_074c & 7) == 3) && (DAT_EXTMEM_074c >> 4 == 1)) &&
         (DAT_EXTMEM_074d == '\x01')) {
        if ((DAT_EXTMEM_0816 >> 1 & 1) != 0) {
          FUN_CODE_19a7(1,0x82);
        }
        DAT_EXTMEM_0816 = DAT_EXTMEM_0816 & 0xfc;
        return;
      }
      if (((((DAT_EXTMEM_074c & 7) != 3) || (DAT_EXTMEM_074c >> 4 != 1)) &&
          ((DAT_EXTMEM_074d == '\0' && ((DAT_EXTMEM_0816 & 1) != 0)))) &&
         (((DAT_EXTMEM_074c & 7) != 2 || (DAT_EXTMEM_074c >> 4 != 2)))) {
        FUN_CODE_19a7(0,0x82);
        DAT_EXTMEM_0816 = DAT_EXTMEM_0816 & 0xfe | 2;
      }
      if (((((DAT_EXTMEM_074c & 7) == 3) && (DAT_EXTMEM_074c >> 4 == 1)) &&
          (DAT_EXTMEM_074d == '\0')) && ((DAT_EXTMEM_0816 & 1) != 1)) {
        DAT_EXTMEM_0816 = DAT_EXTMEM_0816 | 1;
        return;
      }
    }
    FUN_CODE_1841(DAT_EXTMEM_074d,DAT_INTMEM_67);
  }
  else if ((DAT_EXTMEM_00fc == -1) && (DAT_EXTMEM_074d == '\0')) {
    DAT_EXTMEM_00fa = DAT_EXTMEM_074c & 7;
    DAT_EXTMEM_00fb = DAT_EXTMEM_074c >> 4;
    if (DAT_EXTMEM_0020 != '\0') {
      DAT_EXTMEM_00fc = 0x44;
      return;
    }
    DAT_EXTMEM_00fc = 0x33;
    return;
  }
  return;
}

