#ifndef LOGGING_CMN_H_
#define LOGGING_CMN_H_

#define DEBUG_LEVEL 10
#define INFO_LEVEL  20
#define WARN_LEVEL  30
#define ERROR_LEVEL 40
#define NO_LOGS     60

#ifndef LOG_THRESHOLD
#define LOG_THRESHOLD INFO_LEVEL
#endif
#define USE_FLASH_STRINGS

#define PRAGMA(x) _Pragma(#x)

#define PUSH_LOG_THRESHOLD() \
  PRAGMA(push_macro("LOG_THRESHOLD"))

#define POP_LOG_THRESHOLD() \
  PRAGMA(pop_macro("LOG_THRESHOLD"))

#ifdef USE_FLASH_STRINGS
  #define PRINT_LOG(level_str,log_msg,...)\
    printf_P(PSTR(level_str " | " log_msg "\n"),##__VA_ARGS__)
#else
  #define PRINT_LOG(level_str,log_msg,...)\
    printf(level_str " - " log_msg "\n",##__VA_ARGS__)
#endif

// the "##" will remove comma when there are no variable arguments provided
#if LOG_THRESHOLD <= DEBUG_LEVEL
  #define DEBUG(log_msg,...) PRINT_LOG("DEBUG",log_msg,##__VA_ARGS__)
#else
  #define DEBUG(log_msg,...) {}
#endif

#if LOG_THRESHOLD <= INFO_LEVEL
  #define INFO(log_msg,...) PRINT_LOG("INFO ",log_msg,##__VA_ARGS__)
#else
  #define INFO(log_msg,...) {}
#endif

#if LOG_THRESHOLD <= WARN_LEVEL
  #define WARN(log_msg,...) PRINT_LOG("WARN ",log_msg,##__VA_ARGS__)
#else
  #define WARN(log_msg,...) {}
#endif

#if LOG_THRESHOLD <= ERROR_LEVEL
  #define ERROR(log_msg,...) PRINT_LOG("ERROR",log_msg,##__VA_ARGS__)
#else
  #define ERROR(log_msg,...) {}
#endif

#endif