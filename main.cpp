#include <wiringPi.h>
#include <iostream>

int main() {
  wiringPiSetup();
  std::cout << "Hello, World again!" << std::endl;
  return 0;
}
