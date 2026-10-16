
void FUN_CODE_020b(undefined1 param_1,undefined1 param_2,char param_3)

{
  undefined1 *puVar1;
  
  if (param_3 == '\x01') {
    DAT_EXTMEM_1045 = 0x80;
    puVar1 = &DAT_EXTMEM_1043;
  }
  else if (param_3 == '\x02') {
    DAT_EXTMEM_1048 = 0x80;
    puVar1 = &DAT_EXTMEM_1046;
  }
  else if (param_3 == '\x03') {
    DAT_EXTMEM_104b = 0x80;
    puVar1 = &DAT_EXTMEM_1049;
  }
  else if (param_3 == '\x04') {
    DAT_EXTMEM_104e = 0x80;
    puVar1 = &DAT_EXTMEM_104c;
  }
  else {
    if (param_3 != '\0') {
      return;
    }
    DAT_EXTMEM_1042 = 0x80;
    puVar1 = &DAT_EXTMEM_1040;
  }
  *puVar1 = param_2;
  puVar1[1] = param_1;
  puVar1[2] = 0;
  return;
}

