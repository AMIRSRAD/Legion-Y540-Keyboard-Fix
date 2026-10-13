
void _Z15cmd_erase_flashmt(undefined4 param_1,undefined2 param_2)

{
  undefined8 local_58;
  undefined8 uStack_50;
  undefined8 local_48;
  undefined8 uStack_40;
  undefined8 uStack_38;
  undefined7 uStack_30;
  undefined1 local_29;
  undefined7 uStack_28;
  undefined8 uStack_21;
  undefined2 local_e;
  undefined4 local_c;
  
  uStack_28 = 0;
  uStack_21 = 0;
  uStack_38 = 0;
  uStack_30 = 0;
  local_29 = 0;
  local_48 = 0;
  uStack_40 = 0;
  uStack_50 = 0;
  local_c._0_1_ = (undefined1)param_1;
  local_c._1_1_ = (undefined1)((uint)param_1 >> 8);
  local_c._2_1_ = (undefined1)((uint)param_1 >> 0x10);
  local_e._0_1_ = (undefined1)param_2;
  local_e._1_1_ = (undefined1)((ushort)param_2 >> 8);
  local_58 = (ulonglong)
             CONCAT15(local_e._1_1_,
                      CONCAT14((undefined1)local_e,
                               CONCAT13(local_c._2_1_,
                                        CONCAT12(local_c._1_1_,CONCAT11((undefined1)local_c,0xc2))))
                     );
  local_e = param_2;
  local_c = param_1;
  HidRequests(hFile[0],true,'\0',(UCHAR *)&local_58,'\x06');
  Sleep(5);
  return;
}

