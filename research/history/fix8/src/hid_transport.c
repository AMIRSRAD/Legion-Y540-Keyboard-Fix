/* Windows HID transport reconstructed from static updater evidence
 * 030/031/040/051. No claim of hardware compatibility follows from successful
 * compilation. */
#include "hid_transport.h"
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <cfgmgr32.h>
#include <hidsdi.h>
#include <hidpi.h>

#include <setupapi.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#ifndef NT_SUCCESS
#define NT_SUCCESS(status) (((NTSTATUS)(status)) >= 0)
#endif

static y540_hid_trace_fn trace_fn;
static void *trace_context;
void y540_hid_set_trace(y540_hid_trace_fn trace, void *context) {
  trace_fn = trace;
  trace_context = context;
}
static void trace_line(const char *format, ...) {
  char line[4096];
  va_list a;
  if (!trace_fn)
    return;
  va_start(a, format);
  vsnprintf(line, sizeof(line), format, a);
  va_end(a);
  trace_fn(trace_context, line);
}
static void trace_wide(const char *label, const wchar_t *value) {
  char text[3072];
  if (!trace_fn)
    return;
  if (!WideCharToMultiByte(CP_UTF8, 0, value, -1, text, sizeof(text), NULL,
                           NULL))
    strcpy(text, "(unavailable)");
  trace_line("%s=%s", label, text);
}
static void trace_report(int write, unsigned attempt, int success,
                         const uint8_t report[64],
                         const y540_hid_error *error) {
  char hex[129];
  if (!trace_fn)
    return;
  for (size_t i = 0; i < 64; i++)
    snprintf(hex + 2 * i, 3, "%02X", report[i]);
  trace_line("HID %s attempt=%u success=%d error=%lu message=%s report64=%s",
             write ? "TX" : "RX", attempt + 1, success,
             (unsigned long)(error ? error->code : 0),
             error ? error->message : "", hex);
}

static int fail(y540_hid_error *error, DWORD code, const char *message) {
  if (error) {
    error->code = code ? code : ERROR_GEN_FAILURE;
    snprintf(error->message, sizeof(error->message), "%s", message);
  }
  return 0;
}

static void clear_error(y540_hid_error *error) {
  if (error)
    memset(error, 0, sizeof(*error));
}

static int inspect(HANDLE handle, const wchar_t *path, y540_hid_device *device,
                   y540_hid_error *error) {
  HIDD_ATTRIBUTES attributes;
  PHIDP_PREPARSED_DATA preparsed = NULL;
  HIDP_CAPS caps;
  NTSTATUS status;
  size_t length = wcslen(path);
  if (length >= Y540_HID_PATH_CHARS)
    return fail(error, ERROR_BUFFER_OVERFLOW,
                "HID interface path exceeds storage capacity");
  memset(&attributes, 0, sizeof(attributes));
  attributes.Size = sizeof(attributes);
  if (!HidD_GetAttributes(handle, &attributes))
    return fail(error, GetLastError(), "HidD_GetAttributes failed");
  if (!HidD_GetPreparsedData(handle, &preparsed))
    return fail(error, GetLastError(), "HidD_GetPreparsedData failed");
  memset(&caps, 0, sizeof(caps));
  status = HidP_GetCaps(preparsed, &caps);
  HidD_FreePreparsedData(preparsed);
  if (!NT_SUCCESS(status))
    return fail(error, (DWORD)status, "HidP_GetCaps failed (NTSTATUS)");
  memset(device, 0, sizeof(*device));
  memcpy(device->path, path, (length + 1) * sizeof(wchar_t));
  device->vid = attributes.VendorID;
  device->pid = attributes.ProductID;
  device->usage_page = caps.UsagePage;
  device->usage = caps.Usage;
  device->feature_report_bytes = caps.FeatureReportByteLength;
  return 1;
}

