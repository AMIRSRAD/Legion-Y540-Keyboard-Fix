
void FUN_CODE_348d(void)

{
  bool bVar1;
  byte bVar2;
  byte bVar3;
  char cVar4;
  char cVar5;
  char cVar6;
  undefined1 uVar7;
  
  if (10 < DAT_EXTMEM_0c34) {
    DAT_EXTMEM_0c34 = 10;
  }
  DAT_EXTMEM_077f = DAT_EXTMEM_0c34;
  cVar4 = '\f';
  bVar3 = 0x35;
  cVar5 = DAT_EXTMEM_0c32;
  cVar6 = DAT_EXTMEM_0c31;
  while( true ) {
    bVar2 = DAT_EXTMEM_077f;
    DAT_EXTMEM_077f = DAT_EXTMEM_077f - 1;
    if (bVar2 == 0) break;
    if (DAT_EXTMEM_0c33 != '\0') {
      uVar7 = FUN_CODE_8561(cVar4);
      *(undefined1 *)CONCAT11(cVar5,cVar6) = uVar7;
    }
    bVar1 = 0xfe < bVar3;
    bVar3 = bVar3 + 1;
    cVar4 = cVar4 - ((bVar1 << 7) >> 7);
    cVar6 = cVar6 + '\x01';
    if (cVar6 == '\0') {
      cVar5 = cVar5 + '\x01';
    }
  }
  return;
}

