
/* WARNING: Instruction at (CODE,0x49e5) overlaps instruction at (CODE,0x49e3)
    */

undefined1
FUN_CODE_493d(undefined1 *param_1,undefined1 param_2,undefined1 param_3,undefined1 param_4)

{
  byte bVar1;
  char cVar2;
  char cVar3;
  char cVar4;
  
  DAT_EXTMEM_074f = param_4;
  DAT_EXTMEM_0750 = param_3;
  DAT_EXTMEM_0751 = param_2;
  FUN_CODE_8850(0x752);
  nop();
  nop();
  nop();
  nop();
  DAT_EXTMEM_0756 = '\0';
  DAT_EXTMEM_0757 = '\0';
  DAT_EXTMEM_0758 = '\0';
  DAT_EXTMEM_0759 = 0;
  DAT_EXTMEM_075a = 0;
  DAT_EXTMEM_075b = 1;
  DAT_EXTMEM_075d = FUN_CODE_857a(7,DAT_EXTMEM_0751,DAT_EXTMEM_0750,DAT_EXTMEM_074f);
  DAT_EXTMEM_075c = FUN_CODE_857a(6);
  cVar2 = FUN_CODE_857a(5);
  cVar3 = FUN_CODE_857a(4);
  cVar4 = FUN_CODE_857a(1);
  if (((cVar4 == '\x7f') && (cVar3 == '\x05' && cVar2 == '\0')) &&
     (cVar3 = FUN_CODE_8561(DAT_EXTMEM_0751,DAT_EXTMEM_0750,DAT_EXTMEM_074f), cVar3 == -0x3f)) {
    DAT_EXTMEM_0756 = '\x01';
    DAT_EXTMEM_0757 = '\n';
    DAT_EXTMEM_0758 = '\x1f';
  }
  else {
    FUN_CODE_8850(0x752);
    nop();
    nop();
    nop();
    P0 = *param_1;
    bVar1 = P1;
    P1 = bVar1 | 7;
  }
  DAT_EXTMEM_0759 = DAT_EXTMEM_075d;
  DAT_EXTMEM_075a = DAT_EXTMEM_075c;
  if (DAT_EXTMEM_075c == '\0' && DAT_EXTMEM_075d == '\0') {
    DAT_EXTMEM_075a = '\x01';
    DAT_EXTMEM_0759 = '\0';
  }
  if ((DAT_EXTMEM_0758 == '\0' && DAT_EXTMEM_0757 == '\0') && DAT_EXTMEM_0756 == '\0') {
    DAT_EXTMEM_0756 = '\x01';
    DAT_EXTMEM_0757 = '\a';
    DAT_EXTMEM_0758 = '[';
  }
  FUN_CODE_3cf0(0x756);
  return DAT_EXTMEM_0755;
}

