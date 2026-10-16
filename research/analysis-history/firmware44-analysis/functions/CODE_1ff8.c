
char FUN_CODE_1ff8(void)

{
  undefined1 uVar1;
  char cVar2;
  undefined1 uVar3;
  
  while( true ) {
    cVar2 = FUN_CODE_8561(DAT_EXTMEM_075a,DAT_EXTMEM_0759,DAT_EXTMEM_0758);
    if ((cVar2 == '\0') || (DAT_EXTMEM_075b != '\0')) break;
    uVar1 = 1;
    uVar3 = FUN_CODE_85f1(0,0x759,1);
    cVar2 = FUN_CODE_8561(uVar1,uVar3);
    FUN_CODE_1f93();
    if (cVar2 == '\0') {
      DAT_EXTMEM_075b = 0x80;
      cVar2 = FUN_CODE_1ff8();
      return cVar2;
    }
  }
  return DAT_EXTMEM_075b;
}

