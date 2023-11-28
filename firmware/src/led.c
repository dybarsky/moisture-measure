/*
frequency = 1 MHz
divider = 4
clock = 250 000
pwm freq = 100 Hz
pwm time = 20 %
pwm full = 2500 -> clock / freq
pwm time = 500 -> full * time

Total out pins = 10
Port 1 pins = 6
Port 2 pins = 4

The out pins bits are stored in two 8-bit digits, 4 and 6 out pins bits each,
in order where pins numbers start from the highest position and goes right
port 2 bits: ____0123
port 1 bits: __456789
Defined by hardware

The binary mask defines on/off state for each out pin.
It has size of 16 and contains 10 bits of data in a way where:
- out pins numbers start from the highest bit and goes right
- first 4 highest bits belong to port 2, rest 6 bits belong to port 1
binary bits (pins numbers): 01234567890______
binary bits (port belongs): 22221111111______

The mask is generated based on level value. There are 2 ways of creation:
1. Shifting all 1 bits right by level filling with 0 and invert
    111111111 -> 00011111 -> 11100000
2. Shifing the lowest 1 bit cyclically right by level filling with 0
    000000001 -> 00100000

The final values for PxOUT registers are calculated by
applying binary mask on port digit with bits defining out pins.
Since bits in binary mask belong to different ports, it should be separated:
1. Aligning the highest 4 bits of binary mask to the right
    2222111111_______ -> ____2222
2. Aligning the lowest bits of binary mask to the right
    2222111111_______ -> __111111
*/

#include <msp430g2553.h>
#include "led.h"

// PWM time
#define PWM_FULL 2500
#define PWM_DUTY 500
// Binary mask
#define SIZE 16
#define DATA 10
#define SPRT 04
#define SHFT1 SIZE - DATA
#define SHFT2 SIZE - SPRT
// Port 2 out
#define PIN_0 BIT3
#define PIN_1 BIT2
#define PIN_2 BIT1
#define PIN_3 BIT0
// Port 1 out
#define PIN_4 BIT5
#define PIN_5 BIT4
#define PIN_6 BIT3
#define PIN_7 BIT2
#define PIN_8 BIT1
#define PIN_9 BIT0

unsigned int binary = 0;
unsigned char port2 = PIN_0 | PIN_1 | PIN_2 | PIN_3;
unsigned char port1 = PIN_4 | PIN_5 | PIN_6 | PIN_7 | PIN_8 | PIN_9;

void configure_led() {
    // configure out ports
    P2DIR |= PIN_0 | PIN_1 | PIN_2 | PIN_3;
    P1DIR |= PIN_4 | PIN_5 | PIN_6 | PIN_7 | PIN_8 | PIN_9;
    // configure timer counter
    TA0CCR0 = PWM_FULL;
    TA0CCR1 = PWM_DUTY;
    // enable timer interruptions
    TA0CCTL0 = CCIE;
    TA0CCTL1 = CCIE;
    // sum-main clock + freq divider 2 + up mode + init
    TA0CTL = TASSEL_2 + ID_2 + MC_1 + TACLR;
}

void display_level(char level) {
    // shift all 1 bits right filling with 0 and invert
    binary = ~(0xFFFF >> level);
}

void display_point(char level) {
    // shift 1 right filling with 0
    binary = 1 << (SIZE - level);
}

#pragma vector = TIMER0_A0_VECTOR
__interrupt void on_timer0_ccr0(void) {
    unsigned char mask1 = binary >> SHFT1;
    unsigned char mask2 = binary >> SHFT2;
    // turn on ports
    P1OUT |= port1 & mask1;
    P2OUT |= port2 & mask2;
    // reset interruption flag
    TA0CCTL0 &= ~CCIFG;
}

#pragma vector = TIMER0_A1_VECTOR
__interrupt void on_timer0_ccr1(void) {
    // turn off ports
    P1OUT &= ~port1;
    P2OUT &= ~port2;
    // reset interruption flag
    TA0CCTL1 &= ~CCIFG;
}
