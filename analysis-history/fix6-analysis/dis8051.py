"""Minimal 8051 disassembler (for reading the Y540 firmware). Usage: dis8051.py IMAGE START END"""
import sys
R=lambda n:'R%d'%n
def build():
    t={}
    ops=[('NOP',1)]
    t[0x00]=('NOP',1)
    # AJMP/ACALL
    for i in range(8):
        t[0x01+i*0x20]=('AJMP a11',2); t[0x11+i*0x20]=('ACALL a11',2)
    t[0x02]=('LJMP a16',3); t[0x12]=('LCALL a16',3); t[0x22]=('RET',1); t[0x32]=('RETI',1)
    t[0x03]=('RR A',1);t[0x13]=('RRC A',1);t[0x23]=('RL A',1);t[0x33]=('RLC A',1)
    t[0x04]=('INC A',1);t[0x14]=('DEC A',1);t[0x05]=('INC dir',2);t[0x15]=('DEC dir',2)
    t[0x06]=('INC @R0',1);t[0x07]=('INC @R1',1);t[0x16]=('DEC @R0',1);t[0x17]=('DEC @R1',1)
    for i in range(8): t[0x08+i]=('INC R%d'%i,1); t[0x18+i]=('DEC R%d'%i,1)
    t[0x10]=('JBC bit,rel',3);t[0x20]=('JB bit,rel',3);t[0x30]=('JNB bit,rel',3);t[0x40]=('JC rel',2);t[0x50]=('JNC rel',2);t[0x60]=('JZ rel',2);t[0x70]=('JNZ rel',2);t[0x80]=('SJMP rel',2)
    t[0x24]=('ADD A,#imm',2);t[0x25]=('ADD A,dir',2);t[0x26]=('ADD A,@R0',1);t[0x27]=('ADD A,@R1',1)
    t[0x34]=('ADDC A,#imm',2);t[0x35]=('ADDC A,dir',2);t[0x36]=('ADDC A,@R0',1);t[0x37]=('ADDC A,@R1',1)
    t[0x44]=('ORL A,#imm',2);t[0x45]=('ORL A,dir',2);t[0x46]=('ORL A,@R0',1);t[0x47]=('ORL A,@R1',1)
    t[0x54]=('ANL A,#imm',2);t[0x55]=('ANL A,dir',2);t[0x56]=('ANL A,@R0',1);t[0x57]=('ANL A,@R1',1)
    t[0x64]=('XRL A,#imm',2);t[0x65]=('XRL A,dir',2);t[0x66]=('XRL A,@R0',1);t[0x67]=('XRL A,@R1',1)
    for i in range(8):
        t[0x28+i]=('ADD A,R%d'%i,1);t[0x38+i]=('ADDC A,R%d'%i,1);t[0x48+i]=('ORL A,R%d'%i,1);t[0x58+i]=('ANL A,R%d'%i,1);t[0x68+i]=('XRL A,R%d'%i,1)
        t[0x78+i]=('MOV R%d,#imm'%i,2);t[0x88+i]=('MOV dir,R%d'%i,2);t[0xA8+i]=('MOV R%d,dir'%i,2);t[0xB8+i]=('CJNE R%d,#imm,rel'%i,3);t[0xC8+i]=('XCH A,R%d'%i,1);t[0xD8+i]=('DJNZ R%d,rel'%i,2)
        t[0xE8+i]=('MOV A,R%d'%i,1);t[0xF8+i]=('MOV R%d,A'%i,1);t[0x98+i]=('SUBB A,R%d'%i,1)
    t[0x42]=('ORL dir,A',2);t[0x43]=('ORL dir,#imm',3);t[0x52]=('ANL dir,A',2);t[0x53]=('ANL dir,#imm',3);t[0x62]=('XRL dir,A',2);t[0x63]=('XRL dir,#imm',3)
    t[0x72]=('ORL C,bit',2);t[0x82]=('ANL C,bit',2);t[0x92]=('MOV bit,C',2);t[0xA0]=('ORL C,/bit',2);t[0xB0]=('ANL C,/bit',2);t[0xA2]=('MOV C,bit',2)
    t[0x73]=('JMP @A+DPTR',1);t[0x74]=('MOV A,#imm',2);t[0x75]=('MOV dir,#imm',3);t[0x76]=('MOV @R0,#imm',2);t[0x77]=('MOV @R1,#imm',2)
    t[0x83]=('MOVC A,@A+PC',1);t[0x93]=('MOVC A,@A+DPTR',1);t[0x84]=('DIV AB',1);t[0xA4]=('MUL AB',1)
    t[0x85]=('MOV dir,dir',3);t[0x86]=('MOV dir,@R0',2);t[0x87]=('MOV dir,@R1',2)
    t[0x90]=('MOV DPTR,#imm16',3);t[0xA3]=('INC DPTR',1)
    t[0x94]=('SUBB A,#imm',2);t[0x95]=('SUBB A,dir',2);t[0x96]=('SUBB A,@R0',1);t[0x97]=('SUBB A,@R1',1)
    t[0xA6]=('MOV @R0,dir',2);t[0xA7]=('MOV @R1,dir',2)
    t[0xB2]=('CPL bit',2);t[0xB3]=('CPL C',1);t[0xB4]=('CJNE A,#imm,rel',3);t[0xB5]=('CJNE A,dir,rel',3);t[0xB6]=('CJNE @R0,#imm,rel',3);t[0xB7]=('CJNE @R1,#imm,rel',3)
    t[0xC0]=('PUSH dir',2);t[0xC2]=('CLR bit',2);t[0xC3]=('CLR C',1);t[0xC4]=('SWAP A',1);t[0xC5]=('XCH A,dir',2);t[0xC6]=('XCH A,@R0',1);t[0xC7]=('XCH A,@R1',1)
    t[0xD0]=('POP dir',2);t[0xD2]=('SETB bit',2);t[0xD3]=('SETB C',1);t[0xD4]=('DA A',1);t[0xD5]=('DJNZ dir,rel',3);t[0xD6]=('XCHD A,@R0',1);t[0xD7]=('XCHD A,@R1',1)
    t[0xE0]=('MOVX A,@DPTR',1);t[0xE2]=('MOVX A,@R0',1);t[0xE3]=('MOVX A,@R1',1);t[0xE4]=('CLR A',1);t[0xE5]=('MOV A,dir',2);t[0xE6]=('MOV A,@R0',1);t[0xE7]=('MOV A,@R1',1)
    t[0xF0]=('MOVX @DPTR,A',1);t[0xF2]=('MOVX @R0,A',1);t[0xF3]=('MOVX @R1,A',1);t[0xF4]=('CPL A',1);t[0xF5]=('MOV dir,A',2);t[0xF6]=('MOV @R0,A',1);t[0xF7]=('MOV @R1,A',1)
    t[0xA5]=('???',1)
    return t
