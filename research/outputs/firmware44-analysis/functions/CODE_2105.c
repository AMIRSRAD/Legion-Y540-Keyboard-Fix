
void FUN_CODE_2105(void)

{
  undefined1 *puVar1;
  char cVar2;
  undefined1 *puVar3;
  
  cVar2 = '\x13';
  puVar1 = &DAT_INTMEM_6d;
  do {
    *puVar1 = 0;
    puVar1 = puVar1 + '\x01';
    cVar2 = cVar2 + -1;
  } while (cVar2 != '\0');
  cVar2 = -0x80;
  puVar3 = &DAT_EXTMEM_0400;
  do {
    *puVar3 = 0;
    puVar3 = puVar3 + 1;
    cVar2 = cVar2 + -1;
  } while (cVar2 != '\0');
  DAT_INTMEM_30 = 0;
  DAT_INTMEM_31 = 0;
  DAT_INTMEM_34 = DAT_INTMEM_34 & 0xfb;
  DAT_INTMEM_4d = 0;
  FUN_CODE_25bb();
  return;
}

