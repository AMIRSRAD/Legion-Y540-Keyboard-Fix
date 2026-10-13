#define WIN32_LEAN_AND_MEAN
#include "session_log.h"
#include <stdarg.h>
#include <stdio.h>
#include <string.h>
#include <wchar.h>
#include <windows.h>
static SRWLOCK lock = SRWLOCK_INIT;
static HANDLE file = INVALID_HANDLE_VALUE;
static wchar_t path[2048], directory[2048];
static LONG sequence;
static int mkdir_one(const wchar_t *p) {
  return CreateDirectoryW(p, NULL) || GetLastError() == ERROR_ALREADY_EXISTS;
}
const wchar_t *y540_log_path(void) { return path; }
const wchar_t *y540_log_directory(void) { return directory; }
void y540_log_close(void) {
  AcquireSRWLockExclusive(&lock);
  if (file != INVALID_HANDLE_VALUE) {
    FlushFileBuffers(file);
    CloseHandle(file);
    file = INVALID_HANDLE_VALUE;
  }
  ReleaseSRWLockExclusive(&lock);
}
int y540_log_begin(const char *action, char *error, size_t cap) {
  wchar_t executable[1800], *slash, base[1800];
  SYSTEMTIME now;
  unsigned i;
  y540_log_close();
  path[0] = 0;
  directory[0] = 0;
  DWORD n = GetModuleFileNameW(NULL, executable, 1800);
  if (!n || n >= 1800) {
    snprintf(error, cap, "Cannot resolve log location");
    return 0;
  }
  slash = wcsrchr(executable, L'\\');
  if (slash)
    *slash = 0;
  swprintf(directory, 2048, L"%ls\\logs", executable);
  if (!mkdir_one(directory)) {
    n = GetEnvironmentVariableW(L"LOCALAPPDATA", base, 1800);
    if (!n || n >= 1800) {
      snprintf(error, cap, "Cannot create log folder");
      return 0;
    }
    swprintf(directory, 2048, L"%ls\\Y540Updater-fix9", base);
    if (!mkdir_one(directory)) {
      snprintf(error, cap, "Cannot create user log folder");
      return 0;
    }
    wcscat(directory, L"\\logs");
    if (!mkdir_one(directory)) {
      snprintf(error, cap, "Cannot create user logs");
      return 0;
    }
  }
  GetSystemTime(&now);
  for (i = 0; i < 100; i++) {
    swprintf(
        path, 2048, L"%ls\\fix9-%04u%02u%02uT%02u%02u%02u%03uZ-p%lu-%lu.log",
        directory, now.wYear, now.wMonth, now.wDay, now.wHour, now.wMinute,
        now.wSecond, now.wMilliseconds, (unsigned long)GetCurrentProcessId(),
        (unsigned long)InterlockedIncrement(&sequence));
    file = CreateFileW(path, GENERIC_WRITE, FILE_SHARE_READ, NULL, CREATE_NEW,
                       FILE_ATTRIBUTE_NORMAL, NULL);
    if (file != INVALID_HANDLE_VALUE)
      break;
    if (GetLastError() != ERROR_FILE_EXISTS)
      break;
  }
  if (file == INVALID_HANDLE_VALUE) {
    snprintf(error, cap, "Cannot create session log (Win32 %lu)",
             (unsigned long)GetLastError());
    return 0;
  }
  y540_logf("session action=%s version=fix9-0.9.0 utc_timestamps=1", action);
  return 1;
}
void y540_logf(const char *format, ...) {
  char content[8192], line[8704];
  SYSTEMTIME now;
  DWORD written;
  va_list args;
  va_start(args, format);
  vsnprintf(content, sizeof(content), format, args);
  va_end(args);
  GetSystemTime(&now);
  snprintf(line, sizeof(line),
           "%04u-%02u-%02uT%02u:%02u:%02u.%03uZ tick=%llu %s\r\n", now.wYear,
           now.wMonth, now.wDay, now.wHour, now.wMinute, now.wSecond,
           now.wMilliseconds, (unsigned long long)GetTickCount64(), content);
  AcquireSRWLockExclusive(&lock);
  if (file != INVALID_HANDLE_VALUE) {
    WriteFile(file, line, (DWORD)strlen(line), &written, NULL);
    FlushFileBuffers(file);
  }
  ReleaseSRWLockExclusive(&lock);
}
int y540_log_named_path(const wchar_t *prefix, wchar_t *out, size_t chars) {
  SYSTEMTIME now;
  if (!out || chars < 1 || !directory[0])
    return 0;
  GetSystemTime(&now);
  int n = swprintf(
      out, chars,
      L"%ls\\%ls-%04u%02u%02uT%02u%02u%02u%03uZ-p%lu-%lu.bin",
      directory, prefix, now.wYear, now.wMonth, now.wDay, now.wHour, now.wMinute,
      now.wSecond, now.wMilliseconds, (unsigned long)GetCurrentProcessId(),
      (unsigned long)InterlockedIncrement(&sequence));
  return n > 0 && (size_t)n < chars;
}

int y540_log_backup_path(wchar_t *out, size_t chars) {
  return y540_log_named_path(L"before-flash", out, chars);
}
