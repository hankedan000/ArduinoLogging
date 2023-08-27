#define LOG_THRESHOLD WARN_LEVEL
#include <logging.h>

void loggerA() {
  DEBUG("%s", __func__);
  INFO("%s", __func__);
  WARN("%s", __func__);
  ERROR("%s", __func__);
}