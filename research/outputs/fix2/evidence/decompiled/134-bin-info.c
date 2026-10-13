
/* DWARF original prototype: void GetBinFileInfo(TForm1 * this, TObject * Sender) */

void __thiscall TForm1::GetBinFileInfo(TForm1 *this,TObject *Sender)

{
  TStrings *pTVar1;
  _func_int *p_Var2;
  int iVar3;
  undefined4 extraout_var;
  void *pvVar4;
  undefined8 local_f8;
  undefined8 local_f0;
  int i_1;
  char oemver_src [34];
  char ver_src [34];
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
  TObject *Sender_local;
  TForm1 *this_local;
  
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
  iVar3 = (**(msUpdateBINBuffer->super_TCustomMemoryStream).super_TStream.super_TObject.
             _vptr_TObject)();
  if (CONCAT44(extraout_var,iVar3) != 0) {
    iVar3 = (**(msUpdateBINBuffer->super_TCustomMemoryStream).super_TStream.super_TObject.
               _vptr_TObject)(msUpdateBINBuffer);
    pvVar4 = calloc((longlong)(iVar3 * 2),1);
    for (i_1 = 0; i_1 < iVar3; i_1 = i_1 + 1) {
      *(undefined1 *)((longlong)pvVar4 + (longlong)i_1) =
           *(undefined1 *)
            ((longlong)(msUpdateBINBuffer->super_TCustomMemoryStream).FMemory + (longlong)i_1);
    }
    memcpy(oemver_src,(void *)((longlong)pvVar4 + (longlong)OemVerOffset),0x20);
    pTVar1 = (Form1->Memo1->super_TCustomMemo).FLines;
    p_Var2 = (pTVar1->super_TPersistent).super_TObject._vptr_TObject[0xf];
    local_f0 = 0;
    _ZN6System13UnicodeStringC1EPKc(&local_f0,&DAT_006e0293);
    (*p_Var2)(pTVar1,local_f0);
    _ZN6System13UnicodeStringD1Ev(&local_f0);
    System::AnsiStringT<0>::printf(&stPrint,s_New_Firmware_Version___s_006e0581);
    pTVar1 = (Form1->Memo1->super_TCustomMemo).FLines;
    p_Var2 = (pTVar1->super_TPersistent).super_TObject._vptr_TObject[0xf];
    local_f8 = 0;
    _ZN6System8Internal7Strhlpr15UnicodeFromAnsiERNS_13UnicodeStringERNS_11AnsiStringTILt65535EEE
              (&local_f8,&stPrint);
    (*p_Var2)(pTVar1,local_f8);
    _ZN6System13UnicodeStringD1Ev(&local_f8);
  }
  System::AnsiStringT<0>::~AnsiStringT(&stPrint);
  return;
}

