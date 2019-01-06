#include "Libraries/ArduinoCore/Arduino.h"
#include "Hal/Twi.h"

#include <util/delay.h>

namespace {
uint8_t IMU_ADDRESS = 0x68;
uint8_t REG_ACCEL_DATA = 0x3B;
uint8_t REG_GYRO_DATA = 0x43;
}

int main() {
  (void)REG_ACCEL_DATA;
  sei();
  Serial.begin(9600);
  twi::init();

  while (1) {
    twi::writeData(IMU_ADDRESS, &REG_GYRO_DATA, 1, false);
    uint8_t gyroData[6];
    twi::readData(IMU_ADDRESS, gyroData, 6, true);

    int16_t x = static_cast<int16_t>(gyroData[0]);
    int16_t y = static_cast<int16_t>(gyroData[2]);
    int16_t z = static_cast<int16_t>(gyroData[4]);

    Serial.print(x);
    Serial.print(", ");
    Serial.print(y);
    Serial.print(", ");
    Serial.println(z);

    _delay_ms(50000);
  }
}
