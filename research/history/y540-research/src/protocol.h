#ifndef Y540_PROTOCOL_H
#define Y540_PROTOCOL_H
#include "core.h"
#include "hid_transport.h"
typedef void (*y540_progress_fn)(void *context, const char *phase,
                                 size_t completed, size_t total);
/* Recovered normal full-image path. No erase-only/docking/parameter special
 * modes. */
int y540_boot_program(y540_hid_transport *t, const uint8_t *firmware,
                      size_t size, const y540_config *cfg,
                      y540_progress_fn progress, void *context,
                      y540_hid_error *error);
int y540_check_boot_chip(y540_hid_transport *t, uint16_t expected,
                         y540_hid_error *error);
int y540_enter_boot(y540_hid_transport *main_transport, y540_hid_error *error);
/* Main-device handoff and boot discovery. Explicit call performs device writes.
 */
int y540_update_device(const uint8_t *firmware, size_t size,
                       const y540_config *cfg, y540_progress_fn progress,
                       void *context, y540_hid_error *error);
#endif
