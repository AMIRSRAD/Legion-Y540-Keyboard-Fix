
/* WARNING: Type propagation algorithm not settling */
/* WARNING: Restarted to delay deadcode elimination for space: stack */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

void load_code_flow(void)

{
  char cVar1;
  TStrings *pTVar2;
  _func_int *p_Var3;
  TLabel *pTVar4;
  TForm1 *pTVar5;
  byte bVar6;
  bool bVar7;
  int iVar8;
  int iVar9;
  DWORD DVar10;
  DWORD DVar11;
  uint uVar12;
  undefined4 extraout_var;
  BYTE *pDataBuf_00;
  FILE *pFVar13;
  longlong lVar14;
  AnsiStringT<0> *this;
  char *pcVar15;
  undefined4 extraout_var_00;
  AnsiStringT<0> *this_00;
  USAGE UVar16;
  USAGE UVar17;
  int iStack_df4;
  int iStack_d44;
  int iStack_ce4;
  undefined8 uStack_ce0;
  undefined8 uStack_cd8;
  undefined8 uStack_cd0;
  AnsiStringBase AStack_cc8;
  int iStack_cbc;
  undefined8 uStack_cb8;
  undefined8 uStack_cb0;
  undefined8 uStack_ca8;
  undefined8 uStack_ca0;
  AnsiStringBase AStack_c98;
  int iStack_c90;
  undefined8 uStack_c80;
  undefined8 uStack_c78;
  char cStack_c69;
  undefined8 *puStack_c68;
  undefined8 *puStack_c60;
  String *pSStack_c58;
  int iStack_c4c;
  String *pSStack_c48;
  WideChar *pWStack_c40;
  undefined8 *puStack_c38;
  undefined4 uStack_c30;
  int iStack_c2c;
  String *pSStack_c28;
  undefined8 *puStack_c20;
  AnsiStringBase *pAStack_c18;
  AnsiStringBase *pAStack_c10;
  undefined8 *puStack_c00;
  undefined8 *puStack_bf8;
  undefined8 *puStack_bf0;
  undefined8 *puStack_be0;
  String *pSStack_bd8;
  int iStack_bcc;
  String *pSStack_bc8;
  WideChar *pWStack_bc0;
  undefined8 *puStack_bb8;
  AnsiStringBase *pAStack_bb0;
  undefined4 uStack_ba8;
  int iStack_ba4;
  String *pSStack_ba0;
  undefined8 *puStack_b98;
  AnsiStringBase *pAStack_b90;
  undefined8 local_668;
  undefined8 local_660;
  AnsiStringT<0> local_658;
  AnsiStringT<0> local_650;
  AnsiStringT<0> local_648;
  AnsiString OEMVERData;
  undefined8 local_638;
  undefined8 local_630;
  undefined8 local_628;
  String local_620;
  AnsiStringT<0> local_618;
  undefined8 local_610;
  undefined8 local_608;
  undefined8 local_600;
  byte local_5f8 [8];
  AnsiStringBase local_5f0;
  AnsiStringBase local_5e8;
  undefined8 local_5e0;
  int i_2;
  AnsiStringBase local_5d0;
  AnsiStringBase local_5c8;
  undefined8 local_5c0;
  undefined8 local_5b8;
  undefined8 local_5b0;
  undefined8 local_5a8;
  AnsiStringT<0> local_5a0;
  AnsiString BackupFile;
  undefined8 local_590;
  undefined8 local_588;
  undefined8 local_580;
  undefined8 local_578;
  undefined8 local_570;
  undefined8 local_568;
  undefined8 local_560;
  undefined8 local_558;
  undefined8 local_550;
  undefined8 local_548;
  undefined8 local_540;
  undefined8 local_538;
  int k;
  undefined8 local_528;
  byte local_520 [8];
  undefined8 local_518;
  undefined8 local_510;
  undefined8 local_508;
  int i_1;
  uint local_4fc;
  undefined8 local_4f8 [2];
  undefined8 local_4e8;
  BOOL success;
  DWORD tick;
  char oemver_dst [34];
  char oemver_src [34];
  UCHAR Have8910BXBBK;
  UCHAR Is8910BXVersion;
  AnsiString stPrint;
  BYTE *pDst;
  BYTE *pSrc;
  BYTE *pDataBuf;
  int ClockFlag;
  int i;
  int total_sector;
  int file_len;
  FILE *fp;
  UCHAR buffer [63];
  UCHAR local_34e;
  UCHAR UStack_34d;
  UCHAR local_34c;
  UCHAR UStack_34b;
  UCHAR UStack_34a;
  char *local_250;
  UCHAR local_23c;
  UCHAR UStack_23b;
  UCHAR UStack_23a;
  UCHAR local_22e;
  UCHAR UStack_22d;
  UCHAR local_22c;
  UCHAR UStack_22b;
  UCHAR UStack_22a;
  uint iStart;
  uint iStart_1;
  uint iStart_2;
  uint iStart_3;
  uint iStart_4;
  uint iStart_5;
  
  stPrint.super_AnsiStringBase.Data = (AnsiStringBase)(char *)0x0;
  oemver_src[0x10] = '\0';
  oemver_src[0x11] = '\0';
  oemver_src[0x12] = '\0';
  oemver_src[0x13] = '\0';
  oemver_src[0x14] = '\0';
  oemver_src[0x15] = '\0';
  oemver_src[0x16] = '\0';
  oemver_src[0x17] = '\0';
  oemver_src[0x18] = '\0';
  oemver_src[0x19] = '\0';
  oemver_src[0x1a] = '\0';
  oemver_src[0x1b] = '\0';
  oemver_src[0x1c] = '\0';
  oemver_src[0x1d] = '\0';
  oemver_src[0x1e] = '\0';
  oemver_src[0x1f] = '\0';
  oemver_src[0] = '\0';
  oemver_src[1] = '\0';
  oemver_src[2] = '\0';
  oemver_src[3] = '\0';
  oemver_src[4] = '\0';
  oemver_src[5] = '\0';
  oemver_src[6] = '\0';
  oemver_src[7] = '\0';
  oemver_src[8] = '\0';
  oemver_src[9] = '\0';
  oemver_src[10] = '\0';
  oemver_src[0xb] = '\0';
  oemver_src[0xc] = '\0';
  oemver_src[0xd] = '\0';
  oemver_src[0xe] = '\0';
  oemver_src[0xf] = '\0';
  oemver_src[0x20] = '\0';
  oemver_src[0x21] = '\0';
  oemver_dst[0x10] = '\0';
  oemver_dst[0x11] = '\0';
  oemver_dst[0x12] = '\0';
  oemver_dst[0x13] = '\0';
  oemver_dst[0x14] = '\0';
  oemver_dst[0x15] = '\0';
  oemver_dst[0x16] = '\0';
  oemver_dst[0x17] = '\0';
  oemver_dst[0x18] = '\0';
  oemver_dst[0x19] = '\0';
  oemver_dst[0x1a] = '\0';
  oemver_dst[0x1b] = '\0';
  oemver_dst[0x1c] = '\0';
  oemver_dst[0x1d] = '\0';
  oemver_dst[0x1e] = '\0';
  oemver_dst[0x1f] = '\0';
  oemver_dst[0] = '\0';
  oemver_dst[1] = '\0';
  oemver_dst[2] = '\0';
  oemver_dst[3] = '\0';
  oemver_dst[4] = '\0';
  oemver_dst[5] = '\0';
  oemver_dst[6] = '\0';
  oemver_dst[7] = '\0';
  oemver_dst[8] = '\0';
  oemver_dst[9] = '\0';
  oemver_dst[10] = '\0';
  oemver_dst[0xb] = '\0';
  oemver_dst[0xc] = '\0';
  oemver_dst[0xd] = '\0';
  oemver_dst[0xe] = '\0';
  oemver_dst[0xf] = '\0';
  oemver_dst[0x20] = '\0';
  oemver_dst[0x21] = '\0';
  iVar8 = (**(msUpdateBINBuffer->super_TCustomMemoryStream).super_TStream.super_TObject.
             _vptr_TObject)(msUpdateBINBuffer);
  if (CONCAT44(extraout_var,iVar8) != 0) {
    iVar8 = (**(msUpdateBINBuffer->super_TCustomMemoryStream).super_TStream.super_TObject.
               _vptr_TObject)(msUpdateBINBuffer);
    if (Update_OnlyParameter == 0) {
      total_sector = (iVar8 / 0x400 + (uint)(0 < iVar8 % 0x400)) - Update_StartAddress / 0x400;
    }
    else {
      total_sector = iVar8 / 0x400 + (uint)(0 < iVar8 % 0x400);
    }
    if (total_sector < 0) {
      System::AnsiStringT<0>::printf(&stPrint,s_Size_error__006e040a);
      pTVar2 = (Form1->Memo1->super_TCustomMemo).FLines;
      p_Var3 = (pTVar2->super_TPersistent).super_TObject._vptr_TObject[0xf];
      local_4f8[0] = 0;
      _ZN6System8Internal7Strhlpr15UnicodeFromAnsiERNS_13UnicodeStringERNS_11AnsiStringTILt65535EEE
                (local_4f8,&stPrint);
      (*p_Var3)(pTVar2,local_4f8[0]);
      _ZN6System13UnicodeStringD1Ev(local_4f8);
      ReturnValue = 0xa1;
      local_4fc = 1;
      goto LAB_0040ebc0;
    }
    pDataBuf_00 = calloc((longlong)(iVar8 * 2),1);
    for (i_1 = 0; i_1 < iVar8; i_1 = i_1 + 1) {
      pDataBuf_00[i_1] =
           *(BYTE *)((longlong)(msUpdateBINBuffer->super_TCustomMemoryStream).FMemory +
                    (longlong)i_1);
    }
    if (Update_OnlyParameter == 0) {
      memcpy(oemver_src,pDataBuf_00 + OemVerOffset,0x20);
      read_flash(OemVerOffset,0x20,(BYTE *)oemver_dst);
      System::AnsiStringT<0>::printf(&stPrint,s_Old_Version___s_006e0416);
      pTVar2 = (Form1->Memo1->super_TCustomMemo).FLines;
      p_Var3 = (pTVar2->super_TPersistent).super_TObject._vptr_TObject[0xf];
      local_508 = 0;
      _ZN6System8Internal7Strhlpr15UnicodeFromAnsiERNS_13UnicodeStringERNS_11AnsiStringTILt65535EEE
                (&local_508,&stPrint);
      (*p_Var3)(pTVar2,local_508);
      _ZN6System13UnicodeStringD1Ev(&local_508);
      System::AnsiStringT<0>::printf(&stPrint,s_New_Version___s_006e0426);
      pTVar2 = (Form1->Memo1->super_TCustomMemo).FLines;
      p_Var3 = (pTVar2->super_TPersistent).super_TObject._vptr_TObject[0xf];
      local_510 = 0;
      _ZN6System8Internal7Strhlpr15UnicodeFromAnsiERNS_13UnicodeStringERNS_11AnsiStringTILt65535EEE
                (&local_510,&stPrint);
      (*p_Var3)(pTVar2);
      _ZN6System13UnicodeStringD1Ev(&local_510);
      read_flash(0,0x800,pDataBuf_00 + iVar8);
      if (NoCheckIVT == 0) {
        for (i = 4; i < 0x800; i = i + 1) {
          if ((((pDataBuf_00[i] != pDataBuf_00[(longlong)i + (longlong)iVar8]) && (i != 0x87)) &&
              (i != 0x8d)) && (((i != 0x1d && (i != 0x1e)) && (i != 0x1f)))) {
            System::AnsiStringT<0>::printf(&stPrint,s_IVT_Error__Xh___02Xh_____02Xh___006e0437);
            pTVar2 = (Form1->Memo1->super_TCustomMemo).FLines;
            p_Var3 = (pTVar2->super_TPersistent).super_TObject._vptr_TObject[0xf];
            local_518 = 0;
            _ZN6System8Internal7Strhlpr15UnicodeFromAnsiERNS_13UnicodeStringERNS_11AnsiStringTILt65535EEE
                      (&local_518,&stPrint);
            (*p_Var3)(pTVar2);
            _ZN6System13UnicodeStringD1Ev(&local_518);
            free(pDataBuf_00);
            pTVar5 = Form1;
            local_520[0] = 0;
            memset(local_520,0,1);
            _ZN3Vcl5Forms11TCustomForm14SetBorderIconsEN6System3SetINS2_7Uitypes11TBorderIconELS5_0ELS5_3EEE
                      (pTVar5,local_520[0] | 1);
            ReturnValue = 0xa3;
            local_4fc = 1;
            goto LAB_0040ebc0;
          }
        }
      }
    }
    if (Update_OnlyParameter == 0) {
      System::AnsiStringT<0>::printf(&stPrint,s_Start_Load_Code_Flow_0x_06X___0x_006e0457);
    }
    else {
      System::AnsiStringT<0>::printf(&stPrint,s_Start_Load_Code_Flow_0x_06X___0x_006e0457);
    }
    pTVar2 = (Form1->Memo1->super_TCustomMemo).FLines;
    p_Var3 = (pTVar2->super_TPersistent).super_TObject._vptr_TObject[0xf];
    local_528 = 0;
    _ZN6System8Internal7Strhlpr15UnicodeFromAnsiERNS_13UnicodeStringERNS_11AnsiStringTILt65535EEE
              (&local_528,&stPrint);
    (*p_Var3)(pTVar2,local_528);
    _ZN6System13UnicodeStringD1Ev(&local_528);
    tick = GetTickCount();
    for (k = 0; k < ProgramFailRetry + 1; k = k + 1) {
      local_34e = (UCHAR)total_sector;
      UStack_34d = (UCHAR)((uint)total_sector >> 8);
      if ((SpecialFlow != 1) && (SpecialFlow != 3)) {
        if (NeedErase != 0) {
          System::AnsiStringT<0>::printf(&stPrint,s_erase_006e047e);
          pTVar2 = (Form1->Memo1->super_TCustomMemo).FLines;
          p_Var3 = (pTVar2->super_TPersistent).super_TObject._vptr_TObject[0xf];
          local_538 = 0;
          _ZN6System8Internal7Strhlpr15UnicodeFromAnsiERNS_13UnicodeStringERNS_11AnsiStringTILt65535EEE
                    (&local_538,&stPrint);
          (*p_Var3)(pTVar2,local_538);
          _ZN6System13UnicodeStringD1Ev(&local_538);
          pTVar2 = (Form1->Memo2->super_TCustomMemo).FLines;
          p_Var3 = (pTVar2->super_TPersistent).super_TObject._vptr_TObject[0xf];
          local_540 = 0;
          _ZN6System8Internal7Strhlpr15UnicodeFromAnsiERNS_13UnicodeStringERNS_11AnsiStringTILt65535EEE
                    (&local_540,&stPrint);
          (*p_Var3)(pTVar2,local_540);
          _ZN6System13UnicodeStringD1Ev(&local_540);
          buffer[0x30] = '\0';
          buffer[0x31] = '\0';
          buffer[0x32] = '\0';
          buffer[0x33] = '\0';
          buffer[0x34] = '\0';
          buffer[0x35] = '\0';
          buffer[0x36] = '\0';
          buffer[0x37] = '\0';
          buffer[0x38] = '\0';
          buffer[0x39] = '\0';
          buffer[0x3a] = '\0';
          buffer[0x3b] = '\0';
          buffer[0x3c] = '\0';
          buffer[0x3d] = '\0';
          buffer[0x3e] = '\0';
          buffer[0x20] = '\0';
          buffer[0x21] = '\0';
          buffer[0x22] = '\0';
          buffer[0x23] = '\0';
          buffer[0x24] = '\0';
          buffer[0x25] = '\0';
          buffer[0x26] = '\0';
          buffer[0x27] = '\0';
          buffer[0x28] = '\0';
          buffer[0x29] = '\0';
          buffer[0x2a] = '\0';
          buffer[0x2b] = '\0';
          buffer[0x2c] = '\0';
          buffer[0x2d] = '\0';
          buffer[0x2e] = '\0';
          buffer[0x2f] = '\0';
          buffer[0x10] = '\0';
          buffer[0x11] = '\0';
          buffer[0x12] = '\0';
          buffer[0x13] = '\0';
          buffer[0x14] = '\0';
          buffer[0x15] = '\0';
          buffer[0x16] = '\0';
          buffer[0x17] = '\0';
          buffer[0x18] = '\0';
          buffer[0x19] = '\0';
          buffer[0x1a] = '\0';
          buffer[0x1b] = '\0';
          buffer[0x1c] = '\0';
          buffer[0x1d] = '\0';
          buffer[0x1e] = '\0';
          buffer[0x1f] = '\0';
          buffer[8] = '\0';
          buffer[9] = '\0';
          buffer[10] = '\0';
          buffer[0xb] = '\0';
          buffer[0xc] = '\0';
          buffer[0xd] = '\0';
          buffer[0xe] = '\0';
          buffer[0xf] = '\0';
          local_34c = (UCHAR)Update_StartAddress;
          buffer[1] = local_34c;
          buffer[0] = 0xc2;
          UStack_34b = (UCHAR)((uint)Update_StartAddress >> 8);
          buffer[2] = UStack_34b;
          UStack_34a = (UCHAR)((uint)Update_StartAddress >> 0x10);
          buffer[3] = UStack_34a;
          buffer[4] = local_34e;
          buffer[5] = UStack_34d;
          buffer[6] = '\0';
          buffer[7] = '\0';
          HidRequests(hFile[0],true,'\0',buffer,'\x06');
          Sleep(5);
        }
        if (SpecialFlow != 2) {
          System::AnsiStringT<0>::printf(&stPrint,s_write_006e0484);
          pTVar2 = (Form1->Memo1->super_TCustomMemo).FLines;
          p_Var3 = (pTVar2->super_TPersistent).super_TObject._vptr_TObject[0xf];
          local_548 = 0;
          _ZN6System8Internal7Strhlpr15UnicodeFromAnsiERNS_13UnicodeStringERNS_11AnsiStringTILt65535EEE
                    (&local_548,&stPrint);
          (*p_Var3)(pTVar2,local_548);
          _ZN6System13UnicodeStringD1Ev(&local_548);
          pTVar2 = (Form1->Memo2->super_TCustomMemo).FLines;
          p_Var3 = (pTVar2->super_TPersistent).super_TObject._vptr_TObject[0xf];
          local_550 = 0;
          _ZN6System8Internal7Strhlpr15UnicodeFromAnsiERNS_13UnicodeStringERNS_11AnsiStringTILt65535EEE
                    (&local_550,&stPrint);
          (*p_Var3)(pTVar2,local_550);
          _ZN6System13UnicodeStringD1Ev(&local_550);
          if (Update_OnlyParameter == 0) {
            PassOrWriteFirst1K = '\x01';
            write_flash(Update_StartAddress,iVar8 - Update_StartAddress,
                        pDataBuf_00 + Update_StartAddress);
            PassOrWriteFirst1K = '\x02';
            write_flash(Update_StartAddress,iVar8 - Update_StartAddress,
                        pDataBuf_00 + Update_StartAddress);
            PassOrWriteFirst1K = '\0';
          }
          else {
            write_flash(Update_StartAddress,iVar8,pDataBuf_00);
          }
        }
      }
      if (SpecialFlow == 2) {
        success = 1;
      }
      else {
        System::AnsiStringT<0>::printf(&stPrint,&DAT_006e048a);
        pTVar2 = (Form1->Memo1->super_TCustomMemo).FLines;
        p_Var3 = (pTVar2->super_TPersistent).super_TObject._vptr_TObject[0xf];
        local_558 = 0;
        _ZN6System8Internal7Strhlpr15UnicodeFromAnsiERNS_13UnicodeStringERNS_11AnsiStringTILt65535EEE
                  (&local_558,&stPrint);
        (*p_Var3)(pTVar2,local_558);
        _ZN6System13UnicodeStringD1Ev(&local_558);
        pTVar2 = (Form1->Memo2->super_TCustomMemo).FLines;
        p_Var3 = (pTVar2->super_TPersistent).super_TObject._vptr_TObject[0xf];
        local_560 = 0;
        _ZN6System8Internal7Strhlpr15UnicodeFromAnsiERNS_13UnicodeStringERNS_11AnsiStringTILt65535EEE
                  (&local_560,&stPrint);
        (*p_Var3)(pTVar2,local_560);
        _ZN6System13UnicodeStringD1Ev(&local_560);
        if (Update_OnlyParameter == 0) {
          read_flash(Update_StartAddress,iVar8 - Update_StartAddress,
                     pDataBuf_00 + (longlong)Update_StartAddress + (longlong)iVar8);
        }
        else {
          read_flash(Update_StartAddress,iVar8,pDataBuf_00 + iVar8);
        }
        if ((SpecialFlow == 1) || (SpecialFlow == 3)) {
          pFVar13 = fopen(s_flashbin_000_006e048f,&DAT_006e049c);
          fwrite(pDataBuf_00 + iVar8,1,(longlong)iVar8,pFVar13);
          fclose(pFVar13);
          success = 1;
        }
        if (SpecialFlow != 3) {
          if (Update_OnlyParameter == 0) {
            iVar9 = memcmp(pDataBuf_00 + Update_StartAddress,
                           pDataBuf_00 + (longlong)Update_StartAddress + (longlong)iVar8,
                           (longlong)(iVar8 - Update_StartAddress));
          }
          else {
            iVar9 = memcmp(pDataBuf_00,pDataBuf_00 + iVar8,(longlong)iVar8);
          }
          success = (BOOL)(iVar9 == 0);
        }
        if (success == 0) {
          System::AnsiStringT<0>::printf(&stPrint,s_Compare_Fail__006e04ab);
          pTVar2 = (Form1->Memo1->super_TCustomMemo).FLines;
          p_Var3 = (pTVar2->super_TPersistent).super_TObject._vptr_TObject[0xf];
          local_578 = 0;
          _ZN6System8Internal7Strhlpr15UnicodeFromAnsiERNS_13UnicodeStringERNS_11AnsiStringTILt65535EEE
                    (&local_578,&stPrint);
          (*p_Var3)(pTVar2,local_578);
          _ZN6System13UnicodeStringD1Ev(&local_578);
          pTVar2 = (Form1->Memo2->super_TCustomMemo).FLines;
          p_Var3 = (pTVar2->super_TPersistent).super_TObject._vptr_TObject[0xf];
          local_580 = 0;
          _ZN6System8Internal7Strhlpr15UnicodeFromAnsiERNS_13UnicodeStringERNS_11AnsiStringTILt65535EEE
                    (&local_580,&stPrint);
          (*p_Var3)(pTVar2,local_580);
          _ZN6System13UnicodeStringD1Ev(&local_580);
          if (SpecialFlow != 1) {
            System::AnsiStringT<0>::printf(&stPrint,s_Compare_Fail___>_erase_flash_006e04b9);
            pTVar2 = (Form1->Memo1->super_TCustomMemo).FLines;
            p_Var3 = (pTVar2->super_TPersistent).super_TObject._vptr_TObject[0xf];
            local_588 = 0;
            _ZN6System8Internal7Strhlpr15UnicodeFromAnsiERNS_13UnicodeStringERNS_11AnsiStringTILt65535EEE
                      (&local_588,&stPrint);
            (*p_Var3)(pTVar2,local_588);
            _ZN6System13UnicodeStringD1Ev(&local_588);
            pTVar2 = (Form1->Memo2->super_TCustomMemo).FLines;
            p_Var3 = (pTVar2->super_TPersistent).super_TObject._vptr_TObject[0xf];
            local_590 = 0;
            _ZN6System8Internal7Strhlpr15UnicodeFromAnsiERNS_13UnicodeStringERNS_11AnsiStringTILt65535EEE
                      (&local_590,&stPrint);
            (*p_Var3)(pTVar2,local_590);
            _ZN6System13UnicodeStringD1Ev(&local_590);
            memset(&BackupFile,0,8);
            memset(&BackupFile,0,8);
            BackupFile.super_AnsiStringBase.Data = (AnsiStringBase)(char *)0x0;
            memset(&local_5a0,0,8);
            iVar9 = k;
            memset(&local_5b0,0,8);
            local_5b0 = 0;
            _ZN6System8Sysutils8IntToHexEii(&local_5b0,iVar9,3);
            memset(&local_5a8,0,8);
            local_5a8 = 0;
            _ZN6SystemplEPKcRKNS_13UnicodeStringE(&local_5a8,s_Backup__006e04d6,&local_5b0);
            local_5a0.super_AnsiStringBase.Data = (AnsiStringBase)(char *)0x0;
            _ZN6System14AnsiStringBaseC2ERKNS_13UnicodeStringEi(&local_5a0,&local_5a8,0);
            _ZN6System14AnsiStringBaseaSERKS0_(&BackupFile,&local_5a0);
            System::AnsiStringT<0>::~AnsiStringT(&local_5a0);
            _ZN6System13UnicodeStringD1Ev(&local_5a8);
            _ZN6System13UnicodeStringD1Ev(&local_5b0);
            if (BackupFile.super_AnsiStringBase.Data == (char *)0x0) {
              local_250 = &DAT_006e0293;
            }
            else {
              local_250 = (char *)BackupFile.super_AnsiStringBase.Data;
            }
            pFVar13 = fopen(local_250,&DAT_006e049c);
            fwrite(pDataBuf_00 + iVar8,1,(longlong)iVar8,pFVar13);
            fclose(pFVar13);
            if (ProgramFailEraseSkipFirst1K == 0) {
              buffer[0x30] = '\0';
              buffer[0x31] = '\0';
              buffer[0x32] = '\0';
              buffer[0x33] = '\0';
              buffer[0x34] = '\0';
              buffer[0x35] = '\0';
              buffer[0x36] = '\0';
              buffer[0x37] = '\0';
              buffer[0x38] = '\0';
              buffer[0x39] = '\0';
              buffer[0x3a] = '\0';
              buffer[0x3b] = '\0';
              buffer[0x3c] = '\0';
              buffer[0x3d] = '\0';
              buffer[0x3e] = '\0';
              buffer[0x20] = '\0';
              buffer[0x21] = '\0';
              buffer[0x22] = '\0';
              buffer[0x23] = '\0';
              buffer[0x24] = '\0';
              buffer[0x25] = '\0';
              buffer[0x26] = '\0';
              buffer[0x27] = '\0';
              buffer[0x28] = '\0';
              buffer[0x29] = '\0';
              buffer[0x2a] = '\0';
              buffer[0x2b] = '\0';
              buffer[0x2c] = '\0';
              buffer[0x2d] = '\0';
              buffer[0x2e] = '\0';
              buffer[0x2f] = '\0';
              buffer[0x10] = '\0';
              buffer[0x11] = '\0';
              buffer[0x12] = '\0';
              buffer[0x13] = '\0';
              buffer[0x14] = '\0';
              buffer[0x15] = '\0';
              buffer[0x16] = '\0';
              buffer[0x17] = '\0';
              buffer[0x18] = '\0';
              buffer[0x19] = '\0';
              buffer[0x1a] = '\0';
              buffer[0x1b] = '\0';
              buffer[0x1c] = '\0';
              buffer[0x1d] = '\0';
              buffer[0x1e] = '\0';
              buffer[0x1f] = '\0';
              buffer[8] = '\0';
              buffer[9] = '\0';
              buffer[10] = '\0';
              buffer[0xb] = '\0';
              buffer[0xc] = '\0';
              buffer[0xd] = '\0';
              buffer[0xe] = '\0';
              buffer[0xf] = '\0';
              local_23c = (UCHAR)Update_StartAddress;
              buffer[1] = local_23c;
              buffer[0] = 0xc2;
              UStack_23b = (UCHAR)((uint)Update_StartAddress >> 8);
              buffer[2] = UStack_23b;
              UStack_23a = (UCHAR)((uint)Update_StartAddress >> 0x10);
              buffer[3] = UStack_23a;
              buffer[4] = local_34e;
              buffer[5] = UStack_34d;
              buffer[6] = '\0';
              buffer[7] = '\0';
              HidRequests(hFile[0],true,'\0',buffer,'\x06');
              Sleep(5);
            }
            else {
              iVar9 = Update_StartAddress + 0x400;
              buffer[0x30] = '\0';
              buffer[0x31] = '\0';
              buffer[0x32] = '\0';
              buffer[0x33] = '\0';
              buffer[0x34] = '\0';
              buffer[0x35] = '\0';
              buffer[0x36] = '\0';
              buffer[0x37] = '\0';
              buffer[0x38] = '\0';
              buffer[0x39] = '\0';
              buffer[0x3a] = '\0';
              buffer[0x3b] = '\0';
              buffer[0x3c] = '\0';
              buffer[0x3d] = '\0';
              buffer[0x3e] = '\0';
              buffer[0x20] = '\0';
              buffer[0x21] = '\0';
              buffer[0x22] = '\0';
              buffer[0x23] = '\0';
              buffer[0x24] = '\0';
              buffer[0x25] = '\0';
              buffer[0x26] = '\0';
              buffer[0x27] = '\0';
              buffer[0x28] = '\0';
              buffer[0x29] = '\0';
              buffer[0x2a] = '\0';
              buffer[0x2b] = '\0';
              buffer[0x2c] = '\0';
              buffer[0x2d] = '\0';
              buffer[0x2e] = '\0';
              buffer[0x2f] = '\0';
              buffer[0x10] = '\0';
              buffer[0x11] = '\0';
              buffer[0x12] = '\0';
              buffer[0x13] = '\0';
              buffer[0x14] = '\0';
              buffer[0x15] = '\0';
              buffer[0x16] = '\0';
              buffer[0x17] = '\0';
              buffer[0x18] = '\0';
              buffer[0x19] = '\0';
              buffer[0x1a] = '\0';
              buffer[0x1b] = '\0';
              buffer[0x1c] = '\0';
              buffer[0x1d] = '\0';
              buffer[0x1e] = '\0';
              buffer[0x1f] = '\0';
              buffer[8] = '\0';
              buffer[9] = '\0';
              buffer[10] = '\0';
              buffer[0xb] = '\0';
              buffer[0xc] = '\0';
              buffer[0xd] = '\0';
              buffer[0xe] = '\0';
              buffer[0xf] = '\0';
              local_22c = (UCHAR)iVar9;
              buffer[1] = local_22c;
              buffer[0] = 0xc2;
              UStack_22b = (UCHAR)((uint)iVar9 >> 8);
              buffer[2] = UStack_22b;
              UStack_22a = (UCHAR)((uint)iVar9 >> 0x10);
              buffer[3] = UStack_22a;
              local_22e = (UCHAR)((short)total_sector + -1);
              buffer[4] = local_22e;
              UStack_22d = (UCHAR)((ushort)((short)total_sector + -1) >> 8);
              buffer[5] = UStack_22d;
              buffer[6] = '\0';
              buffer[7] = '\0';
              HidRequests(hFile[0],true,'\0',buffer,'\x06');
              Sleep(5);
            }
            System::AnsiStringT<0>::~AnsiStringT(&BackupFile);
          }
        }
        else {
          System::AnsiStringT<0>::printf(&stPrint,s_Compare_OK__006e049f);
          pTVar2 = (Form1->Memo1->super_TCustomMemo).FLines;
          p_Var3 = (pTVar2->super_TPersistent).super_TObject._vptr_TObject[0xf];
          local_568 = 0;
          _ZN6System8Internal7Strhlpr15UnicodeFromAnsiERNS_13UnicodeStringERNS_11AnsiStringTILt65535EEE
                    (&local_568,&stPrint);
          (*p_Var3)(pTVar2,local_568);
          _ZN6System13UnicodeStringD1Ev(&local_568);
          pTVar2 = (Form1->Memo2->super_TCustomMemo).FLines;
          p_Var3 = (pTVar2->super_TPersistent).super_TObject._vptr_TObject[0xf];
          local_570 = 0;
          _ZN6System8Internal7Strhlpr15UnicodeFromAnsiERNS_13UnicodeStringERNS_11AnsiStringTILt65535EEE
                    (&local_570,&stPrint);
          (*p_Var3)(pTVar2,local_570);
          _ZN6System13UnicodeStringD1Ev(&local_570);
        }
      }
      if (success != 0) break;
    }
    free(pDataBuf_00);
    DVar10 = GetTickCount();
    tick = DVar10 - tick;
    System::AnsiStringT<0>::printf(&stPrint,s_Total_Time___d_s_006e04de);
    pTVar2 = (Form1->Memo1->super_TCustomMemo).FLines;
    p_Var3 = (pTVar2->super_TPersistent).super_TObject._vptr_TObject[0xf];
    local_5b8 = 0;
    _ZN6System8Internal7Strhlpr15UnicodeFromAnsiERNS_13UnicodeStringERNS_11AnsiStringTILt65535EEE
              (&local_5b8,&stPrint);
    (*p_Var3)(pTVar2,local_5b8);
    _ZN6System13UnicodeStringD1Ev(&local_5b8);
    pTVar2 = (Form1->Memo2->super_TCustomMemo).FLines;
    p_Var3 = (pTVar2->super_TPersistent).super_TObject._vptr_TObject[0xf];
    local_5c0 = 0;
    _ZN6System8Internal7Strhlpr15UnicodeFromAnsiERNS_13UnicodeStringERNS_11AnsiStringTILt65535EEE
              (&local_5c0,&stPrint);
    (*p_Var3)(pTVar2);
    _ZN6System13UnicodeStringD1Ev(&local_5c0);
    if (success == 0) {
      if (ProgramFailEraseThenReset != 0) {
        buffer[0x30] = '\0';
        buffer[0x31] = '\0';
        buffer[0x32] = '\0';
        buffer[0x33] = '\0';
        buffer[0x34] = '\0';
        buffer[0x35] = '\0';
        buffer[0x36] = '\0';
        buffer[0x37] = '\0';
        buffer[0x38] = '\0';
        buffer[0x39] = '\0';
        buffer[0x3a] = '\0';
        buffer[0x3b] = '\0';
        buffer[0x3c] = '\0';
        buffer[0x3d] = '\0';
        buffer[0x3e] = '\0';
        buffer[0x20] = '\0';
        buffer[0x21] = '\0';
        buffer[0x22] = '\0';
        buffer[0x23] = '\0';
        buffer[0x24] = '\0';
        buffer[0x25] = '\0';
        buffer[0x26] = '\0';
        buffer[0x27] = '\0';
        buffer[0x28] = '\0';
        buffer[0x29] = '\0';
        buffer[0x2a] = '\0';
        buffer[0x2b] = '\0';
        buffer[0x2c] = '\0';
        buffer[0x2d] = '\0';
        buffer[0x2e] = '\0';
        buffer[0x2f] = '\0';
        buffer[0x10] = '\0';
        buffer[0x11] = '\0';
        buffer[0x12] = '\0';
        buffer[0x13] = '\0';
        buffer[0x14] = '\0';
        buffer[0x15] = '\0';
        buffer[0x16] = '\0';
        buffer[0x17] = '\0';
        buffer[0x18] = '\0';
        buffer[0x19] = '\0';
        buffer[0x1a] = '\0';
        buffer[0x1b] = '\0';
        buffer[0x1c] = '\0';
        buffer[0x1d] = '\0';
        buffer[0x1e] = '\0';
        buffer[0x1f] = '\0';
        buffer[8] = '\0';
        buffer[9] = '\0';
        buffer[10] = '\0';
        buffer[0xb] = '\0';
        buffer[0xc] = '\0';
        buffer[0xd] = '\0';
        buffer[0xe] = '\0';
        buffer[0xf] = '\0';
        buffer[0] = 0xc4;
        buffer[1] = '\0';
        buffer[2] = '\0';
        buffer[3] = '\0';
        buffer[4] = '\0';
        buffer[5] = '\0';
        buffer[6] = '\0';
        buffer[7] = '\0';
        HidRequests(hFile[0],true,'\0',buffer,'\x01');
        DVar10 = GetTickCount();
        while (DVar11 = GetTickCount(), DVar11 - DVar10 < 0x3e9) {
          _ZN3Vcl5Forms12TApplication15ProcessMessagesEv
                    (*(undefined8 *)__indStub__ZN3Vcl5Forms11ApplicationE);
        }
      }
    }
    else {
      buffer[0x30] = '\0';
      buffer[0x31] = '\0';
      buffer[0x32] = '\0';
      buffer[0x33] = '\0';
      buffer[0x34] = '\0';
      buffer[0x35] = '\0';
      buffer[0x36] = '\0';
      buffer[0x37] = '\0';
      buffer[0x38] = '\0';
      buffer[0x39] = '\0';
      buffer[0x3a] = '\0';
      buffer[0x3b] = '\0';
      buffer[0x3c] = '\0';
      buffer[0x3d] = '\0';
      buffer[0x3e] = '\0';
      buffer[0x20] = '\0';
      buffer[0x21] = '\0';
      buffer[0x22] = '\0';
      buffer[0x23] = '\0';
      buffer[0x24] = '\0';
      buffer[0x25] = '\0';
      buffer[0x26] = '\0';
      buffer[0x27] = '\0';
      buffer[0x28] = '\0';
      buffer[0x29] = '\0';
      buffer[0x2a] = '\0';
      buffer[0x2b] = '\0';
      buffer[0x2c] = '\0';
      buffer[0x2d] = '\0';
      buffer[0x2e] = '\0';
      buffer[0x2f] = '\0';
      buffer[0x10] = '\0';
      buffer[0x11] = '\0';
      buffer[0x12] = '\0';
      buffer[0x13] = '\0';
      buffer[0x14] = '\0';
      buffer[0x15] = '\0';
      buffer[0x16] = '\0';
      buffer[0x17] = '\0';
      buffer[0x18] = '\0';
      buffer[0x19] = '\0';
      buffer[0x1a] = '\0';
      buffer[0x1b] = '\0';
      buffer[0x1c] = '\0';
      buffer[0x1d] = '\0';
      buffer[0x1e] = '\0';
      buffer[0x1f] = '\0';
      buffer[8] = '\0';
      buffer[9] = '\0';
      buffer[10] = '\0';
      buffer[0xb] = '\0';
      buffer[0xc] = '\0';
      buffer[0xd] = '\0';
      buffer[0xe] = '\0';
      buffer[0xf] = '\0';
      buffer[0] = 0xc4;
      buffer[1] = '\0';
      buffer[2] = '\0';
      buffer[3] = '\0';
      buffer[4] = '\0';
      buffer[5] = '\0';
      buffer[6] = '\0';
      buffer[7] = '\0';
      HidRequests(hFile[0],true,'\0',buffer,'\x01');
      if (RemoveRescan != 0) {
        DVar10 = GetTickCount();
        while (DVar11 = GetTickCount(), DVar11 - DVar10 < 0x3e9) {
          _ZN3Vcl5Forms12TApplication15ProcessMessagesEv
                    (*(undefined8 *)__indStub__ZN3Vcl5Forms11ApplicationE);
        }
      }
      ConnectHub(0x80);
      iVar8 = DelayMSec;
      DVar10 = GetTickCount();
      while (DVar11 = GetTickCount(), DVar11 - DVar10 <= (uint)iVar8) {
        _ZN3Vcl5Forms12TApplication15ProcessMessagesEv
                  (*(undefined8 *)__indStub__ZN3Vcl5Forms11ApplicationE);
      }
      if (RemoveRescan != 0) {
        local_5c8.Data = (char *)0x0;
        _ZN6System14AnsiStringBaseC2ERKNS_13UnicodeStringEi(&local_5c8,&MainHWid,0);
        DisableEnableDevice((AnsiString)local_5c8.Data,false);
        System::AnsiStringT<0>::~AnsiStringT((AnsiStringT<0> *)&local_5c8);
        local_5d0.Data = (char *)0x0;
        _ZN6System14AnsiStringBaseC2ERKNS_13UnicodeStringEi(&local_5d0,&MainHWid,0);
        RemoveDevice((AnsiString)local_5d0.Data);
        System::AnsiStringT<0>::~AnsiStringT((AnsiStringT<0> *)&local_5d0);
        for (i_2 = 0; i_2 < 0x10; i_2 = i_2 + 1) {
          lVar14 = (longlong)i_2;
          local_5e0 = 0;
          _ZN6System13UnicodeStringC1EPKc(&local_5e0,&DAT_006e0293);
          bVar6 = _ZNK6System13UnicodeStringneERKS0_(MainHWid1_16 + lVar14);
          _ZN6System13UnicodeStringD1Ev(&local_5e0);
          if ((bVar6 & 1) != 0) {
            local_5e8.Data = (char *)0x0;
            _ZN6System14AnsiStringBaseC2ERKNS_13UnicodeStringEi(&local_5e8,MainHWid1_16 + i_2,0);
            DisableEnableDevice((AnsiString)local_5e8.Data,false);
            System::AnsiStringT<0>::~AnsiStringT((AnsiStringT<0> *)&local_5e8);
            local_5f0.Data = (char *)0x0;
            _ZN6System14AnsiStringBaseC2ERKNS_13UnicodeStringEi(&local_5f0,MainHWid1_16 + i_2,0);
            RemoveDevice((AnsiString)local_5f0.Data);
            System::AnsiStringT<0>::~AnsiStringT((AnsiStringT<0> *)&local_5f0);
          }
        }
        uVar12 = DelayMSec / 2;
        DVar10 = GetTickCount();
        while (DVar11 = GetTickCount(), DVar11 - DVar10 <= uVar12) {
          _ZN3Vcl5Forms12TApplication15ProcessMessagesEv
                    (*(undefined8 *)__indStub__ZN3Vcl5Forms11ApplicationE);
        }
        RescanDevice();
        uVar12 = DelayMSec / 2;
        DVar10 = GetTickCount();
        while (DVar11 = GetTickCount(), DVar11 - DVar10 <= uVar12) {
          _ZN3Vcl5Forms12TApplication15ProcessMessagesEv
                    (*(undefined8 *)__indStub__ZN3Vcl5Forms11ApplicationE);
        }
      }
      ConnectHub('\x01');
    }
    pTVar5 = Form1;
    local_5f8[0] = 0;
    memset(local_5f8,0,1);
    _ZN3Vcl5Forms11TCustomForm14SetBorderIconsEN6System3SetINS2_7Uitypes11TBorderIconELS5_0ELS5_3EEE
              (pTVar5,local_5f8[0] | 1);
    (**(code **)((longlong)
                 (Form1->Memo1->super_TCustomMemo).super_TCustomEdit.super_TWinControl.
                 super_TControl.super_TComponent.super_TPersistent.super_TObject + 0x280))
              (Form1->Memo1);
    _ZN3Vcl8Graphics5TFont7SetSizeEi
              ((Form1->Memo1->super_TCustomMemo).super_TCustomEdit.super_TWinControl.super_TControl.
               FFont,0x10);
    if (success == 0) {
      _ZN3Vcl8Graphics5TFont8SetColorEN6System7Uitypes6TColorE
                ((Form1->Memo1->super_TCustomMemo).super_TCustomEdit.super_TWinControl.
                 super_TControl.FFont,0xff);
      pTVar2 = (Form1->Memo1->super_TCustomMemo).FLines;
      p_Var3 = (pTVar2->super_TPersistent).super_TObject._vptr_TObject[0xf];
      local_668 = 0;
      _ZN6System13UnicodeStringC1EPKc(&local_668,s_Failure_006e0579);
      (*p_Var3)(pTVar2,local_668);
      _ZN6System13UnicodeStringD1Ev(&local_668);
      if (DisableUpdateLogFile == 0) {
        SaveShfuLog();
      }
      ReturnValue = '\x10';
      if (FailClose != 0) {
        _ZN3Vcl5Forms11TCustomForm5CloseEv(Form1);
      }
    }
    else {
      if (MessageEnable == 0) {
        _ZN3Vcl8Controls8TControl10SetVisibleEb(Form1->Image3,0);
      }
      if (MessageEnable == 0) {
        _ZN3Vcl8Controls8TControl10SetVisibleEb(Form1->Image4,1);
      }
      _ZN3Vcl8Graphics5TFont8SetColorEN6System7Uitypes6TColorE
                ((Form1->Memo1->super_TCustomMemo).super_TCustomEdit.super_TWinControl.
                 super_TControl.FFont,0x8000);
      if (Update_OnlyParameter == 0) {
        System::AnsiStringT<0>::printf(&stPrint,s_New_OEM_Version___s_006e04f0);
        pTVar2 = (Form1->Memo1->super_TCustomMemo).FLines;
        p_Var3 = (pTVar2->super_TPersistent).super_TObject._vptr_TObject[0xf];
        local_600 = 0;
        _ZN6System8Internal7Strhlpr15UnicodeFromAnsiERNS_13UnicodeStringERNS_11AnsiStringTILt65535EEE
                  (&local_600,&stPrint);
        (*p_Var3)(pTVar2,local_600);
        _ZN6System13UnicodeStringD1Ev(&local_600);
        System::AnsiStringT<0>::printf(&stPrint,s_Old_OEM_Version___s_006e0505);
        if (Chicony_BootMode == 1) {
          pTVar2 = (Form1->Memo1->super_TCustomMemo).FLines;
          p_Var3 = (pTVar2->super_TPersistent).super_TObject._vptr_TObject[0xf];
          local_608 = 0;
          _ZN6System13UnicodeStringC1EPKc(&local_608,s_Old_OEM_Version__006e051a);
          (*p_Var3)(pTVar2,local_608);
          _ZN6System13UnicodeStringD1Ev(&local_608);
        }
        else {
          pTVar2 = (Form1->Memo1->super_TCustomMemo).FLines;
          p_Var3 = (pTVar2->super_TPersistent).super_TObject._vptr_TObject[0xf];
          local_610 = 0;
          _ZN6System8Internal7Strhlpr15UnicodeFromAnsiERNS_13UnicodeStringERNS_11AnsiStringTILt65535EEE
                    (&local_610,&stPrint);
          (*p_Var3)(pTVar2,local_610);
          _ZN6System13UnicodeStringD1Ev(&local_610);
        }
        if (oemver_src[0] == '\0') {
          local_618.super_AnsiStringBase.Data = (AnsiStringBase)(char *)0x0;
          _ZN6System14AnsiStringBaseC2EPKci(&local_618,&DAT_006e0293,0);
          _ZN6System14AnsiStringBaseaSERKS0_(&stPrint,&local_618);
          System::AnsiStringT<0>::~AnsiStringT(&local_618);
        }
        else {
          System::AnsiStringT<0>::printf(&stPrint,&DAT_006e052c);
        }
        local_620.Data = (WideChar *)0x0;
        _ZN6System8Internal7Strhlpr15UnicodeFromAnsiERNS_13UnicodeStringERNS_11AnsiStringTILt65535EEE
                  (&local_620,&stPrint);
        WriteFWVersionToRegistry(local_620);
        _ZN6System13UnicodeStringD1Ev(&local_620);
      }
      pTVar2 = (Form1->Memo1->super_TCustomMemo).FLines;
      p_Var3 = (pTVar2->super_TPersistent).super_TObject._vptr_TObject[0xf];
      local_628 = 0;
      _ZN6System13UnicodeStringC1EPKc(&local_628,s_Success_006e052f);
      (*p_Var3)(pTVar2,local_628);
      _ZN6System13UnicodeStringD1Ev(&local_628);
      if (DisableUpdateLogFile == 0) {
        SaveShfuLog();
      }
      (**(code **)((longlong)
                   (Form1->Memo1->super_TCustomMemo).super_TCustomEdit.super_TWinControl.
                   super_TControl.super_TComponent.super_TPersistent.super_TObject + 0x280))
                (Form1->Memo1);
      pTVar2 = (Form1->Memo1->super_TCustomMemo).FLines;
      p_Var3 = (pTVar2->super_TPersistent).super_TObject._vptr_TObject[0xf];
      local_630 = 0;
      _ZN6System13UnicodeStringC1EPKc(&local_630,s_Instructions__006e0537);
      (*p_Var3)(pTVar2,local_630);
      _ZN6System13UnicodeStringD1Ev(&local_630);
      pTVar2 = (Form1->Memo1->super_TCustomMemo).FLines;
      p_Var3 = (pTVar2->super_TPersistent).super_TObject._vptr_TObject[0xf];
      local_638 = 0;
      _ZN6System13UnicodeStringC1EPKc(&local_638,s_Waiting_a_few_seconds____006e0545);
      (*p_Var3)(pTVar2,local_638);
      _ZN6System13UnicodeStringD1Ev(&local_638);
      uVar12 = DelayMSec / 2;
      DVar10 = GetTickCount();
      while (DVar11 = GetTickCount(), DVar11 - DVar10 <= uVar12) {
        _ZN3Vcl5Forms12TApplication15ProcessMessagesEv
                  (*(undefined8 *)__indStub__ZN3Vcl5Forms11ApplicationE);
      }
      ReturnValue = '\0';
      if (PassClose != 0) {
        _ZN3Vcl5Forms11TCustomForm5CloseEv(Form1);
      }
      if (Update_OnlyParameter == 0) {
        memset(&OEMVERData,0,8);
        memset(&OEMVERData,0,8);
        OEMVERData.super_AnsiStringBase.Data = (AnsiStringBase)(char *)0x0;
        if (oemver_src[0] == '\0') {
          local_648.super_AnsiStringBase.Data = (AnsiStringBase)(char *)0x0;
          _ZN6System14AnsiStringBaseC2EPKci(&local_648,&DAT_006e0293,0);
          _ZN6System14AnsiStringBaseaSERKS0_(&OEMVERData,&local_648);
          System::AnsiStringT<0>::~AnsiStringT(&local_648);
        }
        else {
          System::AnsiStringT<0>::printf(&OEMVERData,&DAT_006e052c);
        }
        local_650.super_AnsiStringBase.Data = (AnsiStringBase)(char *)0x0;
        _ZN6System14AnsiStringBaseC2EPKci(&local_650,&DAT_006e0293,0);
        bVar6 = _ZNK6System14AnsiStringBaseneERKS0_(&OEMVERData,&local_650);
        System::AnsiStringT<0>::~AnsiStringT(&local_650);
        if ((bVar6 & 1) != 0) {
          pTVar4 = Form1->Label2;
          memset(&local_658,0,8);
          memset(&local_658,0,8);
          local_658.super_AnsiStringBase.Data = (AnsiStringBase)(char *)0x0;
          System::operator+<0>
                    ((System *)&local_658,s_Current_firmware_version__006e055e,&OEMVERData);
          local_660 = 0;
          _ZN6System8Internal7Strhlpr15UnicodeFromAnsiERNS_13UnicodeStringERNS_11AnsiStringTILt65535EEE
                    (&local_660,&local_658);
          _ZN3Vcl8Controls8TControl7SetTextEN6System13UnicodeStringE(pTVar4,local_660);
          _ZN6System13UnicodeStringD1Ev(&local_660);
          System::AnsiStringT<0>::~AnsiStringT(&local_658);
        }
        System::AnsiStringT<0>::~AnsiStringT(&OEMVERData);
      }
    }
  }
  local_4fc = 0;
LAB_0040ebc0:
  this_00 = &stPrint;
  System::AnsiStringT<0>::~AnsiStringT(this_00);
  if (local_4fc < 2) {
    return;
  }
  if (SBORROW4(local_4fc,1)) {
    System::AnsiStringT<0>::~AnsiStringT(this);
                    /* WARNING: Subroutine does not return */
    _Unwind_Resume(local_4e8);
  }
  cVar1 = *(char *)&(this->super_AnsiStringBase).Data;
  pcVar15 = (char *)CONCAT71((int7)((ulonglong)this >> 8),cVar1);
  *pcVar15 = *pcVar15 + cVar1;
  *pcVar15 = *pcVar15 + cVar1;
  cStack_c69 = (char)this_00;
  if (cStack_c69 == '\x01') {
    pTVar2 = (Form1->Memo2->super_TCustomMemo).FLines;
    p_Var3 = (pTVar2->super_TPersistent).super_TObject._vptr_TObject[0xf];
    memset(&uStack_c80,0,8);
    uStack_c80 = 0;
    puStack_c68 = &uStack_c80;
    _ZN6System8Sysutils8IntToHexEii(&uStack_c80,1,2);
    memset(&uStack_c78,0,8);
    uStack_c78 = 0;
    puStack_c60 = &uStack_c78;
    _ZN6SystemplEPKcRKNS_13UnicodeStringE(&uStack_c78,s_ConnectMode__0x_006e0606,&uStack_c80);
    (*p_Var3)(pTVar2,uStack_c78);
    _ZN6System13UnicodeStringD1Ev(&uStack_c78);
    _ZN6System13UnicodeStringD1Ev(&uStack_c80);
    Sleep(100);
    for (iStack_c90 = 0; iStack_c90 < 0x100; iStack_c90 = iStack_c90 + 1) {
      if (hFile[iStack_c90] != (HANDLE)0x0) {
        CloseHandle(hFile[iStack_c90]);
        hFile[iStack_c90] = (HANDLE)0x0;
      }
    }
    UVar16 = (USAGE)MainDevice_UPID;
    UVar17 = (USAGE)MainDevice_UID;
    memset(&AStack_c98,0,8);
    pSStack_c58 = &MainHWid;
    if (MainHWid.Data == (WideChar *)0x0) {
      iStack_d44 = 0;
    }
    else {
      pSStack_c48 = &MainHWid;
      pWStack_c40 = MainHWid.Data + -8;
      iStack_d44 = *(int *)(MainHWid.Data + -2);
    }
    iStack_c4c = iStack_d44;
    uStack_ca0 = 0;
    pSStack_c28 = &MainHWid;
    iStack_c2c = iStack_d44 + -3;
    uStack_c30 = 4;
    puStack_c38 = &uStack_ca0;
    _ZNK6System13UnicodeString10SubString1Eii(&MainHWid,&uStack_ca0,iStack_c2c,4);
    pAStack_c18 = &AStack_c98;
    AStack_c98.Data = (char *)0x0;
    puStack_c20 = &uStack_ca0;
    _ZN6System14AnsiStringBaseC2ERKNS_13UnicodeStringEi(pAStack_c18,&uStack_ca0,0);
    ConnectHIDDevice('\x01',UVar16,UVar17,(AnsiString)AStack_c98.Data);
    pAStack_c10 = &AStack_c98;
    System::AnsiStringT<0>::~AnsiStringT((AnsiStringT<0> *)pAStack_c10);
    _ZN6System13UnicodeStringD1Ev(&uStack_ca0);
    if (SensorCunt == '\0') {
      cStack_c69 = '\x02';
    }
    else {
      bVar7 = HidCustomCmdInit('\x01');
      if ((!bVar7) && (ITEReportID != 'Z')) {
        ITEReportID = 'Z';
        HidCustomCmdInit('\x01');
      }
      iVar8 = (**(msUpdateBINBuffer->super_TCustomMemoryStream).super_TStream.super_TObject.
                 _vptr_TObject)(msUpdateBINBuffer);
      if (CONCAT44(extraout_var_00,iVar8) == (longlong)(Update_FileSizeKB << 10)) {
        (**(code **)((longlong)
                     (Form1->Button2->super_TCustomButton).super_TButtonControl.super_TWinControl.
                     super_TControl.super_TComponent.super_TPersistent.super_TObject + 0x120))
                  (Form1->Button2,1);
        (**(code **)((longlong)
                     (Form1->Button3->super_TCustomButton).super_TButtonControl.super_TWinControl.
                     super_TControl.super_TComponent.super_TPersistent.super_TObject + 0x120))
                  (Form1->Button3,0);
        (**(code **)((longlong)
                     (Form1->Button4->super_TCustomButton).super_TButtonControl.super_TWinControl.
                     super_TControl.super_TComponent.super_TPersistent.super_TObject + 0x120))
                  (Form1->Button4,0);
        _ZN3Vcl8Controls8TControl6SetTopEi(Form1->GroupBox4,0x1e0);
      }
      else {
        pTVar2 = (Form1->Memo2->super_TCustomMemo).FLines;
        p_Var3 = (pTVar2->super_TPersistent).super_TObject._vptr_TObject[0xf];
        uStack_ca8 = 0;
        _ZN6System13UnicodeStringC1EPKc(&uStack_ca8,s_Bin_file_size_is_not_match___006e0616);
        (*p_Var3)(pTVar2,uStack_ca8);
        _ZN6System13UnicodeStringD1Ev(&uStack_ca8);
      }
      MainBootMode = 1;
    }
  }
  if (cStack_c69 == '\x02') {
    pTVar2 = (Form1->Memo2->super_TCustomMemo).FLines;
    p_Var3 = (pTVar2->super_TPersistent).super_TObject._vptr_TObject[0xf];
    memset(&uStack_cb8,0,8);
    uStack_cb8 = 0;
    puStack_c00 = &uStack_cb8;
    _ZN6System8Sysutils8IntToHexEii(&uStack_cb8,2,2);
    memset(&uStack_cb0,0,8);
    uStack_cb0 = 0;
    puStack_be0 = &uStack_cb0;
    _ZN6SystemplEPKcRKNS_13UnicodeStringE(&uStack_cb0,s_ConnectMode__0x_006e0606,&uStack_cb8);
    (*p_Var3)(pTVar2,uStack_cb0);
    _ZN6System13UnicodeStringD1Ev(&uStack_cb0);
    _ZN6System13UnicodeStringD1Ev(&uStack_cb8);
    Sleep(100);
    for (iStack_cbc = 0; iStack_cbc < 0x100; iStack_cbc = iStack_cbc + 1) {
      if (hFile[iStack_cbc] != (HANDLE)0x0) {
        CloseHandle(hFile[iStack_cbc]);
        hFile[iStack_cbc] = (HANDLE)0x0;
      }
    }
    UVar16 = (USAGE)BootDevice_UPID;
    UVar17 = (USAGE)BootDevice_UID;
    memset(&AStack_cc8,0,8);
    pSStack_bd8 = &MainHWid;
    if (MainHWid.Data == (WideChar *)0x0) {
      iStack_df4 = 0;
    }
    else {
      pSStack_bc8 = &MainHWid;
      pWStack_bc0 = MainHWid.Data + -8;
      iStack_df4 = *(int *)(MainHWid.Data + -2);
    }
    iStack_bcc = iStack_df4;
    uStack_cd0 = 0;
    pSStack_ba0 = &BootHWid;
    iStack_ba4 = iStack_df4 + -3;
    uStack_ba8 = 4;
    puStack_bb8 = &uStack_cd0;
    _ZNK6System13UnicodeString10SubString1Eii(&BootHWid,&uStack_cd0,iStack_ba4,4);
    pAStack_b90 = &AStack_cc8;
    AStack_cc8.Data = (char *)0x0;
    puStack_b98 = &uStack_cd0;
    _ZN6System14AnsiStringBaseC2ERKNS_13UnicodeStringEi(pAStack_b90,&uStack_cd0,0);
    ConnectHIDDevice('\x02',UVar16,UVar17,(AnsiString)AStack_cc8.Data);
    pAStack_bb0 = &AStack_cc8;
    System::AnsiStringT<0>::~AnsiStringT((AnsiStringT<0> *)pAStack_bb0);
    _ZN6System13UnicodeStringD1Ev(&uStack_cd0);
    if (SensorCunt != '\0') {
      (**(code **)((longlong)
                   (Form1->Button2->super_TCustomButton).super_TButtonControl.super_TWinControl.
                   super_TControl.super_TComponent.super_TPersistent.super_TObject + 0x120))
                (Form1->Button2,0);
      (**(code **)((longlong)
                   (Form1->Button3->super_TCustomButton).super_TButtonControl.super_TWinControl.
                   super_TControl.super_TComponent.super_TPersistent.super_TObject + 0x120))
                (Form1->Button3,1);
      MainBootMode = 2;
    }
  }
  cVar1 = cStack_c69;
  if (((cStack_c69 == -0x80) || (cStack_c69 == '\0')) || (SensorCunt == '\0')) {
    pTVar2 = (Form1->Memo2->super_TCustomMemo).FLines;
    p_Var3 = (pTVar2->super_TPersistent).super_TObject._vptr_TObject[0xf];
    memset(&uStack_ce0,0,8);
    uStack_ce0 = 0;
    puStack_bf0 = &uStack_ce0;
    _ZN6System8Sysutils8IntToHexEii(&uStack_ce0,cVar1,2);
    memset(&uStack_cd8,0,8);
    uStack_cd8 = 0;
    puStack_bf8 = &uStack_cd8;
    _ZN6SystemplEPKcRKNS_13UnicodeStringE(&uStack_cd8,s_ConnectMode__0x_006e0606,&uStack_ce0);
    (*p_Var3)(pTVar2,uStack_cd8);
    _ZN6System13UnicodeStringD1Ev(&uStack_cd8);
    _ZN6System13UnicodeStringD1Ev(&uStack_ce0);
    if (cStack_c69 == '\0') {
      HidCustomCmdInit('\0');
    }
    SensorCunt = '\0';
    MainBootMode = 0;
    for (iStack_ce4 = 0; iStack_ce4 < 0x100; iStack_ce4 = iStack_ce4 + 1) {
      if (hFile[iStack_ce4] != (HANDLE)0x0) {
        CloseHandle(hFile[iStack_ce4]);
        hFile[iStack_ce4] = (HANDLE)0x0;
      }
    }
    (**(code **)((longlong)
                 (Form1->Button2->super_TCustomButton).super_TButtonControl.super_TWinControl.
                 super_TControl.super_TComponent.super_TPersistent.super_TObject + 0x120))
              (Form1->Button2,0);
    (**(code **)((longlong)
                 (Form1->Button3->super_TCustomButton).super_TButtonControl.super_TWinControl.
                 super_TControl.super_TComponent.super_TPersistent.super_TObject + 0x120))
              (Form1->Button3,0);
  }
  return;
}

