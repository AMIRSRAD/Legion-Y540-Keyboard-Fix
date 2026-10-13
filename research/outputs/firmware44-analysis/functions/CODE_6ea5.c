
void FUN_CODE_6ea5(void)

{
  FUN_CODE_8391();
  if (DAT_EXTMEM_0892 != '\0') {
    DAT_EXTMEM_0892 = DAT_EXTMEM_0892 + -1;
  }
  if (DAT_EXTMEM_0893 != '\0') {
    DAT_EXTMEM_0893 = DAT_EXTMEM_0893 + -1;
  }
  if ((DAT_EXTMEM_0894 == '\0') && (DAT_EXTMEM_0892 == '\0')) {
    DAT_EXTMEM_1603 = DAT_EXTMEM_1603 & 0xfd;
  }
  if ((DAT_EXTMEM_0894 == '\0') && (DAT_EXTMEM_0893 == '\0')) {
    DAT_EXTMEM_1603 = DAT_EXTMEM_1603 & 0xfd;
  }
  return;
}

