from pathlib import Path
p=Path('outputs/fix1/src/hid_transport.h');s=p.read_text(encoding='utf-8-sig');s=s.replace('    uint16_t vid, pid, usage_page, usage, feature_report_bytes;','    uint16_t vid, pid, usage_page, usage, feature_report_bytes;\n    wchar_t hid_instance_id[1024];\n    wchar_t usb_instance_id[1024];\n    wchar_t usb_parent_id[1024];\n    wchar_t usb_location[256];');s=s.replace('    const wchar_t *path;\n} y540_hid_selector;','    const wchar_t *path;\n    const wchar_t *usb_parent_id;\n    const wchar_t *usb_location;\n} y540_hid_selector;');s=s.replace('int y540_hid_enumerate(', 'typedef void (*y540_hid_trace_fn)(void *context, const char *line);\nvoid y540_hid_set_trace(y540_hid_trace_fn trace, void *context);\nint y540_hid_identity_matches(const y540_hid_selector *, const y540_hid_device *);\nint y540_hid_enumerate(');p.write_text(s,encoding='utf8')
p=Path('outputs/fix1/src/hid_transport.c');s=p.read_text(encoding='utf-8-sig');s=s.replace('#include <setupapi.h>','#include <setupapi.h>\n#include <cfgmgr32.h>\n#include <stdarg.h>')
pos='static int fail('
addition='''static y540_hid_trace_fn trace_fn;
static void *trace_context;
void y540_hid_set_trace(y540_hid_trace_fn trace, void *context) { trace_fn=trace;trace_context=context; }
static void trace_line(const char *format,...) {
    char line[4096];va_list a;if(!trace_fn)return;va_start(a,format);vsnprintf(line,sizeof(line),format,a);va_end(a);trace_fn(trace_context,line);
}
static void trace_wide(const char *label,const wchar_t *value) {
    char text[3072];if(!trace_fn)return;
    if(!WideCharToMultiByte(CP_UTF8,0,value,-1,text,sizeof(text),NULL,NULL))strcpy(text,"(unavailable)");
    trace_line("%s=%s",label,text);
}
static void trace_report(int write,unsigned attempt,int success,const uint8_t report[64],const y540_hid_error *error) {
    char hex[129];if(!trace_fn)return;
    for(size_t i=0;i<64;i++)snprintf(hex+2*i,3,"%02X",report[i]);
    trace_line("HID %s attempt=%u success=%d error=%lu message=%s report64=%s",write?"TX":"RX",attempt+1,success,(unsigned long)(error?error->code:0),error?error->message:"",hex);
}

'''
s=s.replace(pos,addition+pos)
# Add healthy topology inspection before enumerator. Pure metadata, not report I/O.
needle='int y540_hid_enumerate('
addition='''static int physical_identity(DEVINST node,y540_hid_device *device,y540_hid_error *error) {
    ULONG status=0,problem=0;DEVINST current=node,parent;wchar_t id[1024];CONFIGRET cr;
    cr=CM_Get_DevNode_Status(&status,&problem,node,0);
    if(cr!=CR_SUCCESS||problem||!(status&DN_STARTED))return fail(error,ERROR_DEVICE_NOT_CONNECTED,"HID devnode is not present and started with problem zero");
    if(CM_Get_Device_IDW(node,device->hid_instance_id,1024,0)!=CR_SUCCESS)return fail(error,ERROR_NOT_FOUND,"Cannot bind HID instance identity");
    for(unsigned depth=0;depth<16;depth++) {
        if(CM_Get_Device_IDW(current,id,1024,0)!=CR_SUCCESS)break;
        if((!_wcsnicmp(id,L"USB\\\\VID_048D&PID_C100\\\\",22)||!_wcsnicmp(id,L"USB\\\\VID_048D&PID_89DB\\\\",22))) {
            if(CM_Get_DevNode_Status(&status,&problem,current,0)!=CR_SUCCESS||problem||!(status&DN_STARTED))return fail(error,ERROR_DEVICE_NOT_CONNECTED,"Physical keyboard USB devnode is not healthy");
            wcscpy(device->usb_instance_id,id);
            if(CM_Get_Parent(&parent,current,0)!=CR_SUCCESS||CM_Get_Device_IDW(parent,device->usb_parent_id,1024,0)!=CR_SUCCESS)return fail(error,ERROR_NOT_FOUND,"Cannot resolve keyboard parent USB topology");
            ULONG type=0,bytes=sizeof(device->usb_location);
            if(CM_Get_DevNode_Registry_PropertyW(current,CM_DRP_LOCATION_INFORMATION,&type,device->usb_location,&bytes,0)!=CR_SUCCESS||type!=REG_SZ)return fail(error,ERROR_NOT_FOUND,"Cannot resolve keyboard USB port location");
            device->usb_location[255]=0;
            if(!device->usb_location[0])return fail(error,ERROR_NOT_FOUND,"Keyboard USB port location is empty");
            return 1;
        }
        if(CM_Get_Parent(&parent,current,0)!=CR_SUCCESS)break;current=parent;
    }
    return fail(error,ERROR_NOT_FOUND,"HID collection has no bound ITE physical USB identity");
}

'''
s=s.replace(needle,addition+needle)
s=s.replace('        y540_hid_device device;','        y540_hid_device device;\n        y540_hid_error inspect_error={0};\n        SP_DEVINFO_DATA device_info={0};device_info.cbSize=sizeof(device_info);')
s=s.replace('detail, needed, NULL, NULL))','detail, needed, NULL, &device_info))')
s=s.replace('if (handle == INVALID_HANDLE_VALUE) { free(detail); continue; }','if (handle == INVALID_HANDLE_VALUE) { trace_line("HID metadata open skipped error=%lu",(unsigned long)GetLastError());trace_wide("path",detail->DevicePath); free(detail); continue; }')
s=s.replace('if (!inspect(handle, detail->DevicePath, &device, NULL)) {','if (!inspect(handle, detail->DevicePath, &device, &inspect_error)) {\n            trace_line("HID metadata inspection skipped code=%lu message=%s",(unsigned long)inspect_error.code,inspect_error.message);')
# Keep ordinary HID inventory; collect physical binding for ITE collections only.
s=s.replace('        CloseHandle(handle);\n        free(detail);\n        keep_going', '''        if(device.vid==0x048d && (device.pid==0xc100||device.pid==0x89db)) {
            if(!physical_identity(device_info.DevInst,&device,&inspect_error)) {
                trace_line("ITE collection rejected code=%lu message=%s",(unsigned long)inspect_error.code,inspect_error.message);
                CloseHandle(handle);free(detail);continue;
            }
            trace_line("ITE HID vid=%04X pid=%04X usage_page=%04X usage=%04X feature=%u",device.vid,device.pid,device.usage_page,device.usage,device.feature_report_bytes);
            trace_wide("usb_instance",device.usb_instance_id);trace_wide("usb_parent",device.usb_parent_id);trace_wide("usb_location",device.usb_location);
        }
        CloseHandle(handle);
        free(detail);
        keep_going''')
