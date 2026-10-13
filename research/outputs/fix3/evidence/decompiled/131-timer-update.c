
/* WARNING: Control flow encountered bad instruction data */
/* WARNING: Instruction at (ram,0x00412c26) overlaps instruction at (ram,0x00412c25)
    */
/* WARNING: Type propagation algorithm not settling */
/* WARNING: Restarted to delay deadcode elimination for space: stack */
/* DWARF original prototype: void Timer1Timer(TForm1 * this, TObject * Sender) */

void __thiscall TForm1::Timer1Timer(TForm1 *this,TObject *Sender)

{
  TStrings *pTVar1;
  _func_int *p_Var2;
  TLabel *pTVar3;
  int iVar4;
  TForm1 *pTVar5;
  byte bVar6;
  DWORD DVar7;
  DWORD DVar8;
  undefined8 extraout_RAX;
  char *pcVar9;
  AnsiStringT<0> *this_00;
  uint uVar10;
  code *_Dst;
  char cVar11;
  undefined8 local_390;
  undefined8 local_388;
  undefined8 local_380;
  undefined8 local_378;
  undefined8 local_370;
  undefined8 local_368;
  AnsiStringBase local_360;
  AnsiStringBase local_358;
  undefined8 local_350;
  undefined8 local_348;
  undefined8 local_340;
  byte local_338 [8];
  undefined8 local_330;
  undefined1 local_328 [8];
  undefined8 local_320;
  undefined8 local_318;
  AnsiStringT<0> local_310;
  AnsiStringT<0> local_308;
  AnsiStringT<0> local_300;
  AnsiStringBase local_2f8;
  AnsiStringBase local_2f0;
  undefined8 local_2e8;
  undefined8 local_2e0;
  undefined8 local_2d8;
  undefined8 local_2d0;
  byte local_2c8 [8];
  undefined8 local_2c0;
  undefined1 local_2b8 [12];
  uint local_2ac;
  undefined8 local_2a8;
  undefined8 local_2a0;
  undefined8 local_298 [3];
  undefined8 local_280;
  undefined8 local_278;
  AnsiString OEMVERData;
  UCHAR Data [32];
  TObject *Sender_local;
  TForm1 *this_local;
  uint iStart;
  uint iStart_1;
  uint iStart_2;
  uint iStart_3;
  uint iStart_4;
  uint iStart_5;
  
  memset(Data,0,0x20);
  memset(&OEMVERData,0,8);
  memset(&OEMVERData,0,8);
  iVar4 = FlashState;
  OEMVERData.super_AnsiStringBase.Data = (AnsiStringBase)(char *)0x0;
  if (FlashState != 5) {
    pTVar1 = (this->Memo1->super_TCustomMemo).FLines;
    p_Var2 = (pTVar1->super_TPersistent).super_TObject._vptr_TObject[0xf];
    memset(&local_280,0,8);
    local_280 = 0;
    _ZN6System8Sysutils8IntToStrEi(&local_280,iVar4);
    memset(&local_278,0,8);
    local_278 = 0;
    _ZN6SystemplEPKcRKNS_13UnicodeStringE(&local_278,s_State__006e063f,&local_280);
    (*p_Var2)(pTVar1,local_278);
    _ZN6System13UnicodeStringD1Ev(&local_278);
    _ZN6System13UnicodeStringD1Ev(&local_280);
  }
  iVar4 = FlashState;
  _Dst = (code *)&local_2a0;
  pTVar1 = (this->Memo2->super_TCustomMemo).FLines;
  p_Var2 = (pTVar1->super_TPersistent).super_TObject._vptr_TObject[0xf];
  memset(_Dst,0,8);
  local_2a0 = 0;
  _ZN6System8Sysutils8IntToStrEi(&local_2a0,iVar4);
  memset(local_298,0,8);
  local_298[0] = 0;
  _ZN6SystemplEPKcRKNS_13UnicodeStringE(local_298,s_State__006e063f,&local_2a0);
  (*p_Var2)(pTVar1,local_298[0]);
  _ZN6System13UnicodeStringD1Ev(local_298);
  _ZN6System13UnicodeStringD1Ev(&local_2a0);
  switch(FlashState) {
  case 0:
    _ZN3Vcl8Graphics5TFont7SetSizeEi
              ((Form1->Memo1->super_TCustomMemo).super_TCustomEdit.super_TWinControl.super_TControl.
               FFont,8);
    _ZN3Vcl8Graphics5TFont8SetColorEN6System7Uitypes6TColorE
              ((Form1->Memo1->super_TCustomMemo).super_TCustomEdit.super_TWinControl.super_TControl.
               FFont,0xff000008);
    (**(code **)((longlong)
                 (this->Memo1->super_TCustomMemo).super_TCustomEdit.super_TWinControl.super_TControl
                 .super_TComponent.super_TPersistent.super_TObject + 0x280))();
    pTVar1 = (this->Memo1->super_TCustomMemo).FLines;
    p_Var2 = (pTVar1->super_TPersistent).super_TObject._vptr_TObject[0xf];
    local_2a8 = 0;
    _ZN6System13UnicodeStringC1EPKc(&local_2a8,s_Finding_Device_____006e0646);
    (*p_Var2)(pTVar1,local_2a8);
    _ZN6System13UnicodeStringD1Ev(&local_2a8);
    ConnectHub('\x01');
    FlashState = 1;
    break;
  case 1:
    ConnectHub('\x01');
    TimerCunt = TimerCunt + 1;
    if ((DockingBurn != 0) && (MaxStateCunt / 2 + 1 < TimerCunt)) {
      Timer4Timer(this,Sender);
      FlashState = 0;
      TimerCunt = 0;
      if (ReturnValue != '\0') {
        FlashState = 5;
        local_2ac = 1;
        goto LAB_00412bbd;
      }
    }
    if (MaxStateCunt < TimerCunt) {
      _ZN3Vcl8Extctrls6TTimer10SetEnabledEb(this->Timer1,0);
      (**(code **)((longlong)
                   (Form1->Memo1->super_TCustomMemo).super_TCustomEdit.super_TWinControl.
                   super_TControl.super_TComponent.super_TPersistent.super_TObject + 0x280))
                (Form1->Memo1);
      _ZN3Vcl8Graphics5TFont7SetSizeEi
                ((Form1->Memo1->super_TCustomMemo).super_TCustomEdit.super_TWinControl.
                 super_TControl.FFont,0x19);
      _ZN3Vcl8Graphics5TFont8SetColorEN6System7Uitypes6TColorE
                ((Form1->Memo1->super_TCustomMemo).super_TCustomEdit.super_TWinControl.
                 super_TControl.FFont,0xff);
      iVar4 = FlashState;
      _Dst = (code *)&local_2c0;
      pTVar1 = (this->Memo1->super_TCustomMemo).FLines;
      p_Var2 = (pTVar1->super_TPersistent).super_TObject._vptr_TObject[0xf];
      memset(_Dst,0,8);
      local_2c0 = 0;
      _ZN6System8Sysutils8IntToStrEi(&local_2c0,iVar4);
      memset(local_2b8,0,8);
      _ZN6SystemplEPKcRKNS_13UnicodeStringE(local_2b8,s_Can_not_Find_Device____006e0659,&local_2c0);
      (*p_Var2)(pTVar1);
      _ZN6System13UnicodeStringD1Ev(local_2b8);
      _ZN6System13UnicodeStringD1Ev(&local_2c0);
      pTVar5 = Form1;
      local_2c8[0] = 0;
      memset(local_2c8,0,1);
      _ZN3Vcl5Forms11TCustomForm14SetBorderIconsEN6System3SetINS2_7Uitypes11TBorderIconELS5_0ELS5_3EEE
                (pTVar5,local_2c8[0] | 1);
      _ZN3Vcl8Extctrls6TTimer10SetEnabledEb(this->Timer2,1);
      if (DisableUpdateLogFile == 0) {
        SaveShfuLog();
      }
      ReturnValue = '\x01';
      if (FailClose != 0) {
        _ZN3Vcl5Forms11TCustomForm5CloseEv(Form1);
      }
    }
    bVar6 = (**(code **)((longlong)
                         (this->Button2->super_TCustomButton).super_TButtonControl.super_TWinControl
                         .super_TControl.super_TComponent.super_TPersistent.super_TObject + 0xe8))()
    ;
    if (((bVar6 & 1) == 1) &&
       (bVar6 = (**(code **)((longlong)
                             (this->Button3->super_TCustomButton).super_TButtonControl.
                             super_TWinControl.super_TControl.super_TComponent.super_TPersistent.
                             super_TObject + 0xe8))(), (bVar6 & 1) == 0)) {
      FlashState = 2;
      (**(code **)((longlong)
                   (this->Memo1->super_TCustomMemo).super_TCustomEdit.super_TWinControl.
                   super_TControl.super_TComponent.super_TPersistent.super_TObject + 0x280))();
      pTVar1 = (this->Memo1->super_TCustomMemo).FLines;
      p_Var2 = (pTVar1->super_TPersistent).super_TObject._vptr_TObject[0xf];
      local_2d0 = 0;
      _ZN6System13UnicodeStringC1EPKc(&local_2d0,s_Finding_Device_____006e0646);
      (*p_Var2)(pTVar1,local_2d0);
      _ZN6System13UnicodeStringD1Ev(&local_2d0);
    }
    bVar6 = (**(code **)((longlong)
                         (this->Button2->super_TCustomButton).super_TButtonControl.super_TWinControl
                         .super_TControl.super_TComponent.super_TPersistent.super_TObject + 0xe8))()
    ;
    if (((bVar6 & 1) == 0) &&
       (bVar6 = (**(code **)((longlong)
                             (this->Button3->super_TCustomButton).super_TButtonControl.
                             super_TWinControl.super_TControl.super_TComponent.super_TPersistent.
                             super_TObject + 0xe8))(), (bVar6 & 1) == 1)) {
      FlashState = 4;
      (**(code **)((longlong)
                   (this->Memo1->super_TCustomMemo).super_TCustomEdit.super_TWinControl.
                   super_TControl.super_TComponent.super_TPersistent.super_TObject + 0x280))();
      pTVar1 = (this->Memo1->super_TCustomMemo).FLines;
      p_Var2 = (pTVar1->super_TPersistent).super_TObject._vptr_TObject[0xf];
      local_2d8 = 0;
      _ZN6System13UnicodeStringC1EPKc(&local_2d8,s_Finding_Device_____006e0646);
      (*p_Var2)(pTVar1,local_2d8);
      _ZN6System13UnicodeStringD1Ev(&local_2d8);
    }
    if ((DockingBurn == 0) && (TimerCunt == MaxStateCunt / 2 + 1)) {
      ConnectHub(0x80);
      iVar4 = DelayMSec;
      DVar7 = GetTickCount();
      while (DVar8 = GetTickCount(), DVar8 - DVar7 <= (uint)iVar4) {
        _ZN3Vcl5Forms12TApplication15ProcessMessagesEv
                  (*(undefined8 *)__indStub__ZN3Vcl5Forms11ApplicationE);
      }
      memset(&local_2e0,0,8);
      local_2e0 = 0;
      _ZNK6System13UnicodeString10SubString1Eii(&BootHWid,&local_2e0,0,3);
      local_2e8 = 0;
      _ZN6System13UnicodeStringC1EPKc(&local_2e8,&DAT_006e05d9);
      bVar6 = _ZNK6System13UnicodeStringneERKS0_(&local_2e0,&local_2e8);
      _ZN6System13UnicodeStringD1Ev(&local_2e8);
      _ZN6System13UnicodeStringD1Ev(&local_2e0);
      if (((bVar6 & 1) != 0) && (RemoveRescan != 0)) {
        local_2f0.Data = (char *)0x0;
        _ZN6System14AnsiStringBaseC2ERKNS_13UnicodeStringEi(&local_2f0,&BootHWid,0);
        DisableEnableDevice((AnsiString)local_2f0.Data,false);
        System::AnsiStringT<0>::~AnsiStringT((AnsiStringT<0> *)&local_2f0);
        local_2f8.Data = (char *)0x0;
        _ZN6System14AnsiStringBaseC2ERKNS_13UnicodeStringEi(&local_2f8,&BootHWid,0);
        RemoveDevice((AnsiString)local_2f8.Data);
        System::AnsiStringT<0>::~AnsiStringT((AnsiStringT<0> *)&local_2f8);
        uVar10 = DelayMSec / 2;
        DVar7 = GetTickCount();
        while (DVar8 = GetTickCount(), DVar8 - DVar7 <= uVar10) {
          _ZN3Vcl5Forms12TApplication15ProcessMessagesEv
                    (*(undefined8 *)__indStub__ZN3Vcl5Forms11ApplicationE);
        }
        RescanDevice();
        uVar10 = DelayMSec / 2;
        DVar7 = GetTickCount();
        while (DVar8 = GetTickCount(), DVar8 - DVar7 <= uVar10) {
          _ZN3Vcl5Forms12TApplication15ProcessMessagesEv
                    (*(undefined8 *)__indStub__ZN3Vcl5Forms11ApplicationE);
        }
      }
      ConnectHub('\x02');
    }
    break;
  case 2:
    if (Data[0] == '\0') {
      local_300.super_AnsiStringBase.Data = (AnsiStringBase)(char *)0x0;
      _ZN6System14AnsiStringBaseC2EPKci(&local_300,&DAT_006e0293,0);
      _ZN6System14AnsiStringBaseaSERKS0_(&OEMVERData,&local_300);
      System::AnsiStringT<0>::~AnsiStringT(&local_300);
    }
    else {
      System::AnsiStringT<0>::printf(&OEMVERData,&DAT_006e052c);
    }
    local_308.super_AnsiStringBase.Data = (AnsiStringBase)(char *)0x0;
    _ZN6System14AnsiStringBaseC2EPKci(&local_308,&DAT_006e0293,0);
    bVar6 = _ZNK6System14AnsiStringBaseneERKS0_(&OEMVERData,&local_308);
    System::AnsiStringT<0>::~AnsiStringT(&local_308);
    if ((bVar6 & 1) != 0) {
      pTVar3 = this->Label2;
      memset(&local_310,0,8);
      memset(&local_310,0,8);
      local_310.super_AnsiStringBase.Data = (AnsiStringBase)(char *)0x0;
      System::operator+<0>((System *)&local_310,s_Current_firmware_version__006e055e,&OEMVERData);
      local_318 = 0;
      _ZN6System8Internal7Strhlpr15UnicodeFromAnsiERNS_13UnicodeStringERNS_11AnsiStringTILt65535EEE
                (&local_318,&local_310);
      _ZN3Vcl8Controls8TControl7SetTextEN6System13UnicodeStringE(pTVar3,local_318);
      _ZN6System13UnicodeStringD1Ev(&local_318);
      System::AnsiStringT<0>::~AnsiStringT(&local_310);
    }
    _ZN3Vcl8Controls8TControl10SetVisibleEb(this->Panel1,0);
    _ZN3Vcl8Controls8TControl10SetVisibleEb(this->Image8,0);
    _ZN3Vcl8Extctrls6TTimer10SetEnabledEb(this->Timer2,0);
    (**(code **)((longlong)
                 (this->Memo1->super_TCustomMemo).super_TCustomEdit.super_TWinControl.super_TControl
                 .super_TComponent.super_TPersistent.super_TObject + 0x280))();
    pTVar1 = (this->Memo1->super_TCustomMemo).FLines;
    p_Var2 = (pTVar1->super_TPersistent).super_TObject._vptr_TObject[0xf];
    local_320 = 0;
    _ZN6System13UnicodeStringC1EPKc(&local_320,s_Finding_Device_____006e0646);
    (*p_Var2)(pTVar1,local_320);
    _ZN6System13UnicodeStringD1Ev(&local_320);
    TimerCunt = 0;
    (*(this->Button2->super_TCustomButton).super_TButtonControl.super_TWinControl.super_TControl.
      FOnClick.__funcptr)
              ((this->Button2->super_TCustomButton).super_TButtonControl.super_TWinControl.
               super_TControl.FOnClick.__this);
    FlashState = 3;
    break;
  case 3:
    TimerCunt = TimerCunt + 1;
    if (MaxStateCunt < TimerCunt) {
      _ZN3Vcl8Extctrls6TTimer10SetEnabledEb(this->Timer1,0);
      (**(code **)((longlong)
                   (Form1->Memo1->super_TCustomMemo).super_TCustomEdit.super_TWinControl.
                   super_TControl.super_TComponent.super_TPersistent.super_TObject + 0x280))
                (Form1->Memo1);
      _ZN3Vcl8Graphics5TFont7SetSizeEi
                ((Form1->Memo1->super_TCustomMemo).super_TCustomEdit.super_TWinControl.
                 super_TControl.FFont,0x19);
      _ZN3Vcl8Graphics5TFont8SetColorEN6System7Uitypes6TColorE
                ((Form1->Memo1->super_TCustomMemo).super_TCustomEdit.super_TWinControl.
                 super_TControl.FFont,0xff);
      iVar4 = FlashState;
      _Dst = (code *)&local_330;
      pTVar1 = (this->Memo1->super_TCustomMemo).FLines;
      p_Var2 = (pTVar1->super_TPersistent).super_TObject._vptr_TObject[0xf];
      memset(_Dst,0,8);
      local_330 = 0;
      _ZN6System8Sysutils8IntToStrEi(&local_330,iVar4);
      memset(local_328,0,8);
      _ZN6SystemplEPKcRKNS_13UnicodeStringE(local_328,s_Can_not_Find_Device____006e0659,&local_330);
      (*p_Var2)(pTVar1);
      _ZN6System13UnicodeStringD1Ev(local_328);
      _ZN6System13UnicodeStringD1Ev(&local_330);
      pTVar5 = Form1;
      local_338[0] = 0;
      memset(local_338,0,1);
      _ZN3Vcl5Forms11TCustomForm14SetBorderIconsEN6System3SetINS2_7Uitypes11TBorderIconELS5_0ELS5_3EEE
                (pTVar5,local_338[0] | 1);
      _ZN3Vcl8Extctrls6TTimer10SetEnabledEb(this->Timer2,1);
      if (DisableUpdateLogFile == 0) {
        SaveShfuLog();
      }
      ReturnValue = '\x03';
      if (FailClose != 0) {
        _ZN3Vcl5Forms11TCustomForm5CloseEv(Form1);
      }
    }
    bVar6 = (**(code **)((longlong)
                         (this->Button2->super_TCustomButton).super_TButtonControl.super_TWinControl
                         .super_TControl.super_TComponent.super_TPersistent.super_TObject + 0xe8))()
    ;
    if (((bVar6 & 1) == 0) &&
       (bVar6 = (**(code **)((longlong)
                             (this->Button3->super_TCustomButton).super_TButtonControl.
                             super_TWinControl.super_TControl.super_TComponent.super_TPersistent.
                             super_TObject + 0xe8))(), (bVar6 & 1) == 1)) {
      FlashState = 4;
      (**(code **)((longlong)
                   (this->Memo1->super_TCustomMemo).super_TCustomEdit.super_TWinControl.
                   super_TControl.super_TComponent.super_TPersistent.super_TObject + 0x280))();
      pTVar1 = (this->Memo1->super_TCustomMemo).FLines;
      p_Var2 = (pTVar1->super_TPersistent).super_TObject._vptr_TObject[0xf];
      local_340 = 0;
      _ZN6System13UnicodeStringC1EPKc(&local_340,s_Finding_Device_____006e0646);
      (*p_Var2)(pTVar1,local_340);
      _ZN6System13UnicodeStringD1Ev(&local_340);
    }
    if (TimerCunt == MaxStateCunt / 2 + 1) {
      ConnectHub(0x80);
      iVar4 = DelayMSec;
      DVar7 = GetTickCount();
      while (DVar8 = GetTickCount(), DVar8 - DVar7 <= (uint)iVar4) {
        _ZN3Vcl5Forms12TApplication15ProcessMessagesEv
                  (*(undefined8 *)__indStub__ZN3Vcl5Forms11ApplicationE);
      }
      memset(&local_348,0,8);
      local_348 = 0;
      _ZNK6System13UnicodeString10SubString1Eii(&BootHWid,&local_348,0,3);
      local_350 = 0;
      _ZN6System13UnicodeStringC1EPKc(&local_350,&DAT_006e05d9);
      bVar6 = _ZNK6System13UnicodeStringneERKS0_(&local_348,&local_350);
      _ZN6System13UnicodeStringD1Ev(&local_350);
      _ZN6System13UnicodeStringD1Ev(&local_348);
      if (((bVar6 & 1) != 0) && (RemoveRescan != 0)) {
        local_358.Data = (char *)0x0;
        _ZN6System14AnsiStringBaseC2ERKNS_13UnicodeStringEi(&local_358,&BootHWid,0);
        DisableEnableDevice((AnsiString)local_358.Data,false);
        System::AnsiStringT<0>::~AnsiStringT((AnsiStringT<0> *)&local_358);
        local_360.Data = (char *)0x0;
        _ZN6System14AnsiStringBaseC2ERKNS_13UnicodeStringEi(&local_360,&BootHWid,0);
        RemoveDevice((AnsiString)local_360.Data);
        System::AnsiStringT<0>::~AnsiStringT((AnsiStringT<0> *)&local_360);
        uVar10 = DelayMSec / 2;
        DVar7 = GetTickCount();
        while (DVar8 = GetTickCount(), DVar8 - DVar7 <= uVar10) {
          _ZN3Vcl5Forms12TApplication15ProcessMessagesEv
                    (*(undefined8 *)__indStub__ZN3Vcl5Forms11ApplicationE);
        }
        RescanDevice();
        uVar10 = DelayMSec / 2;
        DVar7 = GetTickCount();
        while (DVar8 = GetTickCount(), DVar8 - DVar7 <= uVar10) {
          _ZN3Vcl5Forms12TApplication15ProcessMessagesEv
                    (*(undefined8 *)__indStub__ZN3Vcl5Forms11ApplicationE);
        }
      }
      ConnectHub('\x02');
    }
    break;
  case 4:
    _ZN3Vcl8Controls8TControl10SetVisibleEb(this->Panel1,0);
    _ZN3Vcl8Controls8TControl10SetVisibleEb(this->Image8,0);
    _ZN3Vcl8Extctrls6TTimer10SetEnabledEb(this->Timer2,0);
    (**(code **)((longlong)
                 (this->Memo1->super_TCustomMemo).super_TCustomEdit.super_TWinControl.super_TControl
                 .super_TComponent.super_TPersistent.super_TObject + 0x280))();
    pTVar1 = (this->Memo1->super_TCustomMemo).FLines;
    p_Var2 = (pTVar1->super_TPersistent).super_TObject._vptr_TObject[0xf];
    local_368 = 0;
    _ZN6System13UnicodeStringC1EPKc(&local_368,s_Found_Device__006e0671);
    (*p_Var2)(pTVar1,local_368);
    _ZN6System13UnicodeStringD1Ev(&local_368);
    _ZN3Vcl8Extctrls6TTimer10SetEnabledEb(this->Timer1,0);
    if (MessageEnable == 0) {
      _ZN3Vcl8Controls8TControl10SetVisibleEb(Form1->Image2,0);
    }
    if (MessageEnable == 0) {
      _ZN3Vcl8Controls8TControl10SetVisibleEb(Form1->Image3,1);
    }
    pTVar3 = Form1->Label2;
    local_370 = 0;
    _ZN6System13UnicodeStringC1EPKc(&local_370,&DAT_006e0293);
    _ZN3Vcl8Controls8TControl7SetTextEN6System13UnicodeStringE(pTVar3,local_370);
    _ZN6System13UnicodeStringD1Ev(&local_370);
    load_code_flow();
    if (ReturnValue == '\x10') {
      _ZN3Vcl8Extctrls6TTimer10SetEnabledEb(this->Timer2,1);
    }
    if (ReturnValue == '\0') {
      (**(code **)((longlong)
                   (Form1->Memo1->super_TCustomMemo).super_TCustomEdit.super_TWinControl.
                   super_TControl.super_TComponent.super_TPersistent.super_TObject + 0x280))
                (Form1->Memo1);
      pTVar1 = (Form1->Memo1->super_TCustomMemo).FLines;
      p_Var2 = (pTVar1->super_TPersistent).super_TObject._vptr_TObject[0xf];
      local_378 = 0;
      _ZN6System13UnicodeStringC1EPKc(&local_378,s_Instructions__006e0537);
      (*p_Var2)(pTVar1,local_378);
      _ZN6System13UnicodeStringD1Ev(&local_378);
      if (DockingBurn == 0) {
        pTVar1 = (Form1->Memo1->super_TCustomMemo).FLines;
        p_Var2 = (pTVar1->super_TPersistent).super_TObject._vptr_TObject[0xf];
        local_388 = 0;
        _ZN6System13UnicodeStringC1EPKc(&local_388,s_Firmware_update_is_completed_and_006e06b7);
        (*p_Var2)(pTVar1,local_388);
        _ZN6System13UnicodeStringD1Ev(&local_388);
      }
      else {
        pTVar1 = (Form1->Memo1->super_TCustomMemo).FLines;
        p_Var2 = (pTVar1->super_TPersistent).super_TObject._vptr_TObject[0xf];
        local_380 = 0;
        _ZN6System13UnicodeStringC1EPKc(&local_380,s_Firmware_update_is_completed_and_006e067f);
        (*p_Var2)(pTVar1,local_380);
        _ZN6System13UnicodeStringD1Ev(&local_380);
      }
    }
    _ZN3Vcl8Extctrls6TTimer10SetEnabledEb(Form1->Timer5,0);
    _ZN3Vcl8Controls8TControl10SetVisibleEb(Form1->Image6,0);
    _ZN3Vcl8Controls8TControl10SetVisibleEb(Form1->Image7,0);
    (**(code **)((longlong)
                 (Form1->Button6->super_TCustomButton).super_TButtonControl.super_TWinControl.
                 super_TControl.super_TComponent.super_TPersistent.super_TObject + 0x120))
              (Form1->Button6,1);
    if (DockingBurn != 0) {
      FlashState = 5;
      _ZN3Vcl8Extctrls6TTimer10SetEnabledEb(this->Timer1,1);
    }
  case 5:
    (**(code **)((longlong)
                 (Form1->Button2->super_TCustomButton).super_TButtonControl.super_TWinControl.
                 super_TControl.super_TComponent.super_TPersistent.super_TObject + 0x120))
              (Form1->Button2,0);
    (**(code **)((longlong)
                 (Form1->Button3->super_TCustomButton).super_TButtonControl.super_TWinControl.
                 super_TControl.super_TComponent.super_TPersistent.super_TObject + 0x120))
              (Form1->Button3,0);
    (**(code **)((longlong)
                 (Form1->Button4->super_TCustomButton).super_TButtonControl.super_TWinControl.
                 super_TControl.super_TComponent.super_TPersistent.super_TObject + 0x120))
              (Form1->Button4,0);
    ConnectHub('\x01');
    bVar6 = (**(code **)((longlong)
                         (Form1->Button2->super_TCustomButton).super_TButtonControl.
                         super_TWinControl.super_TControl.super_TComponent.super_TPersistent.
                         super_TObject + 0xe8))(Form1->Button2);
    if ((((bVar6 & 1) == 0) &&
        (bVar6 = (**(code **)((longlong)
                              (Form1->Button3->super_TCustomButton).super_TButtonControl.
                              super_TWinControl.super_TControl.super_TComponent.super_TPersistent.
                              super_TObject + 0xe8))(Form1->Button3), (bVar6 & 1) == 0)) &&
       (bVar6 = (**(code **)((longlong)
                             (Form1->Button4->super_TCustomButton).super_TButtonControl.
                             super_TWinControl.super_TControl.super_TComponent.super_TPersistent.
                             super_TObject + 0xe8))(Form1->Button4), (bVar6 & 1) == 0)) {
      FlashState = 0;
      TimerCunt = 0;
      _ZN3Vcl8Graphics5TFont7SetSizeEi
                ((Form1->Memo1->super_TCustomMemo).super_TCustomEdit.super_TWinControl.
                 super_TControl.FFont,8);
      _ZN3Vcl8Graphics5TFont8SetColorEN6System7Uitypes6TColorE
                ((Form1->Memo1->super_TCustomMemo).super_TCustomEdit.super_TWinControl.
                 super_TControl.FFont,0xff000008);
      pTVar3 = Form1->Label2;
      local_390 = 0;
      _ZN6System13UnicodeStringC1EPKc(&local_390,&DAT_006e0293);
      _ZN3Vcl8Controls8TControl7SetTextEN6System13UnicodeStringE(pTVar3,local_390);
      _ZN6System13UnicodeStringD1Ev(&local_390);
    }
  }
  local_2ac = 0;
LAB_00412bbd:
  this_00 = &OEMVERData;
  System::AnsiStringT<0>::~AnsiStringT(this_00);
  if (local_2ac < 2) {
    return;
  }
  pcVar9 = (char *)CONCAT62((int6)((ulonglong)extraout_RAX >> 0x10),
                            CONCAT11(0xe6,(char)extraout_RAX));
  cVar11 = *pcVar9;
  pcVar9 = (char *)CONCAT71((int7)((ulonglong)pcVar9 >> 8),cVar11);
  *pcVar9 = *pcVar9 + cVar11;
  *pcVar9 = *pcVar9 + cVar11;
  cVar11 = *pcVar9 == '\0';
  (*_Dst)();
  if (this_00 == (AnsiStringT<0> *)0x1 || cVar11 != '\0') {
    *(int *)(_Dst + -0x15) = *(int *)(_Dst + -0x15) + 1;
                    /* WARNING: Bad instruction - Truncating control flow here */
    halt_baddata();
  }
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}

