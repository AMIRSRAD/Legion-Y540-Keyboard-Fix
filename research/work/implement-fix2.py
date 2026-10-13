from pathlib import Path
r=Path('outputs/fix2')
def edit(name, old, new):
 p=r/name
 s=p.read_text(); assert old in s,(name,old)
 p.write_text(s.replace(old,new))
edit('src/hid_transport.h','Always exactly 64 bytes.','Buffer capacity is 64 bytes; report_bytes is the actual transfer length.')
edit('src/hid_transport.h','uint8_t report[Y540_HID_REPORT_BYTES],','uint8_t report[Y540_HID_REPORT_BYTES], size_t report_bytes,')
edit('src/hid_transport.h','int y540_hid_identity_matches(', 'int y540_hid_report_profile_valid(const y540_hid_device *device);\nint y540_hid_identity_matches(')
edit('src/hid_transport.c','static int windows_feature(void *context, int is_write, uint8_t report[64],','''int y540_hid_report_profile_valid(const y540_hid_device *d) {
  return d && d->vid == 0x048d && d->usage_page == 0xff89 &&
    ((d->pid == 0xc100 && d->usage == 0x0010 && d->feature_report_bytes == 17) ||
     (d->pid == 0x89db && d->usage == 0x00db && d->feature_report_bytes == 64));
}

static int windows_feature(void *context, int is_write, uint8_t report[64], size_t report_bytes,''')
edit('src/hid_transport.c','HidD_SetFeature((HANDLE)context, report, 64)','HidD_SetFeature((HANDLE)context, report, (ULONG)report_bytes)')
edit('src/hid_transport.c','HidD_GetFeature((HANDLE)context, report, 64)','HidD_GetFeature((HANDLE)context, report, (ULONG)report_bytes)')
edit('src/hid_transport.c','candidate.selected.feature_report_bytes != 64','!y540_hid_report_profile_valid(&candidate.selected)')
edit('src/hid_transport.c','Selected HID interface does not advertise 64-byte feature reports','Unsupported HID report profile (normal requires 17 bytes; boot requires 64)')
edit('src/hid_transport.c','actual.feature_report_bytes != 64','!y540_hid_report_profile_valid(&actual)')
edit('src/hid_transport.c','now.feature_report_bytes!=64','!y540_hid_report_profile_valid(&now)||now.feature_report_bytes!=transport->device.feature_report_bytes')
edit('src/hid_transport.c','  if (transport->command_delay_ms)\n', '''  size_t report_bytes = transport->device.feature_report_bytes;
  /* An unprofiled injected backend retains the 64-byte boot-model default. */
  if (!report_bytes && !transport->owns_handle) report_bytes = 64;
  if (report_bytes < 1 || report_bytes > 64 || length >= report_bytes)
    return fail(error, ERROR_BAD_LENGTH, "Payload exceeds selected feature report size");
  if (transport->device.vid &&
      (!y540_hid_report_profile_valid(&transport->device) ||
       (transport->device.pid == 0xc100 ? report_id != 0x5a : report_id != 0)))
    return fail(error, ERROR_INVALID_PARAMETER, "Report ID does not match selected device mode");
  trace_line("HID transfer report_id=%02X report_bytes=%u payload_bytes=%u",
             report_id, (unsigned)report_bytes, (unsigned)length);
  if (transport->command_delay_ms)
''')
edit('src/hid_transport.c','transport->context, is_write, report,\n','transport->context, is_write, report, report_bytes,\n')
for name in ['tests/test_hid_transport.c','tests/test_protocol.c']:
 edit(name,'uint8_t report[64], y540_hid_error *error)', 'uint8_t report[64], size_t report_bytes, y540_hid_error *error)')
edit('tests/test_hid_transport.c','    ++state->calls;', '    assert(report_bytes == (report[0] == 0x5a ? 17u : 64u));\n    ++state->calls;')
edit('tests/test_protocol.c','static int feature(void *context, int write, uint8_t report[64], size_t report_bytes, y540_hid_error *error)\n{','static int feature(void *context, int write, uint8_t report[64], size_t report_bytes, y540_hid_error *error)\n{\n    assert(report_bytes == 64 || (report_bytes == 17 && report[0] == 0x5a));')
edit('tests/test_hid_transport.c','    physical_identity_fixtures();','''    physical_identity_fixtures();
    {
      y540_hid_device d = {0};
      d.vid=0x048d; d.pid=0xc100; d.usage_page=0xff89; d.usage=0x10; d.feature_report_bytes=17;
      assert(y540_hid_report_profile_valid(&d));
      d.feature_report_bytes=64; assert(!y540_hid_report_profile_valid(&d));
      d.feature_report_bytes=3; d.usage=0xcd; assert(!y540_hid_report_profile_valid(&d));
      d.pid=0x89db; d.usage=0xdb; d.feature_report_bytes=64;
      assert(y540_hid_report_profile_valid(&d));
      d.feature_report_bytes=17; assert(!y540_hid_report_profile_valid(&d));
      y540_hid_transport normal={0}; fake_state ns={0}; uint8_t payload[17]={0};
      assert(y540_hid_init_custom(&normal,&ns,fake_feature,fake_sleep,0,&error));
      normal.device.vid=0x048d; normal.device.pid=0xc100;
      normal.device.usage_page=0xff89; normal.device.usage=0x10; normal.device.feature_report_bytes=17;
      assert(y540_hid_send_report(&normal,0x5a,payload,16,&error));
      assert(y540_hid_receive_report(&normal,0x5a,payload,16,&error));
      assert(ns.calls==2);
      assert(!y540_hid_send_report(&normal,0x5a,payload,17,&error));
      assert(!y540_hid_send_report(&normal,0,payload,1,&error));
      assert(ns.calls==2);
      y540_hid_close(&normal);
    }''')
# Keep release provenance distinct from the preserved fix1 source and ZIPs.
for name in ['src/session_log.c','src/app.c','src/app.rc','tools/package_release.py','START-HERE.txt','README.md','CMakeLists.txt']:
 p=r/name;s=p.read_text();s=s.replace('fix1','fix2').replace('0.3.0','0.3.1').replace('0,3,0,0','0,3,1,0');p.write_text(s)
edit('src/app.c','Reflashing 44 is not a proven cure for AC-startup failure.','Reflashing 44 is not a proven cure for the observed startup failure.')
