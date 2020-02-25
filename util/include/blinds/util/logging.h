/**
 * @file util/include/blinds/util/logging.h
 */

#ifndef BLINDS_UTIL_INCLUDE_BLINDS_UTIL_LOGGING_H_
#define BLINDS_UTIL_INCLUDE_BLINDS_UTIL_LOGGING_H_

enum log_level_t {
  debug, info
};

/**
 * Implemented by Blinds::RaspberryPi or Blinds::AVR
 *
 * @param level debug or info
 * @param module source
 * @param message_format printf() format string
 * @param ... printf() format args
 */
void logmsg(enum log_level_t level, const char module[], const char message_format[], ...);

#endif //BLINDS_UTIL_INCLUDE_BLINDS_UTIL_LOGGING_H_
