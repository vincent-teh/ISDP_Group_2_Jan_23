/**
 * Authhor: Teh Yu Sheng
 * Desc: This file shows the code for 2 wheel drive DC motor.
 *       Kindly do motor.begin() in the setup portion of the 
 *       main file to initialise the class. When enable debug,
 *       private variables and methods will be freed to use
 *       certain methods may display additional infos. 
 */


#ifndef H_MOTOR_H
#define H_MOTOR_H

#include <Arduino.h>

#define FORWARD     0
#define BACKWARD    1
#define TURN_LEFT   2
#define TURN_RIGHT  3
#define STOP        4

class Motor
{
public:
  Motor(uint8_t left_enable_pin, uint8_t left_pin_forward,
        uint8_t left_pin_backward, uint8_t right_pin_forward,
        uint8_t right_pin_backward, uint8_t right_enable_pin);
  void begin();
  void setSpeed(uint8_t left_speed, uint8_t right_speed);
  void setDirection(uint8_t direction);

#ifndef DEBUG
private:
#endif
  void m_setPinOut(bool left, bool right);
  uint8_t m_left_enable_pin;
  uint8_t m_left_pin_forward;
  uint8_t m_left_pin_backward;
  uint8_t m_right_enable_pin;
  uint8_t m_right_pin_forward;
  uint8_t m_right_pin_backward;
};

#endif