T=build()
def dis(b,a,end):
    while a<end:
        o=b[a]; m,n=T.get(o,('???',1))
        raw=b[a:a+n]; s=m
        if 'a16' in m: s=m.replace('a16','%04x'%(raw[1]<<8|raw[2]))
        elif 'a11' in m: s=m.replace('a11','%04x'%(((a+2)&0xF800)|((o>>5)<<8)|raw[1]))
        elif 'imm16' in m: s=m.replace('imm16','%04x'%(raw[1]<<8|raw[2]))
        elif m=='MOV dir,dir': s='MOV %02x,%02x'%(raw[2],raw[1])
        else:
            if 'rel' in m:
                rel=raw[-1]-256 if raw[-1]>127 else raw[-1]; s=s.replace('rel','%04x'%(a+n+rel))
            if 'dir' in m: s=s.replace('dir','%02x'%raw[1],1)
            if 'bit' in m: s=s.replace('bit','bit%02x'%raw[1],1)
            if 'imm' in m: s=s.replace('imm','%02x'%raw[2 if n==3 and 'dir' in m else (2 if 'CJNE' in m else 1)])
        print('%04x  %-8s %s'%(a,raw.hex(),s)); a+=n
if __name__=='__main__':
    b=open(sys.argv[1],'rb').read(); dis(b,int(sys.argv[2],16),int(sys.argv[3],16))
