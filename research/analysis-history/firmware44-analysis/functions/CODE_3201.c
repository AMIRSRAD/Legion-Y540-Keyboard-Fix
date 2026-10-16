
undefined1
FUN_CODE_3201(undefined1 param_1,undefined1 param_2,char param_3,undefined1 param_4,char param_5)

{
  undefined1 uVar1;
  
  DAT_EXTMEM_0763 = param_5;
  DAT_EXTMEM_0766 = param_1;
  DAT_EXTMEM_0767 = param_2;
  DAT_EXTMEM_0770 = param_4;
  if (param_5 == '\x01') {
    if (param_3 == '\x03') {
      DAT_EXTMEM_0777 = DAT_EXTMEM_076e;
      DAT_EXTMEM_0778 = DAT_EXTMEM_076f;
      uVar1 = FUN_CODE_3029(DAT_EXTMEM_076a,DAT_EXTMEM_0769,DAT_EXTMEM_0768,param_1,param_2,param_4)
      ;
      return uVar1;
    }
  }
  else {
    if (param_5 == '\t') {
      DAT_EXTMEM_0777 = DAT_EXTMEM_076e;
      DAT_EXTMEM_0778 = DAT_EXTMEM_076f;
      uVar1 = FUN_CODE_3044(DAT_EXTMEM_076d,DAT_EXTMEM_076c,DAT_EXTMEM_076b,param_1,param_2,param_4)
      ;
      return uVar1;
    }
    if (param_5 == '\x02') {
      DAT_EXTMEM_0777 = DAT_EXTMEM_076e;
      DAT_EXTMEM_0778 = DAT_EXTMEM_076f;
      FUN_CODE_30a5(DAT_EXTMEM_076d,DAT_EXTMEM_076c,DAT_EXTMEM_076b,param_1,param_2,param_4);
      return 0;
    }
  }
  DAT_EXTMEM_0775 = DAT_EXTMEM_076e;
  DAT_EXTMEM_0776 = DAT_EXTMEM_076f;
  uVar1 = FUN_CODE_3120(DAT_EXTMEM_076a,DAT_EXTMEM_0769,DAT_EXTMEM_0768,param_4);
  return uVar1;
}

