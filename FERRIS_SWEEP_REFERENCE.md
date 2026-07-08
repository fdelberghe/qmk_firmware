# Ferris Sweep Keymap Reference

Reference for the `ferris/sweep` keymap `fdelberghe` (QMK, RP2040). Kept on the
`ferris_sweep` git branch. This is a **34-key** board: a 3×10 alpha grid plus
2+2 thumbs. Missing physical keys (Esc, Enter, Bspc, layer toggles) are provided
by **combos** instead.

- Keymap: `keyboards/ferris/sweep/keymaps/fdelberghe/keymap.c`
- Build: `qmk compile -kb ferris/sweep -km fdelberghe`

## Features (rules.mk)

| Feature | Setting |
|---------|---------|
| Link-Time Optimization | `LTO_ENABLE` |
| N-Key Rollover | `NKRO_ENABLE` |
| Caps Word | `CAPS_WORD_ENABLE` |
| Combos | `COMBO_ENABLE` |
| Repeat Key (`QK_REP`) | `REPEAT_KEY_ENABLE` |
| Custom modules | `oneshot.c`, `swapper.c` |

## Config (config.h)

| Define | Value | Notes |
|--------|-------|-------|
| `TAPPING_TERM` | 180 | global tap/hold decision window |
| `TAPPING_TOGGLE` | 2 | taps to lock a `TT()` layer |
| `ONESHOT_TAP_TOGGLE` | 3 | taps to lock a oneshot mod |
| `ONESHOT_TIMEOUT` | 1500 | ms before a queued oneshot expires |
| `ONESHOT_TAPPING_TERM` | 200 | hold vs. tap threshold for oneshot mods |
| `COMBO_TERM` | 50 | combo detection window (ms) |

## Layers

Order: `QWERTY(0)  EXT(1)  SYM(2)  NAV(3)  FUNC(4)  NUM(5)`.
`FUNC` is a **tri-layer**: holding `SYM`+`EXT` together activates it.

### QWERTY (base)
```
 Q    W    E    R    T   │   Y    U    I    O    P
 A    S    D    F    G   │   H    J    K    L    ;
 Z    X    C    V    B   │   N    M    ,    .    /
           LSFT  SYM     │   EXT  SPC
```

### EXT (numbers, mods, media)  — `MO(EXT)` / right thumb
```
 1    2    3    4    5   │   6    7    8    9    0
 ·    ·    ·    ·    ·   │  BSPC OS_SFT OS_CMD OS_ALT OS_CTL
BRDN BRUP PIPE QK_REP ·  │  VOLD VOLU MPLY MNXT CW_TOGG
           DEL  SYM      │   ·    ·
```

### SYM (symbols, mods)  — `MO(SYM)` / left thumb
```
 !    @    {    }    %   │   ^    [    ]    $    "
OS_CTL OS_ALT OS_CMD OS_SFT # │  *   (    )    _    :
 `    ~    \    &    +   │   -    =    <    >    '
           BSPC  ·       │   EXT  LGUI+SPC
```

### NAV (navigation, editing)  — `TT(NAV)` via A+S combo
```
 ·    ·    ·    ·    ·   │  HOME DSK← DSK→ END   ·
TG(NAV) ·  SW_TAB SW_WIN · │ LEFT DOWN UP  RIGHT BSPC
 ·   CUT  COPY PSTE  ·   │  HOME PGDN PGUP END   ·
           BSPC DEL      │  TG(NAV) ·
```

### FUNC (F-keys, window/desktop nav)  — SYM+EXT tri-layer
```
 ·    ·    ·    ·    ·   │  HOME DSK← DSK→ END  F12
 ·    ·  SW_TAB SW_WIN · │ LEFT DOWN UP  RIGHT F11
 F1   F2   F3   F4   F5  │  F6   F7   F8   F9   F10
           ·    ·        │   ·    ·
```

### NUM (numpad)  — `TG(NUM)` via Z+X combo
```
 /    7    8    9    *   │   ·    ·    ·    ·    ·
BSPC  4    5    6    -   │ TG(NUM) ·   ·    ·    ·
DEL   1    2    3    +   │   ·    ·    ·    ·    ·
           .    0        │  TG(NUM) ·
