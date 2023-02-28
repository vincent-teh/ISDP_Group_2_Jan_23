#include <SoftwareSerial.h>

#define BAUD_RATE 115200

SoftwareSerial espSerial(10, 11); // RX, TX

void setup() {
  Serial.begin(BAUD_RATE);
  espSerial.begin(BAUD_RATE); // ESP01 baud rate
}

void loop() {
  if (espSerial.available()) {
    char c = espSerial.read();
    Serial.print(c);
  }
}

