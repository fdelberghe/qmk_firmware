#include "swapper.h"

#ifndef SWAPPER_TIMEOUT
#    define SWAPPER_TIMEOUT 6000
#endif

void update_swapper(
    bool *active,
    uint16_t cmdish,
    uint16_t tabish,
    uint16_t trigger,
    uint16_t keycode,
    keyrecord_t *record,
    uint16_t *timer
) {
    if (keycode == trigger) {
        if (record->event.pressed) {
            if (!*active) {
                *active = true;
                register_code(cmdish);
            }
            register_code(tabish);
            *timer = timer_read();
        } else {
            unregister_code(tabish);
            // Don't unregister cmdish until some other key is hit or released.
        }
    } else if (*active && !is_swapper_ignored_key(keycode)) {
        unregister_code(cmdish);
        *active = false;
    }
}


void check_swapper_timeout(bool *active, uint16_t cmdish, uint16_t *timer) {
    if (*active && timer_elapsed(*timer) > SWAPPER_TIMEOUT) {
        unregister_code(cmdish);
        *active = false;
    }
}
