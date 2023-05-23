#ifndef H_ULTRASONIC_H
#define H_ULTRASONIC_H

#include "Arduino.h"

class UltrasonicSensor
{
public:
  UltrasonicSensor(uint8_t trig_pin, uint8_t echo_pin);
  void begin();
  float get_distance_cm();

private:
  uint8_t m_trig_pin;
  uint8_t m_echo_pin;
};

#endif