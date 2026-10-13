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
/* fix5: bootloader contact timing.
 * The 2026-10-13 ETW recording shows the boot-mode device (048D:89DB) enumerate
 * about 0.5 s after the 09 handoff, sit idle while the old updater slept for the
 * SHFU.ini DELAY (6 s), be selectively suspended by Windows, and then fail every
 * transfer after resume (USBD 0xC0000011, zero bytes). Contact the boot device
 * as soon as it enumerates instead of sleeping first. */
typedef int (*y540_boot_find_fn)(void *context, y540_hid_transport *transport,
                                 y540_hid_error *error);
typedef uint64_t (*y540_clock_fn)(void *context);
/* Poll find() every poll_ms until it succeeds, fails with a non-transient
 * error, or budget_ms elapses. Transient: NOT_FOUND, FILE/PATH_NOT_FOUND and
 * DEVICE_NOT_CONNECTED (device still starting). Sends no device command. */
int y540_wait_boot_device(y540_boot_find_fn find, void *find_context,
                          y540_hid_transport *transport,
                          y540_hid_sleep_fn sleep, y540_clock_fn clock,
                          void *time_context, uint32_t poll_ms,
                          uint32_t budget_ms, y540_progress_fn progress,
                          void *progress_context, y540_hid_error *error);
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
/* fix7: read-only dump of flash [start,end) (1 KiB aligned, end <= 0x20000) to a
 * NEW file. Chip qualification and port binding as in the update path; only
 * read commands and a final reset are sent. */
int y540_dump_flash_device(const y540_config *cfg, const wchar_t *out_path,
                           uint32_t start, uint32_t end,
                           y540_progress_fn progress, void *context,
                           y540_hid_error *error);
#endif
