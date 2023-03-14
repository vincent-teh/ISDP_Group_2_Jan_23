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

void Encoder::handleInterrupt()
{
  uint8_t clk_state = digitalRead(m_CLK_pin);

  if (clk_state != m_old_clk_state)
    m_counter++;
  m_old_clk_state = clk_state;
}

void Encoder::resetCount()
{
  m_counter = 0;
}

int32_t Encoder::getVal()
{
  return m_counter;
}

uint8_t Encoder::getCLKPin() {
  return m_CLK_pin;
}
