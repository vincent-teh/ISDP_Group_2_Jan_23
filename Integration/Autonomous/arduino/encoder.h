/**
 * Authhor: Teh Yu Sheng
 * Date: 14/3/2023
 * Objective: Encoder class that handles clk interrupt signal and add counters
 * Desc: Encoder class handles the signals coming from the rotary encoder.
 *       In the testing however, realize that the encoder is not sensitive
 *       enough to detect difference in CLK output and DT output. Thus,
 *       resulting both of them always having the same value. Rotary direction
 *       feature is thus remove and only consist of rotation counting methods.
 * Example:
 *
 * Encoder encoder(2);
 *
 * void ISR_Handler()
 * {
 *   encoder.handleInterrupt();
 * }
 *
 * void setup()
 * {
 *   Serial.begin(9600);
 *   encoder.begin(&handleLeftInterrupt);
 * }
 *
 * void loop()
 * {
 *   Serial.println(encoder.getVal());
 *   delay(2000);
 * }
 */

#ifndef H_ENCODER_H
#define H_ENCODER_H

#include <Arduino.h>

class Encoder
{
public:
  Encoder(uint8_t CLK_pin);

  /**
   * @brief Initiate the class in void setup() Arduino
   * @param func the static interrupt handler function
   * @example encoder.begin(&ISR_Function)
   */
  void begin(void (*func)());

  /**
   * @brief The defaultHandler when interrupt happened.
   *        Please call this function in the ISR_Function.
   * @example void ISR_Function() {encoder.handleInterrupt();}
   */
  void handleInterrupt();
  /**
   * @brief Reset the number of rotation
   */
  void resetCount();

  /**
   * @brief Return the CLK pin register with the class
   * @return uint8_t m_CLK_pin
   */
  uint8_t getCLKPin();
  /**
   * @brief Get the number of rotation
   * @return int32_t m_counter
   */
  int32_t getVal();

private:
  volatile int32_t m_counter       = 0;
  volatile uint8_t m_old_clk_state = 0;
  uint8_t m_CLK_pin;
};

#endif
