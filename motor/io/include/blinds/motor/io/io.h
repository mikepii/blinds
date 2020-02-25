/**
 * @file motor/io/include/blinds/motor/io/io.h
 * @brief Motor IO interface.
 * @see @file raspberrypi/raspi_motor.c
 *
 * Controlled by the Motor Position layer.
 */

#ifndef BLINDS_MOTOR_IO_INCLUDE_BLINDS_MOTOR_IO_IO_H_
#define BLINDS_MOTOR_IO_INCLUDE_BLINDS_MOTOR_IO_IO_H_

#include <stdbool.h>

void blinds_motor_io_forward();
void blinds_motor_io_backward();
void blinds_motor_io_stop();

/**
 * @brief Reads the digital state of the encoder sensor on the motor.
 * @see \def BLINDS_MOTOR_EV_PER_ROTATION
 * @return 1 (high) or 0 (low)
 */
int blinds_motor_io_read_rpm0();

#endif //BLINDS_MOTOR_IO_INCLUDE_BLINDS_MOTOR_IO_IO_H_
