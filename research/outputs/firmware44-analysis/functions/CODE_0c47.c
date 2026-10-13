
undefined1 FUN_CODE_0c47(void)

{
  TR0 = 0;
  TF0 = 0;
  TL0 = 0;
  TH0 = 0xfd;
  TMOD = 0x11;
  TR0 = 1;
  ET0 = 1;
  TR1 = 0;
  TF1 = 0;
  TL1 = 1;
  TH1 = 0xfa;
  ET1 = 1;
  return 0;
}

