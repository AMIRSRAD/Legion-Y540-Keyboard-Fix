
undefined1 FUN_CODE_27d2(byte *param_1,char param_2,byte param_3,char param_4)

{
  byte bVar1;
  undefined1 uVar2;
  char cVar3;
  char cVar4;
  byte bVar5;
  
  FUN_CODE_8844(0x780);
  cVar3 = FUN_CODE_8561();
  DAT_EXTMEM_0a73 = 0;
  cVar4 = FUN_CODE_890a(cVar3);
  cVar4 = FUN_CODE_2028((byte)(param_1 + cVar4) & param_3);
  bVar5 = cVar4 + BANK2_R2 + (char)param_1 * '\x02';
  bVar1 = *param_1;
  BANK2_R4 = cVar3;
  *param_1 = *param_1 & 0xf0 | bVar5 & 0xf;
  FUN_CODE_85a7(2,param_1 + (bVar5 & 0xf0 | bVar1 & 0xf),param_2 + -1,param_4 + '\x01',cVar3 + -1);
  if (DAT_EXTMEM_077d == '\0') {
    uVar2 = DAT_EXTMEM_077b;
    FUN_CODE_85b9(DAT_EXTMEM_077c,1,DAT_EXTMEM_077a,DAT_EXTMEM_0779,DAT_EXTMEM_0778,DAT_EXTMEM_077b)
    ;
    FUN_CODE_85b9(uVar2,2);
  }
  return DAT_EXTMEM_077e;
}

