#include "device_state.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <wctype.h>

#ifdef _WIN32
#include <windows.h>
#include <setupapi.h>
#include <cfgmgr32.h>
#include <initguid.h>
#include <devpkey.h>
#endif

static int starts_ci(const wchar_t *text, const wchar_t *prefix)
{
    while (*prefix) {
        if (towupper(*text++) != towupper(*prefix++)) return 0;
    }
    return 1;
}

static int contains_ci(const wchar_t *text, const wchar_t *part)
{
    for (; *text; ++text) if (starts_ci(text, part)) return 1;
    return 0;
}

static int equals_ci(const wchar_t *a, const wchar_t *b)
{
    while (*a && *b) if (towupper(*a++) != towupper(*b++)) return 0;
    return !*a && !*b;
}

static int is_hub_controller(const y540_device_item *item)
{
    return contains_ci(item->service, L"HUB") ||
           contains_ci(item->service, L"XHCI") ||
           contains_ci(item->service, L"EHCI") ||
           contains_ci(item->service, L"UHCI") ||
           contains_ci(item->service, L"OHCI") ||
           contains_ci(item->service, L"USBPORT") ||
           contains_ci(item->hardware_ids, L"ROOT_HUB") ||
           contains_ci(item->compatible_ids, L"CLASS_09") ||
           contains_ci(item->compatible_ids, L"ROOT_HUB");
}

static int physical_product(const wchar_t *id, const wchar_t *prefix)
{
    size_t n = wcslen(prefix);
    return starts_ci(id, prefix) && (id[n] == L'&' || id[n] == L'\\') &&
           !contains_ci(id, L"&MI_");
}

void y540_device_classify(y540_device_item *item)
{
    int forbidden;
    if (!item) return;
    item->kind = Y540_DEVICE_OTHER;
    item->can_recover = 0;
    item->can_case_recover = 0;
    strcpy(item->recovery_reason, "Inventory only: device identity is not an approved physical ITE keyboard.");
    if (physical_product(item->instance_id, L"USB\\VID_048D&PID_C100"))
        item->kind = Y540_DEVICE_KEYBOARD_NORMAL;
    else if (physical_product(item->instance_id, L"USB\\VID_048D&PID_89DB"))
        item->kind = Y540_DEVICE_KEYBOARD_BOOT;
    else if (physical_product(item->instance_id, L"USB\\VID_0000&PID_0002")) {
        item->kind = Y540_DEVICE_DESCRIPTOR_FAILURE;
        strcpy(item->recovery_reason, "Inventory only: failed USB descriptors do not establish keyboard identity, even at a historical keyboard port.");
        if (equals_ci(item->instance_id, L"USB\\VID_0000&PID_0002\\5&1F456139&0&9") &&
            equals_ci(item->parent_id, L"USB\\ROOT_HUB30\\4&15ed8360&0&0") &&
            equals_ci(item->location, L"Port_#0009.Hub_#0002") &&
            equals_ci(item->hardware_ids, L"USB\\DEVICE_DESCRIPTOR_FAILURE") &&
            equals_ci(item->class_name, L"USB") && item->present &&
            !item->present_result && !item->cm_result && item->problem == 43 &&
            !is_hub_controller(item)) {
            item->can_case_recover = 1;
            strcpy(item->recovery_reason, "Case-specific opt-in restart candidate: exact recorded problem-43 instance, parent and location match. Keyboard identity and recovery remain unproven.");
        }
    }
    if (item->kind != Y540_DEVICE_KEYBOARD_NORMAL &&
        item->kind != Y540_DEVICE_KEYBOARD_BOOT) return;
    forbidden = is_hub_controller(item);
    if (forbidden) {
        strcpy(item->recovery_reason, "Refused: hub/controller metadata is excluded from recovery.");
    } else if (!item->present || item->present_result != 0) {
        strcpy(item->recovery_reason, "Inventory only: this is a historical or unavailable devnode.");
    } else if (item->cm_result != 0) {
        strcpy(item->recovery_reason, "Inventory only: live configuration-manager status is unavailable.");
    } else if (item->unavailable_properties & ((1u << 6) | (1u << 8))) {
        strcpy(item->recovery_reason, "Inventory only: service or compatible-ID metadata needed for recovery validation is unavailable.");
    } else {
        item->can_recover = 1;
        strcpy(item->recovery_reason, "Eligible only for an explicitly confirmed restart of this exact physical ITE USB devnode; recovery is unproven.");
    }
}

