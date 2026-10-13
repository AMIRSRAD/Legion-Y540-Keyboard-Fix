from pathlib import Path
p=Path('outputs/y540-research/src/protocol.c');s=p.read_text(encoding='utf-8-sig')
s=s.replace('uint8_t ids[2]={0,0x5a}','uint8_t ids[2]={0x5a,0}')
s=s.replace('int y540_check_boot_chip(y540_hid_transport*t,uint16_t expected,y540_hid_error*e){','int y540_check_boot_chip(y540_hid_transport*t,uint16_t expected,y540_hid_error*e){if(!expected)return 1;')
s=s.replace('size%1024||size<2048||size>0xffffu*1024u','size!=54u*1024u')
s=s.replace('Only aligned full-image profile at address zero is implemented','Only the supplied 54 KiB full-image Y540 profile at address zero is implemented')
s=s.replace('if(!y540_hid_open(&t,&sel,delay_ms,e)){','if(!y540_hid_open(&t,&sel,delay_ms,e)){\n  if(e && e->code!=ERROR_NOT_FOUND)return 0;')
s=s.replace('if(pass==30)return fail(e,"Keyboard did not reappear in boot mode");','if(pass==30)return fail(e,"Keyboard did not reappear in boot mode");')
s=s.replace('sel.usage_page=(uint16_t)page;sel.usage=(uint16_t)usage;', 'if(page>0xffff||usage>0xffff||chip>0xffff)return fail(e,"HID profile values exceed 16 bits");\n sel.usage_page=(uint16_t)page;sel.usage=(uint16_t)usage;')
# Braced early-return statements make ownership of following operations explicit.
import re
s=re.sub(r'if\(([^\n]+?)\)return ([^;\n]+);',r'if(\1){return \2;}',s)
s=re.sub(r'if\(([^\n]+?)\)break;',r'if(\1){break;}',s)
p.write_text(s,encoding='utf8')
