/*
Reads data from soil moisture sensor using ADC.
*/

#include <msp430g2553.h>
#include "sensor.h"

#define RES 1024
#define PIN BIT7
#define CHANNEL INCH_7

void configure_sensor() {
    P1SEL |= PIN;
    P1SEL2 |= PIN;
    // set default voltage reference, 16 cycles, enables
    ADC10CTL0 = SREF_0 | ADC10SHT_2 | ADC10ON;
    // set input channel, samble source, clock divider, clock, single channel + single conv
    ADC10CTL1 = CHANNEL | SHS_0 | ADC10DIV_0 | ADC10SSEL_0 | CONSEQ_0;
    // enable analog input
    ADC10AE0 = PIN;
    // enable coversion
    ADC10CTL0 |= ENC;
}

float read_sensor() {
    // start conversion
    ADC10CTL0 |= ADC10SC;
    // wait while busy
    while (ADC10CTL1 & ADC10BUSY);
    // map to value from 0 to 1
    float value = ADC10MEM;
    return value / RES;
}
