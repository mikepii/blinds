#include <wiringPi.h>
#include <signal.h>
#include <stdlib.h>

// physical 32
#define PIN_PWM0 26
// physical 33
#define PIN_PWM1 23
// physical 11
#define PIN_RPM0 0
// physical 13
#define PIN_RPM1 2
// events per rotation
#define RPM_EPR (11 * 522)

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

static void handle_term(int sig) {
  blinds_motor_io_stop();
  exit(sig);
}

int blinds_motor_io_read_rpm0() {
  return digitalRead(PIN_RPM0);
}

void blinds_motor_io_init() {
  wiringPiSetup();
  signal(SIGHUP, handle_term);
  signal(SIGINT, handle_term);
  signal(SIGQUIT, handle_term);
  pinMode(PIN_PWM0, PWM_OUTPUT);
  pinMode(PIN_PWM1, PWM_OUTPUT);
  pinMode(PIN_RPM0, INPUT);
  pinMode(PIN_RPM1, INPUT);
}
