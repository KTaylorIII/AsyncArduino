#ifndef BUTTON_H_
#define BUTTON_H_

#include <stdint.h>
#include "Arduino.h"
// Bit shortcuts
#define BUTTON_IS_ACTIVE 1
#define BUTTON_IS_HIGH 2
typedef struct{
  /*
   * b_l_trigger : Arduino time since the button was last pressed or
   * released
   * b_delay : Action delay; if the button IS_HIGH, ignore changes
   * in state. Expressed in microseconds
   * 
   * b_st : Button state. By bit index:
   *  0 - IS_ACTIVE - True if button input is enabled
   *  1 - IS_HIGH - True if button is pressed
   */
  uint32_t b_l_trigger;
  uint32_t b_delay;
  uint8_t b_pin; // Button input pin

  uint8_t b_st; // Button state
  
}button;
/*  button_init - Initializes the button structure for further use
    button_start - Sets IS_ACTIVE bit to 1, allowing button functions
    to listen for user events
    on_button_press - Executes the callback handle upon a button
    press and sets b_l_trigger to the current clock value
    on_button_h_or_r - Executes one of two possible callbacks
    depending on whether a button is held down or released after an
    interval specified by b_l_trigger. b_l_trigger also updates here
    button_stop - Sets IS_ACTIVE bit
 */
#ifdef __cplusplus
extern "C"{
#endif

void button_init(button* btn, const uint8_t pin, const uint32_t pressDelay);
void button_listen(button* btn);
uint8_t button_press(button* btn, uint32_t* clk);
uint8_t button_hold(button* btn, uint32_t* clk);
uint8_t button_release(button* btn, uint32_t* clk);
void button_stop(button* btn);

#ifdef __cplusplus
}
#endif

#endif
