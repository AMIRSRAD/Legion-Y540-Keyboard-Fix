
BOOLEAN HidRequests(HANDLE file,bool WriteFlag,UCHAR ReportId,UCHAR *Data,UCHAR DataSize)

{
  TStrings *pTVar1;
  _func_int *p_Var2;
  char cVar3;
  DWORD DVar4;
  undefined8 local_98;
  undefined8 local_90 [3];
  undefined8 local_78;
  undefined8 local_70;
  int i;
  BOOLEAN HIDCMDStatus;
  ULONG bufferSize;
  PHIDMINI_CONTROL_INFO3 controlInfo;
  UCHAR DataSize_local;
  UCHAR *Data_local;
  UCHAR ReportId_local;
  bool WriteFlag_local;
  HANDLE file_local;
  undefined8 *local_28;
  undefined8 *local_20;
  undefined8 *local_18;
  undefined8 *local_10;
  
  DataSize_local = DataSize;
  Data_local = Data;
  ReportId_local = ReportId;
  WriteFlag_local = WriteFlag;
  file_local = file;
  if (AllHidCommandDelay != 0) {
    Sleep(AllHidCommandDelay);
  }
  i = 0;
  while( true ) {
    if (9 < i) {
      return HIDCMDStatus;
    }
    controlInfo = (PHIDMINI_CONTROL_INFO3)0x0;
    HIDCMDStatus = '\x01';
    bufferSize = 0x40;
    controlInfo = (PHIDMINI_CONTROL_INFO3)malloc(0x40);
    if (controlInfo == (PHIDMINI_CONTROL_INFO3)0x0) {
      HIDCMDStatus = '\0';
    }
    controlInfo->ReportId = ReportId_local;
    if (HIDCMDStatus != '\0') {
      if ((WriteFlag_local & 1U) == 0) {
        cVar3 = HidD_GetFeature(file_local,controlInfo,bufferSize);
        if (cVar3 == '\0') {
          HIDCMDStatus = '\0';
          pTVar1 = (Form1->Memo2->super_TCustomMemo).FLines;
          p_Var2 = (pTVar1->super_TPersistent).super_TObject._vptr_TObject[0xf];
          DVar4 = GetLastError();
          memset(&local_98,0,8);
          local_98 = 0;
          local_10 = &local_98;
          _ZN6System8Sysutils8IntToStrEi(&local_98,DVar4);
          memset(local_90,0,8);
          local_90[0] = 0;
          local_18 = local_90;
          _ZN6SystemplEPKcRKNS_13UnicodeStringE
                    (local_90,s_failed_HidD_GetFeature___006e037e,&local_98);
          (*p_Var2)(pTVar1,local_90[0]);
          _ZN6System13UnicodeStringD1Ev(local_90);
          _ZN6System13UnicodeStringD1Ev(&local_98);
          Sleep(100);
        }
        memcpy(Data_local,controlInfo + 1,(ulonglong)DataSize_local);
      }
      else {
        memcpy(controlInfo + 1,Data_local,(ulonglong)DataSize_local);
        cVar3 = HidD_SetFeature(file_local,controlInfo,bufferSize);
        if (cVar3 == '\0') {
          HIDCMDStatus = '\0';
          pTVar1 = (Form1->Memo2->super_TCustomMemo).FLines;
          p_Var2 = (pTVar1->super_TPersistent).super_TObject._vptr_TObject[0xf];
          DVar4 = GetLastError();
          memset(&local_78,0,8);
          local_78 = 0;
          local_28 = &local_78;
          _ZN6System8Sysutils8IntToStrEi(&local_78,DVar4);
          memset(&local_70,0,8);
          local_70 = 0;
          local_20 = &local_70;
          _ZN6SystemplEPKcRKNS_13UnicodeStringE
                    (&local_70,s_failed_HidD_SetFeature___006e0364,&local_78);
          (*p_Var2)(pTVar1,local_70);
          _ZN6System13UnicodeStringD1Ev(&local_70);
          _ZN6System13UnicodeStringD1Ev(&local_78);
          Sleep(100);
        }
      }
    }
    free(controlInfo);
    if (HIDCMDStatus != '\0') break;
    i = i + 1;
  }
  return HIDCMDStatus;
}

