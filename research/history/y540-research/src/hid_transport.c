/* Windows HID transport reconstructed from static updater evidence 030/031/040/051.
 * No claim of hardware compatibility follows from successful compilation. */
#include "hid_transport.h"
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <setupapi.h>
#include <hidsdi.h>
#include <hidpi.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifndef NT_SUCCESS
#define NT_SUCCESS(status) (((NTSTATUS)(status)) >= 0)
#endif

static int fail(y540_hid_error *error, DWORD code, const char *message)
{
    if (error) {
        error->code = code ? code : ERROR_GEN_FAILURE;
        snprintf(error->message, sizeof(error->message), "%s", message);
    }
    return 0;
}

static void clear_error(y540_hid_error *error)
{
    if (error) memset(error, 0, sizeof(*error));
}

static int inspect(HANDLE handle, const wchar_t *path, y540_hid_device *device,
                   y540_hid_error *error)
{
    HIDD_ATTRIBUTES attributes;
    PHIDP_PREPARSED_DATA preparsed = NULL;
    HIDP_CAPS caps;
    NTSTATUS status;
    size_t length = wcslen(path);
    if (length >= Y540_HID_PATH_CHARS)
        return fail(error, ERROR_BUFFER_OVERFLOW, "HID interface path exceeds storage capacity");
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

int y540_hid_enumerate(y540_hid_visit visit, void *context, y540_hid_error *error)
{
    GUID hid_guid;
    HDEVINFO devices;
    DWORD index;
    int result = 1;
    clear_error(error);
    if (!visit) return fail(error, ERROR_INVALID_PARAMETER, "Enumeration callback is required");
    HidD_GetHidGuid(&hid_guid);
    devices = SetupDiGetClassDevsW(&hid_guid, NULL, NULL, DIGCF_PRESENT | DIGCF_DEVICEINTERFACE);
    if (devices == INVALID_HANDLE_VALUE)
        return fail(error, GetLastError(), "SetupDiGetClassDevsW failed");
    for (index = 0; ; ++index) {
        SP_DEVICE_INTERFACE_DATA interface_data;
        PSP_DEVICE_INTERFACE_DETAIL_DATA_W detail;
        DWORD needed = 0;
        DWORD code;
        HANDLE handle;
        y540_hid_device device;
        int keep_going;
        memset(&interface_data, 0, sizeof(interface_data));
        interface_data.cbSize = sizeof(interface_data);
        if (!SetupDiEnumDeviceInterfaces(devices, NULL, &hid_guid, index, &interface_data)) {
            code = GetLastError();
            if (code != ERROR_NO_MORE_ITEMS)
                result = fail(error, code, "SetupDiEnumDeviceInterfaces failed");
            break;
        }
        SetupDiGetDeviceInterfaceDetailW(devices, &interface_data, NULL, 0, &needed, NULL);
        code = GetLastError();
        if (code != ERROR_INSUFFICIENT_BUFFER || needed < sizeof(*detail)) {
            result = fail(error, code, "Unable to determine HID interface detail size");
            break;
        }
        detail = (PSP_DEVICE_INTERFACE_DETAIL_DATA_W)malloc(needed);
        if (!detail) { result = fail(error, ERROR_NOT_ENOUGH_MEMORY, "HID detail allocation failed"); break; }
        memset(detail, 0, needed);
        detail->cbSize = sizeof(*detail);
        if (!SetupDiGetDeviceInterfaceDetailW(devices, &interface_data, detail, needed, NULL, NULL)) {
            code = GetLastError();
            free(detail);
            result = fail(error, code, "SetupDiGetDeviceInterfaceDetailW failed");
            break;
        }
        handle = CreateFileW(detail->DevicePath, 0, FILE_SHARE_READ | FILE_SHARE_WRITE,
                             NULL, OPEN_EXISTING, 0, NULL);
        if (handle == INVALID_HANDLE_VALUE) { free(detail); continue; }
        if (!inspect(handle, detail->DevicePath, &device, NULL)) {
            CloseHandle(handle);
            free(detail);
            continue;
        }
        CloseHandle(handle);
        free(detail);
        keep_going = visit(context, &device);
        if (!keep_going) break;
    }
    SetupDiDestroyDeviceInfoList(devices);
    return result;
}

static int matches(const y540_hid_selector *selector, const y540_hid_device *device)
{
    return selector->vid == device->vid && selector->pid == device->pid &&
           selector->usage_page == device->usage_page && selector->usage == device->usage &&
           (!selector->path || _wcsicmp(selector->path, device->path) == 0);
}

typedef struct {
    const y540_hid_selector *selector;
    size_t count;
    y540_hid_device selected;
} selection;

static int select_device(void *context, const y540_hid_device *device)
{
    selection *candidate = (selection *)context;
    if (matches(candidate->selector, device)) {
        ++candidate->count;
        candidate->selected = *device;
    }
    return 1;
}

static int windows_feature(void *context, int is_write, uint8_t report[64], y540_hid_error *error)
{
    BOOLEAN ok = is_write ? HidD_SetFeature((HANDLE)context, report, 64)
                          : HidD_GetFeature((HANDLE)context, report, 64);
    if (!ok) return fail(error, GetLastError(), is_write ? "HidD_SetFeature failed" : "HidD_GetFeature failed");
    return 1;
}

static void windows_sleep(void *context, uint32_t milliseconds)
{
    (void)context;
    Sleep(milliseconds);
}

int y540_hid_open(y540_hid_transport *transport, const y540_hid_selector *selector,
                  uint32_t command_delay_ms, y540_hid_error *error)
{
    selection candidate;
    HANDLE handle;
    y540_hid_device actual;
    clear_error(error);
    if (!transport || !selector)
        return fail(error, ERROR_INVALID_PARAMETER, "Transport and exact device selector are required");
    if (transport->feature || transport->owns_handle)
        return fail(error, ERROR_ALREADY_EXISTS, "Close the current transport before opening");
    memset(&candidate, 0, sizeof(candidate));
    candidate.selector = selector;
    if (!y540_hid_enumerate(select_device, &candidate, error)) return 0;
    if (!candidate.count) return fail(error, ERROR_NOT_FOUND, "No HID interface matches every selector field");
    if (candidate.count > 1) return fail(error, ERROR_DUP_NAME, "Multiple matching HID interfaces; specify an exact path");
    if (candidate.selected.feature_report_bytes != 64)
        return fail(error, ERROR_BAD_LENGTH, "Selected HID interface does not advertise 64-byte feature reports");
    /* Feature IOCTLs are FILE_ANY_ACCESS. The original also requests access 0;
     * asking for read/write can reject keyboard collections unnecessarily. */
    handle = CreateFileW(candidate.selected.path, 0,
                         FILE_SHARE_READ | FILE_SHARE_WRITE, NULL, OPEN_EXISTING, 0, NULL);
    if (handle == INVALID_HANDLE_VALUE) return fail(error, GetLastError(), "Opening selected HID interface failed");
    if (!inspect(handle, candidate.selected.path, &actual, error)) { CloseHandle(handle); return 0; }
    if (!matches(selector, &actual) || actual.feature_report_bytes != 64) {
        CloseHandle(handle);
        return fail(error, ERROR_DEVICE_NOT_CONNECTED, "HID identity or report size changed before open completed");
    }
    memset(transport, 0, sizeof(*transport));
    transport->context = handle;
    transport->feature = windows_feature;
    transport->sleep = windows_sleep;
    transport->command_delay_ms = command_delay_ms;
    transport->owns_handle = 1;
    transport->device = actual;
    return 1;
}

void y540_hid_close(y540_hid_transport *transport)
{
    if (!transport) return;
    if (transport->owns_handle && transport->context) CloseHandle((HANDLE)transport->context);
    memset(transport, 0, sizeof(*transport));
}

int y540_hid_init_custom(y540_hid_transport *transport, void *context,
                         y540_hid_feature_fn feature, y540_hid_sleep_fn sleep,
                         uint32_t command_delay_ms, y540_hid_error *error)
{
    clear_error(error);
    if (!transport || !feature || !sleep)
        return fail(error, ERROR_INVALID_PARAMETER, "Transport, feature and sleep callbacks are required");
    if (transport->feature || transport->owns_handle)
        return fail(error, ERROR_ALREADY_EXISTS, "Close the current transport before initializing");
    memset(transport, 0, sizeof(*transport));
    transport->context = context;
    transport->feature = feature;
    transport->sleep = sleep;
    transport->command_delay_ms = command_delay_ms;
    return 1;
}

static int transfer(y540_hid_transport *transport, uint8_t report_id, int is_write, const uint8_t *input,
                    uint8_t *output, size_t length, y540_hid_error *error)
{
    unsigned attempt;
    y540_hid_error local_error;
    clear_error(error);
    if (!transport || !transport->feature || !transport->sleep ||
        length > Y540_HID_PAYLOAD_BYTES || (length && !(is_write ? input : output)))
        return fail(error, ERROR_INVALID_PARAMETER, "Open transport and payload length 0..63 are required");
    if (transport->command_delay_ms)
        transport->sleep(transport->context, transport->command_delay_ms);
    for (attempt = 0; attempt < Y540_HID_ATTEMPTS; ++attempt) {
        uint8_t report[Y540_HID_REPORT_BYTES] = {0};
        report[0] = report_id;
        clear_error(&local_error);
        if (is_write && length) memcpy(report + 1, input, length);
        if (transport->feature(transport->context, is_write, report, &local_error)) {
            if (!is_write && length) memcpy(output, report + 1, length);
            clear_error(error);
            return 1;
        }
        if (!local_error.code) fail(&local_error, ERROR_GEN_FAILURE, "Feature callback failed without an error code");
        if (error) *error = local_error;
        transport->sleep(transport->context, 100);
    }
    return 0;
}

int y540_hid_send(y540_hid_transport *transport, const uint8_t *payload,
                  size_t length, y540_hid_error *error)
{
    return transfer(transport, 0, 1, payload, NULL, length, error);
}

int y540_hid_receive(y540_hid_transport *transport, uint8_t *payload,
                     size_t length, y540_hid_error *error)
{
    return transfer(transport, 0, 0, NULL, payload, length, error);
}

int y540_hid_send_report(y540_hid_transport *transport, uint8_t report_id,
                         const uint8_t *payload, size_t length, y540_hid_error *error)
{
    return transfer(transport, report_id, 1, payload, NULL, length, error);
}

int y540_hid_receive_report(y540_hid_transport *transport, uint8_t report_id,
                            uint8_t *payload, size_t length, y540_hid_error *error)
{
    return transfer(transport, report_id, 0, NULL, payload, length, error);
}
