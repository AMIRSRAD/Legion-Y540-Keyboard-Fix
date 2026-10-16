"""Verify disassembly bytes and record bounded firmware audit facts offline."""
from pathlib import Path
import json, hashlib

root=Path(__file__).resolve().parents[1]
source=root.parent/'y540-research/samples/44.bin'
raw=source.read_bytes()
export=json.loads((root/'ghidra-static-inline-aware.json').read_text(encoding='utf-8'))
mismatches=[]
covered=set()
for instruction in export['instructions']:
    offset=int(instruction['address'].split(':')[1],16)
    decoded=bytes.fromhex(instruction['bytes'])
    if raw[offset:offset+len(decoded)]!=decoded:
        mismatches.append(instruction['address'])
    covered.update(range(offset,offset+len(decoded)))
assert not mismatches
assert hashlib.sha256(raw).hexdigest()=='3afec131c6ed70efa0a3f4b601cb799011a582835d371c57fef68af48519e359'
init=json.loads((root/'initializer.json').read_text())
model=(root/'initializer-xdata-model.bin').read_bytes()
assert model[0x975:0x987]==raw[0x5307:0x5319]
checksum={}
for end in [0x8000,0xd800]:
    checksum[hex(end)]={'candidate_sum_with_checksum_slots_ff':hex((sum(raw[0x400:end])-sum(raw[0x7ffe:0x8000])+510)&0xffff)}
facts={
 'source':str(source.resolve()),'source_size':len(raw),'source_sha256':hashlib.sha256(raw).hexdigest(),
 'disassembler':'Ghidra12.1.4,8051:BE:16:default,raw CODE base0',
 'export':str((root/'ghidra-static-inline-aware.json').resolve()),
 'instructions_verified':len(export['instructions']),'instruction_byte_mismatches':mismatches,
 'unique_bytes_decoded_as_instructions':len(covered),'functions_in_export':len(export['functions']),
 'caveat':'Byte equality verifies provenance, not correct hardware mapping or exhaustive reachable control flow. Function counts are recovery results, not actual function totals.',
 'constant_initializer_records':len(init['records']),'device_descriptor_model_xdata':'0x0975','device_descriptor_model_size':model[0x975],
 'standard_get_device_descriptor':{'file_cases':['0x468c','0x405d','0x40e8','0x421e'],'response_pointer':'XDATA0x0975','declared_size':18,'length_clamp':'min(descriptor length,host wLength)','observed_failed_host_length':64,'expected_count_under_model':18,'limit':'Control-flow/table interpretation under classic8051; this is not observed device execution.'},
 'startup':{'vectors':'0x0000 LJMP0x0100','initial_clear_loops':['0x0100..0x0112','0x0400..0x0412'],'xdata_clear_interval':'[0x0000,0x1000)','checksum_mode_read':'XDATA0x1080 &0x05','checksum_end_selection':{'masked_value_5':'0xd800 exclusive','other_masked_values':'0x8000 exclusive'},'checksum_cases':checksum,'stored_big_endian_checksum':hex(int.from_bytes(raw[0x7ffe:0x8000],'big')),'checksum_failure_branch':'0x01ff..0x0205 ->0x0130 ->CODE0xe000','missing_code_targets':['CODE0xe000','CODE0xfe00'],'register_semantics':'Unverified; do not infer flash-size, warm-reset cause, or chip revision from this bit test.'},
 'low_power_candidate_writes':[{'file':hex(a),'bytes':raw[a:a+3].hex(' ')} for a in [0x225b,0x263f,0x2659,0x2672]],
 'review_scope':['USB/HID/OS descriptors','constant RAM initialization','reset/checksum gate','standard and Microsoft vendor descriptor count paths','bounded low-power candidates'],
 'open_questions':['Chip-specific USB reset/suspend MMIO meanings','Runtime state before/after Windows shutdown','ROM/banked code absent from supplied image','Interrupt/indirect callback state-machine completeness','Any causal relation from candidate vendor count flaw to keyboard startup failure'],
 'original_firmware_modified':False,'hardware_access_performed':False
}
(root/'audit-facts.json').write_text(json.dumps(facts,indent=2),encoding='utf-8')
print(json.dumps({k:facts[k] for k in ['source_sha256','instructions_verified','instruction_byte_mismatches','functions_in_export','unique_bytes_decoded_as_instructions']},indent=2))
