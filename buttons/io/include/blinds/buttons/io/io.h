/**
 * @file buttons/io/include/blinds/buttons/io/io.h
 * @brief Buttons IO interface.
 * @see raspberrypi/raspi_buttons.c
 */

#ifndef BLINDS_BUTTONS_IO_INCLUDE_BLINDS_BUTTONS_IO_IO_H_
#define BLINDS_BUTTONS_IO_INCLUDE_BLINDS_BUTTONS_IO_IO_H_

#include <stdbool.h>

bool blinds_buttons_read_backward();
bool blinds_buttons_read_forward();

#endif //BLINDS_BUTTONS_IO_INCLUDE_BLINDS_BUTTONS_IO_IO_H_
