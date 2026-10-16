
void FUN_CODE_0ee3(void)

{
  char cVar1;
  undefined2 *puVar2;
  
  cVar1 = '\0';
  do {
    puVar2 = (undefined2 *)
             CONCAT11('\x0f' - (((0xcbU < (byte)(cVar1 * '\x03')) << 7) >> 7),cVar1 * '\x03' + 0x34)
    ;
    DAT_INTMEM_87 = *(undefined1 *)puVar2;
    DAT_INTMEM_88 = *(undefined1 *)((short)puVar2 + 1);
    *(undefined1 *)*puVar2 =
         *(undefined1 *)
          CONCAT11('\x0f' - (((0xc9U < (byte)(cVar1 * '\x03')) << 7) >> 7),cVar1 * '\x03' + 0x36);
    cVar1 = cVar1 + '\x01';
  } while (cVar1 != '\x16');
  DAT_EXTMEM_1e21 = 0x40;
  DAT_EXTMEM_1e40 = 3;
  DAT_EXTMEM_1e20 = 0x80;
  return;
}

