#define WIN32_LEAN_AND_MEAN
#include "power_policy.h"
#include <windows.h>
#include <powrprof.h>
#include <string.h>

static const GUID usb_subgroup = {0x2a737441, 0x1930, 0x4402,
                                  {0x8d, 0x77, 0xb2, 0xbe, 0xbb, 0xa3, 0x08, 0xa3}};
static const GUID usb_selective_suspend = {0x48e6b7a6, 0x50f5, 0x4782,
                                           {0xa5, 0xd4, 0x53, 0xbb, 0x8f, 0x07, 0xe2, 0x26}};

int y540_read_usb_suspend_policy(y540_usb_suspend_policy *policy)
{
    GUID *scheme = NULL;
    DWORD ac = 0, dc = 0;
    if (!policy) return 0;
    memset(policy, 0, sizeof(*policy));
    if (PowerGetActiveScheme(NULL, &scheme) != ERROR_SUCCESS || !scheme) return 0;
    if (PowerReadACValueIndex(NULL, scheme, &usb_subgroup, &usb_selective_suspend, &ac) == ERROR_SUCCESS &&
        PowerReadDCValueIndex(NULL, scheme, &usb_subgroup, &usb_selective_suspend, &dc) == ERROR_SUCCESS) {
        policy->readable = 1;
        policy->ac_enabled = ac;
        policy->dc_enabled = dc;
    }
    LocalFree(scheme);
    return policy->readable;
}

int y540_usb_suspend_may_idle_device(const y540_usb_suspend_policy *policy)
{
    /* Unknown policy is treated as "may idle": the safe assumption. */
    return !policy || !policy->readable || policy->ac_enabled || policy->dc_enabled;
}
