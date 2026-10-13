
void FUN_CODE_2200(char param_1)

{
  FUN_CODE_059d();
  SP = 0xa0;
  FUN_CODE_0f76();
  FUN_CODE_6000();
  if (param_1 == '3') {
    DAT_EXTMEM_1000 = DAT_EXTMEM_1000 & 0x7f;
    nop();
    TXCNTH = 1;
    nop();
    TXCNTH = 1;
    nop();
    TXCNTH = 1;
    nop();
    TXCNTH = 1;
    nop();
    nop();
    DAT_EXTMEM_0045 = 0;
    FUN_CODE_7fd8();
    FUN_CODE_0c47();
    FUN_CODE_05de();
  }
  else {
    FUN_CODE_0ec1();
    FUN_CODE_8000();
    FUN_CODE_05a7();
  }
  do {
    do {
      FUN_CODE_6fa8();
    } while (param_1 != -1);
    FUN_CODE_07c4();
    FUN_CODE_05de();
    nop();
    nop();
    nop();
    nop();
    if ((DAT_INTMEM_26 == '\0') && (DAT_INTMEM_27 == '\0')) {
      PCON = 1;
    }
  } while( true );
}

