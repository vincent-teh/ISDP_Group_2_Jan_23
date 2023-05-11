#include "encoder.h"
#include "motor.h"

#define BAUD_RATE 9600

/** This section shows the code for running basic motor
 *  receiving inputs from USB serial
 */
#define EN_A          5
#define LEFT_FORW     6
#define LEFT_BACKW    7
#define RIGHT_FORW    9
#define RIGHT_BACKW   8
#define EN_B          10

#define ECDR_LEFT   3
#define ECDR_RIGHT  2

#define TURN_SPEED 150

/**
 * steps per revolve 37
 * Wheel diameter    6
 * Distance travel for 1 revolve 18.86
 */
#define STEPS_IN_90_DEGREES 21

#ifdef MAIN
Motor my_car(EN_A, LEFT_FORW, LEFT_BACKW,
            RIGHT_FORW, RIGHT_BACKW, EN_B);

Encoder encoders[2] = {Encoder(ECDR_LEFT), Encoder(ECDR_RIGHT)};

unsigned long start_time;

void ISR_handler_left()
{
  encoders[0].updateCount();
}

void ISR_handler_right()
{
  encoders[1].updateCount();
}

void setup() {
  Serial.begin(BAUD_RATE);
  my_car.begin();
  my_car.setDirection(0);
  my_car.setSpeed(0, 0);
  encoders[0].begin(ISR_handler_left);
  encoders[1].begin(ISR_handler_left);
}

void loop() {
  if (Serial.available()) {
    int angle = Serial.parseInt();
    int steps = map(abs(angle), 0, 90, 0, STEPS_IN_90_DEGREES);
    if (angle < 0)
      my_car.setDirection(TURN_LEFT);
    else
      my_car.setDirection(TURN_RIGHT);
    uint8_t speeds[] = {TURN_SPEED, TURN_SPEED};
    my_car.setSpeed(speeds[0], speeds[1]);
    while (true) {
      if (encoders[0].getVal() == steps) {
        speeds[0] = 0;
        my_car.setSpeed(speeds[0], speeds[1]);
      }
      if (encoders[1].getVal() == steps) {
        speeds[1] = 0;
        my_car.setSpeed(speeds[0], speeds[1]);
      }
    }
    encoders[0].resetCount();
    encoders[1].resetCount();
  }
}
#endif

#define SPEED 200
Motor my_car(EN_A, LEFT_FORW, LEFT_BACKW, RIGHT_FORW, RIGHT_BACKW, EN_B);

void setup()
{
  my_car.begin();
  Serial.begin(9600);
}

void loop()
{
  if (Serial.available()) {
    int data = Serial.readString().toInt();
    Serial.println(data);
    for (int i = 0; i < 15; i++) {
      if (data == TURN_LEFT) {
        my_car.setSpeed(SPEED, SPEED);
        my_car.setDirection(TURN_LEFT);
      }
      else {
        my_car.setSpeed(SPEED, SPEED);
        my_car.setDirection(TURN_RIGHT);
      }
      delay(100);
      my_car.setSpeed(0, 0);
      delay(500);
    }
  }
  my_car.setSpeed(0, 0);
}

