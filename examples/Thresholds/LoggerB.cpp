#define LOG_THRESHOLD ERROR_LEVEL
#include <logging.h>

void loggerB() {
  DEBUG("%s", __func__);
  INFO("%s", __func__);
  WARN("%s", __func__);
  ERROR("%s", __func__);
}