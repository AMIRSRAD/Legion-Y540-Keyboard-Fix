/* Offline only: the custom backend never calls Windows device APIs. */
#include "../src/hid_transport.h"
#include <assert.h>
#include <string.h>
#include <stdio.h>

typedef struct {
    unsigned calls, failures, sleeps, retry_sleeps, delay_sleeps, expected_bytes;
    int writes;
    uint8_t last_report[64];
} fake_state;

static int fake_feature(void *context, int is_write, uint8_t report[64], size_t report_bytes, y540_hid_error *error)
{
    fake_state *state = context;
    assert(report_bytes == (state->expected_bytes ? state->expected_bytes : 64u));
    ++state->calls;
    state->writes = is_write;
    memcpy(state->last_report, report, 64);
    if (state->calls <= state->failures) {
        /* Simulate failed APIs corrupting their scratch buffer. */
        memset(report, 0xEE, 64);
        error->code = 1234;
        strcpy(error->message, "simulated failure");
        return 0;
    }
    if (!is_write) {
        report[1] = 0xD0;
        report[2] = 0x34;
        report[3] = 0x12;
    }
    return 1;
}

static void fake_sleep(void *context, uint32_t milliseconds)
{
    fake_state *state = context;
    ++state->sleeps;
    if (milliseconds == 100) ++state->retry_sleeps;
    else { assert(milliseconds == 7); ++state->delay_sleeps; }
}

typedef struct { unsigned lines; int saw_failure, saw_tx, saw_rx; } trace_state;
static void capture_trace(void *context, const char *line)
{
    trace_state *state = context;
    ++state->lines;
    if (strstr(line, "success=0")) state->saw_failure = 1;
    if (strstr(line, "HID TX")) state->saw_tx = 1;
    if (strstr(line, "HID RX")) state->saw_rx = 1;
}

static void physical_identity_fixtures(void)
{
    y540_hid_device device = {0};
    y540_hid_selector selector = {0};
    selector.vid = device.vid = 0x048D;
    selector.pid = device.pid = 0x89DB;
    selector.usage_page = device.usage_page = 0xFF00;
    selector.usage = device.usage = 1;
    wcscpy(device.path, L"fixture-path");
    wcscpy(device.usb_parent_id, L"USB\\ROOT_HUB30\\CASE-HUB");
    wcscpy(device.usb_location, L"Port_#0009.Hub_#0002");
    selector.usb_parent_id = L"usb\\root_hub30\\case-hub";
    selector.usb_location = L"port_#0009.hub_#0002";
    assert(y540_hid_identity_matches(&selector, &device));
    selector.usb_location = L"Port_#0008.Hub_#0002";
    assert(!y540_hid_identity_matches(&selector, &device));
    selector.usb_location = NULL;
    selector.usb_parent_id = L"USB\\ROOT_HUB30\\OTHER-HUB";
    assert(!y540_hid_identity_matches(&selector, &device));
    selector.usb_parent_id = NULL;
    selector.path = L"different-path";
    assert(!y540_hid_identity_matches(&selector, &device));
    selector.path = L"FIXTURE-PATH";
    assert(y540_hid_identity_matches(&selector, &device));
    device.pid = 0xC100;
    assert(!y540_hid_identity_matches(&selector, &device));
}