static int physical_identity(DEVINST node, y540_hid_device *device,
                             y540_hid_error *error) {
  ULONG status = 0, problem = 0;
  DEVINST current = node, parent;
  wchar_t id[1024];
  CONFIGRET cr;
  cr = CM_Get_DevNode_Status(&status, &problem, node, 0);
  if (cr != CR_SUCCESS || problem || !(status & DN_STARTED))
    return fail(error, ERROR_DEVICE_NOT_CONNECTED,
                "HID devnode is not present and started with problem zero");
  if (CM_Get_Device_IDW(node, device->hid_instance_id, 1024, 0) != CR_SUCCESS)
    return fail(error, ERROR_NOT_FOUND, "Cannot bind HID instance identity");
  for (unsigned depth = 0; depth < 16; depth++) {
    if (CM_Get_Device_IDW(current, id, 1024, 0) != CR_SUCCESS)
      break;
    if ((!_wcsnicmp(id, L"USB\\VID_048D&PID_C100\\", 22) ||
         !_wcsnicmp(id, L"USB\\VID_048D&PID_89DB\\", 22))) {
      if (CM_Get_DevNode_Status(&status, &problem, current, 0) != CR_SUCCESS ||
          problem || !(status & DN_STARTED))
        return fail(error, ERROR_DEVICE_NOT_CONNECTED,
                    "Physical keyboard USB devnode is not healthy");
      wcscpy(device->usb_instance_id, id);
      if (CM_Get_Parent(&parent, current, 0) != CR_SUCCESS ||
          CM_Get_Device_IDW(parent, device->usb_parent_id, 1024, 0) !=
              CR_SUCCESS)
        return fail(error, ERROR_NOT_FOUND,
                    "Cannot resolve keyboard parent USB topology");
      ULONG type = 0, bytes = sizeof(device->usb_location);
      if (CM_Get_DevNode_Registry_PropertyW(
              current, CM_DRP_LOCATION_INFORMATION, &type, device->usb_location,
              &bytes, 0) != CR_SUCCESS ||
          type != REG_SZ)
        return fail(error, ERROR_NOT_FOUND,
                    "Cannot resolve keyboard USB port location");
      device->usb_location[255] = 0;
      if (!device->usb_location[0])
        return fail(error, ERROR_NOT_FOUND,
                    "Keyboard USB port location is empty");
      return 1;
    }
    if (CM_Get_Parent(&parent, current, 0) != CR_SUCCESS)
      break;
    current = parent;
  }
  return fail(error, ERROR_NOT_FOUND,
              "HID collection has no bound ITE physical USB identity");
}

int y540_hid_enumerate(y540_hid_visit visit, void *context,
                       y540_hid_error *error) {
  GUID hid_guid;
  HDEVINFO devices;
  DWORD index;
  int result = 1;
  clear_error(error);
  if (!visit)
    return fail(error, ERROR_INVALID_PARAMETER,
                "Enumeration callback is required");
  HidD_GetHidGuid(&hid_guid);
  devices = SetupDiGetClassDevsW(&hid_guid, NULL, NULL,
                                 DIGCF_PRESENT | DIGCF_DEVICEINTERFACE);
  if (devices == INVALID_HANDLE_VALUE)
    return fail(error, GetLastError(), "SetupDiGetClassDevsW failed");
  for (index = 0;; ++index) {
    SP_DEVICE_INTERFACE_DATA interface_data;
    PSP_DEVICE_INTERFACE_DETAIL_DATA_W detail;
    DWORD needed = 0;
    DWORD code;
    HANDLE handle;
    y540_hid_device device;
    y540_hid_error inspect_error = {0};
    SP_DEVINFO_DATA device_info = {0};
    device_info.cbSize = sizeof(device_info);
    int keep_going;
    memset(&interface_data, 0, sizeof(interface_data));
    interface_data.cbSize = sizeof(interface_data);
    if (!SetupDiEnumDeviceInterfaces(devices, NULL, &hid_guid, index,
                                     &interface_data)) {
      code = GetLastError();
      if (code != ERROR_NO_MORE_ITEMS)
        result = fail(error, code, "SetupDiEnumDeviceInterfaces failed");
      break;
    }
    SetupDiGetDeviceInterfaceDetailW(devices, &interface_data, NULL, 0, &needed,
                                     NULL);
    code = GetLastError();
    if (code != ERROR_INSUFFICIENT_BUFFER || needed < sizeof(*detail)) {
      result =
          fail(error, code, "Unable to determine HID interface detail size");
      break;
    }
    detail = (PSP_DEVICE_INTERFACE_DETAIL_DATA_W)malloc(needed);
    if (!detail) {
      result =
          fail(error, ERROR_NOT_ENOUGH_MEMORY, "HID detail allocation failed");
      break;
    }
    memset(detail, 0, needed);
    detail->cbSize = sizeof(*detail);
    if (!SetupDiGetDeviceInterfaceDetailW(devices, &interface_data, detail,
                                          needed, NULL, &device_info)) {
      code = GetLastError();
      free(detail);
      result = fail(error, code, "SetupDiGetDeviceInterfaceDetailW failed");
      break;
    }
    handle =
        CreateFileW(detail->DevicePath, 0, FILE_SHARE_READ | FILE_SHARE_WRITE,
                    NULL, OPEN_EXISTING, 0, NULL);
    if (handle == INVALID_HANDLE_VALUE) {
      trace_line("HID metadata open skipped error=%lu",
                 (unsigned long)GetLastError());
      trace_wide("path", detail->DevicePath);
      free(detail);
      continue;
    }
    if (!inspect(handle, detail->DevicePath, &device, &inspect_error)) {
      trace_line("HID metadata inspection skipped code=%lu message=%s",
                 (unsigned long)inspect_error.code, inspect_error.message);
      CloseHandle(handle);
      free(detail);
      continue;
    }
    if (device.vid == 0x048d &&
        (device.pid == 0xc100 || device.pid == 0x89db)) {
      if (!physical_identity(device_info.DevInst, &device, &inspect_error)) {
        trace_line("ITE collection rejected code=%lu message=%s",
                   (unsigned long)inspect_error.code, inspect_error.message);
        CloseHandle(handle);
        free(detail);
        continue;
      }
      trace_line(
          "ITE HID vid=%04X pid=%04X usage_page=%04X usage=%04X feature=%u",
          device.vid, device.pid, device.usage_page, device.usage,
          device.feature_report_bytes);
      trace_wide("usb_instance", device.usb_instance_id);
      trace_wide("usb_parent", device.usb_parent_id);
      trace_wide("usb_location", device.usb_location);
    }
    CloseHandle(handle);
    free(detail);
    keep_going = visit(context, &device);
    if (!keep_going)
      break;
  }
  SetupDiDestroyDeviceInfoList(devices);
  return result;
}

