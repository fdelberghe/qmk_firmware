#pragma once

#include QMK_KEYBOARD_H

// Implements cmd-tab like behaviour on a single key. On first tap of trigger
// cmdish is held and tabish is tapped -- cmdish then remains held until some
// other key is hit or released. For example:
//
//     trigger, trigger, a -> cmd down, tab, tab, cmd up, a
//     nav down, trigger, nav up -> nav down, cmd down, tab, cmd up, nav up
//
// This behaviour is useful for more than just cmd-tab, hence: cmdish, tabish.
void update_swapper(
    bool *active,
    uint16_t cmdish,
    uint16_t tabish,
    uint16_t trigger,
    uint16_t keycode,
    keyrecord_t *record,
    uint16_t *timer
);

// Keys for which update_swapper() keeps cmdish held (e.g. shift for the
// reverse direction). Defined in the keymap.
bool is_swapper_ignored_key(uint16_t keycode);

// Release cmdish once SWAPPER_TIMEOUT ms have passed since the last trigger.
void check_swapper_timeout(bool *active, uint16_t cmdish, uint16_t *timer);
