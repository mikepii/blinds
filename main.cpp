extern "C" {
#include <blinds/hdw/hdw.h>
}
#include <iostream>

int main() {
  blinds_hdw_init();
  std::cout << "Hello, World (cmake modules)" << std::endl;
  while (true) {
    blinds_hdw_forward();
    blinds_hdw_delay_and_read_rpm(5000);
    blinds_hdw_backward();
    blinds_hdw_delay_and_read_rpm(5000);
  }
  return 0;
}
