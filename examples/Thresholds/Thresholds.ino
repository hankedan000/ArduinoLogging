#define LOG_THRESHOLD DEBUG_LEVEL
#include <logging_impl.h>

void loggerA();
void loggerB();

void setup() {
  setupLogging(115200);
  
  // we should get all of these logs
  DEBUG("this is a DEBUG log");
  INFO("this is an INFO log");
  WARN("this is a WARN log");
  ERROR("this is an ERROR log");
}

unsigned int count = 0;
void loop() {
  INFO("count = %d", count++);
  loggerA();// will only log WARN and above
  loggerB();// will only log ERROR and above
  delay(1000);
}
