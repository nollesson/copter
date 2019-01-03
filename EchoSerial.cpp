#include "Libraries/ArduinoCore/Arduino.h"

#include <util/delay.h>

int main() {
  init();
  Serial.begin(9600);

  while (1) {
    if (Serial.available() > 0) {
      Serial.write(Serial.read());
    }
    // if (serialEventRun) serialEventRun();
  }
}
