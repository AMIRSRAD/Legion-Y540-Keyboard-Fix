
undefined1 FUN_CODE_4614(undefined1 *param_1,char *param_2,undefined1 param_3,undefined1 param_4)

{
  char *pcVar1;
  byte bVar2;
  undefined1 uVar3;
  undefined1 *puVar4;
  
  DAT_EXTMEM_074f = param_4;
  DAT_EXTMEM_0750 = param_3;
  DAT_EXTMEM_0751 = param_2;
  FUN_CODE_8850(0x752);
  nop();
  nop();
  nop();
  nop();
  pcVar1 = DAT_EXTMEM_0751;
  bVar2 = FUN_CODE_857a(1,DAT_EXTMEM_0750,DAT_EXTMEM_074f);
  if (9 < bVar2) {
    puVar4 = &DAT_EXTMEM_0752;
    FUN_CODE_8850();
    nop();
    nop();
    nop();
    P1 = *param_1;
    *pcVar1 = *pcVar1 + '\x01';
    return puVar4[3];
  }
                    /* WARNING: Could not recover jumptable at 0x4646. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  uVar3 = (*(code *)((ushort)(bVar2 * '\x03') + 0x4647))();
  return uVar3;
}

