
/* WARNING: Removing unreachable block (CODE,0x816e) */
/* WARNING: Removing unreachable block (CODE,0x8171) */
/* WARNING: Removing unreachable block (CODE,0x817a) */

char FUN_CODE_813c(void)

{
  char cVar1;
  byte bVar2;
  
  FUN_CODE_059d();
  thunk_FUN_CODE_0c42();
  cVar1 = '\x01';
  FUN_CODE_3185();
  if (cVar1 == '\0') {
    FUN_CODE_0cbf(0,0,1,0x2c);
    FUN_CODE_0e30();
  }
  FUN_CODE_810e();
  FUN_CODE_80e3();
  DAT_EXTMEM_00d7 = 0;
  FUN_CODE_05a4();
  DAT_EXTMEM_00a1 = 1;
  FUN_CODE_264b();
  FUN_CODE_80fc();
  FUN_CODE_8121();
  FUN_CODE_0e63();
  thunk_FUN_CODE_0c3c();
  FUN_CODE_2580();
  DAT_EXTMEM_00cf = 1;
  _6_0 = 1;
  DAT_EXTMEM_00f4 = 1;
  DAT_EXTMEM_00f5 = 0x2c;
  for (DAT_EXTMEM_0747 = 0; DAT_EXTMEM_0747 < 0x10; DAT_EXTMEM_0747 = DAT_EXTMEM_0747 + 1) {
    if (*(char *)(DAT_EXTMEM_0747 + 0x6d) != '\0') {
      for (DAT_EXTMEM_0748 = 0; (DAT_EXTMEM_0748 < 8) << 7 < '\0';
          DAT_EXTMEM_0748 = DAT_EXTMEM_0748 + 1) {
        bVar2 = 1;
        cVar1 = DAT_EXTMEM_0748 + 1;
        while (cVar1 = cVar1 + -1, cVar1 != '\0') {
          bVar2 = bVar2 << 1;
        }
        if (((bVar2 & *(byte *)(DAT_EXTMEM_0747 + 0x6d)) != 0) && (FUN_CODE_25d9(), bVar2 == 0)) {
          DAT_EXTMEM_0749 = DAT_EXTMEM_0749 & 8 | DAT_EXTMEM_0747 << 4 | DAT_EXTMEM_0748 & 7;
          FUN_CODE_853b(0x4c,0x49,7,1,7,1,0,1);
          DAT_EXTMEM_074d = 1;
          FUN_CODE_1435();
          FUN_CODE_853b(0x4c,0x49,7,1,7,1,0,1);
          DAT_EXTMEM_074d = 0;
          FUN_CODE_1435();
        }
      }
    }
  }
  return DAT_EXTMEM_0747 - 0x10;
}

