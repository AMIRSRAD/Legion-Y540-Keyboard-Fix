
byte FUN_CODE_6733(byte param_1,byte param_2)

{
  undefined1 *puVar1;
  
  if ((param_2 == 0) && (param_1 < 3)) {
    DAT_EXTMEM_1c10 = DAT_EXTMEM_1c10 | 0x20;
    DAT_EXTMEM_1c34 = DAT_EXTMEM_1c34 & 0xfc | param_1;
    puVar1 = (undefined1 *)
             CONCAT11('\a' - (((0xd5 < param_1 * '\x06') << 7) >> 7),param_1 * '\x06' + 0x2a);
    FUN_CODE_85a7(0,puVar1[2],puVar1[1],*puVar1);
    puVar1 = (undefined1 *)
             CONCAT11('\a' - (((0xd2 < param_1 * '\x06') << 7) >> 7),param_1 * '\x06' + 0x2d);
    FUN_CODE_85a7(0,puVar1[2],puVar1[1],*puVar1);
    DAT_EXTMEM_1100 = 0x10;
    DAT_EXTMEM_1104 = DAT_EXTMEM_1104 | 0x10;
  }
  param_2 = param_2 ^ 1;
  if ((param_2 == 0) && (param_2 = param_1 - 3, param_1 < 3)) {
    DAT_EXTMEM_1c21 = DAT_EXTMEM_1c21 | 0x20;
    puVar1 = (undefined1 *)
             CONCAT11('\a' - (((0xd5 < param_1 * '\x06') << 7) >> 7),param_1 * '\x06' + 0x2a);
    FUN_CODE_85a7(4,puVar1[2],puVar1[1],*puVar1);
    puVar1 = (undefined1 *)
             CONCAT11('\a' - (((0xd2 < param_1 * '\x06') << 7) >> 7),param_1 * '\x06' + 0x2d);
    FUN_CODE_85a7(4,puVar1[2],puVar1[1],*puVar1);
    DAT_EXTMEM_1100 = 0x20;
    param_2 = DAT_EXTMEM_1104 | 0x20;
    DAT_EXTMEM_1104 = param_2;
  }
  return param_2;
}

