
void FUN_CODE_1841(char param_1,byte param_2)

{
  bool bVar1;
  byte bVar2;
  undefined *puVar3;
  char *pcVar4;
  
  DAT_EXTMEM_074e = param_2;
  DAT_EXTMEM_074f = param_1;
  FUN_CODE_76f5(0x4e,7,1);
  FUN_CODE_793d();
  if (param_2 == 0xff) {
    return;
  }
  DAT_EXTMEM_0753 = DAT_EXTMEM_074e;
  FUN_CODE_1f8c();
  DAT_INTMEM_8c = DAT_INTMEM_29;
  if ((DAT_EXTMEM_074e < 0xe0) << 7 < '\0') {
    if (DAT_EXTMEM_074e < 0x9c) goto LAB_CODE_1910;
    DAT_EXTMEM_0750 = DAT_EXTMEM_074e + 100;
    bVar2 = (byte)((ushort)DAT_EXTMEM_0750 * 3);
    DAT_EXTMEM_074e =
         *(byte *)CONCAT11((char)((ushort)DAT_EXTMEM_0750 * 3 >> 8) +
                           ('}' - (((0x76 < bVar2) << 7) >> 7)),bVar2 + 0x89);
    bVar2 = (byte)((ushort)DAT_EXTMEM_0750 * 3);
    pcVar4 = (char *)CONCAT11((char)((ushort)DAT_EXTMEM_0750 * 3 >> 8) +
                              ('}' - (((0x75 < bVar2) << 7) >> 7)),bVar2 + 0x8a);
    DAT_EXTMEM_0751 = *pcVar4;
    DAT_EXTMEM_0752 = pcVar4[1];
    FUN_CODE_19fc(DAT_EXTMEM_074f,DAT_EXTMEM_0753);
    bVar1 = CARRY1(DAT_EXTMEM_0752,DAT_EXTMEM_074e);
    DAT_EXTMEM_0752 = DAT_EXTMEM_0752 + DAT_EXTMEM_074e;
    DAT_EXTMEM_0751 = DAT_EXTMEM_0751 - ((bVar1 << 7) >> 7);
    puVar3 = (undefined *)CONCAT11(DAT_EXTMEM_0751,DAT_EXTMEM_0752);
    bVar2 = 0;
  }
  else {
    DAT_EXTMEM_0750 = (DAT_EXTMEM_074e + 0x20) * '\x02';
    bVar2 = DAT_EXTMEM_0753;
    FUN_CODE_1582(DAT_EXTMEM_074f);
    if (bVar2 == 1) {
      DAT_EXTMEM_0750 = DAT_EXTMEM_0750 + 1;
    }
    puVar3 = &DAT_CODE_7dfb;
    bVar2 = DAT_EXTMEM_0750;
  }
  DAT_EXTMEM_074e = puVar3[bVar2];
LAB_CODE_1910:
  FUN_CODE_192c(DAT_EXTMEM_074f,DAT_EXTMEM_074e);
  if (DAT_EXTMEM_074f == '\x01') {
    FUN_CODE_7a31();
  }
  DAT_INTMEM_29 = DAT_INTMEM_8c;
  return;
}

