
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

int cmd_get_buffer_checksum(void)

{
  ushort uVar1;
  UCHAR buffer [63];
  int i;
  WORD checksum1;
  WORD checksum0;
  
  memset(buffer,0,0x3f);
  buffer[0] = 0xd0;
  HidRequests(hFile[0],true,'\0',buffer,'\x01');
  checksum0 = 0;
  for (i = 0; (uint)i < 0x400; i = i + 1) {
    checksum0 = checksum0 + pRAMBuffer[i];
  }
  HidRequests(hFile[0],false,'\0',buffer,'\x03');
  uVar1 = (ushort)buffer[1] + (ushort)buffer[2] * 0x100;
  if ((uint)checksum0 - (uint)uVar1 != 0) {
    printf(s_Checksum0___d__Xh__Checksum1___d_006e03b4,(ulonglong)checksum0,(ulonglong)checksum0,
           (ulonglong)uVar1,(uint)uVar1);
  }
  return (uint)checksum0 - (uint)uVar1;
}

