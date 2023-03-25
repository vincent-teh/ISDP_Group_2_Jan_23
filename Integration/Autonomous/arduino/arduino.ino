#include "encoder.h"
#include "motor.h"

#define BAUD_RATE 9600

/** This section shows the code for running basic motor
 *  receiving inputs from USB serial
 */
#define EN_A        5
#define LEFT_FORW   8
#define LEFT_BACKW  9
#define RIGHT_FORW  10
#define RIGHT_BACKW 11
#define EN_B        6

Motor my_car(EN_A, LEFT_FORW, LEFT_BACKW,
            RIGHT_FORW, RIGHT_BACKW, EN_B);

void setup() {
  Serial.begin(BAUD_RATE);
  my_car.begin();
  my_car.setDirection(0);
  my_car.setSpeed(0, 0);
}

void loop() {
  while (Serial.available()) {
    String s = Serial.readString();
    int i = s.toInt();
    Serial.println(i);
    my_car.setDirection(i);
    if (i == STOP)
      my_car.setSpeed(0, 0);
    else
      my_car.setSpeed(100, 100);
  }
}
