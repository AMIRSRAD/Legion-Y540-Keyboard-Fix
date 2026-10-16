
void FUN_CODE_4f75(char param_1)

{
  char cVar1;
  
  DAT_EXTMEM_0795 = '\0';
  DAT_EXTMEM_1102 = 0x40;
  FUN_CODE_36eb();
  if (param_1 != '\0') {
    DAT_EXTMEM_0dd3 = 0;
    DAT_EXTMEM_08ad = 0;
  }
  if ((DAT_EXTMEM_2f52 >> 2 & 1) != 0) {
    DAT_EXTMEM_2f53 = 1;
    FUN_CODE_35dd();
    goto LAB_CODE_5093;
  }
  if ((DAT_EXTMEM_2f52 & 1) == 1) {
    FUN_CODE_86d6(0xf,0,DAT_EXTMEM_0dea,DAT_EXTMEM_0de9,DAT_EXTMEM_0de8);
    if ((DAT_EXTMEM_2f40 >> 3 & 1) != 0) {
      DAT_EXTMEM_2f40 = DAT_EXTMEM_2f40 & 0xf7;
    }
    DAT_EXTMEM_2f52 = 1;
    if ((DAT_EXTMEM_2f40 >> 1 & 1) == 0) {
      cVar1 = FUN_CODE_857a(1);
      if (cVar1 == '\x03') {
        cVar1 = '\x02';
        FUN_CODE_3a8e(0x95,7,1);
        if (cVar1 == '\0') {
          if (DAT_EXTMEM_0795 != '\0') {
            FUN_CODE_85b9(0,1,DAT_EXTMEM_0dea,DAT_EXTMEM_0de9,DAT_EXTMEM_0de8);
          }
          goto LAB_CODE_5093;
        }
      }
      else {
        cVar1 = FUN_CODE_857a(1,DAT_EXTMEM_0dea,DAT_EXTMEM_0de9,DAT_EXTMEM_0de8);
        if (cVar1 == '\x04') {
          cVar1 = '\x01';
          FUN_CODE_3a8e(0x95,7,1);
          if (cVar1 == '\0') {
            if (DAT_EXTMEM_0795 != '\0') {
              FUN_CODE_85b9(0,1,DAT_EXTMEM_0dea,DAT_EXTMEM_0de9,DAT_EXTMEM_0de8);
            }
LAB_CODE_5093:
            FUN_CODE_2715();
            return;
          }
          cVar1 = FUN_CODE_8561(DAT_EXTMEM_0dea,DAT_EXTMEM_0de9,DAT_EXTMEM_0de8);
          if (cVar1 != '\0') {
            DAT_EXTMEM_2f54 = cVar1;
            FUN_CODE_85a7(0,cVar1);
          }
        }
        else {
          cVar1 = FUN_CODE_857a(1,DAT_EXTMEM_0dea,DAT_EXTMEM_0de9,DAT_EXTMEM_0de8);
          if (((cVar1 == '\0') && (FUN_CODE_3cc8(), param_1 != '\0')) ||
             (cVar1 = FUN_CODE_857a(1,DAT_EXTMEM_0dea,DAT_EXTMEM_0de9,DAT_EXTMEM_0de8),
             cVar1 != '\0')) goto LAB_CODE_5093;
        }
      }
      FUN_CODE_32d3();
      FUN_CODE_85b9(0,1,DAT_EXTMEM_0dea,DAT_EXTMEM_0de9,DAT_EXTMEM_0de8);
    }
  }
  return;
}

