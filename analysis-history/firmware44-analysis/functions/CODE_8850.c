
void FUN_CODE_8850(undefined2 param_1)

{
  code *UNRECOVERED_JUMPTABLE;
  undefined1 uStackX_0;
  undefined1 in_stack_000000ff;
  
  UNRECOVERED_JUMPTABLE = (code *)CONCAT11(uStackX_0,in_stack_000000ff);
  FUN_CODE_8867((char)((ushort)param_1 >> 8),(char)param_1);
  FUN_CODE_8867();
  FUN_CODE_8867();
  FUN_CODE_8867();
                    /* WARNING: Could not recover jumptable at 0x8866. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (*UNRECOVERED_JUMPTABLE)();
  return;
}

