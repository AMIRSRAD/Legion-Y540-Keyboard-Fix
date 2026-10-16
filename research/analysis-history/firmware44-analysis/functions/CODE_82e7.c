
void FUN_CODE_82e7(void)

{
  char cVar1;
  
  if (((DAT_EXTMEM_0800 == '\x10') || (DAT_EXTMEM_0800 == '3')) || (DAT_EXTMEM_0800 == 'U')) {
    FUN_CODE_8264();
  }
  if (DAT_EXTMEM_0801 != DAT_EXTMEM_0800) {
    DAT_EXTMEM_0801 = DAT_EXTMEM_0800;
  }
  if (DAT_EXTMEM_0800 == '\x03') {
    DAT_EXTMEM_1806 = 0;
    DAT_EXTMEM_0800 = 0x33;
    return;
  }
  if (DAT_EXTMEM_0800 == '\x05') {
    DAT_EXTMEM_1806 = 0;
    DAT_EXTMEM_088b = 0;
    DAT_EXTMEM_0800 = 0x55;
    DAT_EXTMEM_0895 = 0;
    DAT_EXTMEM_0896 = 0;
    return;
  }
  if (DAT_EXTMEM_0800 != '\x10') {
    cVar1 = '\0';
    if (DAT_EXTMEM_0800 == '0') {
LAB_CODE_8356:
      FUN_CODE_6e72(cVar1);
      DAT_EXTMEM_0800 = 0x10;
      return;
    }
    if (DAT_EXTMEM_0800 != '3') {
      if (DAT_EXTMEM_0800 == 'P') {
        cVar1 = DAT_EXTMEM_088b;
        if ((DAT_EXTMEM_088b == '\0') && (cVar1 = DAT_EXTMEM_0891 + -1, DAT_EXTMEM_0891 != '\0')) {
          DAT_EXTMEM_1806 = 0xff;
          DAT_EXTMEM_0891 = DAT_EXTMEM_0891 + -1;
          return;
        }
        goto LAB_CODE_8356;
      }
      if (DAT_EXTMEM_0800 == 'U') {
        DAT_EXTMEM_0891 = 0x32;
        return;
      }
      DAT_EXTMEM_1806 = 0;
      DAT_EXTMEM_0800 = 'U';
    }
  }
  return;
}

