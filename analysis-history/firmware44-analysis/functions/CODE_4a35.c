
char FUN_CODE_4a35(byte param_1)

{
  byte bVar1;
  char cVar2;
  byte bVar3;
  undefined1 uVar4;
  
  DAT_EXTMEM_074b = 0;
  DAT_EXTMEM_074c = 1;
  DAT_EXTMEM_074d = '\f';
  DAT_EXTMEM_074e = 0x3f;
  DAT_EXTMEM_0768 = 1;
  DAT_EXTMEM_0767 = param_1;
  FUN_CODE_3601(1,0x40);
  cVar2 = param_1 - 8;
  if (7 < param_1) {
    bVar1 = 0xee;
    cVar2 = (DAT_EXTMEM_074d - ((CARRY1(DAT_EXTMEM_074e,param_1) << 7) >> 7)) +
            (-1 - (((7 < DAT_EXTMEM_074e + param_1) << 7) >> 7));
    FUN_CODE_5600(cVar2,0,8,cVar2,(DAT_EXTMEM_074e + param_1) - 8,0xd);
    DAT_EXTMEM_0deb = 1;
    DAT_EXTMEM_0dec = 0xd;
    DAT_EXTMEM_0ded = 0xee;
    bVar3 = FUN_CODE_8561(0xee,0xd,1);
    if ((bVar3 & 0x60) == 0) {
      FUN_CODE_4614();
      DAT_EXTMEM_074b = bVar1;
    }
    else {
      bVar1 = FUN_CODE_8561(DAT_EXTMEM_0ded,DAT_EXTMEM_0dec,DAT_EXTMEM_0deb);
      bVar1 = bVar1 & 0x60;
      if (bVar1 == 0x20) {
        FUN_CODE_473f();
        DAT_EXTMEM_074b = bVar1;
      }
      else {
        bVar1 = FUN_CODE_8561(DAT_EXTMEM_0ded,DAT_EXTMEM_0dec,DAT_EXTMEM_0deb);
        bVar1 = bVar1 & 0x60;
        if (bVar1 == 0x40) {
          FUN_CODE_493d();
          DAT_EXTMEM_074b = bVar1;
        }
        else {
          DAT_EXTMEM_074b = 0x85;
        }
      }
    }
    if (DAT_EXTMEM_074b == 0) {
      uVar4 = 1;
    }
    else {
      uVar4 = 2;
    }
    cVar2 = FUN_CODE_85b9(uVar4,4,DAT_EXTMEM_0dea,DAT_EXTMEM_0de9,DAT_EXTMEM_0de8);
  }
  return cVar2;
}

