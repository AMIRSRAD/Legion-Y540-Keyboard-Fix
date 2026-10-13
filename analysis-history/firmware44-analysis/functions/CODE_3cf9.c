
/* WARNING: Removing unreachable block (CODE,0x3d43) */
/* WARNING: Removing unreachable block (CODE,0x3d5b) */
/* WARNING: Removing unreachable block (CODE,0x3d61) */
/* WARNING: Removing unreachable block (CODE,0x3dd4) */
/* WARNING: Removing unreachable block (CODE,0x3dd0) */
/* WARNING: Removing unreachable block (CODE,0x3dd6) */
/* WARNING: Removing unreachable block (CODE,0x3d58) */

undefined1 FUN_CODE_3cf9(undefined1 *param_1)

{
  undefined1 uVar1;
  char cVar2;
  char cVar3;
  
  uVar1 = *param_1;
  cVar2 = param_1[1];
  DAT_EXTMEM_076a = 1;
  FUN_CODE_88b1(6,DAT_EXTMEM_0dea,DAT_EXTMEM_0de9,DAT_EXTMEM_0de8);
  FUN_CODE_86d6(uVar1,9,DAT_EXTMEM_0dea,DAT_EXTMEM_0de9,DAT_EXTMEM_0de8);
  BANK0_R4 = 0xdd;
  BANK0_R5 = 0x3d;
  FUN_CODE_85b9(1,0xc);
  BANK0_R4 = 0xee;
  BANK0_R5 = 0x3d;
  cVar3 = FUN_CODE_8632(9,DAT_EXTMEM_0dea,DAT_EXTMEM_0de9,DAT_EXTMEM_0de8);
  if (cVar3 == '\0' && cVar2 == '\0') {
    cVar2 = '\x01';
    BANK0_R4 = 9;
    BANK0_R5 = 0x3e;
    FUN_CODE_3a88(cVar3);
    if (cVar2 == '\0') {
      BANK0_R4 = 0x1e;
      BANK0_R5 = 0x3e;
      FUN_CODE_85b9(0,1,DAT_EXTMEM_0dea,DAT_EXTMEM_0de9,DAT_EXTMEM_0de8);
    }
    else {
      BANK0_R4 = 0x25;
      BANK0_R5 = 0x3e;
      FUN_CODE_36cf();
    }
  }
  else {
    BANK0_R4 = 0xfa;
    BANK0_R5 = 0x3d;
    FUN_CODE_8881(6);
    BANK0_R4 = 0xfd;
    BANK0_R5 = 0x3d;
    FUN_CODE_3bb9();
  }
  return 0;
}

