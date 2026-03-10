#include "oneshot.h"

#ifndef ONESHOT_TAP_TOGGLE
#    define ONESHOT_TAP_TOGGLE 5
#endif

#ifndef ONESHOT_TIMEOUT
#    define ONESHOT_TIMEOUT 2000
#endif

// Tap tracker structure
typedef struct {
    uint8_t count;
    uint16_t timer;
    uint16_t timeout_timer;
} tap_tracker_t;

// Track tap counts and timing for each oneshot key
static tap_tracker_t os_shft_tap = {0, 0, 0};
static tap_tracker_t os_ctrl_tap = {0, 0, 0};
static tap_tracker_t os_alt_tap = {0, 0, 0};
static tap_tracker_t os_cmd_tap = {0, 0, 0};

// Helper function to get the tap tracker for a given mod
static tap_tracker_t *get_tap_tracker(uint16_t mod) {
    switch (mod) {
        case KC_LSFT:
            return &os_shft_tap;
        case KC_LCTL:
            return &os_ctrl_tap;
        case KC_LALT:
            return &os_alt_tap;
        case KC_LGUI:
            return &os_cmd_tap;
        default:
            return NULL;
    }
}

void update_oneshot(
    oneshot_state *state,
    uint16_t mod,
    uint16_t trigger,
    uint16_t keycode,
    keyrecord_t *record
) {
    tap_tracker_t *tap_tracker = get_tap_tracker(mod);

    if (keycode == trigger) {
        if (record->event.pressed) {
            // Trigger keydown
            if (*state == os_locked) {
                // If locked, unlock on tap
                *state = os_up_unqueued;
                unregister_code(mod);
                if (tap_tracker) tap_tracker->count = 0;
            } else {
                if (*state == os_up_unqueued) {
                    register_code(mod);
                }

                // Check for tap-toggle
                if (tap_tracker) {
                    if (timer_elapsed(tap_tracker->timer) < ONESHOT_TIMEOUT) {
                        tap_tracker->count++;
                    } else {
                        tap_tracker->count = 1;
                    }
                    tap_tracker->timer = timer_read();

                    if (tap_tracker->count >= ONESHOT_TAP_TOGGLE) {
                        *state = os_locked;
                        tap_tracker->count = 0;
                        return;
                    }
                }

                *state = os_down_unused;
            }
        } else {
            // Trigger keyup
            switch (*state) {
            case os_down_unused:
                // If we didn't use the mod while trigger was held, queue it.
                *state = os_up_queued;
                if (tap_tracker) tap_tracker->timeout_timer = timer_read();
                break;
            case os_down_used:
                // If we did use the mod while trigger was held, unregister it.
                *state = os_up_unqueued;
                unregister_code(mod);
                if (tap_tracker) tap_tracker->count = 0;
                break;
            case os_locked:
                // Stay locked
                break;
            default:
                break;
            }
        }
    } else {
        if (record->event.pressed) {
            if (is_oneshot_cancel_key(keycode) && *state != os_up_unqueued && *state != os_locked) {
                // Cancel oneshot on designated cancel keydown.
                *state = os_up_unqueued;
                unregister_code(mod);
                if (tap_tracker) tap_tracker->count = 0;
            }
        } else {
            if (!is_oneshot_ignored_key(keycode)) {
                // On non-ignored keyup, consider the oneshot used.
                switch (*state) {
                case os_down_unused:
                    *state = os_down_used;
                    break;
                case os_up_queued:
                    *state = os_up_unqueued;
                    unregister_code(mod);
                    if (tap_tracker) tap_tracker->count = 0;
                    break;
                case os_locked:
                    // Stay locked
                    break;
                default:
                    break;
                }
            }
        }
    }
}

void check_oneshot_timeout(oneshot_state *state, uint16_t mod) {
    if (*state == os_up_queued) {
        tap_tracker_t *tap_tracker = get_tap_tracker(mod);
        if (tap_tracker && timer_elapsed(tap_tracker->timeout_timer) > ONESHOT_TIMEOUT) {
            *state = os_up_unqueued;
            unregister_code(mod);
            tap_tracker->count = 0;
        }
    }
}
