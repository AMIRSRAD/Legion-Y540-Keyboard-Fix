
void FUN_CODE_0136(void)

{
  bool bVar1;
  byte bVar2;
  char cVar3;
  char cVar4;
  byte bVar5;
  
  bVar5 = 0;
  cVar4 = '\0';
  DAT_EXTMEM_1e21 = 0x40;
  DAT_EXTMEM_1e40 = 3;
  DAT_EXTMEM_1e20 = 0x80;
  bVar2 = 0x7f;
  if ((DAT_EXTMEM_1080 & 5) == 5) {
    bVar2 = 0xd7;
  }
  uEXTMEM0000 = 0x7f;
  uEXTMEM0001 = 0xfe;
  cVar3 = -1;
  do {
    bVar1 = CARRY1(*(byte *)CONCAT11(bVar2,cVar3),bVar5);
    bVar5 = *(byte *)CONCAT11(bVar2,cVar3) + bVar5;
    cVar4 = cVar4 - ((bVar1 << 7) >> 7);
    if (cVar3 == '\0') {
      bVar2 = bVar2 - 1;
    }
    cVar3 = cVar3 + -1;
  } while (2 < bVar2);
  cEXTMEM0002 = cCODE7ffe;
  DAT_EXTMEM_0f0b = DAT_CODE_7fff;
  bVar2 = (-cCODE7ffe - 1U) + bVar5;
  DAT_EXTMEM_0f07 = (-DAT_CODE_7fff - 1U) + bVar2;
  DAT_EXTMEM_0f06 =
       (cVar4 - ((CARRY1(-cCODE7ffe - 1U,bVar5) << 7) >> 7)) -
       ((CARRY1(-DAT_CODE_7fff - 1U,bVar2) << 7) >> 7);
  DAT_EXTMEM_0f0a = cEXTMEM0002;
  if ((DAT_EXTMEM_0f06 == BANK0_R6) && (DAT_EXTMEM_0f07 == BANK0_R7)) {
    DAT_EXTMEM_1045 = 3;
    thunk_FUN_CODE_0400();
  }
  else {
    DAT_EXTMEM_1045 = 3;
    thunk_EXT_FUN_CODE_e000(cCODE7ffe,DAT_CODE_7fff);
  }
  return;
}

