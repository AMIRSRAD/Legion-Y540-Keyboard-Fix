
UINT16 CalculateWordCheckSum
                 (BYTE *pBuffer,UINT32 p_start_addr,UINT32 p_end_addr,UINT32 p_checksum_H,
                 UINT32 p_checksum_L,BOOL InvertCheckSum)

{
  TStrings *pTVar1;
  _func_int *p_Var2;
  WORD WVar3;
  undefined8 local_c0;
  undefined8 local_b8 [3];
  undefined8 local_a0;
  undefined8 local_98;
  undefined8 local_90;
  undefined8 local_88;
  BYTE *pData;
  WORD l_original_checksum;
  WORD Show_checksum;
  WORD l_checksum;
  DWORD l_address_index;
  BOOL InvertCheckSum_local;
  UINT32 p_checksum_L_local;
  UINT32 p_checksum_H_local;
  UINT32 p_end_addr_local;
  UINT32 p_start_addr_local;
  BYTE *pBuffer_local;
  undefined8 *local_48;
  undefined8 *local_40;
  undefined8 *local_38;
  undefined8 *local_30;
  undefined8 *local_28;
  
  p_checksum_L_local = p_checksum_L;
  InvertCheckSum_local = InvertCheckSum;
  l_checksum = 0;
  for (l_address_index = p_start_addr; l_address_index < p_end_addr;
      l_address_index = l_address_index + 1) {
    pData = pBuffer + l_address_index;
    if ((l_address_index < 0x80) || (0x8f < l_address_index)) {
      if (l_address_index == p_checksum_H) {
        l_checksum = l_checksum + 0xff;
      }
      else if (l_address_index == p_checksum_L) {
        l_checksum = l_checksum + 0xff;
      }
      else if (((l_address_index < p_end_addr - CheckSum_LastBytesBeFF) ||
               (p_end_addr < l_address_index)) || (CheckSum_LastBytesBeFF == 0)) {
        l_checksum = l_checksum + *pData;
      }
      else {
        l_checksum = l_checksum + 0xff;
      }
    }
  }
  if (InvertCheckSum != 0) {
    l_checksum = (l_checksum ^ 0xffff) + 1;
  }
  Show_checksum = (l_checksum ^ 0xffff) + 1;
  WVar3 = (ushort)pBuffer[p_checksum_H] * 0x100 + (ushort)pBuffer[p_checksum_L];
  pTVar1 = (Form1->Memo2->super_TCustomMemo).FLines;
  p_Var2 = (pTVar1->super_TPersistent).super_TObject._vptr_TObject[0xf];
  l_original_checksum = WVar3;
  p_checksum_H_local = p_checksum_H;
  p_end_addr_local = p_end_addr;
  p_start_addr_local = p_start_addr;
  pBuffer_local = pBuffer;
  memset(&local_a0,0,8);
  local_a0 = 0;
  local_48 = &local_a0;
  _ZN6System8Sysutils8IntToHexEii(&local_a0,WVar3,4);
  memset(&local_98,0,8);
  local_98 = 0;
  local_40 = &local_98;
  _ZN6SystemplEPKcRKNS_13UnicodeStringE(&local_98,s_CheckSum__006e03db,&local_a0);
  local_b8[0] = 0;
  _ZN6System13UnicodeStringC1EPKc(local_b8,s___Calculate__006e03e5);
  memset(&local_90,0,8);
  local_90 = 0;
  local_28 = &local_90;
  _ZNK6System13UnicodeStringplERKS0_(&local_98,&local_90,local_b8);
  WVar3 = Show_checksum;
  memset(&local_c0,0,8);
  local_c0 = 0;
  local_30 = &local_c0;
  _ZN6System8Sysutils8IntToHexEii(&local_c0,WVar3,4);
  memset(&local_88,0,8);
  local_88 = 0;
  local_38 = &local_88;
  _ZNK6System13UnicodeStringplERKS0_(&local_90,&local_88,&local_c0);
  (*p_Var2)(pTVar1,local_88);
  _ZN6System13UnicodeStringD1Ev(&local_88);
  _ZN6System13UnicodeStringD1Ev(&local_c0);
  _ZN6System13UnicodeStringD1Ev(&local_90);
  _ZN6System13UnicodeStringD1Ev(local_b8);
  _ZN6System13UnicodeStringD1Ev(&local_98);
  _ZN6System13UnicodeStringD1Ev(&local_a0);
  return l_checksum + l_original_checksum;
}

