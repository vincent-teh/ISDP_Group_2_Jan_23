#ifndef H_ENCODER_H
#define H_ENCODER_H

#include <Arduino.h>

class Encoder
{
public:
  Encoder(uint8_t CLK_pin, uint8_t DT_pin);
  
  void    begin(void (*func)());
  void    handleInterrupt();

/**
 * So far unused code
 */
  uint8_t getCLKPin();
  uint8_t getDTPin();
  int32_t getVal();

private:
  int32_t m_rotation_num  = 0;
  uint8_t m_old_clk_state = 0;
  uint8_t m_CLK_pin;
  uint8_t m_DT_pin;
};

#endif
