
void FUN_CODE_6da3(void)

{
  char cVar1;
  
  cVar1 = '\0';
  do {
    **(undefined1 **)CONCAT11(0x6e,cVar1 * '\x03') =
         *(undefined1 *)
          CONCAT11('n' - (((0xfdU < (byte)(cVar1 * '\x03')) << 7) >> 7),cVar1 * '\x03' + 2);
    cVar1 = cVar1 + '\x01';
  } while (cVar1 != '\x0e');
  return;
}

