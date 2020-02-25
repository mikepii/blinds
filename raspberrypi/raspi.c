/**
 * @file raspberrypi/raspi.c
 * @brief General RaspberryPi IO implementation.
 */

#include "pins.h"
#include <blinds/util/configure.h>
#include <blinds/util/logging.h>
#include <wiringPi.h>

/**
 * @brief Sets up Raspberry Pi pins and wiringPi library.
 *
 * For PWM, we use "mark space" mode (conventional on/off cycles) so that we can directly
 * configure a particular frequency that the motor controller circuit supports.
 * The default, "balanced" mode, achieves the same duty cycle, but
 * smooths it out by switching on/off more rapidly.
 */
void blinds_io_init() {
  wiringPiSetupPhys();
  const int pwmClock = (int) ((double) BLINDS_PI_CLOCK_FREQ / (BLINDS_PWM_RANGE * BLINDS_PWM_FREQ));
  logmsg(debug, "raspberrypi", "pwm range=%ld clock=%d freq=%f Hz value=%d",
         (long) BLINDS_PWM_RANGE, pwmClock, BLINDS_PWM_FREQ, BLINDS_PWM_VALUE);
  pinMode(PIN_PWM0, PWM_OUTPUT);  // pin mode needs to be set before PWM is configured
  pinMode(PIN_PWM1, PWM_OUTPUT);
  pwmSetMode(PWM_MODE_MS);  // "mark space" mode
  pwmSetClock(pwmClock);
  pwmSetRange(BLINDS_PWM_RANGE);
  pinMode(PIN_RPM0, INPUT);
  pinMode(PIN_RPM1, INPUT);
  pinMode(PIN_BUTTON_FORWARD, INPUT);
  pinMode(PIN_BUTTON_BACKWARD, INPUT);
}

void blinds_motor_io_stop();

/**
 * @brief Stops the motor by clearing Raspberry Pi PWM output.
 */
void blinds_io_cleanup() {
  blinds_motor_io_stop();
}