```

## Combos

| Keys | Output | Notes |
|------|--------|-------|
| `S`+`D` | `Esc` | |
| `D`+`F` | `Tab` | |
| `K`+`L` | `Enter` | |
| `J`+`K` | `Bspc` | |
| `)`+`_` | `Del` | on SYM layer |
| `~`+`\` | `\|` (pipe) | on SYM layer |
| `A`+`S` | `TT(NAV)` | enter NAV layer |
| `Z`+`X` | `TG(NUM)` | toggle NUM layer (matches totem) |
| `VolDn`+`VolUp` | `Mute` | on EXT layer |
| `Play`+`Next` | `Prev` | on EXT layer |

## Custom behaviors

- **Oneshot mods** (`OS_SFT`, `OS_CTL`, `OS_ALT`, `OS_CMD`) — timer-based
  Callum-style sticky mods (`oneshot.c`). Tap = queue for next key; hold past
  `ONESHOT_TAPPING_TERM` = act as a normal held mod; tap `ONESHOT_TAP_TOGGLE`
  times = lock on.
- **Swapper** (`swapper.c`) — `SW_WIN` = hold-Cmd + Tab (app switcher),
  `SW_TAB` = hold-Ctrl + Tab (tab switcher). Stay open until the layer/mod releases.
- **Oneshot cancel logic** — pressing `SYM` or `EXT` **alone** cancels a queued/held
  oneshot mod. Pressing them **together** to reach FUNC does **not** cancel, so a
  queued mod carries through to the next FUNC-layer key (e.g. `Cmd`+`←`). Implemented
  in `is_oneshot_cancel_key` via `layer_state_is()`.

---

## Extra keys on the Totem (ZMK) layout

The [Totem](../zmk-config/config/totem.keymap) is the 38-key ZMK cousin this config
tracks. It has **4 more keys** than the sweep; each is folded into a sweep combo:

| Totem extra key | Function | Sweep equivalent |
|-----------------|----------|------------------|
| outer bottom-left | `&lt NAV ESC` — hold NAV / tap Esc | `A`+`S` combo (NAV) + `S`+`D` combo (Esc) |
| outer bottom-right | `&kp RET` — Enter | `K`+`L` combo |
| 3rd left thumb | Bspc | `J`+`K` combo |
| 3rd right thumb | `&mo NUM` — momentary NUM | `Z`+`X` combo → `TG(NUM)` |

Other Totem-only differences:

- **Right-inner thumb** is `&lt EXT K_CANCEL` (hold EXT / tap Cancel); the sweep
  uses plain `MO(EXT)` with no tap action.
- **ADJ layer** (reached from NAV's outer key `&mo ADJ`) holds Bluetooth select/clear,
  output toggle, `&sys_reset`, and a mirror of the F-keys. Not present on the sweep —
  it is a wired board, so BT/output controls are irrelevant.
- Totem scopes combos to specific layers; sweep combos are global.
- Tap timing: Totem `mt`/`lt` = 170 ms, sticky-key release 1200 ms.

## Extra keys on the Allium58 (Lily58) layout

The **Allium58** (`keyboards/lily58/keymaps/Allium58`, on the `allium58` branch) is a
58-key board. Beyond the shared 3×10 alphas + 4 central thumbs it adds a **number row**,
**outer pinky columns**, and **extra thumbs**. Their base-layer functions:

| Extra region | Keys (base layer) |
|--------------|-------------------|
| Top number row | `` ` `` `1 2 3 4 5` │ `6 7 8 9 0` `\` |
| Left outer column | `Tab` (top), `LT(NAV,Esc)` (home), `LCtrl` (bottom) |
| Right outer column | `'` (top), `Enter` (home), `RShift` (bottom) |
| Extra left thumbs | `LAlt`, `TT(NAV)` |
| Extra right thumb | `TT(NUM)` |

On the upper layers these extra cells carry secondary functions, e.g.:

- **NAV**: the number row becomes `F1`–`F11` (with `F12` on the right outer column).
- **SYM**: outer keys give `Esc` (top-left) and `Undo` (home-left, `LGUI+Z`).
- **EXT**: top-left outer key is `` ~ ``; the number row passes through digits.

The Allium keeps the sweep's combos too, so `Esc`/`Enter`/`Bspc`/`Tab` are reachable
either from the dedicated outer keys **or** the combos.