int y540_hid_identity_matches(const y540_hid_selector *selector,
                              const y540_hid_device *device) {
  return selector->vid == device->vid && selector->pid == device->pid &&
         selector->usage_page == device->usage_page &&
         selector->usage == device->usage &&
         (!selector->path || _wcsicmp(selector->path, device->path) == 0) &&
         (!selector->usb_parent_id ||
          _wcsicmp(selector->usb_parent_id, device->usb_parent_id) == 0) &&
         (!selector->usb_location ||
          _wcsicmp(selector->usb_location, device->usb_location) == 0);
}

typedef struct {
  const y540_hid_selector *selector;
  size_t count;
  y540_hid_device selected;
} selection;

static int select_device(void *context, const y540_hid_device *device) {
  selection *candidate = (selection *)context;
  if (y540_hid_identity_matches(candidate->selector, device)) {
    ++candidate->count;
    candidate->selected = *device;
  }
  return 1;
}

int y540_hid_report_profile_valid(const y540_hid_device *d) {
  return d && d->vid == 0x048d && d->usage_page == 0xff89 &&
    ((d->pid == 0xc100 && d->usage == 0x0010 && d->feature_report_bytes == 17) ||
     (d->pid == 0x89db && d->usage == 0x00db && d->feature_report_bytes == 64));
}

/* fix5 returns to access 0 for every ITE interface: it is the configuration
 * that completed the only successful boot-mode read/erase/write (fix2). The
 * fix4 read/write open changed nothing: the ETW trace shows the failure is a
 * device that no longer answers after USB suspend/resume, not a rights error. */
uint32_t y540_hid_access_for_device(const y540_hid_device *d) {
  (void)d;
  return 0;
}

static int windows_feature(void *context, int is_write, uint8_t report[64], size_t report_bytes,
                           y540_hid_error *error) {
  BOOLEAN ok = is_write ? HidD_SetFeature((HANDLE)context, report, (ULONG)report_bytes)
                        : HidD_GetFeature((HANDLE)context, report, (ULONG)report_bytes);
  if (!ok)
    return fail(error, GetLastError(),
                is_write ? "HidD_SetFeature failed" : "HidD_GetFeature failed");
  return 1;
}

