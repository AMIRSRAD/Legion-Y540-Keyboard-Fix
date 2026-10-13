
char FUN_CODE_866a(char param_1,undefined2 param_2,byte param_3,char param_4,char param_5,
                  char param_6)

{
  byte bVar1;
  byte *pbVar2;
  char cVar3;
  char *pcVar4;
  byte bVar5;
  char *pcVar6;
  
  if (param_6 == '\x01') {
    cVar3 = FUN_CODE_85db(param_1);
    return cVar3;
  }
  cVar3 = (char)param_2;
  if (param_6 == '\0') {
    pcVar4 = (char *)(cVar3 + param_4);
    pbVar2 = (byte *)(pcVar4 + '\x01');
    bVar1 = *pbVar2;
    *pbVar2 = param_3 + *pbVar2;
    param_1 = param_1 + (*pcVar4 - ((CARRY1(param_3,bVar1) << 7) >> 7));
    *pcVar4 = param_1;
    return param_1;
  }
  if (param_6 == -2) {
    bVar5 = cVar3 + param_4;
    bVar1 = *(byte *)(ushort)(bVar5 + 1);
    *(byte *)(ushort)(bVar5 + 1) = bVar1 + param_3;
    cVar3 = *(char *)(ushort)bVar5 + (param_1 - ((CARRY1(bVar1,param_3) << 7) >> 7));
    *(char *)(ushort)bVar5 = cVar3;
    return cVar3;
  }
  pcVar6 = (char *)CONCAT11((char)((ushort)param_2 >> 8) + param_5,cVar3 + param_4);
  return *pcVar6 + (param_1 - ((CARRY1(pcVar6[1],param_3) << 7) >> 7));
}

