#ifndef BLINDS_HARDWARE_COMMON_INCLUDE_BLINDS_HDW_HDW_H_
#define BLINDS_HARDWARE_COMMON_INCLUDE_BLINDS_HDW_HDW_H_

void blinds_hdw_init();

void blinds_hdw_forward();

void blinds_hdw_backward();

void blinds_hdw_stop();

float blinds_hdw_delay_and_read_rpm(int dur_ms);

#endif //BLINDS_HARDWARE_COMMON_INCLUDE_BLINDS_HDW_HDW_H_
