#include <blinds/hdw/hdw.h>
#include <stdio.h>

int main() {
  blinds_hdw_init();
  printf("Hello, World\n");
  while (1) {
    blinds_hdw_forward();
    printf("fw rpm=%f\n", blinds_hdw_delay_and_read_rpm(5000));
    blinds_hdw_backward();
    printf("bw rpm=%f\n", blinds_hdw_delay_and_read_rpm(5000));
  }
  return 0;
}
