
void FUN_CODE_1577(void)

{
  char cVar1;
  undefined1 *puVar2;
  
  cVar1 = '\x10';
  puVar2 = &DAT_EXTMEM_00e0;
  do {
    *puVar2 = 0;
    puVar2 = puVar2 + 1;
    cVar1 = cVar1 + -1;
  } while (cVar1 != '\0');
  return;
}

