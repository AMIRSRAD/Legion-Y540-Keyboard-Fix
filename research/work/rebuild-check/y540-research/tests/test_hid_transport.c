/* Offline only: the custom backend never calls Windows device APIs. */
#include "../src/hid_transport.h"
#include <assert.h>
#include <string.h>
#include <stdio.h>

typedef struct {
    unsigned calls, failures, sleeps, retry_sleeps, delay_sleeps;
    int writes;
    uint8_t last_report[64];
} fake_state;

static int fake_feature(void *context, int is_write, uint8_t report[64], y540_hid_error *error)
{
    fake_state *state = context;
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

int main(void)
{
    y540_hid_transport transport = {0};
    y540_hid_error error;
    fake_state state = {0};
    const uint8_t command[] = {0xC1, 0x00, 0x01, 0x01, 0xAB};
    uint8_t answer[] = {0x55, 0x55, 0x55};
    unsigned i;
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
    assert(!y540_hid_init_custom(&transport, &state, fake_feature, fake_sleep, 7, &error));
    y540_hid_close(&transport);
    assert(!transport.feature && !transport.context);
    assert(!y540_hid_send(&transport, command, sizeof(command), &error));
    puts("HID transport offline tests passed");
    return 0;
}
