#include "Libraries/ArduinoCore/SoftwareSerial.h"
#include "Libraries/ArduinoCore/Arduino.h"

int main() {
    sei();
    SoftwareSerial MyBlue(2, 3); // RX | TX 
    Serial.begin(9600); 
    MyBlue.begin(9600); 
    if (MyBlue.available()) 
      Serial.println("YAAY");
    else
      Serial.println("YAAY"); 
}
