#include QMK_KEYBOARD_H
#include <stdio.h>
#include <string.h>

char modifier_state_str[24];

const char *read_modifiers(void) {
    uint8_t modifiers = get_mods();

    // Build compact modifier string: S=Shift C=Ctrl A=Alt G=Gui
    char mods[12] = "";
    if (modifiers & MOD_MASK_SHIFT) strcat(mods, "S-");
    if (modifiers & MOD_MASK_CTRL)  strcat(mods, "C-");
    if (modifiers & MOD_MASK_ALT)   strcat(mods, "A-");
    if (modifiers & MOD_MASK_GUI)   strcat(mods, "G ");

    if (mods[0] == '\0') {
        snprintf(modifier_state_str, sizeof(modifier_state_str), "Mods: -");
    } else {
        // Remove trailing space
        mods[strlen(mods) - 1] = '\0';
        snprintf(modifier_state_str, sizeof(modifier_state_str), "Mods: %s", mods);
    }

    return modifier_state_str;
}

