#ifndef Y540_HID_TRANSPORT_H
#define Y540_HID_TRANSPORT_H

#include <stddef.h>
#include <stdint.h>
#include <wchar.h>

#define Y540_HID_REPORT_BYTES 64u
#define Y540_HID_PAYLOAD_BYTES 63u
#define Y540_HID_PATH_CHARS 1024u
#define Y540_HID_ATTEMPTS 10u

typedef struct {
    uint32_t code;
    char message[256];
} y540_hid_error;

typedef struct {
    wchar_t path[Y540_HID_PATH_CHARS];
    uint16_t vid, pid, usage_page, usage, feature_report_bytes;
    wchar_t hid_instance_id[1024];
    wchar_t usb_instance_id[1024];
    wchar_t usb_parent_id[1024];
    wchar_t usb_location[256];
} y540_hid_device;

/* All four identity fields must match. path may be NULL; multiple matches fail. */
typedef struct {
    uint16_t vid, pid, usage_page, usage;
    const wchar_t *path;
    const wchar_t *usb_parent_id;
    const wchar_t *usb_location;
} y540_hid_selector;

typedef int (*y540_hid_visit)(void *context, const y540_hid_device *device);
/* Return nonzero on success. On failure populate error. Buffer capacity is 64 bytes; report_bytes is the actual transfer length. */
typedef int (*y540_hid_feature_fn)(void *context, int is_write,
                                 uint8_t report[Y540_HID_REPORT_BYTES], size_t report_bytes,
                                 y540_hid_error *error);
typedef void (*y540_hid_sleep_fn)(void *context, uint32_t milliseconds);

typedef struct {
    void *context;
    y540_hid_feature_fn feature;
    y540_hid_sleep_fn sleep;
    uint32_t command_delay_ms;
    int owns_handle;
    y540_hid_device device;
} y540_hid_transport;

/* Enumeration only opens metadata handles with zero requested access. No feature I/O.
 * Inaccessible interfaces are skipped. Callback returns zero to stop successfully. */
typedef void (*y540_hid_trace_fn)(void *context, const char *line);
void y540_hid_set_trace(y540_hid_trace_fn trace, void *context);
int y540_hid_report_profile_valid(const y540_hid_device *device);
int y540_hid_identity_matches(const y540_hid_selector *, const y540_hid_device *);
int y540_hid_enumerate(y540_hid_visit visit, void *context, y540_hid_error *error);
/* Zero-initialize transport before first use. Never open an already open instance. */
int y540_hid_open(y540_hid_transport *transport, const y540_hid_selector *selector,
                  uint32_t command_delay_ms, y540_hid_error *error);
int y540_hid_validate_current(y540_hid_transport *transport, y540_hid_error *error);
void y540_hid_close(y540_hid_transport *transport);
/* Custom callbacks allow offline testing; custom context remains caller-owned. */
int y540_hid_init_custom(y540_hid_transport *transport, void *context,
                         y540_hid_feature_fn feature, y540_hid_sleep_fn sleep,
                         uint32_t command_delay_ms, y540_hid_error *error);
/* Report ID is zero; deterministic zero padding is intentional, unlike vendor malloc.
 * API failures retry up to ten attempts, sleeping 100 ms after every failure.
 * receive leaves the caller's buffer unchanged on failure. */
int y540_hid_send(y540_hid_transport *transport, const uint8_t *payload,
                  size_t length, y540_hid_error *error);
int y540_hid_receive(y540_hid_transport *transport, uint8_t *payload,
                     size_t length, y540_hid_error *error);
/* Main-mode custom-command handshake may use report ID 5A. Boot commands use 0. */
int y540_hid_send_report(y540_hid_transport *transport, uint8_t report_id,
                         const uint8_t *payload, size_t length, y540_hid_error *error);
int y540_hid_receive_report(y540_hid_transport *transport, uint8_t report_id,
                            uint8_t *payload, size_t length, y540_hid_error *error);

#endif
