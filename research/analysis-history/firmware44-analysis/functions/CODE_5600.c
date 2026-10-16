
char FUN_CODE_5600(char param_1,byte param_2,char param_3,byte param_4,char param_5,byte param_6)

{
  byte bVar1;
  
  DAT_EXTMEM_078b = 0;
  DAT_EXTMEM_078c = 0;
  DAT_EXTMEM_0785 = param_5;
  DAT_EXTMEM_0786 = param_6;
  DAT_EXTMEM_0787 = param_3;
  DAT_EXTMEM_0788 = param_4;
  DAT_EXTMEM_0789 = param_1;
  DAT_EXTMEM_078a = param_2;
  while (bVar1 = DAT_EXTMEM_0789 - (((DAT_EXTMEM_078c < DAT_EXTMEM_078a) << 7) >> 7),
        DAT_EXTMEM_078b < bVar1) {
    *(undefined1 *)
     CONCAT11(DAT_EXTMEM_0785 +
              (DAT_EXTMEM_078b - ((CARRY1(DAT_EXTMEM_0786,DAT_EXTMEM_078c) << 7) >> 7)),
              DAT_EXTMEM_0786 + DAT_EXTMEM_078c) =
         *(undefined1 *)
          CONCAT11(DAT_EXTMEM_0787 +
                   (DAT_EXTMEM_078b - ((CARRY1(DAT_EXTMEM_0788,DAT_EXTMEM_078c) << 7) >> 7)),
                   DAT_EXTMEM_0788 + DAT_EXTMEM_078c);
    DAT_EXTMEM_078c = DAT_EXTMEM_078c + 1;
    if (DAT_EXTMEM_078c == 0) {
      DAT_EXTMEM_078b = DAT_EXTMEM_078b + 1;
    }
  }
  return DAT_EXTMEM_078b - bVar1;
}

