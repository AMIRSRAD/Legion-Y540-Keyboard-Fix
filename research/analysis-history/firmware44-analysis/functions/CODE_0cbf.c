
void FUN_CODE_0cbf(void)

{
  undefined1 uVar1;
  char cVar2;
  
  FUN_CODE_8844(0x74a);
  cVar2 = FUN_CODE_8820(DAT_EXTMEM_074a,DAT_EXTMEM_074b,DAT_EXTMEM_074c,DAT_EXTMEM_074d,0,0,0,0);
  if (cVar2 != '\0') {
    cVar2 = -0x80;
    FUN_CODE_8820(DAT_EXTMEM_074a,DAT_EXTMEM_074b,DAT_EXTMEM_074c,DAT_EXTMEM_074d,5,0x26,0x5c,0);
    if (cVar2 < '\0') {
      FUN_CODE_8820(DAT_EXTMEM_074a,DAT_EXTMEM_074b,DAT_EXTMEM_074c,DAT_EXTMEM_074d,0,0xf4,0x24,0);
      if (cVar2 < '\0') {
        cVar2 = -0x80;
        FUN_CODE_8820(DAT_EXTMEM_074a,DAT_EXTMEM_074b,DAT_EXTMEM_074c,DAT_EXTMEM_074d,0,7,0xa1,0x20)
        ;
        if (cVar2 < '\0') {
          DAT_EXTMEM_0752 = 0;
          FUN_CODE_8703(DAT_EXTMEM_074a,DAT_EXTMEM_074b,DAT_EXTMEM_074c,DAT_EXTMEM_074d,0,0,0x80,0);
          FUN_CODE_878e(0,0,3,0xe8);
        }
        else {
          DAT_EXTMEM_0752 = 1;
          FUN_CODE_878e(0,0,3,0xe8,DAT_EXTMEM_074a,DAT_EXTMEM_074b,DAT_EXTMEM_074c,DAT_EXTMEM_074d);
          FUN_CODE_8703(0,0,4,0);
        }
      }
      else {
        DAT_EXTMEM_0752 = 2;
        FUN_CODE_878e(0,0,0xc,0x35,DAT_EXTMEM_074a,DAT_EXTMEM_074b,DAT_EXTMEM_074c,DAT_EXTMEM_074d);
        FUN_CODE_8703(0,0,0,100);
      }
      FUN_CODE_8844(0x74e);
      FUN_CODE_85a7(DAT_EXTMEM_0752,DAT_CODE_0e9c,DAT_CODE_0e9b,DAT_CODE_0e9a);
      uVar1 = DAT_EXTMEM_0751;
      FUN_CODE_8831(0x10,DAT_EXTMEM_074e,DAT_EXTMEM_074f,DAT_EXTMEM_0750,DAT_EXTMEM_0751);
      FUN_CODE_85a7(uVar1,DAT_CODE_0ea5,DAT_CODE_0ea4,DAT_CODE_0ea3);
      uVar1 = DAT_EXTMEM_0751;
      FUN_CODE_8831(8,DAT_EXTMEM_074e,DAT_EXTMEM_074f,DAT_EXTMEM_0750,DAT_EXTMEM_0751);
      FUN_CODE_85a7(uVar1,DAT_CODE_0ea2,DAT_CODE_0ea1,DAT_CODE_0ea0);
      FUN_CODE_85a7(DAT_EXTMEM_0751,DAT_CODE_0e9f,DAT_CODE_0e9e,DAT_CODE_0e9d);
    }
  }
  return;
}

