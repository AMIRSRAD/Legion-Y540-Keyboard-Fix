
void cmd_set_data(WORD offset,BYTE len,BYTE *pDataBuffer)

{
  UCHAR buffer [63];
  BYTE *pDataBuffer_local;
  BYTE len_local;
  WORD offset_local;
  
  memcpy(pRAMBuffer + (int)(uint)offset,pDataBuffer,(ulonglong)len);
  memset(buffer,0,0x3f);
  buffer[0] = 0xc1;
  buffer[3] = len;
  buffer._1_2_ = offset;
  memcpy(buffer + 4,pDataBuffer,(ulonglong)len);
  HidRequests(hFile[0],true,'\0',buffer,len + '\x04');
  if (WriteFlashDataDelay != 0) {
    Sleep(WriteFlashDataDelay);
  }
  return;
}

