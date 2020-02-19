#include "raspi.h"
#include <blinds/hdw/hdw.h>
#include <wiringPi.h>
#include <signal.h>
#include <stdlib.h>

void blinds_hdw_forward() {
  pwmWrite(PIN_PWM0, 900);
  pwmWrite(PIN_PWM1, 0);
}

void blinds_hdw_backward() {
  pwmWrite(PIN_PWM0, 0);
  pwmWrite(PIN_PWM1, 1024);
}

void blinds_hdw_stop() {
  pwmWrite(PIN_PWM0, 0);
  pwmWrite(PIN_PWM1, 0);
}

static void handle_term(int sig) {
  blinds_hdw_stop();
  exit(sig);
}

void blinds_hdw_init() {
  wiringPiSetup();
  signal(SIGHUP, handle_term);
  signal(SIGINT, handle_term);
  signal(SIGQUIT, handle_term);
  pinMode(PIN_PWM0, PWM_OUTPUT);
  pinMode(PIN_PWM1, PWM_OUTPUT);
  pinMode(PIN_RPM0, INPUT);
  pinMode(PIN_RPM1, INPUT);
}
