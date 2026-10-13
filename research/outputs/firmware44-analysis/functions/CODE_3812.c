
byte FUN_CODE_3812(undefined1 param_1,undefined1 param_2,undefined1 param_3)

{
  char cVar1;
  byte bVar2;
  undefined1 *puVar3;
  
  DAT_EXTMEM_077f = param_3;
  DAT_EXTMEM_0780 = param_2;
  DAT_EXTMEM_0781 = param_1;
  cVar1 = FUN_CODE_857a(1,param_1,param_2,param_3);
  if (cVar1 == '\0') {
    bVar2 = 0;
    DAT_EXTMEM_0811 = 0;
  }
  else if (cVar1 == '\x01') {
    bVar2 = DAT_EXTMEM_0811 & 0xfd | 1;
    DAT_EXTMEM_0811 = bVar2;
  }
  else {
    cVar1 = FUN_CODE_857a(1);
    if (cVar1 == '\x02') {
      bVar2 = DAT_EXTMEM_0811 & 0xfe | 2;
      DAT_EXTMEM_0811 = bVar2;
    }
    else if (cVar1 == '\x03') {
      bVar2 = 3;
      DAT_EXTMEM_0811 = 3;
    }
    else {
      cVar1 = FUN_CODE_857a(1);
      if (cVar1 == '\x04') {
        bVar2 = FUN_CODE_857a(2);
        DAT_EXTMEM_0810 = bVar2;
      }
      else {
        if (cVar1 == '\x05') {
          cVar1 = FUN_CODE_857a(2);
          puVar3 = &DAT_EXTMEM_0814;
          if (cVar1 == '\0') {
            DAT_EXTMEM_0814 = 0;
            return 0;
          }
        }
        else {
          cVar1 = FUN_CODE_857a(1);
          if (cVar1 == '\x06') {
            cVar1 = FUN_CODE_857a(2);
            if (cVar1 == '\0') {
              DAT_EXTMEM_0815 = DAT_EXTMEM_0815 | 3;
              DAT_EXTMEM_1806 = 0;
              return 0;
            }
            if (cVar1 == '\x01') {
              DAT_EXTMEM_0815 = DAT_EXTMEM_0815 | 3;
              DAT_EXTMEM_1806 = 0x4d;
              return 0x4d;
            }
            cVar1 = FUN_CODE_857a(2);
            if (cVar1 == '\x02') {
              DAT_EXTMEM_0815 = DAT_EXTMEM_0815 | 3;
              DAT_EXTMEM_1806 = 0xff;
              return 0xff;
            }
            DAT_EXTMEM_0815 = DAT_EXTMEM_0815 & 0xfe;
            bVar2 = FUN_CODE_6e72();
            return bVar2;
          }
          cVar1 = FUN_CODE_857a(1,DAT_EXTMEM_0781,DAT_EXTMEM_0780,DAT_EXTMEM_077f);
          if (cVar1 == '\a') {
            puVar3 = &DAT_EXTMEM_0802;
          }
          else {
            if (cVar1 != '\b') {
              if (cVar1 == -3) {
                DAT_EXTMEM_0812 = FUN_CODE_857a(2);
                return DAT_EXTMEM_0812;
              }
              cVar1 = FUN_CODE_857a(1);
              if (cVar1 != -2) {
                bVar2 = FUN_CODE_857a(1,DAT_EXTMEM_0781,DAT_EXTMEM_0780,DAT_EXTMEM_077f);
                if (bVar2 != 0xff) {
                  return bVar2;
                }
                DAT_EXTMEM_0813 = FUN_CODE_857a(2);
                return DAT_EXTMEM_0813;
              }
              DAT_EXTMEM_0812 = FUN_CODE_857a(2);
              if (DAT_EXTMEM_0812 < 4) {
                return DAT_EXTMEM_0812 - 4;
              }
              *(byte *)CONCAT11(0xe,DAT_EXTMEM_0812) = DAT_EXTMEM_0813;
              FUN_CODE_059d();
              FUN_CODE_7f40();
              FUN_CODE_05a4();
              if (DAT_EXTMEM_0812 != 0x10) {
                return DAT_EXTMEM_0812;
              }
              bVar2 = FUN_CODE_7994();
              return bVar2;
            }
            puVar3 = &DAT_EXTMEM_080f;
          }
        }
        bVar2 = 1;
        *puVar3 = 1;
      }
    }
  }
  return bVar2;
}

