"""Offline model of CalculateWordCheckSum at updater VA 0x40b260.
Derived from REA pseudocode, not vendor source. No hardware or updater execution.
"""
from pathlib import Path
import argparse,configparser,json

def calculate(data,start,end,high,low,invert,last_ff=0):
    if not (0<=start<=end<=len(data) and 0<=high<len(data) and 0<=low<len(data) and high!=low and 0<=last_ff<=end):
        raise ValueError('Invalid byte range/checksum fields')
    total=0
    for i in range(start,end):
        if 0x80<=i<=0x8f:continue
        value=255 if i in (high,low) or (last_ff and i>=end-last_ff) else data[i]
        total=(total+value)&0xffff
    stored=(data[high]<<8)|data[low]
    computed=(-total)&0xffff if invert else total
    return {'sum':total,'stored':stored,'computed':computed,'residual':(computed+stored)&0xffff}

if __name__=='__main__':
    root=Path(__file__).resolve().parents[1]
    p=argparse.ArgumentParser(description=__doc__);p.add_argument('firmware',nargs='?',default=str(root/'samples'/'44.bin'));p.add_argument('--ini',default=str(root/'samples'/'SHFU.ini'));a=p.parse_args()
    cfg=configparser.ConfigParser();cfg.read_string(Path(a.ini).read_bytes().decode('ascii',errors='replace'));n=cfg['NEWVERSION']
    r=calculate(Path(a.firmware).read_bytes(),int(n['CHECKSUMSTARTADDRESS'],16),int(n['CHECKSUMENDADDRESS'],16),int(n['CHECKSUMVALUEHIGHADDRESS'],16),int(n['CHECKSUMVALUELOWADDRESS'],16),bool(int(n['CHECKSUMINVERT'])),int(n.get('CHECKSUMLASTBYTESBEFF','0')))
    print(json.dumps(r,indent=2))
