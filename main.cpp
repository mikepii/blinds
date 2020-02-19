#include <wiringPi.h>
#include <chrono>
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
// events per rotation
#define RPM_EPR 11

void forward() {
  pwmWrite(PIN_PWM0, 900);
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

void delay_and_read_rpm(int dur_ms) {
  int last_val = 0;
  int edges = 0, reads = 0, min = 1024, max = 0;
  auto start = std::chrono::system_clock::now();
  auto end = start + std::chrono::milliseconds(dur_ms);
  std::chrono::system_clock::time_point now;
  do {
    auto val = digitalRead(PIN_RPM0);
    reads += 1;
    if (last_val == 0 && val == 1) {
      edges += 1;
    }
    if (val < min) min = val;
    if (val > max) max = val;
    last_val = val;
    delay(1);
    now = std::chrono::system_clock::now();
  } while (now < end);
  std::cout << "edges=" << edges << ", reads=" << reads << ", min=" << min << ", max=" << max << std::endl;
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

  std::cout << "Hello, World again!!! with chrono" << std::endl;

  while (true) {
    forward();
    delay_and_read_rpm(5000);
    backward();
    delay_and_read_rpm(5000);
  }

  return 0;
}
