#include "pins.h"
#include <wiringPi.h>
#include <stdbool.h>

bool blinds_buttons_read_forward() {
  return digitalRead(PIN_BUTTON_FORWARD);
}

bool blinds_buttons_read_backward() {
  return digitalRead(PIN_BUTTON_BACKWARD);
}
