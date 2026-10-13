
byte FUN_CODE_19fc(undefined1 param_1,byte param_2,byte param_3,byte param_4)

{
  char cVar1;
  byte bVar2;
  byte bVar3;
  
  DAT_EXTMEM_0755 = 0;
  DAT_EXTMEM_0756 = 0;
  if ((param_4 >> 1 & 1) != 0) {
    param_3 = DAT_INTMEM_8c;
    if ((DAT_INTMEM_8c >> 1 & 1) != 0 || (DAT_INTMEM_8c >> 2 & 1) != 0) {
      param_3 = 0;
      DAT_EXTMEM_0755 = 1;
      cVar1 = '\x01';
      while (cVar1 = cVar1 + -1, cVar1 != '\0') {
        DAT_EXTMEM_0755 = DAT_EXTMEM_0755 << 1;
      }
    }
    DAT_EXTMEM_0756 = 1;
  }
  if ((param_4 >> 2 & 1) != 0) {
    if ((DAT_INTMEM_8c >> 3 & 1) != 0) {
      bVar2 = 1;
      cVar1 = DAT_EXTMEM_0756 + 1;
      while (cVar1 = cVar1 + -1, cVar1 != '\0') {
        bVar2 = bVar2 << 1;
      }
      param_3 = DAT_EXTMEM_0755;
      DAT_EXTMEM_0755 = bVar2 | DAT_EXTMEM_0755;
    }
    DAT_EXTMEM_0756 = DAT_EXTMEM_0756 + 1;
  }
  bVar2 = param_4;
  if ((param_4 >> 3 & 1) != 0) {
    if ((DAT_INTMEM_8c >> 4 & 1) != 0) {
      bVar3 = 1;
      cVar1 = DAT_EXTMEM_0756 + 1;
      while (cVar1 = cVar1 + -1, cVar1 != '\0') {
        bVar3 = bVar3 << 1;
      }
      param_3 = DAT_EXTMEM_0756;
      bVar2 = DAT_EXTMEM_0755;
      DAT_EXTMEM_0755 = bVar3 | DAT_EXTMEM_0755;
    }
    DAT_EXTMEM_0756 = DAT_EXTMEM_0756 + 1;
  }
  DAT_EXTMEM_0754 = param_4;
  if ((param_4 >> 4 & 1) != 0) {
    bVar2 = param_2;
    FUN_CODE_16e7(param_4,param_1,param_3);
    if (bVar2 == 1) {
      bVar3 = 1;
      cVar1 = DAT_EXTMEM_0756 + 1;
      while (cVar1 = cVar1 + -1, cVar1 != '\0') {
        bVar3 = bVar3 << 1;
      }
      bVar2 = DAT_EXTMEM_0755;
      DAT_EXTMEM_0755 = bVar3 | DAT_EXTMEM_0755;
    }
    DAT_EXTMEM_0756 = DAT_EXTMEM_0756 + 1;
  }
  if ((DAT_EXTMEM_0754 >> 5 & 1) != 0) {
    FUN_CODE_1582(DAT_EXTMEM_0754,param_1);
    if (param_2 == 1) {
      bVar2 = 1;
      cVar1 = DAT_EXTMEM_0756 + 1;
      while (cVar1 = cVar1 + -1, cVar1 != '\0') {
        bVar2 = bVar2 << 1;
      }
      param_2 = DAT_EXTMEM_0755;
      DAT_EXTMEM_0755 = bVar2 | DAT_EXTMEM_0755;
    }
    DAT_EXTMEM_0756 = DAT_EXTMEM_0756 + 1;
    bVar2 = param_2;
  }
  if ((DAT_EXTMEM_0754 >> 6 & 1) != 0) {
    FUN_CODE_7a32();
    if (bVar2 == 0xff) {
      bVar3 = 1;
      cVar1 = DAT_EXTMEM_0756 + 1;
      while (cVar1 = cVar1 + -1, cVar1 != '\0') {
        bVar3 = bVar3 << 1;
      }
      bVar2 = DAT_EXTMEM_0755;
      DAT_EXTMEM_0755 = bVar3 | DAT_EXTMEM_0755;
    }
    DAT_EXTMEM_0756 = DAT_EXTMEM_0756 + 1;
  }
  if ((char)DAT_EXTMEM_0754 < '\0') {
    FUN_CODE_7a35();
    if (bVar2 == 0xff) {
      bVar2 = 1;
      cVar1 = DAT_EXTMEM_0756 + 1;
      while (cVar1 = cVar1 + -1, cVar1 != '\0') {
        bVar2 = bVar2 << 1;
      }
      DAT_EXTMEM_0755 = bVar2 | DAT_EXTMEM_0755;
    }
    DAT_EXTMEM_0756 = DAT_EXTMEM_0756 + 1;
  }
  return DAT_EXTMEM_0755;
}

