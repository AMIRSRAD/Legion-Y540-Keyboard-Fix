
void FUN_CODE_88b1(char param_1,char param_2,char param_3)

{
  undefined1 in_stack_000000fc;
  undefined1 in_stack_000000fd;
  undefined1 in_stack_000000fe;
  
  if (param_3 == '\x01') {
    FUN_CODE_897e(param_1 + param_2,in_stack_000000fe,in_stack_000000fd,in_stack_000000fc);
    return;
  }
  if (param_3 == '\0') {
    FUN_CODE_896c(param_2 + param_1,in_stack_000000fe,in_stack_000000fd,in_stack_000000fc);
    return;
  }
  if (param_3 == -2) {
    FUN_CODE_8990(param_2 + param_1,in_stack_000000fe,in_stack_000000fd,in_stack_000000fc);
    return;
  }
  return;
}

