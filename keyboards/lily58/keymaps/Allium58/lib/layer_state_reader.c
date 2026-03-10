#include "action_layer.h"
#include <stdio.h>

#define L_QWERTY 0
#define L_EXT (1 << 1)
#define L_SYM (1 << 2)
#define L_NAV (1 << 3)
#define L_FUNC (1 << 4)
#define L_NUM (1 << 5)

char layer_state_str[24];

const char *read_layer_state(void) {
  switch (get_highest_layer(layer_state))
  {
  case 0:
    snprintf(layer_state_str, sizeof(layer_state_str), "Layer: QWERTY");
    break;
  case 1:
    snprintf(layer_state_str, sizeof(layer_state_str), "Layer: EXTEND");
    break;
  case 2:
    snprintf(layer_state_str, sizeof(layer_state_str), "Layer: SYMBOLS");
    break;
  case 3:
    snprintf(layer_state_str, sizeof(layer_state_str), "Layer: NAV");
    break;
  case 4:
    snprintf(layer_state_str, sizeof(layer_state_str), "Layer: FUNC");
    break;
  case 5:
    snprintf(layer_state_str, sizeof(layer_state_str), "Layer: NUM");
    break;
  default:
    snprintf(layer_state_str, sizeof(layer_state_str), "Layer: Undef-%u", get_highest_layer(layer_state));
  }

  return layer_state_str;
}
