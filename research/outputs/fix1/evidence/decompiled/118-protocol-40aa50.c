
void _Z19cmd_read_from_flashmhPh(undefined4 param_1,byte param_2,void *param_3)

{
  undefined8 local_68;
  undefined8 uStack_60;
  undefined8 local_58;
  undefined8 uStack_50;
  undefined8 uStack_48;
  undefined7 uStack_40;
  undefined1 local_39;
  undefined7 uStack_38;
  undefined8 uStack_31;
  void *local_20;
  byte local_15;
  undefined4 local_14;
  
  uStack_38 = 0;
  uStack_31 = 0;
  uStack_48 = 0;
  uStack_40 = 0;
  local_39 = 0;
  local_58 = 0;
  uStack_50 = 0;
  uStack_60 = 0;
  local_14._0_1_ = (undefined1)param_1;
  local_14._1_1_ = (undefined1)((uint)param_1 >> 8);
  local_14._2_1_ = (undefined1)((uint)param_1 >> 0x10);
  local_68 = (ulonglong)
             CONCAT14(param_2,CONCAT13(local_14._2_1_,
                                       CONCAT12(local_14._1_1_,CONCAT11((undefined1)local_14,0xd1)))
                     );
  local_20 = param_3;
  local_15 = param_2;
  local_14 = param_1;
  HidRequests(hFile[0],true,'\0',(UCHAR *)&local_68,param_2 + 5);
  HidRequests(hFile[0],false,'\0',(UCHAR *)&local_68,local_15 + 5);
  memcpy(local_20,(void *)((longlong)&local_68 + 5),(ulonglong)local_15);
  return;
}

