#include "raspi.h"
#include <blinds/motor/io/io.h>
#include <wiringPi.h>
#include <signal.h>
#include <stdlib.h>

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

float blinds_hdw_delay_and_read_rpm(int dur_ms) {
  int val, last_val = 0, edges = 0, reads = 0;
  const unsigned start = millis();
  const unsigned end = start + dur_ms;
  unsigned n = 0;
  unsigned now = start;
  do {
    val = digitalRead(PIN_RPM0);
    reads += 1;
    if (last_val == 0 && val == 1) {
      edges += 1;
    }
    last_val = val;
    if (++n % 100 == 0) {
      now = millis();
    }
  } while (now < end);
  const double rpm = (double) edges * 60000 / dur_ms / RPM_EPR;
  return (float) rpm;
}
