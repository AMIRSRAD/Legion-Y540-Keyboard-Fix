
BOOL WinDebugReadRegByteForBootcode
               (int IndexHighByte,int IndexMiddleByte,int IndexLowByte,UCHAR *RegData)

{
  BOOLEAN BVar1;
  int i;
  UCHAR FailCnt;
  UCHAR count;
  UCHAR buffer [16];
  UCHAR *RegData_local;
  int IndexLowByte_local;
  int IndexMiddleByte_local;
  int IndexHighByte_local;
  
  memset(buffer,0,0x10);
  FailCnt = '\0';
  if (IndexHighByte == 0xf0) {
    buffer[0] = '\a';
  }
  else {
    buffer[0] = '\x05';
  }
  i = 0;
  while( true ) {
    if (999 < i) {
      return 1;
    }
    if (100 < FailCnt) break;
    buffer[1] = (UCHAR)IndexLowByte;
    buffer[2] = (UCHAR)IndexMiddleByte;
    buffer[3] = (UCHAR)IndexHighByte;
    buffer[4] = '\x03';
    BVar1 = HidRequests(hFile[0],true,'\0',buffer,'\x05');
    if ((((BVar1 != '\0') && (BVar1 = HidRequests(hFile[0],false,'\0',buffer,'\b'), BVar1 != '\0'))
        && ((uint)buffer[1] == (IndexLowByte & 0xffU))) &&
       ((((uint)buffer[2] == (IndexMiddleByte & 0xffU) &&
         ((uint)buffer[3] == (IndexHighByte & 0xffU))) && (buffer[4] == '\x03')))) {
      memcpy(RegData,buffer + 5,3);
      return 1;
    }
    FailCnt = FailCnt + '\x01';
    i = i + 3;
  }
  return 0;
}

