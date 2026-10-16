
void FUN_CODE_192c(char param_1,byte param_2)

{
  if ((param_2 == 0x82) && (param_1 == '\0')) {
    DAT_EXTMEM_0816 = DAT_EXTMEM_0816 | 4;
  }
  else if ((param_2 == 0x82) && (param_1 == '\x01')) {
    DAT_EXTMEM_0816 = DAT_EXTMEM_0816 & 0xfb;
  }
  DAT_EXTMEM_0754 = param_2;
  DAT_EXTMEM_0755 = param_1;
  if (param_2 != 0) {
    if (-1 < (char)param_2) {
      FUN_CODE_1b56(param_1);
      return;
    }
    DAT_EXTMEM_0754 = param_2 * '\x02';
    FUN_CODE_8961(*(undefined2 *)
                   (CONCAT11('\x1f' - (((0xe6U < (byte)((&DAT_CODE_7e3c)[DAT_EXTMEM_0754] * '\x03'))
                                       << 7) >> 7),(&DAT_CODE_7e3c)[DAT_EXTMEM_0754] * '\x03' + 0x19
                            ) + 1),param_1,(&DAT_CODE_7e3b)[DAT_EXTMEM_0754]);
  }
  return;
}

