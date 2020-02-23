#include "pins.h"
#include <wiringPi.h>

void blinds_io_init() {
  wiringPiSetup();
  pinMode(PIN_PWM0, PWM_OUTPUT);
  pinMode(PIN_PWM1, PWM_OUTPUT);
  pinMode(PIN_RPM0, INPUT);
  pinMode(PIN_RPM1, INPUT);
  pinMode(PIN_BUTTON_FORWARD, INPUT);
  pinMode(PIN_BUTTON_BACKWARD, INPUT);
}

void blinds_motor_io_stop();

void blinds_io_cleanup() {
  blinds_motor_io_stop();
}
