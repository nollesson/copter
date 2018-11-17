#include <avr/io.h>
#include <stdint.h>

int main() {
  DDRB |= 0x20;

  PORTB |= 0x20;
  PORTB &= ~0x20;

  while(true);
}
