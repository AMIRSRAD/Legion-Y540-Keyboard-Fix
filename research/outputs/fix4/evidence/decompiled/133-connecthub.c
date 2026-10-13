
/* WARNING: Type propagation algorithm not settling */

void ConnectHub(UCHAR mode)

{
  TStrings *pTVar1;
  _func_int *p_Var2;
  UCHAR UVar3;
  bool bVar4;
  int iVar5;
  undefined4 extraout_var;
  USAGE UVar6;
  USAGE UVar7;
  int local_27c;
  int local_1cc;
  int i_2;
  undefined8 local_168;
  undefined8 local_160;
  undefined8 local_158;
  AnsiStringBase local_150;
  int i_1;
  undefined8 local_140;
  undefined8 local_138;
  undefined8 local_130;
  undefined8 local_128;
  AnsiStringBase local_120;
  int i;
  undefined8 local_108;
  undefined8 local_100;
  UCHAR mode_local;
  undefined8 *local_f0;
  undefined8 *local_e8;
  String *local_e0;
  int local_d4;
  String *local_d0;
  WideChar *local_c8;
  undefined8 *local_c0;
  undefined4 local_b8;
  int local_b4;
  String *local_b0;
  undefined8 *local_a8;
  AnsiStringBase *local_a0;
  AnsiStringBase *local_98;
  undefined8 *local_88;
  undefined8 *local_80;
  undefined8 *local_78;
  undefined8 *local_68;
  String *local_60;
  int local_54;
  String *local_50;
  WideChar *local_48;
  undefined8 *local_40;
  AnsiStringBase *local_38;
  undefined4 local_30;
  int local_2c;
  String *local_28;
  undefined8 *local_20;
  AnsiStringBase *local_18;
  
  mode_local = mode;
  if (mode == '\x01') {
    pTVar1 = (Form1->Memo2->super_TCustomMemo).FLines;
    p_Var2 = (pTVar1->super_TPersistent).super_TObject._vptr_TObject[0xf];
    memset(&local_108,0,8);
    local_108 = 0;
    local_f0 = &local_108;
    _ZN6System8Sysutils8IntToHexEii(&local_108,1,2);
    memset(&local_100,0,8);
    local_100 = 0;
    local_e8 = &local_100;
    _ZN6SystemplEPKcRKNS_13UnicodeStringE(&local_100,s_ConnectMode__0x_006e0606,&local_108);
    (*p_Var2)(pTVar1,local_100);
    _ZN6System13UnicodeStringD1Ev(&local_100);
    _ZN6System13UnicodeStringD1Ev(&local_108);
    Sleep(100);
    for (i = 0; i < 0x100; i = i + 1) {
      if (hFile[i] != (HANDLE)0x0) {
        CloseHandle(hFile[i]);
        hFile[i] = (HANDLE)0x0;
      }
    }
    UVar6 = (USAGE)MainDevice_UPID;
    UVar7 = (USAGE)MainDevice_UID;
    memset(&local_120,0,8);
    local_e0 = &MainHWid;
    if (MainHWid.Data == (WideChar *)0x0) {
      local_1cc = 0;
    }
    else {
      local_d0 = &MainHWid;
      local_c8 = MainHWid.Data + -8;
      local_1cc = *(int *)(MainHWid.Data + -2);
    }
    local_d4 = local_1cc;
    local_128 = 0;
    local_b0 = &MainHWid;
    local_b4 = local_1cc + -3;
    local_b8 = 4;
    local_c0 = &local_128;
    _ZNK6System13UnicodeString10SubString1Eii(&MainHWid,&local_128,local_b4,4);
    local_a0 = &local_120;
    local_120.Data = (char *)0x0;
    local_a8 = &local_128;
    _ZN6System14AnsiStringBaseC2ERKNS_13UnicodeStringEi(local_a0,&local_128,0);
    ConnectHIDDevice('\x01',UVar6,UVar7,(AnsiString)local_120.Data);
    local_98 = &local_120;
    System::AnsiStringT<0>::~AnsiStringT((AnsiStringT<0> *)local_98);
    _ZN6System13UnicodeStringD1Ev(&local_128);
    if (SensorCunt == '\0') {
      mode_local = '\x02';
    }
    else {
      bVar4 = HidCustomCmdInit('\x01');
      if ((!bVar4) && (ITEReportID != 'Z')) {
        ITEReportID = 'Z';
        HidCustomCmdInit('\x01');
      }
      iVar5 = (**(msUpdateBINBuffer->super_TCustomMemoryStream).super_TStream.super_TObject.
                 _vptr_TObject)(msUpdateBINBuffer);
      if (CONCAT44(extraout_var,iVar5) == (longlong)(Update_FileSizeKB << 10)) {
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
        pTVar1 = (Form1->Memo2->super_TCustomMemo).FLines;
        p_Var2 = (pTVar1->super_TPersistent).super_TObject._vptr_TObject[0xf];
        local_130 = 0;
        _ZN6System13UnicodeStringC1EPKc(&local_130,s_Bin_file_size_is_not_match___006e0616);
        (*p_Var2)(pTVar1,local_130);
        _ZN6System13UnicodeStringD1Ev(&local_130);
      }
      MainBootMode = 1;
    }
  }
  if (mode_local == '\x02') {
    pTVar1 = (Form1->Memo2->super_TCustomMemo).FLines;
    p_Var2 = (pTVar1->super_TPersistent).super_TObject._vptr_TObject[0xf];
    memset(&local_140,0,8);
    local_140 = 0;
    local_88 = &local_140;
    _ZN6System8Sysutils8IntToHexEii(&local_140,2,2);
    memset(&local_138,0,8);
    local_138 = 0;
    local_68 = &local_138;
    _ZN6SystemplEPKcRKNS_13UnicodeStringE(&local_138,s_ConnectMode__0x_006e0606,&local_140);
    (*p_Var2)(pTVar1,local_138);
    _ZN6System13UnicodeStringD1Ev(&local_138);
    _ZN6System13UnicodeStringD1Ev(&local_140);
    Sleep(100);
    for (i_1 = 0; i_1 < 0x100; i_1 = i_1 + 1) {
      if (hFile[i_1] != (HANDLE)0x0) {
        CloseHandle(hFile[i_1]);
        hFile[i_1] = (HANDLE)0x0;
      }
    }
    UVar6 = (USAGE)BootDevice_UPID;
    UVar7 = (USAGE)BootDevice_UID;
    memset(&local_150,0,8);
    local_60 = &MainHWid;
    if (MainHWid.Data == (WideChar *)0x0) {
      local_27c = 0;
    }
    else {
      local_50 = &MainHWid;
      local_48 = MainHWid.Data + -8;
      local_27c = *(int *)(MainHWid.Data + -2);
    }
    local_54 = local_27c;
    local_158 = 0;
    local_28 = &BootHWid;
    local_2c = local_27c + -3;
    local_30 = 4;
    local_40 = &local_158;
    _ZNK6System13UnicodeString10SubString1Eii(&BootHWid,&local_158,local_2c,4);
    local_18 = &local_150;
    local_150.Data = (char *)0x0;
    local_20 = &local_158;
    _ZN6System14AnsiStringBaseC2ERKNS_13UnicodeStringEi(local_18,&local_158,0);
    ConnectHIDDevice('\x02',UVar6,UVar7,(AnsiString)local_150.Data);
    local_38 = &local_150;
    System::AnsiStringT<0>::~AnsiStringT((AnsiStringT<0> *)local_38);
    _ZN6System13UnicodeStringD1Ev(&local_158);
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
  UVar3 = mode_local;
  if (((mode_local == 0x80) || (mode_local == '\0')) || (SensorCunt == '\0')) {
    pTVar1 = (Form1->Memo2->super_TCustomMemo).FLines;
    p_Var2 = (pTVar1->super_TPersistent).super_TObject._vptr_TObject[0xf];
    memset(&local_168,0,8);
    local_168 = 0;
    local_78 = &local_168;
    _ZN6System8Sysutils8IntToHexEii(&local_168,UVar3,2);
    memset(&local_160,0,8);
    local_160 = 0;
    local_80 = &local_160;
    _ZN6SystemplEPKcRKNS_13UnicodeStringE(&local_160,s_ConnectMode__0x_006e0606,&local_168);
    (*p_Var2)(pTVar1,local_160);
    _ZN6System13UnicodeStringD1Ev(&local_160);
    _ZN6System13UnicodeStringD1Ev(&local_168);
    if (mode_local == '\0') {
      HidCustomCmdInit('\0');
    }
    SensorCunt = '\0';
    MainBootMode = 0;
    for (i_2 = 0; i_2 < 0x100; i_2 = i_2 + 1) {
      if (hFile[i_2] != (HANDLE)0x0) {
        CloseHandle(hFile[i_2]);
        hFile[i_2] = (HANDLE)0x0;
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

