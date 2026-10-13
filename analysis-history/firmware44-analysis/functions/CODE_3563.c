
char FUN_CODE_3563(undefined1 param_1,undefined1 param_2,undefined1 param_3,byte param_4)

{
  undefined1 uVar1;
  
  DAT_EXTMEM_0785 = param_3;
  DAT_EXTMEM_0786 = param_2;
  DAT_EXTMEM_0787 = param_1;
  DAT_EXTMEM_0788 = param_4;
  **(undefined1 **)
    CONCAT11('\r' - (((0x3cU < (byte)(DAT_EXTMEM_0789 * '\b')) << 7) >> 7),
             DAT_EXTMEM_0789 * '\b' - 0x3d) = 1;
  DAT_EXTMEM_078b = 0;
  while( true ) {
    if (DAT_EXTMEM_0788 <= DAT_EXTMEM_078b) break;
    uVar1 = FUN_CODE_857a(DAT_EXTMEM_078b,DAT_EXTMEM_0787,DAT_EXTMEM_0786,DAT_EXTMEM_0785);
    **(undefined1 **)
      CONCAT11('\r' - (((0x3aU < (byte)(DAT_EXTMEM_0789 * '\b')) << 7) >> 7),
               DAT_EXTMEM_0789 * '\b' - 0x3b) = uVar1;
    DAT_EXTMEM_078b = DAT_EXTMEM_078b + 1;
  }
  return DAT_EXTMEM_078b - DAT_EXTMEM_0788;
}