int main(void)
{
    y540_hid_transport transport = {0};
    y540_hid_error error;
    fake_state state = {0};
    trace_state traces = {0};
    const uint8_t command[] = {0xC1, 0x00, 0x01, 0x01, 0xAB};
    uint8_t answer[] = {0x55, 0x55, 0x55};
    unsigned i;
    physical_identity_fixtures();
    {
      y540_hid_device d = {0};
      d.vid=0x048d; d.pid=0xc100; d.usage_page=0xff89; d.usage=0x10; d.feature_report_bytes=17;
      assert(y540_hid_report_profile_valid(&d));
      d.feature_report_bytes=64; assert(!y540_hid_report_profile_valid(&d));
      d.feature_report_bytes=3; d.usage=0xcd; assert(!y540_hid_report_profile_valid(&d));
      d.pid=0x89db; d.usage=0xdb; d.feature_report_bytes=64;
      assert(y540_hid_report_profile_valid(&d));
      d.feature_report_bytes=17; assert(!y540_hid_report_profile_valid(&d));
      y540_hid_transport normal={0}; fake_state ns={0}; uint8_t payload[17]={0};
      ns.expected_bytes=17;
      assert(y540_hid_init_custom(&normal,&ns,fake_feature,fake_sleep,0,&error));
      normal.device.vid=0x048d; normal.device.pid=0xc100;
      normal.device.usage_page=0xff89; normal.device.usage=0x10; normal.device.feature_report_bytes=17;
      assert(y540_hid_send_report(&normal,0x5a,payload,16,&error));
      assert(y540_hid_receive_report(&normal,0x5a,payload,16,&error));
      assert(ns.calls==2);
      assert(!y540_hid_send_report(&normal,0x5a,payload,17,&error));
      assert(!y540_hid_send_report(&normal,0,payload,1,&error));
      assert(ns.calls==2);
      y540_hid_close(&normal);
    }
    y540_hid_set_trace(capture_trace, &traces);
    assert(y540_hid_init_custom(&transport, &state, fake_feature, fake_sleep, 7, &error));
    state.failures = 2;
    assert(y540_hid_send(&transport, command, sizeof(command), &error));
    assert(!error.code && state.calls == 3 && state.writes);
    assert(state.retry_sleeps == 2 && state.delay_sleeps == 1);
    assert(state.last_report[0] == 0);
    assert(!memcmp(state.last_report + 1, command, sizeof(command)));
    for (i = 1 + sizeof(command); i < 64; ++i) assert(!state.last_report[i]);

    memset(&state, 0, sizeof(state));
    assert(y540_hid_receive(&transport, answer, sizeof(answer), &error));
    assert(answer[0] == 0xD0 && answer[1] == 0x34 && answer[2] == 0x12);
    for (i = 0; i < 64; ++i) assert(!state.last_report[i]);

    memset(&state, 0, sizeof(state));
    state.failures = 1;
    assert(y540_hid_send_report(&transport, 0x5A, command, sizeof(command), &error));
    assert(state.calls == 2 && state.last_report[0] == 0x5A);
    assert(!memcmp(state.last_report + 1, command, sizeof(command)));
    memset(&state, 0, sizeof(state));
    assert(y540_hid_receive_report(&transport, 0x5A, answer, sizeof(answer), &error));
    assert(state.last_report[0] == 0x5A && answer[0] == 0xD0);
    for (i = 1; i < 64; ++i) assert(!state.last_report[i]);

    memset(&state, 0, sizeof(state));
    state.failures = 10;
    memset(answer, 0x55, sizeof(answer));
    assert(!y540_hid_receive(&transport, answer, sizeof(answer), &error));
    assert(error.code == 1234 && state.calls == 10);
    assert(state.retry_sleeps == 10 && state.delay_sleeps == 1);
    for (i = 0; i < sizeof(answer); ++i) assert(answer[i] == 0x55);
    for (i = 0; i < 64; ++i) assert(!state.last_report[i]);

    memset(&state, 0, sizeof(state));
    assert(!y540_hid_send(&transport, command, 64, &error));
    assert(error.code && state.calls == 0 && state.sleeps == 0);
    assert(!y540_hid_receive(&transport, NULL, 1, &error));
    assert(state.calls == 0 && state.sleeps == 0);
    assert(y540_hid_validate_current(&transport, &error)); /* Memory backend only. */
    assert(!y540_hid_init_custom(&transport, &state, fake_feature, fake_sleep, 7, &error));
    y540_hid_close(&transport);
    assert(!transport.feature && !transport.context);
    assert(!y540_hid_send(&transport, command, sizeof(command), &error));
    assert(traces.lines && traces.saw_failure && traces.saw_tx && traces.saw_rx);
    y540_hid_set_trace(NULL, NULL);
    puts("HID transport offline tests passed");
    return 0;
}
