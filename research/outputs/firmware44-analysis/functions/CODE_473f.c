
byte FUN_CODE_473f(undefined1 param_1,undefined1 param_2,undefined1 param_3,undefined1 param_4)

{
  char cVar1;
  undefined1 uVar2;
  undefined1 uVar3;
  char cVar4;
  byte bVar5;
  
  DAT_EXTMEM_0752 = 0;
  DAT_EXTMEM_074f = param_3;
  DAT_EXTMEM_0750 = param_2;
  DAT_EXTMEM_0751 = param_1;
  cVar1 = FUN_CODE_857a(1,param_1,param_2,param_3);
  if (cVar1 == '\x01') {
    uVar2 = FUN_CODE_857a(3,DAT_EXTMEM_0751,DAT_EXTMEM_0750,DAT_EXTMEM_074f);
    uVar3 = FUN_CODE_857a(2);
    DAT_EXTMEM_0756 = FUN_CODE_857a(7);
    DAT_EXTMEM_0755 = FUN_CODE_857a(6);
    DAT_EXTMEM_0758 = FUN_CODE_857a(5);
    DAT_EXTMEM_0757 = FUN_CODE_857a(4);
    cVar4 = FUN_CODE_857a(1);
    DAT_EXTMEM_0768 = 1;
    DAT_EXTMEM_0769 = 0xc;
    DAT_EXTMEM_076a = 0x3f;
    DAT_EXTMEM_076b = 0;
    DAT_EXTMEM_076c = 0;
    DAT_EXTMEM_076d = 0;
    DAT_EXTMEM_076e = DAT_EXTMEM_0758;
    DAT_EXTMEM_076f = DAT_EXTMEM_0757;
    cVar1 = DAT_EXTMEM_0758;
    FUN_CODE_3201(DAT_EXTMEM_0756,DAT_EXTMEM_0755,uVar2,uVar3);
    DAT_EXTMEM_0753 = cVar1;
    DAT_EXTMEM_0754 = cVar4;
    if (cVar4 == '\0' && cVar1 == '\0') {
      DAT_EXTMEM_0752 = 0x9e;
      return 0x9e;
    }
LAB_CODE_48ab:
    FUN_CODE_3cf9(0x753,0x3f,0xc,1);
  }
  else {
    if (cVar1 == '\x02') {
      cVar1 = FUN_CODE_857a(4);
      if (cVar1 == '\0') {
        DAT_EXTMEM_0754 = '\x01';
        uVar3 = 0;
        DAT_EXTMEM_0753 = cVar1;
        FUN_CODE_2d12();
        DAT_EXTMEM_0c3f = uVar3;
        goto LAB_CODE_48ab;
      }
    }
    else if (cVar1 == '\x03') {
      cVar1 = FUN_CODE_857a(4,DAT_EXTMEM_0751,DAT_EXTMEM_0750,DAT_EXTMEM_074f);
      if (cVar1 == '\0') {
        DAT_EXTMEM_0754 = '\x01';
        DAT_EXTMEM_0753 = cVar1;
        FUN_CODE_2d44();
        DAT_EXTMEM_0c3f = param_4;
        goto LAB_CODE_48ab;
      }
LAB_CODE_47e2:
      FUN_CODE_857a(4,DAT_EXTMEM_0751,DAT_EXTMEM_0750,DAT_EXTMEM_074f);
    }
    else if (cVar1 == '\t') {
      bVar5 = FUN_CODE_857a(7,DAT_EXTMEM_0751,DAT_EXTMEM_0750,DAT_EXTMEM_074f);
      DAT_EXTMEM_0756 = bVar5;
      DAT_EXTMEM_0755 = FUN_CODE_857a(6);
      if (((bVar5 ^ 0x80) < 0x81U - (((DAT_EXTMEM_0755 < 0x81) << 7) >> 7)) << 7 < '\0') {
        DAT_EXTMEM_075e = 1;
        FUN_CODE_3e32(0x3f,0xc,1);
        DAT_EXTMEM_0752 = bVar5;
        return bVar5;
      }
    }
    else if (cVar1 == '\n') {
      cVar1 = FUN_CODE_857a(4,DAT_EXTMEM_0751,DAT_EXTMEM_0750,DAT_EXTMEM_074f);
      if (cVar1 == '\0') {
        DAT_EXTMEM_0951 = FUN_CODE_857a(3);
        FUN_CODE_2cf0(DAT_EXTMEM_0951,0);
LAB_CODE_492a:
        FUN_CODE_3b7f();
        return DAT_EXTMEM_0752;
      }
    }
    else if (cVar1 == '\v') {
      cVar1 = FUN_CODE_857a(4,DAT_EXTMEM_0751,DAT_EXTMEM_0750,DAT_EXTMEM_074f);
      if (cVar1 == '\0') {
        uVar3 = FUN_CODE_857a(2);
        FUN_CODE_2d36(uVar3);
        goto LAB_CODE_492a;
      }
      goto LAB_CODE_47e2;
    }
    DAT_EXTMEM_0752 = 0x86;
  }
  return DAT_EXTMEM_0752;
}

