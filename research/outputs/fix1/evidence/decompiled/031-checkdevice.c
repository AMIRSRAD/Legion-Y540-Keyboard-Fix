
BOOLEAN CheckIfOurDevice(HANDLE file,USAGE MyUsagePage,USAGE MyUsage,AnsiString sPID)

{
  TStrings *pTVar1;
  _func_int *p_Var2;
  USHORT UVar3;
  char cVar4;
  int iVar5;
  uint uVar6;
  undefined8 local_1d0;
  undefined8 local_1c8;
  AnsiStringT<0> local_1c0;
  undefined8 local_1b8;
  undefined8 local_1b0;
  undefined8 local_1a8;
  undefined8 local_1a0;
  undefined8 local_198;
  undefined8 local_190;
  undefined8 local_188;
  undefined8 local_180;
  undefined8 local_178;
  undefined8 local_170;
  undefined8 local_168;
  undefined8 local_160;
  undefined8 local_158;
  undefined8 local_150;
  undefined8 local_148;
  undefined8 local_140;
  undefined4 local_138;
  HIDD_ATTRIBUTES Attributes;
  BOOLEAN Result;
  HIDP_CAPS Caps;
  PHIDP_PREPARSED_DATA Ppd;
  AnsiString sPID_local;
  USAGE MyUsage_local;
  USAGE MyUsagePage_local;
  HANDLE file_local;
  BOOLEAN local_b1;
  
  sPID_local = sPID;
  _ZN6System14AnsiStringBaseC2ERKS0_(&sPID_local,&sPID_local);
  cVar4 = HidD_GetPreparsedData(file,&Ppd);
  if (cVar4 == '\0') {
    local_b1 = '\0';
  }
  else {
    iVar5 = HidP_GetCaps(Ppd,&Caps);
    if (iVar5 == 0) {
      HidD_FreePreparsedData(Ppd);
      local_b1 = '\0';
    }
    else {
      if ((Caps.UsagePage == MyUsagePage) && (Caps.Usage == MyUsage)) {
        pTVar1 = (Form1->Memo2->super_TCustomMemo).FLines;
        p_Var2 = (pTVar1->super_TPersistent).super_TObject._vptr_TObject[0xf];
        memset(&local_150,0,8);
        local_150 = 0;
        _ZN6System8Sysutils8IntToHexEii(&local_150,Caps.UsagePage,4);
        local_158 = 0;
        _ZN6System13UnicodeStringC1EPKc(&local_158,&DAT_006e02c2);
        memset(&local_148,0,8);
        local_148 = 0;
        _ZNK6System13UnicodeStringplERKS0_(&local_150,&local_148,&local_158);
        memset(&local_160,0,8);
        local_160 = 0;
        _ZN6System8Sysutils8IntToHexEii(&local_160,Caps.Usage,4);
        memset(&local_140,0,8);
        local_140 = 0;
        _ZNK6System13UnicodeStringplERKS0_(&local_148,&local_140,&local_160);
        (*p_Var2)(pTVar1,local_140);
        _ZN6System13UnicodeStringD1Ev(&local_140);
        _ZN6System13UnicodeStringD1Ev(&local_160);
        _ZN6System13UnicodeStringD1Ev(&local_148);
        _ZN6System13UnicodeStringD1Ev(&local_158);
        _ZN6System13UnicodeStringD1Ev(&local_150);
        cVar4 = HidD_GetAttributes(file,&Attributes);
        if (cVar4 != '\0') {
          pTVar1 = (Form1->Memo2->super_TCustomMemo).FLines;
          p_Var2 = (pTVar1->super_TPersistent).super_TObject._vptr_TObject[0xf];
          memset(&local_188,0,8);
          local_188 = 0;
          _ZN6System8Sysutils8IntToHexEii(&local_188,Attributes.VendorID,4);
          local_190 = 0;
          _ZN6System13UnicodeStringC1EPKc(&local_190,&DAT_006e02c2);
          memset(&local_180,0,8);
          local_180 = 0;
          _ZNK6System13UnicodeStringplERKS0_(&local_188,&local_180,&local_190);
          UVar3 = Attributes.ProductID;
          memset(&local_198,0,8);
          local_198 = 0;
          _ZN6System8Sysutils8IntToHexEii(&local_198,UVar3,4);
          memset(&local_178,0,8);
          local_178 = 0;
          _ZNK6System13UnicodeStringplERKS0_(&local_180,&local_178,&local_198);
          local_1a0 = 0;
          _ZN6System13UnicodeStringC1EPKc(&local_1a0,&DAT_006e02c2);
          memset(&local_170,0,8);
          local_170 = 0;
          _ZNK6System13UnicodeStringplERKS0_(&local_178,&local_170,&local_1a0);
          memset(&local_1a8,0,8);
          local_1a8 = 0;
          _ZN6System8Sysutils8IntToHexEii(&local_1a8,Attributes.VersionNumber,4);
          memset(&local_168,0,8);
          local_168 = 0;
          _ZNK6System13UnicodeStringplERKS0_(&local_170,&local_168,&local_1a8);
          (*p_Var2)(pTVar1,local_168);
          _ZN6System13UnicodeStringD1Ev(&local_168);
          _ZN6System13UnicodeStringD1Ev(&local_1a8);
          _ZN6System13UnicodeStringD1Ev(&local_170);
          _ZN6System13UnicodeStringD1Ev(&local_1a0);
          _ZN6System13UnicodeStringD1Ev(&local_178);
          _ZN6System13UnicodeStringD1Ev(&local_198);
          _ZN6System13UnicodeStringD1Ev(&local_180);
          _ZN6System13UnicodeStringD1Ev(&local_190);
          _ZN6System13UnicodeStringD1Ev(&local_188);
        }
        if (NoCheckPID != 0) {
          pTVar1 = (Form1->Memo2->super_TCustomMemo).FLines;
          p_Var2 = (pTVar1->super_TPersistent).super_TObject._vptr_TObject[0xf];
          local_1b0 = 0;
          _ZN6System13UnicodeStringC1EPKc(&local_1b0,s_Found_the_device_without_PID_006e02c6);
          (*p_Var2)(pTVar1,local_1b0);
          _ZN6System13UnicodeStringD1Ev(&local_1b0);
          local_b1 = '\x01';
          goto LAB_0040897f;
        }
        memset(&local_1b8,0,8);
        memset(&local_1c0,0,8);
        memset(&local_1c0,0,8);
        local_1c0.super_AnsiStringBase.Data = (AnsiStringBase)(char *)0x0;
        System::operator+<0>((System *)&local_1c0,&DAT_006e02e3,&sPID_local);
        local_1b8 = 0;
        _ZN6System8Internal7Strhlpr15UnicodeFromAnsiERNS_13UnicodeStringERNS_11AnsiStringTILt65535EEE
                  (&local_1b8,&local_1c0);
        uVar6 = _ZN6System8Sysutils8StrToIntENS_13UnicodeStringE(local_1b8);
        _ZN6System13UnicodeStringD1Ev(&local_1b8);
        System::AnsiStringT<0>::~AnsiStringT(&local_1c0);
        if (uVar6 == Attributes.ProductID) {
          pTVar1 = (Form1->Memo2->super_TCustomMemo).FLines;
          p_Var2 = (pTVar1->super_TPersistent).super_TObject._vptr_TObject[0xf];
          local_1c8 = 0;
          _ZN6System13UnicodeStringC1EPKc(&local_1c8,s_Found_the_device_with_PID_006e02e6);
          (*p_Var2)(pTVar1,local_1c8);
          _ZN6System13UnicodeStringD1Ev(&local_1c8);
          local_b1 = '\x01';
          goto LAB_0040897f;
        }
        pTVar1 = (Form1->Memo2->super_TCustomMemo).FLines;
        p_Var2 = (pTVar1->super_TPersistent).super_TObject._vptr_TObject[0xf];
        local_1d0 = 0;
        _ZN6System13UnicodeStringC1EPKc(&local_1d0,s_Error__Can_not_Find_the_device_w_006e0300);
        (*p_Var2)(pTVar1,local_1d0);
        _ZN6System13UnicodeStringD1Ev(&local_1d0);
      }
      local_b1 = '\0';
    }
  }
LAB_0040897f:
  local_138 = 1;
  System::AnsiStringT<0>::~AnsiStringT(&sPID_local);
  return local_b1;
}

