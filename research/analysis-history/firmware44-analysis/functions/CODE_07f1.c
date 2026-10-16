
void FUN_CODE_07f1(short param_1,char param_2,undefined1 *param_3,char param_4,char param_5,
                  char param_6,char param_7,char param_8)

{
  undefined1 uVar1;
  char cVar2;
  byte bVar3;
  byte bVar4;
  byte bVar5;
  
  FUN_CODE_08b8();
  cVar2 = DAT_INTMEM_43;
  DAT_INTMEM_43 = DAT_INTMEM_43 + 1;
  cVar2 = cVar2 + -9;
  if (9 < DAT_INTMEM_43) {
    cVar2 = '\0';
    DAT_INTMEM_43 = 0;
  }
  FUN_CODE_6fa5(cVar2);
  if ((param_8 != '\x01') && (DAT_INTMEM_43 % 5 == 0)) {
    FUN_CODE_08bd();
    DAT_INTMEM_44 = DAT_INTMEM_44 + 1;
    if ((DAT_INTMEM_44 & 1) != 0) {
      FUN_CODE_08c8();
      return;
    }
    thunk_FUN_CODE_6f21();
    cVar2 = (3 < DAT_INTMEM_44) << 7;
    bVar3 = DAT_INTMEM_44 - 4;
    if (bVar3 == 0) {
      thunk_FUN_CODE_6f32();
      goto LAB_CODE_085d;
    }
    while( true ) {
      cVar2 = (1 < bVar3) << 7;
      if (bVar3 == 2) {
        thunk_FUN_CODE_34ff();
      }
      else {
        cVar2 = (1 < bVar3 - 2) << 7;
        if (bVar3 == 4) {
          DAT_INTMEM_46 = DAT_INTMEM_46 + 1;
          if ((DAT_INTMEM_46 & 1) == 0) {
            thunk_FUN_CODE_6f65();
          }
          else {
            thunk_FUN_CODE_6f5b();
          }
        }
        else {
          cVar2 = (0xf9 < bVar3 - 4) << 7;
          if (bVar3 == 0xfe) {
            thunk_FUN_CODE_33ff();
          }
          else {
            DAT_INTMEM_44 = 0;
          }
        }
      }
LAB_CODE_085d:
      if (DAT_INTMEM_44 != 0) break;
      DAT_INTMEM_45 = DAT_INTMEM_45 + 1;
      if ((DAT_INTMEM_45 & 1) != 0) {
        thunk_FUN_CODE_35fd();
        return;
      }
      FUN_CODE_890a(DAT_INTMEM_45);
      param_2 = param_2 + '\x02';
      BANK0_R2 = param_8;
      bVar4 = FUN_CODE_0c04();
      *(char *)(param_2 + '\x01') = *(char *)(param_2 + '\x01') + '\x01';
      bVar3 = BANK1_R0 - (cVar2 >> 7);
      bVar5 = *(byte *)(param_1 + (ushort)bVar4) - bVar3;
      bVar3 = (param_2 + '\x03') - (((*(byte *)(param_1 + (ushort)bVar4) < bVar3) << 7) >> 7);
      bVar4 = bVar5 - bVar3;
      param_4 = param_4 + '\x01';
      bVar3 = param_5 - (((bVar5 < bVar3) << 7) >> 7);
      param_6 = param_6 + '\x01';
      cVar2 = param_7 - (((bVar4 < bVar3) << 7) >> 7);
      param_7 = param_7 + '\x01';
      param_2 = param_2 + '\x06';
      bVar3 = *(byte *)(param_1 + (ushort)((bVar4 - bVar3) - cVar2));
      if (_1_0 == '\0') {
        thunk_FUN_CODE_0100(param_4,param_6);
        uVar1 = P0;
        *param_3 = uVar1;
        thunk_FUN_CODE_35fe(param_2 + '\x01',param_4 + '\x01');
        return;
      }
      _1_0 = '\0';
    }
  }
  return;
}

