#include "Libraries/ArduinoCore/Arduino.h"
#include "Hal/Twi.h"

#include <util/delay.h>

int main() {
  init();
  Serial.begin(9600);
  twi::init();

  Serial.println("Starting scan");
  for (int address = 0; address < 128; ++address)
  {
    bool status = twi::testAddress(address);
    if (status)
    {
      Serial.print("Found address: ");
      Serial.println(address);
    }
  }
  Serial.println("Done");
  while (1) {
  }
}
