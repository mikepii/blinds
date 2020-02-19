#include <wiringPi.h>
#include <iostream>
#include <csignal>

// physical 32
#define PIN_PWM0 26
// physical 33
#define PIN_PWM1 23
// physical 11
#define PIN_RPM0 0
// physical 13
#define PIN_RPM1 2

void forward() {
  pwmWrite(PIN_PWM0, 1024);
  pwmWrite(PIN_PWM1, 0);
}

void backward() {
  pwmWrite(PIN_PWM0, 0);
  pwmWrite(PIN_PWM1, 1024);
}

void stop() {
  pwmWrite(PIN_PWM0, 0);
  pwmWrite(PIN_PWM1, 0);
}

void handle_term(int sig) {
  stop();
  exit(sig);
}

int main() {
  wiringPiSetup();
  signal(SIGHUP, handle_term);
  signal(SIGINT, handle_term);
  signal(SIGQUIT, handle_term);

  pinMode(PIN_PWM0, PWM_OUTPUT);
  pinMode(PIN_PWM1, PWM_OUTPUT);
  pinMode(PIN_RPM0, INPUT);
  pinMode(PIN_RPM1, INPUT);

  std::cout << "Hello, World again!!!" << std::endl;

  while (true) {
    forward();
    delay(5000);
    backward();
    delay(5000);
  }

  return 0;
}