void y540_device_state_init(y540_device_state *state)
{
    if (!state) return;
    memset(state, 0, sizeof(*state));
    state->ac_line_status = state->battery_percent = 255;
}

void y540_device_state_free(y540_device_state *state)
{
    if (!state) return;
    free(state->items);
    y540_device_state_init(state);
}

static int fail(y540_device_error *error, uint32_t code, const char *message)
{
    if (error) { error->code = code; snprintf(error->message, sizeof(error->message), "%s", message); }
    return 0;
}

#ifdef _WIN32
static void flatten(wchar_t *value, size_t chars, DWORD bytes)
{
    size_t n = bytes / sizeof(wchar_t), i;
    if (n >= chars) n = chars - 1;
    value[n] = 0;
    for (i = 0; i + 1 < n; ++i) {
        if (!value[i] && value[i + 1]) value[i] = L'|';
        if (value[i] == L'\r' || value[i] == L'\n') value[i] = L' ';
    }
}

static int registry_text(HDEVINFO set, SP_DEVINFO_DATA *dev, DWORD key,
                         wchar_t *value, size_t chars)
{
    DWORD type = 0, bytes = 0;
    memset(value, 0, chars * sizeof(wchar_t));
    if (!SetupDiGetDeviceRegistryPropertyW(set, dev, key, &type,
            (BYTE *)value, (DWORD)(chars * sizeof(wchar_t)), &bytes)) {
        value[0] = 0;
        return 0;
    }
    if (type != REG_SZ && type != REG_MULTI_SZ && type != REG_EXPAND_SZ) {
        value[0] = 0;
        return 0;
    }
    flatten(value, chars, bytes);
    return 1;
}

static int device_text(HDEVINFO set, SP_DEVINFO_DATA *dev, const DEVPROPKEY *key,
                       wchar_t *value, size_t chars)
{
    DEVPROPTYPE type = 0;
    DWORD bytes = 0;
    memset(value, 0, chars * sizeof(wchar_t));
    if (!SetupDiGetDevicePropertyW(set, dev, key, &type, (BYTE *)value,
            (DWORD)(chars * sizeof(wchar_t)), &bytes, 0)) {
        value[0] = 0;
        return 0;
    }
    if (type != DEVPROP_TYPE_STRING && type != DEVPROP_TYPE_STRING_LIST) {
        value[0] = 0;
        return 0;
    }
    flatten(value, chars, bytes);
    return 1;
}

