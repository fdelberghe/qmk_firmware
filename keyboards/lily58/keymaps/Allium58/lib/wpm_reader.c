#include <stdio.h>
#include "wpm.h"

char wpm_str[24];

const char *read_wpm(void) {
  uint8_t current_wpm = get_current_wpm();
  snprintf(wpm_str, sizeof(wpm_str), "WPM: %03d", current_wpm);
  return wpm_str;
}
