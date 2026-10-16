
void FUN_CODE_510d(char param_1)

{
  if ((param_1 == '\x02') && (DAT_EXTMEM_0dd1 != '\0')) {
    return;
  }
  DAT_EXTMEM_0dd1 = 1;
  DAT_EXTMEM_0dcf = 1;
  DAT_EXTMEM_0dd0 = param_1;
  FUN_CODE_2715();
  return;
}

