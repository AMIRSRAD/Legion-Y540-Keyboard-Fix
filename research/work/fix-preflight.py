from pathlib import Path
p=Path('outputs/y540-research/src/protocol.c');s=p.read_text(encoding='utf8')
s=s.replace('number(c,"OPTION","REPORTID",16,0x5a,&report,e)','number(c,"MAIN","REPORTID",10,0x5a,&report,e)')
needle='uint32_t same,pidcheck,report,retry,wait,wd,oem,page,usage,chip;'
addition='''uint32_t same,pidcheck,report,retry,wait,wd,oem,page,usage,chip;
 struct numeric_option {const char*section;const char*key;int base;uint32_t fallback,max;} options[]={
 {"DEVICE","NEEDERASE",10,1,1}, {"OPTION","NOCHECKIVT",10,0,1},
 {"OPTION","PROGRAMFAILERASESKIPFIRST1K",10,0,1}, {"OPTION","PROGRAMFAILERASETHENRESET",10,0,1},
 {"OPTION","ALLHIDCOMMANDDELAY",10,5,60000}, {"DEVICE","MAININDEX",10,0,0},
 {"NEWVERSION","MAINDEVICEUPID",16,0xff89,0xffff}, {"NEWVERSION","MAINDEVICEUID",16,0x0010,0xffff}
 };
 for(size_t oi=0;oi<sizeof(options)/sizeof(options[0]);oi++){uint32_t value;
 if(!number(c,options[oi].section,options[oi].key,options[oi].base,options[oi].fallback,&value,e)){return 0;}
 if(value>options[oi].max){return fail(e,"Unsupported profile option range");}}
'''
s=s.replace(needle,addition)
s=s.replace(' y540_hid_transport t={0};y540_hid_selector sel={0};',' y540_hid_error local_error={0};if(!e)e=&local_error;\n y540_hid_transport t={0};y540_hid_selector sel={0};')
p.write_text(s,encoding='utf8')
