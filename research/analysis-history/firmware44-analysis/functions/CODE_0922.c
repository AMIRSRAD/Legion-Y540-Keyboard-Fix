
void thunk_FUN_CODE_6f32(void)

{
  if (DAT_EXTMEM_0802 == '\x01') {
    FUN_CODE_1b56(0,0x57);
    DAT_EXTMEM_0802 = 2;
    return;
  }
  if (DAT_EXTMEM_0802 == '\x02') {
    FUN_CODE_1b56(1,0x57);
    DAT_EXTMEM_0802 = '\0';
  }
  return;
}

