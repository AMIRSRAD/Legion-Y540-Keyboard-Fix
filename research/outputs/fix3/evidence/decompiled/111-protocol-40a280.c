
bool HidCustomCmdInit(UCHAR IsEnable)

{
  TStrings *pTVar1;
  _func_int *p_Var2;
  UCHAR UVar3;
  int iVar4;
  undefined8 local_50;
  undefined8 local_48;
  BYTE ReceiveKey [15];
  BYTE gpHidCustomCmdInitKey [15];
  UCHAR IsEnable_local;
  
  gpHidCustomCmdInitKey._0_8_ = s_ITE_Tech__Inc__006e0398._0_8_;
  gpHidCustomCmdInitKey._8_4_ = s_ITE_Tech__Inc__006e0398._8_4_;
  gpHidCustomCmdInitKey._12_2_ = s_ITE_Tech__Inc__006e0398._12_2_;
  gpHidCustomCmdInitKey[0xe] = s_ITE_Tech__Inc__006e0398[0xe];
  memset(ReceiveKey,0,0xf);
  UVar3 = ITEReportID;
  if (hFile[MainIndex] == (HANDLE)0x0) {
    return false;
  }
  pTVar1 = (Form1->Memo2->super_TCustomMemo).FLines;
  p_Var2 = (pTVar1->super_TPersistent).super_TObject._vptr_TObject[0xf];
  memset(&local_50,0,8);
  local_50 = 0;
  _ZN6System8Sysutils8IntToStrEi(&local_50,UVar3);
  memset(&local_48,0,8);
  local_48 = 0;
  _ZN6SystemplEPKcRKNS_13UnicodeStringE(&local_48,s_ITEReportID__006e03a7,&local_50);
  (*p_Var2)(pTVar1,local_48);
  _ZN6System13UnicodeStringD1Ev(&local_48);
  _ZN6System13UnicodeStringD1Ev(&local_50);
  HidRequests(hFile[MainIndex],true,ITEReportID,gpHidCustomCmdInitKey,'\x0f');
  Sleep(100);
  HidRequests(hFile[MainIndex],false,ITEReportID,ReceiveKey,'\x0f');
  Sleep(100);
  iVar4 = memcmp(gpHidCustomCmdInitKey,ReceiveKey,0xf);
  if (((iVar4 != 0) && (IsEnable == '\x01')) ||
     ((iVar4 = memcmp(gpHidCustomCmdInitKey,ReceiveKey,0xf), iVar4 == 0 && (IsEnable == '\0')))) {
    HidRequests(hFile[MainIndex],true,ITEReportID,gpHidCustomCmdInitKey,'\x0f');
    Sleep(100);
    HidRequests(hFile[MainIndex],false,ITEReportID,ReceiveKey,'\x0f');
  }
  Sleep(100);
  iVar4 = memcmp(gpHidCustomCmdInitKey,ReceiveKey,0xf);
  if (((iVar4 != 0) || (IsEnable != '\x01')) &&
     ((iVar4 = memcmp(gpHidCustomCmdInitKey,ReceiveKey,0xf), iVar4 == 0 || (IsEnable != '\0')))) {
    return false;
  }
  return true;
}