static void windows_sleep(void *context, uint32_t milliseconds) {
  (void)context;
  Sleep(milliseconds);
}

int y540_hid_open(y540_hid_transport *transport,
                  const y540_hid_selector *selector, uint32_t command_delay_ms,
                  y540_hid_error *error) {
  selection candidate;
  HANDLE handle;
  y540_hid_device actual;
  clear_error(error);
  if (!transport || !selector)
    return fail(error, ERROR_INVALID_PARAMETER,
                "Transport and exact device selector are required");
  if (transport->feature || transport->owns_handle)
    return fail(error, ERROR_ALREADY_EXISTS,
                "Close the current transport before opening");
  memset(&candidate, 0, sizeof(candidate));
  candidate.selector = selector;
  if (!y540_hid_enumerate(select_device, &candidate, error))
    return 0;
  if (!candidate.count)
    return fail(error, ERROR_NOT_FOUND,
                "No HID interface matches every selector field");
  if (candidate.count > 1)
    return fail(error, ERROR_DUP_NAME,
                "Multiple matching HID interfaces; specify an exact path");
  if (!y540_hid_report_profile_valid(&candidate.selected))
    return fail(
        error, ERROR_BAD_LENGTH,
        "Unsupported HID report profile (normal requires 17 bytes; boot requires 64)");
  /* Access0 previously succeeded once and later failed feature calls with31.
   * RW on this exact boot vendor collection is an alternate transport test,
   * not a diagnosed permission fix. Never request RW on the normal keyboard. */
  DWORD requested_access = y540_hid_access_for_device(&candidate.selected);
  trace_line("HID data open requested_access=0x%08lX", (unsigned long)requested_access);
  handle = CreateFileW(candidate.selected.path, requested_access,
                       FILE_SHARE_READ | FILE_SHARE_WRITE, NULL, OPEN_EXISTING,
                       0, NULL);
  if (handle == INVALID_HANDLE_VALUE)
    return fail(error, GetLastError(), "Opening selected HID interface failed");
  if (!inspect(handle, candidate.selected.path, &actual, error)) {
    CloseHandle(handle);
    return 0;
  }
  DEVINST node = 0;
  if (CM_Locate_DevNodeW(&node, candidate.selected.hid_instance_id,
                         CM_LOCATE_DEVNODE_NORMAL) != CR_SUCCESS ||
      !physical_identity(node, &actual, error)) {
    CloseHandle(handle);
    return fail(error, ERROR_DEVICE_NOT_CONNECTED,
                "Selected HID topology changed or is unhealthy before open");
  }
  if (_wcsicmp(candidate.selected.usb_instance_id, actual.usb_instance_id) ||
      _wcsicmp(candidate.selected.usb_parent_id, actual.usb_parent_id) ||
      _wcsicmp(candidate.selected.usb_location, actual.usb_location)) {
    CloseHandle(handle);
    return fail(error, ERROR_DEVICE_NOT_CONNECTED,
                "Physical keyboard identity changed while opening");
  }
  if (!y540_hid_identity_matches(selector, &actual) ||
      !y540_hid_report_profile_valid(&actual)) {
    CloseHandle(handle);
    return fail(error, ERROR_DEVICE_NOT_CONNECTED,
                "HID identity or report size changed before open completed");
  }
  memset(transport, 0, sizeof(*transport));
  transport->context = handle;
  transport->feature = windows_feature;
  transport->sleep = windows_sleep;
  transport->command_delay_ms = command_delay_ms;
  transport->owns_handle = 1;
  transport->device = actual;
  trace_line("HID identity validated code=0; command readiness not yet established");
  trace_wide("selected_path", actual.path);
  return 1;
}

