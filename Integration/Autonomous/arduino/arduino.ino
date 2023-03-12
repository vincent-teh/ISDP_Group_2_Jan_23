// #define DEBUG

#include <SoftwareSerial.h>
#include "motor.h"

#define BAUD_RATE 115200

#define EN_A        5
#define LEFT_FORW   8
#define LEFT_BACKW  9
#define RIGHT_FORW  10
#define RIGHT_BACKW 11
#define EN_B        6

SoftwareSerial espSerial(10, 11); // RX, TX
Motor my_car(EN_A, LEFT_FORW, LEFT_BACKW,
             RIGHT_FORW, RIGHT_BACKW, EN_B);

void setup() {
  Serial.begin(BAUD_RATE);
  espSerial.begin(BAUD_RATE); // ESP01 baud rate
  my_car.begin();
}

void loop() {
  while (Serial.available()) {
    String s = Serial.readString();
    int i = s.toInt();
    Serial.println(i);
    my_car.setDirection(i);
  }
}


