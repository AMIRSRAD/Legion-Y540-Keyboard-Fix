
void FUN_CODE_806d(void)

{
  FUN_CODE_7f65();
  if ((((DAT_EXTMEM_0e00 != '\x19') || (DAT_EXTMEM_0e01 != 'x')) || (DAT_EXTMEM_0e02 != '\x03')) ||
     (DAT_EXTMEM_0e03 != '\x05')) {
    DAT_EXTMEM_0746 = '\0';
    DAT_EXTMEM_0747 = '\0';
    do {
      *(undefined1 *)CONCAT11(DAT_EXTMEM_0746 + '\x0e',DAT_EXTMEM_0747) = 0;
      DAT_EXTMEM_0747 = DAT_EXTMEM_0747 + '\x01';
      if (DAT_EXTMEM_0747 == '\0') {
        DAT_EXTMEM_0746 = DAT_EXTMEM_0746 + '\x01';
      }
    } while ((DAT_EXTMEM_0746 != '\x01') || (DAT_EXTMEM_0747 != '\0'));
    DAT_EXTMEM_0e00 = '\x19';
    DAT_EXTMEM_0e01 = 'x';
    DAT_EXTMEM_0e02 = '\x03';
    DAT_EXTMEM_0e03 = '\x05';
    DAT_EXTMEM_0e10 = 0;
    FUN_CODE_059d();
    FUN_CODE_7f40();
    FUN_CODE_05a4();
  }
  return;
}

