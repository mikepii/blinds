/**
 * @file raspberrypi/raspi_motor.c
 * @brief RaspberryPi motor IO implementation.
 */

#include "pins.h"
#include <blinds/util/configure.h>
#include <wiringPi.h>

void blinds_motor_io_forward() {
  pwmWrite(PIN_PWM0, BLINDS_PWM_VALUE);
  pwmWrite(PIN_PWM1, 0);
}

void blinds_motor_io_backward() {
  pwmWrite(PIN_PWM0, 0);
  pwmWrite(PIN_PWM1, BLINDS_PWM_VALUE);
}

void blinds_motor_io_stop() {
  pwmWrite(PIN_PWM0, 0);
  pwmWrite(PIN_PWM1, 0);
}

/**
 * @brief Reads the digital state of the encoder sensor on the motor.
 * @see \def BLINDS_MOTOR_EV_PER_ROTATION
 * @return 1 (high) or 0 (low)
 */
int blinds_motor_io_read_rpm0() {
  return digitalRead(PIN_RPM0);
}
