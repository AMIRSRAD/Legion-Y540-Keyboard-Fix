/* Offline classification/logging fixtures only. Never collects live metadata or
 * invokes y540_device_restart. */
#include "../src/device_state.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static y540_device_item *fixture(const wchar_t *id)
{
    y540_device_item *item = calloc(1, sizeof(*item));
    assert(item);
    wcscpy(item->instance_id, id);
    item->present = 1;
    wcscpy(item->service, L"HidUsb");
    wcscpy(item->compatible_ids, L"USB\\Class_03&SubClass_00&Prot_00");
    return item;
}

typedef struct { unsigned lines; int saw_id, saw_power, saw_unknown; } log_state;
static void capture(void *context, const char *line)
{
    log_state *state = context;
    ++state->lines;
    if (strstr(line, "USB\\VID_0000&PID_0002")) state->saw_id = 1;
    if (strstr(line, "AC=1")) state->saw_power = 1;
    if (strstr(line, "do not establish keyboard identity")) state->saw_unknown = 1;
}

int main(void)
{
    y540_device_item *item = fixture(L"USB\\VID_048D&PID_C100\\5&ABC&0&3");
    y540_device_state state;
    log_state logs = {0};
    y540_device_classify(item);
    assert(item->kind == Y540_DEVICE_KEYBOARD_NORMAL && item->can_recover);
    wcscpy(item->instance_id, L"usb\\vid_048d&pid_89db\\5&ABC&0&3");
    y540_device_classify(item);
    assert(item->kind == Y540_DEVICE_KEYBOARD_BOOT && item->can_recover);
    item->present = 0;
    y540_device_classify(item);
    assert(!item->can_recover);
    item->present = 1;
    item->cm_result = 13;
    y540_device_classify(item);
    assert(!item->can_recover);
    item->cm_result = 0;
    item->unavailable_properties = 1u << 6;
    y540_device_classify(item);
    assert(!item->can_recover);
    item->unavailable_properties = 0;
    wcscpy(item->service, L"USBHUB3");
    y540_device_classify(item);
    assert(!item->can_recover);
    wcscpy(item->service, L"USBXHCI");
    y540_device_classify(item);
    assert(!item->can_recover);
    wcscpy(item->service, L"HidUsb");
    wcscpy(item->compatible_ids, L"USB\\Class_09&SubClass_00&Prot_01");
    y540_device_classify(item);
    assert(!item->can_recover);
    wcscpy(item->compatible_ids, L"USB\\Class_03");
    wcscpy(item->instance_id, L"USB\\VID_048D&PID_C100&MI_00\\ABC");
    y540_device_classify(item);
    assert(!item->can_recover);
    wcscpy(item->instance_id, L"HID\\VID_048D&PID_C100\\ABC");
    y540_device_classify(item);
    assert(!item->can_recover);
    wcscpy(item->instance_id, L"USB\\VID_048D&PID_C1000\\ABC");
    y540_device_classify(item);
    assert(!item->can_recover);
    wcscpy(item->instance_id, L"USB\\VID_0000&PID_0002\\5&ABC&0&3");
    wcscpy(item->location_paths, L"PCIROOT(0)#PCI(1400)#USBROOT(0)#USB(3)");
    item->problem = 43;
    y540_device_classify(item);
    assert(item->kind == Y540_DEVICE_DESCRIPTOR_FAILURE && !item->can_recover);
    /* The unknown remains denied unless every recorded live case field agrees. */
    wcscpy(item->instance_id, L"USB\\VID_0000&PID_0002\\5&1F456139&0&9");
    wcscpy(item->parent_id, L"USB\\ROOT_HUB30\\4&15ed8360&0&0");
    wcscpy(item->location, L"Port_#0009.Hub_#0002");
    wcscpy(item->class_name, L"USB");
    wcscpy(item->hardware_ids, L"USB\\DEVICE_DESCRIPTOR_FAILURE");
    y540_device_classify(item);
    assert(!item->can_recover && item->can_case_recover);
    wcscpy(item->hardware_ids, L"USB\\OTHER_FAILURE");
    y540_device_classify(item);
    assert(!item->can_case_recover);
    item->hardware_ids[0] = 0;
    y540_device_classify(item);
    assert(!item->can_case_recover);
    wcscpy(item->hardware_ids, L"USB\\DEVICE_DESCRIPTOR_FAILURE");
    wcscpy(item->parent_id, L"USB\\ROOT_HUB30\\4&DIFFERENT&0&0");
    y540_device_classify(item);
    assert(!item->can_case_recover);
    wcscpy(item->parent_id, L"USB\\ROOT_HUB30\\4&15ed8360&0&0");
    wcscpy(item->location, L"Port_#0008.Hub_#0002");
    y540_device_classify(item);
    assert(!item->can_case_recover);
    wcscpy(item->location, L"Port_#0009.Hub_#0002");
    wcscpy(item->instance_id, L"USB\\VID_0000&PID_0002\\5&OTHER&0&9");
    y540_device_classify(item);
    assert(!item->can_case_recover);
    wcscpy(item->instance_id, L"USB\\VID_0000&PID_0002\\5&1F456139&0&9");
    wcscpy(item->service, L"USBHUB3");
    y540_device_classify(item);
    assert(!item->can_case_recover);
    wcscpy(item->service, L"");
    item->unavailable_properties = 1u << 6;
    y540_device_classify(item);
    assert(item->can_case_recover); /* Failed descriptors can lack a service. */
    item->problem = 10;
    y540_device_classify(item);
    assert(!item->can_case_recover);
    item->problem = 43;
    item->present = 0;
    y540_device_classify(item);
    assert(!item->can_case_recover);
    item->present = 1;
    wcscpy(item->class_name, L"Keyboard");
    y540_device_classify(item);
    assert(!item->can_case_recover);
    y540_device_state_init(&state);
    state.items = item;
    state.count = state.capacity = 1;
    state.ac_line_status = 1;
    y540_device_state_log(&state, capture, &logs);
    assert(logs.lines > 10 && logs.saw_id && logs.saw_power && logs.saw_unknown);
    y540_device_state_free(&state);
    assert(!state.items && !state.count && state.ac_line_status == 255);
    puts("Device-state offline fixtures passed; no Windows device APIs were executed.");
    return 0;
}
