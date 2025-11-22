#ifndef LOGGING_IMPL_H_
#define LOGGING_IMPL_H_

#include <Arduino.h>
#include "logging.h"

inline int
logging_putchar(
		char c,
		FILE *stream)
{
	Serial.print(c);

	return 0;
}

static FILE logging_stdout;

inline void
setupLogging(
  unsigned long baud = 115200)
{
	Serial.begin(baud);
	
	fdev_setup_stream(
			&logging_stdout,
			logging_putchar,
			NULL,
			_FDEV_SETUP_WRITE);

	stdout = &logging_stdout;
}

#endif
