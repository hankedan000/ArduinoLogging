#ifndef LOGGING_CMN_H_
#define LOGGING_CMN_H_

#include <avr/pgmspace.h>
#include <stdio.h>

#define DEBUG_LEVEL 10
#define INFO_LEVEL  20
#define WARN_LEVEL  30
#define ERROR_LEVEL 40
#define NO_LOGS     60

// define global log threshold if not default yet.
// recommend user sets this via compiler flags.
#ifndef GLOBAL_LOG_THRESHOLD
#define GLOBAL_LOG_THRESHOLD DEBUG_LEVEL
#endif

// define logging threshold for current compilation unit
#ifndef LOG_THRESHOLD
#define LOG_THRESHOLD INFO_LEVEL
#endif

#define USE_FLASH_STRINGS

#define PRAGMA(x) _Pragma(#x)

#define IS_THRESHOLDED(level) ((level < GLOBAL_LOG_THRESHOLD) || (level < LOG_THRESHOLD))

#ifdef USE_FLASH_STRINGS
  #define PRINT_LOG(level_str,log_msg,...)\
    printf_P(PSTR(level_str " | " log_msg "\n"),##__VA_ARGS__)
#else
  #define PRINT_LOG(level_str,log_msg,...)\
    printf(level_str " - " log_msg "\n",##__VA_ARGS__)
#endif

// the "##" will remove comma when there are no variable arguments provided
#if (IS_THRESHOLDED(DEBUG_LEVEL))
  #define DEBUG(log_msg,...) {}
#else
  #define DEBUG(log_msg,...) PRINT_LOG("DEBUG",log_msg,##__VA_ARGS__)
#endif

#if (IS_THRESHOLDED(INFO_LEVEL))
  #define INFO(log_msg,...) {}
#else
  #define INFO(log_msg,...) PRINT_LOG("INFO ",log_msg,##__VA_ARGS__)
#endif

#if (IS_THRESHOLDED(WARN_LEVEL))
  #define WARN(log_msg,...) {}
#else
  #define WARN(log_msg,...) PRINT_LOG("WARN ",log_msg,##__VA_ARGS__)
#endif

#if IS_THRESHOLDED(ERROR_LEVEL)
  #define ERROR(log_msg,...) {}
#else
  #define ERROR(log_msg,...) PRINT_LOG("ERROR",log_msg,##__VA_ARGS__)
#endif

#endif