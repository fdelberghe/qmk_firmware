#include QMK_KEYBOARD_H
#include "swapper.h"
#include "oneshot.h"

// Control/Escape and Navigation layer tap
#define ESC_CTL LCTL_T(KC_ESC)
#define GRV_CTL LCTL_T(KC_GRV)
#define ESC_NAV LT(NAV, KC_ESC)
#define SFT_BSC MT(MOD_LSFT, KC_BSPC)

enum layer_number {
  QWERTY = 0,
  EXT,
  SYM,
  NAV,
  FUNC,
  NUM,
};

#define LA_SYM MO(SYM)
#define LA_EXT MO(EXT)
#define LA_FUN MO(FUNC)
#define LA_NUM MO(NUM)
#define TT_NUM TT(NUM)
#define TT_NAV TT(NAV)

enum keycodes {
//     // Custom oneshot mod implementation with no timers.
    OS_SFT = SAFE_RANGE,
    OS_CTL,
    OS_ALT,
    OS_CMD,

    SW_WIN,  // Switch to next window         (cmd-tab)
    SW_TAB,  // Switch to next tab            (ctrl-tab)
};

// virtual desktop navigation
#define DST_PV LCTL(KC_LEFT)
#define DST_NX LCTL(KC_RIGHT)
#define DST_1 HYPR(KC_1)
#define DST_2 HYPR(KC_2)
#define DST_3 HYPR(KC_3)

// useful shortcuts
#define KC_COPY LGUI(KC_C)
#define KC_CUT  LGUI(KC_X)
#define KC_PSTE LGUI(KC_V)
#define KC_UNDO LGUI(KC_Z)
#define KC_SALL LGUI(KC_A)
#define KC_CNCL LCTL(KC_C)
#define KC_CT_W LCTL(KC_W)
#define KC_CT_R LCTL(KC_R)
#define KC_CM_P LGUI(KC_P)
#define KC_SPTL LGUI(KC_SPC)

// Combos
const uint16_t PROGMEM esc_combo[] = {KC_S, KC_D, COMBO_END};
const uint16_t PROGMEM tab_combo[] = {KC_D, KC_F, COMBO_END};
const uint16_t PROGMEM ent_combo[] = {KC_K, KC_L, COMBO_END};
const uint16_t PROGMEM bsp_combo[] = {KC_J, KC_K, COMBO_END};
const uint16_t PROGMEM del_combo[] = {KC_RPRN, KC_UNDS, COMBO_END};
const uint16_t PROGMEM pipe_combo[] = {KC_TILD, KC_BSLS, COMBO_END};
// Media combos
const uint16_t PROGMEM mute_combo[] = {KC_VOLD, KC_VOLU, COMBO_END};
const uint16_t PROGMEM play_combo[] = {KC_MPRV, KC_MNXT, COMBO_END};
// layer combos
const uint16_t PROGMEM nav_combo[] = {KC_A, KC_S, COMBO_END};
const uint16_t PROGMEM num_combo[] = {KC_L, KC_SCLN, COMBO_END};

combo_t key_combos[] = {
    COMBO(esc_combo, KC_ESC),
    COMBO(tab_combo, KC_TAB),
    COMBO(ent_combo, KC_ENT),
    COMBO(bsp_combo, KC_BSPC),
    COMBO(del_combo, KC_DEL),
    COMBO(pipe_combo, KC_PIPE),
    COMBO(mute_combo, KC_MUTE),
    COMBO(play_combo, KC_MPLY),
    COMBO(nav_combo, TT_NAV),
    COMBO(num_combo, TT_NUM),
};


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

[QWERTY] = LAYOUT(
  KC_GRV,   KC_1,   KC_2,    KC_3,    KC_4,    KC_5,                     KC_6,    KC_7,    KC_8,    KC_9,    KC_0,     KC_BSLS,
  KC_TAB,   KC_Q,   KC_W,    KC_E,    KC_R,    KC_T,                     KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,     KC_QUOT,
  ESC_NAV,  KC_A,   KC_S,    KC_D,    KC_F,    KC_G,                     KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN,  KC_ENT,
  KC_LCTL,  KC_Z,   KC_X,    KC_C,    KC_V,    KC_B,   XXXXXXX, XXXXXXX, KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH,  KC_BSLS,
                             KC_LALT, TT_NAV, KC_LSFT, LA_SYM, LA_EXT,   KC_SPC,  LA_NUM, XXXXXXX
),

[EXT] = LAYOUT(
  KC_TILD, _______, _______, _______, _______, _______,                   _______, _______, _______, _______, _______, _______,
  _______, KC_1,    KC_2,    KC_3,    KC_4,    KC_5,                      KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    _______,
  _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                   KC_BSPC, OS_SFT,  OS_CMD,  OS_ALT,  OS_CTL,  _______,
  _______, XXXXXXX, XXXXXXX, KC_PIPE, XXXXXXX, XXXXXXX, _______, _______, KC_VOLD, KC_VOLU, KC_MPRV, KC_MNXT, CW_TOGG, _______,
                             _______, _______, KC_BSPC, LA_SYM,  _______, _______, _______, _______
),

