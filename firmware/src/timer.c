/*
frequency = 1 MHz
divider = 8
clock = 125 000
freq = 50 Hz
time = 2500 -> clock / freq
*/

#include <msp430g2553.h>
#include "timer.h"

// counter
#define COUNT 2500

void configure_timer() {
    // configure timer counter
    TA1CCR0 = COUNT;
    // enable timer interruptions
    TA1CCTL0 = CCIE;
    // sum-main clock + freq divider 2 + up mode + init
    TA1CTL = TASSEL_2 + ID_3 + MC_1 + TACLR;
}

#pragma vector = TIMER1_A0_VECTOR
__interrupt void on_timer1_ccr0(void) {
    // invoke callback
    on_timer_callback();
    // reset interruption flag
    TA1CCTL0 &= ~CCIFG;
}
