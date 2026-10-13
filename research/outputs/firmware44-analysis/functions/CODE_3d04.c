
undefined1 FUN_CODE_3d04(char param_1,undefined1 param_2,char param_3,char param_4)

{
  char cVar1;
  bool bVar2;
  byte bVar3;
  byte bVar4;
  char cVar5;
  undefined1 *puVar6;
  
  puVar6 = (undefined1 *)0x0;
  if (DAT_EXTMEM_076a == '\0') {
    cVar5 = FUN_CODE_8632(9,DAT_EXTMEM_0dea,DAT_EXTMEM_0de9,DAT_EXTMEM_0de8);
    if (cVar5 == '\0' && param_1 == '\0') goto LAB_CODE_3ddd;
    FUN_CODE_35f0();
    if (param_4 == '\0') goto LAB_CODE_3ddd;
    cVar1 = DAT_EXTMEM_0dea + 9;
    cVar5 = DAT_EXTMEM_0de9 - (((0xf6 < DAT_EXTMEM_0dea) << 7) >> 7);
    bVar3 = FUN_CODE_8607(DAT_EXTMEM_0de8);
    bVar4 = FUN_CODE_857a(0xb,DAT_EXTMEM_0dea,DAT_EXTMEM_0de9,bVar3);
    FUN_CODE_86b7(param_1 + (((bVar3 < bVar4) << 7) >> 7),bVar3 - bVar4,cVar1,cVar5);
    param_3 = FUN_CODE_857a(0xb,DAT_EXTMEM_0dea,DAT_EXTMEM_0de9,DAT_EXTMEM_0de8);
    FUN_CODE_866a(0,7);
    cVar5 = FUN_CODE_857a(0xc,DAT_EXTMEM_0dea,DAT_EXTMEM_0de9,DAT_EXTMEM_0de8);
    bVar2 = cVar5 != '\x01';
  }
  else {
    FUN_CODE_88b1(6,DAT_EXTMEM_0dea,DAT_EXTMEM_0de9,DAT_EXTMEM_0de8);
    FUN_CODE_86d6(param_2,9,DAT_EXTMEM_0dea,DAT_EXTMEM_0de9,DAT_EXTMEM_0de8);
    puVar6 = &BANK0_R3;
    bVar2 = true;
  }
  puVar6['\x01'] = 0xdd;
  puVar6['\x02'] = 0x3d;
  FUN_CODE_85b9(bVar2,0xc);
  param_1 = param_3;
LAB_CODE_3ddd:
  puVar6['\x01'] = 0xee;
  puVar6['\x02'] = 0x3d;
  cVar5 = FUN_CODE_8632(9,DAT_EXTMEM_0dea,DAT_EXTMEM_0de9,DAT_EXTMEM_0de8);
  if (cVar5 == '\0' && param_1 == '\0') {
    cVar1 = '\x01';
    puVar6['\x01'] = 9;
    puVar6['\x02'] = 0x3e;
    FUN_CODE_3a88(cVar5);
    if (cVar1 == '\0') {
      puVar6['\x01'] = 0x1e;
      puVar6['\x02'] = 0x3e;
      FUN_CODE_85b9(0,1,DAT_EXTMEM_0dea,DAT_EXTMEM_0de9,DAT_EXTMEM_0de8);
    }
    else {
      puVar6['\x01'] = 0x25;
      puVar6['\x02'] = 0x3e;
      FUN_CODE_36cf();
    }
  }
  else {
    puVar6['\x01'] = 0xfa;
    puVar6['\x02'] = 0x3d;
    FUN_CODE_8881(6);
    puVar6['\x01'] = 0xfd;
    puVar6['\x02'] = 0x3d;
    FUN_CODE_3bb9();
  }
  return 0;
}

