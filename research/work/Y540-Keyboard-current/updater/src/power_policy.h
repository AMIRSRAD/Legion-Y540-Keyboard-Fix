#ifndef Y540_POWER_POLICY_H
#define Y540_POWER_POLICY_H

/* Read-only look at the active Windows power plan's "USB selective suspend"
 * setting (subgroup 2a737441-1930-4402-8d77-b2bebba308a3, setting
 * 48e6b7a6-50f5-4782-a5d4-53bb8f07e226). 1 = enabled, 0 = disabled.
 * Nothing is ever written. */
typedef struct {
    int readable;
    unsigned long ac_enabled;
    unsigned long dc_enabled;
} y540_usb_suspend_policy;

int y540_read_usb_suspend_policy(y540_usb_suspend_policy *policy);
/* True when the active plan can idle (selectively suspend) the keyboard's USB
 * device on the power source that is currently in use or could be used. */
int y540_usb_suspend_may_idle_device(const y540_usb_suspend_policy *policy);

#endif
