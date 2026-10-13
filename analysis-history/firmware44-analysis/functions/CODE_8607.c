
undefined1 FUN_CODE_8607(char param_1,undefined1 param_2,char param_3)

{
  if (param_3 == '\x01') {
    return *(undefined1 *)(CONCAT11(param_2,param_1) + 1);
  }
  if (param_3 == '\0') {
    return *(undefined1 *)(param_1 + '\x01');
  }
  if (param_3 == -2) {
    return *(undefined1 *)(ushort)(param_1 + 1);
  }
  return *(undefined1 *)(CONCAT11(param_2,param_1) + 1);
}

