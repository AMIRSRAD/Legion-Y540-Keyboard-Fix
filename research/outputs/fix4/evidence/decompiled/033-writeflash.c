
void write_flash(int addr,int send_len,BYTE *pDataBuf)

{
  int iVar1;
  int iVar2;
  int local_4bc;
  BYTE dummy_data [1024];
  int i;
  int sect_cnt;
  int offset;
  int tmp_len;
  BYTE *pDataBuf_local;
  int send_len_local;
  int addr_local;
  UCHAR buffer [63];
  
  memset(dummy_data,0xff,0x400);
  iVar2 = send_len / 0x400 + (uint)(0 < send_len % 0x400);
  i = 0;
  send_len_local = send_len;
  do {
    if (iVar2 <= i) {
      return;
    }
    if (((PassOrWriteFirst1K != '\x01') || (i != 0)) && ((PassOrWriteFirst1K != '\x02' || (i == 0)))
       ) {
      _ZN3Vcl8Comctrls12TProgressBar11SetPositionEi
                (Form1->ProgressBar1,(longlong)((i + 1) * 100) / (longlong)iVar2 & 0xffffffff);
      _ZN3Vcl5Forms12TApplication15ProcessMessagesEv
                (*(undefined8 *)__indStub__ZN3Vcl5Forms11ApplicationE);
      iVar1 = memcmp(dummy_data,pDataBuf + (i << 10),0x400);
      if (iVar1 != 0) {
        memset(pRAMBuffer,0xff,0x400);
        memset(buffer,0,0x3f);
        buffer[0] = 0xc0;
        HidRequests(hFile[0],true,'\0',buffer,'\x01');
        if (send_len_local < 0x401) {
          local_4bc = send_len_local;
        }
        else {
          local_4bc = 0x400;
        }
        offset = 0;
        for (tmp_len = local_4bc; 0x39 < tmp_len; tmp_len = tmp_len + -0x39) {
          cmd_set_data((WORD)offset,'9',pDataBuf + (longlong)offset + (longlong)(i << 10));
          offset = offset + 0x39;
        }
        if (0 < tmp_len) {
          cmd_set_data((WORD)offset,(BYTE)tmp_len,pDataBuf + (longlong)offset + (longlong)(i << 10))
          ;
        }
        iVar1 = cmd_get_buffer_checksum();
        if (iVar1 != 0) {
          return;
        }
        iVar1 = addr + i * 0x400;
        memset(buffer,0,0x3f);
        buffer[0] = 0xc3;
        buffer[1] = (UCHAR)iVar1;
        buffer[2] = (UCHAR)((uint)iVar1 >> 8);
        buffer[3] = (UCHAR)((uint)iVar1 >> 0x10);
        buffer[4] = '\0';
        buffer[5] = '\x04';
        HidRequests(hFile[0],true,'\0',buffer,'\x06');
        Sleep(5);
      }
    }
    send_len_local = send_len_local + -0x400;
    i = i + 1;
  } while( true );
}

