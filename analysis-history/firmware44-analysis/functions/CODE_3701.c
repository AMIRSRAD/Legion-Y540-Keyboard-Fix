
char FUN_CODE_3701(void)

{
  char cVar1;
  char cVar2;
  undefined1 *puVar3;
  char cVar4;
  
  if (10 < DAT_EXTMEM_0c34) {
    DAT_EXTMEM_0c34 = 10;
  }
  if (DAT_EXTMEM_0c33 == '\0') {
    DAT_EXTMEM_0781 = '\f';
    DAT_EXTMEM_0782 = (undefined1 *)0x35;
    DAT_EXTMEM_0783 = 0;
    DAT_EXTMEM_0784 = 0;
    cVar2 = DAT_EXTMEM_0c32;
    puVar3 = DAT_EXTMEM_0c31;
    while (cVar1 = ((DAT_EXTMEM_0784 < DAT_EXTMEM_0c34) << 7) >> 7, cVar4 = DAT_EXTMEM_0783 + cVar1,
          (DAT_EXTMEM_0783 < (byte)-cVar1) << 7 < '\0') {
      *(undefined1 *)CONCAT11(DAT_EXTMEM_0781,DAT_EXTMEM_0782) =
           *(undefined1 *)CONCAT11(cVar2,puVar3);
      DAT_EXTMEM_0782 = DAT_EXTMEM_0782 + '\x01';
      if (DAT_EXTMEM_0782 == (undefined1 *)0x0) {
        DAT_EXTMEM_0781 = DAT_EXTMEM_0781 + '\x01';
      }
      puVar3 = puVar3 + '\x01';
      if (puVar3 == (undefined1 *)0x0) {
        cVar2 = cVar2 + '\x01';
      }
      DAT_EXTMEM_0784 = DAT_EXTMEM_0784 + 1;
      if (DAT_EXTMEM_0784 == 0) {
        DAT_EXTMEM_0783 = DAT_EXTMEM_0783 + 1;
      }
    }
  }
  else if (DAT_EXTMEM_0c32 == -0x40) {
    DAT_EXTMEM_077f = '\f';
    DAT_EXTMEM_0780 = '5';
    DAT_EXTMEM_0783 = 0;
    DAT_EXTMEM_0784 = 0;
    puVar3 = DAT_EXTMEM_0c31;
    while (cVar2 = ((DAT_EXTMEM_0784 < DAT_EXTMEM_0c34) << 7) >> 7, cVar4 = DAT_EXTMEM_0783 + cVar2,
          DAT_EXTMEM_0783 < (byte)-cVar2) {
      *(undefined1 *)CONCAT11(DAT_EXTMEM_077f,DAT_EXTMEM_0780) = *puVar3;
      puVar3 = puVar3 + '\x01';
      DAT_EXTMEM_0780 = DAT_EXTMEM_0780 + '\x01';
      if (DAT_EXTMEM_0780 == '\0') {
        DAT_EXTMEM_077f = DAT_EXTMEM_077f + '\x01';
      }
      DAT_EXTMEM_0784 = DAT_EXTMEM_0784 + 1;
      if (DAT_EXTMEM_0784 == 0) {
        DAT_EXTMEM_0783 = DAT_EXTMEM_0783 + 1;
      }
    }
  }
  else {
    DAT_EXTMEM_0781 = DAT_EXTMEM_0c32;
    DAT_EXTMEM_0782 = DAT_EXTMEM_0c31;
    DAT_EXTMEM_077f = '\f';
    DAT_EXTMEM_0780 = '5';
    cVar4 = FUN_CODE_5600(0,DAT_EXTMEM_0c34,DAT_EXTMEM_0c32,DAT_EXTMEM_0c31);
  }
  return cVar4;
}

