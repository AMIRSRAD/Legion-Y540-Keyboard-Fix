// ===== thunk_FUN_CODE_0100  [app]  callers: 

void thunk_FUN_CODE_0100(void)

{
  undefined1 *puVar1;
  char cVar2;
  char cVar3;
  undefined1 *puVar4;
  
  puVar1 = (undefined1 *)0xff;
  do {
    *puVar1 = 0;
    puVar1 = puVar1 + -1;
  } while (puVar1 != (undefined1 *)0x0);
  puVar4 = (undefined1 *)0x0;
  cVar3 = '\0';
  cVar2 = '\x10';
  do {
    do {
      *puVar4 = 0;
      puVar4 = puVar4 + 1;
      cVar3 = cVar3 + -1;
    } while (cVar3 != '\0');
    cVar2 = cVar2 + -1;
  } while (cVar2 != '\0');
  SP = 0xa0;
  FUN_CODE_020b(1,0x36,1);
  FUN_CODE_0136();
  nop();
  nop();
  nop();
  return;
}


// ===== thunk_FUN_CODE_3200  [app]  callers: 

void thunk_FUN_CODE_3200(void)

{
  return;
}


// ===== thunk_FUN_CODE_3300  [app]  callers: 

undefined1 thunk_FUN_CODE_3300(undefined1 param_1)

{
  FUN_CODE_0c33();
  _6_5 = 1;
  DAT_EXTMEM_00cf = 1;
  _6_0 = 1;
  if ((DAT_INTMEM_59 != '\0') && (DAT_INTMEM_59 = DAT_INTMEM_59 + -1, DAT_INTMEM_59 == '\0')) {
    DAT_INTMEM_57 = 0xff;
    DAT_INTMEM_58 = 0xff;
  }
  return param_1;
}


// ===== thunk_FUN_CODE_3400  [app]  callers: 

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


// ===== thunk_FUN_CODE_3500  [app]  callers: 

void thunk_FUN_CODE_3500(void)

{
  return;
}


// ===== thunk_FUN_CODE_3600  [app]  callers: 

void thunk_FUN_CODE_3600(void)

{
  return;
}


// ===== thunk_FUN_CODE_3700  [app]  callers: 

void thunk_FUN_CODE_3700(void)

{
  return;
}


// ===== FUN_CODE_00e1  [app]  callers: 

void FUN_CODE_00e1(void)

{
  undefined1 *puVar1;
  char cVar2;
  char cVar3;
  undefined1 *puVar4;
  
  puVar1 = (undefined1 *)0xff;
  do {
    *puVar1 = 0;
    puVar1 = puVar1 + -1;
  } while (puVar1 != (undefined1 *)0x0);
  puVar4 = (undefined1 *)0x0;
  cVar3 = '\0';
  cVar2 = '\x10';
  do {
    do {
      *puVar4 = 0;
      puVar4 = puVar4 + 1;
      cVar3 = cVar3 + -1;
    } while (cVar3 != '\0');
    cVar2 = cVar2 + -1;
  } while (cVar2 != '\0');
  SP = 0xa0;
  FUN_CODE_020b(1,0x36,1);
  FUN_CODE_0136();
  nop();
  nop();
  nop();
  return;
}


// ===== FUN_CODE_0100  [app]  callers: 

void FUN_CODE_0100(void)

{
  undefined1 *puVar1;
  char cVar2;
  char cVar3;
  undefined1 *puVar4;
  
  puVar1 = (undefined1 *)0xff;
  do {
    *puVar1 = 0;
    puVar1 = puVar1 + -1;
  } while (puVar1 != (undefined1 *)0x0);
  puVar4 = (undefined1 *)0x0;
  cVar3 = '\0';
  cVar2 = '\x10';
  do {
    do {
      *puVar4 = 0;
      puVar4 = puVar4 + 1;
      cVar3 = cVar3 + -1;
    } while (cVar3 != '\0');
    cVar2 = cVar2 + -1;
  } while (cVar2 != '\0');
  SP = 0xa0;
  FUN_CODE_020b(1,0x36,1);
  FUN_CODE_0136();
  nop();
  nop();
  nop();
  return;
}


// ===== thunk_FUN_CODE_e003  [app]  callers: CODE:0136

void thunk_FUN_CODE_e003(void)

{
  undefined1 *puVar1;
  
  puVar1 = &DAT_INTMEM_7f;
  do {
    *puVar1 = 0;
    puVar1 = puVar1 + -1;
  } while (puVar1 != (undefined1 *)0x0);
  SP = 0xb;
  FUN_CODE_f520();
  return;
}


// ===== thunk_FUN_CODE_0400  [app]  callers: CODE:0136

void thunk_FUN_CODE_0400(void)

{
  undefined1 *puVar1;
  char cVar2;
  char cVar3;
  undefined1 uVar4;
  undefined1 *puVar5;
  
  puVar1 = (undefined1 *)0xff;
  do {
    *puVar1 = 0;
    puVar1 = puVar1 + -1;
  } while (puVar1 != (undefined1 *)0x0);
  puVar5 = (undefined1 *)0x0;
  cVar3 = '\0';
  cVar2 = '\x10';
  do {
    do {
      *puVar5 = 0;
      puVar5 = puVar5 + 1;
      cVar3 = cVar3 + -1;
    } while (cVar3 != '\0');
    cVar2 = cVar2 + -1;
  } while (cVar2 != '\0');
  SP = 0xa0;
  uVar4 = FUN_CODE_7f7b();
  DAT_EXTMEM_0082 = DAT_EXTMEM_2006;
  FUN_CODE_0464(uVar4);
  return;
}


// ===== FUN_CODE_0136  [app]  callers: CODE:0100

void FUN_CODE_0136(void)

{
  bool bVar1;
  byte bVar2;
  char cVar3;
  char cVar4;
  byte bVar5;
  
  bVar5 = 0;
  cVar4 = '\0';
  DAT_EXTMEM_1e21 = 0x40;
  DAT_EXTMEM_1e40 = 3;
  DAT_EXTMEM_1e20 = 0x80;
  bVar2 = 0x7f;
  if ((DAT_EXTMEM_1080 & 5) == 5) {
    bVar2 = 0xd7;
  }
  uEXTMEM0000 = 0x7f;
  uEXTMEM0001 = 0xfe;
  cVar3 = -1;
  do {
    bVar1 = CARRY1(*(byte *)CONCAT11(bVar2,cVar3),bVar5);
    bVar5 = *(byte *)CONCAT11(bVar2,cVar3) + bVar5;
    cVar4 = cVar4 - ((bVar1 << 7) >> 7);
    if (cVar3 == '\0') {
      bVar2 = bVar2 - 1;
    }
    cVar3 = cVar3 + -1;
  } while (2 < bVar2);
  cEXTMEM0002 = cCODE7ffe;
  DAT_EXTMEM_0f0b = DAT_CODE_7fff;
  bVar2 = (-cCODE7ffe - 1U) + bVar5;
  DAT_EXTMEM_0f07 = (-DAT_CODE_7fff - 1U) + bVar2;
  DAT_EXTMEM_0f06 =
       (cVar4 - ((CARRY1(-cCODE7ffe - 1U,bVar5) << 7) >> 7)) -
       ((CARRY1(-DAT_CODE_7fff - 1U,bVar2) << 7) >> 7);
  DAT_EXTMEM_0f0a = cEXTMEM0002;
  if ((DAT_EXTMEM_0f06 == BANK0_R6) && (DAT_EXTMEM_0f07 == BANK0_R7)) {
    DAT_EXTMEM_1045 = 3;
    thunk_FUN_CODE_0400();
  }
  else {
    DAT_EXTMEM_1045 = 3;
    thunk_FUN_CODE_e003(cCODE7ffe,DAT_CODE_7fff);
  }
  return;
}


// ===== FUN_CODE_020b  [app]  callers: CODE:0100

void FUN_CODE_020b(undefined1 param_1,undefined1 param_2,char param_3)

{
  undefined1 *puVar1;
  
  if (param_3 == '\x01') {
    DAT_EXTMEM_1045 = 0x80;
    puVar1 = &DAT_EXTMEM_1043;
  }
  else if (param_3 == '\x02') {
    DAT_EXTMEM_1048 = 0x80;
    puVar1 = &DAT_EXTMEM_1046;
  }
  else if (param_3 == '\x03') {
    DAT_EXTMEM_104b = 0x80;
    puVar1 = &DAT_EXTMEM_1049;
  }
  else if (param_3 == '\x04') {
    DAT_EXTMEM_104e = 0x80;
    puVar1 = &DAT_EXTMEM_104c;
  }
  else {
    if (param_3 != '\0') {
      return;
    }
    DAT_EXTMEM_1042 = 0x80;
    puVar1 = &DAT_EXTMEM_1040;
  }
  *puVar1 = param_2;
  puVar1[1] = param_1;
  puVar1[2] = 0;
  return;
}


// ===== FUN_CODE_0400  [app]  callers: 

void FUN_CODE_0400(void)

{
  undefined1 *puVar1;
  char cVar2;
  char cVar3;
  undefined1 uVar4;
  undefined1 *puVar5;
  
  puVar1 = (undefined1 *)0xff;
  do {
    *puVar1 = 0;
    puVar1 = puVar1 + -1;
  } while (puVar1 != (undefined1 *)0x0);
  puVar5 = (undefined1 *)0x0;
  cVar3 = '\0';
  cVar2 = '\x10';
  do {
    do {
      *puVar5 = 0;
      puVar5 = puVar5 + 1;
      cVar3 = cVar3 + -1;
    } while (cVar3 != '\0');
    cVar2 = cVar2 + -1;
  } while (cVar2 != '\0');
  SP = 0xa0;
  uVar4 = FUN_CODE_7f7b();
  DAT_EXTMEM_0082 = DAT_EXTMEM_2006;
  FUN_CODE_0464(uVar4);
  return;
}


// ===== H_045C  [app]  callers: 

void H_045C(void)

{
  nop();
  return;
}


// ===== FUN_CODE_0464  [app]  callers: CODE:0400

void FUN_CODE_0464(void)

{
  char cVar1;
  byte bVar2;
  byte *pbVar3;
  byte bVar4;
  byte bVar5;
  byte *pbVar6;
  byte *pbVar7;
  
  pbVar6 = &DAT_CODE_5154;
  while( true ) {
    bVar2 = 1;
    bVar4 = *pbVar6;
    if (bVar4 == 0) break;
    bVar5 = bVar4 & 0x3f;
    pbVar7 = pbVar6 + 1;
    if (bVar5 >> 5 != 0) {
      bVar2 = bVar4 & 0x1f;
      bVar5 = pbVar6[1];
      pbVar7 = pbVar6 + 2;
      if (bVar5 != 0) {
        bVar2 = bVar2 + 1;
      }
    }
    pbVar6 = pbVar7;
    cVar1 = CARRY1(bVar4 & 0xc0,bVar4 & 0xc0) << 7;
    if ((bVar4 & 0x40) == 0) {
      pbVar3 = (byte *)*pbVar6;
      pbVar6 = pbVar6 + 1;
      do {
        bVar2 = *pbVar6;
        pbVar6 = pbVar6 + 1;
        if (cVar1 < '\0') {
          *(byte *)ZEXT12(pbVar3) = bVar2;
        }
        else {
          *pbVar3 = bVar2;
        }
        pbVar3 = pbVar3 + '\x01';
        bVar5 = bVar5 - 1;
      } while (bVar5 != 0);
    }
    else if (cVar1 < '\0') {
      do {
        bVar2 = *pbVar6;
        pbVar6 = pbVar6 + 1;
        pbVar3 = (byte *)((bVar2 & 0x7f) >> 3 | 0x20);
        bVar4 = *(byte *)((ushort)((bVar2 & 7) + 0xc) + 0x450);
        if ((char)bVar2 < '\0') {
          bVar4 = bVar4 | *pbVar3;
        }
        else {
          bVar4 = ~bVar4 & *pbVar3;
        }
        *pbVar3 = bVar4;
        bVar5 = bVar5 - 1;
      } while (bVar5 != 0);
    }
    else {
      pbVar7 = *(byte **)pbVar6;
      pbVar6 = pbVar6 + 2;
      do {
        do {
          bVar4 = *pbVar6;
          pbVar6 = pbVar6 + 1;
          *pbVar7 = bVar4;
          pbVar7 = pbVar7 + 1;
          bVar5 = bVar5 - 1;
        } while (bVar5 != 0);
        bVar2 = bVar2 - 1;
      } while (bVar2 != 0);
    }
  }
  FUN_CODE_2200();
  return;
}


// ===== H_04A9  [app]  callers: 

void H_04A9(void)

{
  return;
}


// ===== FUN_CODE_059d  [app]  callers: CODE:1353 CODE:813c CODE:1391 CODE:1372 CODE:13b5 CODE:806d CODE:4dba CODE:3812 CODE:13d4 CODE:2200 CODE:0c65 CODE:13fe CODE:31ec

void FUN_CODE_059d(void)

{
  EA = 0;
  nop();
  nop();
  nop();
  nop();
  return;
}


// ===== FUN_CODE_05a4  [app]  callers: CODE:1353 CODE:813c CODE:1391 CODE:05a7 CODE:1372 CODE:13b5 CODE:806d CODE:4dba CODE:3812 CODE:13d4 CODE:05de CODE:0c65 CODE:13fe

void FUN_CODE_05a4(void)

{
  EA = 1;
  return;
}


// ===== FUN_CODE_05a7  [app]  callers: CODE:2200

void FUN_CODE_05a7(void)

{
  DAT_EXTMEM_1100 = 0xff;
  DAT_EXTMEM_1101 = 0xff;
  DAT_EXTMEM_1102 = 0xff;
  DAT_EXTMEM_1103 = 0xff;
  DAT_EXTMEM_1114 = 0xff;
  DAT_EXTMEM_1118 = 0xff;
  DAT_EXTMEM_111c = 0xff;
  DAT_EXTMEM_1120 = 0xff;
  DAT_EXTMEM_1124 = 0xff;
  DAT_EXTMEM_1128 = 0xff;
  DAT_EXTMEM_112c = 0xff;
  DAT_EXTMEM_1130 = 0xff;
  EX1 = 1;
  FUN_CODE_05a4();
  return;
}


// ===== FUN_CODE_05de  [app]  callers: CODE:2200

void FUN_CODE_05de(void)

{
  FUN_CODE_05a4();
  return;
}


// ===== H_062C  [app]  callers: 

void H_062C(void)

{
  char cVar1;
  
  BANK1_R2 = BANK1_R2 + '\x01';
  BANK1_R3 = BANK1_R3 + '\x01';
  BANK1_R4 = BANK1_R4 + '\x01';
  BANK1_R5 = BANK1_R5 + '\x01';
  BANK2_R0 = BANK2_R0 + '\x01';
  BANK2_R1 = BANK2_R1 + '\x01';
  BANK2_R2 = BANK2_R2 + '\x01';
  BANK2_R3 = BANK2_R3 + '\x01';
  BANK2_R4 = BANK2_R4 + '\x01';
  BANK2_R5 = BANK2_R5 + '\x01';
  BANK2_R6 = BANK2_R6 + '\x01';
  BANK2_R7 = BANK2_R7 + '\x01';
  BANK3_R0 = BANK3_R0 + '\x01';
  BANK3_R1 = BANK3_R1 + '\x01';
  BANK3_R2 = BANK3_R2 + '\x01';
  BANK3_R3 = BANK3_R3 + '\x01';
  BANK3_R4 = BANK3_R4 + '\x01';
  BANK3_R5 = BANK3_R5 + '\x01';
  BANK3_R6 = BANK3_R6 + '\x01';
  DAT_INTMEM_21 = DAT_INTMEM_21 + '\x01';
  DAT_INTMEM_24 = DAT_INTMEM_24 + '\x01';
  DAT_INTMEM_2f = DAT_INTMEM_2f + '\x01';
  DAT_INTMEM_3a = DAT_INTMEM_3a + '\x01';
  DAT_INTMEM_45 = DAT_INTMEM_45 + '\x01';
  DAT_INTMEM_50 = DAT_INTMEM_50 + '\x01';
  DAT_INTMEM_5b = DAT_INTMEM_5b + '\x01';
  DAT_INTMEM_66 = DAT_INTMEM_66 + '\x01';
  DAT_INTMEM_71 = DAT_INTMEM_71 + '\x01';
  DAT_INTMEM_7c = DAT_INTMEM_7c + '\x01';
  DAT_INTMEM_7d = DAT_INTMEM_7d + '\x01';
  DAT_INTMEM_7e = DAT_INTMEM_7e + '\x01';
  DAT_INTMEM_7f = DAT_INTMEM_7f + '\x01';
  cVar1 = P0;
  P0 = cVar1 + '\x01';
  cVar1 = SP;
  SP = cVar1 + '\x01';
  cVar1 = DPXL;
  DPXL = cVar1 + '\x01';
  cVar1 = DAT_SFR_85;
  DAT_SFR_85 = cVar1 + '\x01';
  cVar1 = DAT_SFR_86;
  DAT_SFR_86 = cVar1 + '\x01';
  cVar1 = PCON;
  PCON = cVar1 + '\x01';
  cVar1 = TCON;
  TCON = cVar1 + '\x01';
  cVar1 = TMOD;
  TMOD = cVar1 + '\x01';
  cVar1 = TL0;
  TL0 = cVar1 + '\x01';
  cVar1 = TL1;
  TL1 = cVar1 + '\x01';
  cVar1 = TH0;
  TH0 = cVar1 + '\x01';
  cVar1 = TH1;
  TH1 = cVar1 + '\x01';
  cVar1 = DAT_SFR_8e;
  DAT_SFR_8e = cVar1 + '\x01';
  cVar1 = FADDR;
  FADDR = cVar1 + '\x01';
  cVar1 = P1;
  P1 = cVar1 + '\x01';
  cVar1 = DAT_SFR_91;
  DAT_SFR_91 = cVar1 + '\x01';
  cVar1 = DAT_SFR_92;
  DAT_SFR_92 = cVar1 + '\x01';
  cVar1 = DPX;
  DPX = cVar1 + '\x01';
  cVar1 = DAT_SFR_94;
  DAT_SFR_94 = cVar1 + '\x01';
  cVar1 = DAT_SFR_95;
  DAT_SFR_95 = cVar1 + '\x01';
  cVar1 = DAT_SFR_96;
  DAT_SFR_96 = cVar1 + '\x01';
  cVar1 = HADDR;
  HADDR = cVar1 + '\x01';
  cVar1 = SCON;
  SCON = cVar1 + '\x01';
  cVar1 = SBUF;
  SBUF = cVar1 + '\x01';
  cVar1 = DAT_SFR_9a;
  DAT_SFR_9a = cVar1 + '\x01';
  cVar1 = DAT_SFR_9b;
  DAT_SFR_9b = cVar1 + '\x01';
  cVar1 = DAT_SFR_9c;
  DAT_SFR_9c = cVar1 + '\x01';
  cVar1 = DAT_SFR_9c;
  DAT_SFR_9c = cVar1 + '\x01';
  cVar1 = DAT_SFR_9c;
  DAT_SFR_9c = cVar1 + '\x01';
  cVar1 = DAT_SFR_9c;
  DAT_SFR_9c = cVar1 + '\x01';
  cVar1 = DAT_SFR_9c;
  DAT_SFR_9c = cVar1 + '\x01';
  cVar1 = DAT_SFR_9c;
  DAT_SFR_9c = cVar1 + '\x01';
  cVar1 = DAT_SFR_9c;
  DAT_SFR_9c = cVar1 + '\x01';
  cVar1 = DAT_SFR_9c;
  DAT_SFR_9c = cVar1 + '\x01';
  cVar1 = DAT_SFR_9c;
  DAT_SFR_9c = cVar1 + '\x01';
  cVar1 = DAT_SFR_9c;
  DAT_SFR_9c = cVar1 + '\x01';
  cVar1 = DAT_SFR_9c;
  DAT_SFR_9c = cVar1 + '\x01';
  cVar1 = DAT_SFR_9c;
  DAT_SFR_9c = cVar1 + '\x01';
  cVar1 = DAT_SFR_9c;
  DAT_SFR_9c = cVar1 + '\x01';
  cVar1 = DAT_SFR_9c;
  DAT_SFR_9c = cVar1 + '\x01';
  cVar1 = DAT_SFR_9c;
  DAT_SFR_9c = cVar1 + '\x01';
  cVar1 = DAT_SFR_9c;
  DAT_SFR_9c = cVar1 + '\x01';
  cVar1 = DAT_SFR_9c;
  DAT_SFR_9c = cVar1 + '\x01';
  cVar1 = DAT_SFR_9c;
  DAT_SFR_9c = cVar1 + '\x01';
  cVar1 = DAT_SFR_9c;
  DAT_SFR_9c = cVar1 + '\x01';
  cVar1 = DAT_SFR_9c;
  DAT_SFR_9c = cVar1 + '\x01';
  cVar1 = DAT_SFR_9c;
  DAT_SFR_9c = cVar1 + '\x01';
  cVar1 = DAT_SFR_9c;
  DAT_SFR_9c = cVar1 + '\x01';
  cVar1 = DAT_SFR_9c;
  DAT_SFR_9c = cVar1 + '\x01';
  cVar1 = DAT_SFR_9c;
  DAT_SFR_9c = cVar1 + '\x01';
  cVar1 = DAT_SFR_9c;
  DAT_SFR_9c = cVar1 + '\x01';
  cVar1 = DAT_SFR_9c;
  DAT_SFR_9c = cVar1 + '\x01';
  cVar1 = DAT_SFR_9c;
  DAT_SFR_9c = cVar1 + '\x01';
  cVar1 = DAT_SFR_9c;
  DAT_SFR_9c = cVar1 + '\x01';
  cVar1 = DAT_SFR_9c;
  DAT_SFR_9c = cVar1 + '\x01';
  cVar1 = DAT_SFR_9c;
  DAT_SFR_9c = cVar1 + '\x01';
  cVar1 = DAT_SFR_9c;
  DAT_SFR_9c = cVar1 + '\x01';
  cVar1 = DAT_SFR_9c;
  DAT_SFR_9c = cVar1 + '\x01';
  cVar1 = DAT_SFR_9c;
  DAT_SFR_9c = cVar1 + '\x01';
  cVar1 = DAT_SFR_9c;
  DAT_SFR_9c = cVar1 + '\x01';
  cVar1 = DAT_SFR_9c;
  DAT_SFR_9c = cVar1 + '\x01';
  cVar1 = DAT_SFR_9c;
  DAT_SFR_9c = cVar1 + '\x01';
  cVar1 = DAT_SFR_9c;
  DAT_SFR_9c = cVar1 + '\x01';
  cVar1 = DAT_SFR_9c;
  DAT_SFR_9c = cVar1 + '\x01';
  cVar1 = DAT_SFR_9c;
  DAT_SFR_9c = cVar1 + '\x01';
  cVar1 = DAT_SFR_9c;
  DAT_SFR_9c = cVar1 + '\x01';
  cVar1 = DAT_SFR_9c;
  DAT_SFR_9c = cVar1 + '\x01';
  cVar1 = DAT_SFR_9c;
  DAT_SFR_9c = cVar1 + '\x01';
  cVar1 = DAT_SFR_9c;
  DAT_SFR_9c = cVar1 + '\x01';
  cVar1 = DAT_SFR_9c;
  DAT_SFR_9c = cVar1 + '\x01';
  cVar1 = DAT_SFR_9c;
  DAT_SFR_9c = cVar1 + '\x01';
  cVar1 = DAT_SFR_9c;
  DAT_SFR_9c = cVar1 + '\x01';
  cVar1 = DAT_SFR_9c;
  DAT_SFR_9c = cVar1 + '\x01';
  cVar1 = DAT_SFR_9c;
  DAT_SFR_9c = cVar1 + '\x01';
  cVar1 = DAT_SFR_9c;
  DAT_SFR_9c = cVar1 + '\x01';
  cVar1 = DAT_SFR_9c;
  DAT_SFR_9c = cVar1 + '\x01';
  cVar1 = DAT_SFR_9c;
  DAT_SFR_9c = cVar1 + '\x01';
  cVar1 = DAT_SFR_9c;
  DAT_SFR_9c = cVar1 + '\x01';
  cVar1 = DAT_SFR_9c;
  DAT_SFR_9c = cVar1 + '\x01';
  cVar1 = DAT_SFR_9c;
  DAT_SFR_9c = cVar1 + '\x01';
  cVar1 = DAT_SFR_9c;
  DAT_SFR_9c = cVar1 + '\x01';
  cVar1 = DAT_SFR_9c;
  DAT_SFR_9c = cVar1 + '\x01';
  cVar1 = DAT_SFR_9c;
  DAT_SFR_9c = cVar1 + '\x01';
  cVar1 = DAT_SFR_9c;
  DAT_SFR_9c = cVar1 + '\x01';
  cVar1 = DAT_SFR_9c;
  DAT_SFR_9c = cVar1 + '\x01';
  cVar1 = DAT_SFR_9c;
  DAT_SFR_9c = cVar1 + '\x01';
  cVar1 = DAT_SFR_9c;
  DAT_SFR_9c = cVar1 + '\x01';
  cVar1 = DAT_SFR_9c;
  DAT_SFR_9c = cVar1 + '\x01';
  cVar1 = DAT_SFR_9c;
  DAT_SFR_9c = cVar1 + '\x01';
  cVar1 = DAT_SFR_9c;
  DAT_SFR_9c = cVar1 + '\x01';
  cVar1 = DAT_SFR_9c;
  DAT_SFR_9c = cVar1 + '\x01';
  cVar1 = DAT_SFR_9c;
  DAT_SFR_9c = cVar1 + '\x01';
  cVar1 = DAT_SFR_9c;
  DAT_SFR_9c = cVar1 + '\x01';
  cVar1 = DAT_SFR_9c;
  DAT_SFR_9c = cVar1 + '\x01';
  cVar1 = DAT_SFR_9c;
  DAT_SFR_9c = cVar1 + '\x01';
  cVar1 = DAT_SFR_9c;
  DAT_SFR_9c = cVar1 + '\x01';
  cVar1 = DAT_SFR_9c;
  DAT_SFR_9c = cVar1 + '\x01';
  cVar1 = DAT_SFR_9c;
  DAT_SFR_9c = cVar1 + '\x01';
  cVar1 = DAT_SFR_9c;
  DAT_SFR_9c = cVar1 + '\x01';
  cVar1 = DAT_SFR_9c;
  DAT_SFR_9c = cVar1 + '\x01';
  cVar1 = DAT_SFR_9c;
  DAT_SFR_9c = cVar1 + '\x01';
  cVar1 = DAT_SFR_9c;
  DAT_SFR_9c = cVar1 + '\x01';
  cVar1 = DAT_SFR_9c;
  DAT_SFR_9c = cVar1 + '\x01';
  cVar1 = DAT_SFR_9c;
  DAT_SFR_9c = cVar1 + '\x01';
  cVar1 = DAT_SFR_9c;
  DAT_SFR_9c = cVar1 + '\x01';
  cVar1 = DAT_SFR_9c;
  DAT_SFR_9c = cVar1 + '\x01';
  cVar1 = DAT_SFR_9c;
  DAT_SFR_9c = cVar1 + '\x01';
  cVar1 = DAT_SFR_9c;
  DAT_SFR_9c = cVar1 + '\x01';
  cVar1 = DAT_SFR_9c;
  DAT_SFR_9c = cVar1 + '\x01';
  cVar1 = DAT_SFR_9c;
  DAT_SFR_9c = cVar1 + '\x01';
  cVar1 = DAT_SFR_9c;
  DAT_SFR_9c = cVar1 + '\x01';
  cVar1 = DAT_SFR_9c;
  DAT_SFR_9c = cVar1 + '\x01';
  cVar1 = DAT_SFR_9c;
  DAT_SFR_9c = cVar1 + '\x01';
  cVar1 = DAT_SFR_9c;
  DAT_SFR_9c = cVar1 + '\x01';
  cVar1 = DAT_SFR_9c;
  DAT_SFR_9c = cVar1 + '\x01';
  cVar1 = DAT_SFR_9c;
  DAT_SFR_9c = cVar1 + '\x01';
  cVar1 = DAT_SFR_9c;
  DAT_SFR_9c = cVar1 + '\x01';
  cVar1 = DAT_SFR_9c;
  DAT_SFR_9c = cVar1 + '\x01';
  cVar1 = DAT_SFR_9c;
  DAT_SFR_9c = cVar1 + '\x01';
  cVar1 = DAT_SFR_9c;
  DAT_SFR_9c = cVar1 + '\x01';
  cVar1 = DAT_SFR_9c;
  DAT_SFR_9c = cVar1 + '\x01';
  cVar1 = DAT_SFR_9c;
  DAT_SFR_9c = cVar1 + '\x01';
  cVar1 = DAT_SFR_9c;
  DAT_SFR_9c = cVar1 + '\x01';
  cVar1 = DAT_SFR_9c;
  DAT_SFR_9c = cVar1 + '\x01';
  cVar1 = DAT_SFR_9c;
  DAT_SFR_9c = cVar1 + '\x01';
  cVar1 = DAT_SFR_9c;
  DAT_SFR_9c = cVar1 + '\x01';
  cVar1 = DAT_SFR_9c;
  DAT_SFR_9c = cVar1 + '\x01';
  cVar1 = DAT_SFR_9c;
  DAT_SFR_9c = cVar1 + '\x01';
  cVar1 = DAT_SFR_9c;
  DAT_SFR_9c = cVar1 + '\x01';
  cVar1 = DAT_SFR_9c;
  DAT_SFR_9c = cVar1 + '\x01';
  cVar1 = DAT_SFR_9c;
  DAT_SFR_9c = cVar1 + '\x01';
  cVar1 = DAT_SFR_9c;
  DAT_SFR_9c = cVar1 + '\x01';
  cVar1 = DAT_SFR_9c;
  DAT_SFR_9c = cVar1 + '\x01';
  cVar1 = DAT_SFR_9c;
  DAT_SFR_9c = cVar1 + '\x01';
  cVar1 = DAT_SFR_9c;
  DAT_SFR_9c = cVar1 + '\x01';
  cVar1 = DAT_SFR_9c;
  DAT_SFR_9c = cVar1 + '\x01';
  cVar1 = DAT_SFR_9c;
  DAT_SFR_9c = cVar1 + '\x01';
  cVar1 = DAT_SFR_9c;
  DAT_SFR_9c = cVar1 + '\x01';
  cVar1 = DAT_SFR_9c;
  DAT_SFR_9c = cVar1 + '\x01';
  cVar1 = DAT_SFR_9c;
  DAT_SFR_9c = cVar1 + '\x01';
  cVar1 = DAT_SFR_9c;
  DAT_SFR_9c = cVar1 + '\x01';
  cVar1 = DAT_SFR_9c;
  DAT_SFR_9c = cVar1 + '\x01';
  cVar1 = DAT_SFR_9c;
  DAT_SFR_9c = cVar1 + '\x01';
  cVar1 = DAT_SFR_9c;
  DAT_SFR_9c = cVar1 + '\x01';
  cVar1 = DAT_SFR_9c;
  DAT_SFR_9c = cVar1 + '\x01';
  cVar1 = DAT_SFR_9c;
  DAT_SFR_9c = cVar1 + '\x01';
  cVar1 = DAT_SFR_9c;
  DAT_SFR_9c = cVar1 + '\x01';
  cVar1 = DAT_SFR_9c;
  DAT_SFR_9c = cVar1 + '\x01';
  cVar1 = DAT_SFR_9c;
  DAT_SFR_9c = cVar1 + '\x01';
  cVar1 = DAT_SFR_9c;
  DAT_SFR_9c = cVar1 + '\x01';
  cVar1 = DAT_SFR_9c;
  DAT_SFR_9c = cVar1 + '\x01';
  cVar1 = DAT_SFR_9c;
  DAT_SFR_9c = cVar1 + '\x01';
  cVar1 = DAT_SFR_9c;
  DAT_SFR_9c = cVar1 + '\x01';
  cVar1 = DAT_SFR_9c;
  DAT_SFR_9c = cVar1 + '\x01';
  cVar1 = DAT_SFR_9c;
  DAT_SFR_9c = cVar1 + '\x01';
  cVar1 = DAT_SFR_9c;
  DAT_SFR_9c = cVar1 + '\x01';
  cVar1 = DAT_SFR_9c;
  DAT_SFR_9c = cVar1 + '\x01';
  cVar1 = DAT_SFR_9c;
  DAT_SFR_9c = cVar1 + '\x01';
  cVar1 = DAT_SFR_9c;
  DAT_SFR_9c = cVar1 + '\x01';
  cVar1 = DAT_SFR_9c;
  DAT_SFR_9c = cVar1 + '\x01';
  cVar1 = DAT_SFR_9c;
  DAT_SFR_9c = cVar1 + '\x01';
  cVar1 = DAT_SFR_9c;
  DAT_SFR_9c = cVar1 + '\x01';
  cVar1 = DAT_SFR_9c;
  DAT_SFR_9c = cVar1 + '\x01';
  cVar1 = DAT_SFR_9c;
  DAT_SFR_9c = cVar1 + '\x01';
  cVar1 = DAT_SFR_9c;
  DAT_SFR_9c = cVar1 + '\x01';
  cVar1 = DAT_SFR_9c;
  DAT_SFR_9c = cVar1 + '\x01';
  cVar1 = DAT_SFR_9c;
  DAT_SFR_9c = cVar1 + '\x01';
  cVar1 = DAT_SFR_9c;
  DAT_SFR_9c = cVar1 + '\x01';
  cVar1 = DAT_SFR_9c;
  DAT_SFR_9c = cVar1 + '\x01';
  cVar1 = DAT_SFR_9c;
  DAT_SFR_9c = cVar1 + '\x01';
  while ((DAT_INTMEM_26 != '\0' || (DAT_INTMEM_27 != '\0'))) {
    if (_6_1 != '\0') {
      _6_1 = '\0';
      FUN_CODE_0950();
    }
    if (_6_0 != '\0') {
      _6_0 = '\0';
      FUN_CODE_0946();
    }
    if (_6_7 == '\0') {
      if (_6_5 != '\0') {
        _6_5 = '\0';
        FUN_CODE_07f1();
      }
    }
    else {
      _6_7 = '\0';
      FUN_CODE_2260();
    }
  }
  return;
}


// ===== FUN_CODE_07c4  [app]  callers: CODE:2200

void FUN_CODE_07c4(void)

{
  while ((DAT_INTMEM_26 != '\0' || (DAT_INTMEM_27 != '\0'))) {
    if (_6_1 != '\0') {
      _6_1 = '\0';
      FUN_CODE_0950();
    }
    if (_6_0 != '\0') {
      _6_0 = '\0';
      FUN_CODE_0946();
    }
    if (_6_7 == '\0') {
      if (_6_5 != '\0') {
        _6_5 = '\0';
        FUN_CODE_07f1();
      }
    }
    else {
      _6_7 = '\0';
      FUN_CODE_2260();
    }
  }
  return;
}


// ===== FUN_CODE_07f1  [app]  callers: CODE:07c4

void FUN_CODE_07f1(char param_1)

{
  char cVar1;
  
  FUN_CODE_08b8();
  cVar1 = DAT_INTMEM_43;
  DAT_INTMEM_43 = DAT_INTMEM_43 + 1;
  cVar1 = cVar1 + -9;
  if (9 < DAT_INTMEM_43) {
    cVar1 = '\0';
    DAT_INTMEM_43 = 0;
  }
  FUN_CODE_6fa5(cVar1);
  if ((param_1 != '\x01') && (DAT_INTMEM_43 % 5 == 0)) {
    FUN_CODE_08bd();
    DAT_INTMEM_44 = DAT_INTMEM_44 + 1;
    if ((DAT_INTMEM_44 & 1) != 0) {
      FUN_CODE_08c8();
      return;
    }
    thunk_FUN_CODE_6f21();
    if (DAT_INTMEM_44 == 4) {
      thunk_FUN_CODE_6f32();
    }
    else if (DAT_INTMEM_44 == 6) {
      thunk_FUN_CODE_34ff();
    }
    else if (DAT_INTMEM_44 == 8) {
      DAT_INTMEM_46 = DAT_INTMEM_46 + 1;
      if ((DAT_INTMEM_46 & 1) == 0) {
        thunk_FUN_CODE_6f65();
      }
      else {
        thunk_FUN_CODE_6f5b();
      }
    }
    else if (DAT_INTMEM_44 == 2) {
      thunk_FUN_CODE_33ff();
    }
    else {
      DAT_INTMEM_44 = 0;
    }
    if (DAT_INTMEM_44 == 0) {
      DAT_INTMEM_45 = DAT_INTMEM_45 + 1;
      if ((DAT_INTMEM_45 & 1) != 0) {
        thunk_FUN_CODE_35fd();
        return;
      }
                    /* WARNING: Subroutine does not return */
      FUN_CODE_890a(DAT_INTMEM_45);
    }
  }
  return;
}


// ===== FUN_CODE_0800  [app]  callers: 

void FUN_CODE_0800(char param_1)

{
  FUN_CODE_6fa5();
  if ((param_1 != '\x01') && (DAT_INTMEM_43 % 5 == 0)) {
    FUN_CODE_08bd();
    DAT_INTMEM_44 = DAT_INTMEM_44 + 1;
    if ((DAT_INTMEM_44 & 1) != 0) {
      FUN_CODE_08c8();
      return;
    }
    thunk_FUN_CODE_6f21();
    if (DAT_INTMEM_44 == 4) {
      thunk_FUN_CODE_6f32();
    }
    else if (DAT_INTMEM_44 == 6) {
      thunk_FUN_CODE_34ff();
    }
    else if (DAT_INTMEM_44 == 8) {
      DAT_INTMEM_46 = DAT_INTMEM_46 + 1;
      if ((DAT_INTMEM_46 & 1) == 0) {
        thunk_FUN_CODE_6f65();
      }
      else {
        thunk_FUN_CODE_6f5b();
      }
    }
    else if (DAT_INTMEM_44 == 2) {
      thunk_FUN_CODE_33ff();
    }
    else {
      DAT_INTMEM_44 = 0;
    }
    if (DAT_INTMEM_44 == 0) {
      DAT_INTMEM_45 = DAT_INTMEM_45 + 1;
      if ((DAT_INTMEM_45 & 1) != 0) {
        thunk_FUN_CODE_35fd();
        return;
      }
                    /* WARNING: Subroutine does not return */
      FUN_CODE_890a(DAT_INTMEM_45);
    }
  }
  return;
}


// ===== FUN_CODE_0804  [app]  callers: 

void FUN_CODE_0804(char param_1)

{
  if ((param_1 != '\x01') && (DAT_INTMEM_43 % 5 == 0)) {
    FUN_CODE_08bd();
    DAT_INTMEM_44 = DAT_INTMEM_44 + 1;
    if ((DAT_INTMEM_44 & 1) != 0) {
      FUN_CODE_08c8();
      return;
    }
    thunk_FUN_CODE_6f21();
    if (DAT_INTMEM_44 == 4) {
      thunk_FUN_CODE_6f32();
    }
    else if (DAT_INTMEM_44 == 6) {
      thunk_FUN_CODE_34ff();
    }
    else if (DAT_INTMEM_44 == 8) {
      DAT_INTMEM_46 = DAT_INTMEM_46 + 1;
      if ((DAT_INTMEM_46 & 1) == 0) {
        thunk_FUN_CODE_6f65();
      }
      else {
        thunk_FUN_CODE_6f5b();
      }
    }
    else if (DAT_INTMEM_44 == 2) {
      thunk_FUN_CODE_33ff();
    }
    else {
      DAT_INTMEM_44 = 0;
    }
    if (DAT_INTMEM_44 == 0) {
      DAT_INTMEM_45 = DAT_INTMEM_45 + 1;
      if ((DAT_INTMEM_45 & 1) != 0) {
        thunk_FUN_CODE_35fd();
        return;
      }
                    /* WARNING: Subroutine does not return */
      FUN_CODE_890a(DAT_INTMEM_45);
    }
  }
  return;
}


// ===== FUN_CODE_0815  [app]  callers: CODE:0f72

void FUN_CODE_0815(void)

{
  return;
}


// ===== FUN_CODE_0818  [app]  callers: CODE:0f40

void FUN_CODE_0818(void)

{
  FUN_CODE_08bd();
  DAT_INTMEM_44 = DAT_INTMEM_44 + 1;
  if ((DAT_INTMEM_44 & 1) != 0) {
    FUN_CODE_08c8();
    return;
  }
  thunk_FUN_CODE_6f21();
  if (DAT_INTMEM_44 == 4) {
    thunk_FUN_CODE_6f32();
  }
  else if (DAT_INTMEM_44 == 6) {
    thunk_FUN_CODE_34ff();
  }
  else if (DAT_INTMEM_44 == 8) {
    DAT_INTMEM_46 = DAT_INTMEM_46 + 1;
    if ((DAT_INTMEM_46 & 1) == 0) {
      thunk_FUN_CODE_6f65();
    }
    else {
      thunk_FUN_CODE_6f5b();
    }
  }
  else if (DAT_INTMEM_44 == 2) {
    thunk_FUN_CODE_33ff();
  }
  else {
    DAT_INTMEM_44 = 0;
  }
  if (DAT_INTMEM_44 == 0) {
    DAT_INTMEM_45 = DAT_INTMEM_45 + 1;
    if ((DAT_INTMEM_45 & 1) != 0) {
      thunk_FUN_CODE_35fd();
      return;
    }
                    /* WARNING: Subroutine does not return */
    FUN_CODE_890a(DAT_INTMEM_45);
  }
  return;
}


// ===== thunk_FUN_CODE_6f75  [app]  callers: 

void thunk_FUN_CODE_6f75(void)

{
  if ((DAT_EXTMEM_0897 >> 6 & 1) != 0) {
    if ((DAT_EXTMEM_0897 < 0x41) << 7 < '\0') {
      DAT_EXTMEM_0897 = DAT_EXTMEM_0897 + 1;
    }
    else {
      DAT_EXTMEM_0897 = 0x80;
    }
  }
  if ((DAT_EXTMEM_0898 >> 6 & 1) != 0) {
    if (0x40 < DAT_EXTMEM_0898) {
      DAT_EXTMEM_0898 = 0x80;
      return;
    }
    DAT_EXTMEM_0898 = DAT_EXTMEM_0898 + 1;
  }
  return;
}


// ===== thunk_FUN_CODE_35fe  [app]  callers: 

void thunk_FUN_CODE_35fe(void)

{
  return;
}


// ===== thunk_FUN_CODE_35ff  [app]  callers: 

void thunk_FUN_CODE_35ff(void)

{
  return;
}


// ===== thunk_FUN_CODE_36fc  [app]  callers: 

void thunk_FUN_CODE_36fc(void)

{
  return;
}


// ===== thunk_FUN_CODE_36fd  [app]  callers: 

void thunk_FUN_CODE_36fd(void)

{
  return;
}


// ===== thunk_FUN_CODE_6f75  [app]  callers: 

void thunk_FUN_CODE_6f75(void)

{
  if ((DAT_EXTMEM_0897 >> 6 & 1) != 0) {
    if ((DAT_EXTMEM_0897 < 0x41) << 7 < '\0') {
      DAT_EXTMEM_0897 = DAT_EXTMEM_0897 + 1;
    }
    else {
      DAT_EXTMEM_0897 = 0x80;
    }
  }
  if ((DAT_EXTMEM_0898 >> 6 & 1) != 0) {
    if (0x40 < DAT_EXTMEM_0898) {
      DAT_EXTMEM_0898 = 0x80;
      return;
    }
    DAT_EXTMEM_0898 = DAT_EXTMEM_0898 + 1;
  }
  return;
}


// ===== thunk_FUN_CODE_35fe  [app]  callers: 

void thunk_FUN_CODE_35fe(void)

{
  return;
}


// ===== thunk_FUN_CODE_35ff  [app]  callers: 

void thunk_FUN_CODE_35ff(void)

{
  return;
}


// ===== thunk_FUN_CODE_36fe  [app]  callers: 

void thunk_FUN_CODE_36fe(void)

{
  return;
}


// ===== FUN_CODE_08a7  [app]  callers: 

void FUN_CODE_08a7(void)

{
  DAT_INTMEM_45 = 0;
  DAT_INTMEM_47 = DAT_INTMEM_47 + '\x01';
  if (DAT_INTMEM_47 == '<') {
    thunk_FUN_CODE_36ff();
    DAT_INTMEM_47 = '\0';
  }
  return;
}


// ===== FUN_CODE_08b8  [app]  callers: CODE:07f1

void FUN_CODE_08b8(void)

{
  FUN_CODE_34f7(DAT_INTMEM_43);
  return;
}


// ===== FUN_CODE_08bd  [app]  callers: CODE:0818

void FUN_CODE_08bd(void)

{
  if ((DAT_INTMEM_40 >> 4 & 1) != 0) {
    FUN_CODE_258e();
  }
  FUN_CODE_6ea5();
  return;
}


// ===== FUN_CODE_08c8  [app]  callers: CODE:0818

void FUN_CODE_08c8(void)

{
  bool bVar1;
  char cVar2;
  byte bVar3;
  
  if ((byte)-(((DAT_EXTMEM_00f5 == '\0') << 7) >> 7) <= DAT_EXTMEM_00f4) {
    bVar1 = DAT_EXTMEM_00f5 != '\0';
    DAT_EXTMEM_00f5 = DAT_EXTMEM_00f5 + -1;
    DAT_EXTMEM_00f4 = DAT_EXTMEM_00f4 + (-1 - ((bVar1 << 7) >> 7));
  }
  if ((byte)-(((DAT_EXTMEM_00f9 == '\0') << 7) >> 7) <= DAT_EXTMEM_00f8) {
    bVar1 = DAT_EXTMEM_00f9 != '\0';
    DAT_EXTMEM_00f9 = DAT_EXTMEM_00f9 + -1;
    DAT_EXTMEM_00f8 = DAT_EXTMEM_00f8 + (-1 - ((bVar1 << 7) >> 7));
  }
  cVar2 = ((DAT_EXTMEM_00f7 == '\0') << 7) >> 7;
  bVar3 = DAT_EXTMEM_00f6 + cVar2;
  if ((byte)-cVar2 <= DAT_EXTMEM_00f6) {
    bVar1 = DAT_EXTMEM_00f7 != '\0';
    DAT_EXTMEM_00f7 = DAT_EXTMEM_00f7 + -1;
    bVar3 = DAT_EXTMEM_00f6 + (-1 - ((bVar1 << 7) >> 7));
    DAT_EXTMEM_00f6 = bVar3;
  }
  FUN_CODE_6ee1(bVar3);
  return;
}


// ===== FUN_CODE_0916  [app]  callers: 

void FUN_CODE_0916(char param_1,char *param_2)

{
  char in_PSW;
  
  *param_2 = param_1 + (-1 - (in_PSW >> 7));
  FUN_CODE_6ee1();
  return;
}


// ===== thunk_FUN_CODE_6f21  [app]  callers: CODE:0818

void thunk_FUN_CODE_6f21(void)

{
  if ((DAT_EXTMEM_0800 != 'P') || (DAT_EXTMEM_088b != '\0')) {
    FUN_CODE_6e72();
  }
  return;
}


// ===== thunk_FUN_CODE_33ff  [app]  callers: CODE:0818

void thunk_FUN_CODE_33ff(void)

{
  return;
}


// ===== thunk_FUN_CODE_6f32  [app]  callers: CODE:0818

void thunk_FUN_CODE_6f32(void)

{
  if (DAT_EXTMEM_0802 == '\x01') {
    FUN_CODE_1b56(0,0x57);
    DAT_EXTMEM_0802 = 2;
    return;
  }
  if (DAT_EXTMEM_0802 == '\x02') {
    FUN_CODE_1b56(1,0x57);
    DAT_EXTMEM_0802 = '\0';
  }
  return;
}


// ===== thunk_FUN_CODE_34ff  [app]  callers: CODE:0818

void thunk_FUN_CODE_34ff(void)

{
  return;
}


// ===== thunk_FUN_CODE_6f5b  [app]  callers: CODE:0818

void thunk_FUN_CODE_6f5b(void)

{
  if (DAT_EXTMEM_08ae != '\0') {
    DAT_EXTMEM_08ae = DAT_EXTMEM_08ae + -1;
  }
  return;
}


// ===== thunk_FUN_CODE_6f65  [app]  callers: CODE:0818

void thunk_FUN_CODE_6f65(void)

{
  FUN_CODE_82e7();
  FUN_CODE_7a38();
  if (DAT_EXTMEM_0895 != '\0') {
    DAT_EXTMEM_0895 = DAT_EXTMEM_0895 + -1;
  }
  return;
}


// ===== thunk_FUN_CODE_35fd  [app]  callers: CODE:0818

void thunk_FUN_CODE_35fd(void)

{
  return;
}


// ===== thunk_FUN_CODE_6f75  [app]  callers: 

void thunk_FUN_CODE_6f75(void)

{
  if ((DAT_EXTMEM_0897 >> 6 & 1) != 0) {
    if ((DAT_EXTMEM_0897 < 0x41) << 7 < '\0') {
      DAT_EXTMEM_0897 = DAT_EXTMEM_0897 + 1;
    }
    else {
      DAT_EXTMEM_0897 = 0x80;
    }
  }
  if ((DAT_EXTMEM_0898 >> 6 & 1) != 0) {
    if (0x40 < DAT_EXTMEM_0898) {
      DAT_EXTMEM_0898 = 0x80;
      return;
    }
    DAT_EXTMEM_0898 = DAT_EXTMEM_0898 + 1;
  }
  return;
}


// ===== thunk_FUN_CODE_35fe  [app]  callers: 

void thunk_FUN_CODE_35fe(void)

{
  return;
}


// ===== thunk_FUN_CODE_35ff  [app]  callers: 

void thunk_FUN_CODE_35ff(void)

{
  return;
}


// ===== thunk_FUN_CODE_36fc  [app]  callers: 

void thunk_FUN_CODE_36fc(void)

{
  return;
}


// ===== thunk_FUN_CODE_36fd  [app]  callers: 

void thunk_FUN_CODE_36fd(void)

{
  return;
}


// ===== thunk_FUN_CODE_36fe  [app]  callers: 

void thunk_FUN_CODE_36fe(void)

{
  return;
}


// ===== thunk_FUN_CODE_36ff  [app]  callers: CODE:08a7

void thunk_FUN_CODE_36ff(void)

{
  return;
}


// ===== FUN_CODE_0946  [app]  callers: CODE:07c4

void FUN_CODE_0946(char param_1)

{
  FUN_CODE_6fab();
  if (param_1 == -1) {
    FUN_CODE_26b7();
  }
  return;
}


// ===== FUN_CODE_0950  [app]  callers: CODE:07c4

void FUN_CODE_0950(void)

{
  DAT_EXTMEM_1106 = DAT_EXTMEM_1106 & 0xbf;
  nop();
  nop();
  nop();
  nop();
  FUN_CODE_4f66();
  DAT_EXTMEM_1106 = DAT_EXTMEM_1106 | 0x40;
  return;
}


// ===== FUN_CODE_0984  [app]  callers: CODE:0992

void FUN_CODE_0984(void)

{
  char cVar1;
  
  cVar1 = '\0';
  do {
    DAT_EXTMEM_0480 = DAT_EXTMEM_0480 + '\x01';
    cVar1 = cVar1 + '\x01';
  } while (cVar1 != -0x38);
  return;
}


// ===== H_0986  [app]  callers: 

void H_0986(char param_1)

{
  do {
    DAT_EXTMEM_0480 = DAT_EXTMEM_0480 + '\x01';
    param_1 = param_1 + '\x01';
  } while (param_1 != -0x38);
  return;
}


// ===== FUN_CODE_0992  [app]  callers: CODE:63e6 CODE:0b4b CODE:64f0 CODE:65fa CODE:600d CODE:5ccf CODE:5a36

void FUN_CODE_0992(char param_1)

{
  byte *pbVar1;
  undefined2 *puVar2;
  
  pbVar1 = *(byte **)CONCAT11('\v' - (((0x47U < (byte)(param_1 * '\x15')) << 7) >> 7),
                              param_1 * '\x15' + 0xb8);
  *pbVar1 = *pbVar1 | 2;
  *pbVar1 = *pbVar1 & 0xfd;
  **(undefined1 **)
    CONCAT11('\v' - (((8U < (byte)(param_1 * '\x0f')) << 7) >> 7),param_1 * '\x0f' - 9) = 0xfe;
  **(undefined1 **)
    CONCAT11('\v' - (((2U < (byte)(param_1 * '\x0f')) << 7) >> 7),param_1 * '\x0f' - 3) = 0x40;
  **(undefined1 **)CONCAT11('\v' - (((param_1 * '\x0f' != '\0') << 7) >> 7),param_1 * '\x0f' + -1) =
       0x40;
  FUN_CODE_0984();
  puVar2 = (undefined2 *)
           CONCAT11('\f' - (((0xfeU < (byte)(param_1 * '\x0f')) << 7) >> 7),param_1 * '\x0f' + 1);
  *(byte *)*puVar2 =
       *(byte *)*puVar2 |
       *(byte *)CONCAT11('\f' - (((0xfcU < (byte)(param_1 * '\x0f')) << 7) >> 7),
                         param_1 * '\x0f' + 3);
  FUN_CODE_0984();
  **(undefined1 **)
    CONCAT11('\v' - (((2U < (byte)(param_1 * '\x0f')) << 7) >> 7),param_1 * '\x0f' - 3) = 0;
  **(undefined1 **)CONCAT11('\v' - (((param_1 * '\x0f' != '\0') << 7) >> 7),param_1 * '\x0f' + -1) =
       0;
  **(undefined1 **)
    CONCAT11('\v' - (((6U < (byte)(param_1 * '\x0f')) << 7) >> 7),param_1 * '\x0f' - 7) = 2;
  **(undefined1 **)
    CONCAT11('\v' - (((4U < (byte)(param_1 * '\x0f')) << 7) >> 7),param_1 * '\x0f' - 5) = 3;
  FUN_CODE_0984();
  **(undefined1 **)
    CONCAT11('\v' - (((4U < (byte)(param_1 * '\x0f')) << 7) >> 7),param_1 * '\x0f' - 5) = 7;
  **(undefined1 **)
    CONCAT11('\v' - (((6U < (byte)(param_1 * '\x0f')) << 7) >> 7),param_1 * '\x0f' - 7) = 0x11;
  return;
}


// ===== FUN_CODE_0ae6  [app]  callers: CODE:0b4b

void FUN_CODE_0ae6(char param_1)

{
  if ((**(byte **)CONCAT11('\v' - (((4U < (byte)(param_1 * '\x0f')) << 7) >> 7),param_1 * '\x0f' - 5
                          ) & 3) == 3) {
    return;
  }
  return;
}


// ===== FUN_CODE_0b0b  [app]  callers: CODE:0b4b

void FUN_CODE_0b0b(char param_1)

{
  if (((**(byte **)CONCAT11('\v' - (((2U < (byte)(param_1 * '\x0f')) << 7) >> 7),
                            param_1 * '\x0f' - 3) & 0xfb) == 0) &&
     ((**(byte **)CONCAT11('\v' - (((param_1 * '\x0f' != '\0') << 7) >> 7),param_1 * '\x0f' + -1) &
      0xfb) == 0)) {
    return;
  }
  return;
}


// ===== H_0B2F  [app]  callers: 

void H_0B2F(undefined1 param_1)

{
  char in_PSW;
  
  if ((**(byte **)CONCAT11('\v' - (in_PSW >> 7),param_1) & 0xfb) != 0) {
    return;
  }
  return;
}


// ===== FUN_CODE_0b4b  [app]  callers: CODE:63e6 CODE:64f0 CODE:65fa CODE:600d CODE:5ccf CODE:5a36

char FUN_CODE_0b4b(undefined1 param_1,char param_2)

{
  byte bVar1;
  byte *pbVar2;
  char cVar3;
  char cVar4;
  
  cVar4 = param_2;
  DAT_EXTMEM_0481 = param_1;
  FUN_CODE_0b0b(param_1,1);
  if (cVar4 == '\0') {
    cVar4 = '\0';
  }
  else {
    cVar3 = param_2;
    FUN_CODE_0ae6(cVar4);
    if (cVar3 == '\x01') {
      pbVar2 = *(byte **)CONCAT11('\f' - (((0xfbU < (byte)(param_2 * '\x0f')) << 7) >> 7),
                                  param_2 * '\x0f' + 4);
      bVar1 = *pbVar2;
      *pbVar2 = bVar1 + 1;
      cVar4 = bVar1 - (DAT_EXTMEM_008f + 1U);
      if (DAT_EXTMEM_008f + 1U <= bVar1) {
        cVar4 = FUN_CODE_0992(cVar4,0,param_2);
      }
    }
    else {
      cVar4 = '\0';
      **(undefined1 **)
        CONCAT11('\f' - (((0xfbU < (byte)(param_2 * '\x0f')) << 7) >> 7),param_2 * '\x0f' + 4) = 0;
    }
  }
  return cVar4;
}


// ===== H_0BB8  [app]  callers: 

void H_0BB8(byte *param_1,char param_2)

{
  FUN_CODE_08c8(*param_1 >> 1 | *param_1 << 7,param_2 + -1);
  return;
}


// ===== FUN_CODE_0c33  [app]  callers: CODE:0c3c CODE:3300

undefined1 FUN_CODE_0c33(void)

{
  TL0 = 0;
  TH0 = 0xfd;
  TF0 = 0;
  return 0;
}


// ===== FUN_CODE_0c3c  [app]  callers: 

void FUN_CODE_0c3c(void)

{
  FUN_CODE_0c33();
  TR0 = 1;
  return;
}


// ===== FUN_CODE_0c42  [app]  callers: 

void FUN_CODE_0c42(void)

{
  TR0 = 0;
  TF0 = 0;
  return;
}


// ===== FUN_CODE_0c47  [app]  callers: CODE:2200 CODE:0ec1

undefined1 FUN_CODE_0c47(void)

{
  TR0 = 0;
  TF0 = 0;
  TL0 = 0;
  TH0 = 0xfd;
  TMOD = 0x11;
  TR0 = 1;
  ET0 = 1;
  TR1 = 0;
  TF1 = 0;
  TL1 = 1;
  TH1 = 0xfa;
  ET1 = 1;
  return 0;
}


// ===== H_0C65  [app]  callers: 

void H_0C65(char param_1)

{
  char cVar1;
  
  TR1 = 0;
  ET1 = 0;
  DAT_EXTMEM_0482 = param_1;
  FUN_CODE_059d();
  for (; DAT_EXTMEM_0482 != '\0'; DAT_EXTMEM_0482 = DAT_EXTMEM_0482 + -1) {
    TH1 = 0xfd;
    TL1 = 0;
    TF1 = 0;
    TR1 = 1;
    do {
      cVar1 = TF1;
    } while (cVar1 == '\0');
    TR1 = 0;
    TF1 = 0;
  }
  FUN_CODE_05a4();
  ET1 = 1;
  return;
}


// ===== FUN_CODE_0c96  [app]  callers: CODE:4dba CODE:31ec CODE:4b88

void FUN_CODE_0c96(char param_1)

{
  char cVar1;
  
  TR1 = 0;
  ET1 = 0;
  nop();
  nop();
  nop();
  nop();
  for (; param_1 != '\0'; param_1 = param_1 + -1) {
    TH1 = 0xfd;
    TL1 = 0;
    TF1 = 0;
    TR1 = 1;
    do {
      cVar1 = TF1;
    } while (cVar1 == '\0');
    TR1 = 0;
    TF1 = 0;
  }
  ET1 = 1;
  return;
}


// ===== thunk_FUN_CODE_0c42  [app]  callers: CODE:813c

void thunk_FUN_CODE_0c42(void)

{
  TR0 = 0;
  TF0 = 0;
  return;
}


// ===== thunk_FUN_CODE_0c3c  [app]  callers: CODE:813c

void thunk_FUN_CODE_0c3c(void)

{
  FUN_CODE_0c33();
  TR0 = 1;
  return;
}


// ===== FUN_CODE_0cbf  [app]  callers: CODE:813c

void FUN_CODE_0cbf(void)

{
  undefined1 uVar1;
  char cVar2;
  
  FUN_CODE_8844(0x74a);
  cVar2 = FUN_CODE_8820(DAT_EXTMEM_074a,DAT_EXTMEM_074b,DAT_EXTMEM_074c,DAT_EXTMEM_074d,0,0,0,0);
  if (cVar2 != '\0') {
    cVar2 = -0x80;
    FUN_CODE_8820(DAT_EXTMEM_074a,DAT_EXTMEM_074b,DAT_EXTMEM_074c,DAT_EXTMEM_074d,5,0x26,0x5c,0);
    if (cVar2 < '\0') {
      FUN_CODE_8820(DAT_EXTMEM_074a,DAT_EXTMEM_074b,DAT_EXTMEM_074c,DAT_EXTMEM_074d,0,0xf4,0x24,0);
      if (cVar2 < '\0') {
        cVar2 = -0x80;
        FUN_CODE_8820(DAT_EXTMEM_074a,DAT_EXTMEM_074b,DAT_EXTMEM_074c,DAT_EXTMEM_074d,0,7,0xa1,0x20)
        ;
        if (cVar2 < '\0') {
          DAT_EXTMEM_0752 = 0;
          FUN_CODE_8703(DAT_EXTMEM_074a,DAT_EXTMEM_074b,DAT_EXTMEM_074c,DAT_EXTMEM_074d,0,0,0x80,0);
          FUN_CODE_878e(0,0,3,0xe8);
        }
        else {
          DAT_EXTMEM_0752 = 1;
          FUN_CODE_878e(0,0,3,0xe8,DAT_EXTMEM_074a,DAT_EXTMEM_074b,DAT_EXTMEM_074c,DAT_EXTMEM_074d);
          FUN_CODE_8703(0,0,4,0);
        }
      }
      else {
        DAT_EXTMEM_0752 = 2;
        FUN_CODE_878e(0,0,0xc,0x35,DAT_EXTMEM_074a,DAT_EXTMEM_074b,DAT_EXTMEM_074c,DAT_EXTMEM_074d);
        FUN_CODE_8703(0,0,0,100);
      }
      FUN_CODE_8844(0x74e);
      FUN_CODE_85a7(DAT_EXTMEM_0752,DAT_CODE_0e9c,DAT_CODE_0e9b,DAT_CODE_0e9a);
      uVar1 = DAT_EXTMEM_0751;
      FUN_CODE_8831(0x10,DAT_EXTMEM_074e,DAT_EXTMEM_074f,DAT_EXTMEM_0750,DAT_EXTMEM_0751);
      FUN_CODE_85a7(uVar1,DAT_CODE_0ea5,DAT_CODE_0ea4,DAT_CODE_0ea3);
      uVar1 = DAT_EXTMEM_0751;
      FUN_CODE_8831(8,DAT_EXTMEM_074e,DAT_EXTMEM_074f,DAT_EXTMEM_0750,DAT_EXTMEM_0751);
      FUN_CODE_85a7(uVar1,DAT_CODE_0ea2,DAT_CODE_0ea1,DAT_CODE_0ea0);
      FUN_CODE_85a7(DAT_EXTMEM_0751,DAT_CODE_0e9f,DAT_CODE_0e9e,DAT_CODE_0e9d);
    }
  }
  return;
}


// ===== FUN_CODE_0e30  [app]  callers: CODE:813c

void FUN_CODE_0e30(void)

{
  byte bVar1;
  
  FUN_CODE_85a7(DAT_CODE_0eac,DAT_CODE_0eab,DAT_CODE_0eaa,DAT_CODE_0ea9);
  bVar1 = FUN_CODE_8561(DAT_CODE_0ea8,DAT_CODE_0ea7,DAT_CODE_0ea6);
  FUN_CODE_85a7(DAT_CODE_0eac | bVar1);
  return;
}


// ===== FUN_CODE_0e63  [app]  callers: CODE:813c

void FUN_CODE_0e63(void)

{
  byte bVar1;
  
  bVar1 = FUN_CODE_8561(DAT_CODE_0ea8,DAT_CODE_0ea7,DAT_CODE_0ea6);
  FUN_CODE_85a7(~DAT_CODE_0eac & bVar1);
  FUN_CODE_85a7(DAT_CODE_0eac,DAT_CODE_0eab,DAT_CODE_0eaa,DAT_CODE_0ea9);
  return;
}


// ===== FUN_CODE_0ead  [app]  callers: CODE:0ec1

void FUN_CODE_0ead(void)

{
  DAT_INTMEM_84 = 0x22;
  DAT_INTMEM_28 = 0;
  return;
}


// ===== FUN_CODE_0eb5  [app]  callers: CODE:0ec1

void FUN_CODE_0eb5(void)

{
  DAT_INTMEM_26 = 0;
  DAT_INTMEM_27 = 0;
  DAT_INTMEM_40 = 0;
  DAT_INTMEM_41 = 0;
  DAT_INTMEM_29 = 0;
  return;
}


// ===== FUN_CODE_0ec1  [app]  callers: CODE:2200

void FUN_CODE_0ec1(void)

{
  FUN_CODE_6da3();
  FUN_CODE_806d();
  FUN_CODE_2137();
  FUN_CODE_0ead();
  FUN_CODE_0eb5();
  FUN_CODE_0c47();
  FUN_CODE_0ee3();
  DAT_EXTMEM_0907 = 0;
  FUN_CODE_21b2();
  FUN_CODE_7ac1(0x42);
  return;
}


// ===== FUN_CODE_0ee3  [app]  callers: CODE:0ec1

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


// ===== H_0F34  [app]  callers: 

void H_0F34(char param_1,char param_2)

{
  bool bVar1;
  char cVar2;
  byte bVar3;
  char in_PSW;
  
  BANK0_R4 = BANK0_R4 + '\x01';
  nop();
  cVar2 = ((DAT_EXTMEM_00f7 < (byte)-(in_PSW >> 7)) << 7) >> 7;
  bVar3 = DAT_EXTMEM_00f6 + cVar2;
  if ((byte)-cVar2 <= DAT_EXTMEM_00f6) {
    bVar1 = DAT_EXTMEM_00f7 != 0;
    DAT_EXTMEM_00f7 = DAT_EXTMEM_00f7 - 1;
    bVar3 = DAT_EXTMEM_00f6 + (-1 - ((bVar1 << 7) >> 7));
    DAT_EXTMEM_00f6 = bVar3;
  }
  FUN_CODE_6ee1(bVar3,param_1 + -2,param_2 + -1);
  return;
}


// ===== H_0F40  [app]  callers: 

void H_0F40(byte param_1,char param_2,char *param_3,char param_4)

{
  nop();
  nop();
  nop();
  FUN_CODE_0818((param_1 << 1 | param_1 >> 7) + *param_3 + param_2 + -3 + param_4,param_2 + -4);
  return;
}


// ===== H_0F72  [app]  callers: 

void H_0F72(char param_1)

{
  FUN_CODE_0815(param_1 + '\x01');
  return;
}


// ===== FUN_CODE_0f76  [app]  callers: CODE:2200

void FUN_CODE_0f76(void)

{
  return;
}


// ===== thunk_FUN_CODE_e003  [app]  callers: CODE:31ec

void thunk_FUN_CODE_e003(void)

{
  thunk_FUN_CODE_e003();
  return;
}


// ===== FUN_CODE_0f7f  [app]  callers: CODE:1353 CODE:13d4 CODE:1391 CODE:13fe CODE:1372 CODE:13b5

void FUN_CODE_0f7f(void)

{
  nop();
  nop();
  nop();
  nop();
  nop();
  nop();
  nop();
  nop();
  FUN_CODE_fe00();
  return;
}


// ===== FUN_CODE_0f8b  [app]  callers: CODE:7f65

undefined1 FUN_CODE_0f8b(char param_1,char param_2,char param_3,char param_4,char param_5)

{
  DAT_INTMEM_55 = param_4;
  DAT_INTMEM_56 = param_5;
  DAT_INTMEM_87 = param_1;
  DAT_INTMEM_88 = param_2;
  for (; param_3 != '\0'; param_3 = param_3 + -1) {
    *(undefined1 *)CONCAT11(DAT_INTMEM_87,DAT_INTMEM_88) =
         *(undefined1 *)CONCAT11(DAT_INTMEM_55,DAT_INTMEM_56);
    DAT_INTMEM_88 = DAT_INTMEM_88 + '\x01';
    if (DAT_INTMEM_88 == '\0') {
      DAT_INTMEM_87 = DAT_INTMEM_87 + '\x01';
    }
    DAT_INTMEM_56 = DAT_INTMEM_56 + '\x01';
    if (DAT_INTMEM_56 == '\0') {
      DAT_INTMEM_55 = DAT_INTMEM_55 + '\x01';
    }
  }
  return 0xff;
}


// ===== FUN_CODE_0fc9  [app]  callers: CODE:1353 CODE:13d4 CODE:1391 CODE:13fe CODE:1372 CODE:13b5

void FUN_CODE_0fc9(char param_1,char param_2)

{
  char cVar1;
  
  DAT_INTMEM_87 = '\x06';
  DAT_INTMEM_88 = '\0';
  cVar1 = '\0';
  DAT_INTMEM_55 = param_1;
  DAT_INTMEM_56 = param_2;
  do {
    *(undefined1 *)CONCAT11(DAT_INTMEM_87,DAT_INTMEM_88) =
         *(undefined1 *)CONCAT11(DAT_INTMEM_55,DAT_INTMEM_56);
    DAT_INTMEM_88 = DAT_INTMEM_88 + '\x01';
    if (DAT_INTMEM_88 == '\0') {
      DAT_INTMEM_87 = DAT_INTMEM_87 + '\x01';
    }
    DAT_INTMEM_56 = DAT_INTMEM_56 + '\x01';
    if (DAT_INTMEM_56 == '\0') {
      DAT_INTMEM_55 = DAT_INTMEM_55 + '\x01';
    }
    cVar1 = cVar1 + '\x01';
  } while (cVar1 != '\0');
  return;
}


// ===== H_100B  [app]  callers: 

void H_100B(undefined1 param_1,undefined1 *param_2)

{
  *param_2 = param_1;
  DAT_EXTMEM_103b = 0;
  DAT_EXTMEM_103c = 0xfd;
  DAT_EXTMEM_103f = 5;
  DAT_EXTMEM_0099 = 5;
  DAT_EXTMEM_103e = 0;
  DAT_EXTMEM_103d = 0;
  return;
}


// ===== H_10E6  [app]  callers: 

/* WARNING: Removing unreachable block (CODE,0x110d) */
/* WARNING: Removing unreachable block (CODE,0x1129) */
/* WARNING: Removing unreachable block (CODE,0x1145) */
/* WARNING: Removing unreachable block (CODE,0x115c) */
/* WARNING: Removing unreachable block (CODE,0x1163) */

void H_10E6(undefined1 param_1,undefined1 *param_2)

{
  *param_2 = param_1;
  do {
  } while( true );
}


// ===== H_1178  [app]  callers: 

/* WARNING: Removing unreachable block (CODE,0x119c) */
/* WARNING: Removing unreachable block (CODE,0x11e1) */
/* WARNING: Removing unreachable block (CODE,0x11eb) */

void H_1178(undefined1 param_1,undefined1 *param_2)

{
  *param_2 = param_1;
  do {
  } while( true );
}


// ===== H_1200  [app]  callers: 

/* WARNING: Removing unreachable block (CODE,0x1224) */
/* WARNING: Removing unreachable block (CODE,0x1252) */
/* WARNING: Removing unreachable block (CODE,0x125a) */

void H_1200(undefined1 param_1,undefined1 *param_2)

{
  *param_2 = param_1;
  do {
  } while( true );
}


// ===== FUN_CODE_1353  [app]  callers: CODE:7f40

void FUN_CODE_1353(void)

{
  FUN_CODE_059d();
  FUN_CODE_0fc9(0x11,0x6d);
  DAT_EXTMEM_1000 = DAT_EXTMEM_1000 | 0x80;
  FUN_CODE_0f7f();
  DAT_EXTMEM_1000 = DAT_EXTMEM_1000 & 0x7f;
  FUN_CODE_05a4();
  return;
}


// ===== FUN_CODE_1372  [app]  callers: CODE:7f30 CODE:7f40

void FUN_CODE_1372(void)

{
  FUN_CODE_059d();
  FUN_CODE_0fc9(0x11,0xf5);
  DAT_EXTMEM_1000 = DAT_EXTMEM_1000 | 0x80;
  FUN_CODE_0f7f();
  DAT_EXTMEM_1000 = DAT_EXTMEM_1000 & 0x7f;
  FUN_CODE_05a4();
  return;
}


// ===== FUN_CODE_1391  [app]  callers: CODE:7f30 CODE:7f40

void FUN_CODE_1391(undefined1 param_1)

{
  DAT_EXTMEM_009a = param_1;
  FUN_CODE_059d();
  FUN_CODE_0fc9(0x10,0x37);
  DAT_EXTMEM_1000 = DAT_EXTMEM_1000 | 0x80;
  FUN_CODE_0f7f();
  DAT_EXTMEM_1000 = DAT_EXTMEM_1000 & 0x7f;
  FUN_CODE_05a4();
  return;
}


// ===== H_13B5  [app]  callers: 

void H_13B5(void)

{
  FUN_CODE_059d();
  FUN_CODE_0fc9(0x10,0);
  DAT_EXTMEM_1000 = DAT_EXTMEM_1000 | 0x80;
  FUN_CODE_0f7f();
  DAT_EXTMEM_1000 = DAT_EXTMEM_1000 & 0x7f;
  FUN_CODE_05a4();
  return;
}


// ===== FUN_CODE_13d4  [app]  callers: CODE:7f40

void FUN_CODE_13d4(undefined1 param_1,undefined1 param_2,undefined1 param_3)

{
  DAT_EXTMEM_0095 = param_3;
  DAT_EXTMEM_0096 = param_2;
  DAT_EXTMEM_0097 = param_1;
  FUN_CODE_059d();
  FUN_CODE_0fc9(0x10,0xdb);
  DAT_EXTMEM_1000 = DAT_EXTMEM_1000 | 0x80;
  FUN_CODE_0f7f();
  DAT_EXTMEM_1000 = DAT_EXTMEM_1000 & 0x7f;
  FUN_CODE_05a4();
  return;
}


// ===== FUN_CODE_13fe  [app]  callers: CODE:7f40

void FUN_CODE_13fe(undefined1 param_1,undefined1 param_2,undefined1 param_3,undefined1 param_4)

{
  DAT_EXTMEM_0097 = DAT_EXTMEM_0786;
  DAT_EXTMEM_0095 = param_2;
  DAT_EXTMEM_0096 = param_1;
  DAT_EXTMEM_009b = param_3;
  DAT_EXTMEM_009c = param_4;
  FUN_CODE_059d();
  FUN_CODE_0fc9(0x12,100);
  DAT_EXTMEM_1000 = DAT_EXTMEM_1000 | 0x80;
  FUN_CODE_0f7f();
  DAT_EXTMEM_1000 = DAT_EXTMEM_1000 & 0x7f;
  FUN_CODE_05a4();
  return;
}


// ===== FUN_CODE_1435  [app]  callers: CODE:2260 CODE:813c

void FUN_CODE_1435(void)

{
  char *pcVar1;
  
  if ((DAT_EXTMEM_00ff >> 6 & 1) == 0) {
    if (DAT_EXTMEM_0020 == '\0') {
      DAT_INTMEM_68 = DAT_EXTMEM_074c >> 4 | (DAT_EXTMEM_074c & 7) << 4;
      pcVar1 = &DAT_EXTMEM_0027;
    }
    else {
      DAT_INTMEM_68 = (DAT_EXTMEM_074c >> 4) + (DAT_EXTMEM_074c & 7) * '\x03';
      pcVar1 = &DAT_EXTMEM_0029;
    }
    DAT_INTMEM_67 =
         *(undefined1 *)
          CONCAT11(*pcVar1 - ((CARRY1(pcVar1[1],DAT_INTMEM_68) << 7) >> 7),pcVar1[1] + DAT_INTMEM_68
                  );
    FUN_CODE_7940(DAT_EXTMEM_074d,DAT_EXTMEM_074c >> 4,DAT_EXTMEM_074c,DAT_EXTMEM_074c & 7);
    if ((DAT_EXTMEM_0811 & 1) == 1) {
      if ((((DAT_EXTMEM_074c & 7) == 3) && (DAT_EXTMEM_074c >> 4 == 1)) &&
         (DAT_EXTMEM_074d == '\x01')) {
        if ((DAT_EXTMEM_0816 >> 1 & 1) != 0) {
          FUN_CODE_19a7(1,0x82);
        }
        DAT_EXTMEM_0816 = DAT_EXTMEM_0816 & 0xfc;
        return;
      }
      if (((((DAT_EXTMEM_074c & 7) != 3) || (DAT_EXTMEM_074c >> 4 != 1)) &&
          ((DAT_EXTMEM_074d == '\0' && ((DAT_EXTMEM_0816 & 1) != 0)))) &&
         (((DAT_EXTMEM_074c & 7) != 2 || (DAT_EXTMEM_074c >> 4 != 2)))) {
        FUN_CODE_19a7(0,0x82);
        DAT_EXTMEM_0816 = DAT_EXTMEM_0816 & 0xfe | 2;
      }
      if (((((DAT_EXTMEM_074c & 7) == 3) && (DAT_EXTMEM_074c >> 4 == 1)) &&
          (DAT_EXTMEM_074d == '\0')) && ((DAT_EXTMEM_0816 & 1) != 1)) {
        DAT_EXTMEM_0816 = DAT_EXTMEM_0816 | 1;
        return;
      }
    }
    FUN_CODE_1841(DAT_EXTMEM_074d,DAT_INTMEM_67);
  }
  else if ((DAT_EXTMEM_00fc == -1) && (DAT_EXTMEM_074d == '\0')) {
    DAT_EXTMEM_00fa = DAT_EXTMEM_074c & 7;
    DAT_EXTMEM_00fb = DAT_EXTMEM_074c >> 4;
    if (DAT_EXTMEM_0020 != '\0') {
      DAT_EXTMEM_00fc = 0x44;
      return;
    }
    DAT_EXTMEM_00fc = 0x33;
    return;
  }
  return;
}


// ===== FUN_CODE_1577  [app]  callers: CODE:25bb

void FUN_CODE_1577(void)

{
  char cVar1;
  undefined1 *puVar2;
  
  cVar1 = '\x10';
  puVar2 = &DAT_EXTMEM_00e0;
  do {
    *puVar2 = 0;
    puVar2 = puVar2 + 1;
    cVar1 = cVar1 + -1;
  } while (cVar1 != '\0');
  return;
}


// ===== FUN_CODE_1582  [app]  callers: CODE:1841 CODE:19fc

undefined1 FUN_CODE_1582(char param_1,byte param_2)

{
  char cVar1;
  char cVar2;
  byte bVar3;
  undefined2 uStack_1;
  
  DAT_EXTMEM_0758 = 0;
  if (param_2 < 0x9c) {
    DAT_EXTMEM_0757 = param_1;
    DAT_EXTMEM_0758 = 0;
    return 0;
  }
  DAT_EXTMEM_0759 = param_2 + 0x70;
  cVar1 = '\x03';
  bVar3 = 0xff - (((0x8f < param_2) << 7) >> 7);
  do {
    DAT_EXTMEM_0759 = DAT_EXTMEM_0759 >> 1 | bVar3 << 7;
    cVar1 = cVar1 + -1;
    bVar3 = bVar3 >> 1;
  } while (cVar1 != '\0');
  DAT_EXTMEM_075a = param_2 + 0x70 & 7;
  DAT_EXTMEM_0757 = param_1;
  if (param_1 != '\x01') {
    if (((DAT_INTMEM_8c >> 6 & 1) != 0) && (param_1 == '\0')) {
      cVar1 = -(((0x1f < DAT_EXTMEM_0759) << 7) >> 7);
      uStack_1 = (byte *)CONCAT11(cVar1,DAT_EXTMEM_0759 - 0x20);
      bVar3 = 1;
      cVar2 = DAT_EXTMEM_075a + 1;
      while (cVar2 = cVar2 + -1, cVar2 != '\0') {
        bVar3 = bVar3 << 1;
      }
      *uStack_1 = bVar3 | *(byte *)CONCAT11(cVar1,DAT_EXTMEM_0759 - 0x20);
    }
    if ((DAT_INTMEM_8c >> 6 & 1) != 1) {
      bVar3 = 1;
      cVar1 = DAT_EXTMEM_075a + 1;
      while (cVar1 = cVar1 + -1, cVar1 != '\0') {
        bVar3 = bVar3 << 1;
      }
      if ((bVar3 & *(byte *)CONCAT11(-(((0x1f < DAT_EXTMEM_0759) << 7) >> 7),DAT_EXTMEM_0759 - 0x20)
          ) == 0) {
        return DAT_EXTMEM_0758;
      }
    }
    DAT_EXTMEM_0758 = 1;
    return 1;
  }
  if ((DAT_INTMEM_8c >> 6 & 1) == 0) {
    bVar3 = 1;
    cVar1 = DAT_EXTMEM_075a + 1;
    while (cVar1 = cVar1 + -1, cVar1 != '\0') {
      bVar3 = bVar3 << 1;
    }
    if ((bVar3 & *(byte *)CONCAT11(-(((0x1f < DAT_EXTMEM_0759) << 7) >> 7),DAT_EXTMEM_0759 - 0x20))
        == 0) {
      DAT_EXTMEM_0758 = 0;
      goto LAB_CODE_1637;
    }
  }
  else {
    bVar3 = 1;
    cVar1 = DAT_EXTMEM_075a + 1;
    while (cVar1 = cVar1 + -1, cVar1 != '\0') {
      bVar3 = bVar3 << 1;
    }
    if ((bVar3 & *(byte *)CONCAT11(-(((0x1f < DAT_EXTMEM_0759) << 7) >> 7),DAT_EXTMEM_0759 - 0x20))
        == 0) {
      DAT_EXTMEM_0758 = 0;
      goto LAB_CODE_1637;
    }
  }
  DAT_EXTMEM_0758 = 1;
LAB_CODE_1637:
  cVar1 = -(((0x1f < DAT_EXTMEM_0759) << 7) >> 7);
  uStack_1 = (byte *)CONCAT11(cVar1,DAT_EXTMEM_0759 - 0x20);
  bVar3 = 1;
  cVar2 = DAT_EXTMEM_075a + 1;
  while (cVar2 = cVar2 + -1, cVar2 != '\0') {
    bVar3 = bVar3 << 1;
  }
  *uStack_1 = ~bVar3 & *(byte *)CONCAT11(cVar1,DAT_EXTMEM_0759 - 0x20);
  return DAT_EXTMEM_0758;
}


// ===== FUN_CODE_16dc  [app]  callers: CODE:25bb

void FUN_CODE_16dc(void)

{
  char cVar1;
  undefined1 *puVar2;
  
  cVar1 = '\x10';
  puVar2 = &DAT_EXTMEM_00b0;
  do {
    *puVar2 = 0;
    puVar2 = puVar2 + 1;
    cVar1 = cVar1 + -1;
  } while (cVar1 != '\0');
  return;
}


// ===== FUN_CODE_16e7  [app]  callers: CODE:19fc

undefined1 FUN_CODE_16e7(char param_1,byte param_2)

{
  char cVar1;
  char cVar2;
  byte bVar3;
  undefined2 uStack_1;
  
  DAT_EXTMEM_0758 = 0;
  if (param_2 < 0x9c) {
    DAT_EXTMEM_0757 = param_1;
    DAT_EXTMEM_0758 = 0;
    return 0;
  }
  DAT_EXTMEM_0759 = param_2 + 0x70;
  cVar1 = '\x03';
  bVar3 = 0xff - (((0x8f < param_2) << 7) >> 7);
  do {
    DAT_EXTMEM_0759 = DAT_EXTMEM_0759 >> 1 | bVar3 << 7;
    cVar1 = cVar1 + -1;
    bVar3 = bVar3 >> 1;
  } while (cVar1 != '\0');
  DAT_EXTMEM_075a = param_2 + 0x70 & 7;
  DAT_EXTMEM_0757 = param_1;
  if (param_1 != '\x01') {
    if (((DAT_INTMEM_8c & 1) != 0) && (param_1 == '\0')) {
      cVar1 = -(((0x4f < DAT_EXTMEM_0759) << 7) >> 7);
      uStack_1 = (byte *)CONCAT11(cVar1,DAT_EXTMEM_0759 + 0xb0);
      bVar3 = 1;
      cVar2 = DAT_EXTMEM_075a + 1;
      while (cVar2 = cVar2 + -1, cVar2 != '\0') {
        bVar3 = bVar3 << 1;
      }
      *uStack_1 = bVar3 | *(byte *)CONCAT11(cVar1,DAT_EXTMEM_0759 + 0xb0);
    }
    if ((DAT_INTMEM_8c & 1) != 1) {
      bVar3 = 1;
      cVar1 = DAT_EXTMEM_075a + 1;
      while (cVar1 = cVar1 + -1, cVar1 != '\0') {
        bVar3 = bVar3 << 1;
      }
      if ((bVar3 & *(byte *)CONCAT11(-(((0x4f < DAT_EXTMEM_0759) << 7) >> 7),DAT_EXTMEM_0759 + 0xb0)
          ) == 0) {
        return DAT_EXTMEM_0758;
      }
    }
    DAT_EXTMEM_0758 = 1;
    return 1;
  }
  if ((DAT_INTMEM_8c & 1) == 0) {
    bVar3 = 1;
    cVar1 = DAT_EXTMEM_075a + 1;
    while (cVar1 = cVar1 + -1, cVar1 != '\0') {
      bVar3 = bVar3 << 1;
    }
    if ((bVar3 & *(byte *)CONCAT11(-(((0x4f < DAT_EXTMEM_0759) << 7) >> 7),DAT_EXTMEM_0759 + 0xb0))
        == 0) {
      DAT_EXTMEM_0758 = 0;
      goto LAB_CODE_179c;
    }
  }
  else {
    bVar3 = 1;
    cVar1 = DAT_EXTMEM_075a + 1;
    while (cVar1 = cVar1 + -1, cVar1 != '\0') {
      bVar3 = bVar3 << 1;
    }
    if ((bVar3 & *(byte *)CONCAT11(-(((0x4f < DAT_EXTMEM_0759) << 7) >> 7),DAT_EXTMEM_0759 + 0xb0))
        == 0) {
      DAT_EXTMEM_0758 = 0;
      goto LAB_CODE_179c;
    }
  }
  DAT_EXTMEM_0758 = 1;
LAB_CODE_179c:
  cVar1 = -(((0x4f < DAT_EXTMEM_0759) << 7) >> 7);
  uStack_1 = (byte *)CONCAT11(cVar1,DAT_EXTMEM_0759 + 0xb0);
  bVar3 = 1;
  cVar2 = DAT_EXTMEM_075a + 1;
  while (cVar2 = cVar2 + -1, cVar2 != '\0') {
    bVar3 = bVar3 << 1;
  }
  *uStack_1 = ~bVar3 & *(byte *)CONCAT11(cVar1,DAT_EXTMEM_0759 + 0xb0);
  return DAT_EXTMEM_0758;
}


// ===== FUN_CODE_1841  [app]  callers: CODE:1435

void FUN_CODE_1841(char param_1,byte param_2)

{
  bool bVar1;
  byte bVar2;
  undefined *puVar3;
  char *pcVar4;
  
  DAT_EXTMEM_074e = param_2;
  DAT_EXTMEM_074f = param_1;
  FUN_CODE_76f5(0x4e,7,1);
  FUN_CODE_793d();
  if (param_2 == 0xff) {
    return;
  }
  DAT_EXTMEM_0753 = DAT_EXTMEM_074e;
  FUN_CODE_1f8c();
  DAT_INTMEM_8c = DAT_INTMEM_29;
  if ((DAT_EXTMEM_074e < 0xe0) << 7 < '\0') {
    if (DAT_EXTMEM_074e < 0x9c) goto LAB_CODE_1910;
    DAT_EXTMEM_0750 = DAT_EXTMEM_074e + 100;
    bVar2 = (byte)((ushort)DAT_EXTMEM_0750 * 3);
    DAT_EXTMEM_074e =
         *(byte *)CONCAT11((char)((ushort)DAT_EXTMEM_0750 * 3 >> 8) +
                           ('}' - (((0x76 < bVar2) << 7) >> 7)),bVar2 + 0x89);
    bVar2 = (byte)((ushort)DAT_EXTMEM_0750 * 3);
    pcVar4 = (char *)CONCAT11((char)((ushort)DAT_EXTMEM_0750 * 3 >> 8) +
                              ('}' - (((0x75 < bVar2) << 7) >> 7)),bVar2 + 0x8a);
    DAT_EXTMEM_0751 = *pcVar4;
    DAT_EXTMEM_0752 = pcVar4[1];
    FUN_CODE_19fc(DAT_EXTMEM_074f,DAT_EXTMEM_0753);
    bVar1 = CARRY1(DAT_EXTMEM_0752,DAT_EXTMEM_074e);
    DAT_EXTMEM_0752 = DAT_EXTMEM_0752 + DAT_EXTMEM_074e;
    DAT_EXTMEM_0751 = DAT_EXTMEM_0751 - ((bVar1 << 7) >> 7);
    puVar3 = (undefined *)CONCAT11(DAT_EXTMEM_0751,DAT_EXTMEM_0752);
    bVar2 = 0;
  }
  else {
    DAT_EXTMEM_0750 = (DAT_EXTMEM_074e + 0x20) * '\x02';
    bVar2 = DAT_EXTMEM_0753;
    FUN_CODE_1582(DAT_EXTMEM_074f);
    if (bVar2 == 1) {
      DAT_EXTMEM_0750 = DAT_EXTMEM_0750 + 1;
    }
    puVar3 = &DAT_CODE_7dfb;
    bVar2 = DAT_EXTMEM_0750;
  }
  DAT_EXTMEM_074e = puVar3[bVar2];
LAB_CODE_1910:
  FUN_CODE_192c(DAT_EXTMEM_074f,DAT_EXTMEM_074e);
  if (DAT_EXTMEM_074f == '\x01') {
    FUN_CODE_7a31();
  }
  DAT_INTMEM_29 = DAT_INTMEM_8c;
  return;
}


// ===== FUN_CODE_192c  [app]  callers: CODE:1841

void FUN_CODE_192c(char param_1,byte param_2)

{
  if ((param_2 == 0x82) && (param_1 == '\0')) {
    DAT_EXTMEM_0816 = DAT_EXTMEM_0816 | 4;
  }
  else if ((param_2 == 0x82) && (param_1 == '\x01')) {
    DAT_EXTMEM_0816 = DAT_EXTMEM_0816 & 0xfb;
  }
  DAT_EXTMEM_0754 = param_2;
  DAT_EXTMEM_0755 = param_1;
  if (param_2 != 0) {
    if (-1 < (char)param_2) {
      FUN_CODE_1b56(param_1);
      return;
    }
    DAT_EXTMEM_0754 = param_2 * '\x02';
    FUN_CODE_8961(*(undefined2 *)
                   (CONCAT11('\x1f' - (((0xe6U < (byte)((&DAT_CODE_7e3c)[DAT_EXTMEM_0754] * '\x03'))
                                       << 7) >> 7),(&DAT_CODE_7e3c)[DAT_EXTMEM_0754] * '\x03' + 0x19
                            ) + 1),param_1,(&DAT_CODE_7e3b)[DAT_EXTMEM_0754]);
  }
  return;
}


// ===== FUN_CODE_19a7  [app]  callers: CODE:1435

void FUN_CODE_19a7(undefined1 param_1,byte param_2)

{
  DAT_EXTMEM_074e = param_2;
  DAT_EXTMEM_074f = param_1;
  if (param_2 != 0) {
    if (-1 < (char)param_2) {
      FUN_CODE_1b56(param_1,param_2);
      return;
    }
    DAT_EXTMEM_074e = param_2 * '\x02';
    FUN_CODE_8961(*(undefined2 *)
                   (CONCAT11('\x1f' - (((0xe6U < (byte)((&DAT_CODE_7e3c)[DAT_EXTMEM_074e] * '\x03'))
                                       << 7) >> 7),(&DAT_CODE_7e3c)[DAT_EXTMEM_074e] * '\x03' + 0x19
                            ) + 1),param_1,(&DAT_CODE_7e3b)[DAT_EXTMEM_074e]);
  }
  return;
}


// ===== FUN_CODE_19fc  [app]  callers: CODE:1841

byte FUN_CODE_19fc(undefined1 param_1,byte param_2,byte param_3,byte param_4)

{
  char cVar1;
  byte bVar2;
  byte bVar3;
  
  DAT_EXTMEM_0755 = 0;
  DAT_EXTMEM_0756 = 0;
  if ((param_4 >> 1 & 1) != 0) {
    param_3 = DAT_INTMEM_8c;
    if ((DAT_INTMEM_8c >> 1 & 1) != 0 || (DAT_INTMEM_8c >> 2 & 1) != 0) {
      param_3 = 0;
      DAT_EXTMEM_0755 = 1;
      cVar1 = '\x01';
      while (cVar1 = cVar1 + -1, cVar1 != '\0') {
        DAT_EXTMEM_0755 = DAT_EXTMEM_0755 << 1;
      }
    }
    DAT_EXTMEM_0756 = 1;
  }
  if ((param_4 >> 2 & 1) != 0) {
    if ((DAT_INTMEM_8c >> 3 & 1) != 0) {
      bVar2 = 1;
      cVar1 = DAT_EXTMEM_0756 + 1;
      while (cVar1 = cVar1 + -1, cVar1 != '\0') {
        bVar2 = bVar2 << 1;
      }
      param_3 = DAT_EXTMEM_0755;
      DAT_EXTMEM_0755 = bVar2 | DAT_EXTMEM_0755;
    }
    DAT_EXTMEM_0756 = DAT_EXTMEM_0756 + 1;
  }
  bVar2 = param_4;
  if ((param_4 >> 3 & 1) != 0) {
    if ((DAT_INTMEM_8c >> 4 & 1) != 0) {
      bVar3 = 1;
      cVar1 = DAT_EXTMEM_0756 + 1;
      while (cVar1 = cVar1 + -1, cVar1 != '\0') {
        bVar3 = bVar3 << 1;
      }
      param_3 = DAT_EXTMEM_0756;
      bVar2 = DAT_EXTMEM_0755;
      DAT_EXTMEM_0755 = bVar3 | DAT_EXTMEM_0755;
    }
    DAT_EXTMEM_0756 = DAT_EXTMEM_0756 + 1;
  }
  DAT_EXTMEM_0754 = param_4;
  if ((param_4 >> 4 & 1) != 0) {
    bVar2 = param_2;
    FUN_CODE_16e7(param_4,param_1,param_3);
    if (bVar2 == 1) {
      bVar3 = 1;
      cVar1 = DAT_EXTMEM_0756 + 1;
      while (cVar1 = cVar1 + -1, cVar1 != '\0') {
        bVar3 = bVar3 << 1;
      }
      bVar2 = DAT_EXTMEM_0755;
      DAT_EXTMEM_0755 = bVar3 | DAT_EXTMEM_0755;
    }
    DAT_EXTMEM_0756 = DAT_EXTMEM_0756 + 1;
  }
  if ((DAT_EXTMEM_0754 >> 5 & 1) != 0) {
    FUN_CODE_1582(DAT_EXTMEM_0754,param_1);
    if (param_2 == 1) {
      bVar2 = 1;
      cVar1 = DAT_EXTMEM_0756 + 1;
      while (cVar1 = cVar1 + -1, cVar1 != '\0') {
        bVar2 = bVar2 << 1;
      }
      param_2 = DAT_EXTMEM_0755;
      DAT_EXTMEM_0755 = bVar2 | DAT_EXTMEM_0755;
    }
    DAT_EXTMEM_0756 = DAT_EXTMEM_0756 + 1;
    bVar2 = param_2;
  }
  if ((DAT_EXTMEM_0754 >> 6 & 1) != 0) {
    FUN_CODE_7a32();
    if (bVar2 == 0xff) {
      bVar3 = 1;
      cVar1 = DAT_EXTMEM_0756 + 1;
      while (cVar1 = cVar1 + -1, cVar1 != '\0') {
        bVar3 = bVar3 << 1;
      }
      bVar2 = DAT_EXTMEM_0755;
      DAT_EXTMEM_0755 = bVar3 | DAT_EXTMEM_0755;
    }
    DAT_EXTMEM_0756 = DAT_EXTMEM_0756 + 1;
  }
  if ((char)DAT_EXTMEM_0754 < '\0') {
    FUN_CODE_7a35();
    if (bVar2 == 0xff) {
      bVar2 = 1;
      cVar1 = DAT_EXTMEM_0756 + 1;
      while (cVar1 = cVar1 + -1, cVar1 != '\0') {
        bVar2 = bVar2 << 1;
      }
      DAT_EXTMEM_0755 = bVar2 | DAT_EXTMEM_0755;
    }
    DAT_EXTMEM_0756 = DAT_EXTMEM_0756 + 1;
  }
  return DAT_EXTMEM_0755;
}


// ===== FUN_CODE_1b56  [app]  callers: CODE:76f5 CODE:19a7 CODE:7a38 CODE:192c CODE:1db2 CODE:6f32 CODE:79bd

void FUN_CODE_1b56(char param_1,char param_2)

{
  DAT_EXTMEM_0790 = param_2;
  DAT_EXTMEM_0791 = param_1;
  FUN_CODE_21f9();
  if ((param_2 == '\0') || (DAT_EXTMEM_0791 != '\x02')) {
    if (DAT_EXTMEM_0791 == '\x01') {
      FUN_CODE_1f93(0xf0);
    }
    FUN_CODE_1f93(DAT_EXTMEM_0790);
  }
  return;
}


// ===== FUN_CODE_1b81  [app]  callers: CODE:1bd4

void FUN_CODE_1b81(char param_1)

{
  DAT_EXTMEM_0793 = param_1;
  FUN_CODE_21f9();
  if (param_1 != '\0') {
    return;
  }
  if ((((((DAT_EXTMEM_0793 != 'p') && (DAT_EXTMEM_0793 != 'q')) && (DAT_EXTMEM_0793 != 'k')) &&
       ((DAT_EXTMEM_0793 != 'l' && (DAT_EXTMEM_0793 != 'i')))) &&
      ((DAT_EXTMEM_0793 != 'u' && ((DAT_EXTMEM_0793 != 'r' && (DAT_EXTMEM_0793 != '}')))))) &&
     ((DAT_EXTMEM_0793 != 'z' && (DAT_EXTMEM_0793 != 't')))) {
    if (DAT_EXTMEM_0793 == 'J') {
      return;
    }
    return;
  }
  return;
}


// ===== H_1B91  [app]  callers: 

void H_1B91(char param_1,char param_2)

{
  if ((((((param_1 != 'p') && (param_2 != 'q')) && (param_2 != 'k')) &&
       ((param_2 != 'l' && (param_2 != 'i')))) &&
      ((param_2 != 'u' && ((param_2 != 'r' && (param_2 != '}')))))) &&
     ((param_2 != 'z' && (param_2 != 't')))) {
    if (DAT_EXTMEM_0793 == 'J') {
      return;
    }
    return;
  }
  return;
}


// ===== FUN_CODE_1bd4  [app]  callers: CODE:1db2 CODE:79bd

void FUN_CODE_1bd4(char param_1,char param_2)

{
  undefined1 uVar1;
  
  DAT_EXTMEM_0790 = param_2;
  DAT_EXTMEM_0791 = param_1;
  FUN_CODE_1b81();
  DAT_EXTMEM_0792 = param_2;
  if ((DAT_EXTMEM_0791 != '\x01') &&
     ((FUN_CODE_21f9(), param_2 == '\0' || (DAT_EXTMEM_0791 != '\x02')))) {
    if (DAT_EXTMEM_0792 == '\x01') {
      if (_9_0 == '\0') {
        if ((_9_1 == '\0') || (_9_2 == '\0')) {
          if (_9_1 != '\0') {
            FUN_CODE_1f93(0xe0);
            uVar1 = 0xf0;
            goto LAB_CODE_1c56;
          }
          if (_9_2 == '\0') goto LAB_CODE_1c6f;
        }
        else {
LAB_CODE_1c3b:
          FUN_CODE_1f93(0xe0);
          FUN_CODE_1f93(0xf0);
          FUN_CODE_1f93(0x12);
        }
LAB_CODE_1c60:
        FUN_CODE_1f93(0xe0);
        FUN_CODE_1f93(0xf0);
        param_2 = 'Y';
      }
      else {
        if ((_9_1 == '\x01') || (_9_2 == '\x01')) goto LAB_CODE_1c6f;
        uVar1 = 0xe0;
LAB_CODE_1c56:
        FUN_CODE_1f93(uVar1);
        param_2 = '\x12';
      }
      FUN_CODE_1f93();
    }
    else if (DAT_EXTMEM_0792 == '\x02') {
      if ((_9_1 != '\0') && (_9_2 != '\0')) goto LAB_CODE_1c3b;
      if (_9_1 != '\0') {
        FUN_CODE_1f93(0xe0);
        uVar1 = 0xf0;
        goto LAB_CODE_1c56;
      }
      if (_9_2 != '\0') goto LAB_CODE_1c60;
    }
  }
LAB_CODE_1c6f:
  FUN_CODE_21f9();
  if ((param_2 == '\0') || (DAT_EXTMEM_0791 != '\x02')) {
    FUN_CODE_1f93(0xe0);
    if (DAT_EXTMEM_0791 == '\x01') {
      FUN_CODE_1f93(0xf0);
    }
    FUN_CODE_1f93(DAT_EXTMEM_0790);
  }
  if (DAT_EXTMEM_0791 != '\x01') {
    return;
  }
  if (DAT_EXTMEM_0792 == '\x01') {
    if (_9_0 == '\0') {
      if ((_9_1 == '\0') || (_9_2 == '\0')) {
        if (_9_1 == '\0') goto joined_c0x1cfe;
        uVar1 = 0xe0;
      }
      else {
        FUN_CODE_1f93(0xe0);
        FUN_CODE_1f93(0x59);
        uVar1 = 0xe0;
      }
    }
    else {
      if (_9_1 == '\x01') {
        return;
      }
      if (_9_2 == '\x01') {
        return;
      }
      FUN_CODE_1f93(0xe0);
      uVar1 = 0xf0;
    }
  }
  else {
    if (DAT_EXTMEM_0792 != '\x02') {
      return;
    }
    if ((_9_1 == '\0') || (_9_2 == '\0')) {
      if (_9_1 == '\0') {
joined_c0x1cfe:
        if (_9_2 == '\0') {
          return;
        }
        FUN_CODE_1f93(0xe0);
        uVar1 = 0x59;
        goto LAB_CODE_1d08;
      }
      uVar1 = 0xe0;
    }
    else {
      FUN_CODE_1f93(0xe0);
      FUN_CODE_1f93(0x59);
      uVar1 = 0xe0;
    }
  }
  FUN_CODE_1f93(uVar1);
  uVar1 = 0x12;
LAB_CODE_1d08:
  FUN_CODE_1f93(uVar1);
  return;
}


// ===== FUN_CODE_1c00  [app]  callers: 

void FUN_CODE_1c00(byte param_1,char *param_2,char param_3)

{
  undefined1 uVar1;
  byte in_PSW;
  
  *param_2 = *param_2 + '\x01';
  if ((param_1 & 0xfe | in_PSW >> 7) == 1) {
    if (_9_0 == '\0') {
      if ((_9_1 == '\0') || (_9_2 == '\0')) {
        if (_9_1 != '\0') {
          FUN_CODE_1f93(0xe0);
          uVar1 = 0xf0;
          goto LAB_CODE_1c56;
        }
        if (_9_2 == '\0') goto LAB_CODE_1c6f;
      }
      else {
LAB_CODE_1c3b:
        FUN_CODE_1f93(0xe0);
        FUN_CODE_1f93(0xf0);
        FUN_CODE_1f93(0x12);
      }
LAB_CODE_1c60:
      FUN_CODE_1f93(0xe0);
      FUN_CODE_1f93(0xf0);
      param_3 = 'Y';
    }
    else {
      if ((_9_1 == '\x01') || (_9_2 == '\x01')) goto LAB_CODE_1c6f;
      uVar1 = 0xe0;
LAB_CODE_1c56:
      FUN_CODE_1f93(uVar1);
      param_3 = '\x12';
    }
    FUN_CODE_1f93();
  }
  else if (DAT_EXTMEM_0792 == '\x02') {
    if ((_9_1 != '\0') && (_9_2 != '\0')) goto LAB_CODE_1c3b;
    if (_9_1 != '\0') {
      FUN_CODE_1f93(0xe0);
      uVar1 = 0xf0;
      goto LAB_CODE_1c56;
    }
    if (_9_2 != '\0') goto LAB_CODE_1c60;
  }
LAB_CODE_1c6f:
  FUN_CODE_21f9();
  if ((param_3 == '\0') || (DAT_EXTMEM_0791 != '\x02')) {
    FUN_CODE_1f93(0xe0);
    if (DAT_EXTMEM_0791 == '\x01') {
      FUN_CODE_1f93(0xf0);
    }
    FUN_CODE_1f93(DAT_EXTMEM_0790);
  }
  if (DAT_EXTMEM_0791 != '\x01') {
    return;
  }
  if (DAT_EXTMEM_0792 == '\x01') {
    if (_9_0 == '\0') {
      if ((_9_1 == '\0') || (_9_2 == '\0')) {
        if (_9_1 == '\0') goto joined_c0x1cfe;
        uVar1 = 0xe0;
      }
      else {
        FUN_CODE_1f93(0xe0);
        FUN_CODE_1f93(0x59);
        uVar1 = 0xe0;
      }
    }
    else {
      if (_9_1 == '\x01') {
        return;
      }
      if (_9_2 == '\x01') {
        return;
      }
      FUN_CODE_1f93(0xe0);
      uVar1 = 0xf0;
    }
  }
  else {
    if (DAT_EXTMEM_0792 != '\x02') {
      return;
    }
    if ((_9_1 == '\0') || (_9_2 == '\0')) {
      if (_9_1 == '\0') {
joined_c0x1cfe:
        if (_9_2 == '\0') {
          return;
        }
        FUN_CODE_1f93(0xe0);
        uVar1 = 0x59;
        goto LAB_CODE_1d08;
      }
      uVar1 = 0xe0;
    }
    else {
      FUN_CODE_1f93(0xe0);
      FUN_CODE_1f93(0x59);
      uVar1 = 0xe0;
    }
  }
  FUN_CODE_1f93(uVar1);
  uVar1 = 0x12;
LAB_CODE_1d08:
  FUN_CODE_1f93(uVar1);
  return;
}


// ===== FUN_CODE_1c14  [app]  callers: 

void FUN_CODE_1c14(char param_1)

{
  undefined1 uVar1;
  
  if ((_9_1 == '\0') || (_9_2 == '\0')) {
    if (_9_1 != '\0') {
      FUN_CODE_1f93(0xe0);
      FUN_CODE_1f93(0xf0);
      param_1 = '\x12';
      goto LAB_CODE_1c6c;
    }
    if (_9_2 != '\0') goto LAB_CODE_1c60;
  }
  else {
    FUN_CODE_1f93(0xe0);
    FUN_CODE_1f93(0xf0);
    FUN_CODE_1f93(0x12);
LAB_CODE_1c60:
    FUN_CODE_1f93(0xe0);
    FUN_CODE_1f93(0xf0);
    param_1 = 'Y';
LAB_CODE_1c6c:
    FUN_CODE_1f93();
  }
  FUN_CODE_21f9();
  if ((param_1 == '\0') || (DAT_EXTMEM_0791 != '\x02')) {
    FUN_CODE_1f93(0xe0);
    if (DAT_EXTMEM_0791 == '\x01') {
      FUN_CODE_1f93(0xf0);
    }
    FUN_CODE_1f93(DAT_EXTMEM_0790);
  }
  if (DAT_EXTMEM_0791 != '\x01') {
    return;
  }
  if (DAT_EXTMEM_0792 == '\x01') {
    if (_9_0 == '\0') {
      if ((_9_1 == '\0') || (_9_2 == '\0')) {
        if (_9_1 == '\0') goto joined_c0x1cfe;
        uVar1 = 0xe0;
      }
      else {
        FUN_CODE_1f93(0xe0);
        FUN_CODE_1f93(0x59);
        uVar1 = 0xe0;
      }
    }
    else {
      if (_9_1 == '\x01') {
        return;
      }
      if (_9_2 == '\x01') {
        return;
      }
      FUN_CODE_1f93(0xe0);
      uVar1 = 0xf0;
    }
  }
  else {
    if (DAT_EXTMEM_0792 != '\x02') {
      return;
    }
    if ((_9_1 == '\0') || (_9_2 == '\0')) {
      if (_9_1 == '\0') {
joined_c0x1cfe:
        if (_9_2 == '\0') {
          return;
        }
        FUN_CODE_1f93(0xe0);
        uVar1 = 0x59;
        goto LAB_CODE_1d08;
      }
      uVar1 = 0xe0;
    }
    else {
      FUN_CODE_1f93(0xe0);
      FUN_CODE_1f93(0x59);
      uVar1 = 0xe0;
    }
  }
  FUN_CODE_1f93(uVar1);
  uVar1 = 0x12;
LAB_CODE_1d08:
  FUN_CODE_1f93(uVar1);
  return;
}


// ===== H_1D0C  [app]  callers: 

void H_1D0C(char param_1,char param_2)

{
  undefined1 uVar1;
  
  if (param_2 == 'M') {
    uVar1 = 0xb5;
  }
  else if (param_2 == '\x15') {
    uVar1 = 0xb6;
  }
  else if (param_2 == ';') {
    uVar1 = 0xb7;
  }
  else {
    if (param_2 != '4') {
      DAT_EXTMEM_0756 = param_2;
      DAT_EXTMEM_0757 = param_1;
      return;
    }
    uVar1 = 0xcd;
  }
  DAT_EXTMEM_0756 = param_2;
  DAT_EXTMEM_0757 = param_1;
  FUN_CODE_2d4a(param_1 == '\x01',0,uVar1);
  return;
}


// ===== H_1DB2  [app]  callers: 

void H_1DB2(char param_1,char param_2)

{
  undefined1 uVar1;
  
  DAT_EXTMEM_0756 = param_2;
  DAT_EXTMEM_0757 = param_1;
  if (param_2 != '\x02') {
    if (param_1 == '\0') {
      if ((_9_4 == '\x01') || (param_2 != '\0')) {
        uVar1 = 0x45;
      }
      else {
        uVar1 = 0x3c;
      }
      FUN_CODE_1fea(uVar1,0x1f,0xff);
    }
    return;
  }
  FUN_CODE_21f9();
  if (param_2 == '\0') {
    if (_9_3 != '\0') {
      FUN_CODE_1b56(DAT_EXTMEM_0757,0x84);
      return;
    }
    if (((_9_4 != '\x01') && (_9_1 != '\x01')) && (_9_2 == '\0')) {
      if (DAT_EXTMEM_0757 == '\x01') {
        FUN_CODE_1bd4(1,0x7c);
        uVar1 = 0x12;
      }
      else {
        FUN_CODE_1bd4(DAT_EXTMEM_0757,0x12);
        uVar1 = 0x7c;
      }
      goto LAB_CODE_1e0e;
    }
  }
  uVar1 = 0x7c;
LAB_CODE_1e0e:
  FUN_CODE_1bd4(DAT_EXTMEM_0757,uVar1);
  return;
}


// ===== H_1E32  [app]  callers: 

void H_1E32(undefined1 param_1,byte param_2)

{
  byte bVar1;
  
  bVar1 = (byte)((ushort)param_2 * 3);
  FUN_CODE_8961(*(undefined2 *)
                 (CONCAT11((char)((ushort)param_2 * 3 >> 8) + ('|' - (((0x4e < bVar1) << 7) >> 7)),
                           bVar1 + 0xb1) + 1),param_1);
  return;
}


// ===== H_1F00  [app]  callers: 

void H_1F00(char param_1,char param_2)

{
  if (param_1 == '\0') {
    DAT_INTMEM_8c = DAT_EXTMEM_0756 | DAT_INTMEM_8c;
    return;
  }
  if (param_2 == '\x01') {
    DAT_INTMEM_8c = ~DAT_EXTMEM_0756 & DAT_INTMEM_8c;
  }
  return;
}


// ===== H_1F2F  [app]  callers: 

void H_1F2F(void)

{
  return;
}


// ===== FUN_CODE_1f4e  [app]  callers: CODE:2db4

char FUN_CODE_1f4e(void)

{
  byte bVar1;
  char cVar2;
  
  cVar2 = ((DAT_EXTMEM_00f7 == '\0') << 7) >> 7;
  if ((byte)-cVar2 <= DAT_EXTMEM_00f6) {
    return DAT_EXTMEM_00f6 + cVar2;
  }
  if (DAT_INTMEM_30 == DAT_INTMEM_31) {
    cVar2 = '\0';
  }
  else {
    bVar1 = DAT_INTMEM_30 + 1;
    cVar2 = DAT_INTMEM_30 + 0x81;
    DAT_INTMEM_30 = bVar1;
    if (0x7f < bVar1) {
      DAT_INTMEM_30 = 0;
    }
  }
  return cVar2;
}


// ===== FUN_CODE_1f8c  [app]  callers: CODE:1841

void FUN_CODE_1f8c(void)

{
  DAT_INTMEM_32 = DAT_INTMEM_31;
  return;
}


// ===== FUN_CODE_1f93  [app]  callers: CODE:1fea CODE:1c14 CODE:1b56 CODE:79bd

undefined1 FUN_CODE_1f93(undefined1 param_1)

{
  DAT_EXTMEM_0794 = 1;
  DAT_EXTMEM_0793 = param_1;
  if (DAT_EXTMEM_08ad != '\0') {
    FUN_CODE_4f75();
  }
  *(undefined1 *)CONCAT11(4,DAT_INTMEM_31) = DAT_EXTMEM_0793;
  DAT_INTMEM_31 = DAT_INTMEM_31 + 1;
  if (0x7f < DAT_INTMEM_31) {
    DAT_INTMEM_31 = 0;
  }
  if (DAT_INTMEM_31 == DAT_INTMEM_30) {
    DAT_INTMEM_31 = DAT_INTMEM_32;
    *(undefined1 *)CONCAT11(4,DAT_INTMEM_32) = 0;
    DAT_EXTMEM_0794 = 0;
  }
  return DAT_EXTMEM_0794;
}


// ===== FUN_CODE_1fea  [app]  callers: CODE:1db2

char FUN_CODE_1fea(undefined1 param_1,undefined1 param_2,undefined1 param_3)

{
  undefined1 uVar1;
  char cVar2;
  undefined1 uVar3;
  
  DAT_EXTMEM_075b = '\0';
  DAT_EXTMEM_0758 = param_3;
  DAT_EXTMEM_0759 = param_2;
  DAT_EXTMEM_075a = param_1;
  while( true ) {
    cVar2 = FUN_CODE_8561(DAT_EXTMEM_075a,DAT_EXTMEM_0759,DAT_EXTMEM_0758);
    if ((cVar2 == '\0') || (DAT_EXTMEM_075b != '\0')) break;
    uVar1 = 1;
    uVar3 = FUN_CODE_85f1(0,0x759,1);
    cVar2 = FUN_CODE_8561(uVar1,uVar3);
    FUN_CODE_1f93();
    if (cVar2 == '\0') {
      DAT_EXTMEM_075b = -0x80;
    }
  }
  return DAT_EXTMEM_075b;
}


// ===== H_2056  [app]  callers: 

undefined1 H_2056(char param_1,byte param_2,byte param_3)

{
  bool bVar1;
  byte bVar2;
  byte bVar3;
  
  if (param_1 == '\0') {
    DAT_EXTMEM_0485 = '\x01';
  }
  if (DAT_EXTMEM_0485 == '\0') {
    DAT_EXTMEM_0486 =
         ~*(byte *)CONCAT11(DAT_EXTMEM_0488 - ((CARRY1(DAT_EXTMEM_0489,param_2) << 7) >> 7),
                            DAT_EXTMEM_0489 + param_2) | param_3;
    if (DAT_EXTMEM_0486 == 0) {
      DAT_EXTMEM_0485 = '\x01';
    }
  }
  while (DAT_EXTMEM_0485 == '\0') {
    param_2 = param_2 + 1;
    if ((0xef < DAT_EXTMEM_0081 ^ 0x80U) - (((param_2 < DAT_EXTMEM_0081 + 0x10) << 7) >> 7) < 0x81)
    {
      param_2 = 0;
    }
    if (DAT_EXTMEM_0487 == param_2) {
      DAT_EXTMEM_0485 = '\x01';
    }
    if (DAT_EXTMEM_0485 == '\0') {
      bVar2 = ~*(byte *)CONCAT11(DAT_EXTMEM_0488 - ((CARRY1(DAT_EXTMEM_0489,param_2) << 7) >> 7),
                                 DAT_EXTMEM_0489 + param_2);
      bVar3 = 0;
      if (bVar2 != 0) {
        bVar3 = DAT_EXTMEM_0486 & bVar2;
      }
      if (bVar3 != 0) {
        if (DAT_EXTMEM_0483 != bVar3) {
          DAT_EXTMEM_0484 = 1;
          DAT_EXTMEM_0485 = '\x01';
        }
        if (DAT_EXTMEM_0485 == '\0') {
          bVar1 = false;
          bVar3 = DAT_EXTMEM_0486;
          do {
            if ((bVar3 & 1) != 0) {
              bVar1 = true;
            }
            bVar3 = bVar3 >> 1;
          } while (!bVar1);
          if (bVar3 != 0) {
            DAT_EXTMEM_0484 = 1;
            DAT_EXTMEM_0485 = '\x01';
          }
        }
      }
    }
  }
  return DAT_EXTMEM_0484;
}


// ===== FUN_CODE_2105  [app]  callers: CODE:2137 CODE:25d9

void FUN_CODE_2105(void)

{
  undefined1 *puVar1;
  char cVar2;
  undefined1 *puVar3;
  
  cVar2 = '\x13';
  puVar1 = &DAT_INTMEM_6d;
  do {
    *puVar1 = 0;
    puVar1 = puVar1 + '\x01';
    cVar2 = cVar2 + -1;
  } while (cVar2 != '\0');
  cVar2 = -0x80;
  puVar3 = &DAT_EXTMEM_0400;
  do {
    *puVar3 = 0;
    puVar3 = puVar3 + 1;
    cVar2 = cVar2 + -1;
  } while (cVar2 != '\0');
  DAT_INTMEM_30 = 0;
  DAT_INTMEM_31 = 0;
  DAT_INTMEM_34 = DAT_INTMEM_34 & 0xfb;
  DAT_INTMEM_4d = 0;
  FUN_CODE_25bb();
  return;
}


// ===== FUN_CODE_2127  [app]  callers: CODE:2137 CODE:25d9

void FUN_CODE_2127(void)

{
  DAT_INTMEM_4e = 0;
  DAT_EXTMEM_0024 = 0x3c;
  DAT_EXTMEM_0023 = 3;
  return;
}


// ===== FUN_CODE_2137  [app]  callers: CODE:0ec1

void FUN_CODE_2137(void)

{
  DAT_EXTMEM_1604 = 0xff;
  DAT_EXTMEM_1628 = 4;
  DAT_EXTMEM_1629 = 4;
  DAT_EXTMEM_162a = 4;
  DAT_EXTMEM_162b = 4;
  DAT_EXTMEM_162c = 4;
  DAT_EXTMEM_162d = 4;
  DAT_EXTMEM_162e = 4;
  DAT_EXTMEM_162f = 4;
  DAT_EXTMEM_1630 = 0;
  DAT_EXTMEM_1631 = 0;
  DAT_EXTMEM_1632 = 0;
  DAT_EXTMEM_1633 = 0;
  DAT_EXTMEM_1634 = 0;
  DAT_EXTMEM_1635 = 0;
  DAT_EXTMEM_1636 = 0;
  DAT_EXTMEM_1637 = 0;
  DAT_EXTMEM_1638 = 0;
  DAT_EXTMEM_1639 = 0;
  DAT_EXTMEM_163a = 0;
  DAT_EXTMEM_163b = 0;
  DAT_EXTMEM_163c = 0;
  DAT_EXTMEM_163d = 0;
  DAT_EXTMEM_163e = 0;
  DAT_EXTMEM_163f = 0;
  FUN_CODE_21b2();
  FUN_CODE_7994();
  FUN_CODE_2105();
  FUN_CODE_2127();
  FUN_CODE_2580();
  FUN_CODE_2612();
  return;
}


// ===== FUN_CODE_21b2  [app]  callers: CODE:0ec1 CODE:2137

/* WARNING: Removing unreachable block (CODE,0x21bd) */
/* WARNING: Removing unreachable block (CODE,0x21ea) */
/* WARNING: Removing unreachable block (CODE,0x21d8) */

void FUN_CODE_21b2(void)

{
  DAT_EXTMEM_0081 = 0;
  DAT_EXTMEM_1d22 = DAT_EXTMEM_1d22 | 0x20;
  DAT_EXTMEM_1d29 = DAT_EXTMEM_1d29 | 0x80;
  DAT_EXTMEM_1d23 = 4;
  DAT_EXTMEM_1d24 = 0x91;
  return;
}


// ===== FUN_CODE_21f9  [app]  callers: CODE:1c14 CODE:1b81 CODE:1bd4 CODE:1b56 CODE:1db2

void FUN_CODE_21f9(void)

{
  return;
}


// ===== thunk_FUN_CODE_4f75  [app]  callers: 

void thunk_FUN_CODE_4f75(void)

{
  FUN_CODE_4f75();
  return;
}


// ===== FUN_CODE_2200  [app]  callers: CODE:0400

void FUN_CODE_2200(char param_1)

{
  FUN_CODE_059d();
  SP = 0xa0;
  FUN_CODE_0f76();
  FUN_CODE_6000();
  if (param_1 == '3') {
    DAT_EXTMEM_1000 = DAT_EXTMEM_1000 & 0x7f;
    nop();
    TXCNTH = 1;
    nop();
    TXCNTH = 1;
    nop();
    TXCNTH = 1;
    nop();
    TXCNTH = 1;
    nop();
    nop();
    DAT_EXTMEM_0045 = 0;
    FUN_CODE_7fd8();
    FUN_CODE_0c47();
    FUN_CODE_05de();
  }
  else {
    FUN_CODE_0ec1();
    FUN_CODE_8000();
    FUN_CODE_05a7();
  }
  do {
    do {
      FUN_CODE_6fa8();
    } while (param_1 != -1);
    FUN_CODE_07c4();
    FUN_CODE_05de();
    nop();
    nop();
    nop();
    nop();
    if ((DAT_INTMEM_26 == '\0') && (DAT_INTMEM_27 == '\0')) {
      PCON = 1;
    }
  } while( true );
}


// ===== FUN_CODE_2260  [app]  callers: CODE:07c4

/* WARNING: Removing unreachable block (CODE,0x228b) */

void FUN_CODE_2260(void)

{
  char cVar1;
  byte bVar2;
  byte bVar3;
  byte *pbVar4;
  
  if (((DAT_INTMEM_40 >> 4 & 1) != 1) &&
     (DAT_INTMEM_40 = DAT_INTMEM_40 | 0x10, DAT_EXTMEM_0974 != '\0')) {
    FUN_CODE_2ffb();
  }
  DAT_INTMEM_34 = DAT_INTMEM_34 & 0xfb;
  DAT_EXTMEM_0748 = 0;
  DAT_EXTMEM_074a = '\x1d';
  DAT_EXTMEM_074b = 0x10;
  DAT_EXTMEM_0746 = 0;
  while( true ) {
    bVar2 = DAT_EXTMEM_0081 + 0x10;
    bVar3 = (0xef < DAT_EXTMEM_0081 ^ 0x80U) - (((DAT_EXTMEM_0746 < bVar2) << 7) >> 7);
    if (bVar3 < 0x81) break;
    FUN_CODE_25d9(-0x80 - bVar3);
    if ((bVar2 == 0) &&
       (DAT_EXTMEM_0748 =
             ~*(byte *)CONCAT11(DAT_EXTMEM_074a -
                                ((CARRY1(DAT_EXTMEM_074b,DAT_EXTMEM_0746) << 7) >> 7),
                                DAT_EXTMEM_074b + DAT_EXTMEM_0746) ^
             *(byte *)(DAT_EXTMEM_0746 + 0x6d), DAT_EXTMEM_0748 != 0)) {
      DAT_EXTMEM_0020 = 0xf < DAT_EXTMEM_0746;
      for (DAT_EXTMEM_0747 = 0; (DAT_EXTMEM_0747 < 8) << 7 < '\0';
          DAT_EXTMEM_0747 = DAT_EXTMEM_0747 + 1) {
        bVar3 = 1;
        cVar1 = DAT_EXTMEM_0747 + 1;
        while (cVar1 = cVar1 + -1, cVar1 != '\0') {
          bVar3 = bVar3 << 1;
        }
        if ((bVar3 & DAT_EXTMEM_0748) != 0) {
          bVar3 = DAT_EXTMEM_0746;
          if (DAT_EXTMEM_0020 == '\x01') {
            bVar3 = DAT_EXTMEM_0746 - 0x10;
          }
          DAT_INTMEM_4d = DAT_INTMEM_4d & 8 | bVar3 << 4 | DAT_EXTMEM_0747 & 7;
          bVar3 = 1;
          cVar1 = DAT_EXTMEM_0747 + 1;
          while (cVar1 = cVar1 + -1, cVar1 != '\0') {
            bVar3 = bVar3 << 1;
          }
          if ((bVar3 & *(byte *)(DAT_EXTMEM_0746 + 0x6d)) != 0) {
            FUN_CODE_853b(0x4c,0x4d,0,0,7,1,0,1);
            DAT_EXTMEM_074d = 1;
            FUN_CODE_1435();
            pbVar4 = (byte *)(DAT_EXTMEM_0746 + 0x6d);
            bVar3 = *pbVar4;
            bVar2 = 1;
            cVar1 = DAT_EXTMEM_0747 + 1;
            while (cVar1 = cVar1 + -1, cVar1 != '\0') {
              bVar2 = bVar2 << 1;
            }
            *pbVar4 = (byte)pbVar4;
            *pbVar4 = ~bVar2 & bVar3;
            DAT_EXTMEM_0748 = DAT_EXTMEM_0748 & ~bVar2;
          }
        }
      }
    }
    DAT_EXTMEM_0746 = DAT_EXTMEM_0746 + 1;
  }
  DAT_EXTMEM_0746 = 0;
  while( true ) {
    bVar2 = DAT_EXTMEM_0081 + 0x10;
    bVar3 = (0xef < DAT_EXTMEM_0081 ^ 0x80U) - (((DAT_EXTMEM_0746 < bVar2) << 7) >> 7);
    if (bVar3 < 0x81) break;
    FUN_CODE_25d9(-0x80 - bVar3);
    if ((bVar2 == 0) &&
       (DAT_EXTMEM_0748 =
             ~*(byte *)CONCAT11(DAT_EXTMEM_074a -
                                ((CARRY1(DAT_EXTMEM_074b,DAT_EXTMEM_0746) << 7) >> 7),
                                DAT_EXTMEM_074b + DAT_EXTMEM_0746) ^
             *(byte *)(DAT_EXTMEM_0746 + 0x6d), DAT_EXTMEM_0748 != 0)) {
      DAT_EXTMEM_0020 = 0xf < DAT_EXTMEM_0746;
      for (DAT_EXTMEM_0747 = 0; (DAT_EXTMEM_0747 < 8) << 7 < '\0';
          DAT_EXTMEM_0747 = DAT_EXTMEM_0747 + 1) {
        bVar3 = DAT_EXTMEM_0746;
        FUN_CODE_261c(DAT_EXTMEM_0747);
        if (bVar3 != 0) {
          bVar3 = 1;
          cVar1 = DAT_EXTMEM_0747 + 1;
          while (cVar1 = cVar1 + -1, cVar1 != '\0') {
            bVar3 = bVar3 << 1;
          }
          if ((bVar3 & DAT_EXTMEM_0748) != 0) {
            bVar3 = DAT_EXTMEM_0746;
            if (DAT_EXTMEM_0020 == '\x01') {
              bVar3 = DAT_EXTMEM_0746 - 0x10;
            }
            DAT_INTMEM_4d = DAT_INTMEM_4d & 8 | bVar3 << 4 | DAT_EXTMEM_0747 & 7;
            bVar3 = 1;
            cVar1 = DAT_EXTMEM_0747 + 1;
            while (cVar1 = cVar1 + -1, cVar1 != '\0') {
              bVar3 = bVar3 << 1;
            }
            if ((bVar3 & *(byte *)(DAT_EXTMEM_0746 + 0x6d)) == 0) {
              FUN_CODE_853b(0x4c,0x4d,0,0,7,1,0,1);
              DAT_EXTMEM_074d = 0;
              FUN_CODE_1435();
              DAT_INTMEM_4e = DAT_INTMEM_4d;
              DAT_INTMEM_59 = 0x28;
              DAT_INTMEM_57 = DAT_EXTMEM_0746;
              DAT_INTMEM_58 = DAT_EXTMEM_0747;
              DAT_INTMEM_33 = DAT_INTMEM_33 & 0xf0 | 2;
              DAT_EXTMEM_0025 = DAT_EXTMEM_0024;
              DAT_EXTMEM_0021 = DAT_EXTMEM_0020 == '\x01';
              pbVar4 = (byte *)(DAT_EXTMEM_0746 + 0x6d);
              bVar3 = *pbVar4;
              bVar2 = 1;
              cVar1 = DAT_EXTMEM_0747 + 1;
              while (cVar1 = cVar1 + -1, cVar1 != '\0') {
                bVar2 = bVar2 << 1;
              }
              *pbVar4 = (byte)pbVar4;
              *pbVar4 = bVar2 | bVar3;
              DAT_EXTMEM_0748 = DAT_EXTMEM_0748 & ~bVar2;
            }
          }
        }
      }
    }
    if (*(char *)(DAT_EXTMEM_0746 + 0x6d) != '\0') {
      DAT_INTMEM_34 = DAT_INTMEM_34 | 4;
    }
    DAT_EXTMEM_0746 = DAT_EXTMEM_0746 + 1;
  }
  if ((DAT_INTMEM_34 >> 2 & 1) != 1) {
    FUN_CODE_25bb(bVar2);
  }
  DAT_EXTMEM_1d33 = 1;
  DAT_EXTMEM_1105 = DAT_EXTMEM_1105 | 2;
  return;
}


// ===== FUN_CODE_2580  [app]  callers: CODE:813c CODE:2137

void FUN_CODE_2580(void)

{
  DAT_EXTMEM_1101 = 2;
  DAT_EXTMEM_1105 = DAT_EXTMEM_1105 | 2;
  return;
}


// ===== FUN_CODE_258e  [app]  callers: CODE:08bd

byte FUN_CODE_258e(void)

{
  byte bVar1;
  byte bVar2;
  byte bVar3;
  
  bVar3 = DAT_EXTMEM_1d33;
  if ((DAT_EXTMEM_1d33 >> 2 & 1) != 0) {
    bVar2 = 0;
    while (bVar1 = (0xef < DAT_EXTMEM_0081 ^ 0x80U) - (((bVar2 < DAT_EXTMEM_0081 + 0x10) << 7) >> 7)
          , bVar3 = 0x80 - bVar1, 0x80 < bVar1) {
      if (*(byte *)(bVar2 + 0x6d) != 0) {
        _6_7 = 1;
        return *(byte *)(bVar2 + 0x6d);
      }
      bVar2 = bVar2 + 1;
    }
  }
  return bVar3;
}


// ===== FUN_CODE_25bb  [app]  callers: CODE:2105 CODE:2260

void FUN_CODE_25bb(void)

{
  DAT_INTMEM_40 = DAT_INTMEM_40 & 0xef;
  DAT_INTMEM_4e = 0;
  DAT_EXTMEM_008d = 0;
  DAT_EXTMEM_008e = 0;
  FUN_CODE_1577();
  FUN_CODE_16dc();
  DAT_EXTMEM_0020 = 0;
  DAT_EXTMEM_0021 = 0;
  return;
}


// ===== FUN_CODE_25d9  [app]  callers: CODE:2260 CODE:813c

char FUN_CODE_25d9(void)

{
  char cVar1;
  
  if ((DAT_INTMEM_30 < DAT_INTMEM_31 + 1U) << 7 < '\0') {
    DAT_EXTMEM_074c = DAT_INTMEM_31 - DAT_INTMEM_30;
  }
  else {
    DAT_EXTMEM_074c = (DAT_INTMEM_31 + -0x80) - DAT_INTMEM_30;
  }
  cVar1 = DAT_EXTMEM_074c - 0x40;
  if (0x3f < DAT_EXTMEM_074c) {
    FUN_CODE_2105(0);
    cVar1 = FUN_CODE_2127();
    DAT_INTMEM_32 = 0;
    DAT_INTMEM_33 = DAT_INTMEM_33 & 0xf0;
  }
  return cVar1;
}


// ===== FUN_CODE_2612  [app]  callers: CODE:2137

void FUN_CODE_2612(void)

{
  DAT_INTMEM_57 = 0xff;
  DAT_INTMEM_58 = 0xff;
  DAT_INTMEM_59 = 0;
  return;
}


// ===== FUN_CODE_261c  [app]  callers: CODE:2260

void FUN_CODE_261c(char param_1,char param_2)

{
  if ((DAT_INTMEM_57 == param_2) && (DAT_INTMEM_58 == param_1)) {
    if (DAT_INTMEM_59 == '\0') {
      return;
    }
    return;
  }
  return;
}


// ===== FUN_CODE_2633  [app]  callers: CODE:813c

void FUN_CODE_2633(void)

{
  if ((DAT_EXTMEM_2f52 & 0xf) == 0) {
    PCON = 2;
    nop();
    nop();
    nop();
    nop();
    nop();
    nop();
    nop();
    nop();
    DAT_EXTMEM_1e03 = 0;
  }
  return;
}


// ===== FUN_CODE_264b  [app]  callers: CODE:813c

void FUN_CODE_264b(void)

{
  if ((DAT_EXTMEM_2f52 & 0xf) == 0) {
    DAT_EXTMEM_1e03 = 3;
    PCON = 2;
    nop();
    nop();
    nop();
    nop();
    nop();
    nop();
    nop();
    nop();
  }
  return;
}


// ===== FUN_CODE_2665  [app]  callers: CODE:813c

void FUN_CODE_2665(void)

{
  if ((DAT_EXTMEM_2f52 & 0xf) == 0) {
    DAT_EXTMEM_1e03 = 1;
    PCON = 2;
    nop();
    nop();
    nop();
    nop();
    nop();
    nop();
    nop();
    nop();
  }
  return;
}


// ===== FUN_CODE_267e  [app]  callers: 

void FUN_CODE_267e(char param_1)

{
  char cVar1;
  
  DAT_EXTMEM_111d = DAT_EXTMEM_111d & 0xbf;
  DAT_EXTMEM_1b06 = 0x40;
  DAT_EXTMEM_111c = 0x40;
  FUN_CODE_36eb();
  if (param_1 != '\0') {
    cVar1 = '\x01';
    FUN_CODE_510d();
    if (cVar1 == '\0') {
      DAT_EXTMEM_111d = DAT_EXTMEM_111d | 0x40;
    }
  }
  return;
}


// ===== FUN_CODE_26a5  [app]  callers: 

void FUN_CODE_26a5(void)

{
  DAT_EXTMEM_111d = DAT_EXTMEM_111d & 0x7f;
  DAT_EXTMEM_1b06 = 0x80;
  DAT_EXTMEM_111c = 0x80;
  return;
}


// ===== FUN_CODE_26b7  [app]  callers: CODE:0946

void FUN_CODE_26b7(void)

{
  DAT_EXTMEM_0746 = '\0';
  if (DAT_EXTMEM_00cf != '\0') {
    DAT_EXTMEM_00cf = '\0';
    FUN_CODE_26e2();
    DAT_EXTMEM_00df = 1;
    if (DAT_EXTMEM_0746 == '\0') {
      FUN_CODE_6d7b();
    }
    DAT_EXTMEM_00df = 0;
    DAT_EXTMEM_00da = DAT_EXTMEM_00da + '\x01';
  }
  return;
}


// ===== FUN_CODE_26e2  [app]  callers: CODE:26b7

void FUN_CODE_26e2(char param_1)

{
  char cVar1;
  
  DAT_EXTMEM_1106 = DAT_EXTMEM_1106 & 0xbf;
  nop();
  nop();
  nop();
  nop();
  cVar1 = DAT_EXTMEM_00f4;
  if (DAT_EXTMEM_00f4 == '\0') {
    cVar1 = DAT_EXTMEM_00f5;
  }
  if (cVar1 == '\0') {
    FUN_CODE_4bc4();
  }
  else {
    FUN_CODE_512d();
  }
  FUN_CODE_6d0d();
  FUN_CODE_36eb();
  if (param_1 != '\0') {
    FUN_CODE_510d(2);
  }
  DAT_EXTMEM_1106 = DAT_EXTMEM_1106 | 0x40;
  return;
}


// ===== FUN_CODE_2715  [app]  callers: CODE:510d CODE:4f75

void FUN_CODE_2715(void)

{
  _6_1 = 1;
  return;
}


// ===== FUN_CODE_2718  [app]  callers: CODE:291f

void FUN_CODE_2718(byte param_1)

{
  DAT_EXTMEM_0785 = param_1;
  if (0x84 < param_1) {
    FUN_CODE_27cf(param_1 + 0x7b);
    return;
  }
  if (DAT_EXTMEM_0a6b == '\0') {
    FUN_CODE_27bf();
    return;
  }
                    /* WARNING: Subroutine does not return */
  FUN_CODE_890a(param_1);
}


// ===== FUN_CODE_2769  [app]  callers: 

void FUN_CODE_2769(void)

{
  return;
}


// ===== FUN_CODE_276c  [app]  callers: 

void FUN_CODE_276c(void)

{
  return;
}


// ===== FUN_CODE_276f  [app]  callers: 

void FUN_CODE_276f(void)

{
  return;
}


// ===== FUN_CODE_2772  [app]  callers: 

void FUN_CODE_2772(void)

{
  return;
}


// ===== FUN_CODE_2775  [app]  callers: 

void FUN_CODE_2775(void)

{
  return;
}


// ===== FUN_CODE_2778  [app]  callers: 

void FUN_CODE_2778(void)

{
  return;
}


// ===== FUN_CODE_277b  [app]  callers: 

void FUN_CODE_277b(void)

{
  return;
}


// ===== FUN_CODE_277e  [app]  callers: 

void FUN_CODE_277e(void)

{
  return;
}


// ===== FUN_CODE_2781  [app]  callers: 

void FUN_CODE_2781(void)

{
  return;
}


// ===== FUN_CODE_2784  [app]  callers: 

void FUN_CODE_2784(void)

{
  return;
}


// ===== FUN_CODE_2787  [app]  callers: 

void FUN_CODE_2787(void)

{
  return;
}


// ===== FUN_CODE_278a  [app]  callers: 

void FUN_CODE_278a(void)

{
  return;
}


// ===== FUN_CODE_278d  [app]  callers: 

void FUN_CODE_278d(void)

{
  return;
}


// ===== FUN_CODE_2790  [app]  callers: 

void FUN_CODE_2790(void)

{
  if (DAT_EXTMEM_0a6c == '\0') {
    DAT_EXTMEM_0a72 = 1;
  }
  return;
}


// ===== FUN_CODE_279e  [app]  callers: 

void FUN_CODE_279e(void)

{
  if (DAT_EXTMEM_0a71 == '\x02') {
    DAT_EXTMEM_0a71 = 1;
    if (DAT_EXTMEM_0a6c == '\0') {
      DAT_EXTMEM_0a72 = 1;
    }
    return;
  }
  return;
}


// ===== FUN_CODE_27b9  [app]  callers: 

void FUN_CODE_27b9(void)

{
  return;
}


// ===== FUN_CODE_27bc  [app]  callers: 

void FUN_CODE_27bc(void)

{
  return;
}


// ===== FUN_CODE_27bf  [app]  callers: CODE:2718

undefined1 FUN_CODE_27bf(void)

{
  return *(undefined1 *)
          CONCAT11('\v' - (((0x65 < DAT_EXTMEM_0785) << 7) >> 7),DAT_EXTMEM_0785 + 0x9a);
}


// ===== FUN_CODE_27cf  [app]  callers: CODE:2718

void FUN_CODE_27cf(void)

{
  return;
}


// ===== FUN_CODE_27d2  [app]  callers: CODE:30ce CODE:2db4

void FUN_CODE_27d2(void)

{
  undefined1 uVar1;
  
  FUN_CODE_8844(0x780);
  uVar1 = FUN_CODE_8561();
  DAT_EXTMEM_0a73 = 0;
                    /* WARNING: Subroutine does not return */
  FUN_CODE_890a(uVar1);
}


// ===== FUN_CODE_2807  [app]  callers: 

void FUN_CODE_2807(void)

{
  DAT_EXTMEM_0a6c = 1;
  return;
}


// ===== FUN_CODE_280e  [app]  callers: 

void FUN_CODE_280e(void)

{
  DAT_EXTMEM_0a6b = 1;
  DAT_EXTMEM_0a71 = 1;
  return;
}


// ===== FUN_CODE_2819  [app]  callers: 

void FUN_CODE_2819(void)

{
  DAT_EXTMEM_0a6b = 1;
  DAT_EXTMEM_0a71 = 2;
  return;
}


// ===== FUN_CODE_2825  [app]  callers: 

void FUN_CODE_2825(void)

{
  if (DAT_EXTMEM_0a6b != '\0') {
    DAT_EXTMEM_0a6b = 0;
    DAT_EXTMEM_0a6c = 0;
    return;
  }
  if (DAT_EXTMEM_0a6c == '\0') {
    DAT_EXTMEM_0a6f = DAT_EXTMEM_0a6f | 2;
  }
  else {
    DAT_EXTMEM_0a6f = DAT_EXTMEM_0a6f & 0xfd;
  }
  DAT_EXTMEM_0a6c = 0;
  DAT_EXTMEM_0a72 = 1;
  return;
}


// ===== FUN_CODE_2847  [app]  callers: 

void FUN_CODE_2847(void)

{
  if (DAT_EXTMEM_0a6c == '\0') {
    DAT_EXTMEM_0a6f = DAT_EXTMEM_0a6f | 0x20;
  }
  else {
    DAT_EXTMEM_0a6f = DAT_EXTMEM_0a6f & 0xdf;
  }
  DAT_EXTMEM_0a6c = 0;
  DAT_EXTMEM_0a72 = 1;
  return;
}


// ===== FUN_CODE_285c  [app]  callers: 

void FUN_CODE_285c(void)

{
  if (DAT_EXTMEM_0a6b == '\0') {
    if (DAT_EXTMEM_0a6c == '\0') {
      DAT_EXTMEM_0a6f = DAT_EXTMEM_0a6f | 4;
    }
    else {
      DAT_EXTMEM_0a6f = DAT_EXTMEM_0a6f & 0xfb;
    }
  }
  else {
    if (DAT_EXTMEM_0a6c == '\0') {
      DAT_EXTMEM_0a6f = DAT_EXTMEM_0a6f | 0x40;
    }
    else {
      DAT_EXTMEM_0a6f = DAT_EXTMEM_0a6f & 0xbf;
    }
    DAT_EXTMEM_0a6b = '\0';
  }
  DAT_EXTMEM_0a6c = 0;
  DAT_EXTMEM_0a72 = 1;
  return;
}


// ===== FUN_CODE_288f  [app]  callers: 

void FUN_CODE_288f(void)

{
  if (DAT_EXTMEM_0a71 == '\x02') {
    return;
  }
  if (DAT_EXTMEM_0a6b == '\0') {
    if (DAT_EXTMEM_0a6c == '\0') {
      DAT_EXTMEM_0a6f = DAT_EXTMEM_0a6f | 1;
    }
    else {
      DAT_EXTMEM_0a6f = DAT_EXTMEM_0a6f & 0xfe;
    }
  }
  else {
    if (DAT_EXTMEM_0a6c == '\0') {
      DAT_EXTMEM_0a6f = DAT_EXTMEM_0a6f | 0x10;
    }
    else {
      DAT_EXTMEM_0a6f = DAT_EXTMEM_0a6f & 0xef;
    }
    DAT_EXTMEM_0a6b = '\0';
  }
  DAT_EXTMEM_0a6c = 0;
  DAT_EXTMEM_0a72 = 1;
  return;
}


// ===== FUN_CODE_28d6  [app]  callers: 

void FUN_CODE_28d6(void)

{
  if (DAT_EXTMEM_0a6b != '\0') {
    if (DAT_EXTMEM_0a6c == '\0') {
      DAT_EXTMEM_0a6f = DAT_EXTMEM_0a6f | 8;
    }
    else {
      DAT_EXTMEM_0a6f = DAT_EXTMEM_0a6f & 0xf7;
    }
    DAT_EXTMEM_0a6c = '\0';
    DAT_EXTMEM_0a6b = '\0';
  }
  DAT_EXTMEM_0a72 = 1;
  return;
}


// ===== FUN_CODE_28f8  [app]  callers: 

void FUN_CODE_28f8(void)

{
  if (DAT_EXTMEM_0a6b != '\0') {
    if (DAT_EXTMEM_0a6c == '\0') {
      DAT_EXTMEM_0a6f = DAT_EXTMEM_0a6f | 0x80;
    }
    else {
      DAT_EXTMEM_0a6f = DAT_EXTMEM_0a6f & 0x7f;
    }
    DAT_EXTMEM_0a6c = '\0';
    DAT_EXTMEM_0a6b = '\0';
  }
  DAT_EXTMEM_0a72 = 1;
  return;
}


// ===== FUN_CODE_291f  [app]  callers: 

void FUN_CODE_291f(undefined1 param_1,char param_2)

{
  FUN_CODE_2718(param_1);
  if (DAT_EXTMEM_0a6c == '\0') {
    if ((param_2 != '\0') && (DAT_EXTMEM_0a70 < 0x1e)) {
      for (DAT_EXTMEM_0784 = 0;
          (DAT_EXTMEM_0784 < 0x1e &&
          (*(char *)CONCAT11('\n' - (((0x79 < DAT_EXTMEM_0784) << 7) >> 7),DAT_EXTMEM_0784 + 0x86)
           != param_2)); DAT_EXTMEM_0784 = DAT_EXTMEM_0784 + 1) {
      }
      if (DAT_EXTMEM_0784 != 0x1e) {
        DAT_EXTMEM_0a6b = 0;
        return;
      }
      if ((DAT_EXTMEM_0022 >> 2 & 1) != 1) {
        *(char *)CONCAT11('\t' - (((0xaa < DAT_EXTMEM_0a70) << 7) >> 7),DAT_EXTMEM_0a70 + 0x55) =
             param_2;
        DAT_EXTMEM_0a73 = 1;
      }
      DAT_EXTMEM_0a70 = DAT_EXTMEM_0a70 + 1;
      *(char *)CONCAT11('\n' - (((0x79 < DAT_EXTMEM_0974) << 7) >> 7),DAT_EXTMEM_0974 + 0x86) =
           param_2;
      DAT_EXTMEM_0974 = DAT_EXTMEM_0974 + 1;
      DAT_EXTMEM_0a6b = 0;
      return;
    }
    if (param_2 == '\0') {
      DAT_EXTMEM_0a6b = 0;
      return;
    }
    if (0x20 < DAT_EXTMEM_0974) {
      DAT_EXTMEM_0a6b = 0;
      return;
    }
    for (DAT_EXTMEM_0784 = 0;
        (DAT_EXTMEM_0784 < 0x21 &&
        (*(char *)CONCAT11('\n' - (((0x79 < DAT_EXTMEM_0784) << 7) >> 7),DAT_EXTMEM_0784 + 0x86) !=
         param_2)); DAT_EXTMEM_0784 = DAT_EXTMEM_0784 + 1) {
    }
    if (DAT_EXTMEM_0784 != 0x21) {
      DAT_EXTMEM_0a6b = 0;
      return;
    }
    *(char *)CONCAT11('\n' - (((0x79 < DAT_EXTMEM_0974) << 7) >> 7),DAT_EXTMEM_0974 + 0x86) =
         param_2;
    if (DAT_EXTMEM_0974 + 1 != '\x1f') {
      DAT_EXTMEM_0974 = DAT_EXTMEM_0974 + 1;
      DAT_EXTMEM_0a6b = 0;
      return;
    }
    DAT_EXTMEM_0974 = 0x1f;
    for (DAT_EXTMEM_0784 = 0; DAT_EXTMEM_0784 < 0x1e; DAT_EXTMEM_0784 = DAT_EXTMEM_0784 + 1) {
      *(undefined1 *)CONCAT11('\t' - (((0xaa < DAT_EXTMEM_0784) << 7) >> 7),DAT_EXTMEM_0784 + 0x55)
           = 1;
    }
  }
  else {
    DAT_EXTMEM_0a6c = '\0';
    if (param_2 == '\0') {
      DAT_EXTMEM_0a6b = 0;
      DAT_EXTMEM_0a6c = 0;
      return;
    }
    if ((DAT_EXTMEM_0974 < 0x1e) << 7 < '\0') {
      for (DAT_EXTMEM_0784 = 0; (DAT_EXTMEM_0784 < 0x1e) << 7 < '\0';
          DAT_EXTMEM_0784 = DAT_EXTMEM_0784 + 1) {
        if ((*(char *)CONCAT11('\n' - (((0x79 < DAT_EXTMEM_0784) << 7) >> 7),DAT_EXTMEM_0784 + 0x86)
             == param_2) && (DAT_EXTMEM_0a70 != 0)) {
          do {
            if ((DAT_EXTMEM_0022 >> 2 & 1) != 1) {
              *(undefined1 *)
               CONCAT11('\t' - (((0xaa < DAT_EXTMEM_0784) << 7) >> 7),DAT_EXTMEM_0784 + 0x55) =
                   *(undefined1 *)
                    CONCAT11('\t' - (((0xa9 < DAT_EXTMEM_0784) << 7) >> 7),DAT_EXTMEM_0784 + 0x56);
              *(undefined1 *)
               CONCAT11('\t' - (((0xa9 < DAT_EXTMEM_0784) << 7) >> 7),DAT_EXTMEM_0784 + 0x56) = 0;
            }
            *(undefined1 *)
             CONCAT11('\n' - (((0x79 < DAT_EXTMEM_0784) << 7) >> 7),DAT_EXTMEM_0784 + 0x86) =
                 *(undefined1 *)
                  CONCAT11('\n' - (((0x78 < DAT_EXTMEM_0784) << 7) >> 7),DAT_EXTMEM_0784 + 0x87);
            *(undefined1 *)
             CONCAT11('\n' - (((0x78 < DAT_EXTMEM_0784) << 7) >> 7),DAT_EXTMEM_0784 + 0x87) = 0;
            DAT_EXTMEM_0784 = DAT_EXTMEM_0784 + 1;
          } while ((DAT_EXTMEM_0784 < 0x1d) << 7 < '\0');
          DAT_EXTMEM_0a70 = DAT_EXTMEM_0a70 - 1;
          DAT_EXTMEM_0974 = DAT_EXTMEM_0974 - 1;
          if ((DAT_EXTMEM_0022 >> 2 & 1) != 1) {
            DAT_EXTMEM_0a73 = 1;
          }
        }
      }
      DAT_EXTMEM_0a6b = 0;
      return;
    }
    for (DAT_EXTMEM_0784 = 0; DAT_EXTMEM_0784 < 0x21; DAT_EXTMEM_0784 = DAT_EXTMEM_0784 + 1) {
      if (*(char *)CONCAT11('\n' - (((0x79 < DAT_EXTMEM_0784) << 7) >> 7),DAT_EXTMEM_0784 + 0x86) ==
          param_2) {
        if ((DAT_EXTMEM_0784 < 0x20) << 7 < '\0') {
          do {
            *(undefined1 *)
             CONCAT11('\n' - (((0x79 < DAT_EXTMEM_0784) << 7) >> 7),DAT_EXTMEM_0784 + 0x86) =
                 *(undefined1 *)
                  CONCAT11('\n' - (((0x78 < DAT_EXTMEM_0784) << 7) >> 7),DAT_EXTMEM_0784 + 0x87);
            *(undefined1 *)
             CONCAT11('\n' - (((0x78 < DAT_EXTMEM_0784) << 7) >> 7),DAT_EXTMEM_0784 + 0x87) = 0;
            DAT_EXTMEM_0784 = DAT_EXTMEM_0784 + 1;
          } while ((DAT_EXTMEM_0784 < 0x20) << 7 < '\0');
        }
        else {
          *(undefined1 *)
           CONCAT11('\n' - (((0x79 < DAT_EXTMEM_0784) << 7) >> 7),DAT_EXTMEM_0784 + 0x86) = 0;
        }
        DAT_EXTMEM_0974 = DAT_EXTMEM_0974 - 1;
      }
    }
    if (0x1e < DAT_EXTMEM_0974) {
      DAT_EXTMEM_0a6b = 0;
      return;
    }
    DAT_EXTMEM_0784 = 0;
    do {
      *(undefined1 *)CONCAT11('\t' - (((0xaa < DAT_EXTMEM_0784) << 7) >> 7),DAT_EXTMEM_0784 + 0x55)
           = *(undefined1 *)
              CONCAT11('\n' - (((0x79 < DAT_EXTMEM_0784) << 7) >> 7),DAT_EXTMEM_0784 + 0x86);
      DAT_EXTMEM_0784 = DAT_EXTMEM_0784 + 1;
    } while (DAT_EXTMEM_0784 != 0x1e);
    DAT_EXTMEM_0a70 = DAT_EXTMEM_0974;
    DAT_EXTMEM_0784 = 0x1e;
  }
  DAT_EXTMEM_0a73 = 1;
  DAT_EXTMEM_0a6b = 0;
  return;
}


// ===== FUN_CODE_2bbe  [app]  callers: CODE:3029

byte FUN_CODE_2bbe(byte param_1,byte param_2,undefined1 param_3,byte param_4)

{
  byte bVar1;
  undefined1 uVar2;
  undefined2 uVar3;
  
  DAT_EXTMEM_0779 = param_4;
  if ((param_4 == 1) || (DAT_EXTMEM_0973 == '\0')) {
    DAT_EXTMEM_077a = param_2 ^ 1 | param_1;
    if (DAT_EXTMEM_077a == 0) {
      DAT_EXTMEM_077b = 1;
      FUN_CODE_85a7(DAT_EXTMEM_0a6d);
      return DAT_EXTMEM_077b;
    }
    DAT_EXTMEM_077a = 0;
    DAT_EXTMEM_077b = 2;
    FUN_CODE_85a7(1);
    uVar3 = 1;
    uVar2 = DAT_EXTMEM_0a6d;
  }
  else {
    bVar1 = param_4 ^ 0xcd;
    if (bVar1 != 0) {
      FUN_CODE_33af();
      DAT_EXTMEM_077a = param_3;
      DAT_EXTMEM_077b = param_4;
      return param_4;
    }
    DAT_EXTMEM_077b = 3;
    DAT_EXTMEM_077a = bVar1;
    if (DAT_EXTMEM_080f == '\x01') {
      DAT_EXTMEM_080f = '\0';
      FUN_CODE_85a7(0xcd);
      FUN_CODE_85b9(DAT_EXTMEM_0811,1);
      uVar3 = 2;
      uVar2 = 0;
    }
    else {
      FUN_CODE_85a7(0xcd);
      FUN_CODE_85b9(DAT_EXTMEM_0812,1);
      uVar2 = *(undefined1 *)CONCAT11(0xe,DAT_EXTMEM_0812);
      uVar3 = 2;
    }
  }
  FUN_CODE_85b9(uVar2,uVar3);
  return DAT_EXTMEM_077b;
}


// ===== FUN_CODE_2c5b  [app]  callers: CODE:3044

void FUN_CODE_2c5b(undefined1 param_1,undefined1 param_2,undefined1 param_3,byte param_4,
                  byte param_5,char param_6)

{
  byte bVar1;
  
  DAT_EXTMEM_0779 = param_6;
  DAT_EXTMEM_077a = param_4;
  DAT_EXTMEM_077b = param_5;
  DAT_EXTMEM_077c = param_3;
  DAT_EXTMEM_077d = param_2;
  DAT_EXTMEM_077e = param_1;
  if ((param_6 != '\x01') && (DAT_EXTMEM_0973 != '\0')) {
    if (param_6 == -0x33) {
      FUN_CODE_3812(param_1,param_2,param_3);
      return;
    }
    FUN_CODE_3501(param_1,param_2,param_3,0);
    return;
  }
  if (param_4 == 0) {
    param_4 = param_5 ^ 1;
  }
  if (param_4 == 0) {
    DAT_EXTMEM_0a6d = FUN_CODE_8561(param_1,param_2,param_3);
  }
  else {
    DAT_EXTMEM_0a6d = FUN_CODE_857a(1,param_1,param_2,param_3);
  }
  bVar1 = (DAT_EXTMEM_0a6d & 4) >> 2 |
          (DAT_EXTMEM_0a6d & 2) * '\x02' | (DAT_EXTMEM_0a6d & 1) * '\x02';
  FUN_CODE_6e2a(bVar1,bVar1);
  _9_0 = _8_1 & 1;
  return;
}


// ===== FUN_CODE_2cf0  [app]  callers: CODE:473f

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

char FUN_CODE_2cf0(byte param_1,char param_2)

{
  char cVar1;
  
  cVar1 = param_2 + -1;
  if (param_2 == '\0') {
    _DAT_EXTMEM_0740 = (ushort)param_1 * 4;
    cVar1 = (char)_DAT_EXTMEM_0740;
  }
  return cVar1;
}


// ===== FUN_CODE_2d12  [app]  callers: CODE:473f

byte FUN_CODE_2d12(char param_1)

{
  char cVar1;
  byte bVar2;
  byte bVar3;
  
  if (param_1 == '\0') {
    cVar1 = '\x02';
    bVar2 = DAT_EXTMEM_0740;
    bVar3 = DAT_EXTMEM_0741;
    do {
      bVar3 = bVar3 >> 1 | bVar2 << 7;
      cVar1 = cVar1 + -1;
      bVar2 = bVar2 >> 1;
    } while (cVar1 != '\0');
    return bVar3;
  }
  return param_1 - 1;
}


// ===== FUN_CODE_2d36  [app]  callers: CODE:473f CODE:4b29

void FUN_CODE_2d36(char param_1)

{
  DAT_EXTMEM_0973 = param_1;
  if (param_1 == '\0') {
    DAT_EXTMEM_00f6 = 0;
    DAT_EXTMEM_00f7 = 0;
  }
  return;
}


// ===== FUN_CODE_2d44  [app]  callers: CODE:473f

undefined1 FUN_CODE_2d44(void)

{
  return DAT_EXTMEM_0973;
}


// ===== FUN_CODE_2d4a  [app]  callers: CODE:76f5 CODE:1d0c CODE:6fbe CODE:708c CODE:70fe CODE:7675

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


// ===== FUN_CODE_2d85  [app]  callers: CODE:2eb7

undefined1 FUN_CODE_2d85(void)

{
  char cVar1;
  
  cVar1 = DAT_EXTMEM_0a84;
  if (DAT_EXTMEM_0a84 != DAT_EXTMEM_0a85) {
    DAT_EXTMEM_0a84 = DAT_EXTMEM_0a84 + 1;
    if (7 < DAT_EXTMEM_0a84) {
      DAT_EXTMEM_0a84 = 0;
    }
    return *(undefined1 *)
            (CONCAT11('\n' - (((0x8bU < (byte)(cVar1 * '\x02')) << 7) >> 7),cVar1 * '\x02' + 0x74) +
            1);
  }
  return 0;
}


// ===== FUN_CODE_2db4  [app]  callers: CODE:3120

undefined1 FUN_CODE_2db4(undefined1 param_1,undefined1 param_2,undefined1 param_3,char param_4)

{
  bool bVar1;
  char cVar2;
  undefined1 uVar3;
  byte bVar4;
  
  DAT_EXTMEM_077b = '\0';
  DAT_EXTMEM_077c = 0x21;
  DAT_EXTMEM_077e = '\x01';
  DAT_EXTMEM_0777 = param_4;
  DAT_EXTMEM_0778 = param_3;
  DAT_EXTMEM_0779 = param_2;
  DAT_EXTMEM_077a = param_1;
  do {
    FUN_CODE_1f4e();
    DAT_EXTMEM_077d = param_4;
    if (param_4 == -1) break;
    param_4 = '\0';
    FUN_CODE_27d2(0x7d,7,1,0,0,0);
    DAT_EXTMEM_077e = '\0';
  } while (DAT_EXTMEM_0a72 == '\0');
  if (DAT_EXTMEM_0a6e != DAT_EXTMEM_0a6f) {
    DAT_EXTMEM_0a73 = '\x01';
  }
  DAT_EXTMEM_0a72 = 0;
  if ((DAT_EXTMEM_0a73 == '\0') || (DAT_EXTMEM_077e != '\0')) {
    if (DAT_EXTMEM_073d != '\x01') {
      return 0;
    }
    if (DAT_EXTMEM_0953 == '\0') {
      bVar4 = 0;
      do {
        if (*(char *)CONCAT11('\t' - (((0xaa < bVar4) << 7) >> 7),bVar4 + 0x55) != '\0') {
          bVar1 = true;
          break;
        }
        bVar4 = bVar4 + 1;
        bVar1 = false;
      } while (bVar4 != 0x1e);
    }
    else {
      bVar1 = true;
    }
    DAT_EXTMEM_073d = 0;
    if (!bVar1) {
      return 0;
    }
  }
  else {
    DAT_EXTMEM_073e = 0;
    DAT_EXTMEM_073f = 0;
  }
  DAT_EXTMEM_073d = 0;
  DAT_EXTMEM_0952 = 1;
  DAT_EXTMEM_0953 = DAT_EXTMEM_0a6f;
  if (DAT_EXTMEM_0973 == '\0') {
    DAT_EXTMEM_077b = DAT_EXTMEM_0973;
    DAT_EXTMEM_077c = 8;
    uVar3 = 0x53;
    cVar2 = '\0';
  }
  else {
    uVar3 = 0x52;
    cVar2 = DAT_EXTMEM_077b;
  }
  FUN_CODE_5600(cVar2,DAT_EXTMEM_077c,9,uVar3,DAT_EXTMEM_0779,DAT_EXTMEM_077a);
  DAT_EXTMEM_0a6e = DAT_EXTMEM_0a6f;
  return DAT_EXTMEM_077c;
}


// ===== FUN_CODE_2eb7  [app]  callers: CODE:3120

undefined1
FUN_CODE_2eb7(undefined1 param_1,undefined1 param_2,undefined1 param_3,byte param_4,byte param_5)

{
  byte bVar1;
  undefined1 uVar2;
  
  DAT_EXTMEM_077d = '\0';
  DAT_EXTMEM_077e = 3;
  DAT_EXTMEM_0777 = param_5;
  DAT_EXTMEM_0778 = param_3;
  DAT_EXTMEM_0779 = param_2;
  DAT_EXTMEM_077a = param_1;
  FUN_CODE_2d85();
  bVar1 = ~param_5;
  if (bVar1 == 0) {
    bVar1 = ~param_4;
  }
  DAT_EXTMEM_077b = param_4;
  DAT_EXTMEM_077c = param_5;
  if (bVar1 == 0) {
    uVar2 = FUN_CODE_2ff7();
    return uVar2;
  }
  if ((char)param_4 < '\0') {
    DAT_EXTMEM_077b = param_4 & 0x7f;
    DAT_EXTMEM_077d = '\x01';
  }
  FUN_CODE_566e(0,DAT_EXTMEM_077e,0,DAT_EXTMEM_0779,DAT_EXTMEM_077a);
  if (DAT_EXTMEM_077b < 0x40) {
    FUN_CODE_85a7(2,DAT_EXTMEM_077a,DAT_EXTMEM_0779,DAT_EXTMEM_0778);
    if (DAT_EXTMEM_077d == '\0') {
      bVar1 = DAT_EXTMEM_077b;
      FUN_CODE_85b9(DAT_EXTMEM_077c,1,DAT_EXTMEM_077a,DAT_EXTMEM_0779,DAT_EXTMEM_0778,
                    DAT_EXTMEM_077b);
      FUN_CODE_85b9(bVar1,2);
    }
    return DAT_EXTMEM_077e;
  }
                    /* WARNING: Subroutine does not return */
  FUN_CODE_8930(DAT_EXTMEM_077c,DAT_EXTMEM_077b);
}


// ===== FUN_CODE_2f7c  [app]  callers: 

void FUN_CODE_2f7c(void)

{
  FUN_CODE_85a7(3,DAT_EXTMEM_077a,DAT_EXTMEM_0779,DAT_EXTMEM_0778);
  if (DAT_EXTMEM_077d == '\0') {
    FUN_CODE_85b9(1,1,DAT_EXTMEM_077a,DAT_EXTMEM_0779,DAT_EXTMEM_0778);
  }
  return;
}


// ===== FUN_CODE_2fa7  [app]  callers: 

void FUN_CODE_2fa7(void)

{
  char cVar1;
  char cVar2;
  
  FUN_CODE_85a7(4,DAT_EXTMEM_077a,DAT_EXTMEM_0779,DAT_EXTMEM_0778);
  cVar1 = DAT_EXTMEM_077c + -1;
  DAT_EXTMEM_077b = DAT_EXTMEM_077b + (-0x41 - (((DAT_EXTMEM_077c != '\0') << 7) >> 7));
  if (DAT_EXTMEM_077d == '\0') {
    cVar2 = '\x01';
    while (DAT_EXTMEM_077c = DAT_EXTMEM_077c + -1, DAT_EXTMEM_077c != '\0') {
      cVar2 = cVar2 << 1;
    }
    DAT_EXTMEM_077c = cVar1;
    FUN_CODE_85b9(cVar2,1,DAT_EXTMEM_077a,DAT_EXTMEM_0779,DAT_EXTMEM_0778);
    cVar1 = DAT_EXTMEM_077c;
  }
  DAT_EXTMEM_077c = cVar1;
  return;
}


// ===== thunk_FUN_CODE_2ff7  [app]  callers: 

undefined1 thunk_FUN_CODE_2ff7(void)

{
  return 0;
}


// ===== FUN_CODE_2ff7  [app]  callers: CODE:2eb7

undefined1 FUN_CODE_2ff7(void)

{
  return 0;
}


// ===== FUN_CODE_2ffb  [app]  callers: CODE:2260 CODE:6cb3

void FUN_CODE_2ffb(void)

{
  byte bVar1;
  char cVar2;
  undefined1 *puVar3;
  
  DAT_EXTMEM_0953 = 0;
  DAT_EXTMEM_0954 = 0;
  bVar1 = 0;
  do {
    *(undefined1 *)CONCAT11('\t' - (((0xaa < bVar1) << 7) >> 7),bVar1 + 0x55) = 0;
    bVar1 = bVar1 + 1;
  } while (bVar1 != 0x1e);
  DAT_EXTMEM_0a70 = 0;
  cVar2 = '!';
  puVar3 = &DAT_EXTMEM_0a86;
  do {
    *puVar3 = 0;
    puVar3 = puVar3 + 1;
    cVar2 = cVar2 + -1;
  } while (cVar2 != '\0');
  DAT_EXTMEM_0974 = 0;
  return;
}


// ===== FUN_CODE_3029  [app]  callers: CODE:3201

undefined1 FUN_CODE_3029(undefined1 param_1)

{
  char cVar1;
  undefined1 uVar2;
  
  DAT_EXTMEM_0771 = param_1;
  cVar1 = DAT_EXTMEM_0777;
  if (DAT_EXTMEM_0777 == '\0') {
    cVar1 = DAT_EXTMEM_0778;
  }
  if (cVar1 == '\0') {
    uVar2 = FUN_CODE_2bbe(param_1);
    return uVar2;
  }
  return 0;
}


// ===== FUN_CODE_3044  [app]  callers: CODE:3201

undefined1 FUN_CODE_3044(undefined1 param_1)

{
  char cVar1;
  
  cVar1 = DAT_EXTMEM_0777;
  if (DAT_EXTMEM_0777 == '\0') {
    cVar1 = DAT_EXTMEM_0778;
  }
  DAT_EXTMEM_0771 = param_1;
  if (cVar1 == '\0') {
    FUN_CODE_2c5b(param_1);
  }
  return 0;
}


// ===== FUN_CODE_305f  [app]  callers: CODE:3120

byte FUN_CODE_305f(undefined1 param_1)

{
  byte bVar1;
  
  DAT_EXTMEM_0777 = param_1;
  bVar1 = DAT_INTMEM_30 ^ DAT_INTMEM_31;
  if ((bVar1 != 0) || (bVar1 = DAT_EXTMEM_0a84 ^ DAT_EXTMEM_0a85, bVar1 != 0)) {
    return bVar1;
  }
  if ((DAT_EXTMEM_0740 < (byte)-(((DAT_EXTMEM_0741 == '\0') << 7) >> 7)) << 7 < '\0') {
    return 0;
  }
  if (DAT_EXTMEM_073d == '\0') {
    return 0xff;
  }
  return DAT_EXTMEM_073d - 1;
}


// ===== FUN_CODE_30a5  [app]  callers: CODE:3201

void FUN_CODE_30a5(undefined1 param_1,undefined1 param_2,undefined1 param_3,undefined1 param_4,
                  undefined1 param_5,undefined1 param_6)

{
  DAT_EXTMEM_0771 = param_6;
  DAT_EXTMEM_0772 = param_4;
  DAT_EXTMEM_0773 = param_5;
  DAT_EXTMEM_0774 = param_3;
  DAT_EXTMEM_0775 = param_2;
  DAT_EXTMEM_0776 = param_1;
  return;
}


// ===== H_30CE  [app]  callers: 

void H_30CE(undefined1 param_1,undefined1 param_2)

{
  undefined1 uStackX_0;
  undefined1 in_stack_000000fe;
  undefined1 in_stack_000000ff;
  
  FUN_CODE_27d2(uStackX_0,in_stack_000000ff,in_stack_000000fe,0,param_2,param_1);
  return;
}


// ===== FUN_CODE_3120  [app]  callers: CODE:3201

byte FUN_CODE_3120(undefined1 param_1,undefined1 param_2,undefined1 param_3,byte param_4,
                  byte param_5)

{
  byte bVar1;
  
  bVar1 = DAT_EXTMEM_0775;
  if (DAT_EXTMEM_0775 == 0) {
    bVar1 = DAT_EXTMEM_0776;
  }
  DAT_EXTMEM_0771 = param_5;
  DAT_EXTMEM_0772 = param_3;
  DAT_EXTMEM_0773 = param_2;
  DAT_EXTMEM_0774 = param_1;
  if (bVar1 == 0) {
    FUN_CODE_305f(0,0,1);
    if (((param_4 ^ 0x80) < 0x80) << 7 < '\0') {
      return 0;
    }
    bVar1 = DAT_EXTMEM_0771;
    FUN_CODE_2db4(DAT_EXTMEM_0774,DAT_EXTMEM_0773,DAT_EXTMEM_0772);
    bVar1 = bVar1 | param_4;
    if (bVar1 == 0) {
      bVar1 = FUN_CODE_2eb7(DAT_EXTMEM_0774,DAT_EXTMEM_0773,DAT_EXTMEM_0772,DAT_EXTMEM_0771);
    }
  }
  return bVar1;
}


// ===== FUN_CODE_3185  [app]  callers: CODE:813c CODE:4dba

char FUN_CODE_3185(char param_1)

{
  if (param_1 == '\x02') {
    param_1 = '\0';
    if (DAT_EXTMEM_00d7 != '\0') {
      return DAT_EXTMEM_00d7;
    }
  }
  return param_1;
}


// ===== FUN_CODE_31ec  [app]  callers: CODE:3501

void FUN_CODE_31ec(void)

{
  FUN_CODE_059d();
  FUN_CODE_3b7f();
  FUN_CODE_0c96(5);
  DAT_EXTMEM_106c = 0x99;
  thunk_FUN_CODE_e003();
  return;
}


// ===== FUN_CODE_3200  [app]  callers: 

void FUN_CODE_3200(void)

{
  return;
}


// ===== FUN_CODE_3201  [app]  callers: CODE:473f CODE:3a24 CODE:3e32

undefined1
FUN_CODE_3201(undefined1 param_1,undefined1 param_2,char param_3,undefined1 param_4,char param_5)

{
  undefined1 uVar1;
  
  DAT_EXTMEM_0763 = param_5;
  DAT_EXTMEM_0766 = param_1;
  DAT_EXTMEM_0767 = param_2;
  DAT_EXTMEM_0770 = param_4;
  if (param_5 == '\x01') {
    if (param_3 == '\x03') {
      DAT_EXTMEM_0777 = DAT_EXTMEM_076e;
      DAT_EXTMEM_0778 = DAT_EXTMEM_076f;
      uVar1 = FUN_CODE_3029(DAT_EXTMEM_076a,DAT_EXTMEM_0769,DAT_EXTMEM_0768,param_1,param_2,param_4)
      ;
      return uVar1;
    }
  }
  else {
    if (param_5 == '\t') {
      DAT_EXTMEM_0777 = DAT_EXTMEM_076e;
      DAT_EXTMEM_0778 = DAT_EXTMEM_076f;
      uVar1 = FUN_CODE_3044(DAT_EXTMEM_076d,DAT_EXTMEM_076c,DAT_EXTMEM_076b,param_1,param_2,param_4)
      ;
      return uVar1;
    }
    if (param_5 == '\x02') {
      DAT_EXTMEM_0777 = DAT_EXTMEM_076e;
      DAT_EXTMEM_0778 = DAT_EXTMEM_076f;
      FUN_CODE_30a5(DAT_EXTMEM_076d,DAT_EXTMEM_076c,DAT_EXTMEM_076b,param_1,param_2,param_4);
      return 0;
    }
  }
  DAT_EXTMEM_0775 = DAT_EXTMEM_076e;
  DAT_EXTMEM_0776 = DAT_EXTMEM_076f;
  uVar1 = FUN_CODE_3120(DAT_EXTMEM_076a,DAT_EXTMEM_0769,DAT_EXTMEM_0768,param_4);
  return uVar1;
}


// ===== FUN_CODE_32d3  [app]  callers: CODE:3c3e CODE:4f75 CODE:34df CODE:4dba

void FUN_CODE_32d3(void)

{
  DAT_EXTMEM_2f40 = 1;
  return;
}


// ===== FUN_CODE_32da  [app]  callers: CODE:4307

void FUN_CODE_32da(undefined1 param_1)

{
  DAT_EXTMEM_0765 = param_1;
  return;
}


// ===== H_32E7  [app]  callers: 

void H_32E7(void)

{
  return;
}


// ===== FUN_CODE_3300  [app]  callers: 

undefined1 FUN_CODE_3300(undefined1 param_1)

{
  FUN_CODE_0c33();
  _6_5 = 1;
  DAT_EXTMEM_00cf = 1;
  _6_0 = 1;
  if ((DAT_INTMEM_59 != '\0') && (DAT_INTMEM_59 = DAT_INTMEM_59 + -1, DAT_INTMEM_59 == '\0')) {
    DAT_INTMEM_57 = 0xff;
    DAT_INTMEM_58 = 0xff;
  }
  return param_1;
}


// ===== FUN_CODE_3312  [app]  callers: CODE:3626

undefined1 FUN_CODE_3312(void)

{
  undefined1 in_stack_000000fc;
  
  DAT_EXTMEM_00cf = 1;
  _6_0 = 1;
  if ((DAT_INTMEM_59 != '\0') && (DAT_INTMEM_59 = DAT_INTMEM_59 + -1, DAT_INTMEM_59 == '\0')) {
    DAT_INTMEM_57 = 0xff;
    DAT_INTMEM_58 = 0xff;
  }
  return in_stack_000000fc;
}


// ===== FUN_CODE_3335  [app]  callers: CODE:3501

char FUN_CODE_3335(void)

{
  byte bVar1;
  undefined1 *puVar2;
  char cVar3;
  
  if (10 < DAT_EXTMEM_0c34) {
    DAT_EXTMEM_0c34 = 10;
  }
  cVar3 = '\0';
  if (DAT_EXTMEM_0c33 != '\0') {
    if (DAT_EXTMEM_0c32 == -0x40) {
      DAT_EXTMEM_077f = '\f';
      DAT_EXTMEM_0780 = (undefined1 *)0x35;
      puVar2 = DAT_EXTMEM_0c31;
      for (bVar1 = 0; cVar3 = bVar1 - DAT_EXTMEM_0c34, bVar1 < DAT_EXTMEM_0c34; bVar1 = bVar1 + 1) {
        *puVar2 = *(undefined1 *)CONCAT11(DAT_EXTMEM_077f,DAT_EXTMEM_0780);
        puVar2 = puVar2 + '\x01';
        DAT_EXTMEM_0780 = DAT_EXTMEM_0780 + '\x01';
        if (DAT_EXTMEM_0780 == (undefined1 *)0x0) {
          DAT_EXTMEM_077f = DAT_EXTMEM_077f + '\x01';
        }
      }
    }
    else {
      DAT_EXTMEM_077f = DAT_EXTMEM_0c32;
      DAT_EXTMEM_0780 = DAT_EXTMEM_0c31;
      cVar3 = FUN_CODE_5600(DAT_EXTMEM_0c34,0xc,0x35,DAT_EXTMEM_0c32);
    }
  }
  return cVar3;
}


// ===== FUN_CODE_33af  [app]  callers: CODE:2bbe

void FUN_CODE_33af(undefined1 param_1,undefined1 param_2,undefined1 param_3)

{
  DAT_EXTMEM_077c = param_3;
  DAT_EXTMEM_077d = param_2;
  DAT_EXTMEM_077e = param_1;
  if (DAT_EXTMEM_0c2e == '\0') {
    FUN_CODE_566e(0,0xf,0xff,0xc,0x30);
  }
  else if (DAT_EXTMEM_0c30 == '\a') {
    FUN_CODE_3437();
  }
  else if (DAT_EXTMEM_0c30 == '\x05') {
    FUN_CODE_3701();
  }
  FUN_CODE_5600(0,0x10,0xc,0x2f,DAT_EXTMEM_077d,DAT_EXTMEM_077e);
  return;
}


// ===== FUN_CODE_33ff  [app]  callers: 

void FUN_CODE_33ff(void)

{
  return;
}


// ===== FUN_CODE_3400  [app]  callers: 

undefined1 FUN_CODE_3400(undefined1 param_1)

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


// ===== FUN_CODE_3437  [app]  callers: CODE:33af

void FUN_CODE_3437(void)

{
  bool bVar1;
  byte bVar2;
  byte bVar3;
  char cVar4;
  char cVar5;
  char cVar6;
  undefined1 uVar7;
  
  if (10 < DAT_EXTMEM_0c34) {
    DAT_EXTMEM_0c34 = 10;
  }
  DAT_EXTMEM_077f = DAT_EXTMEM_0c34;
  cVar4 = '\f';
  bVar3 = 0x35;
  cVar5 = DAT_EXTMEM_0c32;
  cVar6 = DAT_EXTMEM_0c31;
  while( true ) {
    bVar2 = DAT_EXTMEM_077f;
    DAT_EXTMEM_077f = DAT_EXTMEM_077f - 1;
    if (bVar2 == 0) break;
    if (DAT_EXTMEM_0c33 == '\0') {
      uVar7 = 0x33;
    }
    else {
      uVar7 = *(undefined1 *)CONCAT11(cVar5,cVar6);
    }
    FUN_CODE_85a7(uVar7,bVar3,cVar4);
    bVar1 = 0xfe < bVar3;
    bVar3 = bVar3 + 1;
    cVar4 = cVar4 - ((bVar1 << 7) >> 7);
    cVar6 = cVar6 + '\x01';
    if (cVar6 == '\0') {
      cVar5 = cVar5 + '\x01';
    }
  }
  return;
}


// ===== FUN_CODE_348d  [app]  callers: CODE:3501

void FUN_CODE_348d(void)

{
  bool bVar1;
  byte bVar2;
  byte bVar3;
  char cVar4;
  char cVar5;
  char cVar6;
  undefined1 uVar7;
  
  if (10 < DAT_EXTMEM_0c34) {
    DAT_EXTMEM_0c34 = 10;
  }
  DAT_EXTMEM_077f = DAT_EXTMEM_0c34;
  cVar4 = '\f';
  bVar3 = 0x35;
  cVar5 = DAT_EXTMEM_0c32;
  cVar6 = DAT_EXTMEM_0c31;
  while( true ) {
    bVar2 = DAT_EXTMEM_077f;
    DAT_EXTMEM_077f = DAT_EXTMEM_077f - 1;
    if (bVar2 == 0) break;
    if (DAT_EXTMEM_0c33 != '\0') {
      uVar7 = FUN_CODE_8561(cVar4);
      *(undefined1 *)CONCAT11(cVar5,cVar6) = uVar7;
    }
    bVar1 = 0xfe < bVar3;
    bVar3 = bVar3 + 1;
    cVar4 = cVar4 - ((bVar1 << 7) >> 7);
    cVar6 = cVar6 + '\x01';
    if (cVar6 == '\0') {
      cVar5 = cVar5 + '\x01';
    }
  }
  return;
}


// ===== FUN_CODE_34df  [app]  callers: CODE:39da CODE:4b88

void FUN_CODE_34df(undefined1 param_1,undefined1 *param_2)

{
  *param_2 = param_1;
  DAT_EXTMEM_2f54 = 0;
  FUN_CODE_32d3();
  DAT_EXTMEM_2f44 = 0x21;
  DAT_EXTMEM_0dd4 = 0;
  return;
}


// ===== thunk_FUN_CODE_4f75  [app]  callers: 

void thunk_FUN_CODE_4f75(void)

{
  FUN_CODE_4f75();
  return;
}


// ===== FUN_CODE_34f7  [app]  callers: CODE:08b8

void FUN_CODE_34f7(undefined1 param_1)

{
  DAT_EXTMEM_0746 = param_1;
  FUN_CODE_7aad();
  return;
}


// ===== FUN_CODE_34ff  [app]  callers: 

void FUN_CODE_34ff(void)

{
  return;
}


// ===== FUN_CODE_3500  [app]  callers: 

void FUN_CODE_3500(void)

{
  return;
}


// ===== FUN_CODE_3501  [app]  callers: CODE:2c5b

undefined1 FUN_CODE_3501(undefined1 param_1,undefined1 param_2,undefined1 param_3)

{
  char cVar1;
  
  FUN_CODE_5600(param_1,0,0x10,param_3,param_2,0xc,0x2f);
  if (DAT_EXTMEM_0c2e == '\0') {
    cVar1 = '0';
    FUN_CODE_56c9(0,0xf,0xc,0x1f,0xc);
    if (cVar1 == '\0') {
      DAT_EXTMEM_0c2e = '\x01';
    }
  }
  else if (DAT_EXTMEM_0c30 == '\x06') {
    FUN_CODE_3335();
  }
  else if (DAT_EXTMEM_0c30 == '\b') {
    FUN_CODE_348d();
  }
  else if (DAT_EXTMEM_0c30 == '\t') {
    FUN_CODE_7f2f();
    FUN_CODE_31ec();
  }
  else if (5 < DAT_EXTMEM_0c30 - 5U) {
    DAT_EXTMEM_0c2e = '\0';
  }
  return 0;
}


// ===== FUN_CODE_3563  [app]  callers: CODE:3ae1 CODE:3b43

char FUN_CODE_3563(undefined1 param_1,undefined1 param_2,undefined1 param_3,byte param_4)

{
  undefined1 uVar1;
  
  DAT_EXTMEM_0785 = param_3;
  DAT_EXTMEM_0786 = param_2;
  DAT_EXTMEM_0787 = param_1;
  DAT_EXTMEM_0788 = param_4;
  **(undefined1 **)
    CONCAT11('\r' - (((0x3cU < (byte)(DAT_EXTMEM_0789 * '\b')) << 7) >> 7),
             DAT_EXTMEM_0789 * '\b' - 0x3d) = 1;
  DAT_EXTMEM_078b = 0;
  while( true ) {
    if (DAT_EXTMEM_0788 <= DAT_EXTMEM_078b) break;
    uVar1 = FUN_CODE_857a(DAT_EXTMEM_078b,DAT_EXTMEM_0787,DAT_EXTMEM_0786,DAT_EXTMEM_0785);
    **(undefined1 **)
      CONCAT11('\r' - (((0x3aU < (byte)(DAT_EXTMEM_0789 * '\b')) << 7) >> 7),
               DAT_EXTMEM_0789 * '\b' - 0x3b) = uVar1;
    DAT_EXTMEM_078b = DAT_EXTMEM_078b + 1;
  }
  return DAT_EXTMEM_078b - DAT_EXTMEM_0788;
}


// ===== FUN_CODE_35dd  [app]  callers: CODE:4f75 CODE:4dba

void FUN_CODE_35dd(void)

{
  if ((DAT_EXTMEM_2f52 >> 2 & 1) != 0) {
    FUN_CODE_39da(0);
    DAT_EXTMEM_2f52 = 4;
  }
  return;
}


// ===== FUN_CODE_35f0  [app]  callers: CODE:3d04

void FUN_CODE_35f0(void)

{
  if ((DAT_EXTMEM_2f41 >> 3 & 1) != 1) {
    return;
  }
  return;
}


// ===== FUN_CODE_35fd  [app]  callers: 

void FUN_CODE_35fd(void)

{
  return;
}


// ===== FUN_CODE_35fe  [app]  callers: 

void FUN_CODE_35fe(void)

{
  return;
}


// ===== FUN_CODE_35ff  [app]  callers: 

void FUN_CODE_35ff(void)

{
  return;
}


// ===== FUN_CODE_3600  [app]  callers: 

void FUN_CODE_3600(void)

{
  return;
}


// ===== FUN_CODE_3601  [app]  callers: CODE:4a35 CODE:3e32

/* WARNING: Instruction at (CODE,0x35b8) overlaps instruction at (CODE,0x35b6)
    */

byte FUN_CODE_3601(undefined1 param_1,char *param_2,undefined1 param_3,undefined1 param_4,
                  byte param_5,byte param_6)

{
  byte bVar1;
  char cVar2;
  char *pcVar3;
  
  DAT_EXTMEM_0779 = 0;
  DAT_EXTMEM_0763 = param_4;
  DAT_EXTMEM_0764 = param_3;
  DAT_EXTMEM_0765 = param_2;
  DAT_EXTMEM_0766 = param_5;
  if (DAT_EXTMEM_0767 == '\x01') {
    FUN_CODE_8850(0x769);
    nop();
    nop();
    while( true ) {
      DAT_SFR_ff = uINTMEM7a;
      **(byte **)CONCAT11('\r' - (((0x3aU < (byte)(DAT_EXTMEM_0789 * '\b')) << 7) >> 7),
                          DAT_EXTMEM_0789 * '\b' - 0x3b) = param_6;
      DAT_EXTMEM_078b = DAT_EXTMEM_078b + 1;
      if (DAT_EXTMEM_0788 <= DAT_EXTMEM_078b) break;
      param_6 = FUN_CODE_857a(DAT_EXTMEM_078b,DAT_EXTMEM_0787,DAT_EXTMEM_0786,DAT_EXTMEM_0785);
    }
    return DAT_EXTMEM_078b - DAT_EXTMEM_0788;
  }
  pcVar3 = (char *)0x769;
  cVar2 = FUN_CODE_8850();
  nop();
  nop();
  if (cVar2 + param_6 != 0) {
    *param_2 = *param_2 + '\x01';
    cVar2 = FUN_CODE_8850(cVar2 + param_6 ^ param_5);
    nop();
    nop();
    bVar1 = P1;
    P1 = bVar1 ^ cVar2 + param_6;
    *param_2 = *param_2 + '\x01';
    FUN_CODE_3312();
    nop();
    nop();
    bVar1 = P1;
    P1 = bVar1 ^ 7;
    BANK2_R2 = 0x88;
    nop();
    DAT_INTMEM_50 = param_1;
    *param_2 = *param_2 + '\x01';
    while ((cVar2 = *pcVar3, *pcVar3 = cVar2 + -1, cVar2 != '\0' &&
           ((*(char *)CONCAT11(DAT_EXTMEM_076f,DAT_EXTMEM_0770) != '\0' ||
            (*(char *)CONCAT11(DAT_EXTMEM_0773,DAT_EXTMEM_0774) != '\0'))))) {
      FUN_CODE_85b9(*(undefined1 *)CONCAT11(DAT_EXTMEM_076b,DAT_EXTMEM_076c),DAT_EXTMEM_0779,
                    DAT_EXTMEM_0765,DAT_EXTMEM_0764,DAT_EXTMEM_0763);
      DAT_EXTMEM_0779 = DAT_EXTMEM_0779 + 1;
      pcVar3 = &DAT_EXTMEM_0766;
    }
    return DAT_EXTMEM_0779;
  }
  if ((param_6 >> 2 & 1) != 0) {
    FUN_CODE_39da();
    param_6 = 4;
    DAT_EXTMEM_2f52 = 4;
  }
  return param_6;
}


// ===== H_3626  [app]  callers: 

char H_3626(byte param_1,undefined1 param_2,char *param_3,byte param_4,char param_5)

{
  undefined1 uVar1;
  char cVar2;
  
  *param_3 = *param_3 + '\x01';
  FUN_CODE_8850(param_1 ^ param_4);
  nop();
  nop();
  uVar1 = P1_0;
  *param_3 = *param_3 + '\x01';
  cVar2 = FUN_CODE_3312();
  nop();
  nop();
  DAT_INTMEM_50 = param_2;
  FUN_CODE_8850(*(undefined1 *)((ushort)(byte)(cVar2 + param_5) + 0x3639),0x775);
  nop();
  nop();
  while( true ) {
    cVar2 = DAT_EXTMEM_0766;
    DAT_EXTMEM_0766 = DAT_EXTMEM_0766 + -1;
    if ((cVar2 == '\0') ||
       ((*(char *)CONCAT11(DAT_EXTMEM_076f,DAT_EXTMEM_0770) == '\0' &&
        (*(char *)CONCAT11(DAT_EXTMEM_0773,DAT_EXTMEM_0774) == '\0')))) break;
    FUN_CODE_85b9(*(undefined1 *)CONCAT11(DAT_EXTMEM_076b,DAT_EXTMEM_076c),DAT_EXTMEM_0779,
                  DAT_EXTMEM_0765,DAT_EXTMEM_0764,DAT_EXTMEM_0763);
    DAT_EXTMEM_0779 = DAT_EXTMEM_0779 + '\x01';
  }
  return DAT_EXTMEM_0779;
}


// ===== FUN_CODE_36cf  [app]  callers: CODE:3d04

void FUN_CODE_36cf(void)

{
  FUN_CODE_85b9(3,1,DAT_EXTMEM_0dea,DAT_EXTMEM_0de9,DAT_EXTMEM_0de8);
  DAT_EXTMEM_2f40 = 3;
  return;
}


// ===== FUN_CODE_36eb  [app]  callers: CODE:267e CODE:26e2 CODE:4f75 CODE:4dba

void FUN_CODE_36eb(void)

{
  return;
}


// ===== FUN_CODE_36fc  [app]  callers: 

void FUN_CODE_36fc(void)

{
  return;
}


// ===== FUN_CODE_36fd  [app]  callers: 

void FUN_CODE_36fd(void)

{
  return;
}


// ===== FUN_CODE_36fe  [app]  callers: 

void FUN_CODE_36fe(void)

{
  return;
}


// ===== FUN_CODE_36ff  [app]  callers: 

void FUN_CODE_36ff(void)

{
  return;
}


// ===== FUN_CODE_3700  [app]  callers: 

void FUN_CODE_3700(void)

{
  return;
}


// ===== FUN_CODE_3701  [app]  callers: CODE:33af

char FUN_CODE_3701(void)

{
  char cVar1;
  char cVar2;
  undefined1 *puVar3;
  char cVar4;
  
  if (10 < DAT_EXTMEM_0c34) {
    DAT_EXTMEM_0c34 = 10;
  }
  if (DAT_EXTMEM_0c33 == '\0') {
    DAT_EXTMEM_0781 = '\f';
    DAT_EXTMEM_0782 = (undefined1 *)0x35;
    DAT_EXTMEM_0783 = 0;
    DAT_EXTMEM_0784 = 0;
    cVar2 = DAT_EXTMEM_0c32;
    puVar3 = DAT_EXTMEM_0c31;
    while (cVar1 = ((DAT_EXTMEM_0784 < DAT_EXTMEM_0c34) << 7) >> 7, cVar4 = DAT_EXTMEM_0783 + cVar1,
          (DAT_EXTMEM_0783 < (byte)-cVar1) << 7 < '\0') {
      *(undefined1 *)CONCAT11(DAT_EXTMEM_0781,DAT_EXTMEM_0782) =
           *(undefined1 *)CONCAT11(cVar2,puVar3);
      DAT_EXTMEM_0782 = DAT_EXTMEM_0782 + '\x01';
      if (DAT_EXTMEM_0782 == (undefined1 *)0x0) {
        DAT_EXTMEM_0781 = DAT_EXTMEM_0781 + '\x01';
      }
      puVar3 = puVar3 + '\x01';
      if (puVar3 == (undefined1 *)0x0) {
        cVar2 = cVar2 + '\x01';
      }
      DAT_EXTMEM_0784 = DAT_EXTMEM_0784 + 1;
      if (DAT_EXTMEM_0784 == 0) {
        DAT_EXTMEM_0783 = DAT_EXTMEM_0783 + 1;
      }
    }
  }
  else if (DAT_EXTMEM_0c32 == -0x40) {
    DAT_EXTMEM_077f = '\f';
    DAT_EXTMEM_0780 = '5';
    DAT_EXTMEM_0783 = 0;
    DAT_EXTMEM_0784 = 0;
    puVar3 = DAT_EXTMEM_0c31;
    while (cVar2 = ((DAT_EXTMEM_0784 < DAT_EXTMEM_0c34) << 7) >> 7, cVar4 = DAT_EXTMEM_0783 + cVar2,
          DAT_EXTMEM_0783 < (byte)-cVar2) {
      *(undefined1 *)CONCAT11(DAT_EXTMEM_077f,DAT_EXTMEM_0780) = *puVar3;
      puVar3 = puVar3 + '\x01';
      DAT_EXTMEM_0780 = DAT_EXTMEM_0780 + '\x01';
      if (DAT_EXTMEM_0780 == '\0') {
        DAT_EXTMEM_077f = DAT_EXTMEM_077f + '\x01';
      }
      DAT_EXTMEM_0784 = DAT_EXTMEM_0784 + 1;
      if (DAT_EXTMEM_0784 == 0) {
        DAT_EXTMEM_0783 = DAT_EXTMEM_0783 + 1;
      }
    }
  }
  else {
    DAT_EXTMEM_0781 = DAT_EXTMEM_0c32;
    DAT_EXTMEM_0782 = DAT_EXTMEM_0c31;
    DAT_EXTMEM_077f = '\f';
    DAT_EXTMEM_0780 = '5';
    cVar4 = FUN_CODE_5600(0,DAT_EXTMEM_0c34,DAT_EXTMEM_0c32,DAT_EXTMEM_0c31);
  }
  return cVar4;
}


// ===== FUN_CODE_3812  [app]  callers: CODE:2c5b

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


// ===== FUN_CODE_399e  [app]  callers: CODE:453b CODE:4445

void FUN_CODE_399e(char param_1,undefined1 param_2,byte param_3)

{
  byte bVar1;
  byte bVar2;
  
  bVar1 = (byte)((ushort)param_3 * 4);
  bVar1 = *(byte *)CONCAT11((char)((ushort)param_3 * 4 >> 8) + ('/' - (((0xbf < bVar1) << 7) >> 7)),
                            bVar1 + 0x40);
  if (param_1 == '\0') {
    bVar1 = bVar1 & 0xf7;
  }
  else {
    bVar1 = bVar1 | 8;
  }
  bVar2 = (byte)((ushort)param_3 * 4);
  DAT_EXTMEM_075e = param_2;
  *(byte *)CONCAT11((char)((ushort)param_3 * 4 >> 8) + ('/' - (((0xbf < bVar2) << 7) >> 7)),
                    bVar2 + 0x40) = bVar1;
  return;
}


// ===== H_39BB  [app]  callers: 

void H_39BB(char param_1,byte param_2,byte param_3)

{
  byte bVar1;
  
  if (param_1 == '\0') {
    param_3 = param_3 & 0xf7;
  }
  else {
    param_3 = param_3 | 8;
  }
  bVar1 = (byte)((ushort)param_2 * 4);
  *(byte *)CONCAT11((char)((ushort)param_2 * 4 >> 8) + ('/' - (((0xbf < bVar1) << 7) >> 7)),
                    bVar1 + 0x40) = param_3;
  return;
}


// ===== FUN_CODE_39da  [app]  callers: CODE:35dd

void FUN_CODE_39da(void)

{
  char cVar1;
  
  cVar1 = FUN_CODE_857a(3,DAT_EXTMEM_0dea,DAT_EXTMEM_0de9,DAT_EXTMEM_0de8);
  if (cVar1 == '\0') {
    FUN_CODE_4b29(0);
    DAT_EXTMEM_2f64 = 1;
    DAT_EXTMEM_2f74 = 1;
    DAT_EXTMEM_2f84 = 1;
    FUN_CODE_34df(0x2f94);
    DAT_EXTMEM_2f52 = 0x18;
    FUN_CODE_85b9(1,3,DAT_EXTMEM_0dea,DAT_EXTMEM_0de9,DAT_EXTMEM_0de8);
    return;
  }
  return;
}


// ===== FUN_CODE_3a24  [app]  callers: CODE:4dba

byte FUN_CODE_3a24(void)

{
  char cVar1;
  byte bVar2;
  
  cVar1 = '\0';
  bVar2 = DAT_EXTMEM_2f44;
  if (((DAT_EXTMEM_2f44 >> 1 & 1) != 1) &&
     (bVar2 = (DAT_EXTMEM_2f45 & 0x50) - 1, (DAT_EXTMEM_2f45 & 0x50) != 0)) {
    DAT_EXTMEM_0768 = 1;
    DAT_EXTMEM_0769 = 0xc;
    DAT_EXTMEM_076a = 0x3f;
    DAT_EXTMEM_076b = 0;
    DAT_EXTMEM_076c = 0;
    DAT_EXTMEM_076d = 0;
    DAT_EXTMEM_076e = 0;
    DAT_EXTMEM_076f = 0;
    FUN_CODE_3201(0,0,0,0);
    bVar2 = cVar1 - 1;
    if (cVar1 != '\0') {
      DAT_EXTMEM_0751 = DAT_EXTMEM_0dd4;
      DAT_EXTMEM_0752 = 1;
      FUN_CODE_3ae1(0x3f,0xc,1,0,cVar1);
      bVar2 = DAT_EXTMEM_0dd4 != '\x01';
      DAT_EXTMEM_0dd4 = bVar2;
    }
  }
  return bVar2;
}


// ===== FUN_CODE_3a88  [app]  callers: CODE:3e32 CODE:3d04

/* WARNING: Removing unreachable block (CODE,0x3aac) */
/* WARNING: Removing unreachable block (CODE,0x3ad2) */

void FUN_CODE_3a88(char param_1)

{
  DAT_EXTMEM_0798 = 0;
  DAT_EXTMEM_0797 = 0;
  DAT_EXTMEM_0796 = 0;
  if (param_1 == DAT_EXTMEM_2f42) {
    return;
  }
  DAT_EXTMEM_2f42 = DAT_EXTMEM_2f42;
  return;
}


// ===== FUN_CODE_3a8e  [app]  callers: CODE:4f75

void FUN_CODE_3a8e(char param_1,char param_2,char param_3,char param_4)

{
  char cVar1;
  
  cVar1 = DAT_EXTMEM_2f42;
  DAT_EXTMEM_0796 = param_3;
  DAT_EXTMEM_0797 = param_2;
  DAT_EXTMEM_0798 = param_1;
  if ((param_1 != '\0' || param_2 != '\0') || param_3 != '\0') {
    FUN_CODE_85a7(0,param_1);
  }
  if (param_4 == cVar1) {
    return;
  }
  if ((cVar1 == '\0') &&
     ((DAT_EXTMEM_0798 != '\0' || DAT_EXTMEM_0797 != '\0') || DAT_EXTMEM_0796 != '\0')) {
    FUN_CODE_85a7(1,DAT_EXTMEM_0798,0);
  }
  return;
}


// ===== FUN_CODE_3ae1  [app]  callers: CODE:3a24

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


// ===== FUN_CODE_3b43  [app]  callers: CODE:3bb9 CODE:3b7f

void FUN_CODE_3b43(char param_1)

{
  byte bVar1;
  
  DAT_EXTMEM_0789 = 0;
  DAT_EXTMEM_078a = param_1 != '\0';
  FUN_CODE_3563();
  if (DAT_EXTMEM_0784 == '\0') {
    bVar1 = DAT_EXTMEM_2f40 & 0xfb | 1;
  }
  else {
    bVar1 = DAT_EXTMEM_2f40 | 5;
  }
  DAT_EXTMEM_2f40 = bVar1 | 2;
  return;
}


// ===== FUN_CODE_3b7f  [app]  callers: CODE:4283 CODE:473f CODE:3e32 CODE:4034 CODE:31ec

void FUN_CODE_3b7f(void)

{
  FUN_CODE_853b(0x7f,0xfd,0x30,0xff,7,1,0,1);
  FUN_CODE_85b9(4,1,DAT_EXTMEM_0dea,DAT_EXTMEM_0de9,DAT_EXTMEM_0de8);
  DAT_EXTMEM_0784 = 1;
  FUN_CODE_3b43(0x7f,7,1,0);
  return;
}


// ===== FUN_CODE_3bb9  [app]  callers: CODE:3d04

void FUN_CODE_3bb9(undefined1 param_1,undefined1 param_2,undefined1 param_3,byte param_4,
                  byte param_5)

{
  char cVar1;
  
  DAT_EXTMEM_076e = 0;
  DAT_EXTMEM_076b = param_3;
  DAT_EXTMEM_076c = param_2;
  DAT_EXTMEM_076d = param_1;
  FUN_CODE_85b9(1,1,DAT_EXTMEM_0dea,DAT_EXTMEM_0de9,DAT_EXTMEM_0de8);
  if (param_5 != 0 || param_4 != 0) {
    DAT_EXTMEM_076e = param_5;
    if ((byte)-(((param_5 < 0x40) << 7) >> 7) <= param_4) {
      DAT_EXTMEM_076e = 0x40;
    }
    FUN_CODE_85b9(DAT_EXTMEM_076e,0xb);
    cVar1 = '?';
    FUN_CODE_5600(0,DAT_EXTMEM_076e,DAT_EXTMEM_076c,DAT_EXTMEM_076d,0xc);
    DAT_EXTMEM_0784 =
         FUN_CODE_857a(0xc,DAT_EXTMEM_0dea,DAT_EXTMEM_0de9,DAT_EXTMEM_0de8,DAT_EXTMEM_076e);
    FUN_CODE_3b43(0x3f,0xc,1);
    if (cVar1 == '\0') {
      return;
    }
  }
  return;
}


// ===== FUN_CODE_3c3e  [app]  callers: CODE:3c58

void FUN_CODE_3c3e(undefined1 param_1,undefined1 param_2,undefined1 param_3,undefined1 param_4)

{
  DAT_EXTMEM_0766 = param_3;
  DAT_EXTMEM_0767 = param_2;
  DAT_EXTMEM_0768 = param_1;
  DAT_EXTMEM_0769 = param_4;
  FUN_CODE_32d3();
  DAT_EXTMEM_2f40 = 3;
  return;
}


// ===== FUN_CODE_3c58  [app]  callers: CODE:3e32

void FUN_CODE_3c58(undefined1 param_1,undefined1 param_2,undefined1 param_3,byte param_4,
                  byte param_5,char param_6)

{
  undefined1 uVar1;
  
  DAT_EXTMEM_0763 = param_3;
  DAT_EXTMEM_0764 = param_2;
  DAT_EXTMEM_0765 = param_1;
  FUN_CODE_85b9(0,0xb,DAT_EXTMEM_0dea,DAT_EXTMEM_0de9,DAT_EXTMEM_0de8);
  FUN_CODE_85b9(2,1);
  if (param_5 != 0 || param_4 != 0) {
    if ((byte)-(((param_5 < 0x40) << 7) >> 7) <= param_4) {
      param_5 = 0x40;
    }
    FUN_CODE_85b9(param_5,0xb,DAT_EXTMEM_0dea,DAT_EXTMEM_0de9,DAT_EXTMEM_0de8);
    uVar1 = FUN_CODE_857a(0xb,DAT_EXTMEM_0dea,DAT_EXTMEM_0de9,DAT_EXTMEM_0de8);
    FUN_CODE_3c3e(DAT_EXTMEM_0765,DAT_EXTMEM_0764,DAT_EXTMEM_0763,uVar1);
    if (param_6 == '\0') {
      return;
    }
  }
  return;
}


// ===== FUN_CODE_3cc8  [app]  callers: CODE:3e32 CODE:4f75 CODE:4dba

void FUN_CODE_3cc8(void)

{
  if (((((DAT_EXTMEM_2f41 & 1) == 0) && ((DAT_EXTMEM_2f41 >> 1 & 1) == 0)) &&
      ((DAT_EXTMEM_2f41 >> 2 & 1) == 0)) && ((DAT_EXTMEM_2f41 >> 3 & 1) == 0)) {
    return;
  }
  DAT_EXTMEM_2f64 = 1;
  return;
}


// ===== FUN_CODE_3cf0  [app]  callers: CODE:408f CODE:493d

/* WARNING: Removing unreachable block (CODE,0x3d43) */
/* WARNING: Removing unreachable block (CODE,0x3d5b) */
/* WARNING: Removing unreachable block (CODE,0x3d61) */
/* WARNING: Removing unreachable block (CODE,0x3dd4) */
/* WARNING: Removing unreachable block (CODE,0x3dd0) */
/* WARNING: Removing unreachable block (CODE,0x3dd6) */
/* WARNING: Removing unreachable block (CODE,0x3d58) */

undefined1 FUN_CODE_3cf0(short param_1)

{
  undefined1 uVar1;
  char cVar2;
  char cVar3;
  
  uVar1 = *(undefined1 *)(param_1 + 3);
  cVar2 = *(char *)(param_1 + 4);
  DAT_EXTMEM_076a = 1;
  FUN_CODE_88b1(6,DAT_EXTMEM_0dea,DAT_EXTMEM_0de9,DAT_EXTMEM_0de8);
  FUN_CODE_86d6(uVar1,9,DAT_EXTMEM_0dea,DAT_EXTMEM_0de9,DAT_EXTMEM_0de8);
  BANK0_R4 = 0xdd;
  BANK0_R5 = 0x3d;
  FUN_CODE_85b9(1,0xc);
  BANK0_R4 = 0xee;
  BANK0_R5 = 0x3d;
  cVar3 = FUN_CODE_8632(9,DAT_EXTMEM_0dea,DAT_EXTMEM_0de9,DAT_EXTMEM_0de8);
  if (cVar3 == '\0' && cVar2 == '\0') {
    cVar2 = '\x01';
    BANK0_R4 = 9;
    BANK0_R5 = 0x3e;
    FUN_CODE_3a88(cVar3);
    if (cVar2 == '\0') {
      BANK0_R4 = 0x1e;
      BANK0_R5 = 0x3e;
      FUN_CODE_85b9(0,1,DAT_EXTMEM_0dea,DAT_EXTMEM_0de9,DAT_EXTMEM_0de8);
    }
    else {
      BANK0_R4 = 0x25;
      BANK0_R5 = 0x3e;
      FUN_CODE_36cf();
    }
  }
  else {
    BANK0_R4 = 0xfa;
    BANK0_R5 = 0x3d;
    FUN_CODE_8881(6);
    BANK0_R4 = 0xfd;
    BANK0_R5 = 0x3d;
    FUN_CODE_3bb9();
  }
  return 0;
}


// ===== FUN_CODE_3cf9  [app]  callers: CODE:473f

/* WARNING: Removing unreachable block (CODE,0x3d43) */
/* WARNING: Removing unreachable block (CODE,0x3d5b) */
/* WARNING: Removing unreachable block (CODE,0x3d61) */
/* WARNING: Removing unreachable block (CODE,0x3dd4) */
/* WARNING: Removing unreachable block (CODE,0x3dd0) */
/* WARNING: Removing unreachable block (CODE,0x3dd6) */
/* WARNING: Removing unreachable block (CODE,0x3d58) */

undefined1 FUN_CODE_3cf9(undefined1 *param_1)

{
  undefined1 uVar1;
  char cVar2;
  char cVar3;
  
  uVar1 = *param_1;
  cVar2 = param_1[1];
  DAT_EXTMEM_076a = 1;
  FUN_CODE_88b1(6,DAT_EXTMEM_0dea,DAT_EXTMEM_0de9,DAT_EXTMEM_0de8);
  FUN_CODE_86d6(uVar1,9,DAT_EXTMEM_0dea,DAT_EXTMEM_0de9,DAT_EXTMEM_0de8);
  BANK0_R4 = 0xdd;
  BANK0_R5 = 0x3d;
  FUN_CODE_85b9(1,0xc);
  BANK0_R4 = 0xee;
  BANK0_R5 = 0x3d;
  cVar3 = FUN_CODE_8632(9,DAT_EXTMEM_0dea,DAT_EXTMEM_0de9,DAT_EXTMEM_0de8);
  if (cVar3 == '\0' && cVar2 == '\0') {
    cVar2 = '\x01';
    BANK0_R4 = 9;
    BANK0_R5 = 0x3e;
    FUN_CODE_3a88(cVar3);
    if (cVar2 == '\0') {
      BANK0_R4 = 0x1e;
      BANK0_R5 = 0x3e;
      FUN_CODE_85b9(0,1,DAT_EXTMEM_0dea,DAT_EXTMEM_0de9,DAT_EXTMEM_0de8);
    }
    else {
      BANK0_R4 = 0x25;
      BANK0_R5 = 0x3e;
      FUN_CODE_36cf();
    }
  }
  else {
    BANK0_R4 = 0xfa;
    BANK0_R5 = 0x3d;
    FUN_CODE_8881(6);
    BANK0_R4 = 0xfd;
    BANK0_R5 = 0x3d;
    FUN_CODE_3bb9();
  }
  return 0;
}


// ===== FUN_CODE_3d04  [app]  callers: CODE:4402 CODE:4256 CODE:4dba

undefined1 FUN_CODE_3d04(char param_1,undefined1 param_2,char param_3,char param_4)

{
  char cVar1;
  bool bVar2;
  byte bVar3;
  byte bVar4;
  char cVar5;
  undefined1 *puVar6;
  
  puVar6 = (undefined1 *)0x0;
  if (DAT_EXTMEM_076a == '\0') {
    cVar5 = FUN_CODE_8632(9,DAT_EXTMEM_0dea,DAT_EXTMEM_0de9,DAT_EXTMEM_0de8);
    if (cVar5 == '\0' && param_1 == '\0') goto LAB_CODE_3ddd;
    FUN_CODE_35f0();
    if (param_4 == '\0') goto LAB_CODE_3ddd;
    cVar1 = DAT_EXTMEM_0dea + 9;
    cVar5 = DAT_EXTMEM_0de9 - (((0xf6 < DAT_EXTMEM_0dea) << 7) >> 7);
    bVar3 = FUN_CODE_8607(DAT_EXTMEM_0de8);
    bVar4 = FUN_CODE_857a(0xb,DAT_EXTMEM_0dea,DAT_EXTMEM_0de9,bVar3);
    FUN_CODE_86b7(param_1 + (((bVar3 < bVar4) << 7) >> 7),bVar3 - bVar4,cVar1,cVar5);
    param_3 = FUN_CODE_857a(0xb,DAT_EXTMEM_0dea,DAT_EXTMEM_0de9,DAT_EXTMEM_0de8);
    FUN_CODE_866a(0,7);
    cVar5 = FUN_CODE_857a(0xc,DAT_EXTMEM_0dea,DAT_EXTMEM_0de9,DAT_EXTMEM_0de8);
    bVar2 = cVar5 != '\x01';
  }
  else {
    FUN_CODE_88b1(6,DAT_EXTMEM_0dea,DAT_EXTMEM_0de9,DAT_EXTMEM_0de8);
    FUN_CODE_86d6(param_2,9,DAT_EXTMEM_0dea,DAT_EXTMEM_0de9,DAT_EXTMEM_0de8);
    puVar6 = &BANK0_R3;
    bVar2 = true;
  }
  puVar6['\x01'] = 0xdd;
  puVar6['\x02'] = 0x3d;
  FUN_CODE_85b9(bVar2,0xc);
  param_1 = param_3;
LAB_CODE_3ddd:
  puVar6['\x01'] = 0xee;
  puVar6['\x02'] = 0x3d;
  cVar5 = FUN_CODE_8632(9,DAT_EXTMEM_0dea,DAT_EXTMEM_0de9,DAT_EXTMEM_0de8);
  if (cVar5 == '\0' && param_1 == '\0') {
    cVar1 = '\x01';
    puVar6['\x01'] = 9;
    puVar6['\x02'] = 0x3e;
    FUN_CODE_3a88(cVar5);
    if (cVar1 == '\0') {
      puVar6['\x01'] = 0x1e;
      puVar6['\x02'] = 0x3e;
      FUN_CODE_85b9(0,1,DAT_EXTMEM_0dea,DAT_EXTMEM_0de9,DAT_EXTMEM_0de8);
    }
    else {
      puVar6['\x01'] = 0x25;
      puVar6['\x02'] = 0x3e;
      FUN_CODE_36cf();
    }
  }
  else {
    puVar6['\x01'] = 0xfa;
    puVar6['\x02'] = 0x3d;
    FUN_CODE_8881(6);
    puVar6['\x01'] = 0xfd;
    puVar6['\x02'] = 0x3d;
    FUN_CODE_3bb9();
  }
  return 0;
}


// ===== FUN_CODE_3e32  [app]  callers: CODE:473f CODE:4dba

void FUN_CODE_3e32(char param_1,undefined1 param_2,char param_3,char param_4)

{
  char cVar1;
  char cVar2;
  byte bVar3;
  char cVar4;
  byte bVar5;
  undefined1 uVar6;
  undefined1 uVar7;
  undefined1 uVar8;
  undefined1 uVar9;
  undefined1 *puVar10;
  
  puVar10 = (undefined1 *)0x0;
  if (DAT_EXTMEM_075e == '\0') {
    cVar4 = FUN_CODE_8632(9,DAT_EXTMEM_0dea,DAT_EXTMEM_0de9,DAT_EXTMEM_0de8);
    if (cVar4 != '\0' || param_1 != '\0') {
      FUN_CODE_3cc8();
      if (param_4 == '\0') {
        param_4 = '\0';
      }
      else {
        bVar5 = DAT_EXTMEM_0dea;
        cVar4 = DAT_EXTMEM_0de9;
        uVar7 = DAT_EXTMEM_0de8;
        FUN_CODE_8881(6);
        uVar6 = FUN_CODE_857a(0xb,DAT_EXTMEM_0dea,DAT_EXTMEM_0de9,DAT_EXTMEM_0de8);
        DAT_EXTMEM_0767 = 0;
        DAT_EXTMEM_0768 = 1;
        FUN_CODE_3601(bVar5,cVar4,uVar7,uVar6);
        cVar4 = FUN_CODE_857a(0xb,DAT_EXTMEM_0dea,DAT_EXTMEM_0de9,DAT_EXTMEM_0de8);
        if (cVar4 != param_4) {
          return;
        }
        FUN_CODE_866a(0,7);
        cVar2 = DAT_EXTMEM_0dea + 9;
        cVar1 = DAT_EXTMEM_0de9 - (((0xf6 < DAT_EXTMEM_0dea) << 7) >> 7);
        bVar5 = FUN_CODE_8607(DAT_EXTMEM_0de8);
        bVar3 = FUN_CODE_857a(0xb,DAT_EXTMEM_0dea,DAT_EXTMEM_0de9);
        param_4 = bVar5 - bVar3;
        param_1 = param_4;
        FUN_CODE_86b7(cVar4 + (((bVar5 < bVar3) << 7) >> 7),cVar2,cVar1);
      }
    }
  }
  else {
    FUN_CODE_88b1(6,DAT_EXTMEM_0dea,DAT_EXTMEM_0de9,DAT_EXTMEM_0de8);
    param_1 = param_3;
    FUN_CODE_86d6(param_2,9,DAT_EXTMEM_0dea,DAT_EXTMEM_0de9,DAT_EXTMEM_0de8);
    puVar10 = &BANK0_R3;
    param_4 = param_3;
  }
  puVar10['\x01'] = 0x41;
  puVar10['\x02'] = 0x3f;
  cVar4 = FUN_CODE_8632(9,DAT_EXTMEM_0dea,DAT_EXTMEM_0de9,DAT_EXTMEM_0de8);
  if (cVar4 == '\0' && param_1 == '\0') {
    puVar10['\x01'] = 0x67;
    puVar10['\x02'] = 0x3f;
    bVar5 = FUN_CODE_8561(DAT_EXTMEM_0ded,DAT_EXTMEM_0dec,DAT_EXTMEM_0deb,cVar4);
    if ((bVar5 & 0x60) == 0x20) {
      puVar10['\x01'] = 0x76;
      puVar10['\x02'] = 0x3f;
      uVar6 = FUN_CODE_857a(3);
      puVar10['\x01'] = 0x7d;
      puVar10['\x02'] = 0x3f;
      uVar7 = FUN_CODE_857a(2);
      puVar10['\x01'] = 0x84;
      puVar10['\x02'] = 0x3f;
      DAT_EXTMEM_0760 = FUN_CODE_857a(7);
      puVar10['\x01'] = 0x8e;
      puVar10['\x02'] = 0x3f;
      DAT_EXTMEM_075f = FUN_CODE_857a(6);
      puVar10['\x01'] = 0x98;
      puVar10['\x02'] = 0x3f;
      DAT_EXTMEM_0762 = FUN_CODE_857a(5);
      puVar10['\x01'] = 0xa2;
      puVar10['\x02'] = 0x3f;
      DAT_EXTMEM_0761 = FUN_CODE_857a(4);
      puVar10['\x01'] = 0xac;
      puVar10['\x02'] = 0x3f;
      uVar8 = FUN_CODE_857a(1);
      puVar10['\x01'] = uVar8;
      puVar10['\x02'] = DAT_EXTMEM_0760;
      puVar10['\x03'] = DAT_EXTMEM_075f;
      DAT_EXTMEM_0768 = 0;
      DAT_EXTMEM_0769 = 0;
      DAT_EXTMEM_076a = 0;
      DAT_EXTMEM_076b = 1;
      DAT_EXTMEM_076c = 0xc;
      DAT_EXTMEM_076d = 0x3f;
      DAT_EXTMEM_076e = DAT_EXTMEM_0762;
      DAT_EXTMEM_076f = DAT_EXTMEM_0761;
      uVar8 = puVar10['\x02'];
      uVar9 = puVar10['\x01'];
      puVar10['\x01'] = 0xb;
      puVar10['\x02'] = 0x40;
      FUN_CODE_3201(uVar8,puVar10['\x03'],uVar6,uVar7,uVar9);
    }
    cVar4 = '\x02';
    puVar10['\x01'] = 0x10;
    puVar10['\x02'] = 0x40;
    FUN_CODE_3a88();
    if (cVar4 == '\0') {
      puVar10['\x01'] = 0x25;
      puVar10['\x02'] = 0x40;
      FUN_CODE_85b9(0,1,DAT_EXTMEM_0dea,DAT_EXTMEM_0de9,DAT_EXTMEM_0de8);
      return;
    }
    puVar10['\x01'] = 0x2b;
    puVar10['\x02'] = 0x40;
    FUN_CODE_3b7f();
    if (cVar4 == '\0') {
      return;
    }
  }
  else {
    puVar10['\x01'] = 0x4d;
    puVar10['\x02'] = 0x3f;
    FUN_CODE_8881(6);
    puVar10['\x01'] = 0x50;
    puVar10['\x02'] = 0x3f;
    FUN_CODE_3c58();
    if (param_4 == '\0') {
      return;
    }
  }
  return;
}


// ===== FUN_CODE_4034  [app]  callers: 

undefined1 FUN_CODE_4034(void)

{
  undefined1 uVar1;
  
  uVar1 = FUN_CODE_857a(2);
  DAT_EXTMEM_0756 = FUN_CODE_857a(3,uVar1);
  FUN_CODE_85a7(uVar1,DAT_EXTMEM_0dea,DAT_EXTMEM_0de9,DAT_EXTMEM_0de8);
  FUN_CODE_3b7f();
  return 0;
}


// ===== FUN_CODE_405d  [app]  callers: 

undefined1 FUN_CODE_405d(char param_1,undefined1 param_2,undefined1 param_3,undefined1 param_4)

{
  ushort uVar1;
  byte bVar2;
  char cVar3;
  undefined1 uVar4;
  byte bVar5;
  
  DAT_EXTMEM_0756 = param_4;
  DAT_EXTMEM_0757 = param_3;
  DAT_EXTMEM_0758 = param_2;
  FUN_CODE_8850(0x759);
  nop();
  nop();
  nop();
  nop();
  DAT_EXTMEM_075d = 0;
  DAT_EXTMEM_075e = 0;
  DAT_EXTMEM_075f = 0;
  DAT_EXTMEM_0760 = 0;
  DAT_EXTMEM_0761 = 0;
  cVar3 = FUN_CODE_857a(3,DAT_EXTMEM_0758,DAT_EXTMEM_0757,DAT_EXTMEM_0756);
  DAT_EXTMEM_0762 = FUN_CODE_857a(2);
  DAT_EXTMEM_0763 = FUN_CODE_857a(6);
  DAT_EXTMEM_0764 = FUN_CODE_857a(7);
  if (cVar3 == '!') {
    DAT_EXTMEM_0760 = 0;
    DAT_EXTMEM_0761 = 9;
    cVar3 = FUN_CODE_8632(4,DAT_EXTMEM_0758,DAT_EXTMEM_0757,DAT_EXTMEM_0756);
    if (cVar3 == '\0' && param_1 == '\0') {
      DAT_EXTMEM_075d = 1;
      DAT_EXTMEM_075e = 9;
      DAT_EXTMEM_075f = 0x99;
    }
  }
  else {
    if (cVar3 != '\"') {
      if (6 < cVar3 - 1U) {
        FUN_CODE_8850();
        nop();
        nop();
        nop();
        return DAT_EXTMEM_075c;
      }
      uVar1 = (ushort)(cVar3 - 1U) * 3;
                    /* WARNING: Could not recover jumptable at 0x40d2. Too many branches */
                    /* WARNING: Treating indirect jump as call */
      uVar4 = (*(code *)(CONCAT11((char)(uVar1 >> 8) + '@',0xd3) + (uVar1 & 0xff)))();
      return uVar4;
    }
    cVar3 = FUN_CODE_8632(4,DAT_EXTMEM_0758,DAT_EXTMEM_0757,DAT_EXTMEM_0756);
    if (cVar3 == '\0' && param_1 == '\0') {
      DAT_EXTMEM_075d = 1;
      DAT_EXTMEM_075e = 10;
      DAT_EXTMEM_075f = 0xa7;
      DAT_EXTMEM_0760 = 0;
      DAT_EXTMEM_0761 = 0xa1;
    }
  }
  bVar2 = DAT_EXTMEM_0764 - (((DAT_EXTMEM_0761 < DAT_EXTMEM_0763 + 1) << 7) >> 7);
  bVar5 = DAT_EXTMEM_0760 - bVar2;
  if (bVar2 <= DAT_EXTMEM_0760) {
    DAT_EXTMEM_0760 = DAT_EXTMEM_0764;
    DAT_EXTMEM_0761 = DAT_EXTMEM_0763;
    bVar5 = DAT_EXTMEM_0763;
  }
  FUN_CODE_3cf0(bVar5,0x75d);
  return DAT_EXTMEM_075c;
}


// ===== H_408F  [app]  callers: 

undefined1 H_408F(char param_1,char param_2)

{
  ushort uVar1;
  byte bVar2;
  undefined1 uVar3;
  char cVar4;
  byte bVar5;
  
  DAT_EXTMEM_0762 = FUN_CODE_857a(2);
  DAT_EXTMEM_0763 = FUN_CODE_857a(6);
  DAT_EXTMEM_0764 = FUN_CODE_857a(7);
  if (param_2 == '!') {
    DAT_EXTMEM_0760 = 0;
    DAT_EXTMEM_0761 = 9;
    cVar4 = FUN_CODE_8632(4,DAT_EXTMEM_0758,DAT_EXTMEM_0757,DAT_EXTMEM_0756);
    if (cVar4 == '\0' && param_1 == '\0') {
      DAT_EXTMEM_075d = 1;
      DAT_EXTMEM_075e = 9;
      DAT_EXTMEM_075f = 0x99;
    }
  }
  else {
    if (param_2 != '\"') {
      if (6 < param_2 - 1U) {
        FUN_CODE_8850();
        nop();
        nop();
        nop();
        return DAT_EXTMEM_075c;
      }
      uVar1 = (ushort)(param_2 - 1U) * 3;
                    /* WARNING: Could not recover jumptable at 0x40d2. Too many branches */
                    /* WARNING: Treating indirect jump as call */
      uVar3 = (*(code *)(CONCAT11((char)(uVar1 >> 8) + '@',0xd3) + (uVar1 & 0xff)))();
      return uVar3;
    }
    cVar4 = FUN_CODE_8632(4,DAT_EXTMEM_0758,DAT_EXTMEM_0757,DAT_EXTMEM_0756);
    if (cVar4 == '\0' && param_1 == '\0') {
      DAT_EXTMEM_075d = 1;
      DAT_EXTMEM_075e = 10;
      DAT_EXTMEM_075f = 0xa7;
      DAT_EXTMEM_0760 = 0;
      DAT_EXTMEM_0761 = 0xa1;
    }
  }
  bVar2 = DAT_EXTMEM_0764 - (((DAT_EXTMEM_0761 < DAT_EXTMEM_0763 + 1) << 7) >> 7);
  bVar5 = DAT_EXTMEM_0760 - bVar2;
  if (bVar2 <= DAT_EXTMEM_0760) {
    DAT_EXTMEM_0760 = DAT_EXTMEM_0764;
    DAT_EXTMEM_0761 = DAT_EXTMEM_0763;
    bVar5 = DAT_EXTMEM_0763;
  }
  FUN_CODE_3cf0(bVar5,0x75d);
  return DAT_EXTMEM_075c;
}


// ===== FUN_CODE_4256  [app]  callers: 

undefined1 FUN_CODE_4256(void)

{
  DAT_EXTMEM_0c3f = FUN_CODE_857a(0xe,DAT_EXTMEM_0dea,DAT_EXTMEM_0de9,DAT_EXTMEM_0de8);
  DAT_EXTMEM_076a = 1;
  FUN_CODE_3d04(0x3f,0xc,1,0,1);
  return 0;
}


// ===== H_427F  [app]  callers: 

void H_427F(void)

{
  return;
}


// ===== FUN_CODE_4283  [app]  callers: 

undefined1 FUN_CODE_4283(void)

{
  undefined1 uVar1;
  
  uVar1 = FUN_CODE_857a(2);
  DAT_EXTMEM_0756 = FUN_CODE_857a(3,uVar1);
  FUN_CODE_85b9(uVar1,0xe,DAT_EXTMEM_0dea,DAT_EXTMEM_0de9,DAT_EXTMEM_0de8);
  FUN_CODE_3b7f();
  return 0;
}


// ===== FUN_CODE_42af  [app]  callers: 

/* WARNING: Instruction at (CODE,0x43c4) overlaps instruction at (CODE,0x43c3)
    */

undefined1 FUN_CODE_42af(char *param_1,undefined1 param_2,undefined1 param_3)

{
  char *pcVar1;
  undefined1 uVar2;
  byte bVar3;
  byte bVar4;
  char cVar5;
  byte *pbVar6;
  
  DAT_EXTMEM_0756 = param_3;
  DAT_EXTMEM_0757 = param_2;
  DAT_EXTMEM_0758 = param_1;
  FUN_CODE_8850(0x759);
  nop();
  nop();
  nop();
  nop();
  DAT_EXTMEM_075d = 0;
  DAT_EXTMEM_075e = 0;
  DAT_EXTMEM_075f = 0;
  DAT_EXTMEM_0760 = 0;
  DAT_EXTMEM_0761 = 0;
  FUN_CODE_853b(0x62,0xfe,0x30,0xff,7,1,0,2);
  pcVar1 = DAT_EXTMEM_0758;
  uVar2 = DAT_EXTMEM_0757;
  bVar3 = FUN_CODE_8561(DAT_EXTMEM_0757,DAT_EXTMEM_0756);
  DAT_EXTMEM_0764 = bVar3 & 0x1f;
  bVar3 = FUN_CODE_857a(5);
  bVar4 = FUN_CODE_857a(4);
  if (DAT_EXTMEM_0764 != 1) {
    if (DAT_EXTMEM_0764 == 2) {
      if (bVar4 == 0 && bVar3 == 0) {
        DAT_EXTMEM_0760 = FUN_CODE_857a(2,DAT_EXTMEM_0dea,DAT_EXTMEM_0de9,DAT_EXTMEM_0de8);
      }
      else {
        DAT_EXTMEM_075d = bVar4 & 0x7f;
        cVar5 = '\a';
        do {
          bVar4 = bVar4 >> 1 | bVar3 << 7;
          cVar5 = cVar5 + -1;
          bVar3 = bVar3 >> 1;
        } while (cVar5 != '\0');
        DAT_EXTMEM_075f = bVar4;
        if ((DAT_EXTMEM_075d < 5) << 7 < '\0') {
          pbVar6 = &DAT_EXTMEM_075d;
        }
        else {
          pbVar6 = &DAT_EXTMEM_0759;
          FUN_CODE_8850(DAT_EXTMEM_075d - 5);
          nop();
          nop();
          nop();
          P0 = *pcVar1;
          *pcVar1 = *pcVar1 + '\x01';
        }
        bVar3 = *pbVar6;
        pbVar6[1] = bVar3;
        bVar4 = bVar3 - 4;
        if ((bVar3 < 4) << 7 < '\0') {
          bVar4 = bVar3;
        }
        bVar4 = FUN_CODE_8850(bVar4,0x759);
        nop();
        nop();
        nop();
        P0 = cVar5;
        bVar3 = CCAP1L;
        CCAP1L = bVar3 ^ bVar4;
        bVar3 = (byte)((ushort)bVar4 * 4);
        if (*(char *)CONCAT11((char)((ushort)bVar4 * 4 >> 8) + ('/' - (((0xbf < bVar3) << 7) >> 7)),
                              bVar3 + 0x40) == '\0') {
          pbVar6 = &DAT_EXTMEM_0759;
          FUN_CODE_8850();
          nop();
          nop();
          nop();
          P0 = pcVar1;
          bVar3 = P1;
          P1 = bVar3 | 7;
        }
        else {
          pbVar6 = &DAT_EXTMEM_075d;
        }
        bVar3 = *pbVar6;
        FUN_CODE_32da(DAT_EXTMEM_075f);
        DAT_EXTMEM_0760 = bVar3;
      }
    }
    else if (DAT_EXTMEM_0764 == 0) {
      cVar5 = FUN_CODE_857a(0x12,DAT_EXTMEM_0dea,DAT_EXTMEM_0de9,DAT_EXTMEM_0de8);
      if (cVar5 == '\0') {
        bVar3 = 0;
      }
      else {
        bVar3 = 2;
      }
      DAT_EXTMEM_0760 = DAT_EXTMEM_098e >> 6 & 1 | bVar3;
    }
    else {
      FUN_CODE_8850(0x759);
      nop();
      nop();
      nop();
      P0 = uVar2;
    }
  }
  DAT_EXTMEM_0762 = DAT_EXTMEM_0760;
  DAT_EXTMEM_0763 = DAT_EXTMEM_0761;
  DAT_EXTMEM_076a = 1;
  FUN_CODE_3d04(0x62,7,1,0,2);
  return DAT_EXTMEM_075c;
}


// ===== H_4307  [app]  callers: 

/* WARNING: Instruction at (CODE,0x43c4) overlaps instruction at (CODE,0x43c3)
    */

undefined1 H_4307(char *param_1,undefined1 param_2,char param_3,char param_4,byte param_5)

{
  byte bVar1;
  char cVar2;
  byte bVar3;
  char in_PSW;
  byte *pbVar4;
  
  bVar1 = param_3 + (param_4 - (in_PSW >> 7));
  if (DAT_EXTMEM_0764 != '\x01') {
    if (DAT_EXTMEM_0764 == '\x02') {
      if (param_5 == 0 && bVar1 == 0) {
        DAT_EXTMEM_0760 = FUN_CODE_857a(2,DAT_EXTMEM_0dea,DAT_EXTMEM_0de9,DAT_EXTMEM_0de8);
      }
      else {
        DAT_EXTMEM_075d = param_5 & 0x7f;
        cVar2 = '\a';
        do {
          param_5 = param_5 >> 1 | bVar1 << 7;
          cVar2 = cVar2 + -1;
          bVar1 = bVar1 >> 1;
        } while (cVar2 != '\0');
        DAT_EXTMEM_075f = param_5;
        if ((DAT_EXTMEM_075d < 5) << 7 < '\0') {
          pbVar4 = &DAT_EXTMEM_075d;
        }
        else {
          pbVar4 = &DAT_EXTMEM_0759;
          FUN_CODE_8850(DAT_EXTMEM_075d - 5);
          nop();
          nop();
          nop();
          P0 = *param_1;
          param_2 = 0x90;
          *param_1 = *param_1 + '\x01';
        }
        bVar1 = *pbVar4;
        pbVar4[1] = bVar1;
        bVar3 = bVar1 - 4;
        if ((bVar1 < 4) << 7 < '\0') {
          bVar3 = bVar1;
        }
        bVar3 = FUN_CODE_8850(bVar3,0x759,param_2);
        nop();
        nop();
        nop();
        P0 = cVar2;
        bVar1 = CCAP1L;
        CCAP1L = bVar1 ^ bVar3;
        bVar1 = (byte)((ushort)bVar3 * 4);
        if (*(char *)CONCAT11((char)((ushort)bVar3 * 4 >> 8) + ('/' - (((0xbf < bVar1) << 7) >> 7)),
                              bVar1 + 0x40) == '\0') {
          pbVar4 = &DAT_EXTMEM_0759;
          FUN_CODE_8850();
          nop();
          nop();
          nop();
          P0 = param_1;
          bVar1 = P1;
          P1 = bVar1 | 7;
        }
        else {
          pbVar4 = &DAT_EXTMEM_075d;
        }
        bVar1 = *pbVar4;
        FUN_CODE_32da(DAT_EXTMEM_075f);
        DAT_EXTMEM_0760 = bVar1;
      }
    }
    else if (DAT_EXTMEM_0764 == '\0') {
      cVar2 = FUN_CODE_857a(0x12,DAT_EXTMEM_0dea,DAT_EXTMEM_0de9,DAT_EXTMEM_0de8);
      if (cVar2 == '\0') {
        bVar1 = 0;
      }
      else {
        bVar1 = 2;
      }
      DAT_EXTMEM_0760 = DAT_EXTMEM_098e >> 6 & 1 | bVar1;
    }
    else {
      FUN_CODE_8850(0x759);
      nop();
      nop();
      nop();
      P0 = param_2;
    }
  }
  DAT_EXTMEM_0762 = DAT_EXTMEM_0760;
  DAT_EXTMEM_0763 = DAT_EXTMEM_0761;
  DAT_EXTMEM_076a = 1;
  FUN_CODE_3d04(0x62,7,1,0,2);
  return DAT_EXTMEM_075c;
}


// ===== FUN_CODE_4402  [app]  callers: 

undefined1 FUN_CODE_4402(void)

{
  FUN_CODE_3d04(0);
  return DAT_EXTMEM_075c;
}


// ===== FUN_CODE_4416  [app]  callers: 

/* WARNING: Instruction at (CODE,0x44fe) overlaps instruction at (CODE,0x44fd)
    */

undefined1 FUN_CODE_4416(char *param_1,undefined1 param_2)

{
  char cVar1;
  byte bVar2;
  byte bVar3;
  char cVar4;
  undefined1 *puVar5;
  undefined2 uVar6;
  
  FUN_CODE_8850(0x756);
  nop();
  nop();
  nop();
  nop();
  DAT_EXTMEM_075a = 0;
  DAT_EXTMEM_075b = 0;
  DAT_EXTMEM_075c = 0;
  DAT_EXTMEM_075d = FUN_CODE_857a(2);
  bVar2 = FUN_CODE_857a(5);
  bVar3 = FUN_CODE_857a(4);
  if (DAT_EXTMEM_075d == '\x01') {
    uVar6 = 0x12;
LAB_CODE_44ec:
    FUN_CODE_85b9(1,uVar6,DAT_EXTMEM_0dea,DAT_EXTMEM_0de9,DAT_EXTMEM_0de8);
    return DAT_EXTMEM_0759;
  }
  if (DAT_EXTMEM_075d != '\0') {
    FUN_CODE_8850(0x756);
    nop();
    nop();
    nop();
    P1 = param_2;
    *param_1 = *param_1 + '\x01';
    return DAT_EXTMEM_0759;
  }
  if (bVar3 == 0 && bVar2 == 0) {
    uVar6 = 2;
    goto LAB_CODE_44ec;
  }
  DAT_EXTMEM_075a = bVar3 & 0x7f;
  cVar1 = '\a';
  do {
    bVar3 = bVar3 >> 1 | bVar2 << 7;
    cVar1 = cVar1 + -1;
    bVar2 = bVar2 >> 1;
  } while (cVar1 != '\0');
  DAT_EXTMEM_075c = bVar3;
  if (4 < DAT_EXTMEM_075a) {
    FUN_CODE_8850(DAT_EXTMEM_075a - 5,0x756);
    nop();
    nop();
    nop();
    P0 = *param_1;
  }
  puVar5 = &DAT_EXTMEM_075a;
  bVar2 = DAT_EXTMEM_075a;
  do {
    puVar5[1] = bVar2;
    cVar4 = (bVar2 < 4) << 7;
    if (cVar4 < '\0') break;
    puVar5 = (undefined1 *)0x756;
    bVar2 = FUN_CODE_8850(bVar2 - 4);
    nop();
    nop();
    nop();
    P0 = cVar1;
  } while (-1 < cVar4);
  bVar3 = (byte)((ushort)bVar2 * 4);
  if ((*(byte *)CONCAT11((char)((ushort)bVar2 * 4 >> 8) + ('/' - (((0xbf < bVar3) << 7) >> 7)),
                         bVar3 + 0x40) & 1) != 1) {
    bVar2 = FUN_CODE_8850();
    nop();
    nop();
    nop();
    P0 = param_1;
    cVar1 = P1_0;
    if (cVar1 == '\0') goto code_c0x44d6;
  }
  bVar2 = DAT_EXTMEM_075c;
code_c0x44d6:
  FUN_CODE_399e(1,bVar2);
  return DAT_EXTMEM_0759;
}


// ===== H_4445  [app]  callers: 

/* WARNING: Instruction at (CODE,0x44fe) overlaps instruction at (CODE,0x44fd)
    */

undefined1 H_4445(char *param_1,char param_2,undefined1 param_3,char param_4,byte param_5)

{
  char cVar1;
  byte bVar2;
  byte bVar3;
  char in_PSW;
  char cVar4;
  undefined1 *puVar5;
  undefined2 uVar6;
  
  bVar2 = param_2 + (param_4 - (in_PSW >> 7));
  if (DAT_EXTMEM_075d == '\x01') {
    uVar6 = 0x12;
LAB_CODE_44ec:
    FUN_CODE_85b9(1,uVar6,DAT_EXTMEM_0dea,DAT_EXTMEM_0de9,DAT_EXTMEM_0de8);
    return DAT_EXTMEM_0759;
  }
  if (DAT_EXTMEM_075d != '\0') {
    FUN_CODE_8850(0x756);
    nop();
    nop();
    nop();
    P1 = param_3;
    *param_1 = *param_1 + '\x01';
    return DAT_EXTMEM_0759;
  }
  if (param_5 == 0 && bVar2 == 0) {
    uVar6 = 2;
    goto LAB_CODE_44ec;
  }
  DAT_EXTMEM_075a = param_5 & 0x7f;
  cVar1 = '\a';
  do {
    param_5 = param_5 >> 1 | bVar2 << 7;
    cVar1 = cVar1 + -1;
    bVar2 = bVar2 >> 1;
  } while (cVar1 != '\0');
  DAT_EXTMEM_075c = param_5;
  if (4 < DAT_EXTMEM_075a) {
    FUN_CODE_8850(DAT_EXTMEM_075a - 5,0x756);
    nop();
    nop();
    nop();
    P0 = *param_1;
  }
  puVar5 = &DAT_EXTMEM_075a;
  bVar2 = DAT_EXTMEM_075a;
  do {
    puVar5[1] = bVar2;
    cVar4 = (bVar2 < 4) << 7;
    if (cVar4 < '\0') break;
    puVar5 = (undefined1 *)0x756;
    bVar2 = FUN_CODE_8850(bVar2 - 4);
    nop();
    nop();
    nop();
    P0 = cVar1;
  } while (-1 < cVar4);
  bVar3 = (byte)((ushort)bVar2 * 4);
  if ((*(byte *)CONCAT11((char)((ushort)bVar2 * 4 >> 8) + ('/' - (((0xbf < bVar3) << 7) >> 7)),
                         bVar3 + 0x40) & 1) != 1) {
    bVar2 = FUN_CODE_8850();
    nop();
    nop();
    nop();
    P0 = param_1;
    cVar1 = P1_0;
    if (cVar1 == '\0') goto code_c0x44d6;
  }
  bVar2 = DAT_EXTMEM_075c;
code_c0x44d6:
  FUN_CODE_399e(1,bVar2);
  return DAT_EXTMEM_0759;
}


// ===== FUN_CODE_450c  [app]  callers: 

/* WARNING: Instruction at (CODE,0x4606) overlaps instruction at (CODE,0x4605)
    */

undefined1 FUN_CODE_450c(char *param_1,undefined1 param_2)

{
  char cVar1;
  byte bVar2;
  byte bVar3;
  byte bVar4;
  undefined1 uVar5;
  short sVar6;
  undefined2 uVar7;
  
  FUN_CODE_8850(0x756);
  nop();
  nop();
  nop();
  nop();
  DAT_EXTMEM_075a = 0;
  DAT_EXTMEM_075b = 0;
  DAT_EXTMEM_075c = 0;
  DAT_EXTMEM_075d = FUN_CODE_857a(2);
  bVar2 = FUN_CODE_857a(5);
  bVar3 = FUN_CODE_857a(4);
  if (DAT_EXTMEM_075d == '\x01') {
    uVar7 = 0x12;
LAB_CODE_45e9:
    FUN_CODE_85b9(0,uVar7,DAT_EXTMEM_0dea,DAT_EXTMEM_0de9,DAT_EXTMEM_0de8);
  }
  else {
    if (DAT_EXTMEM_075d == '\x02') {
      FUN_CODE_8850(0x756);
      nop();
      nop();
      nop();
      P0 = bVar2;
    }
    else if (DAT_EXTMEM_075d == '\0') {
      if (bVar3 != 0 || bVar2 != 0) {
        bVar4 = bVar3 & 0x7f;
        cVar1 = '\a';
        do {
          bVar3 = bVar3 >> 1 | bVar2 << 7;
          cVar1 = cVar1 + -1;
          bVar2 = bVar2 >> 1;
        } while (cVar1 != '\0');
        DAT_EXTMEM_075a = bVar4;
        DAT_EXTMEM_075c = bVar3;
        if (bVar4 < 5) {
          DAT_EXTMEM_075b = bVar4;
          if (3 < bVar4) {
            FUN_CODE_8850(bVar4 - 4,0x756);
            nop();
            nop();
            nop();
            P0 = cVar1;
          }
          bVar2 = (byte)((ushort)bVar4 * 4);
          if ((*(byte *)CONCAT11((char)((ushort)bVar4 * 4 >> 8) +
                                 ('/' - (((0xbf < bVar2) << 7) >> 7)),bVar2 + 0x40) & 1) != 1) {
            FUN_CODE_8850(0x756);
            nop();
            nop();
            nop();
            P0 = param_1;
          }
          FUN_CODE_399e(0,DAT_EXTMEM_075c,DAT_EXTMEM_075a);
          return DAT_EXTMEM_0759;
        }
        sVar6 = 0x756;
        bVar2 = FUN_CODE_8850(bVar4 - 5);
        nop();
        nop();
        nop();
        P0 = *param_1;
                    /* WARNING: Could not recover jumptable at 0x4591. Too many branches */
                    /* WARNING: Treating indirect jump as call */
        uVar5 = (*(code *)(sVar6 + (ushort)bVar2))();
        return uVar5;
      }
      uVar7 = 2;
      goto LAB_CODE_45e9;
    }
    FUN_CODE_8850(0x756);
    nop();
    nop();
    nop();
    P1 = param_2;
    *param_1 = *param_1 + '\x01';
  }
  return DAT_EXTMEM_0759;
}


// ===== H_453B  [app]  callers: 

/* WARNING: Instruction at (CODE,0x4606) overlaps instruction at (CODE,0x4605)
    */

undefined1
H_453B(char *param_1,char param_2,char param_3,undefined1 param_4,char param_5,byte param_6)

{
  char cVar1;
  byte bVar2;
  byte bVar3;
  undefined1 uVar4;
  char in_PSW;
  short sVar5;
  undefined2 uVar6;
  
  bVar2 = param_3 + (param_5 - (in_PSW >> 7));
  if (DAT_EXTMEM_075d == '\x01') {
    uVar6 = 0x12;
LAB_CODE_45e9:
    FUN_CODE_85b9(0,uVar6,DAT_EXTMEM_0dea,DAT_EXTMEM_0de9,DAT_EXTMEM_0de8);
  }
  else {
    if (DAT_EXTMEM_075d == '\x02') {
      FUN_CODE_8850(0x756);
      nop();
      nop();
      nop();
      P0 = bVar2;
      param_2 = param_2 + '\x01';
    }
    else if (DAT_EXTMEM_075d == '\0') {
      if (param_6 != 0 || bVar2 != 0) {
        bVar3 = param_6 & 0x7f;
        cVar1 = '\a';
        do {
          param_6 = param_6 >> 1 | bVar2 << 7;
          cVar1 = cVar1 + -1;
          bVar2 = bVar2 >> 1;
        } while (cVar1 != '\0');
        DAT_EXTMEM_075a = bVar3;
        DAT_EXTMEM_075c = param_6;
        if (bVar3 < 5) {
          DAT_EXTMEM_075b = bVar3;
          if (3 < bVar3) {
            FUN_CODE_8850(bVar3 - 4,0x756);
            nop();
            nop();
            nop();
            P0 = cVar1;
          }
          bVar2 = (byte)((ushort)bVar3 * 4);
          if ((*(byte *)CONCAT11((char)((ushort)bVar3 * 4 >> 8) +
                                 ('/' - (((0xbf < bVar2) << 7) >> 7)),bVar2 + 0x40) & 1) != 1) {
            FUN_CODE_8850(0x756);
            nop();
            nop();
            nop();
            P0 = param_1;
          }
          FUN_CODE_399e(0,DAT_EXTMEM_075c,DAT_EXTMEM_075a);
          return DAT_EXTMEM_0759;
        }
        sVar5 = 0x756;
        bVar2 = FUN_CODE_8850(bVar3 - 5);
        nop();
        nop();
        nop();
        P0 = *param_1;
                    /* WARNING: Could not recover jumptable at 0x4591. Too many branches */
                    /* WARNING: Treating indirect jump as call */
        uVar4 = (*(code *)(sVar5 + (ushort)bVar2))();
        return uVar4;
      }
      uVar6 = 2;
      goto LAB_CODE_45e9;
    }
    FUN_CODE_8850(0x756,param_2);
    nop();
    nop();
    nop();
    P1 = param_4;
    *param_1 = *param_1 + '\x01';
  }
  return DAT_EXTMEM_0759;
}


// ===== FUN_CODE_4614  [app]  callers: CODE:4a35

undefined1 FUN_CODE_4614(undefined1 *param_1,char *param_2,undefined1 param_3,undefined1 param_4)

{
  char *pcVar1;
  byte bVar2;
  undefined1 uVar3;
  undefined1 *puVar4;
  
  DAT_EXTMEM_074f = param_4;
  DAT_EXTMEM_0750 = param_3;
  DAT_EXTMEM_0751 = param_2;
  FUN_CODE_8850(0x752);
  nop();
  nop();
  nop();
  nop();
  pcVar1 = DAT_EXTMEM_0751;
  bVar2 = FUN_CODE_857a(1,DAT_EXTMEM_0750,DAT_EXTMEM_074f);
  if (9 < bVar2) {
    puVar4 = &DAT_EXTMEM_0752;
    FUN_CODE_8850();
    nop();
    nop();
    nop();
    P1 = *param_1;
    *pcVar1 = *pcVar1 + '\x01';
    return puVar4[3];
  }
                    /* WARNING: Could not recover jumptable at 0x4646. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  uVar3 = (*(code *)((ushort)(bVar2 * '\x03') + 0x4647))();
  return uVar3;
}


// ===== FUN_CODE_473f  [app]  callers: CODE:4a35

byte FUN_CODE_473f(undefined1 param_1,undefined1 param_2,undefined1 param_3,undefined1 param_4)

{
  char cVar1;
  undefined1 uVar2;
  undefined1 uVar3;
  char cVar4;
  byte bVar5;
  
  DAT_EXTMEM_0752 = 0;
  DAT_EXTMEM_074f = param_3;
  DAT_EXTMEM_0750 = param_2;
  DAT_EXTMEM_0751 = param_1;
  cVar1 = FUN_CODE_857a(1,param_1,param_2,param_3);
  if (cVar1 == '\x01') {
    uVar2 = FUN_CODE_857a(3,DAT_EXTMEM_0751,DAT_EXTMEM_0750,DAT_EXTMEM_074f);
    uVar3 = FUN_CODE_857a(2);
    DAT_EXTMEM_0756 = FUN_CODE_857a(7);
    DAT_EXTMEM_0755 = FUN_CODE_857a(6);
    DAT_EXTMEM_0758 = FUN_CODE_857a(5);
    DAT_EXTMEM_0757 = FUN_CODE_857a(4);
    cVar4 = FUN_CODE_857a(1);
    DAT_EXTMEM_0768 = 1;
    DAT_EXTMEM_0769 = 0xc;
    DAT_EXTMEM_076a = 0x3f;
    DAT_EXTMEM_076b = 0;
    DAT_EXTMEM_076c = 0;
    DAT_EXTMEM_076d = 0;
    DAT_EXTMEM_076e = DAT_EXTMEM_0758;
    DAT_EXTMEM_076f = DAT_EXTMEM_0757;
    cVar1 = DAT_EXTMEM_0758;
    FUN_CODE_3201(DAT_EXTMEM_0756,DAT_EXTMEM_0755,uVar2,uVar3);
    DAT_EXTMEM_0753 = cVar1;
    DAT_EXTMEM_0754 = cVar4;
    if (cVar4 == '\0' && cVar1 == '\0') {
      DAT_EXTMEM_0752 = 0x9e;
      return 0x9e;
    }
LAB_CODE_48ab:
    FUN_CODE_3cf9(0x753,0x3f,0xc,1);
  }
  else {
    if (cVar1 == '\x02') {
      cVar1 = FUN_CODE_857a(4);
      if (cVar1 == '\0') {
        DAT_EXTMEM_0754 = '\x01';
        uVar3 = 0;
        DAT_EXTMEM_0753 = cVar1;
        FUN_CODE_2d12();
        DAT_EXTMEM_0c3f = uVar3;
        goto LAB_CODE_48ab;
      }
    }
    else if (cVar1 == '\x03') {
      cVar1 = FUN_CODE_857a(4,DAT_EXTMEM_0751,DAT_EXTMEM_0750,DAT_EXTMEM_074f);
      if (cVar1 == '\0') {
        DAT_EXTMEM_0754 = '\x01';
        DAT_EXTMEM_0753 = cVar1;
        FUN_CODE_2d44();
        DAT_EXTMEM_0c3f = param_4;
        goto LAB_CODE_48ab;
      }
LAB_CODE_47e2:
      FUN_CODE_857a(4,DAT_EXTMEM_0751,DAT_EXTMEM_0750,DAT_EXTMEM_074f);
    }
    else if (cVar1 == '\t') {
      bVar5 = FUN_CODE_857a(7,DAT_EXTMEM_0751,DAT_EXTMEM_0750,DAT_EXTMEM_074f);
      DAT_EXTMEM_0756 = bVar5;
      DAT_EXTMEM_0755 = FUN_CODE_857a(6);
      if (((bVar5 ^ 0x80) < 0x81U - (((DAT_EXTMEM_0755 < 0x81) << 7) >> 7)) << 7 < '\0') {
        DAT_EXTMEM_075e = 1;
        FUN_CODE_3e32(0x3f,0xc,1);
        DAT_EXTMEM_0752 = bVar5;
        return bVar5;
      }
    }
    else if (cVar1 == '\n') {
      cVar1 = FUN_CODE_857a(4,DAT_EXTMEM_0751,DAT_EXTMEM_0750,DAT_EXTMEM_074f);
      if (cVar1 == '\0') {
        DAT_EXTMEM_0951 = FUN_CODE_857a(3);
        FUN_CODE_2cf0(DAT_EXTMEM_0951,0);
LAB_CODE_492a:
        FUN_CODE_3b7f();
        return DAT_EXTMEM_0752;
      }
    }
    else if (cVar1 == '\v') {
      cVar1 = FUN_CODE_857a(4,DAT_EXTMEM_0751,DAT_EXTMEM_0750,DAT_EXTMEM_074f);
      if (cVar1 == '\0') {
        uVar3 = FUN_CODE_857a(2);
        FUN_CODE_2d36(uVar3);
        goto LAB_CODE_492a;
      }
      goto LAB_CODE_47e2;
    }
    DAT_EXTMEM_0752 = 0x86;
  }
  return DAT_EXTMEM_0752;
}


// ===== FUN_CODE_493d  [app]  callers: CODE:4a35

/* WARNING: Instruction at (CODE,0x49e5) overlaps instruction at (CODE,0x49e3)
    */

undefined1
FUN_CODE_493d(undefined1 *param_1,undefined1 param_2,undefined1 param_3,undefined1 param_4)

{
  byte bVar1;
  char cVar2;
  char cVar3;
  char cVar4;
  
  DAT_EXTMEM_074f = param_4;
  DAT_EXTMEM_0750 = param_3;
  DAT_EXTMEM_0751 = param_2;
  FUN_CODE_8850(0x752);
  nop();
  nop();
  nop();
  nop();
  DAT_EXTMEM_0756 = '\0';
  DAT_EXTMEM_0757 = '\0';
  DAT_EXTMEM_0758 = '\0';
  DAT_EXTMEM_0759 = 0;
  DAT_EXTMEM_075a = 0;
  DAT_EXTMEM_075b = 1;
  DAT_EXTMEM_075d = FUN_CODE_857a(7,DAT_EXTMEM_0751,DAT_EXTMEM_0750,DAT_EXTMEM_074f);
  DAT_EXTMEM_075c = FUN_CODE_857a(6);
  cVar2 = FUN_CODE_857a(5);
  cVar3 = FUN_CODE_857a(4);
  cVar4 = FUN_CODE_857a(1);
  if (((cVar4 == '\x7f') && (cVar3 == '\x05' && cVar2 == '\0')) &&
     (cVar3 = FUN_CODE_8561(DAT_EXTMEM_0751,DAT_EXTMEM_0750,DAT_EXTMEM_074f), cVar3 == -0x3f)) {
    DAT_EXTMEM_0756 = '\x01';
    DAT_EXTMEM_0757 = '\n';
    DAT_EXTMEM_0758 = '\x1f';
  }
  else {
    FUN_CODE_8850(0x752);
    nop();
    nop();
    nop();
    P0 = *param_1;
    bVar1 = P1;
    P1 = bVar1 | 7;
  }
  DAT_EXTMEM_0759 = DAT_EXTMEM_075d;
  DAT_EXTMEM_075a = DAT_EXTMEM_075c;
  if (DAT_EXTMEM_075c == '\0' && DAT_EXTMEM_075d == '\0') {
    DAT_EXTMEM_075a = '\x01';
    DAT_EXTMEM_0759 = '\0';
  }
  if ((DAT_EXTMEM_0758 == '\0' && DAT_EXTMEM_0757 == '\0') && DAT_EXTMEM_0756 == '\0') {
    DAT_EXTMEM_0756 = '\x01';
    DAT_EXTMEM_0757 = '\a';
    DAT_EXTMEM_0758 = '[';
  }
  FUN_CODE_3cf0(0x756);
  return DAT_EXTMEM_0755;
}


// ===== FUN_CODE_4a35  [app]  callers: CODE:4dba

char FUN_CODE_4a35(byte param_1)

{
  byte bVar1;
  char cVar2;
  byte bVar3;
  undefined1 uVar4;
  
  DAT_EXTMEM_074b = 0;
  DAT_EXTMEM_074c = 1;
  DAT_EXTMEM_074d = '\f';
  DAT_EXTMEM_074e = 0x3f;
  DAT_EXTMEM_0768 = 1;
  DAT_EXTMEM_0767 = param_1;
  FUN_CODE_3601(1,0x40);
  cVar2 = param_1 - 8;
  if (7 < param_1) {
    bVar1 = 0xee;
    cVar2 = (DAT_EXTMEM_074d - ((CARRY1(DAT_EXTMEM_074e,param_1) << 7) >> 7)) +
            (-1 - (((7 < DAT_EXTMEM_074e + param_1) << 7) >> 7));
    FUN_CODE_5600(cVar2,0,8,cVar2,(DAT_EXTMEM_074e + param_1) - 8,0xd);
    DAT_EXTMEM_0deb = 1;
    DAT_EXTMEM_0dec = 0xd;
    DAT_EXTMEM_0ded = 0xee;
    bVar3 = FUN_CODE_8561(0xee,0xd,1);
    if ((bVar3 & 0x60) == 0) {
      FUN_CODE_4614();
      DAT_EXTMEM_074b = bVar1;
    }
    else {
      bVar1 = FUN_CODE_8561(DAT_EXTMEM_0ded,DAT_EXTMEM_0dec,DAT_EXTMEM_0deb);
      bVar1 = bVar1 & 0x60;
      if (bVar1 == 0x20) {
        FUN_CODE_473f();
        DAT_EXTMEM_074b = bVar1;
      }
      else {
        bVar1 = FUN_CODE_8561(DAT_EXTMEM_0ded,DAT_EXTMEM_0dec,DAT_EXTMEM_0deb);
        bVar1 = bVar1 & 0x60;
        if (bVar1 == 0x40) {
          FUN_CODE_493d();
          DAT_EXTMEM_074b = bVar1;
        }
        else {
          DAT_EXTMEM_074b = 0x85;
        }
      }
    }
    if (DAT_EXTMEM_074b == 0) {
      uVar4 = 1;
    }
    else {
      uVar4 = 2;
    }
    cVar2 = FUN_CODE_85b9(uVar4,4,DAT_EXTMEM_0dea,DAT_EXTMEM_0de9,DAT_EXTMEM_0de8);
  }
  return cVar2;
}


// ===== FUN_CODE_4b29  [app]  callers: CODE:4dba CODE:39da CODE:50ac

void FUN_CODE_4b29(char param_1)

{
  FUN_CODE_85b9(0,3,DAT_EXTMEM_0dea,DAT_EXTMEM_0de9,DAT_EXTMEM_0de8);
  FUN_CODE_85b9(0,2);
  FUN_CODE_85b9(0,4);
  FUN_CODE_85b9(0,2);
  FUN_CODE_85b9(0,1);
  FUN_CODE_85b9(0,5);
  FUN_CODE_86d6(0xf,0);
  FUN_CODE_85b9(0,0x11);
  if (param_1 == '\0') {
    FUN_CODE_85b9(0,0x12,DAT_EXTMEM_0dea,DAT_EXTMEM_0de9,DAT_EXTMEM_0de8);
  }
  FUN_CODE_2d36(1);
  return;
}


// ===== FUN_CODE_4b88  [app]  callers: CODE:50ac

void FUN_CODE_4b88(void)

{
  DAT_EXTMEM_2fe0 = 2;
  FUN_CODE_0c96(1);
  DAT_EXTMEM_2fe4 = DAT_EXTMEM_2fe4 & 0xef;
  DAT_EXTMEM_2fe8 = DAT_EXTMEM_2fe8 & 0xef;
  DAT_EXTMEM_2fe0 = 0;
  DAT_EXTMEM_2f50 = 0x71;
  DAT_EXTMEM_2f52 = 0xd;
  DAT_EXTMEM_2f53 = 0xd;
  FUN_CODE_34df(DAT_EXTMEM_1106 | 0x40);
  DAT_EXTMEM_0dd2 = 1;
  return;
}


// ===== FUN_CODE_4bc4  [app]  callers: CODE:26e2

void FUN_CODE_4bc4(byte param_1)

{
  char cVar1;
  byte bVar2;
  char cVar3;
  
  cVar1 = '\0';
  if (DAT_EXTMEM_0dd2 == '\0') {
    return;
  }
  if (DAT_EXTMEM_0dd3 != '\0') {
    return;
  }
  if ((DAT_EXTMEM_2f52 >> 3 & 1) == 0) {
    cVar3 = FUN_CODE_857a(0x11,DAT_EXTMEM_0dea,DAT_EXTMEM_0de9,DAT_EXTMEM_0de8);
    if (cVar3 == '\0') {
      bVar2 = FUN_CODE_8632(0xf);
      if (0x13U - (((bVar2 < 0x88) << 7) >> 7) <= param_1) {
        cVar1 = '\x01';
        goto LAB_CODE_4c43;
      }
    }
    else {
      bVar2 = FUN_CODE_8632(0xf);
      if ((byte)-(((bVar2 < 8) << 7) >> 7) <= param_1) {
        cVar1 = '\x01';
        goto LAB_CODE_4c43;
      }
    }
    FUN_CODE_866a(0,0xf,1);
  }
  else {
    DAT_EXTMEM_2f52 = 10;
    FUN_CODE_86d6(0xf,0,DAT_EXTMEM_0dea,DAT_EXTMEM_0de9,DAT_EXTMEM_0de8);
    FUN_CODE_85b9(1,0x11);
  }
LAB_CODE_4c43:
  if (DAT_EXTMEM_0891 != '\0') {
    if (DAT_EXTMEM_0800 == '3') {
      cVar3 = -0x80;
    }
    else {
      cVar3 = '\0';
    }
    if (-1 < cVar3) {
      cVar1 = '\0';
    }
  }
  if ((DAT_EXTMEM_08ae != '\0') && (DAT_EXTMEM_0902 != '\x01')) {
    cVar1 = '\0';
  }
  if ((cVar1 != '\0') && (((DAT_EXTMEM_16e0 >> 4 & 1) == 1 || ((DAT_EXTMEM_16e0 >> 5 & 1) != 1)))) {
    cVar1 = '\0';
  }
  if (cVar1 != '\0') {
    DAT_EXTMEM_0dd3 = '\x01';
    DAT_EXTMEM_08ad = 1;
    DAT_EXTMEM_1b06 = 0x80;
    DAT_EXTMEM_111c = 0x80;
    DAT_EXTMEM_111d = DAT_EXTMEM_111d | 0xc0;
    FUN_CODE_7fe5();
    DAT_EXTMEM_1e20 = 0xc0;
    FUN_CODE_813c();
    DAT_EXTMEM_1e20 = 0x80;
    DAT_EXTMEM_1e40 = 3;
    DAT_EXTMEM_111d = DAT_EXTMEM_111d & 0x3f;
    DAT_EXTMEM_1b06 = 0x80;
    DAT_EXTMEM_111c = 0x80;
  }
  return;
}


// ===== FUN_CODE_4dba  [app]  callers: CODE:4f66

void FUN_CODE_4dba(undefined1 param_1,char param_2)

{
  undefined1 uVar1;
  undefined1 uVar2;
  undefined1 uVar3;
  char cVar4;
  char cVar5;
  undefined1 uVar6;
  char *pcVar7;
  
  FUN_CODE_36eb();
  if (param_2 == '\0') {
    if ((DAT_EXTMEM_2f52 >> 2 & 1) != 0) {
      FUN_CODE_35dd();
      return;
    }
    FUN_CODE_85b9(0,3,DAT_EXTMEM_0dea,DAT_EXTMEM_0de9,DAT_EXTMEM_0de8);
    DAT_EXTMEM_2f53 = 5;
    cVar4 = FUN_CODE_857a(1);
    if (cVar4 == '\0') {
      FUN_CODE_3a24();
    }
    if ((DAT_EXTMEM_2f40 >> 1 & 1) != 0) {
      return;
    }
    cVar4 = DAT_EXTMEM_2f42;
    FUN_CODE_85b9(DAT_EXTMEM_2f42,5,DAT_EXTMEM_0dea,DAT_EXTMEM_0de9,DAT_EXTMEM_0de8);
    if ((DAT_EXTMEM_2f41 >> 5 & 1) != 0) {
      FUN_CODE_85b9(0,4);
      FUN_CODE_85b9(0,1);
      FUN_CODE_32d3();
      return;
    }
    cVar5 = FUN_CODE_857a(5);
    if (cVar5 == '\x01') {
      uVar1 = DAT_EXTMEM_0dea;
      uVar2 = DAT_EXTMEM_0de9;
      uVar3 = DAT_EXTMEM_0de8;
      cVar4 = FUN_CODE_857a(1);
      if (cVar4 == '\x04') {
        cVar4 = FUN_CODE_8561();
        if (cVar4 == '\0') {
          return;
        }
        DAT_EXTMEM_2f54 = cVar4;
        FUN_CODE_85a7(0);
        return;
      }
      if (cVar4 == '\0') {
        return;
      }
      cVar4 = FUN_CODE_857a(1);
      if (cVar4 == '\x02') {
        return;
      }
      FUN_CODE_8881(6);
      uVar6 = FUN_CODE_8632(9,DAT_EXTMEM_0dea,DAT_EXTMEM_0de9,DAT_EXTMEM_0de8);
      DAT_EXTMEM_076a = 0;
      FUN_CODE_3d04(uVar1,uVar2,uVar3,param_1,uVar6);
      FUN_CODE_8844(0x747);
    }
    else if (cVar5 == '\x02') {
      uVar1 = DAT_EXTMEM_0dea;
      uVar2 = DAT_EXTMEM_0de9;
      uVar3 = DAT_EXTMEM_0de8;
      cVar4 = FUN_CODE_857a(1);
      if (cVar4 != '\x03') {
        if (cVar4 == '\0') {
          return;
        }
        if (cVar4 == '\x01') {
          FUN_CODE_85b9(0,1);
          return;
        }
        FUN_CODE_8881(6);
        uVar6 = FUN_CODE_8632(9,DAT_EXTMEM_0dea,DAT_EXTMEM_0de9,DAT_EXTMEM_0de8);
        DAT_EXTMEM_075e = 0;
        FUN_CODE_3e32(uVar1,uVar2,uVar3,param_1,uVar6);
        FUN_CODE_8844(0x747,0,0,0);
        FUN_CODE_8820(0,0,0,0);
      }
    }
    else if ((cVar5 == '\0') && ((DAT_EXTMEM_2f62 != '\0' || (DAT_EXTMEM_2f63 != '\0')))) {
      FUN_CODE_85b9(0,1);
      FUN_CODE_3cc8();
      if (cVar4 == '\0') {
        FUN_CODE_32d3();
      }
      else {
        FUN_CODE_4a35(0);
      }
    }
    cVar4 = FUN_CODE_857a(4,DAT_EXTMEM_0dea,DAT_EXTMEM_0de9,DAT_EXTMEM_0de8);
    if (cVar4 == '\x02') {
      DAT_EXTMEM_2f40 = 0xb;
    }
    return;
  }
  if (DAT_EXTMEM_0dd1 == '\0') {
    return;
  }
  FUN_CODE_36eb();
  if (param_2 != '\0') {
    if (DAT_EXTMEM_0dd0 == '\x02') {
      cVar4 = FUN_CODE_857a(0x12,DAT_EXTMEM_0dea,DAT_EXTMEM_0de9,DAT_EXTMEM_0de8);
      if (cVar4 == '\0') {
        DAT_EXTMEM_0dd1 = 0;
        return;
      }
      cVar4 = '\x02';
      FUN_CODE_3185();
      if (cVar4 == '\x01') {
        DAT_EXTMEM_0dd1 = 0;
        return;
      }
    }
    FUN_CODE_4b29(DAT_EXTMEM_0dd0 != '\0');
    DAT_EXTMEM_0dd3 = 0;
    DAT_EXTMEM_08ad = 0;
    if ((DAT_EXTMEM_0dd0 == '\x02') && ((DAT_EXTMEM_2f52 & 0xf) == 0)) {
      FUN_CODE_059d();
      DAT_EXTMEM_2f50 = 0x4a;
      FUN_CODE_0c96(2);
      DAT_EXTMEM_2f50 = 0x71;
      FUN_CODE_05a4();
      FUN_CODE_0c96(0xf);
      TR1 = 0;
      ET1 = 0;
      nop();
      nop();
      nop();
      nop();
      TH1 = 0;
      TL1 = 1;
      TF1 = 0;
      TR1 = 1;
      do {
        while( true ) {
          cVar4 = TF1;
          if (cVar4 == '\x01') goto LAB_CODE_4d9f;
          if ((DAT_EXTMEM_2f52 >> 1 & 1) == 0) break;
          if (((DAT_EXTMEM_16e0 >> 4 & 1) != 1) && ((DAT_EXTMEM_16e0 >> 5 & 1) != 0)) {
            pcVar7 = &DAT_EXTMEM_00f2;
            goto LAB_CODE_4d9c;
          }
          if ((DAT_EXTMEM_2f52 >> 3 & 1) != 0) {
            pcVar7 = &DAT_EXTMEM_00a2;
            goto LAB_CODE_4d9c;
          }
        }
      } while ((DAT_EXTMEM_2f52 & 0xd) == 0);
      pcVar7 = &DAT_EXTMEM_00a3;
LAB_CODE_4d9c:
      *pcVar7 = *pcVar7 + '\x01';
LAB_CODE_4d9f:
      TR1 = 0;
      TF1 = 0;
      ET1 = 1;
    }
    DAT_EXTMEM_0dd1 = '\0';
    DAT_EXTMEM_2f52 = 10;
    if (DAT_EXTMEM_0dd0 != '\0') {
      FUN_CODE_7feb();
    }
  }
  return;
}


// ===== FUN_CODE_4f66  [app]  callers: CODE:6cf7 CODE:0950

void FUN_CODE_4f66(void)

{
  FUN_CODE_4dba();
  if (DAT_EXTMEM_0dcf != '\0') {
    DAT_EXTMEM_0dcf = '\0';
  }
  return;
}


// ===== FUN_CODE_4f75  [app]  callers: CODE:1f93 CODE:34f4

void FUN_CODE_4f75(char param_1)

{
  char cVar1;
  
  DAT_EXTMEM_0795 = '\0';
  DAT_EXTMEM_1102 = 0x40;
  FUN_CODE_36eb();
  if (param_1 != '\0') {
    DAT_EXTMEM_0dd3 = 0;
    DAT_EXTMEM_08ad = 0;
  }
  if ((DAT_EXTMEM_2f52 >> 2 & 1) != 0) {
    DAT_EXTMEM_2f53 = 1;
    FUN_CODE_35dd();
    goto LAB_CODE_5093;
  }
  if ((DAT_EXTMEM_2f52 & 1) == 1) {
    FUN_CODE_86d6(0xf,0,DAT_EXTMEM_0dea,DAT_EXTMEM_0de9,DAT_EXTMEM_0de8);
    if ((DAT_EXTMEM_2f40 >> 3 & 1) != 0) {
      DAT_EXTMEM_2f40 = DAT_EXTMEM_2f40 & 0xf7;
    }
    DAT_EXTMEM_2f52 = 1;
    if ((DAT_EXTMEM_2f40 >> 1 & 1) == 0) {
      cVar1 = FUN_CODE_857a(1);
      if (cVar1 == '\x03') {
        cVar1 = '\x02';
        FUN_CODE_3a8e(0x95,7,1);
        if (cVar1 == '\0') {
          if (DAT_EXTMEM_0795 != '\0') {
            FUN_CODE_85b9(0,1,DAT_EXTMEM_0dea,DAT_EXTMEM_0de9,DAT_EXTMEM_0de8);
          }
          goto LAB_CODE_5093;
        }
      }
      else {
        cVar1 = FUN_CODE_857a(1,DAT_EXTMEM_0dea,DAT_EXTMEM_0de9,DAT_EXTMEM_0de8);
        if (cVar1 == '\x04') {
          cVar1 = '\x01';
          FUN_CODE_3a8e(0x95,7,1);
          if (cVar1 == '\0') {
            if (DAT_EXTMEM_0795 != '\0') {
              FUN_CODE_85b9(0,1,DAT_EXTMEM_0dea,DAT_EXTMEM_0de9,DAT_EXTMEM_0de8);
            }
LAB_CODE_5093:
            FUN_CODE_2715();
            return;
          }
          cVar1 = FUN_CODE_8561(DAT_EXTMEM_0dea,DAT_EXTMEM_0de9,DAT_EXTMEM_0de8);
          if (cVar1 != '\0') {
            DAT_EXTMEM_2f54 = cVar1;
            FUN_CODE_85a7(0,cVar1);
          }
        }
        else {
          cVar1 = FUN_CODE_857a(1,DAT_EXTMEM_0dea,DAT_EXTMEM_0de9,DAT_EXTMEM_0de8);
          if (((cVar1 == '\0') && (FUN_CODE_3cc8(), param_1 != '\0')) ||
             (cVar1 = FUN_CODE_857a(1,DAT_EXTMEM_0dea,DAT_EXTMEM_0de9,DAT_EXTMEM_0de8),
             cVar1 != '\0')) goto LAB_CODE_5093;
        }
      }
      FUN_CODE_32d3();
      FUN_CODE_85b9(0,1,DAT_EXTMEM_0dea,DAT_EXTMEM_0de9,DAT_EXTMEM_0de8);
    }
  }
  return;
}


// ===== FUN_CODE_50ac  [app]  callers: CODE:6cb3

void FUN_CODE_50ac(void)

{
  DAT_EXTMEM_2033 = DAT_EXTMEM_2033 | 0x80;
  DAT_EXTMEM_1b02 = DAT_EXTMEM_1b02 & 0xbf | 0x80;
  DAT_EXTMEM_1b06 = 0x80;
  DAT_EXTMEM_111c = 0x80;
  DAT_EXTMEM_1b0a = DAT_EXTMEM_1b0a | 0xc0;
  DAT_EXTMEM_0de8 = 1;
  DAT_EXTMEM_0de9 = 0xd;
  DAT_EXTMEM_0dea = 0xd5;
  FUN_CODE_4b29(0);
  FUN_CODE_4b88();
  return;
}


// ===== H_50FC  [app]  callers: 

void H_50FC(void)

{
  if (((DAT_EXTMEM_2f52 & 1) != 1) && ((DAT_EXTMEM_2f52 >> 2 & 1) == 0)) {
    return;
  }
  return;
}


// ===== FUN_CODE_510d  [app]  callers: CODE:26e2 CODE:267e

void FUN_CODE_510d(char param_1)

{
  if ((param_1 == '\x02') && (DAT_EXTMEM_0dd1 != '\0')) {
    return;
  }
  DAT_EXTMEM_0dd1 = 1;
  DAT_EXTMEM_0dcf = 1;
  DAT_EXTMEM_0dd0 = param_1;
  FUN_CODE_2715();
  return;
}


// ===== FUN_CODE_512d  [app]  callers: CODE:26e2

void FUN_CODE_512d(void)

{
  if ((DAT_EXTMEM_2f52 >> 3 & 1) != 0) {
    DAT_EXTMEM_2f52 = 8;
    FUN_CODE_86d6(0xf,0,DAT_EXTMEM_0dea,DAT_EXTMEM_0de9,DAT_EXTMEM_0de8);
    FUN_CODE_85b9(1,0x11);
  }
  return;
}


// ===== H_5187  [app]  callers: 

void H_5187(undefined1 *param_1,char param_2)

{
  char cVar1;
  
  cVar1 = P2_1;
  if (cVar1 == '\0') {
    BANK1_R1 = DAT_INTMEM_5a;
  }
  else {
    P2_1 = 0;
  }
  cVar1 = FUN_CODE_857a(1,param_1[1],*param_1);
  if (cVar1 == '\x04') {
    cVar1 = '\x01';
    FUN_CODE_3a8e(0x95,7,1);
    if (cVar1 != '\0') {
      cVar1 = FUN_CODE_8561(DAT_EXTMEM_0dea,DAT_EXTMEM_0de9,DAT_EXTMEM_0de8);
      if (cVar1 != '\0') {
        DAT_EXTMEM_2f54 = cVar1;
        FUN_CODE_85a7(0,cVar1);
      }
LAB_CODE_5096:
      FUN_CODE_32d3();
      FUN_CODE_85b9(0,1,DAT_EXTMEM_0dea,DAT_EXTMEM_0de9,DAT_EXTMEM_0de8);
      return;
    }
    if (DAT_EXTMEM_0795 != '\0') {
      FUN_CODE_85b9(0,1,DAT_EXTMEM_0dea,DAT_EXTMEM_0de9,DAT_EXTMEM_0de8);
    }
  }
  else {
    cVar1 = FUN_CODE_857a(1,DAT_EXTMEM_0dea,DAT_EXTMEM_0de9,DAT_EXTMEM_0de8);
    if (((cVar1 != '\0') || (FUN_CODE_3cc8(), param_2 == '\0')) &&
       (cVar1 = FUN_CODE_857a(1,DAT_EXTMEM_0dea,DAT_EXTMEM_0de9,DAT_EXTMEM_0de8), cVar1 == '\0'))
    goto LAB_CODE_5096;
  }
  FUN_CODE_2715();
  return;
}


// ===== H_51A2  [app]  callers: 

void H_51A2(undefined1 *param_1,char param_2)

{
  char cVar1;
  
  BANK1_R1 = TH2;
  cVar1 = FUN_CODE_857a(1,param_1[1],*param_1);
  if (cVar1 == '\x04') {
    cVar1 = '\x01';
    FUN_CODE_3a8e(0x95,7,1);
    if (cVar1 != '\0') {
      cVar1 = FUN_CODE_8561(DAT_EXTMEM_0dea,DAT_EXTMEM_0de9,DAT_EXTMEM_0de8);
      if (cVar1 != '\0') {
        DAT_EXTMEM_2f54 = cVar1;
        FUN_CODE_85a7(0,cVar1);
      }
LAB_CODE_5096:
      FUN_CODE_32d3();
      FUN_CODE_85b9(0,1,DAT_EXTMEM_0dea,DAT_EXTMEM_0de9,DAT_EXTMEM_0de8);
      return;
    }
    if (DAT_EXTMEM_0795 != '\0') {
      FUN_CODE_85b9(0,1,DAT_EXTMEM_0dea,DAT_EXTMEM_0de9,DAT_EXTMEM_0de8);
    }
  }
  else {
    cVar1 = FUN_CODE_857a(1,DAT_EXTMEM_0dea,DAT_EXTMEM_0de9,DAT_EXTMEM_0de8);
    if (((cVar1 != '\0') || (FUN_CODE_3cc8(), param_2 == '\0')) &&
       (cVar1 = FUN_CODE_857a(1,DAT_EXTMEM_0dea,DAT_EXTMEM_0de9,DAT_EXTMEM_0de8), cVar1 == '\0'))
    goto LAB_CODE_5096;
  }
  FUN_CODE_2715();
  return;
}


// ===== FUN_CODE_5501  [app]  callers: 

/* WARNING: Instruction at (CODE,0x500c) overlaps instruction at (CODE,0x500a)
    */

byte FUN_CODE_5501(byte param_1,byte *param_2,char *param_3,char param_4,byte param_5,char param_6,
                  byte param_7,char param_8,byte param_9)

{
  undefined1 uVar1;
  char cVar2;
  byte bVar3;
  undefined1 *puVar4;
  char in_PSW;
  undefined2 uVar5;
  
  uVar1 = BANK0_R1;
  puVar4 = (undefined1 *)0x0;
  nop();
  nop();
  nop();
  nop();
  nop();
  nop();
  nop();
  nop();
  nop();
  nop();
  nop();
  nop();
  nop();
  nop();
  nop();
  nop();
  nop();
  nop();
  nop();
  nop();
  nop();
  nop();
  nop();
  nop();
  nop();
  nop();
  nop();
  nop();
  nop();
  nop();
  nop();
  nop();
  nop();
  nop();
  nop();
  nop();
  nop();
  nop();
  nop();
  nop();
  nop();
  nop();
  nop();
  nop();
  nop();
  nop();
  nop();
  nop();
  nop();
  nop();
  nop();
  nop();
  nop();
  nop();
  nop();
  nop();
  nop();
  nop();
  nop();
  nop();
  nop();
  nop();
  nop();
  nop();
  nop();
  nop();
  nop();
  nop();
  nop();
  nop();
  nop();
  nop();
  nop();
  nop();
  nop();
  nop();
  nop();
  nop();
  nop();
  nop();
  nop();
  nop();
  nop();
  nop();
  nop();
  nop();
  nop();
  nop();
  nop();
  nop();
  nop();
  nop();
  nop();
  nop();
  nop();
  nop();
  nop();
  nop();
  nop();
  nop();
  nop();
  nop();
  nop();
  nop();
  nop();
  nop();
  nop();
  nop();
  nop();
  nop();
  nop();
  nop();
  nop();
  nop();
  nop();
  nop();
  nop();
  nop();
  nop();
  nop();
  nop();
  nop();
  nop();
  nop();
  nop();
  nop();
  nop();
  nop();
  nop();
  nop();
  nop();
  nop();
  nop();
  nop();
  nop();
  nop();
  nop();
  nop();
  nop();
  nop();
  nop();
  nop();
  nop();
  nop();
  nop();
  nop();
  nop();
  nop();
  nop();
  nop();
  nop();
  nop();
  nop();
  nop();
  nop();
  nop();
  nop();
  nop();
  nop();
  nop();
  nop();
  nop();
  nop();
  nop();
  nop();
  nop();
  nop();
  nop();
  nop();
  nop();
  nop();
  nop();
  nop();
  nop();
  nop();
  if (in_PSW < '\0') {
    if (param_9 != 0x2f) {
      *param_3 = *param_3 + '\x01';
      bVar3 = param_6 - (((param_9 < 0x2f) << 7) >> 7);
      nop();
      DAT_INTMEM_32 = DAT_INTMEM_32 | param_1 + bVar3 | 7;
      _3_3 = CARRY1(param_1,bVar3);
      DAT_EXTMEM_078b = 0;
      DAT_EXTMEM_078c = 0;
      DAT_EXTMEM_0785 = param_8;
      DAT_EXTMEM_0786 = param_9;
      DAT_EXTMEM_0787 = param_6;
      DAT_EXTMEM_0788 = param_7;
      DAT_EXTMEM_0789 = param_4;
      DAT_EXTMEM_078a = param_5;
      while (bVar3 = DAT_EXTMEM_0789 - (((DAT_EXTMEM_078c < DAT_EXTMEM_078a) << 7) >> 7),
            DAT_EXTMEM_078b < bVar3) {
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
      return DAT_EXTMEM_078b - bVar3;
    }
    BANK2_R5 = BANK0_R1;
    nop();
    BANK0_R1 = 0x95;
    if (param_3['\x05'] != '\t') {
      BANK3_R1 = BANK0_R2;
      nop();
      bVar3 = *param_2;
      *param_2 = bVar3 & 0xfd;
      return bVar3 & 0xfd;
    }
    param_3 = param_3 + '\x06';
    if (param_7 == BANK1_R2) {
      BANK0_R2 = SADEN;
      if (BANK1_R2 <= param_7) {
        if ((param_7 & 1) != 1) {
          BANK0_R1 = 0x95;
          BANK2_R5 = uVar1;
          return param_7;
        }
        FUN_CODE_86d6(0xf,0,DAT_EXTMEM_0dea,DAT_EXTMEM_0de9,DAT_EXTMEM_0de8,param_4);
        if ((DAT_EXTMEM_2f40 >> 3 & 1) != 0) {
          DAT_EXTMEM_2f40 = DAT_EXTMEM_2f40 & 0xf7;
        }
        DAT_EXTMEM_2f52 = 1;
        if ((DAT_EXTMEM_2f40 >> 1 & 1) != 0) {
          DAT_EXTMEM_2f52 = 1;
          return DAT_EXTMEM_2f40;
        }
        cVar2 = FUN_CODE_857a(1);
        if (cVar2 == '\x03') {
          cVar2 = '\x02';
          FUN_CODE_3a8e(0x95,7,1);
          if (cVar2 != '\0') goto LAB_CODE_5096;
          param_3 = DAT_EXTMEM_0dea;
          param_4 = DAT_EXTMEM_0de9;
          param_5 = DAT_EXTMEM_0de8;
          if (DAT_EXTMEM_0795 == '\0') goto LAB_CODE_5093;
          goto code_c0x5005;
        }
      }
      cVar2 = FUN_CODE_857a(1,DAT_EXTMEM_0dea,DAT_EXTMEM_0de9,DAT_EXTMEM_0de8);
      if (cVar2 == '\x04') {
        cVar2 = '\x01';
        FUN_CODE_3a8e(0x95,7,1);
        if (cVar2 != '\0') {
          cVar2 = FUN_CODE_8561(DAT_EXTMEM_0dea,DAT_EXTMEM_0de9,DAT_EXTMEM_0de8);
          if (cVar2 != '\0') {
            DAT_EXTMEM_2f54 = cVar2;
            FUN_CODE_85a7(0,cVar2);
          }
LAB_CODE_5096:
          FUN_CODE_32d3();
          bVar3 = FUN_CODE_85b9(0,1,DAT_EXTMEM_0dea,DAT_EXTMEM_0de9,DAT_EXTMEM_0de8);
          return bVar3;
        }
        if (DAT_EXTMEM_0795 != '\0') {
          FUN_CODE_85b9(0,1,DAT_EXTMEM_0dea,DAT_EXTMEM_0de9,DAT_EXTMEM_0de8);
        }
      }
      else {
        cVar2 = FUN_CODE_857a(1,DAT_EXTMEM_0dea,DAT_EXTMEM_0de9,DAT_EXTMEM_0de8);
        if (((cVar2 != '\0') || (FUN_CODE_3cc8(), param_9 == 0)) &&
           (cVar2 = FUN_CODE_857a(1,DAT_EXTMEM_0dea,DAT_EXTMEM_0de9,DAT_EXTMEM_0de8), cVar2 == '\0')
           ) goto LAB_CODE_5096;
      }
      goto LAB_CODE_5093;
    }
code_c0x5005:
    uVar5 = 1;
    param_9 = 0;
  }
  else {
    uVar5 = 0x410d;
    nop();
    puVar4 = &BANK0_R1;
  }
  puVar4['\x01'] = 0xc;
  puVar4['\x02'] = 0x50;
  FUN_CODE_85b9(param_9,uVar5,param_3,param_4,param_5);
LAB_CODE_5093:
  bVar3 = FUN_CODE_2715();
  return bVar3;
}


// ===== FUN_CODE_5600  [app]  callers: CODE:3335 CODE:3701 CODE:2db4 CODE:3bb9 CODE:33af CODE:4a35 CODE:3501

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


// ===== FUN_CODE_566e  [app]  callers: CODE:2eb7 CODE:33af

char FUN_CODE_566e(char param_1,byte param_2,undefined1 param_3,char param_4,byte param_5)

{
  byte bVar1;
  
  DAT_EXTMEM_0784 = 0;
  DAT_EXTMEM_0785 = 0;
  DAT_EXTMEM_077f = param_4;
  DAT_EXTMEM_0780 = param_5;
  DAT_EXTMEM_0781 = param_3;
  DAT_EXTMEM_0782 = param_1;
  DAT_EXTMEM_0783 = param_2;
  while (bVar1 = DAT_EXTMEM_0782 - (((DAT_EXTMEM_0785 < DAT_EXTMEM_0783) << 7) >> 7),
        DAT_EXTMEM_0784 < bVar1) {
    *(undefined1 *)
     CONCAT11(DAT_EXTMEM_077f +
              (DAT_EXTMEM_0784 - ((CARRY1(DAT_EXTMEM_0780,DAT_EXTMEM_0785) << 7) >> 7)),
              DAT_EXTMEM_0780 + DAT_EXTMEM_0785) = DAT_EXTMEM_0781;
    DAT_EXTMEM_0785 = DAT_EXTMEM_0785 + 1;
    if (DAT_EXTMEM_0785 == 0) {
      DAT_EXTMEM_0784 = DAT_EXTMEM_0784 + 1;
    }
  }
  return DAT_EXTMEM_0784 - bVar1;
}


// ===== FUN_CODE_56c9  [app]  callers: CODE:3501

byte FUN_CODE_56c9(char param_1,byte param_2,char param_3,byte param_4,char param_5,byte param_6)

{
  byte bVar1;
  
  DAT_EXTMEM_077f = param_5;
  DAT_EXTMEM_0780 = param_6;
  DAT_EXTMEM_0781 = param_3;
  DAT_EXTMEM_0782 = param_4;
  DAT_EXTMEM_0783 = param_1;
  DAT_EXTMEM_0784 = param_2;
  DAT_EXTMEM_0785 = 0;
  DAT_EXTMEM_0786 = 0;
  while( true ) {
    bVar1 = param_1 - (((DAT_EXTMEM_0786 < param_2) << 7) >> 7);
    if (bVar1 <= DAT_EXTMEM_0785) {
      return DAT_EXTMEM_0785 - bVar1;
    }
    bVar1 = *(byte *)CONCAT11(param_5 + (DAT_EXTMEM_0785 -
                                        ((CARRY1(param_6,DAT_EXTMEM_0786) << 7) >> 7)),
                              param_6 + DAT_EXTMEM_0786) ^
            *(byte *)CONCAT11(param_3 + (DAT_EXTMEM_0785 -
                                        ((CARRY1(param_4,DAT_EXTMEM_0786) << 7) >> 7)),
                              param_4 + DAT_EXTMEM_0786);
    if (bVar1 != 0) break;
    DAT_EXTMEM_0786 = DAT_EXTMEM_0786 + 1;
    if (DAT_EXTMEM_0786 == 0) {
      DAT_EXTMEM_0785 = DAT_EXTMEM_0785 + 1;
    }
  }
  return bVar1;
}


// ===== H_573E  [app]  callers: 

char H_573E(undefined1 param_1,undefined1 param_2,undefined1 param_3,undefined1 param_4,char param_5
           )

{
  char cVar1;
  byte bVar2;
  
  DAT_EXTMEM_049d = 0;
  DAT_EXTMEM_0490 = param_5;
  DAT_EXTMEM_0491 = param_4;
  DAT_EXTMEM_0492 = param_3;
  DAT_EXTMEM_0493 = param_2;
  DAT_EXTMEM_0494 = param_1;
  do {
    bVar2 = ~DAT_EXTMEM_049a;
    if (bVar2 == 0) {
      bVar2 = ~DAT_EXTMEM_049b;
    }
    if (bVar2 == 0) {
      DAT_EXTMEM_04c5 = 5;
      DAT_EXTMEM_04c6 = 0;
      DAT_EXTMEM_04c7 = 0;
      DAT_EXTMEM_04c8 = 0x10;
      DAT_EXTMEM_04c9 = 2;
      DAT_EXTMEM_04ca = 0;
      DAT_EXTMEM_04cb = 1;
      cVar1 = DAT_EXTMEM_0490;
      FUN_CODE_600d(DAT_EXTMEM_0496,DAT_EXTMEM_00c6);
      if (cVar1 != '\x01') goto LAB_CODE_57d9;
LAB_CODE_57d1:
      DAT_EXTMEM_049c = '\x01';
    }
    else {
      DAT_EXTMEM_04c5 = 5;
      DAT_EXTMEM_04c6 = 0;
      DAT_EXTMEM_04c7 = DAT_EXTMEM_049a;
      DAT_EXTMEM_04c8 = DAT_EXTMEM_049b;
      DAT_EXTMEM_04c9 = 2;
      DAT_EXTMEM_04ca = 0;
      DAT_EXTMEM_04cb = 0;
      cVar1 = DAT_EXTMEM_0490;
      FUN_CODE_600d(DAT_EXTMEM_0496,DAT_EXTMEM_00c6);
      if (cVar1 == '\x01') goto LAB_CODE_57d1;
LAB_CODE_57d9:
      DAT_EXTMEM_049c = '\0';
    }
    if ((DAT_EXTMEM_049c == '\x01') || (DAT_EXTMEM_049d = DAT_EXTMEM_049d + 1, 2 < DAT_EXTMEM_049d))
    {
      return DAT_EXTMEM_049c;
    }
  } while( true );
}


// ===== H_57FB  [app]  callers: 

undefined1 H_57FB(undefined1 param_1,undefined1 param_2,undefined1 param_3,char param_4)

{
  undefined1 uVar1;
  char cVar2;
  
  DAT_EXTMEM_04a3 = 0;
  DAT_EXTMEM_049e = param_4;
  DAT_EXTMEM_049f = param_2;
  DAT_EXTMEM_04a0 = param_3;
  DAT_EXTMEM_04a1 = param_1;
  uVar1 = DAT_EXTMEM_04a2;
  do {
    DAT_EXTMEM_04a2 = uVar1;
    DAT_EXTMEM_04be = DAT_EXTMEM_049f;
    DAT_EXTMEM_04bf = DAT_EXTMEM_04a0;
    cVar2 = DAT_EXTMEM_049e;
    FUN_CODE_5ccf(DAT_EXTMEM_04a1,DAT_EXTMEM_00c6);
    DAT_EXTMEM_04a2 = cVar2 == '\x01';
    if ((bool)DAT_EXTMEM_04a2) {
      return 1;
    }
    DAT_EXTMEM_04a3 = DAT_EXTMEM_04a3 + 1;
    uVar1 = 0;
  } while ((DAT_EXTMEM_04a3 < 3) << 7 < '\0');
  return 0;
}


// ===== H_5859  [app]  callers: 

char H_5859(undefined1 param_1,char param_2,char param_3)

{
  char cVar1;
  
  DAT_EXTMEM_04aa = 0;
  DAT_EXTMEM_04a4 = param_3;
  DAT_EXTMEM_04a5 = param_2;
  DAT_EXTMEM_04a6 = param_1;
  do {
    if (DAT_EXTMEM_04a5 == '\0') {
      DAT_EXTMEM_04d4 = 2;
      DAT_EXTMEM_04d5 = 0;
      cVar1 = DAT_EXTMEM_04a4;
      FUN_CODE_5ed4(DAT_EXTMEM_04a6,DAT_EXTMEM_00c6);
      if (cVar1 != '\x01') goto LAB_CODE_58d1;
LAB_CODE_58c9:
      DAT_EXTMEM_04a9 = '\x01';
    }
    else {
      DAT_EXTMEM_04c5 = 5;
      DAT_EXTMEM_04c6 = 0;
      DAT_EXTMEM_04c7 = 0;
      DAT_EXTMEM_04c8 = DAT_EXTMEM_04a6;
      DAT_EXTMEM_04c9 = 2;
      DAT_EXTMEM_04ca = 0;
      DAT_EXTMEM_04cb = 0;
      cVar1 = DAT_EXTMEM_04a4;
      FUN_CODE_600d(DAT_EXTMEM_04a5,DAT_EXTMEM_00c6);
      if (cVar1 == '\x01') goto LAB_CODE_58c9;
LAB_CODE_58d1:
      DAT_EXTMEM_04a9 = '\0';
    }
    if ((DAT_EXTMEM_04a9 == '\x01') || (DAT_EXTMEM_04aa = DAT_EXTMEM_04aa + 1, 2 < DAT_EXTMEM_04aa))
    {
      return DAT_EXTMEM_04a9;
    }
  } while( true );
}


// ===== H_58F3  [app]  callers: 

undefined1 H_58F3(undefined1 param_1,char param_2)

{
  undefined1 uVar1;
  char cVar2;
  
  DAT_EXTMEM_04ae = 0;
  DAT_EXTMEM_04ab = param_2;
  DAT_EXTMEM_04ac = param_1;
  uVar1 = DAT_EXTMEM_04ad;
  do {
    DAT_EXTMEM_04ad = uVar1;
    DAT_EXTMEM_04d4 = 5;
    DAT_EXTMEM_04d5 = 0xe0;
    cVar2 = DAT_EXTMEM_04ab;
    FUN_CODE_5ed4(DAT_EXTMEM_04ac,DAT_EXTMEM_00c6);
    DAT_EXTMEM_04ad = cVar2 == '\x01';
    if ((bool)DAT_EXTMEM_04ad) {
      return 1;
    }
    DAT_EXTMEM_04ae = DAT_EXTMEM_04ae + 1;
    uVar1 = 0;
  } while ((DAT_EXTMEM_04ae < 3) << 7 < '\0');
  return 0;
}


// ===== H_5946  [app]  callers: 

void H_5946(char param_1,char param_2)

{
  DAT_EXTMEM_1c22 = 0x28;
  DAT_EXTMEM_1c23 = 0x25;
  DAT_EXTMEM_1c24 = 3;
  DAT_EXTMEM_1c25 = 2;
  DAT_EXTMEM_1c26 = 0x19;
  DAT_EXTMEM_1c27 = 0xa5;
  DAT_EXTMEM_1c28 = 1;
  DAT_EXTMEM_1c33 = 0;
  if (param_2 == '\x01') {
    DAT_EXTMEM_1c21 = 0x11;
    DAT_EXTMEM_1c12 = 1;
    DAT_EXTMEM_1c11 = 0xff;
    if (param_1 == '\0') {
      DAT_EXTMEM_1c41 = 0;
    }
    else {
      DAT_EXTMEM_1c41 = 3;
    }
    DAT_EXTMEM_1612 = 0;
    DAT_EXTMEM_1613 = 0;
    DAT_EXTMEM_16e4 = DAT_EXTMEM_16e4 & 0xf3;
    return;
  }
  if (param_2 == '\x02') {
    DAT_EXTMEM_1c32 = 0x11;
    DAT_EXTMEM_1c2a = 1;
    DAT_EXTMEM_1c29 = 0xff;
    if (param_1 == '\0') {
      DAT_EXTMEM_1c42 = 0;
    }
    else {
      DAT_EXTMEM_1c42 = 3;
    }
    DAT_EXTMEM_1640 = 0;
    DAT_EXTMEM_1641 = 0;
    DAT_EXTMEM_16e4 = DAT_EXTMEM_16e4 | 0x10;
  }
  else if (param_2 == '\0') {
    DAT_EXTMEM_1c10 = 0x11;
    DAT_EXTMEM_1c01 = 1;
    DAT_EXTMEM_1c00 = 0xff;
    if (param_1 == '\0') {
      DAT_EXTMEM_1c40 = 0;
    }
    else {
      DAT_EXTMEM_1c40 = 3;
    }
    DAT_EXTMEM_1610 = 0;
    DAT_EXTMEM_1611 = 0;
    DAT_EXTMEM_16e4 = DAT_EXTMEM_16e4 & 0xfc;
    return;
  }
  return;
}


// ===== H_5A36  [app]  callers: 

undefined1 H_5A36(byte param_1,byte param_2,byte param_3,byte param_4)

{
  bool bVar1;
  byte *pbVar2;
  byte bVar3;
  byte bVar4;
  char cVar5;
  char cVar6;
  undefined1 *puVar7;
  
  DAT_EXTMEM_04b7 = 0;
  if (DAT_EXTMEM_04b5 != '\0') {
    DAT_EXTMEM_04ba = 2;
  }
  bVar4 = param_1;
  if (param_1 == 0) {
    bVar4 = param_2;
  }
  DAT_EXTMEM_04af = param_4;
  DAT_EXTMEM_04b0 = param_3;
  DAT_EXTMEM_04b1 = param_1;
  DAT_EXTMEM_04b2 = param_2;
  if ((bVar4 == 0) || (FUN_CODE_0b4b(1), bVar4 = DAT_EXTMEM_04af, param_4 == 0)) {
    DAT_EXTMEM_04b7 = 0;
  }
  else {
    bVar3 = (byte)((ushort)DAT_EXTMEM_04af * 0xf);
    **(undefined1 **)
      CONCAT11((char)((ushort)DAT_EXTMEM_04af * 0xf >> 8) + ('\v' - (((6 < bVar3) << 7) >> 7)),
               bVar3 - 7) = 0x13;
    bVar3 = (byte)((ushort)bVar4 * 0x15);
    **(byte **)CONCAT11((char)((ushort)bVar4 * 0x15 >> 8) + ('\v' - (((0x45 < bVar3) << 7) >> 7)),
                        bVar3 + 0xba) = DAT_EXTMEM_04b0 | 1;
    bVar4 = DAT_EXTMEM_04b1;
    if (DAT_EXTMEM_04b1 == 0) {
      bVar4 = DAT_EXTMEM_04b2 ^ 1;
    }
    if (bVar4 == 0) {
      bVar4 = (byte)((ushort)DAT_EXTMEM_04af * 0x15);
      pbVar2 = *(byte **)CONCAT11((char)((ushort)DAT_EXTMEM_04af * 0x15 >> 8) +
                                  ('\v' - (((0x47 < bVar4) << 7) >> 7)),bVar4 + 0xb8);
      *pbVar2 = *pbVar2 | 0x20;
    }
    bVar4 = (byte)((ushort)DAT_EXTMEM_04af * 0x15);
    **(undefined1 **)
      CONCAT11((char)((ushort)DAT_EXTMEM_04af * 0x15 >> 8) + ('\v' - (((0x47 < bVar4) << 7) >> 7)),
               bVar4 + 0xb8) = 0x5c;
    TR1 = 0;
    ET1 = 0;
    TH1 = 0xb2;
    TL1 = 0x19;
    TF1 = 0;
    TR1 = 1;
    while (cVar5 = TF1, cVar5 == '\0') {
      bVar4 = (byte)((ushort)DAT_EXTMEM_04af * 0x15);
      DAT_EXTMEM_04b6 =
           **(byte **)CONCAT11((char)((ushort)DAT_EXTMEM_04af * 0x15 >> 8) +
                               ('\v' - (((0x41 < bVar4) << 7) >> 7)),bVar4 + 0xbe);
      if ((DAT_EXTMEM_04b6 & 0xfe) != 0) {
        if ((DAT_EXTMEM_04b6 & 0x7c) != 0) {
          if ((DAT_EXTMEM_04b6 & 0x18) != 0) {
            FUN_CODE_0992(DAT_EXTMEM_04af);
          }
          TR1 = 0;
          TF1 = 0;
          break;
        }
        if (-1 < (char)DAT_EXTMEM_04b6) {
          TR1 = 0;
          TF1 = 0;
          bVar4 = DAT_EXTMEM_04b1;
          if (DAT_EXTMEM_04b1 == 0) {
            bVar4 = DAT_EXTMEM_04b2;
          }
          if (bVar4 == 0) {
            DAT_EXTMEM_04b7 = 1;
          }
          break;
        }
        bVar4 = DAT_EXTMEM_04b1;
        if (DAT_EXTMEM_04b1 == 0) {
          bVar4 = DAT_EXTMEM_04b2;
        }
        cVar5 = DAT_EXTMEM_04b4;
        if (bVar4 != 0) {
          bVar4 = (byte)((ushort)DAT_EXTMEM_04af * 0x15);
          *(undefined1 *)CONCAT11(DAT_EXTMEM_04b3,DAT_EXTMEM_04b4) =
               **(undefined1 **)
                 CONCAT11((char)((ushort)DAT_EXTMEM_04af * 0x15 >> 8) +
                          ('\v' - (((0x3b < bVar4) << 7) >> 7)),bVar4 - 0x3c);
          cVar5 = DAT_EXTMEM_04b4 + '\x01';
          if (cVar5 == '\0') {
            DAT_EXTMEM_04b3 = DAT_EXTMEM_04b3 + '\x01';
          }
          bVar1 = DAT_EXTMEM_04b2 != 0;
          DAT_EXTMEM_04b2 = DAT_EXTMEM_04b2 - 1;
          DAT_EXTMEM_04b1 = DAT_EXTMEM_04b1 + (-1 - ((bVar1 << 7) >> 7));
          if ((DAT_EXTMEM_04b5 != '\0') && (DAT_EXTMEM_04ba != 0)) {
            bVar4 = DAT_EXTMEM_04ba - 1;
            puVar7 = (undefined1 *)
                     CONCAT11(DAT_EXTMEM_04b3 + (-1 - (((cVar5 != '\0') << 7) >> 7)),DAT_EXTMEM_04b4
                             );
            cVar6 = DAT_EXTMEM_04ba + 0xb7;
            DAT_EXTMEM_04b4 = cVar5;
            DAT_EXTMEM_04ba = bVar4;
            *(undefined1 *)CONCAT11('\x04' - (((0x47 < bVar4) << 7) >> 7),cVar6) = *puVar7;
            cVar5 = DAT_EXTMEM_04b4;
            if (bVar4 == 0) {
              DAT_EXTMEM_04b1 = DAT_EXTMEM_04b8;
              DAT_EXTMEM_04b2 = DAT_EXTMEM_04b9;
              if ((byte)-(((DAT_EXTMEM_04b9 < 3) << 7) >> 7) <= DAT_EXTMEM_04b8) {
                DAT_EXTMEM_04b2 = DAT_EXTMEM_04b9 - 2;
                DAT_EXTMEM_04b1 = DAT_EXTMEM_04b8 + (-1 - (((1 < DAT_EXTMEM_04b9) << 7) >> 7));
              }
            }
          }
        }
        DAT_EXTMEM_04b4 = cVar5;
        bVar4 = DAT_EXTMEM_04b1;
        if (DAT_EXTMEM_04b1 == 0) {
          bVar4 = DAT_EXTMEM_04b2 ^ 1;
        }
        if (bVar4 == 0) {
          bVar4 = (byte)((ushort)DAT_EXTMEM_04af * 0x15);
          pbVar2 = *(byte **)CONCAT11((char)((ushort)DAT_EXTMEM_04af * 0x15 >> 8) +
                                      ('\v' - (((0x47 < bVar4) << 7) >> 7)),bVar4 + 0xb8);
          *pbVar2 = *pbVar2 | 0x20;
        }
        bVar4 = (byte)((ushort)DAT_EXTMEM_04af * 0x15);
        **(undefined1 **)
          CONCAT11((char)((ushort)DAT_EXTMEM_04af * 0x15 >> 8) +
                   ('\v' - (((0x41 < bVar4) << 7) >> 7)),bVar4 + 0xbe) = 0xfc;
        TH1 = 0xb2;
        TL1 = 0x19;
        TF1 = 0;
      }
    }
    cVar5 = TF1;
    if (cVar5 != '\0') {
      FUN_CODE_0992(DAT_EXTMEM_04af);
    }
    bVar4 = DAT_EXTMEM_04af;
    bVar3 = (byte)((ushort)DAT_EXTMEM_04af * 0xf);
    **(undefined1 **)
      CONCAT11((char)((ushort)DAT_EXTMEM_04af * 0xf >> 8) + ('\v' - (((6 < bVar3) << 7) >> 7)),
               bVar3 - 7) = 0x11;
    bVar3 = (byte)((ushort)bVar4 * 0x15);
    **(undefined1 **)
      CONCAT11((char)((ushort)bVar4 * 0x15 >> 8) + ('\v' - (((0x41 < bVar3) << 7) >> 7)),
               bVar3 + 0xbe) = 0xfe;
    TR1 = 0;
    TF1 = 0;
    ET1 = 1;
  }
  return DAT_EXTMEM_04b7;
}


// ===== FUN_CODE_5ccf  [app]  callers: CODE:57fb

undefined1 FUN_CODE_5ccf(char param_1,undefined1 param_2,byte param_3)

{
  char cVar1;
  byte bVar2;
  byte bVar3;
  
  DAT_EXTMEM_04c1 = 0;
  DAT_EXTMEM_04bb = param_3;
  DAT_EXTMEM_04bc = param_2;
  DAT_EXTMEM_04bd = param_1;
  if (param_1 == '\0') {
    DAT_EXTMEM_04c1 = 0;
  }
  else {
    FUN_CODE_0b4b(1);
    bVar3 = DAT_EXTMEM_04bb;
    if (param_3 == 0) {
      DAT_EXTMEM_04c1 = 0;
    }
    else {
      bVar2 = (byte)((ushort)DAT_EXTMEM_04bb * 0xf);
      **(undefined1 **)
        CONCAT11((char)((ushort)DAT_EXTMEM_04bb * 0xf >> 8) + ('\v' - (((6 < bVar2) << 7) >> 7)),
                 bVar2 - 7) = 0x13;
      bVar2 = (byte)((ushort)bVar3 * 0x15);
      **(undefined1 **)
        CONCAT11((char)((ushort)bVar3 * 0x15 >> 8) + ('\v' - (((0x45 < bVar2) << 7) >> 7)),
                 bVar2 + 0xba) = DAT_EXTMEM_04bc;
      bVar3 = DAT_EXTMEM_04bb;
      bVar2 = (byte)((ushort)DAT_EXTMEM_04bb * 0x15);
      **(undefined1 **)
        CONCAT11((char)((ushort)DAT_EXTMEM_04bb * 0x15 >> 8) + ('\v' - (((0x3b < bVar2) << 7) >> 7))
                 ,bVar2 - 0x3c) = *(undefined1 *)CONCAT11(DAT_EXTMEM_04be,DAT_EXTMEM_04bf);
      bVar2 = (byte)((ushort)bVar3 * 0x15);
      **(undefined1 **)
        CONCAT11((char)((ushort)bVar3 * 0x15 >> 8) + ('\v' - (((0x47 < bVar2) << 7) >> 7)),
                 bVar2 + 0xb8) = 0x5c;
      TR1 = 0;
      ET1 = 0;
      TH1 = 0xb2;
      TL1 = 0x19;
      TF1 = 0;
      TR1 = 1;
      while (cVar1 = TF1, cVar1 == '\0') {
        bVar3 = (byte)((ushort)DAT_EXTMEM_04bb * 0x15);
        DAT_EXTMEM_04c0 =
             **(byte **)CONCAT11((char)((ushort)DAT_EXTMEM_04bb * 0x15 >> 8) +
                                 ('\v' - (((0x41 < bVar3) << 7) >> 7)),bVar3 + 0xbe);
        if ((DAT_EXTMEM_04c0 & 0xfe) != 0) {
          if ((DAT_EXTMEM_04c0 & 0x7c) != 0) {
            if ((DAT_EXTMEM_04c0 & 0x18) != 0) {
              FUN_CODE_0992(DAT_EXTMEM_04bb);
            }
            DAT_EXTMEM_04c1 = 0;
            break;
          }
          if ((DAT_EXTMEM_04c0 >> 1 & 1) != 0) {
            TR1 = 0;
            TF1 = 0;
            if (DAT_EXTMEM_04bd == '\0') {
              DAT_EXTMEM_04c1 = 1;
            }
            break;
          }
          if (DAT_EXTMEM_04bd != '\0') {
            DAT_EXTMEM_04bd = DAT_EXTMEM_04bd + -1;
            if (DAT_EXTMEM_04bd == '\0') {
              bVar3 = (byte)((ushort)DAT_EXTMEM_04bb * 0xf);
              **(undefined1 **)
                CONCAT11((char)((ushort)DAT_EXTMEM_04bb * 0xf >> 8) +
                         ('\v' - (((6 < bVar3) << 7) >> 7)),bVar3 - 7) = 0x11;
            }
            else {
              DAT_EXTMEM_04bf = DAT_EXTMEM_04bf + '\x01';
              if (DAT_EXTMEM_04bf == '\0') {
                DAT_EXTMEM_04be = DAT_EXTMEM_04be + '\x01';
              }
              bVar3 = (byte)((ushort)DAT_EXTMEM_04bb * 0x15);
              **(undefined1 **)
                CONCAT11((char)((ushort)DAT_EXTMEM_04bb * 0x15 >> 8) +
                         ('\v' - (((0x3b < bVar3) << 7) >> 7)),bVar3 - 0x3c) =
                   *(undefined1 *)CONCAT11(DAT_EXTMEM_04be,DAT_EXTMEM_04bf);
            }
            bVar3 = (byte)((ushort)DAT_EXTMEM_04bb * 0x15);
            **(undefined1 **)
              CONCAT11((char)((ushort)DAT_EXTMEM_04bb * 0x15 >> 8) +
                       ('\v' - (((0x41 < bVar3) << 7) >> 7)),bVar3 + 0xbe) = 0xfc;
          }
          TH1 = 0xb2;
          TL1 = 0x19;
          TF1 = 0;
        }
      }
      cVar1 = TF1;
      if (cVar1 != '\0') {
        FUN_CODE_0992(DAT_EXTMEM_04bb);
      }
      bVar3 = DAT_EXTMEM_04bb;
      bVar2 = (byte)((ushort)DAT_EXTMEM_04bb * 0xf);
      **(undefined1 **)
        CONCAT11((char)((ushort)DAT_EXTMEM_04bb * 0xf >> 8) + ('\v' - (((6 < bVar2) << 7) >> 7)),
                 bVar2 - 7) = 0x11;
      bVar2 = (byte)((ushort)bVar3 * 0x15);
      **(undefined1 **)
        CONCAT11((char)((ushort)bVar3 * 0x15 >> 8) + ('\v' - (((0x41 < bVar2) << 7) >> 7)),
                 bVar2 + 0xbe) = 0xfe;
      TR1 = 0;
      TF1 = 0;
      ET1 = 1;
    }
  }
  return DAT_EXTMEM_04c1;
}


// ===== FUN_CODE_5ed4  [app]  callers: CODE:58f3 CODE:5859

char FUN_CODE_5ed4(undefined1 param_1,undefined1 param_2,char param_3)

{
  DAT_EXTMEM_04d1 = param_3;
  DAT_EXTMEM_04d2 = param_2;
  DAT_EXTMEM_04d3 = param_1;
  if (param_3 == '\0') {
    param_3 = FUN_CODE_63e6(DAT_EXTMEM_04d4,DAT_EXTMEM_04d5,param_1,param_2);
  }
  else if (param_3 == '\x01') {
    param_3 = FUN_CODE_64f0(DAT_EXTMEM_04d4,DAT_EXTMEM_04d5,param_1,param_2);
  }
  else if (param_3 == '\x02') {
    param_3 = FUN_CODE_65fa(DAT_EXTMEM_04d4,DAT_EXTMEM_04d5,param_1,0,param_2);
  }
  return param_3;
}


// ===== FUN_CODE_5f2c  [app]  callers: CODE:6841

void FUN_CODE_5f2c(void)

{
  FUN_CODE_8850(0x700);
  nop();
  nop();
  nop();
  nop();
  FUN_CODE_8850(0x708);
  nop();
  nop();
  nop();
  nop();
  return;
}


// ===== FUN_CODE_5f41  [app]  callers: CODE:69ff CODE:8000

void FUN_CODE_5f41(void)

{
  FUN_CODE_8850(0x704);
  nop();
  nop();
  nop();
  nop();
  FUN_CODE_8850(0x70c);
  nop();
  nop();
  nop();
  nop();
  return;
}


// ===== H_5F99  [app]  callers: 

void H_5F99(short param_1,undefined1 param_2)

{
  DAT_EXTMEM_0724 = param_2;
  DAT_EXTMEM_0725 = *(undefined1 *)(param_1 + 1);
  return;
}


// ===== FUN_CODE_5ff2  [app]  callers: CODE:6e2a

void FUN_CODE_5ff2(void)

{
  DAT_EXTMEM_1611 = 0x40;
  DAT_EXTMEM_1601 = DAT_EXTMEM_1601 & 0xfd;
  return;
}


// ===== FUN_CODE_6000  [app]  callers: CODE:2200

void FUN_CODE_6000(void)

{
  if (DAT_EXTMEM_0045 == '3') {
    return;
  }
  return;
}


// ===== FUN_CODE_600d  [app]  callers: CODE:573e CODE:5859

char FUN_CODE_600d(char param_1,byte param_2,byte param_3)

{
  bool bVar1;
  short sVar2;
  byte *pbVar3;
  byte *pbVar4;
  byte bVar5;
  byte bVar6;
  char cVar7;
  char cVar8;
  undefined2 *puVar9;
  undefined1 *puVar10;
  
  if (DAT_EXTMEM_04cb != '\0') {
    DAT_EXTMEM_04d0 = 2;
  }
  DAT_EXTMEM_04cd = '\0';
  DAT_EXTMEM_04c2 = param_3;
  DAT_EXTMEM_04c3 = param_2;
  DAT_EXTMEM_04c4 = param_1;
  if ((param_1 == '\0') || (FUN_CODE_0b4b(1), bVar6 = DAT_EXTMEM_04c2, param_3 == 0)) {
    DAT_EXTMEM_04cd = '\0';
  }
  else {
    bVar5 = (byte)((ushort)DAT_EXTMEM_04c2 * 0xf);
    **(undefined1 **)
      CONCAT11((char)((ushort)DAT_EXTMEM_04c2 * 0xf >> 8) + ('\v' - (((6 < bVar5) << 7) >> 7)),
               bVar5 - 7) = 0x13;
    bVar5 = (byte)((ushort)bVar6 * 0x15);
    **(byte **)CONCAT11((char)((ushort)bVar6 * 0x15 >> 8) + ('\v' - (((0x45 < bVar5) << 7) >> 7)),
                        bVar5 + 0xba) = DAT_EXTMEM_04c3 & 0xfe;
    bVar6 = DAT_EXTMEM_04c2;
    bVar5 = (byte)((ushort)DAT_EXTMEM_04c2 * 0x15);
    **(undefined1 **)
      CONCAT11((char)((ushort)DAT_EXTMEM_04c2 * 0x15 >> 8) + ('\v' - (((0x3b < bVar5) << 7) >> 7)),
               bVar5 - 0x3c) = *(undefined1 *)CONCAT11(DAT_EXTMEM_04c5,DAT_EXTMEM_04c6);
    bVar5 = (byte)((ushort)bVar6 * 0x15);
    **(undefined1 **)
      CONCAT11((char)((ushort)bVar6 * 0x15 >> 8) + ('\v' - (((0x47 < bVar5) << 7) >> 7)),
               bVar5 + 0xb8) = 0x5c;
    TR1 = 0;
    ET1 = 0;
    TH1 = 0xb2;
    TL1 = 0x19;
    TF1 = 0;
    TR1 = 1;
    while (bVar6 = DAT_EXTMEM_04c2, cVar7 = TF1, cVar7 == '\0') {
      bVar5 = (byte)((ushort)DAT_EXTMEM_04c2 * 0x15);
      DAT_EXTMEM_04cc =
           **(byte **)CONCAT11((char)((ushort)DAT_EXTMEM_04c2 * 0x15 >> 8) +
                               ('\v' - (((0x41 < bVar5) << 7) >> 7)),bVar5 + 0xbe);
      if ((DAT_EXTMEM_04cc & 0xfc) != 0) {
        if ((DAT_EXTMEM_04cc & 0x7c) != 0) {
          if ((DAT_EXTMEM_04cc & 0x18) != 0) {
            FUN_CODE_0992(DAT_EXTMEM_04c2);
          }
          DAT_EXTMEM_04cd = '\0';
          break;
        }
        if ((DAT_EXTMEM_04cc >> 1 & 1) == 0) {
          if (DAT_EXTMEM_04c4 != '\0') {
            DAT_EXTMEM_04c4 = DAT_EXTMEM_04c4 + -1;
            if (DAT_EXTMEM_04c4 == '\0') {
              bVar5 = (byte)((ushort)DAT_EXTMEM_04c2 * 0xf);
              puVar9 = (undefined2 *)
                       CONCAT11((char)((ushort)DAT_EXTMEM_04c2 * 0xf >> 8) +
                                ('\v' - (((6 < bVar5) << 7) >> 7)),bVar5 - 7);
              pbVar4 = (byte *)*puVar9;
              pbVar3 = (byte *)*puVar9;
              *pbVar3 = *pbVar3 | 0xc;
              sVar2 = (ushort)bVar6 * 0x15;
              bVar6 = (byte)sVar2;
              **(undefined1 **)
                CONCAT11((char)((ushort)sVar2 >> 8) + ('\v' - (((0x41 < bVar6) << 7) >> 7)),
                         bVar6 + 0xbe) = 0xfc;
              bVar6 = DAT_EXTMEM_04c7;
              if (DAT_EXTMEM_04c7 == 0) {
                bVar6 = DAT_EXTMEM_04c8 ^ 1;
              }
              if (bVar6 == 0) {
                bVar6 = (byte)((ushort)DAT_EXTMEM_04c2 * 0x15);
                pbVar3 = *(byte **)CONCAT11((char)((ushort)DAT_EXTMEM_04c2 * 0x15 >> 8) +
                                            ('\v' - (((0x47 < bVar6) << 7) >> 7)),bVar6 + 0xb8);
                *pbVar3 = *pbVar3 | 0x20;
              }
              *pbVar4 = *pbVar4 & 0xfb;
              DAT_EXTMEM_04cd = '\x01';
              break;
            }
            DAT_EXTMEM_04c6 = DAT_EXTMEM_04c6 + '\x01';
            if (DAT_EXTMEM_04c6 == '\0') {
              DAT_EXTMEM_04c5 = DAT_EXTMEM_04c5 + '\x01';
            }
            bVar5 = (byte)((ushort)DAT_EXTMEM_04c2 * 0x15);
            **(undefined1 **)
              CONCAT11((char)((ushort)DAT_EXTMEM_04c2 * 0x15 >> 8) +
                       ('\v' - (((0x3b < bVar5) << 7) >> 7)),bVar5 - 0x3c) =
                 *(undefined1 *)CONCAT11(DAT_EXTMEM_04c5,DAT_EXTMEM_04c6);
            sVar2 = (ushort)bVar6 * 0x15;
            bVar6 = (byte)sVar2;
            **(undefined1 **)
              CONCAT11((char)((ushort)sVar2 >> 8) + ('\v' - (((0x41 < bVar6) << 7) >> 7)),
                       bVar6 + 0xbe) = 0xfc;
            TH1 = 0xb2;
            TL1 = 0x19;
            TF1 = 0;
          }
        }
        else {
          TR1 = 0;
          TF1 = 0;
          DAT_EXTMEM_04cd = '\0';
        }
      }
    }
    if (DAT_EXTMEM_04cd == '\x01') {
      DAT_EXTMEM_04cd = '\0';
      while( true ) {
        TH1 = 0xb2;
        TL1 = 0x19;
        TF1 = 0;
        do {
          cVar7 = TF1;
          if (cVar7 != '\0') goto LAB_CODE_6393;
          bVar6 = (byte)((ushort)DAT_EXTMEM_04c2 * 0x15);
          DAT_EXTMEM_04cc =
               **(byte **)CONCAT11((char)((ushort)DAT_EXTMEM_04c2 * 0x15 >> 8) +
                                   ('\v' - (((0x41 < bVar6) << 7) >> 7)),bVar6 + 0xbe);
        } while ((DAT_EXTMEM_04cc & 0xfe) == 0);
        if ((DAT_EXTMEM_04cc & 0x7c) != 0) {
          if ((DAT_EXTMEM_04cc & 0x18) != 0) {
            FUN_CODE_0992(DAT_EXTMEM_04c2);
          }
          TR1 = 0;
          TF1 = 0;
          goto LAB_CODE_6393;
        }
        if (-1 < (char)DAT_EXTMEM_04cc) break;
        bVar6 = DAT_EXTMEM_04c7;
        if (DAT_EXTMEM_04c7 == 0) {
          bVar6 = DAT_EXTMEM_04c8;
        }
        cVar7 = DAT_EXTMEM_04ca;
        if (bVar6 != 0) {
          bVar6 = (byte)((ushort)DAT_EXTMEM_04c2 * 0x15);
          *(undefined1 *)CONCAT11(DAT_EXTMEM_04c9,DAT_EXTMEM_04ca) =
               **(undefined1 **)
                 CONCAT11((char)((ushort)DAT_EXTMEM_04c2 * 0x15 >> 8) +
                          ('\v' - (((0x3b < bVar6) << 7) >> 7)),bVar6 - 0x3c);
          cVar7 = DAT_EXTMEM_04ca + '\x01';
          if (cVar7 == '\0') {
            DAT_EXTMEM_04c9 = DAT_EXTMEM_04c9 + '\x01';
          }
          bVar1 = DAT_EXTMEM_04c8 != 0;
          DAT_EXTMEM_04c8 = DAT_EXTMEM_04c8 - 1;
          DAT_EXTMEM_04c7 = DAT_EXTMEM_04c7 + (-1 - ((bVar1 << 7) >> 7));
          if ((DAT_EXTMEM_04cb != '\0') && (DAT_EXTMEM_04d0 != 0)) {
            bVar6 = DAT_EXTMEM_04d0 - 1;
            puVar10 = (undefined1 *)
                      CONCAT11(DAT_EXTMEM_04c9 + (-1 - (((cVar7 != '\0') << 7) >> 7)),
                               DAT_EXTMEM_04ca);
            cVar8 = DAT_EXTMEM_04d0 - 0x33;
            DAT_EXTMEM_04ca = cVar7;
            DAT_EXTMEM_04d0 = bVar6;
            *(undefined1 *)CONCAT11('\x04' - (((0x31 < bVar6) << 7) >> 7),cVar8) = *puVar10;
            cVar7 = DAT_EXTMEM_04ca;
            if (bVar6 == 0) {
              DAT_EXTMEM_04c7 = DAT_EXTMEM_04ce;
              DAT_EXTMEM_04c8 = DAT_EXTMEM_04cf;
              if ((byte)-(((DAT_EXTMEM_04cf < 3) << 7) >> 7) <= DAT_EXTMEM_04ce) {
                DAT_EXTMEM_04c8 = DAT_EXTMEM_04cf - 2;
                DAT_EXTMEM_04c7 = DAT_EXTMEM_04ce + (-1 - (((1 < DAT_EXTMEM_04cf) << 7) >> 7));
              }
            }
          }
        }
        DAT_EXTMEM_04ca = cVar7;
        bVar6 = DAT_EXTMEM_04c7;
        if (DAT_EXTMEM_04c7 == 0) {
          bVar6 = DAT_EXTMEM_04c8 ^ 1;
        }
        if (bVar6 == 0) {
          bVar6 = (byte)((ushort)DAT_EXTMEM_04c2 * 0x15);
          pbVar3 = *(byte **)CONCAT11((char)((ushort)DAT_EXTMEM_04c2 * 0x15 >> 8) +
                                      ('\v' - (((0x47 < bVar6) << 7) >> 7)),bVar6 + 0xb8);
          *pbVar3 = *pbVar3 | 0x20;
        }
        bVar6 = (byte)((ushort)DAT_EXTMEM_04c2 * 0x15);
        **(undefined1 **)
          CONCAT11((char)((ushort)DAT_EXTMEM_04c2 * 0x15 >> 8) +
                   ('\v' - (((0x41 < bVar6) << 7) >> 7)),bVar6 + 0xbe) = 0xfc;
      }
      TR1 = 0;
      TF1 = 0;
      bVar6 = DAT_EXTMEM_04c7;
      if (DAT_EXTMEM_04c7 == 0) {
        bVar6 = DAT_EXTMEM_04c8;
      }
      if (bVar6 == 0) {
        DAT_EXTMEM_04cd = '\x01';
      }
    }
LAB_CODE_6393:
    cVar7 = TF1;
    if (cVar7 != '\0') {
      FUN_CODE_0992(DAT_EXTMEM_04c2);
    }
    bVar6 = DAT_EXTMEM_04c2;
    bVar5 = (byte)((ushort)DAT_EXTMEM_04c2 * 0x15);
    **(undefined1 **)
      CONCAT11((char)((ushort)DAT_EXTMEM_04c2 * 0x15 >> 8) + ('\v' - (((0x41 < bVar5) << 7) >> 7)),
               bVar5 + 0xbe) = 0xfe;
    bVar5 = (byte)((ushort)bVar6 * 0xf);
    **(undefined1 **)
      CONCAT11((char)((ushort)bVar6 * 0xf >> 8) + ('\v' - (((6 < bVar5) << 7) >> 7)),bVar5 - 7) =
         0x11;
    TR1 = 0;
    TF1 = 0;
    ET1 = 1;
  }
  return DAT_EXTMEM_04cd;
}


// ===== FUN_CODE_63e6  [app]  callers: CODE:5ed4

undefined1 FUN_CODE_63e6(char param_1,char param_2,byte param_3,byte param_4)

{
  char cVar1;
  
  DAT_EXTMEM_04da = 0;
  DAT_EXTMEM_04d6 = param_4;
  DAT_EXTMEM_04d7 = param_3;
  DAT_EXTMEM_04d8 = param_1;
  DAT_EXTMEM_04d9 = param_2;
  if (param_3 == 0) {
    DAT_EXTMEM_04da = 0;
  }
  else {
    cVar1 = '\0';
    FUN_CODE_0b4b(1);
    if (cVar1 == '\0') {
      DAT_EXTMEM_04da = 0;
    }
    else {
      if (0x20 < DAT_EXTMEM_04d7) {
        DAT_EXTMEM_04d7 = 0x20;
      }
      DAT_EXTMEM_1c10 = 0x13;
      DAT_EXTMEM_1c45 = DAT_EXTMEM_1c45 | 8;
      DAT_EXTMEM_1c04 = DAT_EXTMEM_04d7;
      DAT_EXTMEM_1c03 = DAT_EXTMEM_04d6 | 1;
      DAT_EXTMEM_1c01 = 0x5c;
      TR1 = 0;
      ET1 = 0;
      TH1 = 0xb2;
      TL1 = 0x19;
      TF1 = 0;
      TR1 = 1;
      DAT_EXTMEM_04db = 0;
      do {
        cVar1 = TF1;
        if (cVar1 == '\x01') goto LAB_CODE_64c9;
      } while ((DAT_EXTMEM_1c00 & 0x7e) == 0);
      if ((DAT_EXTMEM_1c00 & 0x7c) == 0) {
        if (DAT_EXTMEM_04d7 == (DAT_EXTMEM_1c46 & 0x3f)) {
          for (; DAT_EXTMEM_04db < DAT_EXTMEM_04d7; DAT_EXTMEM_04db = DAT_EXTMEM_04db + 1) {
            *(undefined1 *)CONCAT11(DAT_EXTMEM_04d8,DAT_EXTMEM_04d9) = DAT_EXTMEM_1c06;
            DAT_EXTMEM_04d9 = DAT_EXTMEM_04d9 + '\x01';
            if (DAT_EXTMEM_04d9 == '\0') {
              DAT_EXTMEM_04d8 = DAT_EXTMEM_04d8 + '\x01';
            }
          }
          DAT_EXTMEM_04da = 1;
        }
        else {
          DAT_EXTMEM_04da = 0;
        }
      }
      else {
        if ((DAT_EXTMEM_1c00 & 0x18) != 0) {
          FUN_CODE_0992(0);
        }
        TR1 = 0;
        TF1 = 0;
      }
LAB_CODE_64c9:
      cVar1 = TF1;
      if (cVar1 != '\0') {
        FUN_CODE_0992(0);
      }
      DAT_EXTMEM_1c10 = 0x11;
      DAT_EXTMEM_1c45 = DAT_EXTMEM_1c45 & 0xf7;
      DAT_EXTMEM_1c00 = 0xfe;
      TR1 = 0;
      TF1 = 0;
      ET1 = 1;
    }
  }
  return DAT_EXTMEM_04da;
}


// ===== FUN_CODE_64f0  [app]  callers: CODE:5ed4

undefined1 FUN_CODE_64f0(char param_1,char param_2,byte param_3,byte param_4)

{
  char cVar1;
  
  DAT_EXTMEM_04e0 = 0;
  DAT_EXTMEM_04dc = param_4;
  DAT_EXTMEM_04dd = param_3;
  DAT_EXTMEM_04de = param_1;
  DAT_EXTMEM_04df = param_2;
  if (param_3 == 0) {
    DAT_EXTMEM_04e0 = 0;
  }
  else {
    cVar1 = '\x01';
    FUN_CODE_0b4b(1);
    if (cVar1 == '\0') {
      DAT_EXTMEM_04e0 = 0;
    }
    else {
      if (0x20 < DAT_EXTMEM_04dd) {
        DAT_EXTMEM_04dd = 0x20;
      }
      DAT_EXTMEM_1c21 = 0x13;
      DAT_EXTMEM_1c47 = DAT_EXTMEM_1c47 | 8;
      DAT_EXTMEM_1c15 = DAT_EXTMEM_04dd;
      DAT_EXTMEM_1c14 = DAT_EXTMEM_04dc | 1;
      DAT_EXTMEM_1c12 = 0x5c;
      TR1 = 0;
      ET1 = 0;
      TH1 = 0xb2;
      TL1 = 0x19;
      TF1 = 0;
      TR1 = 1;
      DAT_EXTMEM_04e1 = 0;
      do {
        cVar1 = TF1;
        if (cVar1 == '\x01') goto LAB_CODE_65d3;
      } while ((DAT_EXTMEM_1c11 & 0x7e) == 0);
      if ((DAT_EXTMEM_1c11 & 0x7c) == 0) {
        if (DAT_EXTMEM_04dd == (DAT_EXTMEM_1c48 & 0x3f)) {
          for (; DAT_EXTMEM_04e1 < DAT_EXTMEM_04dd; DAT_EXTMEM_04e1 = DAT_EXTMEM_04e1 + 1) {
            *(undefined1 *)CONCAT11(DAT_EXTMEM_04de,DAT_EXTMEM_04df) = DAT_EXTMEM_1c17;
            DAT_EXTMEM_04df = DAT_EXTMEM_04df + '\x01';
            if (DAT_EXTMEM_04df == '\0') {
              DAT_EXTMEM_04de = DAT_EXTMEM_04de + '\x01';
            }
          }
          DAT_EXTMEM_04e0 = 1;
        }
        else {
          DAT_EXTMEM_04e0 = 0;
        }
      }
      else {
        if ((DAT_EXTMEM_1c11 & 0x18) != 0) {
          FUN_CODE_0992(1);
        }
        TR1 = 0;
        TF1 = 0;
      }
LAB_CODE_65d3:
      cVar1 = TF1;
      if (cVar1 != '\0') {
        FUN_CODE_0992(1);
      }
      DAT_EXTMEM_1c21 = 0x11;
      DAT_EXTMEM_1c47 = DAT_EXTMEM_1c47 & 0xf7;
      DAT_EXTMEM_1c11 = 0xfe;
      TR1 = 0;
      TF1 = 0;
      ET1 = 1;
    }
  }
  return DAT_EXTMEM_04e0;
}


// ===== FUN_CODE_65fa  [app]  callers: CODE:5ed4

undefined1 FUN_CODE_65fa(char param_1,char param_2,byte param_3,byte param_4)

{
  char cVar1;
  
  DAT_EXTMEM_04e6 = 0;
  DAT_EXTMEM_04e2 = param_4;
  DAT_EXTMEM_04e3 = param_3;
  DAT_EXTMEM_04e4 = param_1;
  DAT_EXTMEM_04e5 = param_2;
  if (param_3 == 0) {
    DAT_EXTMEM_04e6 = 0;
  }
  else {
    cVar1 = '\x02';
    FUN_CODE_0b4b(1);
    if (cVar1 == '\0') {
      DAT_EXTMEM_04e6 = 0;
    }
    else {
      if (0x20 < DAT_EXTMEM_04e3) {
        DAT_EXTMEM_04e3 = 0x20;
      }
      DAT_EXTMEM_1c32 = 0x13;
      DAT_EXTMEM_1c47 = DAT_EXTMEM_1c47 | 9;
      DAT_EXTMEM_1c2d = DAT_EXTMEM_04e3;
      DAT_EXTMEM_1c2c = DAT_EXTMEM_04e2 | 1;
      DAT_EXTMEM_1c2a = 0x5c;
      TR1 = 0;
      ET1 = 0;
      TH1 = 0xb2;
      TL1 = 0x19;
      TF1 = 0;
      TR1 = 1;
      DAT_EXTMEM_04e7 = 0;
      do {
        cVar1 = TF1;
        if (cVar1 == '\x01') goto LAB_CODE_66dd;
      } while ((DAT_EXTMEM_1c29 & 0x7e) == 0);
      if ((DAT_EXTMEM_1c29 & 0x7c) == 0) {
        if (DAT_EXTMEM_04e3 == (DAT_EXTMEM_1c48 & 0x3f)) {
          for (; DAT_EXTMEM_04e7 < DAT_EXTMEM_04e3; DAT_EXTMEM_04e7 = DAT_EXTMEM_04e7 + 1) {
            *(undefined1 *)CONCAT11(DAT_EXTMEM_04e4,DAT_EXTMEM_04e5) = DAT_EXTMEM_1c2f;
            DAT_EXTMEM_04e5 = DAT_EXTMEM_04e5 + '\x01';
            if (DAT_EXTMEM_04e5 == '\0') {
              DAT_EXTMEM_04e4 = DAT_EXTMEM_04e4 + '\x01';
            }
          }
          DAT_EXTMEM_04e6 = 1;
        }
        else {
          DAT_EXTMEM_04e6 = 0;
        }
      }
      else {
        if ((DAT_EXTMEM_1c29 & 0x18) != 0) {
          FUN_CODE_0992(2);
        }
        TR1 = 0;
        TF1 = 0;
      }
LAB_CODE_66dd:
      cVar1 = TF1;
      if (cVar1 != '\0') {
        FUN_CODE_0992(2);
      }
      DAT_EXTMEM_1c32 = 0x11;
      DAT_EXTMEM_1c47 = DAT_EXTMEM_1c47 & 0xf6;
      DAT_EXTMEM_1c29 = 0xfe;
      TR1 = 0;
      TF1 = 0;
      ET1 = 1;
    }
  }
  return DAT_EXTMEM_04e6;
}


// ===== FUN_CODE_6704  [app]  callers: CODE:8000

void FUN_CODE_6704(undefined1 param_1,byte param_2,undefined1 param_3)

{
  DAT_EXTMEM_0746 = param_3;
  DAT_EXTMEM_0747 = param_2;
  DAT_EXTMEM_0748 = param_1;
  FUN_CODE_6733(1);
  if (DAT_EXTMEM_0747 < 3) {
    FUN_CODE_6814(DAT_EXTMEM_074b,DAT_EXTMEM_074a);
  }
  DAT_EXTMEM_1c26 = 0x19;
  return;
}


// ===== FUN_CODE_6733  [app]  callers: CODE:6704

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


// ===== H_680E  [app]  callers: 

void H_680E(undefined1 param_1,undefined1 *param_2)

{
  *param_2 = param_1;
  DAT_EXTMEM_1c0b = param_1;
  return;
}


// ===== FUN_CODE_6814  [app]  callers: CODE:6704

void FUN_CODE_6814(char param_1,undefined1 param_2)

{
  DAT_EXTMEM_1c21 = 0x20;
  DAT_EXTMEM_1c1d = 0xf;
  DAT_EXTMEM_1c19 = param_2;
  if (param_1 != '\0') {
    DAT_EXTMEM_1c44 = param_1 + -0x80;
  }
  DAT_EXTMEM_1c12 = 0;
  DAT_EXTMEM_1c11 = 0xff;
  DAT_EXTMEM_1c1c = 0xff;
  return;
}


// ===== H_6841  [app]  callers: CODE:69eb

void H_6841(undefined1 param_1)

{
  bool bVar1;
  byte bVar2;
  char cVar5;
  char cVar6;
  undefined2 uVar7;
  undefined1 *puVar8;
  undefined1 uVar3;
  undefined1 uVar4;
  
  DAT_EXTMEM_05d8 = param_1;
  if ((DAT_EXTMEM_1c0b >> 1 & 1) != 1) {
    if ((DAT_EXTMEM_1c0b >> 5 & 1) == 0) {
      if ((DAT_EXTMEM_1c0b >> 2 & 1) == 0) {
        return;
      }
      DAT_EXTMEM_1c0b = 4;
    }
    else {
      DAT_EXTMEM_1c0b = 0x20;
    }
    FUN_CODE_5f2c();
    return;
  }
  if ((DAT_EXTMEM_1c0b >> 3 & 1) != 0) {
    DAT_EXTMEM_1c09 = DAT_EXTMEM_0930;
    FUN_CODE_7aa7();
    FUN_CODE_841d(0xfd);
    FUN_CODE_841d(DAT_EXTMEM_1c09);
    DAT_EXTMEM_1c09 = 0;
    cVar5 = DAT_EXTMEM_070a - (((0xfe < DAT_EXTMEM_070b) << 7) >> 7);
    uVar7 = 0x708;
    bVar2 = DAT_EXTMEM_070b;
    uVar3 = DAT_EXTMEM_0708;
    uVar4 = DAT_EXTMEM_0709;
    goto LAB_CODE_69c6;
  }
  DAT_EXTMEM_0728 = DAT_EXTMEM_1c09;
  FUN_CODE_841d(0xdd);
  FUN_CODE_841d(DAT_EXTMEM_0728);
  if (DAT_EXTMEM_0906 == '\x01') {
    if (DAT_EXTMEM_0928 < 8) {
      bVar1 = 0xe7 < DAT_EXTMEM_0928;
      cVar5 = DAT_EXTMEM_0928 + 0x18;
      DAT_EXTMEM_0928 = DAT_EXTMEM_0928 + 1;
      *(byte *)CONCAT11('\t' - ((bVar1 << 7) >> 7),cVar5) = DAT_EXTMEM_0728;
    }
LAB_CODE_68ea:
    DAT_EXTMEM_0906 = '\0';
  }
  else {
    if (DAT_EXTMEM_0906 == '\x02') {
      DAT_EXTMEM_094b = DAT_EXTMEM_0728;
      DAT_EXTMEM_094c = 1;
      goto LAB_CODE_68ea;
    }
    if ((((DAT_EXTMEM_0728 < 0x10) ||
         (-1 < (DAT_EXTMEM_0728 < 0x1cU - (((DAT_EXTMEM_0728 < 0x10) << 7) >> 7)) << 7)) &&
        (DAT_EXTMEM_0728 != 0x1f)) &&
       ((DAT_EXTMEM_0728 < 0x20 ||
        (0x26U - (((DAT_EXTMEM_0728 < 0x20) << 7) >> 7) <= DAT_EXTMEM_0728)))) {
      if (DAT_EXTMEM_0728 == 2) {
        puVar8 = &DAT_EXTMEM_0906;
LAB_CODE_6982:
        *puVar8 = 1;
      }
      else if (((DAT_EXTMEM_0728 < 3) << 7 < '\0') || (8 < DAT_EXTMEM_0728)) {
        if (DAT_EXTMEM_0728 == 0x30) {
          puVar8 = &DAT_EXTMEM_0949;
          goto LAB_CODE_6982;
        }
        if (DAT_EXTMEM_0728 == 0x31) {
          DAT_EXTMEM_0949 = 0;
        }
        else {
          if (DAT_EXTMEM_0728 == 0x32) {
            puVar8 = &DAT_EXTMEM_094a;
            goto LAB_CODE_6982;
          }
          if (DAT_EXTMEM_0728 == 0x33) {
            DAT_EXTMEM_094a = 0;
          }
          else if (DAT_EXTMEM_0728 == 0x34) {
            DAT_EXTMEM_0906 = '\x02';
          }
        }
      }
      else if (DAT_EXTMEM_0929 < 8) {
        cVar5 = DAT_EXTMEM_0728 - 0x30;
        goto LAB_CODE_694d;
      }
    }
    else if ((DAT_EXTMEM_0929 < 8) << 7 < '\0') {
      cVar5 = DAT_EXTMEM_0728 + 0xa0;
LAB_CODE_694d:
      bVar1 = 0xdf < DAT_EXTMEM_0929;
      cVar6 = DAT_EXTMEM_0929 + 0x20;
      DAT_EXTMEM_0929 = DAT_EXTMEM_0929 + 1;
      *(char *)CONCAT11('\t' - ((bVar1 << 7) >> 7),cVar6) = cVar5;
    }
  }
  DAT_EXTMEM_05d9 = DAT_EXTMEM_1c09;
  cVar5 = DAT_EXTMEM_0702 - (((0xfe < DAT_EXTMEM_0703) << 7) >> 7);
  uVar7 = 0x700;
  bVar2 = DAT_EXTMEM_0703;
  uVar3 = DAT_EXTMEM_0700;
  uVar4 = DAT_EXTMEM_0701;
LAB_CODE_69c6:
  DAT_EXTMEM_1c0b = 2;
  FUN_CODE_8844(uVar7,uVar3,uVar4,cVar5,bVar2 + 1);
  return;
}


// ===== H_69EB  [app]  callers: 

void H_69EB(void)

{
  H_6841();
  H_6841((DAT_EXTMEM_1c0b >> 4 & 1) != 0);
  return;
}


// ===== FUN_CODE_69ff  [app]  callers: CODE:6c88

void FUN_CODE_69ff(undefined1 param_1)

{
  bool bVar1;
  byte bVar2;
  char cVar4;
  char cVar5;
  undefined1 uVar6;
  undefined2 uVar7;
  undefined1 *puVar8;
  undefined1 uVar3;
  
  DAT_EXTMEM_078d = param_1;
  if ((DAT_EXTMEM_1c1c >> 1 & 1) != 1) {
    if ((DAT_EXTMEM_1c1c >> 5 & 1) == 0) {
      if ((DAT_EXTMEM_1c1c >> 2 & 1) == 0) {
        FUN_CODE_841d(0xa5);
        return;
      }
      FUN_CODE_841d(0xa4);
      DAT_EXTMEM_1c1c = 4;
    }
    else {
      FUN_CODE_841d(0xa3);
      DAT_EXTMEM_1c1c = 0x20;
    }
    FUN_CODE_5f41();
    return;
  }
  if ((DAT_EXTMEM_1c1c >> 3 & 1) != 0) {
    DAT_EXTMEM_1c1a = DAT_EXTMEM_0930;
    FUN_CODE_7aa7();
    FUN_CODE_841d(0xfd);
    FUN_CODE_841d(DAT_EXTMEM_1c1a);
    DAT_EXTMEM_1c1a = 0;
    cVar4 = DAT_EXTMEM_070e - (((0xfe < DAT_EXTMEM_070f) << 7) >> 7);
    uVar7 = 0x70c;
    bVar2 = DAT_EXTMEM_070f;
    uVar6 = DAT_EXTMEM_070c;
    uVar3 = DAT_EXTMEM_070d;
    goto LAB_CODE_6c56;
  }
  DAT_EXTMEM_0728 = DAT_EXTMEM_1c1a;
  FUN_CODE_841d(DAT_EXTMEM_1c1a);
  FUN_CODE_841d(0xfe);
  if (DAT_EXTMEM_0906 == '\x01') {
    if (DAT_EXTMEM_0928 < 8) {
      bVar1 = 0xe7 < DAT_EXTMEM_0928;
      cVar4 = DAT_EXTMEM_0928 + 0x18;
      DAT_EXTMEM_0928 = DAT_EXTMEM_0928 + 1;
      *(byte *)CONCAT11('\t' - ((bVar1 << 7) >> 7),cVar4) = DAT_EXTMEM_0728;
    }
LAB_CODE_6ac8:
    DAT_EXTMEM_0906 = '\0';
  }
  else {
    if (DAT_EXTMEM_0906 == '\x02') {
      DAT_EXTMEM_0e10 = DAT_EXTMEM_0728;
      FUN_CODE_7994();
      goto LAB_CODE_6ac8;
    }
    if (DAT_EXTMEM_0906 == '\x03') {
      DAT_EXTMEM_088b = DAT_EXTMEM_0728 - 0x20;
      if (((DAT_EXTMEM_088b != '\0') && (DAT_EXTMEM_088b != '\x01')) && (DAT_EXTMEM_088b != '\x02'))
      {
        DAT_EXTMEM_088b = '\0';
      }
      FUN_CODE_6e72();
      goto LAB_CODE_6ac8;
    }
    if (((DAT_EXTMEM_0728 < 0x10) ||
        (-1 < (DAT_EXTMEM_0728 < 0x1cU - (((DAT_EXTMEM_0728 < 0x10) << 7) >> 7)) << 7)) &&
       ((DAT_EXTMEM_0728 != 0x1f &&
        ((DAT_EXTMEM_0728 < 0x20 ||
         (0x26U - (((DAT_EXTMEM_0728 < 0x20) << 7) >> 7) <= DAT_EXTMEM_0728)))))) {
      if (DAT_EXTMEM_0728 == 2) {
        puVar8 = &DAT_EXTMEM_0906;
        goto LAB_CODE_6c12;
      }
      if ((2 < DAT_EXTMEM_0728) && (DAT_EXTMEM_0728 < 9)) {
        if (7 < DAT_EXTMEM_0929) goto LAB_CODE_6c2c;
        cVar4 = DAT_EXTMEM_0728 - 0x30;
        goto LAB_CODE_6b4a;
      }
      if (DAT_EXTMEM_0728 == 0x26) {
        puVar8 = &DAT_EXTMEM_088b;
LAB_CODE_6c29:
        *puVar8 = 2;
        goto LAB_CODE_6c2c;
      }
      if (DAT_EXTMEM_0728 == 0x27) {
        puVar8 = &DAT_EXTMEM_094d;
LAB_CODE_6b82:
        uVar6 = 2;
LAB_CODE_6baa:
        *puVar8 = uVar6;
        FUN_CODE_6e2a(DAT_INTMEM_28);
      }
      else {
        if (DAT_EXTMEM_0728 == 0x28) {
          puVar8 = &DAT_EXTMEM_094e;
          goto LAB_CODE_6b82;
        }
        if (DAT_EXTMEM_0728 != 0x29) {
          if (DAT_EXTMEM_0728 != 0x2a) {
            if (DAT_EXTMEM_0728 == 0x2b) {
              DAT_EXTMEM_0906 = '\x03';
            }
            else if (DAT_EXTMEM_0728 == 0x2c) {
              DAT_EXTMEM_0811 = DAT_EXTMEM_0811 | 1;
            }
            else if (DAT_EXTMEM_0728 == 0x2d) {
              DAT_EXTMEM_0811 = DAT_EXTMEM_0811 & 0xfe;
            }
            else if (DAT_EXTMEM_0728 == 0x2e) {
              DAT_EXTMEM_0903 = 1;
              DAT_EXTMEM_1601 = DAT_EXTMEM_1601 & 0x7f;
            }
            else if (DAT_EXTMEM_0728 == 0x30) {
              puVar8 = &DAT_EXTMEM_0949;
LAB_CODE_6c12:
              *puVar8 = 1;
            }
            else if (DAT_EXTMEM_0728 == 0x31) {
              DAT_EXTMEM_0949 = 0;
            }
            else {
              if (DAT_EXTMEM_0728 == 0x32) {
                puVar8 = &DAT_EXTMEM_094a;
                goto LAB_CODE_6c12;
              }
              if (DAT_EXTMEM_0728 == 0x33) {
                DAT_EXTMEM_094a = 0;
              }
              else if (DAT_EXTMEM_0728 == 0x34) {
                puVar8 = &DAT_EXTMEM_0906;
                goto LAB_CODE_6c29;
              }
            }
            goto LAB_CODE_6c2c;
          }
          DAT_EXTMEM_1806 = 0;
          FUN_CODE_6e72();
          uVar6 = 0;
          DAT_EXTMEM_094e = 0;
          puVar8 = &DAT_EXTMEM_094d;
          goto LAB_CODE_6baa;
        }
        DAT_EXTMEM_088b = '\0';
      }
    }
    else {
      if (DAT_EXTMEM_0728 == 0x24) {
        puVar8 = &DAT_EXTMEM_094d;
LAB_CODE_6b02:
        *puVar8 = 1;
        FUN_CODE_6e2a(DAT_INTMEM_28);
      }
      else if (DAT_EXTMEM_0728 == 0x25) {
        puVar8 = &DAT_EXTMEM_094e;
        goto LAB_CODE_6b02;
      }
      if ((DAT_EXTMEM_0929 < 8) << 7 < '\0') {
        cVar4 = DAT_EXTMEM_0728 + 0xa0;
LAB_CODE_6b4a:
        bVar1 = 0xdf < DAT_EXTMEM_0929;
        cVar5 = DAT_EXTMEM_0929 + 0x20;
        DAT_EXTMEM_0929 = DAT_EXTMEM_0929 + 1;
        *(char *)CONCAT11('\t' - ((bVar1 << 7) >> 7),cVar5) = cVar4;
      }
    }
  }
LAB_CODE_6c2c:
  DAT_EXTMEM_078e = DAT_EXTMEM_1c1a;
  cVar4 = DAT_EXTMEM_0706 - (((0xfe < DAT_EXTMEM_0707) << 7) >> 7);
  uVar7 = 0x704;
  bVar2 = DAT_EXTMEM_0707;
  uVar6 = DAT_EXTMEM_0704;
  uVar3 = DAT_EXTMEM_0705;
LAB_CODE_6c56:
  DAT_EXTMEM_1c1c = 2;
  FUN_CODE_8844(uVar7,uVar6,uVar3,cVar4,bVar2 + 1);
  return;
}


// ===== FUN_CODE_6c88  [app]  callers: CODE:80db

void FUN_CODE_6c88(void)

{
  bool bVar1;
  
  FUN_CODE_841d(0xa1);
  DAT_EXTMEM_1100 = 0x20;
  FUN_CODE_69ff(0);
  bVar1 = (DAT_EXTMEM_1c1c >> 4 & 1) == 0;
  if (bVar1) {
    FUN_CODE_841d(0xa7);
  }
  else {
    FUN_CODE_841d(0xa6);
  }
  FUN_CODE_69ff(!bVar1);
  return;
}


// ===== FUN_CODE_6cb3  [app]  callers: CODE:6d7b

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


// ===== FUN_CODE_6cf7  [app]  callers: CODE:6d7b

void FUN_CODE_6cf7(void)

{
  DAT_EXTMEM_1106 = DAT_EXTMEM_1106 & 0xbf;
  nop();
  nop();
  nop();
  nop();
  FUN_CODE_4f66();
  DAT_EXTMEM_1106 = DAT_EXTMEM_1106 | 0x40;
  return;
}


// ===== FUN_CODE_6d0d  [app]  callers: CODE:26e2

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


// ===== FUN_CODE_6d7b  [app]  callers: CODE:26b7

void FUN_CODE_6d7b(void)

{
  if (DAT_EXTMEM_00d6 == '\x01') {
    DAT_EXTMEM_00d6 = 2;
    return;
  }
  if (DAT_EXTMEM_00d6 != '\x02') {
    if (DAT_EXTMEM_00d6 == '\0') {
      FUN_CODE_6cb3();
      DAT_EXTMEM_00d6 = 1;
      return;
    }
    DAT_EXTMEM_00d6 = 0;
    return;
  }
  FUN_CODE_6cf7();
  return;
}


// ===== FUN_CODE_6da3  [app]  callers: CODE:0ec1

void FUN_CODE_6da3(void)

{
  char cVar1;
  
  cVar1 = '\0';
  do {
    **(undefined1 **)CONCAT11(0x6e,cVar1 * '\x03') =
         *(undefined1 *)
          CONCAT11('n' - (((0xfdU < (byte)(cVar1 * '\x03')) << 7) >> 7),cVar1 * '\x03' + 2);
    cVar1 = cVar1 + '\x01';
  } while (cVar1 != '\x0e');
  return;
}


// ===== FUN_CODE_6dd6  [app]  callers: CODE:7fe5 CODE:6e2a

void FUN_CODE_6dd6(void)

{
  DAT_EXTMEM_1611 = 0x40;
  DAT_EXTMEM_1601 = DAT_EXTMEM_1601 | 2;
  return;
}


// ===== FUN_CODE_6de4  [app]  callers: CODE:6e2a

void FUN_CODE_6de4(void)

{
  DAT_EXTMEM_1610 = 0x40;
  DAT_EXTMEM_1601 = DAT_EXTMEM_1601 & 0xfe;
  return;
}


// ===== FUN_CODE_6df2  [app]  callers: CODE:7fe5 CODE:6e2a

void FUN_CODE_6df2(void)

{
  DAT_EXTMEM_1610 = 0x40;
  DAT_EXTMEM_1601 = DAT_EXTMEM_1601 | 1;
  return;
}


// ===== H_6E00  [app]  callers: 

void H_6E00(byte *param_1,char *param_2,undefined1 param_3,undefined1 param_4,char param_5)

{
  *param_2 = *param_2 + -1;
  FUN_CODE_8844(0x708,param_3,param_4,param_5 - (((0xfe < *param_1) << 7) >> 7),*param_1 + 1);
  return;
}


// ===== FUN_CODE_6e2a  [app]  callers: CODE:2c5b CODE:69ff CODE:7feb

void FUN_CODE_6e2a(byte param_1)

{
  DAT_INTMEM_28 = param_1;
  DAT_EXTMEM_078f = param_1;
  if ((DAT_EXTMEM_094d == '\x01') || ((DAT_EXTMEM_094d != '\x02' && ((param_1 >> 1 & 1) != 0)))) {
    FUN_CODE_5ff2();
  }
  else {
    FUN_CODE_6dd6();
  }
  if ((DAT_EXTMEM_094e != '\x01') &&
     ((DAT_EXTMEM_094e == '\x02' || ((DAT_EXTMEM_078f >> 2 & 1) == 0)))) {
    FUN_CODE_6df2();
    return;
  }
  FUN_CODE_6de4();
  return;
}


// ===== FUN_CODE_6e72  [app]  callers: CODE:6f21 CODE:69ff CODE:3812 CODE:82e7

void FUN_CODE_6e72(void)

{
  if ((DAT_EXTMEM_0815 & 1) != 1) {
    if (DAT_EXTMEM_088c != '\0') {
      DAT_EXTMEM_088c = DAT_EXTMEM_088c + -1;
      return;
    }
    if (DAT_EXTMEM_088b == '\x01') {
      DAT_EXTMEM_1806 = 0x4d;
      return;
    }
    if (DAT_EXTMEM_088b == '\x02') {
      DAT_EXTMEM_1806 = 0xff;
      return;
    }
    DAT_EXTMEM_1806 = 0;
  }
  return;
}


// ===== FUN_CODE_6ea5  [app]  callers: CODE:08bd

void FUN_CODE_6ea5(void)

{
  FUN_CODE_8391();
  if (DAT_EXTMEM_0892 != '\0') {
    DAT_EXTMEM_0892 = DAT_EXTMEM_0892 + -1;
  }
  if (DAT_EXTMEM_0893 != '\0') {
    DAT_EXTMEM_0893 = DAT_EXTMEM_0893 + -1;
  }
  if ((DAT_EXTMEM_0894 == '\0') && (DAT_EXTMEM_0892 == '\0')) {
    DAT_EXTMEM_1603 = DAT_EXTMEM_1603 & 0xfd;
  }
  if ((DAT_EXTMEM_0894 == '\0') && (DAT_EXTMEM_0893 == '\0')) {
    DAT_EXTMEM_1603 = DAT_EXTMEM_1603 & 0xfd;
  }
  return;
}


// ===== FUN_CODE_6ee1  [app]  callers: CODE:0916

void FUN_CODE_6ee1(void)

{
  if ((char)DAT_EXTMEM_0897 < '\0') {
    if ((DAT_EXTMEM_0897 < 0x85) << 7 < '\0') {
      DAT_EXTMEM_0897 = DAT_EXTMEM_0897 + 1;
    }
    else {
      FUN_CODE_7ac1(DAT_EXTMEM_0897 + 0x7b,3);
      DAT_EXTMEM_0897 = 0x80;
    }
  }
  if ((char)DAT_EXTMEM_0898 < '\0') {
    if (0x84 < DAT_EXTMEM_0898) {
      FUN_CODE_7ac1(DAT_EXTMEM_0898 + 0x7b,4);
      DAT_EXTMEM_0898 = 0x80;
      return;
    }
    DAT_EXTMEM_0898 = DAT_EXTMEM_0898 + 1;
  }
  return;
}


// ===== FUN_CODE_6f21  [app]  callers: 

void FUN_CODE_6f21(void)

{
  if ((DAT_EXTMEM_0800 != 'P') || (DAT_EXTMEM_088b != '\0')) {
    FUN_CODE_6e72();
  }
  return;
}


// ===== FUN_CODE_6f32  [app]  callers: 

void FUN_CODE_6f32(void)

{
  if (DAT_EXTMEM_0802 == '\x01') {
    FUN_CODE_1b56(0,0x57);
    DAT_EXTMEM_0802 = 2;
    return;
  }
  if (DAT_EXTMEM_0802 == '\x02') {
    FUN_CODE_1b56(1,0x57);
    DAT_EXTMEM_0802 = '\0';
  }
  return;
}


// ===== FUN_CODE_6f5b  [app]  callers: 

void FUN_CODE_6f5b(void)

{
  if (DAT_EXTMEM_08ae != '\0') {
    DAT_EXTMEM_08ae = DAT_EXTMEM_08ae + -1;
  }
  return;
}


// ===== FUN_CODE_6f65  [app]  callers: 

void FUN_CODE_6f65(void)

{
  FUN_CODE_82e7();
  FUN_CODE_7a38();
  if (DAT_EXTMEM_0895 != '\0') {
    DAT_EXTMEM_0895 = DAT_EXTMEM_0895 + -1;
  }
  return;
}


// ===== FUN_CODE_6f75  [app]  callers: 

void FUN_CODE_6f75(void)

{
  if ((DAT_EXTMEM_0897 >> 6 & 1) != 0) {
    if ((DAT_EXTMEM_0897 < 0x41) << 7 < '\0') {
      DAT_EXTMEM_0897 = DAT_EXTMEM_0897 + 1;
    }
    else {
      DAT_EXTMEM_0897 = 0x80;
    }
  }
  if ((DAT_EXTMEM_0898 >> 6 & 1) != 0) {
    if (0x40 < DAT_EXTMEM_0898) {
      DAT_EXTMEM_0898 = 0x80;
      return;
    }
    DAT_EXTMEM_0898 = DAT_EXTMEM_0898 + 1;
  }
  return;
}


// ===== FUN_CODE_6fa5  [app]  callers: CODE:0800

void FUN_CODE_6fa5(void)

{
  return;
}


// ===== FUN_CODE_6fa8  [app]  callers: CODE:2200

void FUN_CODE_6fa8(void)

{
  return;
}


// ===== FUN_CODE_6fab  [app]  callers: CODE:0946

void FUN_CODE_6fab(void)

{
  return;
}


// ===== H_6FBE  [app]  callers: 

void H_6FBE(char param_1,char param_2)

{
  if (param_1 != '\x02') {
    FUN_CODE_2d4a(param_2 == '\x01',0,0xe2);
    return;
  }
  return;
}


// ===== H_708C  [app]  callers: 

void H_708C(char param_1,char param_2)

{
  if (param_1 != '\x02') {
    FUN_CODE_2d4a(param_2 == '\x01',0,0xea);
    return;
  }
  return;
}


// ===== H_70FE  [app]  callers: 

void H_70FE(char param_1,char param_2)

{
  if (param_1 != '\x02') {
    FUN_CODE_2d4a(param_2 == '\x01',0,0xe9);
    return;
  }
  return;
}


// ===== H_7675  [app]  callers: 

void H_7675(char param_1)

{
  if (param_1 != '\x02') {
    FUN_CODE_2d4a(param_1 == '\x01',0,0x53);
  }
  return;
}


// ===== FUN_CODE_76f5  [app]  callers: CODE:1841

void FUN_CODE_76f5(char param_1)

{
  DAT_EXTMEM_0754 = param_1;
  DAT_EXTMEM_0756 = FUN_CODE_8561();
  FUN_CODE_7b31(0,0,DAT_EXTMEM_0756);
  if (((DAT_INTMEM_8c >> 6 & 1) == 1) || (DAT_EXTMEM_08af == '\x01')) {
    if ((DAT_EXTMEM_0756 == '%') && (DAT_EXTMEM_0754 != '\x02')) {
      FUN_CODE_2d4a(DAT_EXTMEM_0754 == '\x01',0x40,2);
    }
    if (DAT_EXTMEM_084a != '\0') {
      if ((DAT_EXTMEM_0756 == '\x1c') && (DAT_EXTMEM_0754 == '\0')) {
        if ((DAT_EXTMEM_088d >> 6 & 1) != 0) {
          FUN_CODE_1b56(1,0x11);
          DAT_EXTMEM_088d = DAT_EXTMEM_088d & 0xbf;
        }
        FUN_CODE_1b56(0,0x14);
        FUN_CODE_1b56(0,0x1c);
        FUN_CODE_1b56(1,0x1c);
        DAT_EXTMEM_088d = DAT_EXTMEM_088d | 0x20;
      }
      if ((DAT_EXTMEM_0756 == '+') && (DAT_EXTMEM_0754 == '\0')) {
        if ((DAT_EXTMEM_088d >> 6 & 1) != 0) {
          FUN_CODE_1b56(1,0x11);
          DAT_EXTMEM_088d = DAT_EXTMEM_088d & 0xbf;
        }
        FUN_CODE_1b56(0,0x14);
        FUN_CODE_1b56(0,0x2b);
        FUN_CODE_1b56(1,0x2b);
        DAT_EXTMEM_088d = DAT_EXTMEM_088d | 0x20;
      }
      if ((DAT_EXTMEM_0756 == '\x1a') && (DAT_EXTMEM_0754 == '\0')) {
        if ((DAT_EXTMEM_088d >> 6 & 1) != 0) {
          FUN_CODE_1b56(1,0x11);
          DAT_EXTMEM_088d = DAT_EXTMEM_088d & 0xbf;
        }
        FUN_CODE_1b56(0,0x14);
        FUN_CODE_1b56(0,0x1a);
        FUN_CODE_1b56(1,0x1a);
        DAT_EXTMEM_088d = DAT_EXTMEM_088d | 0x20;
      }
      if ((DAT_EXTMEM_0756 == '\"') && (DAT_EXTMEM_0754 == '\0')) {
        if ((DAT_EXTMEM_088d >> 6 & 1) != 0) {
          FUN_CODE_1b56(1,0x11);
          DAT_EXTMEM_088d = DAT_EXTMEM_088d & 0xbf;
        }
        FUN_CODE_1b56(0,0x14);
        FUN_CODE_1b56(0,0x22);
        FUN_CODE_1b56(1,0x22);
        DAT_EXTMEM_088d = DAT_EXTMEM_088d | 0x20;
      }
      if ((DAT_EXTMEM_0756 == '!') && (DAT_EXTMEM_0754 == '\0')) {
        if ((DAT_EXTMEM_088d >> 6 & 1) != 0) {
          FUN_CODE_1b56(1,0x11);
          DAT_EXTMEM_088d = DAT_EXTMEM_088d & 0xbf;
        }
        FUN_CODE_1b56(0,0x14);
        FUN_CODE_1b56(0,0x21);
        FUN_CODE_1b56(1,0x21);
        DAT_EXTMEM_088d = DAT_EXTMEM_088d | 0x20;
      }
      if ((DAT_EXTMEM_0756 == '*') && (DAT_EXTMEM_0754 == '\0')) {
        if ((DAT_EXTMEM_088d >> 6 & 1) != 0) {
          FUN_CODE_1b56(1,0x11);
          DAT_EXTMEM_088d = DAT_EXTMEM_088d & 0xbf;
        }
        FUN_CODE_1b56(0,0x14);
        FUN_CODE_1b56(0,0x2a);
        FUN_CODE_1b56(1,0x2a);
        DAT_EXTMEM_088d = DAT_EXTMEM_088d | 0x20;
      }
      if ((DAT_EXTMEM_0756 == '\x1d') && (DAT_EXTMEM_0754 == '\0')) {
        if ((DAT_EXTMEM_088d >> 6 & 1) != 0) {
          FUN_CODE_1b56(1,0x11);
          DAT_EXTMEM_088d = DAT_EXTMEM_088d & 0xbf;
        }
        FUN_CODE_1b56(0,0x14);
        FUN_CODE_1b56(0,0x1d);
        FUN_CODE_1b56(1,0x1d);
        DAT_EXTMEM_088d = DAT_EXTMEM_088d | 0x20;
      }
      if ((DAT_EXTMEM_0756 == '5') && (DAT_EXTMEM_0754 == '\0')) {
        if ((DAT_EXTMEM_088d >> 6 & 1) != 0) {
          FUN_CODE_1b56(1,0x11);
          DAT_EXTMEM_088d = DAT_EXTMEM_088d & 0xbf;
        }
        FUN_CODE_1b56(0,0x14);
        FUN_CODE_1b56(0,0x35);
        FUN_CODE_1b56(1,0x35);
        DAT_EXTMEM_088d = DAT_EXTMEM_088d | 0x20;
      }
    }
  }
  return;
}


// ===== FUN_CODE_793d  [app]  callers: CODE:1841

void FUN_CODE_793d(void)

{
  return;
}


// ===== FUN_CODE_7940  [app]  callers: CODE:1435

void FUN_CODE_7940(char param_1,char param_2,char param_3)

{
  DAT_EXTMEM_074e = param_3;
  DAT_EXTMEM_074f = param_2;
  if (param_1 == '\x01') {
    DAT_EXTMEM_0894 = 0;
    if ((param_3 == '\x03') && (param_2 == '\r')) {
      DAT_EXTMEM_0893 = 200;
      DAT_EXTMEM_0892 = 0;
    }
  }
  else {
    DAT_EXTMEM_0894 = 1;
    if ((param_3 == '\x03') && (param_2 == '\r')) {
      FUN_CODE_7ac1(8);
      DAT_EXTMEM_1603 = DAT_EXTMEM_1603 | 2;
      return;
    }
  }
  return;
}


// ===== H_798B  [app]  callers: 

void H_798B(undefined1 param_1,undefined1 param_2)

{
  DAT_EXTMEM_05dc = param_2;
  DAT_EXTMEM_05dd = param_1;
  return;
}


// ===== FUN_CODE_7994  [app]  callers: CODE:2137 CODE:69ff CODE:3812 CODE:8391

void FUN_CODE_7994(void)

{
  if (DAT_EXTMEM_0e10 == '\x14') {
    DAT_EXTMEM_0027 = 0x7b;
    DAT_EXTMEM_0028 = 0x99;
  }
  else {
    DAT_EXTMEM_0027 = 0x7c;
    DAT_EXTMEM_0028 = 0x19;
  }
  DAT_EXTMEM_0029 = 0x7c;
  DAT_EXTMEM_002a = 0x99;
  return;
}


// ===== H_79B9  [app]  callers: 

void H_79B9(void)

{
  return;
}


// ===== FUN_CODE_79bd  [app]  callers: 

void FUN_CODE_79bd(void)

{
  if ((DAT_EXTMEM_088d >> 2 & 1) != 0) {
    if ((DAT_EXTMEM_088d >> 3 & 1) == 1) {
      FUN_CODE_1bd4(1,0x1f);
    }
    else {
      FUN_CODE_1b56(0x4d);
      DAT_EXTMEM_088d = DAT_EXTMEM_088d | 2;
    }
    DAT_EXTMEM_088d = DAT_EXTMEM_088d & 0xf3;
    _6_2 = 1;
  }
  if ((DAT_EXTMEM_088d >> 6 & 1) != 0) {
    if ((char)DAT_EXTMEM_088d < '\0') {
      FUN_CODE_1b56(1,0x11);
    }
    else {
      FUN_CODE_1f93(0xe0);
      FUN_CODE_1f93(0xf0);
      FUN_CODE_1f93(0x7c);
      DAT_EXTMEM_088d = DAT_EXTMEM_088d | 1;
    }
    DAT_EXTMEM_088d = DAT_EXTMEM_088d & 0x3f;
  }
  if ((DAT_EXTMEM_088d >> 5 & 1) != 0) {
    FUN_CODE_1b56(1,0x14);
    DAT_EXTMEM_088d = DAT_EXTMEM_088d & 0xdf;
  }
  return;
}


// ===== FUN_CODE_7a31  [app]  callers: CODE:1841

void FUN_CODE_7a31(void)

{
  return;
}


// ===== FUN_CODE_7a32  [app]  callers: CODE:19fc

void FUN_CODE_7a32(void)

{
  return;
}


// ===== FUN_CODE_7a35  [app]  callers: CODE:19fc

void FUN_CODE_7a35(void)

{
  return;
}


// ===== FUN_CODE_7a38  [app]  callers: CODE:6f65

void FUN_CODE_7a38(void)

{
  if ((DAT_EXTMEM_08a1 & 1) != 0) {
    if ((DAT_EXTMEM_08a0 < 6) << 7 < '\0') {
      DAT_EXTMEM_08a0 = DAT_EXTMEM_08a0 + 1;
    }
    else {
      DAT_EXTMEM_08a0 = 0;
      FUN_CODE_1b56(0,0x14);
      FUN_CODE_1b56(0,0x12);
      FUN_CODE_1b56(0,0x50);
      DAT_EXTMEM_08a1 = DAT_EXTMEM_08a1 & 0xfe | 2;
    }
  }
  if ((DAT_EXTMEM_08a1 >> 1 & 1) != 0) {
    if (2 < DAT_EXTMEM_08a0) {
      DAT_EXTMEM_08a0 = 0;
      FUN_CODE_1b56(1,0x14);
      FUN_CODE_1b56(1,0x12);
      FUN_CODE_1b56(1,0x50);
      DAT_EXTMEM_08a1 = DAT_EXTMEM_08a1 & 0xfd;
      return;
    }
    DAT_EXTMEM_08a0 = DAT_EXTMEM_08a0 + 1;
  }
  return;
}


// ===== FUN_CODE_7aa7  [app]  callers: CODE:69ff CODE:6841

void FUN_CODE_7aa7(void)

{
  DAT_EXTMEM_0930 = 0;
  return;
}


// ===== FUN_CODE_7aad  [app]  callers: CODE:34f7

void FUN_CODE_7aad(void)

{
  if ((DAT_EXTMEM_0908 != '\0') && (DAT_EXTMEM_0908 = DAT_EXTMEM_0908 + -1, DAT_EXTMEM_0908 == '\0')
     ) {
    DAT_EXTMEM_1603 = DAT_EXTMEM_1603 | 4;
  }
  return;
}


// ===== FUN_CODE_7ac1  [app]  callers: CODE:0ec1 CODE:6ee1 CODE:7940

void FUN_CODE_7ac1(undefined1 param_1)

{
  DAT_EXTMEM_1603 = DAT_EXTMEM_1603 & 0xfb;
  DAT_EXTMEM_0908 = 6;
  DAT_EXTMEM_0930 = param_1;
  return;
}


// ===== H_7AD4  [app]  callers: 

void H_7AD4(void)

{
  if (DAT_EXTMEM_0901 == '\0') {
    if ((DAT_INTMEM_8c >> 6 & 1) != 0) {
      return;
    }
    return;
  }
  if ((DAT_INTMEM_8c >> 6 & 1) != 0) {
    return;
  }
  return;
}


// ===== FUN_CODE_7b31  [app]  callers: CODE:76f5

void FUN_CODE_7b31(undefined1 param_1,undefined1 param_2,byte param_3,byte param_4)

{
  byte bVar1;
  
  DAT_EXTMEM_0757 = param_3;
  DAT_EXTMEM_0758 = param_4;
  DAT_EXTMEM_0759 = param_1;
  DAT_EXTMEM_075a = param_2;
  DAT_EXTMEM_075b = 0;
  while( true ) {
    if (2 < DAT_EXTMEM_075b) {
      DAT_EXTMEM_0950 = 0;
      return;
    }
    bVar1 = param_3;
    if (param_3 == 0) {
      bVar1 = param_4 ^ *(byte *)CONCAT11('\x7f' - (((0xdc < DAT_EXTMEM_075b * '\x04') << 7) >> 7),
                                          DAT_EXTMEM_075b * '\x04' + 0x23);
    }
    if (bVar1 == 0) break;
    DAT_EXTMEM_075b = DAT_EXTMEM_075b + 1;
  }
  FUN_CODE_8961(*(undefined2 *)
                 (CONCAT11('\x7f' - (((0xdb < DAT_EXTMEM_075b * '\x04') << 7) >> 7),
                           DAT_EXTMEM_075b * '\x04' + 0x24) + 1),param_2);
  return;
}


// ===== FUN_CODE_7f2f  [app]  callers: CODE:3501

void FUN_CODE_7f2f(void)

{
  return;
}


// ===== H_7F30  [app]  callers: 

void H_7F30(void)

{
  FUN_CODE_1391(0xfc);
  FUN_CODE_1372();
  return;
}


// ===== FUN_CODE_7f40  [app]  callers: CODE:806d CODE:3812

void FUN_CODE_7f40(void)

{
  FUN_CODE_1391(0);
  FUN_CODE_1353();
  FUN_CODE_13d4(0,0xd8,0);
  FUN_CODE_1353();
  DAT_EXTMEM_0786 = 0;
  FUN_CODE_13fe(0xd8,0,0xe,0);
  FUN_CODE_1372();
  return;
}


// ===== FUN_CODE_7f65  [app]  callers: CODE:806d

void FUN_CODE_7f65(void)

{
  FUN_CODE_0f8b(0xe,0,0xff,0xd8,0);
  return;
}


// ===== FUN_CODE_7f7b  [app]  callers: CODE:0400

void FUN_CODE_7f7b(void)

{
  return;
}


// ===== H_7F7E  [app]  callers: 

void H_7F7E(char param_1)

{
  undefined2 *puVar1;
  
  do {
    puVar1 = (undefined2 *)
             CONCAT11('\x7f' - (((0x26U < (byte)(param_1 * '\x03')) << 7) >> 7),
                      param_1 * '\x03' - 0x27);
    DAT_INTMEM_87 = *(undefined1 *)puVar1;
    DAT_INTMEM_88 = *(undefined1 *)((short)puVar1 + 1);
    *(undefined1 *)*puVar1 =
         *(undefined1 *)
          CONCAT11('\x7f' - (((0x24U < (byte)(param_1 * '\x03')) << 7) >> 7),param_1 * '\x03' - 0x25
                  );
    param_1 = param_1 + '\x01';
  } while (param_1 != '\x04');
  return;
}


// ===== FUN_CODE_7fb5  [app]  callers: CODE:8000

void FUN_CODE_7fb5(void)

{
  DAT_EXTMEM_0910 = 0;
  DAT_EXTMEM_0911 = 0x44;
  DAT_EXTMEM_0912 = 0;
  DAT_EXTMEM_0913 = 0x20;
  DAT_EXTMEM_0914 = 4;
  DAT_EXTMEM_0915 = 7;
  return;
}


// ===== FUN_CODE_7fd8  [app]  callers: CODE:2200

void FUN_CODE_7fd8(void)

{
  return;
}


// ===== FUN_CODE_7fe5  [app]  callers: CODE:4bc4

void FUN_CODE_7fe5(void)

{
  FUN_CODE_6df2();
  FUN_CODE_6dd6();
  return;
}


// ===== FUN_CODE_7feb  [app]  callers: CODE:4dba

void FUN_CODE_7feb(void)

{
  FUN_CODE_6e2a(DAT_INTMEM_28);
  return;
}


// ===== H_7FF0  [app]  callers: 

void H_7FF0(undefined1 param_1)

{
  DAT_EXTMEM_05de = param_1;
  return;
}


// ===== H_7FF7  [app]  callers: 

void H_7FF7(void)

{
  return;
}


// ===== thunk_FUN_CODE_80fc  [app]  callers: 

void thunk_FUN_CODE_80fc(void)

{
  FUN_CODE_80fc();
  return;
}


// ===== FUN_CODE_8000  [app]  callers: CODE:2200

void FUN_CODE_8000(void)

{
  DAT_EXTMEM_16e1 = 0;
  DAT_EXTMEM_0749 = 0;
  DAT_EXTMEM_074a = 0x66;
  DAT_EXTMEM_074b = 0;
  FUN_CODE_6704(0,1,0);
  FUN_CODE_5f41();
  DAT_EXTMEM_0811 = 0;
  DAT_EXTMEM_0903 = 0;
  DAT_EXTMEM_0812 = 0;
  DAT_EXTMEM_0813 = 0;
  DAT_EXTMEM_0814 = 0;
  DAT_EXTMEM_0815 = 0;
  DAT_EXTMEM_0800 = 0x55;
  DAT_EXTMEM_0801 = 0x55;
  DAT_EXTMEM_0891 = 0x32;
  DAT_EXTMEM_0802 = 0;
  DAT_EXTMEM_080f = 0;
  DAT_EXTMEM_0906 = 0;
  DAT_EXTMEM_0901 = 0;
  DAT_EXTMEM_0902 = 0;
  FUN_CODE_7fb5();
  DAT_EXTMEM_0928 = 0;
  DAT_EXTMEM_094a = 0;
  DAT_EXTMEM_094b = 0;
  DAT_EXTMEM_094c = 0;
  return;
}


// ===== FUN_CODE_806d  [app]  callers: CODE:0ec1

void FUN_CODE_806d(void)

{
  FUN_CODE_7f65();
  if ((((DAT_EXTMEM_0e00 != '\x19') || (DAT_EXTMEM_0e01 != 'x')) || (DAT_EXTMEM_0e02 != '\x03')) ||
     (DAT_EXTMEM_0e03 != '\x05')) {
    DAT_EXTMEM_0746 = '\0';
    DAT_EXTMEM_0747 = '\0';
    do {
      *(undefined1 *)CONCAT11(DAT_EXTMEM_0746 + '\x0e',DAT_EXTMEM_0747) = 0;
      DAT_EXTMEM_0747 = DAT_EXTMEM_0747 + '\x01';
      if (DAT_EXTMEM_0747 == '\0') {
        DAT_EXTMEM_0746 = DAT_EXTMEM_0746 + '\x01';
      }
    } while ((DAT_EXTMEM_0746 != '\x01') || (DAT_EXTMEM_0747 != '\0'));
    DAT_EXTMEM_0e00 = '\x19';
    DAT_EXTMEM_0e01 = 'x';
    DAT_EXTMEM_0e02 = '\x03';
    DAT_EXTMEM_0e03 = '\x05';
    DAT_EXTMEM_0e10 = 0;
    FUN_CODE_059d();
    FUN_CODE_7f40();
    FUN_CODE_05a4();
  }
  return;
}


// ===== FUN_CODE_80db  [app]  callers: 

void FUN_CODE_80db(void)

{
  FUN_CODE_841d(0xa0);
  FUN_CODE_6c88();
  return;
}


// ===== FUN_CODE_80e3  [app]  callers: CODE:813c

void FUN_CODE_80e3(void)

{
  DAT_EXTMEM_1b00 = DAT_EXTMEM_1b00 | 0x20;
  DAT_EXTMEM_1b04 = 0x20;
  DAT_EXTMEM_1114 = 0x20;
  DAT_EXTMEM_1115 = DAT_EXTMEM_1115 | 0x20;
  return;
}


// ===== FUN_CODE_80fc  [app]  callers: CODE:813c CODE:7ff9

void FUN_CODE_80fc(void)

{
  DAT_EXTMEM_1115 = DAT_EXTMEM_1115 & 0xdf;
  DAT_EXTMEM_1b04 = 0x20;
  DAT_EXTMEM_1114 = 0x20;
  return;
}


// ===== FUN_CODE_810e  [app]  callers: CODE:813c

void FUN_CODE_810e(void)

{
  DAT_EXTMEM_1b03 = 0xff;
  DAT_EXTMEM_1b07 = 0xff;
  DAT_EXTMEM_1120 = 0xff;
  DAT_EXTMEM_1121 = 0xff;
  return;
}


// ===== FUN_CODE_8121  [app]  callers: CODE:813c

void FUN_CODE_8121(void)

{
  DAT_EXTMEM_1121 = 0;
  DAT_EXTMEM_1b07 = 0xff;
  DAT_EXTMEM_1120 = 0xff;
  return;
}


// ===== FUN_CODE_8131  [app]  callers: 

void FUN_CODE_8131(void)

{
  DAT_EXTMEM_1b07 = 0xff;
  DAT_EXTMEM_1120 = 0xff;
  return;
}


// ===== FUN_CODE_813c  [app]  callers: CODE:4bc4

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


// ===== FUN_CODE_8264  [app]  callers: CODE:82e7

void FUN_CODE_8264(void)

{
  char cVar1;
  
  if (DAT_EXTMEM_0800 == '3') {
    if ((DAT_EXTMEM_1601 >> 6 & 1) == 1) {
      cVar1 = '\0';
    }
    else {
      cVar1 = -0x80;
    }
    if ((-1 < cVar1) && ((DAT_EXTMEM_1601 >> 5 & 1) != 1)) {
      DAT_EXTMEM_0800 = 0x30;
      return;
    }
    if (((DAT_EXTMEM_1601 >> 6 & 1) != 1) && ((DAT_EXTMEM_1601 >> 5 & 1) != 1)) {
      DAT_EXTMEM_0800 = 5;
      return;
    }
  }
  else if (DAT_EXTMEM_0800 == 'U') {
    if ((DAT_EXTMEM_1601 >> 6 & 1) == 1) {
      cVar1 = '\0';
    }
    else {
      cVar1 = -0x80;
    }
    if ((-1 < cVar1) && ((DAT_EXTMEM_1601 >> 5 & 1) != 1)) {
      DAT_EXTMEM_0800 = 'P';
      DAT_EXTMEM_0891 = 0x32;
    }
  }
  else if (DAT_EXTMEM_0800 == '\x10') {
    if (((DAT_EXTMEM_1601 >> 5 & 1) != 1) && ((DAT_EXTMEM_1601 >> 6 & 1) != 1)) {
      DAT_EXTMEM_0800 = 5;
      return;
    }
    if ((DAT_EXTMEM_1601 >> 6 & 1) != 1) {
      if ((DAT_EXTMEM_1601 >> 5 & 1) == 1) {
        cVar1 = '\0';
      }
      else {
        cVar1 = -0x80;
      }
      if (-1 < cVar1) {
        DAT_EXTMEM_0800 = 3;
        return;
      }
    }
  }
  return;
}


// ===== FUN_CODE_82e7  [app]  callers: CODE:6f65

void FUN_CODE_82e7(void)

{
  char cVar1;
  
  if (((DAT_EXTMEM_0800 == '\x10') || (DAT_EXTMEM_0800 == '3')) || (DAT_EXTMEM_0800 == 'U')) {
    FUN_CODE_8264();
  }
  if (DAT_EXTMEM_0801 != DAT_EXTMEM_0800) {
    DAT_EXTMEM_0801 = DAT_EXTMEM_0800;
  }
  if (DAT_EXTMEM_0800 == '\x03') {
    DAT_EXTMEM_1806 = 0;
    DAT_EXTMEM_0800 = 0x33;
    return;
  }
  if (DAT_EXTMEM_0800 == '\x05') {
    DAT_EXTMEM_1806 = 0;
    DAT_EXTMEM_088b = 0;
    DAT_EXTMEM_0800 = 0x55;
    DAT_EXTMEM_0895 = 0;
    DAT_EXTMEM_0896 = 0;
    return;
  }
  if (DAT_EXTMEM_0800 != '\x10') {
    cVar1 = '\0';
    if (DAT_EXTMEM_0800 == '0') {
LAB_CODE_8356:
      FUN_CODE_6e72(cVar1);
      DAT_EXTMEM_0800 = 0x10;
      return;
    }
    if (DAT_EXTMEM_0800 != '3') {
      if (DAT_EXTMEM_0800 == 'P') {
        cVar1 = DAT_EXTMEM_088b;
        if ((DAT_EXTMEM_088b == '\0') && (cVar1 = DAT_EXTMEM_0891 + -1, DAT_EXTMEM_0891 != '\0')) {
          DAT_EXTMEM_1806 = 0xff;
          DAT_EXTMEM_0891 = DAT_EXTMEM_0891 + -1;
          return;
        }
        goto LAB_CODE_8356;
      }
      if (DAT_EXTMEM_0800 == 'U') {
        DAT_EXTMEM_0891 = 0x32;
        return;
      }
      DAT_EXTMEM_1806 = 0;
      DAT_EXTMEM_0800 = 'U';
    }
  }
  return;
}


// ===== FUN_CODE_8391  [app]  callers: CODE:6ea5

void FUN_CODE_8391(void)

{
  byte bVar1;
  
  if (DAT_EXTMEM_0928 != '\0') {
    DAT_EXTMEM_0901 = (DAT_EXTMEM_0918 & 1) != 0;
    DAT_EXTMEM_0902 = (DAT_EXTMEM_0918 >> 1 & 1) != 0;
    if ((bool)DAT_EXTMEM_0902) {
      DAT_EXTMEM_08ae = 4;
    }
    if ((DAT_EXTMEM_0918 >> 6 & 1) == 0) {
      DAT_EXTMEM_0e10 = 0;
    }
    else {
      DAT_EXTMEM_0e10 = 0x14;
    }
    FUN_CODE_7994();
    DAT_EXTMEM_084a = (char)DAT_EXTMEM_0918 < '\0';
    bVar1 = 0;
    do {
      *(undefined1 *)CONCAT11('\t' - (((0xe7 < bVar1) << 7) >> 7),bVar1 + 0x18) =
           *(undefined1 *)CONCAT11('\t' - (((0xe6 < bVar1) << 7) >> 7),bVar1 + 0x19);
      bVar1 = bVar1 + 1;
    } while (bVar1 != 7);
    DAT_EXTMEM_091f = 0;
    DAT_EXTMEM_0928 = DAT_EXTMEM_0928 + -1;
  }
  return;
}


// ===== FUN_CODE_841d  [app]  callers: CODE:6c88 CODE:69ff CODE:80db CODE:6841

void FUN_CODE_841d(undefined1 param_1)

{
  char cVar1;
  char cVar2;
  
  cVar1 = DAT_EXTMEM_0fff;
  DAT_EXTMEM_0fff = DAT_EXTMEM_0fff + '\x01';
  if (DAT_EXTMEM_0fff == -1) {
    DAT_EXTMEM_0fff = '\0';
    DAT_EXTMEM_078f = '\x0f';
    DAT_EXTMEM_0790 = '\0';
    cVar2 = '\0';
    do {
      *(undefined1 *)CONCAT11(DAT_EXTMEM_078f,DAT_EXTMEM_0790) = 0;
      DAT_EXTMEM_0790 = DAT_EXTMEM_0790 + '\x01';
      if (DAT_EXTMEM_0790 == '\0') {
        DAT_EXTMEM_078f = DAT_EXTMEM_078f + '\x01';
      }
      cVar2 = cVar2 + '\x01';
    } while (cVar2 != -1);
  }
  *(undefined1 *)CONCAT11(0xf,cVar1) = param_1;
  return;
}


// ===== H_846B  [app]  callers: 

undefined1 H_846B(undefined1 *param_1,undefined1 *param_2,undefined1 param_3,char param_4)

{
  undefined1 uVar1;
  
  do {
    uVar1 = *param_2;
    param_2 = param_2 + '\x01';
    *param_1 = uVar1;
    param_1 = param_1 + '\x01';
    param_4 = param_4 + -1;
  } while (param_4 != '\0');
  return param_3;
}


// ===== FUN_CODE_853b  [app]  callers: CODE:813c CODE:3b7f CODE:42af CODE:2260

char FUN_CODE_853b(undefined1 param_1,char param_2,char param_3,char param_4,char param_5)

{
  byte bVar1;
  char cVar2;
  
  if (param_5 != '\0') {
    param_4 = param_4 + '\x01';
  }
  if (((param_5 != '\0' || param_4 != '\0') && (param_3 + 2U < 4)) &&
     (bVar1 = param_2 + 2, bVar1 < 4)) {
    bVar1 = (bVar1 * '\x02' | bVar1 >> 7) << 1 | (bVar1 & 0x7f) >> 6 | param_3 + 2U;
                    /* WARNING: Could not recover jumptable at 0x8560. Too many branches */
                    /* WARNING: Treating indirect jump as call */
    cVar2 = (*(code *)((ushort)(bVar1 << 1 | bVar1 >> 7) + 0x84bb))(param_1);
    return cVar2;
  }
  return param_3;
}


// ===== FUN_CODE_8561  [app]  callers: CODE:2c5b CODE:27d2 CODE:0e63 CODE:42af CODE:4f75 CODE:4dba CODE:348d CODE:1fea CODE:0e30 CODE:3e32 CODE:76f5 CODE:4a35 CODE:493d

undefined1 FUN_CODE_8561(undefined1 *param_1,undefined1 param_2,char param_3)

{
  if (param_3 == '\x01') {
    return *(undefined1 *)CONCAT11(param_2,param_1);
  }
  if (param_3 == '\0') {
    return *param_1;
  }
  if (param_3 == -2) {
    return *(undefined1 *)ZEXT12(param_1);
  }
  return *(undefined1 *)CONCAT11(param_2,param_1);
}


// ===== FUN_CODE_857a  [app]  callers: CODE:2c5b CODE:450c CODE:3d04 CODE:408f CODE:3563 CODE:42af CODE:405d CODE:4307 CODE:4f75 CODE:4dba CODE:4283 CODE:4034 CODE:4bc4 CODE:473f CODE:3812 CODE:4416 CODE:3bb9 CODE:3e32 CODE:4614 CODE:4256 CODE:3c58 CODE:39da CODE:493d

undefined1 FUN_CODE_857a(undefined2 param_1,byte param_2,char param_3,char param_4)

{
  char cVar1;
  byte bVar2;
  
  bVar2 = (byte)param_1;
  cVar1 = (char)((ushort)param_1 >> 8);
  if (param_4 == '\x01') {
    return *(undefined1 *)
            CONCAT11(cVar1 + (param_3 - ((CARRY1(bVar2,param_2) << 7) >> 7)),bVar2 + param_2);
  }
  if (param_4 == '\0') {
    return *(undefined1 *)(param_2 + bVar2);
  }
  if (param_4 == -2) {
    return *(undefined1 *)(ushort)(param_2 + bVar2);
  }
  return *(undefined1 *)
          CONCAT11(cVar1 + (param_3 - ((CARRY1(bVar2,param_2) << 7) >> 7)),bVar2 + param_2);
}


// ===== FUN_CODE_85a7  [app]  callers: CODE:0e63 CODE:3a8e CODE:4f75 CODE:4dba CODE:4034 CODE:3437 CODE:2bbe CODE:2fa7 CODE:0e30 CODE:2eb7 CODE:2f7c CODE:6733 CODE:0cbf

void FUN_CODE_85a7(undefined1 param_1,undefined1 *param_2,undefined1 param_3,char param_4)

{
  if (param_4 == '\x01') {
    *(undefined1 *)CONCAT11(param_3,param_2) = param_1;
    return;
  }
  if (param_4 == '\0') {
    *param_2 = param_1;
    return;
  }
  if (param_4 == -2) {
    *(undefined1 *)ZEXT12(param_2) = param_1;
  }
  return;
}


// ===== FUN_CODE_85b9  [app]  callers: CODE:3b7f CODE:512d CODE:3d04 CODE:4b29 CODE:4445 CODE:453b CODE:4f75 CODE:4dba CODE:4283 CODE:3626 CODE:4bc4 CODE:2bbe CODE:2fa7 CODE:2eb7 CODE:2f7c CODE:3bb9 CODE:3e32 CODE:36cf CODE:3c58 CODE:39da CODE:4a35

void FUN_CODE_85b9(undefined1 param_1,undefined2 param_2,byte param_3,char param_4,char param_5)

{
  byte bVar1;
  
  bVar1 = (byte)param_2;
  if (param_5 == '\x01') {
    *(undefined1 *)
     CONCAT11((char)((ushort)param_2 >> 8) + (param_4 - ((CARRY1(bVar1,param_3) << 7) >> 7)),
              bVar1 + param_3) = param_1;
    return;
  }
  if (param_5 == '\0') {
    *(undefined1 *)(param_3 + bVar1) = param_1;
    return;
  }
  if (param_5 == -2) {
    *(undefined1 *)(ushort)(param_3 + bVar1) = param_1;
  }
  return;
}


// ===== FUN_CODE_85db  [app]  callers: CODE:866a CODE:6d0d

void FUN_CODE_85db(char param_1,short param_2,byte param_3)

{
  byte bVar1;
  char cVar2;
  byte *pbVar3;
  char *pcVar4;
  
  pbVar3 = (byte *)(param_2 + 1);
  bVar1 = *pbVar3;
  *pbVar3 = bVar1 + param_3;
  cVar2 = (char)((ushort)pbVar3 >> 8);
  if ((char)pbVar3 == '\0') {
    cVar2 = cVar2 + -1;
  }
  pcVar4 = (char *)CONCAT11(cVar2,(char)pbVar3 + -1);
  *pcVar4 = *pcVar4 + (param_1 - ((CARRY1(bVar1,param_3) << 7) >> 7));
  return;
}


// ===== FUN_CODE_85f1  [app]  callers: CODE:1fea

char FUN_CODE_85f1(char param_1,short param_2,byte param_3)

{
  byte bVar1;
  char cVar2;
  byte *pbVar3;
  char *pcVar4;
  
  pbVar3 = (byte *)(param_2 + 1);
  bVar1 = *pbVar3;
  *pbVar3 = param_3 + bVar1;
  cVar2 = (char)((ushort)pbVar3 >> 8);
  if ((char)pbVar3 == '\0') {
    cVar2 = cVar2 + -1;
  }
  pcVar4 = (char *)CONCAT11(cVar2,(char)pbVar3 + -1);
  cVar2 = *pcVar4;
  *pcVar4 = param_1 + (cVar2 - ((CARRY1(param_3,bVar1) << 7) >> 7));
  return cVar2;
}


// ===== FUN_CODE_8607  [app]  callers: CODE:3d04 CODE:3e32

undefined1 FUN_CODE_8607(char param_1,undefined1 param_2,char param_3)

{
  if (param_3 == '\x01') {
    return *(undefined1 *)(CONCAT11(param_2,param_1) + 1);
  }
  if (param_3 == '\0') {
    return *(undefined1 *)(param_1 + '\x01');
  }
  if (param_3 == -2) {
    return *(undefined1 *)(ushort)(param_1 + 1);
  }
  return *(undefined1 *)(CONCAT11(param_2,param_1) + 1);
}


// ===== FUN_CODE_8632  [app]  callers: CODE:4bc4 CODE:3d04 CODE:408f CODE:3e32 CODE:4dba

undefined1 FUN_CODE_8632(undefined2 param_1,byte param_2,char param_3,char param_4)

{
  char cVar1;
  byte bVar2;
  
  bVar2 = (byte)param_1;
  cVar1 = (char)((ushort)param_1 >> 8);
  if (param_4 == '\x01') {
    return *(undefined1 *)
            (CONCAT11(cVar1 + (param_3 - ((CARRY1(bVar2,param_2) << 7) >> 7)),bVar2 + param_2) + 1);
  }
  if (param_4 == '\0') {
    return *(undefined1 *)(param_2 + bVar2 + '\x01');
  }
  if (param_4 == -2) {
    return *(undefined1 *)(ushort)(param_2 + bVar2 + 1);
  }
  return *(undefined1 *)(CONCAT11(cVar1 + param_3,bVar2) + 1 + (ushort)param_2);
}


// ===== FUN_CODE_866a  [app]  callers: CODE:4bc4 CODE:3d04 CODE:3e32

char FUN_CODE_866a(char param_1,undefined2 param_2,byte param_3,char param_4,char param_5,
                  char param_6)

{
  byte bVar1;
  byte *pbVar2;
  char cVar3;
  char *pcVar4;
  byte bVar5;
  char *pcVar6;
  
  if (param_6 == '\x01') {
    cVar3 = FUN_CODE_85db(param_1);
    return cVar3;
  }
  cVar3 = (char)param_2;
  if (param_6 == '\0') {
    pcVar4 = (char *)(cVar3 + param_4);
    pbVar2 = (byte *)(pcVar4 + '\x01');
    bVar1 = *pbVar2;
    *pbVar2 = param_3 + *pbVar2;
    param_1 = param_1 + (*pcVar4 - ((CARRY1(param_3,bVar1) << 7) >> 7));
    *pcVar4 = param_1;
    return param_1;
  }
  if (param_6 == -2) {
    bVar5 = cVar3 + param_4;
    bVar1 = *(byte *)(ushort)(bVar5 + 1);
    *(byte *)(ushort)(bVar5 + 1) = bVar1 + param_3;
    cVar3 = *(char *)(ushort)bVar5 + (param_1 - ((CARRY1(bVar1,param_3) << 7) >> 7));
    *(char *)(ushort)bVar5 = cVar3;
    return cVar3;
  }
  pcVar6 = (char *)CONCAT11((char)((ushort)param_2 >> 8) + param_5,cVar3 + param_4);
  return *pcVar6 + (param_1 - ((CARRY1(pcVar6[1],param_3) << 7) >> 7));
}


// ===== FUN_CODE_86b7  [app]  callers: CODE:3d04 CODE:3e32

void FUN_CODE_86b7(undefined1 param_1,undefined1 param_2,undefined1 *param_3,undefined1 param_4,
                  char param_5)

{
  if (param_5 == '\x01') {
    *(undefined1 *)CONCAT11(param_4,param_3) = param_1;
    ((undefined1 *)CONCAT11(param_4,param_3))[1] = param_2;
    return;
  }
  if (param_5 == '\0') {
    *param_3 = param_1;
    param_3['\x01'] = param_2;
    return;
  }
  if (param_5 == -2) {
    *(undefined1 *)ZEXT12(param_3) = param_1;
    *(undefined1 *)ZEXT12(param_3 + '\x01') = param_2;
  }
  return;
}


// ===== FUN_CODE_86d6  [app]  callers: CODE:4bc4 CODE:512d CODE:3d04 CODE:4b29 CODE:3e32 CODE:4f75

void FUN_CODE_86d6(undefined1 param_1,undefined2 param_2,undefined1 param_3,byte param_4,
                  char param_5,char param_6)

{
  byte bVar2;
  undefined1 *puVar1;
  
  bVar2 = (byte)param_2;
  if (param_6 == '\x01') {
    puVar1 = (undefined1 *)
             CONCAT11((char)((ushort)param_2 >> 8) + (param_5 - ((CARRY1(bVar2,param_4) << 7) >> 7))
                      ,bVar2 + param_4);
    *puVar1 = param_1;
    puVar1[1] = param_3;
    return;
  }
  if (param_6 == '\0') {
    *(undefined1 *)(param_4 + bVar2) = param_1;
    ((undefined1 *)(param_4 + bVar2))['\x01'] = param_3;
    return;
  }
  if (param_6 == -2) {
    *(undefined1 *)(ushort)(param_4 + bVar2) = param_1;
    *(undefined1 *)(ushort)(param_4 + bVar2 + 1) = param_3;
  }
  return;
}


// ===== FUN_CODE_8703  [app]  callers: CODE:0cbf

char FUN_CODE_8703(char param_1,byte param_2,byte param_3,byte param_4,char param_5,byte param_6,
                  byte param_7,byte param_8)

{
  byte bVar1;
  byte bVar2;
  byte bVar3;
  byte bVar4;
  byte bVar5;
  byte bVar6;
  byte bVar7;
  byte bVar8;
  
  bVar3 = (byte)((ushort)param_3 * (ushort)param_7);
  bVar4 = (byte)((ushort)param_6 * (ushort)param_4);
  bVar5 = bVar4 + bVar3;
  bVar6 = (byte)((ushort)param_2 * (ushort)param_8);
  bVar7 = bVar6 + bVar5;
  bVar8 = (byte)((ushort)param_4 * (ushort)param_7);
  bVar2 = (byte)((ushort)param_4 * (ushort)param_8 >> 8);
  bVar1 = (char)((ushort)param_4 * (ushort)param_7 >> 8) - ((CARRY1(bVar2,bVar8) << 7) >> 7);
  return ((param_6 * param_3 + param_2 * param_7 + param_5 * param_4 + param_1 * param_8 +
           ((char)((ushort)param_3 * (ushort)param_7 >> 8) - ((CARRY1(bVar4,bVar3) << 7) >> 7)) +
           (char)((ushort)param_6 * (ushort)param_4 >> 8) +
          ((char)((ushort)param_2 * (ushort)param_8 >> 8) - ((CARRY1(bVar6,bVar5) << 7) >> 7))) -
         ((CARRY1(bVar7,bVar1) << 7) >> 7)) -
         ((CARRY1(bVar7 + bVar1,
                  (char)((ushort)param_3 * (ushort)param_8 >> 8) -
                  ((CARRY1((byte)((ushort)param_3 * (ushort)param_8),bVar2 + bVar8) << 7) >> 7)) <<
          7) >> 7);
}


// ===== FUN_CODE_878e  [app]  callers: CODE:0cbf

byte FUN_CODE_878e(char param_1,char param_2,char param_3,byte param_4,byte param_5,byte param_6,
                  byte param_7,byte param_8)

{
  bool bVar1;
  bool bVar2;
  char cVar3;
  char cVar4;
  byte bVar5;
  byte bVar6;
  byte bVar7;
  byte bVar8;
  byte bVar9;
  byte bVar10;
  
  if (param_1 != '\0') {
    cVar4 = '\b';
    bVar7 = 0;
    do {
      bVar1 = CARRY1(param_8,param_8);
      param_8 = param_8 * '\x02';
      bVar10 = param_7 << 1 | bVar1;
      bVar8 = param_6 << 1 | param_7 >> 7;
      bVar9 = param_5 << 1 | param_6 >> 7;
      bVar6 = bVar7 << 1 | param_5 >> 7;
      bVar5 = param_1 - (((bVar9 < (byte)(param_2 -
                                         (((bVar8 < (byte)(param_3 -
                                                          (((bVar10 < param_4 - ((char)bVar7 >> 7))
                                                           << 7) >> 7))) << 7) >> 7))) << 7) >> 7);
      bVar7 = bVar6;
      if (bVar6 >= bVar5) {
        bVar7 = param_4 - (((bVar6 < bVar5) << 7) >> 7);
        bVar1 = bVar10 < bVar7;
        bVar10 = bVar10 - bVar7;
        bVar7 = param_3 - ((bVar1 << 7) >> 7);
        bVar1 = bVar8 < bVar7;
        bVar8 = bVar8 - bVar7;
        bVar9 = bVar9 - (param_2 - ((bVar1 << 7) >> 7));
        param_8 = param_8 + 1;
        bVar7 = bVar6 - bVar5;
      }
      cVar4 = cVar4 + -1;
      param_5 = bVar9;
      param_6 = bVar8;
      param_7 = bVar10;
    } while (cVar4 != '\0');
    return bVar9;
  }
  if (param_2 != '\0') {
    cVar4 = '\x10';
    bVar7 = 0;
    do {
      bVar1 = CARRY1(param_8,param_8);
      param_8 = param_8 * '\x02';
      bVar10 = param_6 << 1 | param_7 >> 7;
      bVar8 = param_5 << 1 | param_6 >> 7;
      bVar9 = bVar7 << 1 | param_5 >> 7;
      bVar5 = bVar7 & 0x80;
      cVar3 = C;
      if (cVar3 == '\0') {
        bVar2 = bVar9 < (byte)(param_2 -
                              (((bVar8 < (byte)(param_3 -
                                               (((bVar10 < param_4 - ((char)bVar7 >> 7)) << 7) >> 7)
                                               )) << 7) >> 7));
        bVar5 = bVar2 << 7;
        if (!bVar2) goto LAB_CODE_8809;
      }
      else {
        C = 0;
LAB_CODE_8809:
        bVar7 = param_4 - ((char)bVar5 >> 7);
        bVar2 = bVar10 < bVar7;
        bVar10 = bVar10 - bVar7;
        bVar7 = param_3 - ((bVar2 << 7) >> 7);
        bVar2 = bVar8 < bVar7;
        bVar8 = bVar8 - bVar7;
        bVar9 = bVar9 - (param_2 - ((bVar2 << 7) >> 7));
        param_8 = param_8 + 1;
      }
      cVar4 = cVar4 + -1;
      bVar7 = bVar9;
      param_5 = bVar8;
      param_6 = bVar10;
      param_7 = param_7 << 1 | bVar1;
      if (cVar4 == '\0') {
        return bVar9;
      }
    } while( true );
  }
  if (param_3 != '\0') {
    cVar4 = '\x18';
    bVar7 = 0;
    do {
      bVar1 = CARRY1(param_8,param_8);
      param_8 = param_8 * '\x02';
      bVar8 = param_5 << 1 | param_6 >> 7;
      bVar9 = bVar7 << 1 | param_5 >> 7;
      bVar5 = bVar7 & 0x80;
      cVar3 = C;
      if (cVar3 == '\0') {
        bVar2 = bVar9 < (byte)(param_3 - (((bVar8 < param_4 - ((char)bVar7 >> 7)) << 7) >> 7));
        bVar5 = bVar2 << 7;
        if (!bVar2) goto LAB_CODE_87dd;
      }
      else {
        C = 0;
LAB_CODE_87dd:
        bVar7 = param_4 - ((char)bVar5 >> 7);
        bVar2 = bVar8 < bVar7;
        bVar8 = bVar8 - bVar7;
        bVar9 = bVar9 - (param_3 - ((bVar2 << 7) >> 7));
        param_8 = param_8 + 1;
      }
      cVar4 = cVar4 + -1;
      bVar7 = bVar9;
      param_5 = bVar8;
      param_6 = param_6 << 1 | param_7 >> 7;
      param_7 = param_7 << 1 | bVar1;
      if (cVar4 == '\0') {
        return bVar8;
      }
    } while( true );
  }
  bVar5 = 0;
  bVar7 = param_5;
  if (param_4 != 0) {
    bVar7 = param_5 / param_4;
    bVar5 = param_5 % param_4;
  }
  cVar4 = '\x18';
  do {
    bVar1 = CARRY1(bVar7,bVar7);
    bVar7 = bVar7 * '\x02';
    bVar8 = bVar5 << 1 | param_6 >> 7;
    bVar9 = bVar5 & 0x80;
    cVar3 = C;
    if (cVar3 == '\0') {
      bVar2 = bVar8 < param_4 - ((char)bVar5 >> 7);
      bVar9 = bVar2 << 7;
      if (!bVar2) goto LAB_CODE_87ba;
    }
    else {
      C = 0;
LAB_CODE_87ba:
      bVar8 = bVar8 - (param_4 - ((char)bVar9 >> 7));
      bVar7 = bVar7 + 1;
    }
    cVar4 = cVar4 + -1;
    bVar5 = bVar8;
    param_6 = param_6 << 1 | param_7 >> 7;
    param_7 = param_7 << 1 | param_8 >> 7;
    param_8 = param_8 << 1 | bVar1;
    if (cVar4 == '\0') {
      return 0;
    }
  } while( true );
}


// ===== FUN_CODE_8820  [app]  callers: CODE:0cbf CODE:4dba

byte FUN_CODE_8820(char param_1,byte param_2,byte param_3,byte param_4,char param_5,char param_6,
                  char param_7,char param_8)

{
  byte bVar1;
  byte bVar2;
  byte bVar3;
  char in_PSW;
  
  bVar1 = param_8 - (in_PSW >> 7);
  bVar2 = param_7 - (((param_4 < bVar1) << 7) >> 7);
  bVar3 = param_6 - (((param_3 < bVar2) << 7) >> 7);
  return param_1 - (param_5 - (((param_2 < bVar3) << 7) >> 7)) |
         param_4 - bVar1 | param_3 - bVar2 | param_2 - bVar3;
}


// ===== FUN_CODE_8831  [app]  callers: CODE:0cbf

byte FUN_CODE_8831(byte param_1,byte param_2,byte param_3,byte param_4,byte param_5)

{
  byte bVar1;
  
  for (bVar1 = param_1; bVar1 != 0; bVar1 = bVar1 - 1) {
    param_1 = param_5 >> 1 | param_4 << 7;
    param_5 = param_1;
    param_4 = param_4 >> 1 | param_3 << 7;
    param_3 = param_3 >> 1 | param_2 << 7;
    param_2 = param_2 >> 1;
  }
  return param_1;
}


// ===== FUN_CODE_8844  [app]  callers: CODE:27d2 CODE:69ff CODE:0cbf CODE:6841 CODE:4dba

void FUN_CODE_8844(undefined1 *param_1,undefined1 param_2,undefined1 param_3,undefined1 param_4,
                  undefined1 param_5)

{
  *param_1 = param_2;
  param_1[1] = param_3;
  param_1[2] = param_4;
  param_1[3] = param_5;
  return;
}


// ===== FUN_CODE_8850  [app]  callers: CODE:450c CODE:5f41 CODE:408f CODE:5f2c CODE:42af CODE:4445 CODE:405d CODE:4307 CODE:453b CODE:3626 CODE:4416 CODE:3601 CODE:4614 CODE:493d

void FUN_CODE_8850(undefined2 param_1)

{
  code *UNRECOVERED_JUMPTABLE;
  undefined1 uStackX_0;
  undefined1 in_stack_000000ff;
  
  UNRECOVERED_JUMPTABLE = (code *)CONCAT11(uStackX_0,in_stack_000000ff);
  FUN_CODE_8867((char)((ushort)param_1 >> 8),(char)param_1);
  FUN_CODE_8867();
  FUN_CODE_8867();
  FUN_CODE_8867();
                    /* WARNING: Could not recover jumptable at 0x8866. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (*UNRECOVERED_JUMPTABLE)();
  return;
}


// ===== FUN_CODE_8867  [app]  callers: CODE:8850

undefined1 FUN_CODE_8867(undefined1 *param_1,undefined1 param_2,undefined1 param_3)

{
  *(undefined1 *)CONCAT11(param_2,param_3) = *param_1;
  return *param_1;
}


// ===== FUN_CODE_8881  [app]  callers: CODE:3d04 CODE:3e32 CODE:4dba

void FUN_CODE_8881(undefined2 param_1,byte param_2,char param_3,char param_4)

{
  char cVar1;
  byte bVar2;
  
  bVar2 = (byte)param_1;
  cVar1 = (char)((ushort)param_1 >> 8);
  if (param_4 == '\x01') {
    FUN_CODE_8975(cVar1 + (param_3 - ((CARRY1(bVar2,param_2) << 7) >> 7)),bVar2 + param_2);
    return;
  }
  if (param_4 == '\0') {
    FUN_CODE_8963(param_2 + bVar2);
    return;
  }
  if (param_4 == -2) {
    FUN_CODE_8987(param_2 + bVar2);
    return;
  }
  FUN_CODE_8999(cVar1 + (param_3 - ((CARRY1(bVar2,param_2) << 7) >> 7)),bVar2 + param_2);
  return;
}


// ===== FUN_CODE_88b1  [app]  callers: CODE:3d04 CODE:3e32

void FUN_CODE_88b1(char param_1,char param_2,char param_3)

{
  undefined1 in_stack_000000fc;
  undefined1 in_stack_000000fd;
  undefined1 in_stack_000000fe;
  
  if (param_3 == '\x01') {
    FUN_CODE_897e(param_1 + param_2,in_stack_000000fe,in_stack_000000fd,in_stack_000000fc);
    return;
  }
  if (param_3 == '\0') {
    FUN_CODE_896c(param_2 + param_1,in_stack_000000fe,in_stack_000000fd,in_stack_000000fc);
    return;
  }
  if (param_3 == -2) {
    FUN_CODE_8990(param_2 + param_1,in_stack_000000fe,in_stack_000000fd,in_stack_000000fc);
    return;
  }
  return;
}


// ===== FUN_CODE_890a  [app]  callers: CODE:27d2 CODE:0818 CODE:2718

void FUN_CODE_890a(char param_1)

{
  char *pcVar1;
  undefined1 uStackX_0;
  undefined1 in_stack_000000ff;
  
  for (pcVar1 = (char *)CONCAT11(uStackX_0,in_stack_000000ff);
      (*pcVar1 != '\0' || (pcVar1[1] != '\0')); pcVar1 = pcVar1 + 3) {
    if (pcVar1[2] == param_1) goto LAB_CODE_891a;
  }
  pcVar1 = pcVar1 + 2;
LAB_CODE_891a:
                    /* WARNING: Could not recover jumptable at 0x8924. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (**(code **)pcVar1)();
  return;
}


// ===== FUN_CODE_8930  [app]  callers: CODE:2eb7

void FUN_CODE_8930(char param_1,char param_2)

{
  char *pcVar1;
  undefined1 uStackX_0;
  undefined1 in_stack_000000ff;
  
  for (pcVar1 = (char *)CONCAT11(uStackX_0,in_stack_000000ff);
      (*pcVar1 != '\0' || (pcVar1[1] != '\0')); pcVar1 = pcVar1 + 4) {
    if ((pcVar1[2] == param_2) && (pcVar1[3] == param_1)) goto LAB_CODE_8940;
  }
  pcVar1 = pcVar1 + 2;
LAB_CODE_8940:
                    /* WARNING: Could not recover jumptable at 0x894a. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (**(code **)pcVar1)();
  return;
}


// ===== FUN_CODE_895d  [app]  callers: CODE:3400

void FUN_CODE_895d(undefined1 param_1,undefined1 param_2)

{
                    /* WARNING: Could not recover jumptable at 0x8962. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (*(code *)CONCAT11(param_2,param_1))();
  return;
}


// ===== FUN_CODE_8961  [app]  callers: CODE:19a7 CODE:1e32 CODE:192c CODE:7b31

void FUN_CODE_8961(code *UNRECOVERED_JUMPTABLE)

{
                    /* WARNING: Could not recover jumptable at 0x8962. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (*UNRECOVERED_JUMPTABLE)();
  return;
}


// ===== FUN_CODE_8963  [app]  callers: CODE:8881

undefined1 FUN_CODE_8963(char param_1)

{
  return *(undefined1 *)(param_1 + '\x02');
}


// ===== FUN_CODE_896c  [app]  callers: CODE:88b1

void FUN_CODE_896c(undefined1 *param_1,undefined1 param_2,undefined1 param_3,undefined1 param_4)

{
  *param_1 = param_4;
  param_1['\x01'] = param_3;
  param_1['\x02'] = param_2;
  return;
}


// ===== FUN_CODE_8975  [app]  callers: CODE:8881

undefined1 FUN_CODE_8975(short param_1)

{
  return *(undefined1 *)(param_1 + 2);
}


// ===== FUN_CODE_897e  [app]  callers: CODE:88b1

void FUN_CODE_897e(undefined1 *param_1,undefined1 param_2,undefined1 param_3,undefined1 param_4)

{
  *param_1 = param_4;
  param_1[1] = param_3;
  param_1[2] = param_2;
  return;
}


// ===== FUN_CODE_8987  [app]  callers: CODE:8881

undefined1 FUN_CODE_8987(char param_1)

{
  return *(undefined1 *)(ushort)(param_1 + 2);
}


// ===== FUN_CODE_8990  [app]  callers: CODE:88b1

void FUN_CODE_8990(byte param_1,undefined1 param_2,undefined1 param_3,undefined1 param_4)

{
  *(undefined1 *)(ushort)param_1 = param_4;
  *(undefined1 *)(ushort)(param_1 + 1) = param_3;
  *(undefined1 *)(ushort)(param_1 + 2) = param_2;
  return;
}


// ===== FUN_CODE_8999  [app]  callers: CODE:8881

undefined1 FUN_CODE_8999(short param_1)

{
  return *(undefined1 *)(param_1 + 2);
}


// ===== FUN_CODE_b100  [app]  callers: 

void FUN_CODE_b100(undefined1 param_1,char param_2)

{
  undefined1 *puVar1;
  
  BANK0_R0 = BANK0_R0 + '\x01';
  nop();
  nop();
  nop();
  nop();
  nop();
  nop();
  nop();
  nop();
  nop();
  nop();
  nop();
  nop();
  nop();
  nop();
  nop();
  nop();
  nop();
  nop();
  nop();
  nop();
  nop();
  nop();
  nop();
  nop();
  nop();
  nop();
  nop();
  nop();
  nop();
  nop();
  nop();
  nop();
  nop();
  nop();
  nop();
  nop();
  nop();
  nop();
  nop();
  nop();
  nop();
  nop();
  nop();
  nop();
  nop();
  nop();
  nop();
  nop();
  nop();
  nop();
  nop();
  nop();
  nop();
  nop();
  nop();
  nop();
  nop();
  nop();
  nop();
  nop();
  nop();
  nop();
  nop();
  nop();
  nop();
  nop();
  nop();
  nop();
  nop();
  nop();
  nop();
  nop();
  nop();
  nop();
  nop();
  nop();
  nop();
  nop();
  nop();
  nop();
  nop();
  nop();
  nop();
  nop();
  nop();
  nop();
  nop();
  nop();
  nop();
  nop();
  nop();
  nop();
  nop();
  nop();
  nop();
  nop();
  nop();
  nop();
  nop();
  nop();
  nop();
  nop();
  nop();
  nop();
  nop();
  nop();
  nop();
  nop();
  nop();
  nop();
  nop();
  nop();
  nop();
  nop();
  nop();
  nop();
  nop();
  nop();
  nop();
  nop();
  nop();
  nop();
  nop();
  nop();
  nop();
  nop();
  nop();
  nop();
  nop();
  nop();
  nop();
  nop();
  nop();
  nop();
  nop();
  nop();
  nop();
  nop();
  nop();
  nop();
  nop();
  nop();
  nop();
  nop();
  nop();
  nop();
  nop();
  nop();
  nop();
  nop();
  nop();
  nop();
  nop();
  nop();
  nop();
  nop();
  nop();
  nop();
  nop();
  nop();
  nop();
  nop();
  nop();
  nop();
  nop();
  nop();
  nop();
  nop();
  nop();
  nop();
  nop();
  nop();
  nop();
  nop();
  nop();
  nop();
  nop();
  nop();
  nop();
  nop();
  nop();
  nop();
  nop();
  nop();
  nop();
  nop();
  nop();
  nop();
  nop();
  nop();
  nop();
  nop();
  nop();
  nop();
  nop();
  nop();
  nop();
  nop();
  nop();
  nop();
  nop();
  nop();
  nop();
  nop();
  nop();
  nop();
  nop();
  nop();
  nop();
  nop();
  nop();
  nop();
  nop();
  nop();
  nop();
  nop();
  nop();
  nop();
  nop();
  nop();
  nop();
  nop();
  nop();
  nop();
  nop();
  nop();
  nop();
  nop();
  nop();
  nop();
  nop();
  nop();
  nop();
  nop();
  nop();
  nop();
  nop();
  nop();
  nop();
  nop();
  nop();
  nop();
  nop();
  nop();
  nop();
  nop();
  nop();
  nop();
  nop();
  nop();
  nop();
  puVar1 = &DAT_INTMEM_7f;
  do {
    *puVar1 = 0;
    puVar1 = puVar1 + -1;
  } while (puVar1 != (undefined1 *)0x0);
  SP = 0xb;
  FUN_CODE_f520(param_2 + -1,param_1);
  return;
}


// ===== thunk_FUN_CODE_e003  [bootloader]  callers: CODE:0f7b

void thunk_FUN_CODE_e003(void)

{
  undefined1 *puVar1;
  
  puVar1 = &DAT_INTMEM_7f;
  do {
    *puVar1 = 0;
    puVar1 = puVar1 + -1;
  } while (puVar1 != (undefined1 *)0x0);
  SP = 0xb;
  FUN_CODE_f520();
  return;
}


// ===== FUN_CODE_e003  [bootloader]  callers: 

void FUN_CODE_e003(void)

{
  undefined1 *puVar1;
  
  puVar1 = &DAT_INTMEM_7f;
  do {
    *puVar1 = 0;
    puVar1 = puVar1 + -1;
  } while (puVar1 != (undefined1 *)0x0);
  SP = 0xb;
  FUN_CODE_f520();
  return;
}


// ===== FUN_CODE_e00f  [bootloader]  callers: CODE:e6ff

void FUN_CODE_e00f(void)

{
  return;
}


// ===== H_E022  [bootloader]  callers: 

void H_E022(void)

{
  return;
}


// ===== thunk_FUN_CODE_ef2f  [bootloader]  callers: CODE:f520

void thunk_FUN_CODE_ef2f(void)

{
  DAT_EXTMEM_2fe0 = 2;
  FUN_CODE_f12c(0,1);
  DAT_EXTMEM_2fe4 = DAT_EXTMEM_2fe4 & 0xef;
  DAT_EXTMEM_2fe8 = DAT_EXTMEM_2fe8 & 0xef;
  DAT_EXTMEM_2fe0 = 0;
  DAT_EXTMEM_2f50 = 8;
  FUN_CODE_f12c(1);
  DAT_EXTMEM_2f50 = 0x71;
  DAT_EXTMEM_2f54 = 0;
  DAT_EXTMEM_2f52 = 4;
  DAT_EXTMEM_2f40 = 1;
  DAT_EXTMEM_2f44 = 3;
  while ((DAT_EXTMEM_2f52 >> 2 & 1) != 0) {
    DAT_EXTMEM_2f52 = 4;
    FUN_CODE_f896();
  }
  return;
}


// ===== FUN_CODE_e061  [bootloader]  callers: CODE:e5cd

undefined1
FUN_CODE_e061(undefined1 param_1,undefined1 param_2,undefined1 param_3,undefined1 param_4,
             char param_5)

{
  char cVar1;
  undefined1 uVar2;
  undefined2 uVar3;
  
  DAT_EXTMEM_041e = 0;
  DAT_EXTMEM_0418 = param_4;
  DAT_EXTMEM_0419 = param_3;
  DAT_EXTMEM_041a = param_2;
  cVar1 = FUN_CODE_f289(1,param_2,param_3,param_4);
  if (cVar1 == '\x01') {
    cVar1 = FUN_CODE_f289(1,DAT_EXTMEM_041a,DAT_EXTMEM_0419,DAT_EXTMEM_0418);
    uVar2 = FUN_CODE_f316(2,0);
    FUN_CODE_f83b(DAT_EXTMEM_041d + 4,DAT_EXTMEM_041c - (((0xfb < DAT_EXTMEM_041d) << 7) >> 7),
                  DAT_EXTMEM_041b,param_1,uVar2);
    DAT_EXTMEM_041f = 0;
    DAT_EXTMEM_0420 = cVar1;
    if (cVar1 == '\0') {
      DAT_EXTMEM_041e = 0x9e;
      DAT_EXTMEM_041f = 0;
      return 0x9e;
    }
  }
  else {
    if (cVar1 == '\x02') {
      uVar3 = 0x44;
    }
    else {
      if (cVar1 != '\x03') {
        if (cVar1 != '\t') {
          if (cVar1 == '\n') {
            uVar2 = FUN_CODE_f289(3,DAT_EXTMEM_041a,DAT_EXTMEM_0419,DAT_EXTMEM_0418);
            uVar3 = 0x44;
          }
          else {
            if (cVar1 != '\v') {
              DAT_EXTMEM_041e = 0x86;
              return 0x86;
            }
            uVar2 = FUN_CODE_f316(2,DAT_EXTMEM_041a,DAT_EXTMEM_0419,DAT_EXTMEM_0418);
            uVar3 = 0x45;
          }
          FUN_CODE_f2c8(uVar2,uVar3,DAT_EXTMEM_041d,DAT_EXTMEM_041c,DAT_EXTMEM_041b);
          FUN_CODE_eb67();
          return DAT_EXTMEM_041e;
        }
        DAT_EXTMEM_0f0f = '\0';
        uVar2 = FUN_CODE_f316(6,DAT_EXTMEM_041a,DAT_EXTMEM_0419,DAT_EXTMEM_0418);
        DAT_EXTMEM_0426 = DAT_EXTMEM_041b;
        DAT_EXTMEM_0427 = DAT_EXTMEM_041c;
        DAT_EXTMEM_0428 = DAT_EXTMEM_041d;
        FUN_CODE_ebf6(uVar2,BANK0_R4);
        if (param_5 == '\0') {
          return DAT_EXTMEM_041e;
        }
        uVar2 = FUN_CODE_f289(1,DAT_EXTMEM_041a,DAT_EXTMEM_0419,DAT_EXTMEM_0418);
        uVar2 = FUN_CODE_f316(2,0,uVar2);
        FUN_CODE_f83b(0,0,0,param_1,uVar2);
        FUN_CODE_eb5f(0x41b);
        if (DAT_EXTMEM_0f0f != '3') {
          return DAT_EXTMEM_041e;
        }
        FUN_CODE_f455();
        return DAT_EXTMEM_041e;
      }
      uVar3 = 0x45;
    }
    DAT_EXTMEM_0420 = '\x01';
    DAT_EXTMEM_041f = 0;
    FUN_CODE_f289(uVar3,DAT_EXTMEM_041d,DAT_EXTMEM_041c,DAT_EXTMEM_041b);
    FUN_CODE_f2c8(4);
    cVar1 = '\x01';
  }
  DAT_EXTMEM_0433 = DAT_EXTMEM_041b;
  DAT_EXTMEM_0434 = DAT_EXTMEM_041c;
  DAT_EXTMEM_0435 = DAT_EXTMEM_041d;
  FUN_CODE_f7d5(0,cVar1);
  return DAT_EXTMEM_041e;
}


// ===== FUN_CODE_e276  [bootloader]  callers: 

void FUN_CODE_e276(undefined1 param_1,undefined1 param_2,undefined1 param_3)

{
  ushort uVar1;
  char cVar2;
  
  DAT_EXTMEM_0425 = 0;
  DAT_EXTMEM_0426 = 0;
  DAT_EXTMEM_0427 = 0;
  DAT_EXTMEM_0428 = 0;
  DAT_EXTMEM_0429 = 0;
  DAT_EXTMEM_042a = 0;
  DAT_EXTMEM_041f = param_3;
  DAT_EXTMEM_0420 = param_2;
  DAT_EXTMEM_0421 = param_1;
  cVar2 = FUN_CODE_f289(3,param_1,param_2,param_3);
  DAT_EXTMEM_042b = FUN_CODE_f289(2);
  DAT_EXTMEM_042c = FUN_CODE_f289(6);
  DAT_EXTMEM_042d = FUN_CODE_f289(7);
  if (cVar2 == '!') {
    FUN_CODE_e3c7();
    return;
  }
  if (cVar2 != '\"') {
    if (cVar2 - 1U < 7) {
      uVar1 = (ushort)(cVar2 - 1U) * 3;
                    /* WARNING: Could not recover jumptable at 0xe2e9. Too many branches */
                    /* WARNING: Treating indirect jump as call */
      (*(code *)(CONCAT11((char)(uVar1 >> 8) + -0x1e,0xea) + (uVar1 & 0xff)))();
      return;
    }
    FUN_CODE_e3ff();
    return;
  }
  FUN_CODE_e3e8();
  return;
}


// ===== H_E2A6  [bootloader]  callers: 

void H_E2A6(char param_1)

{
  ushort uVar1;
  
  DAT_EXTMEM_042b = FUN_CODE_f289(2);
  DAT_EXTMEM_042c = FUN_CODE_f289(6);
  DAT_EXTMEM_042d = FUN_CODE_f289(7);
  if (param_1 == '!') {
    FUN_CODE_e3c7();
    return;
  }
  if (param_1 != '\"') {
    if (param_1 - 1U < 7) {
      uVar1 = (ushort)(param_1 - 1U) * 3;
                    /* WARNING: Could not recover jumptable at 0xe2e9. Too many branches */
                    /* WARNING: Treating indirect jump as call */
      (*(code *)(CONCAT11((char)(uVar1 >> 8) + -0x1e,0xea) + (uVar1 & 0xff)))();
      return;
    }
    FUN_CODE_e3ff();
    return;
  }
  FUN_CODE_e3e8();
  return;
}


// ===== H_E304  [bootloader]  callers: 

void H_E304(undefined1 param_1,undefined1 *param_2)

{
  *param_2 = param_1;
  param_2[1] = 0xf9;
  param_2[2] = 10;
  DAT_EXTMEM_0429 = 0;
  DAT_EXTMEM_042a = uCODEf90a;
  FUN_CODE_e407();
  return;
}


// ===== FUN_CODE_e312  [bootloader]  callers: 

undefined1 FUN_CODE_e312(void)

{
  undefined1 uVar1;
  
  if (DAT_EXTMEM_042b == '\0') {
    DAT_EXTMEM_0426 = 0xff;
    DAT_EXTMEM_0427 = 0xf9;
    DAT_EXTMEM_0428 = 0x1c;
    DAT_EXTMEM_0429 = DAT_CODE_f91f;
    DAT_EXTMEM_042a = DAT_CODE_f91e;
    uVar1 = FUN_CODE_e407();
    return uVar1;
  }
  DAT_EXTMEM_0425 = 0x91;
  return 0x91;
}


// ===== FUN_CODE_e347  [bootloader]  callers: 

undefined1 FUN_CODE_e347(void)

{
  undefined1 uVar1;
  
  if (DAT_EXTMEM_042b == '\x01') {
    DAT_EXTMEM_0428 = 0x54;
    DAT_EXTMEM_042a = DAT_CODE_f954;
  }
  else if (DAT_EXTMEM_042b == '\x02') {
    DAT_EXTMEM_0428 = 0x72;
    DAT_EXTMEM_042a = uCODEf972;
  }
  else if (DAT_EXTMEM_042b == '\x03') {
    DAT_EXTMEM_0428 = 0x94;
    DAT_EXTMEM_042a = DAT_CODE_f994;
  }
  else {
    if (DAT_EXTMEM_042b != '\0') {
      return DAT_EXTMEM_0425;
    }
    DAT_EXTMEM_0428 = 0x50;
    DAT_EXTMEM_042a = DAT_CODE_f950;
  }
  DAT_EXTMEM_0427 = 0xf9;
  DAT_EXTMEM_0426 = 0xff;
  DAT_EXTMEM_0429 = 0;
  uVar1 = FUN_CODE_e407();
  return uVar1;
}


// ===== FUN_CODE_e3c7  [bootloader]  callers: CODE:e2a6

void FUN_CODE_e3c7(void)

{
  DAT_EXTMEM_0426 = 0xff;
  DAT_EXTMEM_0427 = 0xf9;
  DAT_EXTMEM_0428 = 0x2e;
  DAT_EXTMEM_0429 = 0;
  DAT_EXTMEM_042a = 9;
  FUN_CODE_e407();
  return;
}


// ===== thunk_FUN_CODE_e3e0  [bootloader]  callers: 

undefined1 thunk_FUN_CODE_e3e0(void)

{
  DAT_EXTMEM_0425 = 0x92;
  return 0x92;
}


// ===== FUN_CODE_e3e0  [bootloader]  callers: 

undefined1 FUN_CODE_e3e0(void)

{
  DAT_EXTMEM_0425 = 0x92;
  return 0x92;
}


// ===== FUN_CODE_e3e8  [bootloader]  callers: CODE:e2a6

void FUN_CODE_e3e8(void)

{
  DAT_EXTMEM_0426 = 0xff;
  DAT_EXTMEM_0427 = 0xf9;
  DAT_EXTMEM_0428 = 0xb4;
  DAT_EXTMEM_0429 = 0;
  DAT_EXTMEM_042a = 0x15;
  FUN_CODE_e407();
  return;
}


// ===== FUN_CODE_e3ff  [bootloader]  callers: CODE:e2a6

undefined1 FUN_CODE_e3ff(void)

{
  DAT_EXTMEM_0425 = 0x93;
  return 0x93;
}


// ===== FUN_CODE_e407  [bootloader]  callers: CODE:e3c7 CODE:e347 CODE:e3e8

undefined1 FUN_CODE_e407(void)

{
  if (DAT_EXTMEM_042d - (((DAT_EXTMEM_042a < DAT_EXTMEM_042c + 1) << 7) >> 7) <= DAT_EXTMEM_0429) {
    DAT_EXTMEM_0429 = DAT_EXTMEM_042d;
    DAT_EXTMEM_042a = DAT_EXTMEM_042c;
  }
  DAT_EXTMEM_0433 = DAT_EXTMEM_0422;
  DAT_EXTMEM_0434 = DAT_EXTMEM_0423;
  DAT_EXTMEM_0435 = DAT_EXTMEM_0424;
  FUN_CODE_f7d5(DAT_EXTMEM_0428,DAT_EXTMEM_0427,DAT_EXTMEM_0426,DAT_EXTMEM_0429,DAT_EXTMEM_042a);
  return DAT_EXTMEM_0425;
}


// ===== FUN_CODE_e45b  [bootloader]  callers: CODE:e5cd

undefined1 FUN_CODE_e45b(undefined1 param_1,undefined1 param_2,undefined1 param_3)

{
  byte bVar1;
  undefined1 uVar2;
  
  DAT_EXTMEM_041e = 0;
  DAT_EXTMEM_0418 = param_3;
  DAT_EXTMEM_0419 = param_2;
  DAT_EXTMEM_041a = param_1;
  bVar1 = FUN_CODE_f289(1,param_1,param_2,param_3);
  if (9 < bVar1) {
    DAT_EXTMEM_041e = 0x86;
    return 0x86;
  }
                    /* WARNING: Could not recover jumptable at 0xe48a. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  uVar2 = (*(code *)((ushort)(bVar1 * '\x03') + 0xe48b))();
  return uVar2;
}


// ===== FUN_CODE_e5cd  [bootloader]  callers: CODE:f730

void FUN_CODE_e5cd(undefined1 param_1,undefined1 param_2,undefined1 param_3)

{
  bool bVar1;
  char cVar2;
  byte bVar3;
  byte bVar4;
  undefined1 uVar5;
  
  DAT_EXTMEM_0409 = 0;
  DAT_EXTMEM_040a = 0;
  DAT_EXTMEM_040b = 0;
  DAT_EXTMEM_040c = 0;
  uVar5 = BANK0_R7;
  DAT_EXTMEM_0406 = param_3;
  DAT_EXTMEM_0407 = param_2;
  DAT_EXTMEM_0408 = param_1;
  while( true ) {
    if ((((DAT_EXTMEM_2f41 & 1) == 0) && ((DAT_EXTMEM_2f41 >> 1 & 1) == 0)) &&
       ((DAT_EXTMEM_2f41 >> 2 & 1) == 0)) {
      DAT_EXTMEM_040a = 1;
      DAT_EXTMEM_040b = 4;
      DAT_EXTMEM_040c = 0x10;
      bVar4 = DAT_EXTMEM_2f41;
      DAT_EXTMEM_0435 = uVar5;
      FUN_CODE_ed12(8);
      if (bVar4 != 0) {
        DAT_EXTMEM_040d = 1;
        DAT_EXTMEM_040e = 4;
        DAT_EXTMEM_040f = 0x10;
        DAT_EXTMEM_2f52 = 0x11;
        bVar3 = FUN_CODE_f270(0x10,4,1);
        if ((bVar3 & 0x60) == 0) {
          DAT_EXTMEM_041b = DAT_EXTMEM_0406;
          DAT_EXTMEM_041c = DAT_EXTMEM_0407;
          DAT_EXTMEM_041d = DAT_EXTMEM_0408;
          FUN_CODE_e45b();
          DAT_EXTMEM_0409 = bVar4;
        }
        else {
          bVar4 = FUN_CODE_f270(DAT_EXTMEM_040f,DAT_EXTMEM_040e,DAT_EXTMEM_040d);
          bVar4 = bVar4 & 0x60;
          if (bVar4 == 0x20) {
            DAT_EXTMEM_041b = DAT_EXTMEM_0406;
            DAT_EXTMEM_041c = DAT_EXTMEM_0407;
            DAT_EXTMEM_041d = DAT_EXTMEM_0408;
            FUN_CODE_e061();
            DAT_EXTMEM_0409 = bVar4;
          }
          else {
            DAT_EXTMEM_0409 = 0x85;
          }
        }
        if (DAT_EXTMEM_0409 == 0) {
          uVar5 = 1;
        }
        else {
          uVar5 = 2;
        }
        FUN_CODE_f2c8(uVar5,3,DAT_EXTMEM_0408,DAT_EXTMEM_0407,DAT_EXTMEM_0406);
        return;
      }
      FUN_CODE_f8d0();
      return;
    }
    DAT_EXTMEM_2f64 = 1;
    bVar4 = DAT_EXTMEM_2f41;
    FUN_CODE_f8ca();
    while ((DAT_EXTMEM_2f40 >> 1 & 1) != 0) {
      FUN_CODE_f76d(0x406);
      bVar1 = bVar4 != 0;
      bVar4 = 0;
      if (bVar1) {
        return;
      }
    }
    cVar2 = '\0';
    FUN_CODE_f8d7();
    if (cVar2 == '\0') break;
    DAT_EXTMEM_2f52 = 0x11;
  }
  return;
}


// ===== FUN_CODE_e6ff  [bootloader]  callers: 

undefined1 FUN_CODE_e6ff(byte param_1,undefined1 param_2,undefined1 param_3,undefined1 param_4)

{
  char cVar1;
  byte bVar2;
  byte bVar3;
  char *pcVar4;
  
  DAT_EXTMEM_0425 = 0;
  DAT_EXTMEM_0426 = 0;
  DAT_EXTMEM_0427 = 0;
  DAT_EXTMEM_0428 = 0;
  DAT_EXTMEM_0429 = 0;
  DAT_EXTMEM_041f = param_4;
  DAT_EXTMEM_0420 = param_3;
  DAT_EXTMEM_0421 = param_2;
  FUN_CODE_f24a(0x2a,0xca,0xf9,0xff,4,1,0,2);
  bVar2 = FUN_CODE_f270(DAT_EXTMEM_0421,DAT_EXTMEM_0420,DAT_EXTMEM_041f);
  DAT_EXTMEM_042c = bVar2 & 0x1f;
  bVar2 = FUN_CODE_f316(4);
  if (DAT_EXTMEM_042c != 1) {
    if (DAT_EXTMEM_042c == 2) {
      if (bVar2 == 0 && param_1 == 0) {
        DAT_EXTMEM_0428 = FUN_CODE_f270(DAT_EXTMEM_0424,DAT_EXTMEM_0423,DAT_EXTMEM_0422);
      }
      else {
        bVar3 = bVar2 & 0x7f;
        cVar1 = '\a';
        DAT_EXTMEM_0427 = bVar2;
        do {
          DAT_EXTMEM_0427 = DAT_EXTMEM_0427 >> 1 | param_1 << 7;
          cVar1 = cVar1 + -1;
          param_1 = param_1 >> 1;
        } while (cVar1 != '\0');
        if (4 < bVar3) {
          DAT_EXTMEM_0425 = 0x87;
          DAT_EXTMEM_0426 = bVar3;
          return 0x87;
        }
        pcVar4 = (char *)CONCAT11(-7 - (((0xfd < bVar2 * '\x02') << 7) >> 7),bVar2 * '\x02' + 2);
        bVar2 = pcVar4[1];
        if (*(char *)CONCAT11(BANK1_R0 + (*pcVar4 - ((CARRY1(BANK1_R1,bVar2) << 7) >> 7)),
                              BANK1_R1 + bVar2) == '\0') {
          DAT_EXTMEM_0425 = 0x89;
          DAT_EXTMEM_0426 = bVar3;
          return 0x89;
        }
        DAT_EXTMEM_0426 = bVar3;
        FUN_CODE_e00f();
        DAT_EXTMEM_0428 = bVar3;
      }
    }
    else {
      if (DAT_EXTMEM_042c != 0) {
        DAT_EXTMEM_0425 = 0x8a;
        return 0x8a;
      }
      DAT_EXTMEM_0428 = DAT_CODE_f923 >> 6 & 1;
    }
  }
  DAT_EXTMEM_042a = DAT_EXTMEM_0428;
  DAT_EXTMEM_042b = DAT_EXTMEM_0429;
  DAT_EXTMEM_0433 = DAT_EXTMEM_0422;
  DAT_EXTMEM_0434 = DAT_EXTMEM_0423;
  DAT_EXTMEM_0435 = DAT_EXTMEM_0424;
  FUN_CODE_f7d5(0x2a,4,1,0,2);
  return DAT_EXTMEM_0425;
}


// ===== FUN_CODE_e823  [bootloader]  callers: CODE:f7d5

void FUN_CODE_e823(undefined1 param_1,undefined1 param_2,undefined1 param_3,byte param_4,
                  byte param_5)

{
  bool bVar1;
  byte bVar2;
  
  DAT_EXTMEM_043e = 0;
  DAT_EXTMEM_043f = '\x01';
  DAT_EXTMEM_0436 = param_3;
  DAT_EXTMEM_0437 = param_2;
  DAT_EXTMEM_0438 = param_1;
  DAT_EXTMEM_0439 = param_4;
  DAT_EXTMEM_043a = param_5;
  FUN_CODE_f2c8(1,0x47,DAT_EXTMEM_043d,DAT_EXTMEM_043c,DAT_EXTMEM_043b);
  do {
    if (DAT_EXTMEM_0439 < (byte)-(((DAT_EXTMEM_043a < 0x40) << 7) >> 7)) {
      DAT_EXTMEM_043e = DAT_EXTMEM_043a;
    }
    else {
      DAT_EXTMEM_043e = 0x40;
    }
    bVar1 = DAT_EXTMEM_043a < DAT_EXTMEM_043e;
    DAT_EXTMEM_043a = DAT_EXTMEM_043a - DAT_EXTMEM_043e;
    DAT_EXTMEM_0439 = DAT_EXTMEM_0439 + ((bVar1 << 7) >> 7);
    bVar2 = DAT_EXTMEM_043e;
    FUN_CODE_f6f2(0x43b);
    if (bVar2 == 0) {
      return;
    }
    DAT_EXTMEM_0443 = DAT_EXTMEM_0436;
    DAT_EXTMEM_0444 = DAT_EXTMEM_0437;
    DAT_EXTMEM_0445 = DAT_EXTMEM_0438;
    DAT_EXTMEM_0446 = DAT_EXTMEM_043e;
    FUN_CODE_f478(DAT_EXTMEM_043b);
    DAT_EXTMEM_0444 = DAT_EXTMEM_043f;
    DAT_EXTMEM_0445 = 0;
    DAT_EXTMEM_0446 = DAT_EXTMEM_043b;
    DAT_EXTMEM_0447 = DAT_EXTMEM_043c;
    DAT_EXTMEM_0448 = DAT_EXTMEM_043d;
    FUN_CODE_ed90(DAT_EXTMEM_043e);
    if (bVar2 == 0) {
      return;
    }
    FUN_CODE_f2ea(0,0x437,DAT_EXTMEM_043e);
    DAT_EXTMEM_043f = DAT_EXTMEM_043f != '\x01';
    bVar2 = DAT_EXTMEM_0439;
    if (DAT_EXTMEM_0439 == 0) {
      bVar2 = DAT_EXTMEM_043a;
    }
  } while (bVar2 != 0);
  return;
}


// ===== FUN_CODE_e931  [bootloader]  callers: 

undefined1 FUN_CODE_e931(byte param_1)

{
  char cVar1;
  byte bVar2;
  char *pcVar3;
  
  DAT_EXTMEM_0425 = 0;
  DAT_EXTMEM_0426 = 0;
  DAT_EXTMEM_0427 = 0;
  DAT_EXTMEM_0429 = FUN_CODE_f316(2);
  DAT_EXTMEM_0428 = param_1;
  bVar2 = FUN_CODE_f316(4);
  if (DAT_EXTMEM_0428 == 0) {
    if (DAT_EXTMEM_0429 == '\x01') {
      return DAT_EXTMEM_0425;
    }
    if (DAT_EXTMEM_0429 == '\x02') {
      DAT_EXTMEM_0425 = 0x8e;
      return 0x8e;
    }
    if (DAT_EXTMEM_0429 == '\0') {
      if (bVar2 == 0 && param_1 == 0) {
        FUN_CODE_f2b6(0,DAT_EXTMEM_0424,DAT_EXTMEM_0423,DAT_EXTMEM_0422);
        return DAT_EXTMEM_0425;
      }
      DAT_EXTMEM_0426 = bVar2 & 0x7f;
      cVar1 = '\a';
      DAT_EXTMEM_0427 = bVar2;
      do {
        DAT_EXTMEM_0427 = DAT_EXTMEM_0427 >> 1 | param_1 << 7;
        cVar1 = cVar1 + -1;
        param_1 = param_1 >> 1;
      } while (cVar1 != '\0');
      if (4 < DAT_EXTMEM_0426) {
        DAT_EXTMEM_0425 = 0x87;
        return 0x87;
      }
      pcVar3 = (char *)CONCAT11(-7 - (((0xfd < bVar2 * '\x02') << 7) >> 7),bVar2 * '\x02' + 2);
      bVar2 = pcVar3[1];
      if ((*(byte *)CONCAT11(BANK1_R0 + (*pcVar3 - ((CARRY1(BANK1_R1,bVar2) << 7) >> 7)),
                             BANK1_R1 + bVar2) & 1) != 1) {
        DAT_EXTMEM_0425 = 0x89;
        return 0x89;
      }
      FUN_CODE_f4cd(0,DAT_EXTMEM_0426);
      return DAT_EXTMEM_0425;
    }
  }
  DAT_EXTMEM_0425 = 0x8d;
  return 0x8d;
}


// ===== FUN_CODE_e9f6  [bootloader]  callers: 

undefined1 FUN_CODE_e9f6(byte param_1)

{
  char cVar1;
  byte bVar2;
  char *pcVar3;
  
  DAT_EXTMEM_0425 = 0;
  DAT_EXTMEM_0426 = 0;
  DAT_EXTMEM_0427 = 0;
  DAT_EXTMEM_0429 = FUN_CODE_f316(2);
  DAT_EXTMEM_0428 = param_1;
  bVar2 = FUN_CODE_f316(4);
  if (DAT_EXTMEM_0428 == 0) {
    if (DAT_EXTMEM_0429 != '\x01') {
      if (DAT_EXTMEM_0429 != '\0') goto LAB_CODE_eaa4;
      if (bVar2 == 0 && param_1 == 0) {
        FUN_CODE_f2b6(1,DAT_EXTMEM_0424,DAT_EXTMEM_0423,DAT_EXTMEM_0422);
      }
      else {
        DAT_EXTMEM_0426 = bVar2 & 0x7f;
        cVar1 = '\a';
        DAT_EXTMEM_0427 = bVar2;
        do {
          DAT_EXTMEM_0427 = DAT_EXTMEM_0427 >> 1 | param_1 << 7;
          cVar1 = cVar1 + -1;
          param_1 = param_1 >> 1;
        } while (cVar1 != '\0');
        if (4 < DAT_EXTMEM_0426) {
          DAT_EXTMEM_0425 = 0x87;
          return 0x87;
        }
        pcVar3 = (char *)CONCAT11(-7 - (((0xfd < bVar2 * '\x02') << 7) >> 7),bVar2 * '\x02' + 2);
        bVar2 = pcVar3[1];
        if ((*(byte *)CONCAT11(BANK1_R0 + (*pcVar3 - ((CARRY1(BANK1_R1,bVar2) << 7) >> 7)),
                               BANK1_R1 + bVar2) & 1) != 1) {
          DAT_EXTMEM_0425 = 0x89;
          return 0x89;
        }
        FUN_CODE_f4cd(1,DAT_EXTMEM_0426);
      }
    }
    FUN_CODE_eb5f(0x422);
  }
  else {
LAB_CODE_eaa4:
    DAT_EXTMEM_0425 = 0x8d;
  }
  return DAT_EXTMEM_0425;
}


// ===== FUN_CODE_eab8  [bootloader]  callers: CODE:f520

void FUN_CODE_eab8(void)

{
  char cVar1;
  
  DAT_EXTMEM_0400 = 1;
  DAT_EXTMEM_0401 = 5;
  DAT_EXTMEM_0402 = 0x40;
  FUN_CODE_f2b6(0,0x40,5,1);
  FUN_CODE_f2c8(0,1,DAT_EXTMEM_0402,DAT_EXTMEM_0401,DAT_EXTMEM_0400);
  FUN_CODE_f2c8(0,2);
  FUN_CODE_f2c8(0,3);
  FUN_CODE_f2c8(0,0x44);
  FUN_CODE_f2c8(1,0x45);
  do {
    do {
      FUN_CODE_f730(DAT_EXTMEM_0402,DAT_EXTMEM_0401,DAT_EXTMEM_0400);
      FUN_CODE_f2c8(0,1,DAT_EXTMEM_0402,DAT_EXTMEM_0401,DAT_EXTMEM_0400);
      cVar1 = FUN_CODE_f289(3);
    } while (cVar1 != '\x02');
    FUN_CODE_f2c8(0,3,DAT_EXTMEM_0402,DAT_EXTMEM_0401,DAT_EXTMEM_0400);
    DAT_EXTMEM_2f40 = 0xb;
    while ((DAT_EXTMEM_2f41 >> 5 & 1) != 1) {
      FUN_CODE_f8f1(0x400);
    }
    FUN_CODE_f8d0();
    DAT_EXTMEM_2f52 = 0x11;
  } while( true );
}


// ===== FUN_CODE_eb5f  [bootloader]  callers: CODE:e9f6 CODE:e061

void FUN_CODE_eb5f(undefined1 *param_1)

{
  char cVar1;
  
  DAT_EXTMEM_042a = *param_1;
  DAT_EXTMEM_042b = param_1[1];
  DAT_EXTMEM_042c = param_1[2];
  cVar1 = '\x01';
  FUN_CODE_f24a(0x2d,0xc9,0xf9,0xff,4,1,0);
  FUN_CODE_f6f2(0x42a);
  if (cVar1 == '\0') {
    return;
  }
  FUN_CODE_f2c8(3,0x47,DAT_EXTMEM_042c,DAT_EXTMEM_042b,DAT_EXTMEM_042a);
  DAT_EXTMEM_0444 = 1;
  DAT_EXTMEM_0445 = 0;
  DAT_EXTMEM_0446 = DAT_EXTMEM_042a;
  DAT_EXTMEM_0447 = DAT_EXTMEM_042b;
  DAT_EXTMEM_0448 = DAT_EXTMEM_042c;
  FUN_CODE_ed90(0x2d,4,1,0);
  if (cVar1 == '\0') {
    return;
  }
  cVar1 = FUN_CODE_f289(2,DAT_EXTMEM_042c,DAT_EXTMEM_042b,DAT_EXTMEM_042a);
  if (cVar1 != '\0') {
    DAT_EXTMEM_2f54 = cVar1;
    FUN_CODE_f2c8(0,2,cVar1);
  }
  FUN_CODE_f8d0();
  return;
}


// ===== FUN_CODE_eb67  [bootloader]  callers: CODE:efe0 CODE:e061 CODE:f86d

void FUN_CODE_eb67(undefined1 param_1,undefined1 param_2,undefined1 param_3)

{
  char cVar1;
  
  cVar1 = '\x01';
  DAT_EXTMEM_042a = param_3;
  DAT_EXTMEM_042b = param_2;
  DAT_EXTMEM_042c = param_1;
  FUN_CODE_f24a(0x2d,0xc9,0xf9,0xff,4,1,0);
  FUN_CODE_f6f2(0x42a);
  if (cVar1 == '\0') {
    return;
  }
  FUN_CODE_f2c8(3,0x47,DAT_EXTMEM_042c,DAT_EXTMEM_042b,DAT_EXTMEM_042a);
  DAT_EXTMEM_0444 = 1;
  DAT_EXTMEM_0445 = 0;
  DAT_EXTMEM_0446 = DAT_EXTMEM_042a;
  DAT_EXTMEM_0447 = DAT_EXTMEM_042b;
  DAT_EXTMEM_0448 = DAT_EXTMEM_042c;
  FUN_CODE_ed90(0x2d,4,1,0);
  if (cVar1 == '\0') {
    return;
  }
  cVar1 = FUN_CODE_f289(2,DAT_EXTMEM_042c,DAT_EXTMEM_042b,DAT_EXTMEM_042a);
  if (cVar1 != '\0') {
    DAT_EXTMEM_2f54 = cVar1;
    FUN_CODE_f2c8(0,2,cVar1);
  }
  FUN_CODE_f8d0();
  return;
}


// ===== FUN_CODE_ebf6  [bootloader]  callers: CODE:e061

void FUN_CODE_ebf6(undefined1 param_1,undefined1 param_2,undefined1 param_3,byte param_4,
                  byte param_5)

{
  bool bVar1;
  byte bVar2;
  
  DAT_EXTMEM_0429 = 0;
  DAT_EXTMEM_0421 = param_3;
  DAT_EXTMEM_0422 = param_2;
  DAT_EXTMEM_0423 = param_1;
  DAT_EXTMEM_0424 = param_4;
  DAT_EXTMEM_0425 = param_5;
  FUN_CODE_f2c8(1,0x47,DAT_EXTMEM_0428,DAT_EXTMEM_0427,DAT_EXTMEM_0426);
  do {
    if (DAT_EXTMEM_0424 < (byte)-(((DAT_EXTMEM_0425 < 0x40) << 7) >> 7)) {
      DAT_EXTMEM_0429 = DAT_EXTMEM_0425;
    }
    else {
      DAT_EXTMEM_0429 = 0x40;
    }
    bVar1 = DAT_EXTMEM_0425 < DAT_EXTMEM_0429;
    DAT_EXTMEM_0425 = DAT_EXTMEM_0425 - DAT_EXTMEM_0429;
    DAT_EXTMEM_0424 = DAT_EXTMEM_0424 + ((bVar1 << 7) >> 7);
    DAT_EXTMEM_042e = DAT_EXTMEM_0426;
    DAT_EXTMEM_042f = DAT_EXTMEM_0427;
    DAT_EXTMEM_0430 = DAT_EXTMEM_0428;
    bVar2 = DAT_EXTMEM_0429;
    FUN_CODE_ec86(DAT_EXTMEM_0423,DAT_EXTMEM_0422,DAT_EXTMEM_0421,DAT_EXTMEM_0429);
    if (bVar2 == 0) {
      return;
    }
    bVar2 = DAT_EXTMEM_0424;
    if (DAT_EXTMEM_0424 == 0) {
      bVar2 = DAT_EXTMEM_0425;
    }
  } while (bVar2 != 0);
  return;
}


// ===== FUN_CODE_ec86  [bootloader]  callers: CODE:ebf6

void FUN_CODE_ec86(undefined1 param_1,undefined1 param_2,undefined1 param_3)

{
  bool bVar1;
  byte bVar2;
  char cVar3;
  
  bVar2 = 0;
  DAT_EXTMEM_042a = param_3;
  DAT_EXTMEM_042b = param_2;
  DAT_EXTMEM_042c = param_1;
  while( true ) {
    cVar3 = '\x02';
    FUN_CODE_f6fc(DAT_EXTMEM_0430,DAT_EXTMEM_042f,DAT_EXTMEM_042e,bVar2);
    if (cVar3 == '\0') {
      return;
    }
    FUN_CODE_f8ca();
    while ((DAT_EXTMEM_2f52 & 1) != 1) {
      FUN_CODE_f76a();
      bVar1 = cVar3 != '\0';
      cVar3 = '\0';
      if (bVar1) {
        return;
      }
    }
    while ((DAT_EXTMEM_2f40 >> 1 & 1) != 0) {
      FUN_CODE_f76a();
      bVar1 = cVar3 != '\0';
      cVar3 = '\0';
      if (bVar1) {
        return;
      }
    }
    DAT_EXTMEM_2f52 = 0x11;
    cVar3 = '\x02';
    FUN_CODE_f8d7(DAT_EXTMEM_2f42);
    if (cVar3 == '\0') break;
    bVar2 = DAT_EXTMEM_2f41;
    if ((DAT_EXTMEM_2f41 & 1) == 0) {
      if (((DAT_EXTMEM_2f41 >> 1 & 1) != 1) && ((DAT_EXTMEM_2f41 >> 2 & 1) != 1)) {
        DAT_EXTMEM_0435 = 0;
        FUN_CODE_ed12(DAT_EXTMEM_042c,DAT_EXTMEM_042b,DAT_EXTMEM_042a);
        return;
      }
    }
    else {
      DAT_EXTMEM_2f64 = 1;
    }
  }
  return;
}


// ===== FUN_CODE_ed12  [bootloader]  callers: CODE:e5cd CODE:ec86

char FUN_CODE_ed12(undefined1 param_1,undefined1 param_2,undefined1 param_3,char param_4)

{
  char cVar1;
  char cVar2;
  char cVar3;
  
  cVar3 = '\0';
  DAT_EXTMEM_0431 = param_3;
  DAT_EXTMEM_0432 = param_2;
  DAT_EXTMEM_0433 = param_1;
  DAT_EXTMEM_0434 = param_4;
  if (DAT_EXTMEM_0435 == '\x01') {
    BANK1_R0 = 0x2f;
    BANK1_R1 = 0x80;
    DAT_EXTMEM_0436 = DAT_EXTMEM_2f82;
    cVar2 = DAT_EXTMEM_2f83;
  }
  else {
    BANK1_R0 = 0x2f;
    BANK1_R1 = 0x60;
    DAT_EXTMEM_0436 = DAT_EXTMEM_2f62;
    cVar2 = DAT_EXTMEM_2f63;
  }
  while( true ) {
    cVar1 = DAT_EXTMEM_0434;
    DAT_EXTMEM_0434 = DAT_EXTMEM_0434 + -1;
    if ((cVar1 == '\0') << 7 < '\0') {
      return cVar1 + -1;
    }
    if ((DAT_EXTMEM_0436 == '\0') && (cVar2 == '\0')) break;
    FUN_CODE_f2c8(*(undefined1 *)CONCAT11(BANK1_R0,BANK1_R1),cVar3,DAT_EXTMEM_0433,DAT_EXTMEM_0432,
                  DAT_EXTMEM_0431);
    cVar3 = cVar3 + '\x01';
  }
  return '\0';
}


// ===== FUN_CODE_ed90  [bootloader]  callers: CODE:e823 CODE:eb67

void FUN_CODE_ed90(undefined1 param_1,undefined1 param_2,undefined1 param_3)

{
  bool bVar1;
  char cVar2;
  byte bVar3;
  
  DAT_EXTMEM_0440 = param_3;
  DAT_EXTMEM_0441 = param_2;
  DAT_EXTMEM_0442 = param_1;
  do {
    DAT_EXTMEM_044d = 0;
    FUN_CODE_ee71(DAT_EXTMEM_0442,DAT_EXTMEM_0441,DAT_EXTMEM_0440,BANK0_R6);
    DAT_EXTMEM_2f52 = 0x1b;
    bVar3 = DAT_EXTMEM_2f40 | 1;
    if (DAT_EXTMEM_0444 == '\0') {
      DAT_EXTMEM_2f40 = DAT_EXTMEM_2f40 & 0xfb | 3;
    }
    else {
      DAT_EXTMEM_2f40 = DAT_EXTMEM_2f40 | 7;
    }
    if (DAT_EXTMEM_0445 != '\0') {
      return;
    }
    while ((DAT_EXTMEM_2f52 & 1) != 1) {
      FUN_CODE_f76d(0x446);
      bVar1 = bVar3 != 0;
      bVar3 = 0;
      if (bVar1) {
        return;
      }
    }
    DAT_EXTMEM_2f52 = 0x1b;
    cVar2 = '\x01';
    FUN_CODE_f8d7();
    if (cVar2 == '\0') {
      return;
    }
  } while ((DAT_EXTMEM_2f41 >> 3 & 1) == 1);
  return;
}


// ===== FUN_CODE_ee09  [bootloader]  callers: CODE:f83b

void FUN_CODE_ee09(void)

{
                    /* WARNING: Subroutine does not return */
  FUN_CODE_f35a(DAT_EXTMEM_0544);
}


// ===== FUN_CODE_ee2f  [bootloader]  callers: 

void FUN_CODE_ee2f(void)

{
  DAT_EXTMEM_0428 = 4;
  DAT_EXTMEM_0429 = 0;
  FUN_CODE_f14a(0,0,1,0xff);
  return;
}


// ===== FUN_CODE_ee45  [bootloader]  callers: 

void FUN_CODE_ee45(void)

{
  FUN_CODE_f3fe();
  return;
}


// ===== FUN_CODE_ee4a  [bootloader]  callers: 

void FUN_CODE_ee4a(void)

{
  FUN_CODE_f380();
  return;
}


// ===== FUN_CODE_ee4f  [bootloader]  callers: 

void FUN_CODE_ee4f(void)

{
  FUN_CODE_f3cb();
  return;
}


// ===== FUN_CODE_ee54  [bootloader]  callers: 

void FUN_CODE_ee54(void)

{
  DAT_EXTMEM_0f0f = 0x33;
  return;
}


// ===== FUN_CODE_ee5c  [bootloader]  callers: 

void FUN_CODE_ee5c(void)

{
  FUN_CODE_f664();
  return;
}


// ===== FUN_CODE_ee61  [bootloader]  callers: 

void FUN_CODE_ee61(void)

{
  FUN_CODE_f809();
  return;
}


// ===== FUN_CODE_ee66  [bootloader]  callers: 

void FUN_CODE_ee66(void)

{
  FUN_CODE_ef8a();
  return;
}


// ===== FUN_CODE_ee6b  [bootloader]  callers: 

void FUN_CODE_ee6b(void)

{
  FUN_CODE_f573();
  return;
}


// ===== FUN_CODE_ee71  [bootloader]  callers: CODE:ed90

char FUN_CODE_ee71(undefined1 param_1,undefined1 param_2,undefined1 param_3,byte param_4)

{
  byte bVar1;
  char cVar2;
  
  DAT_EXTMEM_0449 = param_3;
  DAT_EXTMEM_044a = param_2;
  DAT_EXTMEM_044b = param_1;
  if (DAT_EXTMEM_044d == '\x01') {
    DAT_EXTMEM_2f94 = 1;
    for (bVar1 = 0; cVar2 = bVar1 - param_4, bVar1 < param_4; bVar1 = bVar1 + 1) {
      DAT_EXTMEM_2f90 = FUN_CODE_f289(bVar1,DAT_EXTMEM_044b,DAT_EXTMEM_044a,DAT_EXTMEM_0449);
    }
  }
  else {
    DAT_EXTMEM_2f74 = 1;
    for (bVar1 = 0; cVar2 = bVar1 - param_4, bVar1 < param_4; bVar1 = bVar1 + 1) {
      DAT_EXTMEM_2f70 = FUN_CODE_f289(bVar1,DAT_EXTMEM_044b,DAT_EXTMEM_044a,DAT_EXTMEM_0449);
    }
  }
  return cVar2;
}


// ===== FUN_CODE_eed2  [bootloader]  callers: CODE:f7d5

void FUN_CODE_eed2(undefined1 param_1,undefined1 param_2,undefined1 param_3)

{
  bool bVar1;
  char cVar2;
  
  cVar2 = '\x02';
  DAT_EXTMEM_0436 = param_3;
  DAT_EXTMEM_0437 = param_2;
  DAT_EXTMEM_0438 = param_1;
  FUN_CODE_f6fc();
  if (cVar2 == '\0') {
    return;
  }
  FUN_CODE_f2c8(2,0x47,DAT_EXTMEM_0438,DAT_EXTMEM_0437,DAT_EXTMEM_0436);
  DAT_EXTMEM_2f52 = 0x1b;
  DAT_EXTMEM_2f40 = 3;
  do {
    if ((DAT_EXTMEM_2f52 & 1) == 1) {
      DAT_EXTMEM_2f52 = 1;
      cVar2 = '\x02';
      FUN_CODE_f8d7();
      if (cVar2 == '\0') {
        return;
      }
      FUN_CODE_f8d0();
      return;
    }
    FUN_CODE_f76d(0x436);
    bVar1 = cVar2 == '\0';
    cVar2 = '\0';
  } while (bVar1);
  return;
}


// ===== FUN_CODE_ef2f  [bootloader]  callers: 

void FUN_CODE_ef2f(void)

{
  DAT_EXTMEM_2fe0 = 2;
  FUN_CODE_f12c(0,1);
  DAT_EXTMEM_2fe4 = DAT_EXTMEM_2fe4 & 0xef;
  DAT_EXTMEM_2fe8 = DAT_EXTMEM_2fe8 & 0xef;
  DAT_EXTMEM_2fe0 = 0;
  DAT_EXTMEM_2f50 = 8;
  FUN_CODE_f12c(1);
  DAT_EXTMEM_2f50 = 0x71;
  DAT_EXTMEM_2f54 = 0;
  DAT_EXTMEM_2f52 = 4;
  DAT_EXTMEM_2f40 = 1;
  DAT_EXTMEM_2f44 = 3;
  while ((DAT_EXTMEM_2f52 >> 2 & 1) != 0) {
    DAT_EXTMEM_2f52 = 4;
    FUN_CODE_f896();
  }
  return;
}


// ===== FUN_CODE_ef8a  [bootloader]  callers: CODE:ee66

void FUN_CODE_ef8a(void)

{
  bool bVar1;
  byte bVar2;
  byte bVar3;
  char cVar4;
  char cVar5;
  char cVar6;
  undefined1 uVar7;
  
  if (10 < DAT_EXTMEM_0548) {
    DAT_EXTMEM_0548 = 10;
  }
  DAT_EXTMEM_0424 = DAT_EXTMEM_0548;
  cVar4 = '\x05';
  bVar3 = 0x49;
  cVar5 = DAT_EXTMEM_0546;
  cVar6 = DAT_EXTMEM_0545;
  while( true ) {
    bVar2 = DAT_EXTMEM_0424;
    DAT_EXTMEM_0424 = DAT_EXTMEM_0424 - 1;
    if (bVar2 == 0) break;
    if (DAT_EXTMEM_0547 == '\0') {
      uVar7 = 0x33;
    }
    else {
      uVar7 = *(undefined1 *)CONCAT11(cVar5,cVar6);
    }
    FUN_CODE_f2b6(uVar7,bVar3,cVar4);
    bVar1 = 0xfe < bVar3;
    bVar3 = bVar3 + 1;
    cVar4 = cVar4 - ((bVar1 << 7) >> 7);
    cVar6 = cVar6 + '\x01';
    if (cVar6 == '\0') {
      cVar5 = cVar5 + '\x01';
    }
  }
  return;
}


// ===== FUN_CODE_efe0  [bootloader]  callers: 

void FUN_CODE_efe0(void)

{
  undefined1 uVar1;
  
  uVar1 = FUN_CODE_f316(2);
  FUN_CODE_f2c8(uVar1,0x46,DAT_EXTMEM_0424,DAT_EXTMEM_0423,DAT_EXTMEM_0422);
  FUN_CODE_eb67();
  return;
}


// ===== FUN_CODE_f000  [bootloader]  callers: CODE:f380 CODE:f06c

undefined1 FUN_CODE_f000(void)

{
  BANK1_R0 = 5;
  DAT_EXTMEM_103c = 0xfe;
  DAT_EXTMEM_103f = 0;
  return 5;
}


// ===== FUN_CODE_f01e  [bootloader]  callers: CODE:f380 CODE:f06c

void FUN_CODE_f01e(void)

{
  DAT_EXTMEM_103c = 0xfe;
  DAT_EXTMEM_103f = 0;
  return;
}


// ===== FUN_CODE_f036  [bootloader]  callers: CODE:f380 CODE:f06c

void FUN_CODE_f036(void)

{
  DAT_EXTMEM_103c = 0xfe;
  DAT_EXTMEM_103f = 0;
  return;
}


// ===== FUN_CODE_f04e  [bootloader]  callers: CODE:f380

void FUN_CODE_f04e(void)

{
  DAT_EXTMEM_103c = 0xfe;
  DAT_EXTMEM_103f = 0;
  return;
}


// ===== FUN_CODE_f06c  [bootloader]  callers: CODE:f3cb

void FUN_CODE_f06c(undefined1 param_1,byte param_2)

{
  bool bVar1;
  char cVar2;
  char cVar3;
  
  DAT_EXTMEM_2260 = '\0';
  DAT_EXTMEM_2261 = '\0';
  DAT_EXTMEM_103e = 0x7f;
  DAT_EXTMEM_103d = 0xff;
  DAT_EXTMEM_103c = 0xff;
  DAT_EXTMEM_103b = 0xff;
  DAT_EXTMEM_0424 = param_1;
  DAT_EXTMEM_0425 = param_2;
  FUN_CODE_f01e();
  do {
    FUN_CODE_f000();
  } while ((param_2 & 1) == 1);
  cVar3 = '\0';
  for (; cVar2 = ((DAT_EXTMEM_042a == 0) << 7) >> 7, (byte)-cVar2 <= DAT_EXTMEM_0429;
      DAT_EXTMEM_0429 = DAT_EXTMEM_0429 + (-1 - ((bVar1 << 7) >> 7))) {
    DAT_EXTMEM_2261 = DAT_EXTMEM_2261 + '\x01';
    if (DAT_EXTMEM_2261 == '\0') {
      DAT_EXTMEM_2260 = DAT_EXTMEM_2260 + '\x01';
    }
    DAT_EXTMEM_103c = 0xfd;
    if (cVar3 == '\0') {
      DAT_EXTMEM_103f = 0;
      cVar3 = '\x01';
    }
    else {
      DAT_EXTMEM_103f = 0xad;
    }
    DAT_EXTMEM_103f = FUN_CODE_f270();
    FUN_CODE_f270();
    DAT_EXTMEM_103c = 0xfe;
    DAT_EXTMEM_103f = 0;
    do {
      FUN_CODE_f000();
    } while ((param_2 & 1) == 1);
    bVar1 = 1 < DAT_EXTMEM_042a;
    DAT_EXTMEM_042a = DAT_EXTMEM_042a - 2;
  }
  FUN_CODE_f036(DAT_EXTMEM_0429 + cVar2);
  do {
    FUN_CODE_f000();
  } while ((param_2 & 1) == 1);
  DAT_EXTMEM_103e = 0;
  DAT_EXTMEM_103d = 0;
  return;
}


// ===== FUN_CODE_f12c  [bootloader]  callers: CODE:f455 CODE:ef2f CODE:f520

char FUN_CODE_f12c(char param_1,byte param_2)

{
  byte bVar1;
  char cVar2;
  byte bVar3;
  byte bVar4;
  
  bVar4 = 0;
  bVar3 = 0;
  while (bVar1 = param_1 - (((bVar4 < param_2) << 7) >> 7), bVar3 < bVar1) {
    cVar2 = '\0';
    do {
      DAT_EXTMEM_200b = 0;
      cVar2 = cVar2 + '\x01';
    } while (cVar2 != 'B');
    bVar4 = bVar4 + 1;
    if (bVar4 == 0) {
      bVar3 = bVar3 + 1;
    }
  }
  return bVar3 - bVar1;
}


// ===== FUN_CODE_f14a  [bootloader]  callers: CODE:ee2f

void FUN_CODE_f14a(undefined1 param_1,undefined1 param_2,undefined1 param_3,undefined1 param_4)

{
  char cVar1;
  undefined1 uVar2;
  char cVar3;
  undefined1 uVar4;
  
  DAT_EXTMEM_042a = param_3;
  DAT_EXTMEM_042b = param_2;
  DAT_EXTMEM_042c = param_1;
  while( true ) {
    cVar1 = -1;
    cVar3 = FUN_CODE_f300(0x428);
    if (cVar3 == '\0' && cVar1 == '\0') break;
    uVar2 = 1;
    uVar4 = FUN_CODE_f300(0,0x42b,1,DAT_EXTMEM_042a);
    FUN_CODE_f2b6(param_4,uVar2,uVar4);
  }
  return;
}


// ===== H_F17A  [bootloader]  callers: 

undefined1 H_F17A(undefined1 *param_1,undefined1 *param_2,undefined1 param_3,char param_4)

{
  undefined1 uVar1;
  
  do {
    uVar1 = *param_2;
    param_2 = param_2 + '\x01';
    *param_1 = uVar1;
    param_1 = param_1 + '\x01';
    param_4 = param_4 + -1;
  } while (param_4 != '\0');
  return param_3;
}


// ===== FUN_CODE_f24a  [bootloader]  callers: CODE:e6ff CODE:eb67

char FUN_CODE_f24a(undefined1 param_1,char param_2,char param_3,char param_4,char param_5)

{
  byte bVar1;
  char cVar2;
  
  if (param_5 != '\0') {
    param_4 = param_4 + '\x01';
  }
  if (((param_5 != '\0' || param_4 != '\0') && (param_3 + 2U < 4)) &&
     (bVar1 = param_2 + 2, bVar1 < 4)) {
    bVar1 = (bVar1 * '\x02' | bVar1 >> 7) << 1 | (bVar1 & 0x7f) >> 6 | param_3 + 2U;
                    /* WARNING: Could not recover jumptable at 0xf26f. Too many branches */
                    /* WARNING: Treating indirect jump as call */
    cVar2 = (*(code *)((ushort)(bVar1 << 1 | bVar1 >> 7) - 0xe36))(param_1);
    return cVar2;
  }
  return param_3;
}


// ===== FUN_CODE_f270  [bootloader]  callers: CODE:f478 CODE:f573 CODE:e5cd CODE:e6ff CODE:f06c

undefined1 FUN_CODE_f270(undefined1 *param_1,undefined1 param_2,char param_3)

{
  if (param_3 == '\x01') {
    return *(undefined1 *)CONCAT11(param_2,param_1);
  }
  if (param_3 == '\0') {
    return *param_1;
  }
  if (param_3 == -2) {
    return *(undefined1 *)ZEXT12(param_1);
  }
  return *(undefined1 *)CONCAT11(param_2,param_1);
}


// ===== FUN_CODE_f289  [bootloader]  callers: CODE:ee71 CODE:e276 CODE:f7a0 CODE:e2a6 CODE:eab8 CODE:e061 CODE:f86d CODE:f5c5 CODE:eb67 CODE:e45b

undefined1 FUN_CODE_f289(undefined2 param_1,byte param_2,char param_3,char param_4)

{
  char cVar1;
  byte bVar2;
  
  bVar2 = (byte)param_1;
  cVar1 = (char)((ushort)param_1 >> 8);
  if (param_4 == '\x01') {
    return *(undefined1 *)
            CONCAT11(cVar1 + (param_3 - ((CARRY1(bVar2,param_2) << 7) >> 7)),bVar2 + param_2);
  }
  if (param_4 == '\0') {
    return *(undefined1 *)(param_2 + bVar2);
  }
  if (param_4 == -2) {
    return *(undefined1 *)(ushort)(param_2 + bVar2);
  }
  return *(undefined1 *)
          CONCAT11(cVar1 + (param_3 - ((CARRY1(bVar2,param_2) << 7) >> 7)),bVar2 + param_2);
}


// ===== FUN_CODE_f2b6  [bootloader]  callers: CODE:f6ab CODE:e931 CODE:f478 CODE:f664 CODE:ef8a CODE:eab8 CODE:f14a CODE:e9f6

void FUN_CODE_f2b6(undefined1 param_1,undefined1 *param_2,undefined1 param_3,char param_4)

{
  if (param_4 == '\x01') {
    *(undefined1 *)CONCAT11(param_3,param_2) = param_1;
    return;
  }
  if (param_4 == '\0') {
    *param_2 = param_1;
    return;
  }
  if (param_4 == -2) {
    *(undefined1 *)ZEXT12(param_2) = param_1;
  }
  return;
}


// ===== FUN_CODE_f2c8  [bootloader]  callers: CODE:f7a0 CODE:e823 CODE:e5cd CODE:f86d CODE:efe0 CODE:ed12 CODE:eed2 CODE:f664 CODE:eab8 CODE:e061 CODE:f5c5 CODE:f730 CODE:eb67 CODE:ebf6

void FUN_CODE_f2c8(undefined1 param_1,undefined2 param_2,byte param_3,char param_4,char param_5)

{
  byte bVar1;
  
  bVar1 = (byte)param_2;
  if (param_5 == '\x01') {
    *(undefined1 *)
     CONCAT11((char)((ushort)param_2 >> 8) + (param_4 - ((CARRY1(bVar1,param_3) << 7) >> 7)),
              bVar1 + param_3) = param_1;
    return;
  }
  if (param_5 == '\0') {
    *(undefined1 *)(param_3 + bVar1) = param_1;
    return;
  }
  if (param_5 == -2) {
    *(undefined1 *)(ushort)(param_3 + bVar1) = param_1;
  }
  return;
}


// ===== FUN_CODE_f2ea  [bootloader]  callers: CODE:e823

void FUN_CODE_f2ea(char param_1,short param_2,byte param_3)

{
  byte bVar1;
  char cVar2;
  byte *pbVar3;
  char *pcVar4;
  
  pbVar3 = (byte *)(param_2 + 1);
  bVar1 = *pbVar3;
  *pbVar3 = bVar1 + param_3;
  cVar2 = (char)((ushort)pbVar3 >> 8);
  if ((char)pbVar3 == '\0') {
    cVar2 = cVar2 + -1;
  }
  pcVar4 = (char *)CONCAT11(cVar2,(char)pbVar3 + -1);
  *pcVar4 = *pcVar4 + (param_1 - ((CARRY1(bVar1,param_3) << 7) >> 7));
  return;
}


// ===== FUN_CODE_f300  [bootloader]  callers: CODE:f478 CODE:f14a

char FUN_CODE_f300(char param_1,short param_2,byte param_3)

{
  byte bVar1;
  char cVar2;
  byte *pbVar3;
  char *pcVar4;
  
  pbVar3 = (byte *)(param_2 + 1);
  bVar1 = *pbVar3;
  *pbVar3 = param_3 + bVar1;
  cVar2 = (char)((ushort)pbVar3 >> 8);
  if ((char)pbVar3 == '\0') {
    cVar2 = cVar2 + -1;
  }
  pcVar4 = (char *)CONCAT11(cVar2,(char)pbVar3 + -1);
  cVar2 = *pcVar4;
  *pcVar4 = param_1 + (cVar2 - ((CARRY1(param_3,bVar1) << 7) >> 7));
  return cVar2;
}


// ===== FUN_CODE_f316  [bootloader]  callers: CODE:e931 CODE:e061 CODE:e6ff CODE:efe0 CODE:e9f6

undefined1 FUN_CODE_f316(undefined2 param_1,byte param_2,char param_3,char param_4)

{
  char cVar1;
  byte bVar2;
  
  bVar2 = (byte)param_1;
  cVar1 = (char)((ushort)param_1 >> 8);
  if (param_4 == '\x01') {
    return *(undefined1 *)
            (CONCAT11(cVar1 + (param_3 - ((CARRY1(bVar2,param_2) << 7) >> 7)),bVar2 + param_2) + 1);
  }
  if (param_4 == '\0') {
    return *(undefined1 *)(param_2 + bVar2 + '\x01');
  }
  if (param_4 == -2) {
    return *(undefined1 *)(ushort)(param_2 + bVar2 + 1);
  }
  return *(undefined1 *)(CONCAT11(cVar1 + param_3,bVar2) + 1 + (ushort)param_2);
}


// ===== H_F34E  [bootloader]  callers: 

void H_F34E(undefined1 *param_1,undefined1 param_2,undefined1 param_3,undefined1 param_4,
           undefined1 param_5)

{
  *param_1 = param_2;
  param_1[1] = param_3;
  param_1[2] = param_4;
  param_1[3] = param_5;
  return;
}


// ===== FUN_CODE_f35a  [bootloader]  callers: CODE:ee09

void FUN_CODE_f35a(char param_1)

{
  char *pcVar1;
  undefined1 uStackX_0;
  undefined1 in_stack_000000ff;
  
  for (pcVar1 = (char *)CONCAT11(uStackX_0,in_stack_000000ff);
      (*pcVar1 != '\0' || (pcVar1[1] != '\0')); pcVar1 = pcVar1 + 3) {
    if (pcVar1[2] == param_1) goto LAB_CODE_f36a;
  }
  pcVar1 = pcVar1 + 2;
LAB_CODE_f36a:
                    /* WARNING: Could not recover jumptable at 0xf374. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (**(code **)pcVar1)();
  return;
}


// ===== FUN_CODE_f380  [bootloader]  callers: CODE:ee4a

void FUN_CODE_f380(byte param_1)

{
  char cVar1;
  char cVar2;
  
  DAT_EXTMEM_103e = 0x7f;
  DAT_EXTMEM_103d = 0xff;
  DAT_EXTMEM_103c = 0xff;
  DAT_EXTMEM_103b = 0xff;
  cVar2 = DAT_EXTMEM_0546;
  for (cVar1 = DAT_EXTMEM_0548; cVar1 != '\0'; cVar1 = cVar1 + -1) {
    FUN_CODE_f01e(cVar2);
    do {
      FUN_CODE_f000();
    } while ((param_1 & 1) == 1);
    param_1 = BANK0_R6;
    FUN_CODE_f04e();
    do {
      FUN_CODE_f000();
    } while ((param_1 & 1) == 1);
    FUN_CODE_f036();
    cVar2 = cVar2 + '\x04';
  }
  DAT_EXTMEM_103e = 0;
  DAT_EXTMEM_103d = 0;
  return;
}


// ===== FUN_CODE_f3cb  [bootloader]  callers: CODE:ee4f

void FUN_CODE_f3cb(void)

{
  DAT_EXTMEM_0429 = DAT_EXTMEM_0549;
  DAT_EXTMEM_042a = DAT_EXTMEM_0548;
  FUN_CODE_f06c(0,0,1,BANK0_R4,BANK0_R5);
  return;
}


// ===== FUN_CODE_f3fe  [bootloader]  callers: CODE:ee45

void FUN_CODE_f3fe(void)

{
  DAT_EXTMEM_0424 = 1;
  DAT_EXTMEM_0425 = DAT_EXTMEM_0546;
  DAT_EXTMEM_0426 = DAT_EXTMEM_0545;
  DAT_EXTMEM_0427 = 1;
  DAT_EXTMEM_0428 = 5;
  DAT_EXTMEM_0429 = 0x48;
  DAT_EXTMEM_0443 = 1;
  DAT_EXTMEM_0444 = 5;
  DAT_EXTMEM_0445 = 0x48;
  DAT_EXTMEM_0446 = DAT_EXTMEM_0547;
  FUN_CODE_f478(DAT_EXTMEM_0545,DAT_EXTMEM_0546,1);
  return;
}


// ===== FUN_CODE_f455  [bootloader]  callers: CODE:e061

void FUN_CODE_f455(void)

{
  byte bVar1;
  
  FUN_CODE_f12c(0,5);
  DAT_EXTMEM_2f50 = 8;
  FUN_CODE_f12c(3,0xe8);
  bVar1 = DAT_SFR_8e;
  DAT_SFR_8e = bVar1 & 0x3f;
  CCON = 2;
  do {
                    /* WARNING: Do nothing block with infinite loop */
  } while( true );
}


// ===== FUN_CODE_f478  [bootloader]  callers: CODE:f8b2 CODE:e823 CODE:f3fe

void FUN_CODE_f478(undefined1 param_1,undefined1 param_2,undefined1 param_3)

{
  char cVar1;
  undefined1 uVar2;
  undefined1 uVar3;
  undefined1 uVar4;
  
  DAT_EXTMEM_044a = DAT_EXTMEM_0443;
  DAT_EXTMEM_044b = DAT_EXTMEM_0444;
  DAT_EXTMEM_044c = DAT_EXTMEM_0445;
  DAT_EXTMEM_0447 = param_3;
  DAT_EXTMEM_0448 = param_2;
  DAT_EXTMEM_0449 = param_1;
  while (cVar1 = DAT_EXTMEM_0446, DAT_EXTMEM_0446 = DAT_EXTMEM_0446 + -1, cVar1 != '\0') {
    uVar2 = 1;
    uVar3 = FUN_CODE_f300(0,1099,1,DAT_EXTMEM_044a);
    uVar2 = FUN_CODE_f270(uVar2,uVar3);
    uVar3 = 1;
    uVar4 = FUN_CODE_f300(0,0x448,1,DAT_EXTMEM_0447,uVar2);
    FUN_CODE_f2b6(uVar2,uVar3,uVar4);
  }
  return;
}


// ===== FUN_CODE_f4cd  [bootloader]  callers: CODE:e931 CODE:e9f6

void FUN_CODE_f4cd(char param_1,char param_2)

{
  byte bVar1;
  char *pcVar2;
  byte *pbVar3;
  
  if (param_1 != '\0') {
    pcVar2 = (char *)CONCAT11(-7 - (((0xfdU < (byte)(param_2 * '\x02')) << 7) >> 7),
                              param_2 * '\x02' + 2);
    bVar1 = pcVar2[1];
    pbVar3 = (byte *)CONCAT11(BANK1_R2 + (*pcVar2 - ((CARRY1(BANK1_R3,bVar1) << 7) >> 7)),
                              BANK1_R3 + bVar1);
    *pbVar3 = *pbVar3 | 8;
    return;
  }
  pcVar2 = (char *)CONCAT11(-7 - (((0xfdU < (byte)(param_2 * '\x02')) << 7) >> 7),
                            param_2 * '\x02' + 2);
  bVar1 = pcVar2[1];
  pbVar3 = (byte *)CONCAT11(BANK1_R2 + (*pcVar2 - ((CARRY1(BANK1_R3,bVar1) << 7) >> 7)),
                            BANK1_R3 + bVar1);
  *pbVar3 = *pbVar3 & 0xf7;
  return;
}


// ===== FUN_CODE_f520  [bootloader]  callers: CODE:e003

void FUN_CODE_f520(char param_1)

{
  undefined1 uVar1;
  undefined1 uVar2;
  char cVar3;
  
  FUN_CODE_f8e4();
  if (param_1 == '\0') {
    uVar2 = 0xb0;
    uVar1 = 4;
  }
  else {
    DAT_EXTMEM_1e21 = 0x40;
    DAT_EXTMEM_1e40 = 3;
    DAT_EXTMEM_1e20 = 0x80;
    uVar2 = 0x78;
    uVar1 = 0;
  }
  DAT_EXTMEM_16fd = 0x8c;
  FUN_CODE_f12c(uVar1,uVar2);
  DAT_EXTMEM_16fd = 0;
  cVar3 = '\x01';
  FUN_CODE_f615(0xf0,0,1);
  FUN_CODE_f615(0xf4,0,cVar3 + '\x01');
  thunk_FUN_CODE_ef2f();
  FUN_CODE_eab8();
  return;
}


// ===== FUN_CODE_f573  [bootloader]  callers: CODE:ee6b

void FUN_CODE_f573(void)

{
  bool bVar1;
  byte bVar2;
  byte bVar3;
  char cVar4;
  char cVar5;
  char cVar6;
  undefined1 uVar7;
  
  if (10 < DAT_EXTMEM_0548) {
    DAT_EXTMEM_0548 = 10;
  }
  DAT_EXTMEM_0424 = DAT_EXTMEM_0548;
  cVar4 = '\x05';
  bVar3 = 0x49;
  cVar5 = DAT_EXTMEM_0546;
  cVar6 = DAT_EXTMEM_0545;
  while( true ) {
    bVar2 = DAT_EXTMEM_0424;
    DAT_EXTMEM_0424 = DAT_EXTMEM_0424 - 1;
    if (bVar2 == 0) break;
    if (DAT_EXTMEM_0547 != '\0') {
      uVar7 = FUN_CODE_f270(cVar4);
      *(undefined1 *)CONCAT11(cVar5,cVar6) = uVar7;
    }
    bVar1 = 0xfe < bVar3;
    bVar3 = bVar3 + 1;
    cVar4 = cVar4 - ((bVar1 << 7) >> 7);
    cVar6 = cVar6 + '\x01';
    if (cVar6 == '\0') {
      cVar5 = cVar5 + '\x01';
    }
  }
  return;
}


// ===== FUN_CODE_f5c5  [bootloader]  callers: 

void FUN_CODE_f5c5(undefined1 param_1,undefined1 param_2,undefined1 param_3)

{
  DAT_EXTMEM_041f = param_3;
  DAT_EXTMEM_0420 = param_2;
  DAT_EXTMEM_0421 = param_1;
  FUN_CODE_f289(0x46,param_1,param_2,param_3);
  FUN_CODE_f2c8(4);
  DAT_EXTMEM_0433 = DAT_EXTMEM_041f;
  DAT_EXTMEM_0434 = DAT_EXTMEM_0420;
  DAT_EXTMEM_0435 = DAT_EXTMEM_0421;
  FUN_CODE_f7d5(0,1);
  return;
}


// ===== FUN_CODE_f615  [bootloader]  callers: CODE:f520

void FUN_CODE_f615(undefined1 param_1,undefined1 param_2,char param_3)

{
  undefined1 *puVar1;
  
  if (param_3 == '\x01') {
    DAT_EXTMEM_1045 = 0x80;
    puVar1 = &DAT_EXTMEM_1043;
  }
  else if (param_3 == '\x02') {
    DAT_EXTMEM_1048 = 0x80;
    puVar1 = &DAT_EXTMEM_1046;
  }
  else if (param_3 == '\x03') {
    DAT_EXTMEM_104b = 0x80;
    puVar1 = &DAT_EXTMEM_1049;
  }
  else if (param_3 == '\x04') {
    DAT_EXTMEM_104e = 0x80;
    puVar1 = &DAT_EXTMEM_104c;
  }
  else {
    if (param_3 != '\0') {
      return;
    }
    DAT_EXTMEM_1042 = 0x80;
    puVar1 = &DAT_EXTMEM_1040;
  }
  *puVar1 = param_2;
  puVar1[1] = param_1;
  puVar1[2] = 0;
  return;
}


// ===== FUN_CODE_f664  [bootloader]  callers: CODE:ee5c

void FUN_CODE_f664(void)

{
  bool bVar1;
  char cVar2;
  char cVar3;
  
  DAT_EXTMEM_0424 = '\0';
  DAT_EXTMEM_0425 = 0;
  cVar3 = '\0';
  cVar2 = '\0';
  do {
    bVar1 = CARRY1(DAT_EXTMEM_0425,*(byte *)CONCAT11(cVar2,cVar3));
    DAT_EXTMEM_0425 = DAT_EXTMEM_0425 + *(byte *)CONCAT11(cVar2,cVar3);
    DAT_EXTMEM_0424 = DAT_EXTMEM_0424 - ((bVar1 << 7) >> 7);
    cVar3 = cVar3 + '\x01';
    if (cVar3 == '\0') {
      cVar2 = cVar2 + '\x01';
    }
  } while ((BANK0_R7 != '\0') || (cVar2 != '\x04'));
  FUN_CODE_f2b6(DAT_EXTMEM_0425,0x45,5,1);
  FUN_CODE_f2c8(DAT_EXTMEM_0424,1);
  return;
}


// ===== FUN_CODE_f6ab  [bootloader]  callers: CODE:f809

void FUN_CODE_f6ab(void)

{
  bool bVar1;
  char cVar2;
  char cVar3;
  char cVar4;
  
  DAT_EXTMEM_103e = 0x40;
  DAT_EXTMEM_103d = 0;
  cVar2 = BANK0_R6;
  cVar3 = BANK0_R7;
  while( true ) {
    cVar4 = DAT_EXTMEM_042b;
    if (DAT_EXTMEM_042b == '\0') {
      cVar4 = DAT_EXTMEM_042c;
    }
    if (cVar4 == '\0') break;
    DAT_EXTMEM_103b = cVar3;
    DAT_EXTMEM_103c = cVar2;
    FUN_CODE_f2b6(DAT_EXTMEM_103f);
    cVar3 = cVar3 + '\x01';
    if (cVar3 == '\0') {
      cVar2 = cVar2 + '\x01';
    }
    bVar1 = DAT_EXTMEM_042c != '\0';
    DAT_EXTMEM_042c = DAT_EXTMEM_042c + -1;
    DAT_EXTMEM_042b = DAT_EXTMEM_042b + (-1 - ((bVar1 << 7) >> 7));
  }
  return;
}


// ===== FUN_CODE_f6f2  [bootloader]  callers: CODE:e823 CODE:eb67

void FUN_CODE_f6f2(undefined1 *param_1)

{
  bool bVar1;
  char cVar2;
  
  DAT_EXTMEM_0440 = *param_1;
  DAT_EXTMEM_0441 = param_1[1];
  DAT_EXTMEM_0442 = param_1[2];
  cVar2 = '\x01';
  do {
    if ((DAT_EXTMEM_2f41 >> 4 & 1) == 1) {
      if (DAT_EXTMEM_2f43 == BANK0_R6) {
        return;
      }
      if (DAT_EXTMEM_2f43 == '\0') {
        FUN_CODE_f8d0();
      }
      return;
    }
    FUN_CODE_f76d(0x440);
    bVar1 = cVar2 == '\0';
    cVar2 = '\0';
  } while (bVar1);
  return;
}


// ===== FUN_CODE_f6fc  [bootloader]  callers: CODE:eed2 CODE:ec86

void FUN_CODE_f6fc(undefined1 param_1,undefined1 param_2,undefined1 param_3,char param_4)

{
  bool bVar1;
  
  DAT_EXTMEM_0440 = param_3;
  DAT_EXTMEM_0441 = param_2;
  DAT_EXTMEM_0442 = param_1;
  do {
    if ((DAT_EXTMEM_2f41 >> 4 & 1) == 1) {
      if (DAT_EXTMEM_2f43 == BANK0_R6) {
        return;
      }
      if (DAT_EXTMEM_2f43 == '\0') {
        FUN_CODE_f8d0();
      }
      return;
    }
    FUN_CODE_f76d(0x440);
    bVar1 = param_4 == '\0';
    param_4 = '\0';
  } while (bVar1);
  return;
}


// ===== FUN_CODE_f730  [bootloader]  callers: CODE:eab8

void FUN_CODE_f730(undefined1 param_1,undefined1 param_2,undefined1 param_3)

{
  DAT_EXTMEM_0403 = param_3;
  DAT_EXTMEM_0404 = param_2;
  DAT_EXTMEM_0405 = param_1;
  FUN_CODE_f2c8(0,0x47,param_1,param_2,param_3);
  do {
    FUN_CODE_f8f1(0x403);
  } while ((DAT_EXTMEM_2f40 >> 1 & 1) == 1);
  FUN_CODE_e5cd(DAT_EXTMEM_0405,DAT_EXTMEM_0404,DAT_EXTMEM_0403,0);
  return;
}


// ===== FUN_CODE_f76a  [bootloader]  callers: CODE:ec86

void FUN_CODE_f76a(void)

{
  DAT_EXTMEM_0449 = DAT_EXTMEM_042e;
  DAT_EXTMEM_044a = DAT_EXTMEM_042f;
  DAT_EXTMEM_044b = DAT_EXTMEM_0430;
  while ((DAT_EXTMEM_2f52 >> 2 & 1) != 0) {
    FUN_CODE_f7a0(DAT_EXTMEM_044b,DAT_EXTMEM_044a,DAT_EXTMEM_0449);
    DAT_EXTMEM_2f52 = 4;
  }
  return;
}


// ===== FUN_CODE_f76d  [bootloader]  callers: CODE:eed2 CODE:ed90 CODE:e5cd CODE:f6fc

void FUN_CODE_f76d(undefined1 *param_1)

{
  DAT_EXTMEM_0449 = *param_1;
  DAT_EXTMEM_044a = param_1[1];
  DAT_EXTMEM_044b = param_1[2];
  while ((DAT_EXTMEM_2f52 >> 2 & 1) != 0) {
    FUN_CODE_f7a0(DAT_EXTMEM_044b,DAT_EXTMEM_044a,DAT_EXTMEM_0449);
    DAT_EXTMEM_2f52 = 4;
  }
  return;
}


// ===== FUN_CODE_f7a0  [bootloader]  callers: CODE:f76d

void FUN_CODE_f7a0(void)

{
  char cVar1;
  
  cVar1 = FUN_CODE_f289(1);
  if (cVar1 == '\0') {
    DAT_EXTMEM_2f64 = 1;
    DAT_EXTMEM_2f74 = 1;
    DAT_EXTMEM_2f84 = 1;
    DAT_EXTMEM_2f94 = 1;
    FUN_CODE_f8d0();
    DAT_EXTMEM_2f54 = 0;
    DAT_EXTMEM_2f52 = 0x11;
    FUN_CODE_f2c8(1,1);
    return;
  }
  return;
}


// ===== FUN_CODE_f7d5  [bootloader]  callers: CODE:e407 CODE:e061 CODE:e6ff CODE:f5c5

void FUN_CODE_f7d5(void)

{
  char cVar1;
  
  cVar1 = '\0';
  DAT_EXTMEM_043b = DAT_EXTMEM_0433;
  DAT_EXTMEM_043c = DAT_EXTMEM_0434;
  DAT_EXTMEM_043d = DAT_EXTMEM_0435;
  FUN_CODE_e823();
  if (cVar1 != '\0') {
    FUN_CODE_eed2(DAT_EXTMEM_0435,DAT_EXTMEM_0434,DAT_EXTMEM_0433);
  }
  return;
}


// ===== FUN_CODE_f809  [bootloader]  callers: CODE:f9b7 CODE:ee61

void FUN_CODE_f809(void)

{
  DAT_EXTMEM_0424 = DAT_EXTMEM_0546;
  DAT_EXTMEM_0425 = DAT_EXTMEM_0545;
  DAT_EXTMEM_042b = 0;
  DAT_EXTMEM_042c = DAT_EXTMEM_0548;
  FUN_CODE_f6ab(0x49,5,1,DAT_EXTMEM_0546,DAT_EXTMEM_0545);
  return;
}


// ===== FUN_CODE_f83b  [bootloader]  callers: CODE:e061

void FUN_CODE_f83b(undefined1 param_1,byte param_2,byte param_3)

{
  byte bVar1;
  
  DAT_EXTMEM_0421 = param_2;
  DAT_EXTMEM_0422 = param_3;
  DAT_EXTMEM_0423 = param_1;
  bVar1 = param_2;
  if (param_2 == 0) {
    bVar1 = param_3 ^ 1;
  }
  if (bVar1 == 0) {
    if (BANK0_R5 == '\x03') {
      FUN_CODE_f8b2();
      return;
    }
  }
  else {
    if (param_2 == 0) {
      param_2 = param_3 ^ 9;
    }
    if (param_2 == 0) {
      FUN_CODE_ee09();
      return;
    }
  }
  return;
}


// ===== FUN_CODE_f86d  [bootloader]  callers: 

void FUN_CODE_f86d(void)

{
  undefined1 uVar1;
  
  uVar1 = FUN_CODE_f289(2);
  DAT_EXTMEM_0425 = FUN_CODE_f289(3,uVar1);
  FUN_CODE_f2c8(uVar1,2,DAT_EXTMEM_0424,DAT_EXTMEM_0423,DAT_EXTMEM_0422);
  FUN_CODE_eb67();
  return;
}


// ===== FUN_CODE_f896  [bootloader]  callers: CODE:ef2f

void FUN_CODE_f896(void)

{
  if ((DAT_EXTMEM_1f01 >> 6 & 1) != 0) {
    DAT_EXTMEM_1f07 = 0x5c;
    return;
  }
  if ((DAT_EXTMEM_1f01 >> 3 & 1) != 1) {
    DAT_EXTMEM_1f06 = 0xff;
  }
  return;
}


// ===== FUN_CODE_f8b2  [bootloader]  callers: CODE:f83b

void FUN_CODE_f8b2(void)

{
  DAT_EXTMEM_0443 = 1;
  DAT_EXTMEM_0444 = 5;
  DAT_EXTMEM_0445 = 0x44;
  DAT_EXTMEM_0446 = 0x3f;
  FUN_CODE_f478();
  return;
}


// ===== FUN_CODE_f8ca  [bootloader]  callers: CODE:e5cd CODE:ec86

void FUN_CODE_f8ca(void)

{
  DAT_EXTMEM_2f52 = 0x11;
  DAT_EXTMEM_2f40 = 3;
  return;
}


// ===== FUN_CODE_f8d0  [bootloader]  callers: CODE:eed2 CODE:f7a0 CODE:e5cd CODE:eab8 CODE:f6fc CODE:eb67

void FUN_CODE_f8d0(void)

{
  DAT_EXTMEM_2f40 = 3;
  return;
}


// ===== FUN_CODE_f8d7  [bootloader]  callers: CODE:eed2 CODE:ed90 CODE:e5cd CODE:ec86

void FUN_CODE_f8d7(void)

{
  if (DAT_EXTMEM_2f42 == BANK0_R7) {
    return;
  }
  return;
}


// ===== FUN_CODE_f8e4  [bootloader]  callers: CODE:f520

void FUN_CODE_f8e4(void)

{
  return;
}


// ===== FUN_CODE_f8f1  [bootloader]  callers: CODE:eab8 CODE:f730

void FUN_CODE_f8f1(undefined1 *param_1)

{
  DAT_EXTMEM_0449 = *param_1;
  DAT_EXTMEM_044a = param_1[1];
  DAT_EXTMEM_044b = param_1[2];
  while ((DAT_EXTMEM_2f52 >> 2 & 1) != 0) {
    FUN_CODE_f7a0(DAT_EXTMEM_044b,DAT_EXTMEM_044a,DAT_EXTMEM_0449);
    DAT_EXTMEM_2f52 = 4;
  }
  return;
}


// ===== H_F9B7  [bootloader]  callers: 

byte H_F9B7(byte param_1,char *param_2,char param_3,char param_4,byte param_5)

{
  byte bVar1;
  
  do {
    bVar1 = BANK0_R0;
    param_3 = param_3 + '\x01';
    param_4 = param_4 + -1;
    if (param_4 == '\0') {
      bVar1 = FUN_CODE_f809(param_3);
      return bVar1;
    }
    nop();
    if (_0_0 == '\x01') {
      nop();
    }
    else {
      nop();
      param_1 = param_1 ^ BANK0_R0;
      BANK0_R0 = BANK0_R0 ^ 0x68;
      nop();
      param_1 = param_1 + param_5;
      nop();
      if (_0_0 != '\x01') {
        nop();
        nop();
        BANK0_R0 = bVar1 ^ 0x46;
        nop();
        return param_1 ^ param_5;
      }
    }
    *param_2 = *param_2 + '\x01';
    DAT_SFR_ff = param_3;
  } while( true );
}


// ===== FUN_CODE_fd00  [bootloader]  callers: 

void FUN_CODE_fd00(void)

{
  undefined1 *puVar1;
  char cVar2;
  char cVar3;
  undefined1 *puVar4;
  
  puVar1 = (undefined1 *)0xff;
  do {
    *puVar1 = 0;
    puVar1 = puVar1 + -1;
  } while (puVar1 != (undefined1 *)0x0);
  puVar4 = (undefined1 *)0x0;
  cVar3 = '\0';
  cVar2 = '\x10';
  do {
    do {
      *puVar4 = 0;
      puVar4 = puVar4 + 1;
      cVar3 = cVar3 + -1;
    } while (cVar3 != '\0');
    cVar2 = cVar2 + -1;
  } while (cVar2 != '\0');
  SP = 0xa0;
  FUN_CODE_020b(1,0x36,1);
  FUN_CODE_0136();
  nop();
  nop();
  nop();
  return;
}


// ===== FUN_CODE_fe00  [bootloader]  callers: CODE:0f7f

void FUN_CODE_fe00(void)

{
  undefined1 *puVar1;
  char cVar2;
  char cVar3;
  undefined1 *puVar4;
  
  puVar1 = (undefined1 *)0xff;
  do {
    *puVar1 = 0;
    puVar1 = puVar1 + -1;
  } while (puVar1 != (undefined1 *)0x0);
  puVar4 = (undefined1 *)0x0;
  cVar3 = '\0';
  cVar2 = '\x10';
  do {
    do {
      *puVar4 = 0;
      puVar4 = puVar4 + 1;
      cVar3 = cVar3 + -1;
    } while (cVar3 != '\0');
    cVar2 = cVar2 + -1;
  } while (cVar2 != '\0');
  SP = 0xa0;
  FUN_CODE_020b(1,0x36,1);
  FUN_CODE_0136();
  nop();
  nop();
  nop();
  return;
}


