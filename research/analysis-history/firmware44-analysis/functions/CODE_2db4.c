
undefined1 FUN_CODE_2db4(undefined1 param_1,undefined1 param_2,undefined1 param_3,char param_4)

{
  bool bVar1;
  char cVar2;
  undefined1 uVar3;
  byte bVar4;
  
  DAT_EXTMEM_077b = '\0';
  DAT_EXTMEM_077c = 0x21;
  DAT_EXTMEM_077e = '\x01';
  DAT_EXTMEM_0777 = param_4;
  DAT_EXTMEM_0778 = param_3;
  DAT_EXTMEM_0779 = param_2;
  DAT_EXTMEM_077a = param_1;
  do {
    FUN_CODE_1f4e();
    DAT_EXTMEM_077d = param_4;
    if (param_4 == -1) break;
    param_4 = '\0';
    FUN_CODE_27d2(0x7d,7,1,0,0,0);
    DAT_EXTMEM_077e = '\0';
  } while (DAT_EXTMEM_0a72 == '\0');
  if (DAT_EXTMEM_0a6e != DAT_EXTMEM_0a6f) {
    DAT_EXTMEM_0a73 = '\x01';
  }
  DAT_EXTMEM_0a72 = 0;
  if ((DAT_EXTMEM_0a73 == '\0') || (DAT_EXTMEM_077e != '\0')) {
    if (DAT_EXTMEM_073d != '\x01') {
      return 0;
    }
    if (DAT_EXTMEM_0953 == '\0') {
      bVar4 = 0;
      do {
        if (*(char *)CONCAT11('\t' - (((0xaa < bVar4) << 7) >> 7),bVar4 + 0x55) != '\0') {
          bVar1 = true;
          break;
        }
        bVar4 = bVar4 + 1;
        bVar1 = false;
      } while (bVar4 != 0x1e);
    }
    else {
      bVar1 = true;
    }
    DAT_EXTMEM_073d = 0;
    if (!bVar1) {
      return 0;
    }
  }
  else {
    DAT_EXTMEM_073e = 0;
    DAT_EXTMEM_073f = 0;
  }
  DAT_EXTMEM_073d = 0;
  DAT_EXTMEM_0952 = 1;
  DAT_EXTMEM_0953 = DAT_EXTMEM_0a6f;
  if (DAT_EXTMEM_0973 == '\0') {
    DAT_EXTMEM_077b = DAT_EXTMEM_0973;
    DAT_EXTMEM_077c = 8;
    uVar3 = 0x53;
    cVar2 = '\0';
  }
  else {
    uVar3 = 0x52;
    cVar2 = DAT_EXTMEM_077b;
  }
  FUN_CODE_5600(cVar2,DAT_EXTMEM_077c,9,uVar3,DAT_EXTMEM_0779,DAT_EXTMEM_077a);
  DAT_EXTMEM_0a6e = DAT_EXTMEM_0a6f;
  return DAT_EXTMEM_077c;
}

