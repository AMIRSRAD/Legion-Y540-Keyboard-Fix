from pathlib import Path
p=Path('outputs/fix1/src/hid_transport.h');s=p.read_text(encoding='utf8').replace('void y540_hid_close(', 'int y540_hid_validate_current(y540_hid_transport *transport, y540_hid_error *error);\nvoid y540_hid_close(');p.write_text(s,encoding='utf8')
p=Path('outputs/fix1/src/hid_transport.c');s=p.read_text(encoding='utf-8-sig');needle='void y540_hid_close('
addition='''int y540_hid_validate_current(y540_hid_transport *transport, y540_hid_error *error) {
  if(!transport || !transport->feature)return fail(error,ERROR_INVALID_HANDLE,"Transport is not open");
  if(!transport->owns_handle)return 1; /* Injected memory backend, not a Windows device. */
  DEVINST node=0;y540_hid_device now;
  if(CM_Locate_DevNodeW(&node,transport->device.hid_instance_id,CM_LOCATE_DEVNODE_NORMAL)!=CR_SUCCESS)return fail(error,ERROR_DEVICE_NOT_CONNECTED,"HID collection disappeared before write");
  if(!inspect((HANDLE)transport->context,transport->device.path,&now,error)||!physical_identity(node,&now,error))return 0;
  if(now.vid!=transport->device.vid||now.pid!=transport->device.pid||now.usage_page!=transport->device.usage_page||now.usage!=transport->device.usage||now.feature_report_bytes!=64||
    _wcsicmp(now.usb_instance_id,transport->device.usb_instance_id)||_wcsicmp(now.usb_parent_id,transport->device.usb_parent_id)||_wcsicmp(now.usb_location,transport->device.usb_location))return fail(error,ERROR_DEVICE_NOT_CONNECTED,"Keyboard identity/topology changed before write");
  trace_line("HID current identity and PnP health revalidated");return 1;
}

'''
s=s.replace(needle,addition+needle);p.write_text(s,encoding='utf8')
