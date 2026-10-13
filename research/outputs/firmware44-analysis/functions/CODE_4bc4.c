
void FUN_CODE_4bc4(byte param_1)

{
  char cVar1;
  byte bVar2;
  char cVar3;
  
  cVar1 = '\0';
  if (DAT_EXTMEM_0dd2 == '\0') {
    return;
  }
  if (DAT_EXTMEM_0dd3 != '\0') {
    return;
  }
  if ((DAT_EXTMEM_2f52 >> 3 & 1) == 0) {
    cVar3 = FUN_CODE_857a(0x11,DAT_EXTMEM_0dea,DAT_EXTMEM_0de9,DAT_EXTMEM_0de8);
    if (cVar3 == '\0') {
      bVar2 = FUN_CODE_8632(0xf);
      if (0x13U - (((bVar2 < 0x88) << 7) >> 7) <= param_1) {
        cVar1 = '\x01';
        goto LAB_CODE_4c43;
      }
    }
    else {
      bVar2 = FUN_CODE_8632(0xf);
      if ((byte)-(((bVar2 < 8) << 7) >> 7) <= param_1) {
        cVar1 = '\x01';
        goto LAB_CODE_4c43;
      }
    }
    FUN_CODE_866a(0,0xf,1);
  }
  else {
    DAT_EXTMEM_2f52 = 10;
    FUN_CODE_86d6(0xf,0,DAT_EXTMEM_0dea,DAT_EXTMEM_0de9,DAT_EXTMEM_0de8);
    FUN_CODE_85b9(1,0x11);
  }
LAB_CODE_4c43:
  if (DAT_EXTMEM_0891 != '\0') {
    if (DAT_EXTMEM_0800 == '3') {
      cVar3 = -0x80;
    }
    else {
      cVar3 = '\0';
    }
    if (-1 < cVar3) {
      cVar1 = '\0';
    }
  }
  if ((DAT_EXTMEM_08ae != '\0') && (DAT_EXTMEM_0902 != '\x01')) {
    cVar1 = '\0';
  }
  if ((cVar1 != '\0') && (((DAT_EXTMEM_16e0 >> 4 & 1) == 1 || ((DAT_EXTMEM_16e0 >> 5 & 1) != 1)))) {
    cVar1 = '\0';
  }
  if (cVar1 != '\0') {
    DAT_EXTMEM_0dd3 = '\x01';
    DAT_EXTMEM_08ad = 1;
    DAT_EXTMEM_1b06 = 0x80;
    DAT_EXTMEM_111c = 0x80;
    DAT_EXTMEM_111d = DAT_EXTMEM_111d | 0xc0;
    FUN_CODE_7fe5();
    DAT_EXTMEM_1e20 = 0xc0;
    FUN_CODE_813c();
    DAT_EXTMEM_1e20 = 0x80;
    DAT_EXTMEM_1e40 = 3;
    DAT_EXTMEM_111d = DAT_EXTMEM_111d & 0x3f;
    DAT_EXTMEM_1b06 = 0x80;
    DAT_EXTMEM_111c = 0x80;
  }
  return;
}