[SYM] = LAYOUT(
  KC_ESC,  _______, _______, _______, _______, _______,                   _______, _______, _______, _______, _______, _______,
  _______, KC_EXLM, KC_AT,   KC_LCBR, KC_RCBR, KC_PERC,                   KC_CIRC, KC_LBRC, KC_RBRC, KC_DLR,  KC_DQUO, _______,
  KC_UNDO, OS_CTL,  OS_ALT,  OS_CMD,  OS_SFT,  KC_HASH,                   KC_ASTR, KC_LPRN, KC_RPRN, KC_UNDS, KC_COLN, _______,
  _______, KC_GRV,  KC_TILD, KC_BSLS, KC_AMPR, KC_PLUS, _______, _______, KC_MINS, KC_EQL,  KC_LT,   KC_GT,   KC_QUOT, _______,
                             _______, _______, _______, _______, LA_EXT,  KC_SPTL, _______, _______
),

[NAV] = LAYOUT(
  KC_ESC,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,                      KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10, _______,
  _______, _______, _______, _______, _______, _______,                    KC_HOME, DST_PV,  DST_NX,  KC_END,  _______, _______,
  _______, TG(NAV), _______, SW_TAB,  SW_WIN,  _______,                    KC_LEFT, KC_DOWN, KC_UP,   KC_RIGHT,KC_BSPC, _______,
  _______, _______, KC_CUT,  KC_COPY, KC_PSTE, _______, _______, _______,  KC_HOME, KC_PGDN, KC_PGUP, KC_END,  _______,_______,
                             _______, _______, KC_BSPC, KC_DEL,  _______,  XXXXXXX, _______, _______
),

[FUNC] = LAYOUT(
  _______, _______, _______, _______, _______, _______,                   _______, _______, _______, _______, _______, _______,
  _______, KC_BRIU, KC_LPAD, KC_MCTL, KC_MUTE, KC_VOLU,                   _______, DST_PV,  DST_NX,  _______, KC_F12, _______,
  _______, KC_BRID, KC_MPRV, KC_MPLY, KC_MNXT, KC_VOLD,                   KC_HOME, KC_PGDN, KC_PGUP, KC_END,  KC_F11, _______,
  _______, KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5, _______, _______,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10, _______,
                             _______, _______, _______, _______, _______, _______, _______, _______
),

[NUM] = LAYOUT(
  _______, _______, _______, _______, _______, _______,                   _______, _______, _______, _______, _______, _______,
  _______, KC_SLSH, KC_7,    KC_8,    KC_9,    KC_ASTR,                   _______, _______, _______, _______, _______, _______,
  _______, KC_BSPC, KC_4,    KC_5,    KC_6,    KC_MINS,                   TG(NUM), _______, _______, _______, TG(NUM),  _______,
  _______, KC_DEL,  KC_1,    KC_2,    KC_3,    KC_PLUS, _______, _______, _______, _______, _______, _______, _______, _______,
                             _______, KC_0,    KC_DOT,  KC_ENT,  _______, _______, _______, _______
)

// [EXT] = LAYOUT(
//   KC_ESC,  _______, _______, _______, _______, _______,                   _______, _______, _______, _______, _______, _______,
//   _______, KC_1,    KC_2,    KC_3,    KC_4,    KC_5,                      KC_CIRC, KC_LBRC, KC_RBRC, KC_DLR,  KC_DQUO, _______,
//   KC_UNDO, OS_CTL,  OS_ALT,  OS_CMD,  OS_SFT,  SW_WIN,                    KC_ASTR, KC_LPRN, KC_RPRN, KC_UNDS, KC_COLN, _______,
//   _______, KC_GRV,  KC_CUT,  KC_COPY, KC_PSTE, SW_TAB,  _______, _______, KC_MINS, KC_EQL,  KC_LT,   KC_GT,   KC_QUOT, _______,
//                              _______, _______, _______, _______, _______, KC_SPTL, _______, _______
// ),
//
// [SYM] = LAYOUT(
//   KC_TILD, _______, _______, _______, _______, _______,                   _______, _______, _______, _______, _______, _______,
//   _______, KC_EXLM, KC_AT,   XXXXXXX, XXXXXXX, KC_PERC,                   KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    _______,
//   _______, KC_TILD, KC_BSLS, KC_LCBR, KC_RCBR, KC_HASH,                   TT_NUM,  OS_SFT,  OS_CMD,  OS_ALT,  OS_CTL,  _______,
//   _______, KC_GRV,  KC_PIPE, KC_AMPR, XXXXXXX, KC_PLUS, _______, _______, _______, _______, _______, _______, CW_TOGG,  _______,
//                              _______, CW_TOGG, KC_DEL,  _______, _______, _______, _______, _______
// ),
};

