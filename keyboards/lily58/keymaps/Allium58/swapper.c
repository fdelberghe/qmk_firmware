#include "swapper.h"

// Forward declaration
bool is_swapper_ignored_key(uint16_t keycode);

void update_swapper(
    bool *active,
    uint16_t cmdish,
    uint16_t tabish,
    uint16_t trigger,
    uint16_t keycode,
    keyrecord_t *record
) {
    if (keycode == trigger) {
        if (record->event.pressed) {
            if (!*active) {
                *active = true;
                register_code(cmdish);
            }
            register_code(tabish);
        } else {
            unregister_code(tabish);
            // Don't unregister cmdish until some other key is hit or released.
        }
    } else if (*active && !is_swapper_ignored_key(keycode)) {
        // Only close the swapper if the key is not in the ignored list
        unregister_code(cmdish);
        *active = false;
    }
}

