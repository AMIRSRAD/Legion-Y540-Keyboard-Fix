
void FUN_CODE_19a7(undefined1 param_1,byte param_2)

{
  DAT_EXTMEM_074e = param_2;
  DAT_EXTMEM_074f = param_1;
  if (param_2 != 0) {
    if (-1 < (char)param_2) {
      FUN_CODE_1b56(param_1,param_2);
      return;
    }
    DAT_EXTMEM_074e = param_2 * '\x02';
    FUN_CODE_8961(*(undefined2 *)
                   (CONCAT11('\x1f' - (((0xe6U < (byte)((&DAT_CODE_7e3c)[DAT_EXTMEM_074e] * '\x03'))
                                       << 7) >> 7),(&DAT_CODE_7e3c)[DAT_EXTMEM_074e] * '\x03' + 0x19
                            ) + 1),param_1,(&DAT_CODE_7e3b)[DAT_EXTMEM_074e]);
  }
  return;
}