int y540_hid_validate_current(y540_hid_transport *transport, y540_hid_error *error) {
  if(!transport || !transport->feature)return fail(error,ERROR_INVALID_HANDLE,"Transport is not open");
  if(!transport->owns_handle)return 1; /* Injected memory backend, not a Windows device. */
  DEVINST node=0;y540_hid_device now;
  if(CM_Locate_DevNodeW(&node,transport->device.hid_instance_id,CM_LOCATE_DEVNODE_NORMAL)!=CR_SUCCESS)return fail(error,ERROR_DEVICE_NOT_CONNECTED,"HID collection disappeared before write");
  if(!inspect((HANDLE)transport->context,transport->device.path,&now,error)||!physical_identity(node,&now,error))return 0;
  if(now.vid!=transport->device.vid||now.pid!=transport->device.pid||now.usage_page!=transport->device.usage_page||now.usage!=transport->device.usage||!y540_hid_report_profile_valid(&now)||now.feature_report_bytes!=transport->device.feature_report_bytes||
    _wcsicmp(now.usb_instance_id,transport->device.usb_instance_id)||_wcsicmp(now.usb_parent_id,transport->device.usb_parent_id)||_wcsicmp(now.usb_location,transport->device.usb_location))return fail(error,ERROR_DEVICE_NOT_CONNECTED,"Keyboard identity/topology changed before write");
  trace_line("HID current identity and PnP health revalidated");return 1;
}

void y540_hid_close(y540_hid_transport *transport) {
  if (!transport)
    return;
  if (transport->owns_handle && transport->context)
    CloseHandle((HANDLE)transport->context);
  memset(transport, 0, sizeof(*transport));
}

int y540_hid_init_custom(y540_hid_transport *transport, void *context,
                         y540_hid_feature_fn feature, y540_hid_sleep_fn sleep,
                         uint32_t command_delay_ms, y540_hid_error *error) {
  clear_error(error);
  if (!transport || !feature || !sleep)
    return fail(error, ERROR_INVALID_PARAMETER,
                "Transport, feature and sleep callbacks are required");
  if (transport->feature || transport->owns_handle)
    return fail(error, ERROR_ALREADY_EXISTS,
                "Close the current transport before initializing");
  memset(transport, 0, sizeof(*transport));
  transport->context = context;
  transport->feature = feature;
  transport->sleep = sleep;
  transport->command_delay_ms = command_delay_ms;
  return 1;
}

static int transfer(y540_hid_transport *transport, uint8_t report_id,
                    int is_write, const uint8_t *input, uint8_t *output,
                    size_t length, y540_hid_error *error) {
  unsigned attempt;
  y540_hid_error local_error;
  clear_error(error);
  if (!transport || !transport->feature || !transport->sleep ||
      length > Y540_HID_PAYLOAD_BYTES ||
      (length && !(is_write ? input : output)))
    return fail(error, ERROR_INVALID_PARAMETER,
                "Open transport and payload length 0..63 are required");
  size_t report_bytes = transport->device.feature_report_bytes;
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
    transport->sleep(transport->context, transport->command_delay_ms);
  for (attempt = 0; attempt < Y540_HID_ATTEMPTS; ++attempt) {
    uint8_t report[Y540_HID_REPORT_BYTES] = {0};
    report[0] = report_id;
    clear_error(&local_error);
    if (is_write && length)
      memcpy(report + 1, input, length);
    if (transport->feature(transport->context, is_write, report, report_bytes,
                           &local_error)) {
      trace_report(is_write, attempt, 1, report, &local_error);
      if (!is_write && length)
        memcpy(output, report + 1, length);
      clear_error(error);
      return 1;
    }
    if (!local_error.code)
      fail(&local_error, ERROR_GEN_FAILURE,
           "Feature callback failed without an error code");
    trace_report(is_write, attempt, 0, report, &local_error);
    if (error)
      *error = local_error;
    transport->sleep(transport->context, 100);
  }
  return 0;
}

int y540_hid_send(y540_hid_transport *transport, const uint8_t *payload,
                  size_t length, y540_hid_error *error) {
  return transfer(transport, 0, 1, payload, NULL, length, error);
}

int y540_hid_receive(y540_hid_transport *transport, uint8_t *payload,
                     size_t length, y540_hid_error *error) {
  return transfer(transport, 0, 0, NULL, payload, length, error);
}

int y540_hid_send_report(y540_hid_transport *transport, uint8_t report_id,
                         const uint8_t *payload, size_t length,
                         y540_hid_error *error) {
  return transfer(transport, report_id, 1, payload, NULL, length, error);
}

int y540_hid_receive_report(y540_hid_transport *transport, uint8_t report_id,
                            uint8_t *payload, size_t length,
                            y540_hid_error *error) {
  return transfer(transport, report_id, 0, NULL, payload, length, error);
}



