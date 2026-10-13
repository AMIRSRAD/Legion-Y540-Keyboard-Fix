
byte FUN_CODE_2d12(char param_1)

{
  char cVar1;
  byte bVar2;
  byte bVar3;
  
  if (param_1 == '\0') {
    cVar1 = '\x02';
    bVar2 = DAT_EXTMEM_0740;
    bVar3 = DAT_EXTMEM_0741;
    do {
      bVar3 = bVar3 >> 1 | bVar2 << 7;
      cVar1 = cVar1 + -1;
      bVar2 = bVar2 >> 1;
    } while (cVar1 != '\0');
    return bVar3;
  }
  return param_1 - 1;
}

