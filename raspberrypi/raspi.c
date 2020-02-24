#include "pins.h"
#include <blinds/util/configure.h>
#include <wiringPi.h>
#include <stdio.h>

#define BLINDS_PWM_CLOCK ((int) ((double) BLINDS_PI_CLOCK_FREQ / (BLINDS_PWM_RANGE * BLINDS_PWM_FREQ)))

void blinds_io_init() {
  wiringPiSetupPhys();
  printf("pwm range=%ld clock=%d freq=%f Hz value=%d\n",
         (long) BLINDS_PWM_RANGE, BLINDS_PWM_CLOCK, BLINDS_PWM_FREQ, BLINDS_PWM_VALUE);
  pinMode(PIN_PWM0, PWM_OUTPUT);  // pin mode needs to be set before PWM is configured
  pinMode(PIN_PWM1, PWM_OUTPUT);
  pwmSetMode(PWM_MODE_MS);
  pwmSetClock(BLINDS_PWM_CLOCK);
  pwmSetRange(BLINDS_PWM_RANGE);
  pinMode(PIN_RPM0, INPUT);
  pinMode(PIN_RPM1, INPUT);
  pinMode(PIN_BUTTON_FORWARD, INPUT);
  pinMode(PIN_BUTTON_BACKWARD, INPUT);
}

void blinds_motor_io_stop();

void blinds_io_cleanup() {
  blinds_motor_io_stop();
}