/* QWERTY Layer (Default)
 * ,-----------------------------------------.                    ,-----------------------------------------.
 * | ESC  |   1  |   2  |   3  |   4  |   5  |                    |   6  |   7  |   8  |   9  |   0  |  `   |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * | Tab  |   Q  |   W  |   E  |   R  |   T  |                    |   Y  |   U  |   I  |   O  |   P  |  -   |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |LCTRL |   A  |   S  |   D  |   F  |   G  |-------.    ,-------|   H  |   J  |   K  |   L  |   ;  |  '   |
 * |------+------+------+------+------+------|   [   |    |    ]  |------+------+------+------+------+------|
 * |LShift|   Z  |   X  |   C  |   V  |   B  |-------|    |-------|   N  |   M  |   ,  |   .  |   /  |RShift|
 * `-----------------------------------------/       /     \      \-----------------------------------------'
 *                   | LAlt | LGUI |LOWER | /Space  /       \Enter \  |RAISE |BackSP| RGUI |
 *                   |      |      |      |/       /         \      \ |      |      |      |
 *                   `----------------------------'           '------''--------------------'
 */


//SSD1306 OLED update loop, make sure to enable OLED_ENABLE=yes in rules.mk
#ifdef OLED_ENABLE

oled_rotation_t oled_init_user(oled_rotation_t rotation) {
  if (!is_keyboard_master())
    return OLED_ROTATION_180;  // flips the display 180 degrees if offhand
  return rotation;
}

// When you add source files to SRC in rules.mk, you can use functions.
const char *read_layer_state(void);
const char *read_logo(void);
const char *read_wpm(void);
const char *read_modifiers(void);

// const char *read_mode_icon(bool swap);
// const char *read_host_led_state(void);
// void set_timelog(void);
// const char *read_timelog(void);

bool oled_task_user(void) {
  if (is_keyboard_master()) {
    // If you want to change the display of OLED, you need to change here
    oled_write_ln(read_layer_state(), false);
    oled_write_ln(read_modifiers(), false);
    oled_write_ln(read_wpm(), false);

    //oled_write_ln(read_host_led_state(), false);
    // oled_write_ln(read_timelog(), false);
  } else {
    // oled_write(read_logo(), false);
    // draw_bongo(false);
    // draw_bongo(true);
  }
    return false;
}
#endif // OLED_ENABLE


bool is_oneshot_cancel_key(uint16_t keycode) {
    switch (keycode) {
    case LA_EXT:
    case LA_SYM:
        return true;
    default:
        return false;
    }
}

bool is_oneshot_ignored_key(uint16_t keycode) {
    switch (keycode) {
    case LA_SYM:
    case LA_EXT:
    case KC_LSFT:
    case OS_SFT:
    case OS_CTL:
    case OS_ALT:
    case OS_CMD:
    case SW_WIN:
    case SW_TAB:
    case ESC_NAV:
        return true;
    default:
        return false;
    }
}

// Swapper-specific ignored keys (excludes layer keys so releasing them closes the swapper)
bool is_swapper_ignored_key(uint16_t keycode) {
    switch (keycode) {
    case KC_LSFT:
    case OS_SFT:
    case OS_CTL:
    case OS_ALT:
    case OS_CMD:
    case SW_WIN:
    case SW_TAB:
        return true;
    default:
        return false;
    }
}

bool sw_win_active = false;
bool sw_tab_active = false;

oneshot_state os_shft_state = os_up_unqueued;
oneshot_state os_ctrl_state = os_up_unqueued;
oneshot_state os_alt_state = os_up_unqueued;
oneshot_state os_cmd_state = os_up_unqueued;

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    update_swapper(
        &sw_win_active, KC_LGUI, KC_TAB, SW_WIN,
        keycode, record
    );
    update_swapper(
        &sw_tab_active, KC_LCTL, KC_TAB, SW_TAB,
        keycode, record
    );

    update_oneshot(
        &os_shft_state, KC_LSFT, OS_SFT,
        keycode, record
    );
    update_oneshot(
        &os_ctrl_state, KC_LCTL, OS_CTL,
        keycode, record
    );
    update_oneshot(
        &os_alt_state, KC_LALT, OS_ALT,
        keycode, record
    );
    update_oneshot(
        &os_cmd_state, KC_LGUI, OS_CMD,
        keycode, record
    );

    // WPM is automatically tracked by QMK when WPM_ENABLE is set

    // Don't process these custom keycodes any further
    switch (keycode) {
        case SW_WIN:
        case SW_TAB:
        case OS_SFT:
        case OS_CTL:
        case OS_ALT:
        case OS_CMD:
            return false;
    }

    return true;
}

layer_state_t layer_state_set_user(layer_state_t state) {
    return update_tri_layer_state(state, SYM, EXT, FUNC);
}

void matrix_scan_user(void) {
    check_oneshot_timeout(&os_shft_state, KC_LSFT);
    check_oneshot_timeout(&os_ctrl_state, KC_LCTL);
    check_oneshot_timeout(&os_alt_state, KC_LALT);
    check_oneshot_timeout(&os_cmd_state, KC_LGUI);
}