static void read_item(HDEVINFO set, SP_DEVINFO_DATA *dev, y540_device_item *item)
{
    DEVINST parent, live;
    ULONG status = 0, problem = 0;
    memset(item, 0, sizeof(*item));
    if (!SetupDiGetDeviceInstanceIdW(set, dev, item->instance_id,
            Y540_DEVICE_TEXT_CHARS, NULL)) {
        item->instance_id[0] = 0;
        item->unavailable_properties |= 1u;
    }
    item->cm_result = CM_Get_DevNode_Status(&status, &problem, dev->DevInst, 0);
    item->status = status;
    item->problem = problem;
    item->present_result = item->instance_id[0] ?
        CM_Locate_DevNodeW(&live, item->instance_id, CM_LOCATE_DEVNODE_NORMAL) : CR_INVALID_DEVICE_ID;
    item->present = item->present_result == CR_SUCCESS;
    if (CM_Get_Parent(&parent, dev->DevInst, 0) != CR_SUCCESS ||
        CM_Get_Device_IDW(parent, item->parent_id, Y540_DEVICE_TEXT_CHARS, 0) != CR_SUCCESS) {
        if (!device_text(set, dev, &DEVPKEY_Device_Parent, item->parent_id,
                         Y540_DEVICE_TEXT_CHARS)) item->unavailable_properties |= 1u << 1;
    }
    if (!registry_text(set, dev, SPDRP_DEVICEDESC, item->description, Y540_DEVICE_TEXT_CHARS))
        item->unavailable_properties |= 1u << 2;
    if (!device_text(set, dev, &DEVPKEY_Device_BusReportedDeviceDesc,
                     item->bus_description, Y540_DEVICE_TEXT_CHARS)) item->unavailable_properties |= 1u << 3;
    if (!registry_text(set, dev, SPDRP_LOCATION_INFORMATION, item->location, Y540_DEVICE_TEXT_CHARS))
        item->unavailable_properties |= 1u << 4;
    if (!registry_text(set, dev, SPDRP_LOCATION_PATHS, item->location_paths, Y540_DEVICE_IDS_CHARS))
        item->unavailable_properties |= 1u << 5;
    if (!registry_text(set, dev, SPDRP_SERVICE, item->service, 128)) item->unavailable_properties |= 1u << 6;
    if (!registry_text(set, dev, SPDRP_HARDWAREID, item->hardware_ids, Y540_DEVICE_IDS_CHARS))
        item->unavailable_properties |= 1u << 7;
    if (!registry_text(set, dev, SPDRP_COMPATIBLEIDS, item->compatible_ids, Y540_DEVICE_IDS_CHARS))
        item->unavailable_properties |= 1u << 8;
    if (!registry_text(set, dev, SPDRP_CLASS, item->class_name, 128)) item->unavailable_properties |= 1u << 9;
    y540_device_classify(item);
}

static int relevant(const y540_device_item *item)
{
    return starts_ci(item->instance_id, L"USB\\") || starts_ci(item->instance_id, L"HID\\") ||
           starts_ci(item->class_name, L"Keyboard") || starts_ci(item->class_name, L"HIDClass") ||
           starts_ci(item->class_name, L"USB") || contains_ci(item->hardware_ids, L"VID_048D");
}

int y540_device_state_collect(y540_device_state *state, y540_device_error *error)
{
    HDEVINFO set;
    SP_DEVINFO_DATA dev;
    DWORD index, end_error;
    SYSTEM_POWER_STATUS power;
    SYSTEMTIME now;
    y540_device_item *item;
    if (!state) return fail(error, ERROR_INVALID_PARAMETER, "Missing state object.");
    y540_device_state_free(state);
    if (error) memset(error, 0, sizeof(*error));
    GetSystemTime(&now);
    snprintf(state->collected_utc, sizeof(state->collected_utc),
             "%04u-%02u-%02uT%02u:%02u:%02uZ", now.wYear, now.wMonth, now.wDay,
             now.wHour, now.wMinute, now.wSecond);
    if (GetSystemPowerStatus(&power)) {
        state->ac_line_status = power.ACLineStatus;
        state->battery_percent = power.BatteryLifePercent;
    } else state->power_error = GetLastError();
    set = SetupDiGetClassDevsW(NULL, NULL, NULL, DIGCF_ALLCLASSES);
    if (set == INVALID_HANDLE_VALUE) return fail(error, GetLastError(), "SetupDiGetClassDevsW failed.");
    item = malloc(sizeof(*item));
    if (!item) { SetupDiDestroyDeviceInfoList(set); return fail(error, ERROR_NOT_ENOUGH_MEMORY, "Cannot allocate metadata scratch."); }
    for (index = 0; ; ++index) {
        memset(&dev, 0, sizeof(dev));
        dev.cbSize = sizeof(dev);
        if (!SetupDiEnumDeviceInfo(set, index, &dev)) break;
        read_item(set, &dev, item);
        if (!relevant(item)) continue;
        if (state->count == state->capacity) {
            size_t capacity = state->capacity ? state->capacity * 2 : 32;
            y540_device_item *grown;
            if (capacity > 8192) {
                free(item); SetupDiDestroyDeviceInfoList(set);
                return fail(error, ERROR_NOT_ENOUGH_MEMORY, "Inventory limit reached; collection is incomplete.");
            }
            grown = realloc(state->items, capacity * sizeof(*grown));
            if (!grown) {
                free(item); SetupDiDestroyDeviceInfoList(set);
                return fail(error, ERROR_NOT_ENOUGH_MEMORY, "Cannot grow metadata inventory; collection is incomplete.");
            }
            state->items = grown;
            state->capacity = capacity;
        }
        state->items[state->count++] = *item;
    }
    end_error = GetLastError();
    free(item);
    SetupDiDestroyDeviceInfoList(set);
    if (end_error != ERROR_NO_MORE_ITEMS)
        return fail(error, end_error, "SetupDiEnumDeviceInfo failed; collection is incomplete.");
    return 1;
}

