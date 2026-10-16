
void FUN_CODE_2665(void)

{
  if ((DAT_EXTMEM_2f52 & 0xf) == 0) {
    DAT_EXTMEM_1e03 = 1;
    PCON = 2;
    nop();
    nop();
    nop();
    nop();
    nop();
    nop();
    nop();
    nop();
  }
  return;
}

