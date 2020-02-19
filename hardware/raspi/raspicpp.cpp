extern "C" {
#include "raspi.h"
#include <blinds/hdw/hdw.h>
#include <wiringPi.h>
}
#include <chrono>
#include <iostream>

void blinds_hdw_delay_and_read_rpm(int dur_ms) {
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
