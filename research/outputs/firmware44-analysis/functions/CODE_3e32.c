
void FUN_CODE_3e32(char param_1,undefined1 param_2,char param_3,char param_4)

{
  char cVar1;
  char cVar2;
  byte bVar3;
  char cVar4;
  byte bVar5;
  undefined1 uVar6;
  undefined1 uVar7;
  undefined1 uVar8;
  undefined1 uVar9;
  undefined1 *puVar10;
  
  puVar10 = (undefined1 *)0x0;
  if (DAT_EXTMEM_075e == '\0') {
    cVar4 = FUN_CODE_8632(9,DAT_EXTMEM_0dea,DAT_EXTMEM_0de9,DAT_EXTMEM_0de8);
    if (cVar4 != '\0' || param_1 != '\0') {
      FUN_CODE_3cc8();
      if (param_4 == '\0') {
        param_4 = '\0';
      }
      else {
        bVar5 = DAT_EXTMEM_0dea;
        cVar4 = DAT_EXTMEM_0de9;
        uVar7 = DAT_EXTMEM_0de8;
        FUN_CODE_8881(6);
        uVar6 = FUN_CODE_857a(0xb,DAT_EXTMEM_0dea,DAT_EXTMEM_0de9,DAT_EXTMEM_0de8);
        DAT_EXTMEM_0767 = 0;
        DAT_EXTMEM_0768 = 1;
        FUN_CODE_3601(bVar5,cVar4,uVar7,uVar6);
        cVar4 = FUN_CODE_857a(0xb,DAT_EXTMEM_0dea,DAT_EXTMEM_0de9,DAT_EXTMEM_0de8);
        if (cVar4 != param_4) {
          return;
        }
        FUN_CODE_866a(0,7);
        cVar2 = DAT_EXTMEM_0dea + 9;
        cVar1 = DAT_EXTMEM_0de9 - (((0xf6 < DAT_EXTMEM_0dea) << 7) >> 7);
        bVar5 = FUN_CODE_8607(DAT_EXTMEM_0de8);
        bVar3 = FUN_CODE_857a(0xb,DAT_EXTMEM_0dea,DAT_EXTMEM_0de9);
        param_4 = bVar5 - bVar3;
        param_1 = param_4;
        FUN_CODE_86b7(cVar4 + (((bVar5 < bVar3) << 7) >> 7),cVar2,cVar1);
      }
    }
  }
  else {
    FUN_CODE_88b1(6,DAT_EXTMEM_0dea,DAT_EXTMEM_0de9,DAT_EXTMEM_0de8);
    param_1 = param_3;
    FUN_CODE_86d6(param_2,9,DAT_EXTMEM_0dea,DAT_EXTMEM_0de9,DAT_EXTMEM_0de8);
    puVar10 = &BANK0_R3;
    param_4 = param_3;
  }
  puVar10['\x01'] = 0x41;
  puVar10['\x02'] = 0x3f;
  cVar4 = FUN_CODE_8632(9,DAT_EXTMEM_0dea,DAT_EXTMEM_0de9,DAT_EXTMEM_0de8);
  if (cVar4 == '\0' && param_1 == '\0') {
    puVar10['\x01'] = 0x67;
    puVar10['\x02'] = 0x3f;
    bVar5 = FUN_CODE_8561(DAT_EXTMEM_0ded,DAT_EXTMEM_0dec,DAT_EXTMEM_0deb,cVar4);
    if ((bVar5 & 0x60) == 0x20) {
      puVar10['\x01'] = 0x76;
      puVar10['\x02'] = 0x3f;
      uVar6 = FUN_CODE_857a(3);
      puVar10['\x01'] = 0x7d;
      puVar10['\x02'] = 0x3f;
      uVar7 = FUN_CODE_857a(2);
      puVar10['\x01'] = 0x84;
      puVar10['\x02'] = 0x3f;
      DAT_EXTMEM_0760 = FUN_CODE_857a(7);
      puVar10['\x01'] = 0x8e;
      puVar10['\x02'] = 0x3f;
      DAT_EXTMEM_075f = FUN_CODE_857a(6);
      puVar10['\x01'] = 0x98;
      puVar10['\x02'] = 0x3f;
      DAT_EXTMEM_0762 = FUN_CODE_857a(5);
      puVar10['\x01'] = 0xa2;
      puVar10['\x02'] = 0x3f;
      DAT_EXTMEM_0761 = FUN_CODE_857a(4);
      puVar10['\x01'] = 0xac;
      puVar10['\x02'] = 0x3f;
      uVar8 = FUN_CODE_857a(1);
      puVar10['\x01'] = uVar8;
      puVar10['\x02'] = DAT_EXTMEM_0760;
      puVar10['\x03'] = DAT_EXTMEM_075f;
      DAT_EXTMEM_0768 = 0;
      DAT_EXTMEM_0769 = 0;
      DAT_EXTMEM_076a = 0;
      DAT_EXTMEM_076b = 1;
      DAT_EXTMEM_076c = 0xc;
      DAT_EXTMEM_076d = 0x3f;
      DAT_EXTMEM_076e = DAT_EXTMEM_0762;
      DAT_EXTMEM_076f = DAT_EXTMEM_0761;
      uVar8 = puVar10['\x02'];
      uVar9 = puVar10['\x01'];
      puVar10['\x01'] = 0xb;
      puVar10['\x02'] = 0x40;
      FUN_CODE_3201(uVar8,puVar10['\x03'],uVar6,uVar7,uVar9);
    }
    cVar4 = '\x02';
    puVar10['\x01'] = 0x10;
    puVar10['\x02'] = 0x40;
    FUN_CODE_3a88();
    if (cVar4 == '\0') {
      puVar10['\x01'] = 0x25;
      puVar10['\x02'] = 0x40;
      FUN_CODE_85b9(0,1,DAT_EXTMEM_0dea,DAT_EXTMEM_0de9,DAT_EXTMEM_0de8);
      return;
    }
    puVar10['\x01'] = 0x2b;
    puVar10['\x02'] = 0x40;
    FUN_CODE_3b7f();
    if (cVar4 == '\0') {
      return;
    }
  }
  else {
    puVar10['\x01'] = 0x4d;
    puVar10['\x02'] = 0x3f;
    FUN_CODE_8881(6);
    puVar10['\x01'] = 0x50;
    puVar10['\x02'] = 0x3f;
    FUN_CODE_3c58();
    if (param_4 == '\0') {
      return;
    }
  }
  return;
}

