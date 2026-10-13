
undefined1 FUN_CODE_6cb3(void)

{
  byte bVar1;
  undefined1 *puVar2;
  
  bVar1 = 0;
  do {
    *(undefined1 *)CONCAT11('\a' - (((0xc2 < bVar1) << 7) >> 7),bVar1 + 0x3d) = 0;
    puVar2 = (undefined1 *)
             CONCAT11('\a' - (((0xc1 < bVar1 * '\x02') << 7) >> 7),bVar1 * '\x02' + 0x3e);
    *puVar2 = 0;
    puVar2[1] = 0;
    puVar2 = (undefined1 *)
             CONCAT11('\a' - (((0xbf < bVar1 * '\x02') << 7) >> 7),bVar1 * '\x02' + 0x40);
    *puVar2 = 0;
    puVar2[1] = 0x7d;
    bVar1 = bVar1 + 1;
  } while (bVar1 != 1);
  FUN_CODE_2ffb();
  FUN_CODE_50ac();
  DAT_EXTMEM_073c = 1;
  return 1;
}

