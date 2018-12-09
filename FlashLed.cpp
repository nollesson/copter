#include <avr/io.h>
#include <util/delay.h>

int main()
{
  DDRB |= (1 << DDB5);    // Make pin 13 be an output.
  while(1)
  {
    PORTB |= (1 << PORTB5);   // Turn the LED on.
    _delay_ms(100);
    PORTB &= ~(1 << PORTB5);  // Turn the LED off.
    _delay_ms(100);
  }
}
