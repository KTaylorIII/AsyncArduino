#include "button.h"
void button_init(button* btn, const uint8_t pin, const uint32_t pressDelay){
    memset(btn, 0, sizeof btn);
    btn->b_pin = pin;
    pinMode(pin, INPUT);
    btn->b_delay = pressDelay;
}
void button_listen(button* btn){
    btn->b_st = btn->b_st | BUTTON_IS_ACTIVE;
}
uint8_t button_press(button* btn, uint32_t* clk){
    
    if ((btn->b_st & BUTTON_IS_ACTIVE) && ((*clk - btn->b_l_trigger)>=btn->b_delay)){
      if (!(btn->b_st & BUTTON_IS_HIGH) && digitalRead(btn->b_pin)){
        // If the button was previously depressed and is now pressed..
        btn->b_st = btn->b_st | BUTTON_IS_HIGH;
        btn->b_l_trigger = *clk;
        return 1;
      }
    }
    return 0;
}
uint8_t button_hold(button* btn, uint32_t* clk)
{
    
    if (btn->b_st & BUTTON_IS_ACTIVE){
      // If the input is active
      if ((*clk - btn->b_l_trigger) >= (btn->b_delay)){
        // .. and time elapsed since last trigger exceeds the delay
        if ((btn->b_st & BUTTON_IS_HIGH) && digitalRead(btn->b_pin)){
          // .. and the button is held down, then return 1
          btn->b_l_trigger = *clk;
          return 1;
        }
        
      }
    }
    return 0;
}
uint8_t button_release(button* btn, uint32_t* clk){
    if (btn->b_st & BUTTON_IS_ACTIVE){
      // If the input is active
      if ((*clk - btn->b_l_trigger) >= (btn->b_delay)){
        // .. and time elapsed since last trigger exceeds the delay
        if ((btn->b_st & BUTTON_IS_HIGH) && !digitalRead(btn->b_pin)){
          btn->b_st = btn->b_st & ~BUTTON_IS_HIGH;
          btn->b_l_trigger = *clk;
          return 1;
        }
      }
    }
    return 0;
}

void button_stop(button* btn){
    btn->b_st = btn->b_st & ~BUTTON_IS_ACTIVE;
    btn->b_l_trigger = 0;
}

