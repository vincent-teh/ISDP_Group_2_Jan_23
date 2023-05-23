#include "ultrasonic.h"

UltrasonicSensor::UltrasonicSensor(uint8_t trig_pin, uint8_t echo_pin)
    : m_trig_pin(trig_pin),
      m_echo_pin(echo_pin)
{
}

void UltrasonicSensor::begin()
{
  pinMode(m_trig_pin, OUTPUT);
  pinMode(m_echo_pin, INPUT);
}

float UltrasonicSensor::get_distance_cm()
{
  digitalWrite(m_trig_pin, HIGH);
  delayMicroseconds(10);
  digitalWrite(m_trig_pin, LOW);

  unsigned long duration_us = pulseIn(m_echo_pin, HIGH);
  return 0.017 * duration_us;
}
