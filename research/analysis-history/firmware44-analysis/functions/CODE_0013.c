
undefined1 thunk_FUN_CODE_3400(undefined1 param_1)

{
  byte bVar1;
  undefined1 *puVar2;
  
  bVar1 = (byte)((ushort)DAT_EXTMEM_1110 * 2);
  puVar2 = (undefined1 *)
           CONCAT11((char)((ushort)DAT_EXTMEM_1110 * 2 >> 8) +
                    ('\x05' - (((0x3b < bVar1) << 7) >> 7)),bVar1 - 0x3c);
  FUN_CODE_895d(puVar2[1],*puVar2);
  return param_1;
}

