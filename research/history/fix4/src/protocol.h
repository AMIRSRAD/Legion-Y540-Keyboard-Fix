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
typedef int (*y540_boot_reopen_fn)(void *context, y540_hid_transport *transport,
                                  y540_hid_error *error);
/* Only generic failure31 is retried after a chip request; invalid chip replies
 * remain terminal. Reopen may transiently return NOT_FOUND. Never flashes. */
int y540_wait_boot_chip(y540_hid_transport *transport, uint16_t expected,
                       y540_boot_reopen_fn reopen, void *reopen_context,
                       y540_progress_fn progress, void *progress_context,
                       y540_hid_error *error);
int y540_enter_boot(y540_hid_transport *main_transport, y540_hid_error *error);
/* Main-device handoff and boot discovery. Explicit call performs device writes.
 */
int y540_update_device(const uint8_t *firmware, size_t size,
                       const y540_config *cfg, y540_progress_fn progress,
                       void *context, y540_hid_error *error);
/* fix1 requires a new, explicit backup file before any device handoff. The
 * entire 54 KiB update region is read twice, compared and durably saved before
 * erase. Existing files are never overwritten. Legacy entry points above fail
 * without device I/O because they cannot provide a backup destination. */
int y540_boot_program_with_backup(y540_hid_transport *transport,
                      const uint8_t *firmware, size_t size,
                      const y540_config *cfg, const wchar_t *backup_path,
                      y540_progress_fn progress, void *context,
                      y540_hid_error *error);
int y540_update_device_with_backup(const uint8_t *firmware, size_t size,
                       const y540_config *cfg, const wchar_t *backup_path,
                       y540_progress_fn progress, void *context,
                       y540_hid_error *error);
/* Only for an already selected normal interface; report 5A, never a guessed
 * interface/report ID. Bounded reproduction of HidCustomCmdInit(0). */
int y540_exit_custom_mode(y540_hid_transport *transport,
                          y540_hid_error *error);
#endif
