#ifndef Y540_SESSION_LOG_H
#define Y540_SESSION_LOG_H
#include <stddef.h>
#include <wchar.h>
int y540_log_begin(const char *action, char *error, size_t cap);
void y540_logf(const char *format, ...);
void y540_log_close(void);
const wchar_t *y540_log_path(void);
const wchar_t *y540_log_directory(void);
int y540_log_backup_path(wchar_t *out, size_t chars);
int y540_log_named_path(const wchar_t *prefix, wchar_t *out, size_t chars);
#endif
