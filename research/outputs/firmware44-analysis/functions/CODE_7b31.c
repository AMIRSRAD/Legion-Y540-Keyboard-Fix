
void FUN_CODE_7b31(undefined1 param_1,undefined1 param_2,byte param_3,byte param_4)

{
  byte bVar1;
  
  DAT_EXTMEM_0757 = param_3;
  DAT_EXTMEM_0758 = param_4;
  DAT_EXTMEM_0759 = param_1;
  DAT_EXTMEM_075a = param_2;
  DAT_EXTMEM_075b = 0;
  while( true ) {
    if (2 < DAT_EXTMEM_075b) {
      DAT_EXTMEM_0950 = 0;
      return;
    }
    bVar1 = param_3;
    if (param_3 == 0) {
      bVar1 = param_4 ^ *(byte *)CONCAT11('\x7f' - (((0xdc < DAT_EXTMEM_075b * '\x04') << 7) >> 7),
                                          DAT_EXTMEM_075b * '\x04' + 0x23);
    }
    if (bVar1 == 0) break;
    DAT_EXTMEM_075b = DAT_EXTMEM_075b + 1;
  }
  FUN_CODE_8961(*(undefined2 *)
                 (CONCAT11('\x7f' - (((0xdb < DAT_EXTMEM_075b * '\x04') << 7) >> 7),
                           DAT_EXTMEM_075b * '\x04' + 0x24) + 1),param_2);
  return;
}

