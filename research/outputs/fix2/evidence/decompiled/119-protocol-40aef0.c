
void read_flash(int offset,int send_len,BYTE *pDataBuf)

{
  int iVar1;
  byte bVar2;
  int cnt;
  int i;
  BYTE *pDataBuf_local;
  int send_len_local;
  int offset_local;
  UCHAR buffer [63];
  
  i = 0;
  cnt = 0;
  for (send_len_local = send_len; 0x38 < send_len_local; send_len_local = send_len_local + -0x38) {
    _ZN3Vcl8Comctrls12TProgressBar11SetPositionEi
              (Form1->ProgressBar1,(longlong)((i + 2) * 100) / (longlong)send_len_local & 0xffffffff
              );
    _ZN3Vcl5Forms12TApplication15ProcessMessagesEv
              (*(undefined8 *)__indStub__ZN3Vcl5Forms11ApplicationE);
    iVar1 = offset + cnt;
    memset(buffer,0,0x3f);
    buffer[0] = 0xd1;
    buffer[1] = (UCHAR)iVar1;
    buffer[2] = (UCHAR)((uint)iVar1 >> 8);
    buffer[3] = (UCHAR)((uint)iVar1 >> 0x10);
    buffer[4] = '8';
    HidRequests(hFile[0],true,'\0',buffer,'=');
    HidRequests(hFile[0],false,'\0',buffer,'=');
    memcpy(pDataBuf + cnt,buffer + 5,0x38);
    cnt = cnt + 0x38;
    i = i + 1;
  }
  if (0 < send_len_local) {
    iVar1 = offset + cnt;
    bVar2 = (byte)send_len_local;
    memset(buffer,0,0x3f);
    buffer[0] = 0xd1;
    buffer[1] = (UCHAR)iVar1;
    buffer[2] = (UCHAR)((uint)iVar1 >> 8);
    buffer[3] = (UCHAR)((uint)iVar1 >> 0x10);
    buffer[4] = bVar2;
    HidRequests(hFile[0],true,'\0',buffer,bVar2 + 5);
    HidRequests(hFile[0],false,'\0',buffer,bVar2 + 5);
    memcpy(pDataBuf + cnt,buffer + 5,(ulonglong)bVar2);
  }
  return;
}