static int restart_target(const wchar_t *exact_instance_id, int permit_case,
                           y540_device_error *error)
{
    HDEVINFO set;
    SP_DEVINFO_DATA dev;
    y540_device_item *item;
    CONFIGRET result, enable_result;
    unsigned attempt;
    if (error) memset(error, 0, sizeof(*error));
    if (!exact_instance_id || !*exact_instance_id ||
        wcslen(exact_instance_id) >= Y540_DEVICE_TEXT_CHARS)
        return fail(error, ERROR_INVALID_PARAMETER, "An exact device instance ID is required.");
    set = SetupDiCreateDeviceInfoList(NULL, NULL);
    if (set == INVALID_HANDLE_VALUE) return fail(error, GetLastError(), "Cannot create device metadata set.");
    memset(&dev, 0, sizeof(dev));
    dev.cbSize = sizeof(dev);
    if (!SetupDiOpenDeviceInfoW(set, exact_instance_id, NULL, 0, &dev)) {
        DWORD code = GetLastError();
        SetupDiDestroyDeviceInfoList(set);
        return fail(error, code, "Exact device instance is unavailable; nothing changed.");
    }
    item = malloc(sizeof(*item));
    if (!item) { SetupDiDestroyDeviceInfoList(set); return fail(error, ERROR_NOT_ENOUGH_MEMORY, "Cannot allocate metadata scratch; nothing changed."); }
    read_item(set, &dev, item);
    if (_wcsicmp(exact_instance_id, item->instance_id) ||
        (!item->can_recover && !(permit_case && item->can_case_recover))) {
        char reason[256];
        snprintf(reason, sizeof(reason), "%s", item->recovery_reason);
        free(item); SetupDiDestroyDeviceInfoList(set);
        return fail(error, ERROR_ACCESS_DENIED, reason);
    }
    /* Deliberately no CM_DISABLE_PERSIST: a reboot must not retain our disable. */
    result = item->problem == CM_PROB_DISABLED ? CR_SUCCESS :
        CM_Disable_DevNode(dev.DevInst, CM_DISABLE_UI_NOT_OK);
    free(item);
    if (result != CR_SUCCESS) {
        SetupDiDestroyDeviceInfoList(set);
        return fail(error, result, "Windows refused the per-device disable; run elevated if authorized. No firmware command was sent.");
    }
    enable_result = CR_FAILURE;
    for (attempt = 0; attempt < 3; ++attempt) {
        enable_result = CM_Enable_DevNode(dev.DevInst, 0);
        if (enable_result == CR_SUCCESS) break;
        if (attempt + 1 < 3) Sleep(250);
    }
    SetupDiDestroyDeviceInfoList(set);
    if (enable_result != CR_SUCCESS)
        return fail(error, enable_result, "Device disable succeeded but re-enable FAILED after three attempts. Re-enable this exact device in Device Manager or reboot. No firmware command was sent.");
    return 1;
}

