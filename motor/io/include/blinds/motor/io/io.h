#ifndef BLINDS_MOTOR_IO_INCLUDE_BLINDS_MOTOR_IO_IO_H_
#define BLINDS_MOTOR_IO_INCLUDE_BLINDS_MOTOR_IO_IO_H_

#include <stdbool.h>

void blinds_motor_io_init();

void blinds_motor_io_forward();

void blinds_motor_io_backward();

void blinds_motor_io_stop();

int blinds_motor_io_read_rpm0();

#endif //BLINDS_MOTOR_IO_INCLUDE_BLINDS_MOTOR_IO_IO_H_
