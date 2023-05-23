#include "encoder.h"

Encoder::Encoder(uint8_t CLK_pin)
                 : m_CLK_pin(CLK_pin)
{
}

void Encoder::begin(void (*func)())
{
  pinMode(m_CLK_pin, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(m_CLK_pin), func, CHANGE);
}
