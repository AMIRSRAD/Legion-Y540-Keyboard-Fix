
/* WARNING: Removing unreachable block (CODE,0x228b) */

void FUN_CODE_2260(void)

{
  char cVar1;
  byte bVar2;
  byte bVar3;
  byte *pbVar4;
  
  if (((DAT_INTMEM_40 >> 4 & 1) != 1) &&
     (DAT_INTMEM_40 = DAT_INTMEM_40 | 0x10, DAT_EXTMEM_0974 != '\0')) {
    FUN_CODE_2ffb();
  }
  DAT_INTMEM_34 = DAT_INTMEM_34 & 0xfb;
  DAT_EXTMEM_0748 = 0;
  DAT_EXTMEM_074a = '\x1d';
  DAT_EXTMEM_074b = 0x10;
  DAT_EXTMEM_0746 = 0;
  while( true ) {
    bVar2 = DAT_EXTMEM_0081 + 0x10;
    bVar3 = (0xef < DAT_EXTMEM_0081 ^ 0x80U) - (((DAT_EXTMEM_0746 < bVar2) << 7) >> 7);
    if (bVar3 < 0x81) break;
    FUN_CODE_25d9(-0x80 - bVar3);
    if ((bVar2 == 0) &&
       (DAT_EXTMEM_0748 =
             ~*(byte *)CONCAT11(DAT_EXTMEM_074a -
                                ((CARRY1(DAT_EXTMEM_074b,DAT_EXTMEM_0746) << 7) >> 7),
                                DAT_EXTMEM_074b + DAT_EXTMEM_0746) ^
             *(byte *)(DAT_EXTMEM_0746 + 0x6d), DAT_EXTMEM_0748 != 0)) {
      DAT_EXTMEM_0020 = 0xf < DAT_EXTMEM_0746;
      for (DAT_EXTMEM_0747 = 0; (DAT_EXTMEM_0747 < 8) << 7 < '\0';
          DAT_EXTMEM_0747 = DAT_EXTMEM_0747 + 1) {
        bVar3 = 1;
        cVar1 = DAT_EXTMEM_0747 + 1;
        while (cVar1 = cVar1 + -1, cVar1 != '\0') {
          bVar3 = bVar3 << 1;
        }
        if ((bVar3 & DAT_EXTMEM_0748) != 0) {
          bVar3 = DAT_EXTMEM_0746;
          if (DAT_EXTMEM_0020 == '\x01') {
            bVar3 = DAT_EXTMEM_0746 - 0x10;
          }
          DAT_INTMEM_4d = DAT_INTMEM_4d & 8 | bVar3 << 4 | DAT_EXTMEM_0747 & 7;
          bVar3 = 1;
          cVar1 = DAT_EXTMEM_0747 + 1;
          while (cVar1 = cVar1 + -1, cVar1 != '\0') {
            bVar3 = bVar3 << 1;
          }
          if ((bVar3 & *(byte *)(DAT_EXTMEM_0746 + 0x6d)) != 0) {
            FUN_CODE_853b(0x4c,0x4d,0,0,7,1,0,1);
            DAT_EXTMEM_074d = 1;
            FUN_CODE_1435();
            pbVar4 = (byte *)(DAT_EXTMEM_0746 + 0x6d);
            bVar3 = *pbVar4;
            bVar2 = 1;
            cVar1 = DAT_EXTMEM_0747 + 1;
            while (cVar1 = cVar1 + -1, cVar1 != '\0') {
              bVar2 = bVar2 << 1;
            }
            *pbVar4 = (byte)pbVar4;
            *pbVar4 = ~bVar2 & bVar3;
            DAT_EXTMEM_0748 = DAT_EXTMEM_0748 & ~bVar2;
          }
        }
      }
    }
    DAT_EXTMEM_0746 = DAT_EXTMEM_0746 + 1;
  }
  DAT_EXTMEM_0746 = 0;
  while( true ) {
    bVar2 = DAT_EXTMEM_0081 + 0x10;
    bVar3 = (0xef < DAT_EXTMEM_0081 ^ 0x80U) - (((DAT_EXTMEM_0746 < bVar2) << 7) >> 7);
    if (bVar3 < 0x81) break;
    FUN_CODE_25d9(-0x80 - bVar3);
    if ((bVar2 == 0) &&
       (DAT_EXTMEM_0748 =
             ~*(byte *)CONCAT11(DAT_EXTMEM_074a -
                                ((CARRY1(DAT_EXTMEM_074b,DAT_EXTMEM_0746) << 7) >> 7),
                                DAT_EXTMEM_074b + DAT_EXTMEM_0746) ^
             *(byte *)(DAT_EXTMEM_0746 + 0x6d), DAT_EXTMEM_0748 != 0)) {
      DAT_EXTMEM_0020 = 0xf < DAT_EXTMEM_0746;
      for (DAT_EXTMEM_0747 = 0; (DAT_EXTMEM_0747 < 8) << 7 < '\0';
          DAT_EXTMEM_0747 = DAT_EXTMEM_0747 + 1) {
        bVar3 = DAT_EXTMEM_0746;
        FUN_CODE_261c(DAT_EXTMEM_0747);
        if (bVar3 != 0) {
          bVar3 = 1;
          cVar1 = DAT_EXTMEM_0747 + 1;
          while (cVar1 = cVar1 + -1, cVar1 != '\0') {
            bVar3 = bVar3 << 1;
          }
          if ((bVar3 & DAT_EXTMEM_0748) != 0) {
            bVar3 = DAT_EXTMEM_0746;
            if (DAT_EXTMEM_0020 == '\x01') {
              bVar3 = DAT_EXTMEM_0746 - 0x10;
            }
            DAT_INTMEM_4d = DAT_INTMEM_4d & 8 | bVar3 << 4 | DAT_EXTMEM_0747 & 7;
            bVar3 = 1;
            cVar1 = DAT_EXTMEM_0747 + 1;
            while (cVar1 = cVar1 + -1, cVar1 != '\0') {
              bVar3 = bVar3 << 1;
            }
            if ((bVar3 & *(byte *)(DAT_EXTMEM_0746 + 0x6d)) == 0) {
              FUN_CODE_853b(0x4c,0x4d,0,0,7,1,0,1);
              DAT_EXTMEM_074d = 0;
              FUN_CODE_1435();
              DAT_INTMEM_4e = DAT_INTMEM_4d;
              DAT_INTMEM_59 = 0x28;
              DAT_INTMEM_57 = DAT_EXTMEM_0746;
              DAT_INTMEM_58 = DAT_EXTMEM_0747;
              DAT_INTMEM_33 = DAT_INTMEM_33 & 0xf0 | 2;
              DAT_EXTMEM_0025 = DAT_EXTMEM_0024;
              DAT_EXTMEM_0021 = DAT_EXTMEM_0020 == '\x01';
              pbVar4 = (byte *)(DAT_EXTMEM_0746 + 0x6d);
              bVar3 = *pbVar4;
              bVar2 = 1;
              cVar1 = DAT_EXTMEM_0747 + 1;
              while (cVar1 = cVar1 + -1, cVar1 != '\0') {
                bVar2 = bVar2 << 1;
              }
              *pbVar4 = (byte)pbVar4;
              *pbVar4 = bVar2 | bVar3;
              DAT_EXTMEM_0748 = DAT_EXTMEM_0748 & ~bVar2;
            }
          }
        }
      }
    }
    if (*(char *)(DAT_EXTMEM_0746 + 0x6d) != '\0') {
      DAT_INTMEM_34 = DAT_INTMEM_34 | 4;
    }
    DAT_EXTMEM_0746 = DAT_EXTMEM_0746 + 1;
  }
  if ((DAT_INTMEM_34 >> 2 & 1) != 1) {
    FUN_CODE_25bb(bVar2);
  }
  DAT_EXTMEM_1d33 = 1;
  DAT_EXTMEM_1105 = DAT_EXTMEM_1105 | 2;
  return;
}

