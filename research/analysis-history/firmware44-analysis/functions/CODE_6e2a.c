
void FUN_CODE_6e2a(byte param_1)

{
  DAT_INTMEM_28 = param_1;
  DAT_EXTMEM_078f = param_1;
  if ((DAT_EXTMEM_094d == '\x01') || ((DAT_EXTMEM_094d != '\x02' && ((param_1 >> 1 & 1) != 0)))) {
    FUN_CODE_5ff2();
  }
  else {
    FUN_CODE_6dd6();
  }
  if ((DAT_EXTMEM_094e != '\x01') &&
     ((DAT_EXTMEM_094e == '\x02' || ((DAT_EXTMEM_078f >> 2 & 1) == 0)))) {
    FUN_CODE_6df2();
    return;
  }
  DAT_EXTMEM_1610 = 0x40;
  DAT_EXTMEM_1601 = DAT_EXTMEM_1601 & 0xfe;
  return;
}

