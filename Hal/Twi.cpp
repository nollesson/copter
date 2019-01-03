#include "Twi.h"

#include "Libraries/ArduinoCore/Arduino.h"

extern "C" {
#include <avr/io.h>
#include <compat/twi.h>
}

#define TWI_FREQUENCY 400000L
#define TWI_READ 1
#define TWI_WRITE 0

namespace {
//void printDebug(char const *s, uint8_t twcr, uint8_t status) {
//  Serial.println(s);
//  Serial.println(twcr, HEX);
//  Serial.println(status, HEX);
//}

volatile bool _isFinished;
uint8_t _address;
uint8_t _status;
} // namespace

namespace twi {
/*
 * Sets up TWI. Needs to be called before any other functions.
 */
void init() {
  // Set frequency to TWI_FREQUENCY
  TWSR &= ~((1 << TWPS0) | (1 << TWPS1));
  TWBR = ((F_CPU / TWI_FREQUENCY) - 16) / 2;
}

/*
 * Tests if there is a response at given address
 * \param address 7-bit address for TWI slave
 * \return true if slave responds to address
 */
bool testAddress(uint8_t const address) {
  _isFinished = false;

  _address = (address << 1) + TWI_WRITE;
  // Enable twi, send start and enable interrupts
  TWCR = (1 << TWINT) | (1 << TWSTA) | (1 << TWEN) | (1 << TWIE);

  while (!_isFinished) {}
  return _status != TW_MT_SLA_NACK;
}

ISR(TWI_vect) {
  _status = TW_STATUS;

  switch (_status) {
  case TW_START:
    TWDR = _address;
    TWCR |= (1 << TWINT);
    break;
  case TW_MT_SLA_ACK:
    _isFinished = true;
    TWCR |= (1 << TWINT) | (1 << TWSTO);
    TWCR &= ~((1 << TWSTA) | (1 << TWIE));
    break;
  case TW_MT_SLA_NACK:
    _isFinished = true;
    TWCR |= (1 << TWINT) | (1 << TWSTO);
    TWCR &= ~((1 << TWSTA) | (1 << TWIE));
    break;
  default:
    Serial.println("Unhandled case");
    break;
  }
}
} // namespace twi
