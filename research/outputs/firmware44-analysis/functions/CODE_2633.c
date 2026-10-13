
void FUN_CODE_2633(void)

{
  if ((DAT_EXTMEM_2f52 & 0xf) == 0) {
    PCON = 2;
    nop();
    nop();
    nop();
    nop();
    nop();
    nop();
    nop();
    nop();
    DAT_EXTMEM_1e03 = 0;
  }
  return;
}

