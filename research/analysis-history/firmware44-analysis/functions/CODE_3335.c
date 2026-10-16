
char FUN_CODE_3335(void)

{
  byte bVar1;
  undefined1 *puVar2;
  char cVar3;
  
  if (10 < DAT_EXTMEM_0c34) {
    DAT_EXTMEM_0c34 = 10;
  }
  cVar3 = '\0';
  if (DAT_EXTMEM_0c33 != '\0') {
    if (DAT_EXTMEM_0c32 == -0x40) {
      DAT_EXTMEM_077f = '\f';
      DAT_EXTMEM_0780 = (undefined1 *)0x35;
      puVar2 = DAT_EXTMEM_0c31;
      for (bVar1 = 0; cVar3 = bVar1 - DAT_EXTMEM_0c34, bVar1 < DAT_EXTMEM_0c34; bVar1 = bVar1 + 1) {
        *puVar2 = *(undefined1 *)CONCAT11(DAT_EXTMEM_077f,DAT_EXTMEM_0780);
        puVar2 = puVar2 + '\x01';
        DAT_EXTMEM_0780 = DAT_EXTMEM_0780 + '\x01';
        if (DAT_EXTMEM_0780 == (undefined1 *)0x0) {
          DAT_EXTMEM_077f = DAT_EXTMEM_077f + '\x01';
        }
      }
    }
    else {
      DAT_EXTMEM_077f = DAT_EXTMEM_0c32;
      DAT_EXTMEM_0780 = DAT_EXTMEM_0c31;
      cVar3 = FUN_CODE_5600(DAT_EXTMEM_0c34,0xc,0x35,DAT_EXTMEM_0c32);
    }
  }
  return cVar3;
}

