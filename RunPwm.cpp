#include "Libraries/ArduinoCore/Arduino.h"

#include <util/delay.h>

int main() {
  init();
  Serial.begin(9600);

  pinMode(3, OUTPUT);
  TCCR2A = _BV(COM2B1) | _BV(WGM21) | _BV(WGM20); // Fast PWM, OCR2B (PIN 3) used
  TCCR2B = _BV(CS21); // Prescaler 8, with 8bit registers -> f=8kHz
  OCR2B = 0;

  while (1) {
    if (Serial.available() > 0) {
       uint8_t byte = Serial.read();
       if (byte >= '0' && byte <= '9')
       {
         int new_value = byte == '9' ? 255 : (byte - '0') * 25;
         OCR2B = new_value;
         Serial.print("Set to :");
         Serial.println(new_value);
       }
     }
  }
}
