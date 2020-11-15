#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

#define USART_BAUDRATE 9600
#define BAUD_PRESCALE (((F_CPU / (USART_BAUDRATE * 16UL))) - 1)


int main() {
    UBRR0L = USART_BAUDRATE & 0xff;
    UBRR0H = USART_BAUDRATE >> 8;
    UCSR0B = (1 << RXEN0) | (1 << TXEN0);
    sei();

    while (1) {
        if (UCSR0A & (1 << RXC0)) {
            uint8_t data = UDR0;
            while (!(UCSR0A & (1 << UDRE0)));
            UDR0 = data;
        }
    }
}
