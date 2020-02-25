/**
 * @file io/include/blinds/io/io.h
 * @brief General IO interface.
 */

#ifndef BLINDS_IO_INCLUDE_BLINDS_IO_IO_H_
#define BLINDS_IO_INCLUDE_BLINDS_IO_IO_H_

/**
 * @brief Initialize IO (e.g. configure GPIO pins).
 * @see @file raspberrypi/raspi.c
 */
void blinds_io_init();

/**
 * @brief Cleanup IO (e.g. stop motor).
 * @see @file raspberrypi/raspi.c
 */
void blinds_io_cleanup();

#endif //BLINDS_IO_INCLUDE_BLINDS_IO_IO_H_
