/* File-only test: no device enumeration, feature I/O, or device restart. */
#include "../src/session_log.h"
#include <assert.h>
#include <stdio.h>
#include <string.h>
#include <windows.h>

int main(void)
{
    wchar_t first[2048], second[2048], backup1[2048], backup2[2048];
    char error[256], content[4096];
    DWORD read;
    HANDLE file;
    assert(y540_log_begin("offline-log-test", error, sizeof(error)));
    wcscpy(first, y540_log_path());
    y540_logf("fixture utf8=\xD8\xA2 value=%d", 123);
    assert(y540_log_backup_path(backup1, 2048));
    assert(y540_log_backup_path(backup2, 2048));
    assert(wcscmp(backup1, backup2));
    assert(wcsstr(backup1, L"before-flash-") && wcsstr(backup1, L".bin"));
    assert(GetFileAttributesW(backup1) == INVALID_FILE_ATTRIBUTES);
    y540_log_close();
    file = CreateFileW(first, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, 0, NULL);
    assert(file != INVALID_HANDLE_VALUE);
    assert(ReadFile(file, content, sizeof(content) - 1, &read, NULL));
    content[read] = 0;
    assert(strstr(content, "session action=offline-log-test"));
    assert(strstr(content, "fixture utf8=\xD8\xA2 value=123"));
    assert(strstr(content, "Z tick="));
    CloseHandle(file);
    assert(y540_log_begin("offline-log-test-2", error, sizeof(error)));
    wcscpy(second, y540_log_path());
    assert(wcscmp(first, second));
    y540_log_close();
    assert(DeleteFileW(first) && DeleteFileW(second));
    puts("Session log file/UTF-8/unique-path tests passed; no device access.");
    return 0;
}