s=s.replace('static int matches(', 'int y540_hid_identity_matches(')
s=s.replace('(!selector->path || _wcsicmp(selector->path, device->path) == 0);','(!selector->path || _wcsicmp(selector->path, device->path) == 0) &&\n           (!selector->usb_parent_id || _wcsicmp(selector->usb_parent_id,device->usb_parent_id)==0) &&\n           (!selector->usb_location || _wcsicmp(selector->usb_location,device->usb_location)==0);')
s=s.replace('matches(candidate->selector, device)','y540_hid_identity_matches(candidate->selector, device)').replace('matches(selector, &actual)','y540_hid_identity_matches(selector, &actual)')
s=s.replace('    if (!matches(selector,', '    if (!y540_hid_identity_matches(selector,')
needle='    if (!y540_hid_identity_matches(selector, &actual)'
s=s.replace(needle,'''    DEVINST node=0;
    if(CM_Locate_DevNodeW(&node,candidate.selected.hid_instance_id,CM_LOCATE_DEVNODE_NORMAL)!=CR_SUCCESS || !physical_identity(node,&actual,error)) { CloseHandle(handle);return fail(error,ERROR_DEVICE_NOT_CONNECTED,"Selected HID topology changed or is unhealthy before open"); }
    if(_wcsicmp(candidate.selected.usb_instance_id,actual.usb_instance_id)||_wcsicmp(candidate.selected.usb_parent_id,actual.usb_parent_id)||_wcsicmp(candidate.selected.usb_location,actual.usb_location)) {CloseHandle(handle);return fail(error,ERROR_DEVICE_NOT_CONNECTED,"Physical keyboard identity changed while opening");}
'''+needle)
s=s.replace('    transport->device = actual;\n    return 1;', '    transport->device = actual;\n    trace_line("HID open healthy code=0");trace_wide("selected_path",actual.path);\n    return 1;')
s=s.replace('if (transport->feature(transport->context, is_write, report, &local_error)) {','if (transport->feature(transport->context, is_write, report, &local_error)) {\n            trace_report(is_write,attempt,1,report,&local_error);')
s=s.replace('        if (error) *error = local_error;', '        trace_report(is_write,attempt,0,report,&local_error);\n        if (error) *error = local_error;')
p.write_text(s,encoding='utf8')