int y540_device_restart(const wchar_t *exact_instance_id, y540_device_error *error)
{ return restart_target(exact_instance_id, 0, error); }

int y540_device_restart_case_target(const wchar_t *exact_instance_id, y540_device_error *error)
{ return restart_target(exact_instance_id, 1, error); }
#else
int y540_device_state_collect(y540_device_state *state, y540_device_error *error)
{ (void)state; return fail(error, 1, "Windows metadata collection is unavailable on this platform."); }
int y540_device_restart(const wchar_t *id, y540_device_error *error)
{ (void)id; return fail(error, 1, "Windows per-device restart is unavailable on this platform."); }
int y540_device_restart_case_target(const wchar_t *id, y540_device_error *error)
{ (void)id; return fail(error, 1, "Windows per-device restart is unavailable on this platform."); }
#endif

static void log_wide(y540_device_log_fn log, void *context, const char *name,
                      const wchar_t *value)
{
    char utf8[Y540_DEVICE_IDS_CHARS * 4], line[Y540_DEVICE_IDS_CHARS * 4 + 80];
#ifdef _WIN32
    if (!WideCharToMultiByte(CP_UTF8, 0, value, -1, utf8, sizeof(utf8), NULL, NULL))
        strcpy(utf8, "<UTF-8 conversion failed>");
#else
    if (wcstombs(utf8, value, sizeof(utf8)) == (size_t)-1)
        strcpy(utf8, "<text conversion failed>");
    utf8[sizeof(utf8) - 1] = 0;
#endif
    snprintf(line, sizeof(line), "  %s=%s", name, utf8);
    log(context, line);
}

void y540_device_state_log(const y540_device_state *state,
                           y540_device_log_fn log, void *context)
{
    size_t i;
    char line[768];
    if (!state || !log) return;
    snprintf(line, sizeof(line), "PnP metadata inventory UTC=%s count=%lu AC=%lu battery_percent=%lu power_error=%lu",
             state->collected_utc, (unsigned long)state->count,
             (unsigned long)state->ac_line_status, (unsigned long)state->battery_percent,
             (unsigned long)state->power_error);
    log(context, line);
    log(context, "AC values: 0=battery, 1=AC, 255=unknown. Metadata only; no HID commands were sent.");
    log(context, "Unavailable-property bits: 0 instance, 1 parent, 2 description, 3 bus description, 4 location, 5 location paths, 6 service, 7 hardware IDs, 8 compatible IDs, 9 class.");
    for (i = 0; i < state->count; ++i) {
        const y540_device_item *item = &state->items[i];
        snprintf(line, sizeof(line), "device[%lu] present=%d kind=%d status=0x%08lX problem=%lu CM=0x%08lX presence_CM=0x%08lX unavailable=0x%08lX can_recover=%d can_case_recover=%d",
                 (unsigned long)i, item->present, item->kind, (unsigned long)item->status,
                 (unsigned long)item->problem, (unsigned long)item->cm_result,
                 (unsigned long)item->present_result, (unsigned long)item->unavailable_properties,
                 item->can_recover, item->can_case_recover);
        log(context, line);
        log_wide(log, context, "instance_id", item->instance_id);
        log_wide(log, context, "parent_id", item->parent_id);
        log_wide(log, context, "class", item->class_name);
        log_wide(log, context, "service", item->service);
        log_wide(log, context, "description", item->description);
        log_wide(log, context, "bus_description", item->bus_description);
        log_wide(log, context, "location", item->location);
        log_wide(log, context, "location_paths", item->location_paths);
        log_wide(log, context, "hardware_ids", item->hardware_ids);
        log_wide(log, context, "compatible_ids", item->compatible_ids);
        snprintf(line, sizeof(line), "  recovery=%s", item->recovery_reason);
        log(context, line);
    }
}
