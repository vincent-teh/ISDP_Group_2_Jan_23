// #define MOTOR_EXAMPLE
#define ENCODER_EXAMPLE


#include "encoder.h"
#include "motor.h"

#define BAUD_RATE 9600

/** This section shows the code for running basic motor
 *  receiving inputs from USB serial
 */
#ifdef MOTOR_EXAMPLE
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
}

void loop() {
  while (Serial.available()) {
    String s = Serial.readString();
    int i = s.toInt();
    Serial.println(i);
    my_car.setDirection(i);
  }
}
#endif

/**
 * This section shows the code for reading encoders value 
 */
#ifdef ENCODER_EXAMPLE
#define LEFT_CLK_PIN  2
#define LEFT_DT_PIN   3
#define RIGHT_CLK_PIN 4
#define RIGHT_DT_PIN  5

Encoder left(LEFT_CLK_PIN, LEFT_DT_PIN);
Encoder right(RIGHT_CLK_PIN, RIGHT_DT_PIN);

void handleLeftInterrupt()
{
  left.handleInterrupt();
}

void handleRightInterrupt()
{
  right.handleInterrupt();
}

void setup()
{
  left.begin(handleLeftInterrupt);
  right.begin(handleRightInterrupt);
  Serial.begin(9600);
}

void loop()
{
  Serial.print("Left encoder: ");
  Serial.println(left.getVal());
  Serial.print("Right encoder: ");
  Serial.println(right.getVal());
  delay(1000);
}
#endif




