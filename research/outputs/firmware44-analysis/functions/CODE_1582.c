
undefined1 FUN_CODE_1582(char param_1,byte param_2)

{
  char cVar1;
  char cVar2;
  byte bVar3;
  undefined2 uStack_1;
  
  DAT_EXTMEM_0758 = 0;
  if (param_2 < 0x9c) {
    DAT_EXTMEM_0757 = param_1;
    DAT_EXTMEM_0758 = 0;
    return 0;
  }
  DAT_EXTMEM_0759 = param_2 + 0x70;
  cVar1 = '\x03';
  bVar3 = 0xff - (((0x8f < param_2) << 7) >> 7);
  do {
    DAT_EXTMEM_0759 = DAT_EXTMEM_0759 >> 1 | bVar3 << 7;
    cVar1 = cVar1 + -1;
    bVar3 = bVar3 >> 1;
  } while (cVar1 != '\0');
  DAT_EXTMEM_075a = param_2 + 0x70 & 7;
  DAT_EXTMEM_0757 = param_1;
  if (param_1 != '\x01') {
    if (((DAT_INTMEM_8c >> 6 & 1) != 0) && (param_1 == '\0')) {
      cVar1 = -(((0x1f < DAT_EXTMEM_0759) << 7) >> 7);
      uStack_1 = (byte *)CONCAT11(cVar1,DAT_EXTMEM_0759 - 0x20);
      bVar3 = 1;
      cVar2 = DAT_EXTMEM_075a + 1;
      while (cVar2 = cVar2 + -1, cVar2 != '\0') {
        bVar3 = bVar3 << 1;
      }
      *uStack_1 = bVar3 | *(byte *)CONCAT11(cVar1,DAT_EXTMEM_0759 - 0x20);
    }
    if ((DAT_INTMEM_8c >> 6 & 1) != 1) {
      bVar3 = 1;
      cVar1 = DAT_EXTMEM_075a + 1;
      while (cVar1 = cVar1 + -1, cVar1 != '\0') {
        bVar3 = bVar3 << 1;
      }
      if ((bVar3 & *(byte *)CONCAT11(-(((0x1f < DAT_EXTMEM_0759) << 7) >> 7),DAT_EXTMEM_0759 - 0x20)
          ) == 0) {
        return DAT_EXTMEM_0758;
      }
    }
    DAT_EXTMEM_0758 = 1;
    return 1;
  }
  if ((DAT_INTMEM_8c >> 6 & 1) == 0) {
    bVar3 = 1;
    cVar1 = DAT_EXTMEM_075a + 1;
    while (cVar1 = cVar1 + -1, cVar1 != '\0') {
      bVar3 = bVar3 << 1;
    }
    if ((bVar3 & *(byte *)CONCAT11(-(((0x1f < DAT_EXTMEM_0759) << 7) >> 7),DAT_EXTMEM_0759 - 0x20))
        == 0) {
      DAT_EXTMEM_0758 = 0;
      goto LAB_CODE_1637;
    }
  }
  else {
    bVar3 = 1;
    cVar1 = DAT_EXTMEM_075a + 1;
    while (cVar1 = cVar1 + -1, cVar1 != '\0') {
      bVar3 = bVar3 << 1;
    }
    if ((bVar3 & *(byte *)CONCAT11(-(((0x1f < DAT_EXTMEM_0759) << 7) >> 7),DAT_EXTMEM_0759 - 0x20))
        == 0) {
      DAT_EXTMEM_0758 = 0;
      goto LAB_CODE_1637;
    }
  }
  DAT_EXTMEM_0758 = 1;
LAB_CODE_1637:
  cVar1 = -(((0x1f < DAT_EXTMEM_0759) << 7) >> 7);
  uStack_1 = (byte *)CONCAT11(cVar1,DAT_EXTMEM_0759 - 0x20);
  bVar3 = 1;
  cVar2 = DAT_EXTMEM_075a + 1;
  while (cVar2 = cVar2 + -1, cVar2 != '\0') {
    bVar3 = bVar3 << 1;
  }
  *uStack_1 = ~bVar3 & *(byte *)CONCAT11(cVar1,DAT_EXTMEM_0759 - 0x20);
  return DAT_EXTMEM_0758;
}

