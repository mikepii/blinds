#include "pins.h"
#include <wiringPi.h>

void blinds_motor_io_forward() {
  // 800 -> 1.4 rpm
  // 900 -> 4.0 rpm
  // 1024 -> 7.0 rpm
  pwmWrite(PIN_PWM0, 900);
  pwmWrite(PIN_PWM1, 0);
}

void blinds_motor_io_backward() {
  pwmWrite(PIN_PWM0, 0);
  pwmWrite(PIN_PWM1, 900);
}

void blinds_motor_io_stop() {
  pwmWrite(PIN_PWM0, 0);
  pwmWrite(PIN_PWM1, 0);
}

int blinds_motor_io_read_rpm0() {
  return digitalRead(PIN_RPM0);
}
