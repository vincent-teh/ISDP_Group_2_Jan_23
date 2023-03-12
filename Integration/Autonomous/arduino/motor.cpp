#include "motor.h"

Motor::Motor(uint8_t left_enable_pin, uint8_t left_pin_forward,
             uint8_t left_pin_backward, uint8_t right_pin_forward,
             uint8_t right_pin_backward, uint8_t right_enable_pin)
            : m_left_enable_pin(left_enable_pin),
              m_left_pin_forward(left_pin_forward),
              m_left_pin_backward(left_pin_backward),
              m_right_pin_forward(right_pin_forward),
              m_right_pin_backward(right_pin_backward),
              m_right_enable_pin(right_enable_pin)
{
}

void Motor::begin()
{
  pinMode(m_left_enable_pin, OUTPUT);
  pinMode(m_left_pin_forward, OUTPUT);
  pinMode(m_left_pin_backward, OUTPUT);
  pinMode(m_right_pin_forward, OUTPUT);
  pinMode(m_right_pin_backward, OUTPUT);
  pinMode(m_right_enable_pin, OUTPUT);
}

void Motor::m_setPinOut(bool turn_left, bool turn_right)
{
  digitalWrite(m_left_pin_forward, turn_left);
  digitalWrite(m_left_pin_backward, !turn_left);
  digitalWrite(m_right_pin_forward, turn_right);
  digitalWrite(m_right_pin_backward, !turn_right);
  
  #ifdef DEBUG
    Serial.println("Debug info: ");
    Serial.print(turn_left);
    Serial.print(!turn_left);
    Serial.print(turn_right);
    Serial.print(!turn_right);
  #endif
}

void Motor::setSpeed(uint8_t left_speed, uint8_t right_speed)
{
  analogWrite(m_left_enable_pin, left_speed);
  analogWrite(m_right_enable_pin, right_speed);
}

void Motor::setDirection(uint8_t direction)
{
  switch (direction) {
    case FORWARD:
      Motor::m_setPinOut(1, 1);
      break;
    case BACKWARD:
      Motor::m_setPinOut(0, 0);
      break;
    case TURN_LEFT:
      Motor::m_setPinOut(1, 0);
      break;
    case TURN_RIGHT:
      Motor::m_setPinOut(0, 1);
      break;
    case STOP:
      Motor:setSpeed(0, 0);
      break;
  }
}