#include <avr/io.h>

int main() {
  DDRD = 0x20;
  PORTD |= 0x20;

  while (true);
}