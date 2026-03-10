LTO_ENABLE = yes            # Link Time Optimization enabled
BOOTMAGIC_ENABLE = no       # Enable Bootmagic Lite
MOUSEKEY_ENABLE = no        # Mouse keys
EXTRAKEY_ENABLE = yes       # Audio control and System control
CONSOLE_ENABLE = no         # Console for debug
COMMAND_ENABLE = no         # Commands for debug and configuration
NKRO_ENABLE = yes           # N-Key Rollover
BACKLIGHT_ENABLE = no       # Enable keyboard backlight functionality
AUDIO_ENABLE = no           # Audio output
RGBLIGHT_ENABLE = no        # Enable WS2812 RGB underlight.
SWAP_HANDS_ENABLE = no      # Enable one-hand typing
OLED_ENABLE = yes           # OLED display
WPM_ENABLE = yes            # Words Per Minute tracking
CAPS_WORD_ENABLE = yes      # Enable Caps Word functionality
COMBO_ENABLE = yes          # Enable Combo functionality

# If you want to change the display of OLED, you need to change here

SRC +=  oneshot.c \
        swapper.c \
        ./lib/layer_state_reader.c \
        ./lib/wpm_reader.c \
        ./lib/modifier_state_reader.c
