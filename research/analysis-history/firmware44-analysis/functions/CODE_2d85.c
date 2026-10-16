
undefined1 FUN_CODE_2d85(void)

{
  char cVar1;
  
  cVar1 = DAT_EXTMEM_0a84;
  if (DAT_EXTMEM_0a84 != DAT_EXTMEM_0a85) {
    DAT_EXTMEM_0a84 = DAT_EXTMEM_0a84 + 1;
    if (7 < DAT_EXTMEM_0a84) {
      DAT_EXTMEM_0a84 = 0;
    }
    return *(undefined1 *)
            (CONCAT11('\n' - (((0x8bU < (byte)(cVar1 * '\x02')) << 7) >> 7),cVar1 * '\x02' + 0x74) +
            1);
  }
  return 0;
}

