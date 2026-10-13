
byte FUN_CODE_2bbe(byte param_1,byte param_2,undefined1 param_3,byte param_4)

{
  byte bVar1;
  undefined1 uVar2;
  undefined2 uVar3;
  
  DAT_EXTMEM_0779 = param_4;
  if ((param_4 == 1) || (DAT_EXTMEM_0973 == '\0')) {
    DAT_EXTMEM_077a = param_2 ^ 1 | param_1;
    if (DAT_EXTMEM_077a == 0) {
      DAT_EXTMEM_077b = 1;
      FUN_CODE_85a7(DAT_EXTMEM_0a6d);
      return DAT_EXTMEM_077b;
    }
    DAT_EXTMEM_077a = 0;
    DAT_EXTMEM_077b = 2;
    FUN_CODE_85a7(1);
    uVar3 = 1;
    uVar2 = DAT_EXTMEM_0a6d;
  }
  else {
    bVar1 = param_4 ^ 0xcd;
    if (bVar1 != 0) {
      FUN_CODE_33af();
      DAT_EXTMEM_077a = param_3;
      DAT_EXTMEM_077b = param_4;
      return param_4;
    }
    DAT_EXTMEM_077b = 3;
    DAT_EXTMEM_077a = bVar1;
    if (DAT_EXTMEM_080f == '\x01') {
      DAT_EXTMEM_080f = '\0';
      FUN_CODE_85a7(0xcd);
      FUN_CODE_85b9(DAT_EXTMEM_0811,1);
      uVar3 = 2;
      uVar2 = 0;
    }
    else {
      FUN_CODE_85a7(0xcd);
      FUN_CODE_85b9(DAT_EXTMEM_0812,1);
      uVar2 = *(undefined1 *)CONCAT11(0xe,DAT_EXTMEM_0812);
      uVar3 = 2;
    }
  }
  FUN_CODE_85b9(uVar2,uVar3);
  return DAT_EXTMEM_077b;
}

