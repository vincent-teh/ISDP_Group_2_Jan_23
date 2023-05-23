/**
 * Authhor: Teh Yu Sheng
 * Date: 23/5/2023
 * Objective: Main function for running a Arduino Powered Robot Car.
 * Desc: The main function pulls 2 library which is motor class and ultrasonic
 *       class. The main function will read input through serial communication
 *       (USB).
 *       Case FORWARD: The car will constantly moves until the distance less
 *                     than 20cm through ultrasonic sensor.
 *       Case LEFT & RIGHT: The car will perform turning through differential
 *                          drive principle. Adjust the turn_time parameters
 *                          for accurate angle.
 */

#include "motor.h"
#include "ultrasonic.h"

#define INVERTED

#define BAUD_RATE 9600

// Motor Driver's Pins
#define EN_A          5
#define LEFT_FORW     6
#define LEFT_BACKW    7
#define RIGHT_FORW    9
#define RIGHT_BACKW   8
#define EN_B          10

// Ultrasonic Sensor's Pin
#define TRIG_PIN 13
#define ECHO_PIN 12

#define LEFT_TURN_TIME  500 //ms
#define RIGHT_TURN_TIME 500 //ms

#define SPEED 255

Motor my_car(EN_A, LEFT_FORW, LEFT_BACKW, RIGHT_FORW, RIGHT_BACKW, EN_B);
UltrasonicSensor my_ult_sensor(TRIG_PIN, ECHO_PIN);

void setup()
{
  my_car.begin();
  Serial.begin(9600);
  my_ult_sensor.begin();
}

void loop()
{
  if (Serial.available()) {
    int data = Serial.readString().toInt();
    int distance = 100;
    Serial.println(data);
    switch (data) {
      case (FORWARD):
        my_car.setDirection(FORWARD);
        my_car.setSpeed(SPEED, SPEED);
        while (distance > 20) {
          delay(50);
          distance = my_ult_sensor.get_distance_cm();
          Serial.println(distance);
        }
        break;
      case (TURN_LEFT):
        my_car.setDirection(TURN_LEFT);
        my_car.setSpeed(SPEED, SPEED);
        delay(LEFT_TURN_TIME);
        break;
      case (TURN_RIGHT):
        my_car.setDirection(TURN_RIGHT);
        my_car.setSpeed(SPEED, SPEED);
        delay(RIGHT_TURN_TIME);
        break;
    }
    my_car.setDirection(STOP);
  }
}


