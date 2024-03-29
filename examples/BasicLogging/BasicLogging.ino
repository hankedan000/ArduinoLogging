#define LOG_THRESHOLD DEBUG_LEVEL
#include <logging_impl.h>

void setup() {
  setupLogging(115200);
  
  DEBUG("this is a DEBUG log");
  INFO("this is an INFO log");
  WARN("this is a WARN log");
  ERROR("this is an ERROR log");
}

unsigned int count = 0;
void loop() {
  INFO("count = %d", count++);
  delay(1000);
}
