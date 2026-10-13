
void FUN_CODE_3cc8(void)

{
  if (((((DAT_EXTMEM_2f41 & 1) == 0) && ((DAT_EXTMEM_2f41 >> 1 & 1) == 0)) &&
      ((DAT_EXTMEM_2f41 >> 2 & 1) == 0)) && ((DAT_EXTMEM_2f41 >> 3 & 1) == 0)) {
    return;
  }
  DAT_EXTMEM_2f64 = 1;
  return;
}

