
void ConnectHIDDevice(uchar Mode,USAGE MyUsagePage,USAGE MyUsage,AnsiString sPID)

{
  TStrings *pTVar1;
  _func_int *p_Var2;
  UCHAR UVar3;
  uchar uVar4;
  int iVar5;
  bool bVar6;
  BOOLEAN BVar7;
  HANDLE pvVar8;
  undefined8 local_220;
  undefined8 local_218;
  undefined8 local_210;
  undefined8 local_208;
  undefined8 local_200;
  undefined8 local_1f8;
  undefined8 local_1f0;
  undefined8 local_1e8;
  undefined8 local_1e0;
  undefined8 local_1d8;
  undefined8 local_1d0;
  undefined8 local_1c8;
  undefined8 local_1c0;
  undefined8 local_1b8;
  undefined8 local_1b0;
  undefined8 local_1a8;
  undefined8 local_1a0;
  undefined8 local_198;
  undefined8 local_190;
  undefined8 local_188;
  undefined8 local_180;
  undefined8 local_178;
  uchar BootChipID [2];
  undefined8 local_168;
  undefined8 local_160;
  undefined8 local_158;
  undefined8 local_150;
  undefined8 local_148;
  int i;
  AnsiString Path;
  AnsiString sPID_local;
  USAGE MyUsage_local;
  USAGE MyUsagePage_local;
  uchar Mode_local;
  LPCSTR local_e8;
  
  sPID_local = sPID;
  _ZN6System14AnsiStringBaseC2ERKS0_(&sPID_local,&sPID_local);
  memset(&Path,0,8);
  memset(&Path,0,8);
  Path.super_AnsiStringBase.Data = (AnsiStringBase)(char *)0x0;
  SensorCunt = '\0';
  i = 0;
  do {
    UVar3 = SensorCunt;
    if (MaxScanDevice <= i) {
      pTVar1 = (Form1->Memo2->super_TCustomMemo).FLines;
      p_Var2 = (pTVar1->super_TPersistent).super_TObject._vptr_TObject[0xf];
      memset(&local_218,0,8);
      local_218 = 0;
      _ZN6System8Sysutils8IntToStrEi(&local_218,UVar3);
      memset(&local_210,0,8);
      local_210 = 0;
      _ZN6SystemplEPKcRKNS_13UnicodeStringE(&local_210,s_Find_006e034d,&local_218);
      local_220 = 0;
      _ZN6System13UnicodeStringC1EPKc(&local_220,s_ITE_HID_Device__006e0353);
      memset(&local_208,0,8);
      local_208 = 0;
      _ZNK6System13UnicodeStringplERKS0_(&local_210,&local_208,&local_220);
      (*p_Var2)(pTVar1,local_208);
      _ZN6System13UnicodeStringD1Ev(&local_208);
      _ZN6System13UnicodeStringD1Ev(&local_220);
      _ZN6System13UnicodeStringD1Ev(&local_210);
      _ZN6System13UnicodeStringD1Ev(&local_218);
      System::AnsiStringT<0>::~AnsiStringT(&Path);
      System::AnsiStringT<0>::~AnsiStringT(&sPID_local);
      return;
    }
    bVar6 = GetHIDDevicePath(i,&Path);
    if (bVar6) {
      if (Path.super_AnsiStringBase.Data == (char *)0x0) {
        local_e8 = &DAT_006e0293;
      }
      else {
        local_e8 = (LPCSTR)Path.super_AnsiStringBase.Data;
      }
      pvVar8 = CreateFileA(local_e8,0,3,(LPSECURITY_ATTRIBUTES)0x0,3,0,(HANDLE)0x0);
      iVar5 = i;
      hFile[SensorCunt] = pvVar8;
      if (hFile[SensorCunt] != (HANDLE)0x0) {
        pTVar1 = (Form1->Memo2->super_TCustomMemo).FLines;
        p_Var2 = (pTVar1->super_TPersistent).super_TObject._vptr_TObject[0xf];
        memset(&local_158,0,8);
        local_158 = 0;
        _ZN6System8Sysutils8IntToStrEi(&local_158,iVar5);
        local_160 = 0;
        _ZN6System13UnicodeStringC1EPKc(&local_160,&DAT_006e0329);
        memset(&local_150,0,8);
        local_150 = 0;
        _ZNK6System13UnicodeStringplERKS0_(&local_158,&local_150,&local_160);
        local_168 = 0;
        _ZN6System8Internal7Strhlpr15UnicodeFromAnsiERNS_13UnicodeStringERNS_11AnsiStringTILt65535EEE
                  (&local_168,&Path);
        memset(&local_148,0,8);
        local_148 = 0;
        _ZNK6System13UnicodeStringplERKS0_(&local_150,&local_148,&local_168);
        (*p_Var2)(pTVar1,local_148);
        _ZN6System13UnicodeStringD1Ev(&local_148);
        _ZN6System13UnicodeStringD1Ev(&local_168);
        _ZN6System13UnicodeStringD1Ev(&local_150);
        _ZN6System13UnicodeStringD1Ev(&local_160);
        _ZN6System13UnicodeStringD1Ev(&local_158);
        BVar7 = CheckIfOurDevice(hFile[SensorCunt],MyUsagePage,MyUsage,sPID_local);
        if (BVar7 == '\0') {
          CloseHandle(hFile[SensorCunt]);
          hFile[SensorCunt] = (HANDLE)0x0;
        }
        else {
          if ((Mode == '\x02') && (BootDevice_ChipID != 0)) {
            WinDebugReadRegByteForBootcode(0xf0,0x20,0,BootChipID);
            WinDebugReadRegByteForBootcode(0xf0,0x20,1,BootChipID + 1);
            uVar4 = BootChipID[0];
            if (((uint)BootChipID[0] == (int)(BootDevice_ChipID & 0xff00U) >> 8) &&
               ((uint)BootChipID[1] == (BootDevice_ChipID & 0xffU))) {
              pTVar1 = (Form1->Memo2->super_TCustomMemo).FLines;
              p_Var2 = (pTVar1->super_TPersistent).super_TObject._vptr_TObject[0xf];
              memset(&local_190,0,8);
              local_190 = 0;
              _ZN6System8Sysutils8IntToHexEii(&local_190,uVar4,2);
              memset(&local_188,0,8);
              local_188 = 0;
              _ZN6SystemplEPKcRKNS_13UnicodeStringE(&local_188,s_ChipID__006e032d,&local_190);
              uVar4 = BootChipID[1];
              memset(&local_198,0,8);
              local_198 = 0;
              _ZN6System8Sysutils8IntToHexEii(&local_198,uVar4,2);
              memset(&local_180,0,8);
              local_180 = 0;
              _ZNK6System13UnicodeStringplERKS0_(&local_188,&local_180,&local_198);
              local_1a0 = 0;
              _ZN6System13UnicodeStringC1EPKc(&local_1a0,s_is_match_006e0335);
              memset(&local_178,0,8);
              local_178 = 0;
              _ZNK6System13UnicodeStringplERKS0_(&local_180,&local_178,&local_1a0);
              (*p_Var2)(pTVar1,local_178);
              _ZN6System13UnicodeStringD1Ev(&local_178);
              _ZN6System13UnicodeStringD1Ev(&local_1a0);
              _ZN6System13UnicodeStringD1Ev(&local_180);
              _ZN6System13UnicodeStringD1Ev(&local_198);
              _ZN6System13UnicodeStringD1Ev(&local_188);
              _ZN6System13UnicodeStringD1Ev(&local_190);
            }
            else {
              if ((BootDevice_ChipID != 0x8171) && (BootDevice_ChipID != 0x8176)) {
                pTVar1 = (Form1->Memo2->super_TCustomMemo).FLines;
                p_Var2 = (pTVar1->super_TPersistent).super_TObject._vptr_TObject[0xf];
                memset(&local_1f0,0,8);
                local_1f0 = 0;
                _ZN6System8Sysutils8IntToHexEii(&local_1f0,uVar4,2);
                memset(&local_1e8,0,8);
                local_1e8 = 0;
                _ZN6SystemplEPKcRKNS_13UnicodeStringE(&local_1e8,s_ChipID__006e032d,&local_1f0);
                uVar4 = BootChipID[1];
                memset(&local_1f8,0,8);
                local_1f8 = 0;
                _ZN6System8Sysutils8IntToHexEii(&local_1f8,uVar4,2);
                memset(&local_1e0,0,8);
                local_1e0 = 0;
                _ZNK6System13UnicodeStringplERKS0_(&local_1e8,&local_1e0,&local_1f8);
                local_200 = 0;
                _ZN6System13UnicodeStringC1EPKc(&local_200,s_is_not_match_006e033f);
                memset(&local_1d8,0,8);
                local_1d8 = 0;
                _ZNK6System13UnicodeStringplERKS0_(&local_1e0,&local_1d8,&local_200);
                (*p_Var2)(pTVar1,local_1d8);
                _ZN6System13UnicodeStringD1Ev(&local_1d8);
                _ZN6System13UnicodeStringD1Ev(&local_200);
                _ZN6System13UnicodeStringD1Ev(&local_1e0);
                _ZN6System13UnicodeStringD1Ev(&local_1f8);
                _ZN6System13UnicodeStringD1Ev(&local_1e8);
                _ZN6System13UnicodeStringD1Ev(&local_1f0);
                CloseHandle(hFile[SensorCunt]);
                hFile[SensorCunt] = (HANDLE)0x0;
                goto LAB_00409a05;
              }
              if ((BootChipID[0] == 0x81) && ((BootChipID[1] == 'q' || (BootChipID[1] == 'v')))) {
                pTVar1 = (Form1->Memo2->super_TCustomMemo).FLines;
                p_Var2 = (pTVar1->super_TPersistent).super_TObject._vptr_TObject[0xf];
                memset(&local_1c0,0,8);
                local_1c0 = 0;
                _ZN6System8Sysutils8IntToHexEii(&local_1c0,0x81,2);
                memset(&local_1b8,0,8);
                local_1b8 = 0;
                _ZN6SystemplEPKcRKNS_13UnicodeStringE(&local_1b8,s_ChipID__006e032d,&local_1c0);
                uVar4 = BootChipID[1];
                memset(&local_1c8,0,8);
                local_1c8 = 0;
                _ZN6System8Sysutils8IntToHexEii(&local_1c8,uVar4,2);
                memset(&local_1b0,0,8);
                local_1b0 = 0;
                _ZNK6System13UnicodeStringplERKS0_(&local_1b8,&local_1b0,&local_1c8);
                local_1d0 = 0;
                _ZN6System13UnicodeStringC1EPKc(&local_1d0,s_is_match_006e0335);
                memset(&local_1a8,0,8);
                local_1a8 = 0;
                _ZNK6System13UnicodeStringplERKS0_(&local_1b0,&local_1a8,&local_1d0);
                (*p_Var2)(pTVar1,local_1a8);
                _ZN6System13UnicodeStringD1Ev(&local_1a8);
                _ZN6System13UnicodeStringD1Ev(&local_1d0);
                _ZN6System13UnicodeStringD1Ev(&local_1b0);
                _ZN6System13UnicodeStringD1Ev(&local_1c8);
                _ZN6System13UnicodeStringD1Ev(&local_1b8);
                _ZN6System13UnicodeStringD1Ev(&local_1c0);
              }
            }
          }
          SensorCunt = SensorCunt + '\x01';
        }
      }
    }
LAB_00409a05:
    i = i + 1;
  } while( true );
}

