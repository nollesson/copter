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
    volatile bool _isFinished;
    uint8_t _address;
    uint8_t const *_writeData;
    uint8_t *_readData;
    uint8_t _size;
    uint8_t _status;
    bool _shouldStop;

    void start() {
        _isFinished = false;
        TWCR = (TWCR | (1 << TWINT) | (1 << TWSTA) | (1 << TWIE)) & ~((1 << TWSTO));
    }

    void stop() {
        _isFinished = true;
        if (_shouldStop) {
            TWCR = (TWCR | (1 << TWINT) | (1 << TWSTO)) & ~((1 << TWSTA) | (1 << TWIE));
        } else {
            TWCR &= ~(1 << TWIE);
            _delay_ms(1); // Doesn't behave stable without this, don't know why
        }
    }
} // namespace

namespace twi {
/*
 * Sets up TWI. Needs to be called before any other functions.
 */
    void init() {
        // Set frequency to TWI_FREQUENCY
        TWSR &= ~((1 << TWPS0) | (1 << TWPS1));
        TWBR = ((F_CPU / TWI_FREQUENCY) - 16) / 2;
        TWCR = (1 << TWEN) | (1 << TWIE);
    }

/*
 * Tests if there is a response at given address
 * \param address 7-bit address for TWI slave
 * \return true if slave responds to address
 */
    bool testAddress(uint8_t const address) {
        _size = 0;
        _shouldStop = true;
        _address = (address << 1) + TWI_WRITE;

        start();
        while (!_isFinished);
        return _status != TW_MT_SLA_NACK;
    }

    bool writeData(uint8_t const address, uint8_t const *const data, int const size, bool shouldStop) {
        _size = size;
        _writeData = data;
        _shouldStop = shouldStop;
        _address = (address << 1) + TWI_WRITE;

        start();
        while (!_isFinished);
        return _status == TW_MT_DATA_ACK;
    }

    bool readData(uint8_t const address, uint8_t *const data, int const size, bool shouldStop) {
        _isFinished = false;
        _size = size;
        _readData = data;
        _shouldStop = shouldStop;
        _address = (address << 1) + TWI_READ;

        start();
        while (!_isFinished);
        return _status == TW_MR_DATA_ACK;
    }

    ISR(TWI_vect) {
            _status = TW_STATUS;

            switch (_status) {
                case TW_START:
                case TW_REP_START:
                    Serial.print("START");
                    Serial.print("--");
                    Serial.println(TW_STATUS, HEX);
                    TWDR = _address;
                    TWCR |= 1 << TWINT;
                    break;
                case TW_MT_SLA_ACK:
                case TW_MT_DATA_ACK:
                    if (_size > 0) {
                        Serial.print("SEND--");
                        Serial.print(*_writeData, HEX);
                        Serial.print("--");
                        Serial.println(TW_STATUS, HEX);
                        TWDR = *_writeData;
                        TWCR = (TWCR | (1 << TWINT)) & ~((1 << TWSTA) | (1 << TWSTO));
                        ++_writeData;
                        --_size;
                    } else {
                        Serial.print("SEND DONE");
                        Serial.print("--");
                        Serial.println(TW_STATUS, HEX);
                        stop();
                    }
                    break;
                case TW_MT_SLA_NACK:
                case TW_MT_DATA_NACK:
                    Serial.println("STOP FROM SLAVE");
                    stop();
                    break;
                case TW_MR_SLA_ACK:
                    Serial.println("SLACK");
                    TWCR = (TWCR | ((1 << TWINT) | (1 << TWEA))) & ~((1 << TWSTA) | (1 << TWSTO));
                    break;
                case TW_MR_DATA_ACK:
                    *_readData = TWDR;
                    Serial.print("READ--");
                    Serial.print(*_readData, HEX);
                    Serial.print("--");
                    Serial.println(TW_STATUS, HEX);
                    if (_size > 1) {
                        TWCR = (TWCR | ((1 << TWINT) | (1 << TWEA))) & ~((1 << TWSTA) | (1 << TWSTO));
                    } else {
                        TWCR = (TWCR | ((1 << TWINT))) & ~((1 << TWSTA) | (1 << TWSTO) | (1 << TWEA));
                    }
                    --_size;
                    ++_readData;
                    break;
                case TW_MR_SLA_NACK:
                case TW_MR_DATA_NACK:
                    Serial.println("SLNACK");
                    stop();
                    break;
                case TW_MT_ARB_LOST: // Same value as TW_MR_ARB_LOST
                    Serial.print("ARBLOST");
                    _isFinished = true;
                    TWCR |= 1 << TWINT;
                break;
                default:
                    Serial.print("Unhandled case: 0x");
                    Serial.println(_status, HEX);
                    break;
            }
    }
} // namespace twi
