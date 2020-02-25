/**
 * @file raspberrypi/raspi_logging.c
 * @brief RaspberryPi logging implementation.
 *
 * We'll want to handle this differently on Arduino/AVR (e.g. no-op).
 */

#include <blinds/util/logging.h>
#include <stdarg.h>
#include <stdio.h>
#include <time.h>

static const char *const levels[] = {
    [debug] = "debug",
    [info] = "info",
};

/**
 * Writes to stderr. Uses local timezone.
 *
 * @param level
 * @param module
 * @param message_format printf format
 * @param ... printf() args
 */
void logmsg(const enum log_level_t level, const char module[], const char message_format[], ...) {
  // Time, level, and module
  time_t now;
  time(&now);
  // %.24s is a dirty way of omitting the newline character from cstring()
  fprintf(stderr, "%.24s %s (%s) ", ctime(&now), levels[level % sizeof(levels)], module);
  // Message
  va_list args;
  va_start(args, message_format);
  vfprintf(stderr, message_format, args);
  fputs("\n", stderr);  // newline
  va_end(args);
  fflush(stderr);
}
