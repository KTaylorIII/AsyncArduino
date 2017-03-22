#ifndef SIG_H_
#define SIG_H_

#include <stdint.h>
#include "Arduino.h"

#define S_STATE_IS_ACTIVE 1
#define S_STATE_IS_HI 2

typedef struct {
  /*
   * S_STATE DESCRIPTION BY BIT INDEX
   * 
   * 0 - IS_ACTIVE - Is the signal present?
   * 1 - IS_HIGH - Is the square wave high or low?
   */
  uint8_t s_state;
  uint8_t s_pin;
  uint32_t s_last_trigger; // MICROSECONDS
  uint32_t s_active_hi; // MICROSECONDS
  uint32_t s_active_lo; // MICROSECONDS
}sigl;


void sigl_init(sigl *sig, uint8_t pin, uint32_t active_hi, uint32_t active_lo);
void sigl_begin(sigl *sig);
void sigl_process(sigl *sig, const uint32_t *clk);
void sigl_stop(sigl *sig);


#endif

