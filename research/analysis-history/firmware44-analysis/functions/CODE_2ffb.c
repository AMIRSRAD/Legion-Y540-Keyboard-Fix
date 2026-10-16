
void FUN_CODE_2ffb(void)

{
  byte bVar1;
  char cVar2;
  undefined1 *puVar3;
  
  DAT_EXTMEM_0953 = 0;
  DAT_EXTMEM_0954 = 0;
  bVar1 = 0;
  do {
    *(undefined1 *)CONCAT11('\t' - (((0xaa < bVar1) << 7) >> 7),bVar1 + 0x55) = 0;
    bVar1 = bVar1 + 1;
  } while (bVar1 != 0x1e);
  DAT_EXTMEM_0a70 = 0;
  cVar2 = '!';
  puVar3 = &DAT_EXTMEM_0a86;
  do {
    *puVar3 = 0;
    puVar3 = puVar3 + 1;
    cVar2 = cVar2 + -1;
  } while (cVar2 != '\0');
  DAT_EXTMEM_0974 = 0;
  return;
}

