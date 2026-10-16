
void FUN_CODE_3ae1(void)

{
  byte bVar1;
  undefined2 *puVar2;
  
  DAT_EXTMEM_0789 = DAT_EXTMEM_0752;
  DAT_EXTMEM_078a = 1;
  FUN_CODE_3563();
  puVar2 = (undefined2 *)
           CONCAT11('\r' - (((0x40U < (byte)(DAT_EXTMEM_0752 * '\b')) << 7) >> 7),
                    DAT_EXTMEM_0752 * '\b' + 0xbf);
  bVar1 = *(byte *)*puVar2;
  if (DAT_EXTMEM_0751 == '\0') {
    **(byte **)CONCAT11('\r' - (((0x40U < (byte)(DAT_EXTMEM_0752 * '\b')) << 7) >> 7),
                        DAT_EXTMEM_0752 * '\b' + 0xbf) = bVar1 & 0xfb | 0x22;
  }
  else {
    *(byte *)*puVar2 = bVar1 | 0x26;
  }
  return;
}

