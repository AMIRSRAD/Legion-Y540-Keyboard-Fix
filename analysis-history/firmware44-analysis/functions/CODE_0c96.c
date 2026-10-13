
void FUN_CODE_0c96(char param_1)

{
  char cVar1;
  
  TR1 = 0;
  ET1 = 0;
  nop();
  nop();
  nop();
  nop();
  for (; param_1 != '\0'; param_1 = param_1 + -1) {
    TH1 = 0xfd;
    TL1 = 0;
    TF1 = 0;
    TR1 = 1;
    do {
      cVar1 = TF1;
    } while (cVar1 == '\0');
    TR1 = 0;
    TF1 = 0;
  }
  ET1 = 1;
  return;
}

