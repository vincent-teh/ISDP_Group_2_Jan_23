#include "encoder.h"

Encoder::Encoder(uint8_t CLK_pin, uint8_t DT_pin) :
                m_CLK_pin(CLK_pin),
                m_DT_pin(DT_pin)
{
}

void Encoder::handleInterrupt()
{
  uint8_t clk_state = digitalRead(m_CLK_pin);
  uint8_t dt_state  = digitalRead(m_DT_pin);

  if (clk_state != m_old_clk_state) {
    if (clk_state != dt_state)  // CLK is ahead of DT
      m_rotation_num++;
    else                        // CLK is behindof DT
      m_rotation_num--;
  }
  m_old_clk_state = clk_state;
}

void Encoder::begin(void (*func)())
{
  pinMode(m_CLK_pin, INPUT_PULLUP);
  pinMode(m_DT_pin,  INPUT_PULLUP);
  attachInterrupt(m_CLK_pin, func, CHANGE);
}

int32_t Encoder::getVal()
{
  return m_rotation_num;
}

uint8_t Encoder::getCLKPin() {
  return m_CLK_pin;
}

uint8_t Encoder::getDTPin() {
  return m_DT_pin;
}
