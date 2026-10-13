
void FUN_CODE_16dc(void)

{
  char cVar1;
  undefined1 *puVar2;
  
  cVar1 = '\x10';
  puVar2 = &DAT_EXTMEM_00b0;
  do {
    *puVar2 = 0;
    puVar2 = puVar2 + 1;
    cVar1 = cVar1 + -1;
  } while (cVar1 != '\0');
  return;
}

