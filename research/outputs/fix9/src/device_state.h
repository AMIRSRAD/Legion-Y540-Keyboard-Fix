#ifndef Y540_DEVICE_STATE_H
#define Y540_DEVICE_STATE_H

#include <stddef.h>
#include <stdint.h>
#include <wchar.h>

#define Y540_DEVICE_TEXT_CHARS 1024u
#define Y540_DEVICE_IDS_CHARS 4096u

typedef struct {
    uint32_t code;
    char message[512];
} y540_device_error;

typedef enum {
    Y540_DEVICE_OTHER = 0,
    Y540_DEVICE_KEYBOARD_NORMAL,
    Y540_DEVICE_KEYBOARD_BOOT,
    Y540_DEVICE_DESCRIPTOR_FAILURE
} y540_device_kind;

typedef struct {
    wchar_t instance_id[Y540_DEVICE_TEXT_CHARS];
    wchar_t parent_id[Y540_DEVICE_TEXT_CHARS];
    wchar_t description[Y540_DEVICE_TEXT_CHARS];
    wchar_t bus_description[Y540_DEVICE_TEXT_CHARS];
    wchar_t location[Y540_DEVICE_TEXT_CHARS];
    wchar_t location_paths[Y540_DEVICE_IDS_CHARS];
    wchar_t hardware_ids[Y540_DEVICE_IDS_CHARS];
    wchar_t compatible_ids[Y540_DEVICE_IDS_CHARS];
    wchar_t class_name[128];
    wchar_t service[128];
    uint32_t status, problem, cm_result, present_result;
    uint32_t unavailable_properties; /* Bit mask documented in diagnostic log. */
    int present;
    y540_device_kind kind;
    int can_recover;
    int can_case_recover; /* Exact recorded case topology only; still opt-in. */
    char recovery_reason[256];
} y540_device_item;

typedef struct {
    y540_device_item *items;
    size_t count, capacity;
    uint32_t ac_line_status; /* 0 battery, 1 AC, 255 unknown. */
    uint32_t battery_percent; /* 255 unknown. */
    uint32_t power_error;
    char collected_utc[48];
} y540_device_state;

typedef void (*y540_device_log_fn)(void *context, const char *line);

/* Zero initialization is also valid. Collection only reads SetupAPI/CM metadata
 * and power status. It never opens HID handles or sends feature reports. All
 * USB, HIDClass and Keyboard devnodes, including historical entries, are kept. */
void y540_device_state_init(y540_device_state *state);
void y540_device_state_free(y540_device_state *state);
int y540_device_state_collect(y540_device_state *state, y540_device_error *error);
void y540_device_state_log(const y540_device_state *state,
                           y540_device_log_fn log, void *context);

/* Pure classification: safe for synthetic offline fixtures. can_recover means
 * narrowly eligible for an explicitly selected restart, never a diagnosis or
 * promise of repair. Failed USB descriptors cannot prove device identity. */
void y540_device_classify(y540_device_item *item);

/* MUTATING, opt-in API: caller must show exact instance ID and obtain explicit
 * user confirmation. Revalidates live metadata and permits only a present,
 * known ITE C100/89DB physical USB devnode. Never disables a hub/controller,
 * guesses from port history, changes power policy, installs drivers or flashes.
 * Requires elevation. Disable is nonpersistent; enable is attempted immediately
 * and retried on failure. A failed enable is reported, never hidden. */
int y540_device_restart(const wchar_t *exact_instance_id,
                        y540_device_error *error);
/* Same opt-in/elevation contract, with one additional allowed case: problem 43
 * USB\\VID_0000&PID_0002\\5&1F456139&0&9 under the recorded exact ROOT_HUB30
 * instance and Port_#0009.Hub_#0002. Requires all live fields to match. A port
 * match is a case-specific recovery hypothesis, not device identity proof. */
int y540_device_restart_case_target(const wchar_t *exact_instance_id,
                                   y540_device_error *error);

#endif
