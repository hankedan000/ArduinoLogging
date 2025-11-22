#ifndef LOGGING_IMPL_H_
#define LOGGING_IMPL_H_

#include "logging.h"

#define SERIAL_8N1 0x06

#define _BV(bit) (1 << (bit))
#define _SFR_BYTE(sfr) _MMIO_BYTE(_SFR_ADDR(sfr))
#define cbi(sfr, bit) (_SFR_BYTE(sfr) &= ~_BV(bit))
#define sbi(sfr, bit) (_SFR_BYTE(sfr) |= _BV(bit))

// disable builtin Arduino Serial class
#define Serial SomeOtherwiseUnusedName
static class {
public:
  void begin(...) {}
  void print(...) {}
  void println(...) {}
} Serial;

inline int
logging_putchar(
    char c,
    FILE *stream)
{
  // wait for data register to be empty
  while ((UCSR0A & (1 << UDRE0)) == 0) {}
  // send the byte
  UDR0 = c;

  return 0;
}

static FILE logging_stdout;

// ripped this off from Arduino HardwareSerial.cpp
inline void arduinoSerialBegin(
  unsigned long baud, uint8_t config)
{
  // Try u2x mode first
  uint16_t baud_setting = (F_CPU / 4 / baud - 1) / 2;
  UCSR0A = 1 << U2X0;

  // hardcoded exception for 57600 for compatibility with the bootloader
  // shipped with the Duemilanove and previous boards and the firmware
  // on the 8U2 on the Uno and Mega 2560. Also, The baud_setting cannot
  // be > 4095, so switch back to non-u2x mode if the baud rate is too
  // low.
  if (((F_CPU == 16000000UL) && (baud == 57600)) || (baud_setting >4095))
  {
    UCSR0A = 0;
    baud_setting = (F_CPU / 8 / baud - 1) / 2;
  }

  // assign the baud_setting, a.k.a. ubrr (USART Baud Rate Register)
  UBRR0H = baud_setting >> 8;
  UBRR0L = baud_setting;

  // _written = false;

  //set the data bits, parity, and stop bits
  #if defined(__AVR_ATmega8__)
  config |= 0x80; // select UCSRC register (shared with UBRRH)
  #endif
  UCSR0C = config;

  // sbi(UCSR0B, RXEN0);
  sbi(UCSR0B, TXEN0);
  // sbi(UCSR0B, RXCIE0);
  // cbi(UCSR0B, UDRIE0);
}

inline void
setupLogging(
  unsigned long baud = 115200)
{
  fdev_setup_stream(
      &logging_stdout,
      logging_putchar,
      NULL,
      _FDEV_SETUP_WRITE);

  stdout = &logging_stdout;

  arduinoSerialBegin(baud, SERIAL_8N1);
}

#endif
