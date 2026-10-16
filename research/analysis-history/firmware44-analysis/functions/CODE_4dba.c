
void FUN_CODE_4dba(undefined1 param_1,char param_2)

{
  undefined1 uVar1;
  undefined1 uVar2;
  undefined1 uVar3;
  char cVar4;
  char cVar5;
  undefined1 uVar6;
  char *pcVar7;
  
  FUN_CODE_36eb();
  if (param_2 == '\0') {
    if ((DAT_EXTMEM_2f52 >> 2 & 1) != 0) {
      FUN_CODE_35dd();
      return;
    }
    FUN_CODE_85b9(0,3,DAT_EXTMEM_0dea,DAT_EXTMEM_0de9,DAT_EXTMEM_0de8);
    DAT_EXTMEM_2f53 = 5;
    cVar4 = FUN_CODE_857a(1);
    if (cVar4 == '\0') {
      FUN_CODE_3a24();
    }
    if ((DAT_EXTMEM_2f40 >> 1 & 1) != 0) {
      return;
    }
    cVar4 = DAT_EXTMEM_2f42;
    FUN_CODE_85b9(DAT_EXTMEM_2f42,5,DAT_EXTMEM_0dea,DAT_EXTMEM_0de9,DAT_EXTMEM_0de8);
    if ((DAT_EXTMEM_2f41 >> 5 & 1) != 0) {
      FUN_CODE_85b9(0,4);
      FUN_CODE_85b9(0,1);
      FUN_CODE_32d3();
      return;
    }
    cVar5 = FUN_CODE_857a(5);
    if (cVar5 == '\x01') {
      uVar1 = DAT_EXTMEM_0dea;
      uVar2 = DAT_EXTMEM_0de9;
      uVar3 = DAT_EXTMEM_0de8;
      cVar4 = FUN_CODE_857a(1);
      if (cVar4 == '\x04') {
        cVar4 = FUN_CODE_8561();
        if (cVar4 == '\0') {
          return;
        }
        DAT_EXTMEM_2f54 = cVar4;
        FUN_CODE_85a7(0);
        return;
      }
      if (cVar4 == '\0') {
        return;
      }
      cVar4 = FUN_CODE_857a(1);
      if (cVar4 == '\x02') {
        return;
      }
      FUN_CODE_8881(6);
      uVar6 = FUN_CODE_8632(9,DAT_EXTMEM_0dea,DAT_EXTMEM_0de9,DAT_EXTMEM_0de8);
      DAT_EXTMEM_076a = 0;
      FUN_CODE_3d04(uVar1,uVar2,uVar3,param_1,uVar6);
      FUN_CODE_8844(0x747);
    }
    else if (cVar5 == '\x02') {
      uVar1 = DAT_EXTMEM_0dea;
      uVar2 = DAT_EXTMEM_0de9;
      uVar3 = DAT_EXTMEM_0de8;
      cVar4 = FUN_CODE_857a(1);
      if (cVar4 != '\x03') {
        if (cVar4 == '\0') {
          return;
        }
        if (cVar4 == '\x01') {
          FUN_CODE_85b9(0,1);
          return;
        }
        FUN_CODE_8881(6);
        uVar6 = FUN_CODE_8632(9,DAT_EXTMEM_0dea,DAT_EXTMEM_0de9,DAT_EXTMEM_0de8);
        DAT_EXTMEM_075e = 0;
        FUN_CODE_3e32(uVar1,uVar2,uVar3,param_1,uVar6);
        FUN_CODE_8844(0x747,0,0,0);
        FUN_CODE_8820(0,0,0,0);
      }
    }
    else if ((cVar5 == '\0') && ((DAT_EXTMEM_2f62 != '\0' || (DAT_EXTMEM_2f63 != '\0')))) {
      FUN_CODE_85b9(0,1);
      FUN_CODE_3cc8();
      if (cVar4 == '\0') {
        FUN_CODE_32d3();
      }
      else {
        FUN_CODE_4a35(0);
      }
    }
    cVar4 = FUN_CODE_857a(4,DAT_EXTMEM_0dea,DAT_EXTMEM_0de9,DAT_EXTMEM_0de8);
    if (cVar4 == '\x02') {
      DAT_EXTMEM_2f40 = 0xb;
    }
    return;
  }
  if (DAT_EXTMEM_0dd1 == '\0') {
    return;
  }
  FUN_CODE_36eb();
  if (param_2 != '\0') {
    if (DAT_EXTMEM_0dd0 == '\x02') {
      cVar4 = FUN_CODE_857a(0x12,DAT_EXTMEM_0dea,DAT_EXTMEM_0de9,DAT_EXTMEM_0de8);
      if (cVar4 == '\0') {
        DAT_EXTMEM_0dd1 = 0;
        return;
      }
      cVar4 = '\x02';
      FUN_CODE_3185();
      if (cVar4 == '\x01') {
        DAT_EXTMEM_0dd1 = 0;
        return;
      }
    }
    FUN_CODE_4b29(DAT_EXTMEM_0dd0 != '\0');
    DAT_EXTMEM_0dd3 = 0;
    DAT_EXTMEM_08ad = 0;
    if ((DAT_EXTMEM_0dd0 == '\x02') && ((DAT_EXTMEM_2f52 & 0xf) == 0)) {
      FUN_CODE_059d();
      DAT_EXTMEM_2f50 = 0x4a;
      FUN_CODE_0c96(2);
      DAT_EXTMEM_2f50 = 0x71;
      FUN_CODE_05a4();
      FUN_CODE_0c96(0xf);
      TR1 = 0;
      ET1 = 0;
      nop();
      nop();
      nop();
      nop();
      TH1 = 0;
      TL1 = 1;
      TF1 = 0;
      TR1 = 1;
      do {
        while( true ) {
          cVar4 = TF1;
          if (cVar4 == '\x01') goto LAB_CODE_4d9f;
          if ((DAT_EXTMEM_2f52 >> 1 & 1) == 0) break;
          if (((DAT_EXTMEM_16e0 >> 4 & 1) != 1) && ((DAT_EXTMEM_16e0 >> 5 & 1) != 0)) {
            pcVar7 = &DAT_EXTMEM_00f2;
            goto LAB_CODE_4d9c;
          }
          if ((DAT_EXTMEM_2f52 >> 3 & 1) != 0) {
            pcVar7 = &DAT_EXTMEM_00a2;
            goto LAB_CODE_4d9c;
          }
        }
      } while ((DAT_EXTMEM_2f52 & 0xd) == 0);
      pcVar7 = &DAT_EXTMEM_00a3;
LAB_CODE_4d9c:
      *pcVar7 = *pcVar7 + '\x01';
LAB_CODE_4d9f:
      TR1 = 0;
      TF1 = 0;
      ET1 = 1;
    }
    DAT_EXTMEM_0dd1 = '\0';
    DAT_EXTMEM_2f52 = 10;
    if (DAT_EXTMEM_0dd0 != '\0') {
      FUN_CODE_7feb();
    }
  }
  return;
}

