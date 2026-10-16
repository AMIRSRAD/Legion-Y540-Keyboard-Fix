
void FUN_CODE_2d4a(char param_1,byte param_2,byte param_3)

{
  byte bVar1;
  char cVar2;
  byte *pbVar3;
  
  cVar2 = DAT_EXTMEM_0a85;
  DAT_EXTMEM_0a85 = DAT_EXTMEM_0a85 + 1;
  if (7 < DAT_EXTMEM_0a85) {
    DAT_EXTMEM_0a85 = 0;
  }
  if (DAT_EXTMEM_0a85 == DAT_EXTMEM_0a84) {
    DAT_EXTMEM_0a85 = cVar2;
    return;
  }
  if (param_1 != '\0') {
    param_2 = param_2 | 0x80;
  }
  bVar1 = cVar2 * '\x02';
  pbVar3 = (byte *)CONCAT11('\n' - (((0x8b < bVar1) << 7) >> 7),bVar1 + 0x74);
  *pbVar3 = param_2;
  pbVar3[1] = param_3;
  return;
}

