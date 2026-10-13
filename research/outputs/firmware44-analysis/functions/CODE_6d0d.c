
void FUN_CODE_6d0d(void)

{
  char cVar1;
  byte bVar2;
  byte bVar3;
  char *pcVar4;
  byte *pbVar5;
  undefined1 *puVar6;
  
  bVar3 = 0;
  if (DAT_EXTMEM_073c == '\x01') {
    do {
      FUN_CODE_85db(0,CONCAT11('\a' - (((0xc1 < bVar3 * '\x02') << 7) >> 7),bVar3 * '\x02' + 0x3e),1
                   );
      pcVar4 = (char *)CONCAT11('\a' - (((0xbf < bVar3 * '\x02') << 7) >> 7),bVar3 * '\x02' + 0x40);
      cVar1 = *pcVar4;
      bVar2 = pcVar4[1];
      if ((bVar2 != 0 || cVar1 != '\0') &&
         (pbVar5 = (byte *)CONCAT11('\a' - (((0xc1 < bVar3 * '\x02') << 7) >> 7),
                                    bVar3 * '\x02' + 0x3e),
         (byte)(cVar1 - (((pbVar5[1] < bVar2) << 7) >> 7)) <= *pbVar5)) {
        puVar6 = (undefined1 *)
                 CONCAT11('\a' - (((0xc1 < bVar3 * '\x02') << 7) >> 7),bVar3 * '\x02' + 0x3e);
        *puVar6 = 0;
        puVar6[1] = 0;
        *(undefined1 *)CONCAT11('\a' - (((0xc2 < bVar3) << 7) >> 7),bVar3 + 0x3d) = 1;
        return;
      }
      bVar3 = bVar3 + 1;
    } while (bVar3 != 1);
  }
  return;
}

