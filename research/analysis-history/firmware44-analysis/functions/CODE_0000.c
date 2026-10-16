
void thunk_FUN_CODE_0100(void)

{
  undefined1 *puVar1;
  char cVar2;
  char cVar3;
  undefined1 *puVar4;
  
  puVar1 = (undefined1 *)0xff;
  do {
    *puVar1 = 0;
    puVar1 = puVar1 + -1;
  } while (puVar1 != (undefined1 *)0x0);
  puVar4 = (undefined1 *)0x0;
  cVar3 = '\0';
  cVar2 = '\x10';
  do {
    do {
      *puVar4 = 0;
      puVar4 = puVar4 + 1;
      cVar3 = cVar3 + -1;
    } while (cVar3 != '\0');
    cVar2 = cVar2 + -1;
  } while (cVar2 != '\0');
  SP = 0xa0;
  FUN_CODE_020b(1,0x36,1);
  FUN_CODE_0136();
  nop();
  nop();
  nop();
  return;
}

