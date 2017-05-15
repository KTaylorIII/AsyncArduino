#include "sig.h"

void sigl_init(sigl *sig, uint8_t pin, uint32_t active_hi, uint32_t active_lo){
    memset(sig, 0, sizeof sig);
    sig->s_pin = pin;
    sig->s_active_hi = active_hi;
    sig->s_active_lo = active_lo;
}

void sigl_begin(sigl *sig){
    pinMode(sig->s_pin, OUTPUT);
    sig->s_state = sig->s_state | S_STATE_IS_ACTIVE;
}

void sigl_process(sigl *sig, const uint32_t *clk){
    if (sig->s_state & S_STATE_IS_ACTIVE){ // If the signal's active
        if (sig->s_state & S_STATE_IS_HI){ // .. and high
            if ((*clk - sig->s_last_trigger) >= sig->s_active_hi){
                // .. and delta t yields/exceeds active hi duration
                // then disable pin and reverse pin state
                sig->s_last_trigger = *clk;
                digitalWrite(sig->s_pin, LOW);
                sig->s_state ^= S_STATE_IS_HI;
            }
        }
        else{ // otherwise, if lo
            if ((*clk - sig->s_last_trigger) >= sig->s_active_lo){
                // .. and delta t yields/exceeds active lo duration
                sig->s_last_trigger = *clk;
                digitalWrite(sig->s_pin, HIGH);
                sig->s_state ^= S_STATE_IS_HI;
            }
        }
    }
}

void sigl_stop(sigl *sig){
  digitalWrite(sig->s_pin, LOW);
  sig->s_state = sig->s_state & ~(S_STATE_IS_HI|S_STATE_IS_ACTIVE);
  sig->s_last_trigger = 0;
}
