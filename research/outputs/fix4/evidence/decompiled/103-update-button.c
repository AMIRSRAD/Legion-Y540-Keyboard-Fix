
/* DWARF original prototype: void Button2Click(TForm1 * this, TObject * Sender) */

void __thiscall TForm1::Button2Click(TForm1 *this,TObject *Sender)

{
  TStrings *pTVar1;
  _func_int *p_Var2;
  byte bVar3;
  DWORD DVar4;
  AnsiStringBase local_c8;
  AnsiStringBase local_c0;
  undefined8 local_b8;
  undefined8 local_b0 [3];
  undefined8 local_98;
  UCHAR buffer;
  TObject *Sender_local;
  TForm1 *this_local;
  uint iStart;
  uint local_74;
  undefined8 *local_70;
  undefined4 local_68;
  undefined4 local_64;
  String *local_60;
  String *local_58;
  AnsiStringBase *local_50;
  AnsiStringBase *local_48;
  String *local_40;
  AnsiStringBase *local_38;
  AnsiStringBase *local_30;
  uint iStart_1;
  uint local_24;
  uint iStart_2;
  uint local_1c;
  
  buffer = '\t';
  Sender_local = Sender;
  this_local = this;
  HidRequests(hFile[MainIndex],true,ITEReportID,&buffer,'\x02');
  Sleep(1000);
  pTVar1 = (this->Memo1->super_TCustomMemo).FLines;
  (*(pTVar1->super_TPersistent).super_TObject._vptr_TObject[0x12])(pTVar1);
  pTVar1 = (this->Memo1->super_TCustomMemo).FLines;
  p_Var2 = (pTVar1->super_TPersistent).super_TObject._vptr_TObject[0xf];
  local_98 = 0;
  _ZN6System13UnicodeStringC1EPKc(&local_98,s_Enter_Flash_Mode__006e05c7);
  (*p_Var2)(pTVar1,local_98);
  _ZN6System13UnicodeStringD1Ev(&local_98);
  _ZN3Vcl8Extctrls6TTimer10SetEnabledEb(this->Timer1,0);
  ConnectHub(0x80);
  local_74 = DelayMSec;
  iStart = GetTickCount();
  while (DVar4 = GetTickCount(), DVar4 - iStart <= local_74) {
    _ZN3Vcl5Forms12TApplication15ProcessMessagesEv
              (*(undefined8 *)__indStub__ZN3Vcl5Forms11ApplicationE);
  }
  local_70 = local_b0;
  local_b0[0] = 0;
  local_60 = &BootHWid;
  local_64 = 0;
  local_68 = 3;
  _ZNK6System13UnicodeString10SubString1Eii(&BootHWid,local_70,0,3);
  local_b8 = 0;
  _ZN6System13UnicodeStringC1EPKc(&local_b8,&DAT_006e05d9);
  bVar3 = _ZNK6System13UnicodeStringneERKS0_(local_b0,&local_b8);
  _ZN6System13UnicodeStringD1Ev(&local_b8);
  _ZN6System13UnicodeStringD1Ev();
  if (((bVar3 & 1) != 0) && (RemoveRescan != 0)) {
    local_50 = &local_c0;
    local_58 = &BootHWid;
    local_c0.Data = (char *)0x0;
    _ZN6System14AnsiStringBaseC2ERKNS_13UnicodeStringEi(local_50,&BootHWid,0);
    DisableEnableDevice((AnsiString)local_c0.Data,false);
    local_48 = &local_c0;
    System::AnsiStringT<0>::~AnsiStringT((AnsiStringT<0> *)local_48);
    local_38 = &local_c8;
    local_40 = &BootHWid;
    local_c8.Data = (char *)0x0;
    _ZN6System14AnsiStringBaseC2ERKNS_13UnicodeStringEi(local_38,&BootHWid,0);
    RemoveDevice((AnsiString)local_c8.Data);
    local_30 = &local_c8;
    System::AnsiStringT<0>::~AnsiStringT((AnsiStringT<0> *)local_30);
    local_24 = DelayMSec / 2;
    iStart_1 = GetTickCount();
    while (DVar4 = GetTickCount(), DVar4 - iStart_1 <= local_24) {
      _ZN3Vcl5Forms12TApplication15ProcessMessagesEv
                (*(undefined8 *)__indStub__ZN3Vcl5Forms11ApplicationE);
    }
    RescanDevice();
    local_1c = DelayMSec / 2;
    iStart_2 = GetTickCount();
    while (DVar4 = GetTickCount(), DVar4 - iStart_2 <= local_1c) {
      _ZN3Vcl5Forms12TApplication15ProcessMessagesEv
                (*(undefined8 *)__indStub__ZN3Vcl5Forms11ApplicationE);
    }
  }
  ConnectHub('\x01');
  _ZN3Vcl8Extctrls6TTimer10SetEnabledEb(this->Timer1,1);
  return;
}

