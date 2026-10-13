
/* DWARF original prototype: void FormCreate(TForm1 * this, TObject * Sender) */

void __thiscall TForm1::FormCreate(TForm1 *this,TObject *Sender)

{
  undefined8 uVar1;
  _func_int *p_Var2;
  undefined *this_00;
  TForm1 *pTVar3;
  TForm1 *pTVar4;
  TIniFile *pTVar5;
  TIniFile *extraout_RAX;
  byte local_128 [8];
  undefined8 local_120;
  undefined1 local_118 [8];
  undefined8 local_110;
  undefined8 local_108;
  undefined8 local_100;
  undefined8 local_f8;
  undefined8 local_f0;
  undefined8 local_e8;
  undefined8 local_e0;
  undefined8 local_d8;
  undefined8 local_d0;
  undefined8 local_c8 [3];
  undefined8 local_b0;
  undefined8 local_a8;
  UnicodeString local_a0;
  TIniFile *iniValue;
  TObject *Sender_local;
  TForm1 *this_local;
  undefined8 *local_80;
  undefined1 local_71;
  byte *local_70;
  byte *local_68;
  byte *local_60;
  undefined8 *local_58;
  undefined8 *local_50;
  undefined8 *local_48;
  undefined8 *local_40;
  UnicodeString *local_38;
  int local_2c;
  undefined8 *local_28;
  undefined8 *local_20;
  undefined8 *local_18;
  
  Sender_local = Sender;
  this_local = this;
  SetThreadExecutionState(0x80000043);
  this_00 = PTR_PTR_0089b1a0;
  uVar1 = *(undefined8 *)__indStub__ZN3Vcl5Forms11ApplicationE;
  memset(&local_b0,0,8);
  local_b0 = 0;
  local_80 = &local_b0;
  _ZN3Vcl5Forms12TApplication10GetExeNameEv(uVar1,&local_b0);
  memset(&local_a8,0,8);
  local_a8 = 0;
  local_58 = &local_a8;
  _ZN6System8Sysutils15ExtractFilePathENS_13UnicodeStringE(&local_a8,local_b0);
  local_c8[0] = 0;
  _ZN6System13UnicodeStringC1EPKc(local_c8,s_SHFU_ini_006e06e9);
  memset(&local_a0,0,8);
  local_a0.Data = (WideChar *)0x0;
  local_38 = &local_a0;
  _ZNK6System13UnicodeStringplERKS0_(&local_a8,&local_a0,local_c8);
  System::Inifiles::TIniFile::TIniFile((TIniFile *)this_00,'\x01',local_a0);
  _ZN6System13UnicodeStringD1Ev(&local_a0);
  _ZN6System13UnicodeStringD1Ev(local_c8);
  _ZN6System13UnicodeStringD1Ev(&local_a8);
  _ZN6System13UnicodeStringD1Ev(&local_b0);
  if (extraout_RAX != (TIniFile *)0x0) {
    p_Var2 = (extraout_RAX->super_TCustomIniFile).super_TObject._vptr_TObject[1];
    local_d8 = 0;
    iniValue = extraout_RAX;
    _ZN6System13UnicodeStringC1EPKc(&local_d8,s_MESSAGE_006e06f2);
    local_e0 = 0;
    _ZN6System13UnicodeStringC1EPKc(&local_e0,s_ENABLE_006e06fa);
    local_28 = &local_e8;
    local_2c = MessageEnable;
    local_e8 = 0;
    _ZN6System13UnicodeString7sprintfEPKwz(local_28,&DAT_006e0eb2,MessageEnable);
    memset(&local_d0,0,8);
    local_d0 = 0;
    local_20 = &local_d0;
    (*p_Var2)(extraout_RAX,&local_d0,local_d8,local_e0,local_e8);
    MessageEnable = _ZN6System8Sysutils8StrToIntENS_13UnicodeStringE(local_d0);
    _ZN6System13UnicodeStringD1Ev(&local_d0);
    _ZN6System13UnicodeStringD1Ev(&local_e8);
    _ZN6System13UnicodeStringD1Ev(&local_e0);
    _ZN6System13UnicodeStringD1Ev(&local_d8);
    pTVar5 = iniValue;
    p_Var2 = (iniValue->super_TCustomIniFile).super_TObject._vptr_TObject[1];
    local_f8 = 0;
    _ZN6System13UnicodeStringC1EPKc(&local_f8,s_OPTION_006e0701);
    local_100 = 0;
    _ZN6System13UnicodeStringC1EPKc(&local_100,s_TITLENAME_006e0708);
    memset(&local_f0,0,8);
    local_f0 = 0;
    local_18 = &local_f0;
    (*p_Var2)(pTVar5,&local_f0,local_f8,local_100,TitleName.Data);
    _ZN6System13UnicodeStringaSERKS0_(&TitleName,&local_f0);
    _ZN6System13UnicodeStringD1Ev(&local_f0);
    _ZN6System13UnicodeStringD1Ev(&local_100);
    _ZN6System13UnicodeStringD1Ev(&local_f8);
    if (iniValue != (TIniFile *)0x0) {
      (*(iniValue->super_TCustomIniFile).super_TObject._vptr_TObject[-4])(iniValue,3);
    }
    if (MessageEnable != 0) {
      _ZN3Vcl8Controls8TControl10SetVisibleEb(this->Memo2,1);
    }
    pTVar3 = Form1;
    memset(local_118,0,8);
    _ZN6System13UnicodeStringC1EPKc(local_118,&DAT_006e0712);
    memset(&local_110,0,8);
    local_110 = 0;
    local_40 = &local_110;
    _ZNK6System13UnicodeStringplERKS0_(&TitleName,&local_110,local_118);
    pTVar4 = Form1;
    memset(&local_120,0,8);
    local_120 = 0;
    local_48 = &local_120;
    _ZN3Vcl8Controls8TControl7GetTextEv(pTVar4,&local_120);
    memset(&local_108,0,8);
    local_108 = 0;
    local_50 = &local_108;
    _ZNK6System13UnicodeStringplERKS0_(&local_110,&local_108,&local_120);
    _ZN3Vcl8Controls8TControl7SetTextEN6System13UnicodeStringE(pTVar3,local_108);
    _ZN6System13UnicodeStringD1Ev(&local_108);
    _ZN6System13UnicodeStringD1Ev(&local_120);
    _ZN6System13UnicodeStringD1Ev(&local_110);
    _ZN6System13UnicodeStringD1Ev(local_118);
  }
  pTVar3 = Form1;
  memset(local_128,0,1);
  local_60 = local_128;
  memset(local_128,0,1);
  local_70 = local_128;
  local_71 = 0;
  local_128[0] = local_128[0] & 0xfe;
  local_68 = local_70;
  _ZN3Vcl5Forms11TCustomForm14SetBorderIconsEN6System3SetINS2_7Uitypes11TBorderIconELS5_0ELS5_3EEE
            (pTVar3,local_128[0]);
  _ZN3Vcl8Controls8TControl10SetVisibleEb(this->GroupBox1,0);
  _ZN3Vcl8Controls8TControl10SetVisibleEb(this->GroupBox2,0);
  _ZN3Vcl8Controls8TControl10SetVisibleEb(this->GroupBox3,0);
  _ZN3Vcl8Controls8TControl9SetHeightEi(Form1,0xfa);
  if (MessageEnable == 0) {
    _ZN3Vcl8Controls8TControl10SetVisibleEb(Form1->Image2,1);
  }
  return;
}

