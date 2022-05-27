#include "Libraries/ArduinoCore/Arduino.h"
#include "Libraries/ArduinoCore/Stepper.h"


#include <util/delay.h>

int const stepsPerRevolution = 1234;
int main() {
  init();
  Serial.begin(9600);
  Stepper stepper(stepsPerRevolution, 8, 9, 10, 11);

  stepper.setSpeed(1);
  while (1) {
    stepper.step(10);
  }
}
