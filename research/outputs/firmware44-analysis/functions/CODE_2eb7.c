
char FUN_CODE_2eb7(undefined1 *param_1,undefined1 param_2,undefined1 param_3,byte param_4,
                  byte param_5)

{
  undefined1 *puVar1;
  byte bVar2;
  char cVar3;
  
  DAT_EXTMEM_077d = '\0';
  DAT_EXTMEM_077e = '\x03';
  DAT_EXTMEM_0777 = param_5;
  DAT_EXTMEM_0778 = param_3;
  DAT_EXTMEM_0779 = param_2;
  DAT_EXTMEM_077a = param_1;
  FUN_CODE_2d85();
  DAT_EXTMEM_077b = param_4;
  DAT_EXTMEM_077c = param_5;
  bVar2 = ~param_5;
  if (bVar2 == 0) {
    bVar2 = ~param_4;
  }
  if (bVar2 == 0) {
    return '\0';
  }
  if ((char)param_4 < '\0') {
    DAT_EXTMEM_077b = param_4 & 0x7f;
    DAT_EXTMEM_077d = '\x01';
  }
  puVar1 = DAT_EXTMEM_077a;
  FUN_CODE_566e(0,DAT_EXTMEM_077e,0,DAT_EXTMEM_0779,DAT_EXTMEM_077a);
  if (DAT_EXTMEM_077b < 0x40) {
    FUN_CODE_85a7(2,DAT_EXTMEM_077a,DAT_EXTMEM_0779,DAT_EXTMEM_0778);
    if (DAT_EXTMEM_077d == '\0') {
      bVar2 = DAT_EXTMEM_077b;
      FUN_CODE_85b9(DAT_EXTMEM_077c,1,DAT_EXTMEM_077a,DAT_EXTMEM_0779,DAT_EXTMEM_0778,
                    DAT_EXTMEM_077b);
      FUN_CODE_85b9(bVar2,2);
    }
    return DAT_EXTMEM_077e;
  }
  cVar3 = FUN_CODE_8930(DAT_EXTMEM_077c,DAT_EXTMEM_077b);
  nop();
  *param_1 = DAT_INTMEM_40;
  return cVar3 + (char)puVar1 * '\x02';
}

