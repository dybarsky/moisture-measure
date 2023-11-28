#include <msp430g2553.h>
#include "led.h"
#include "timer.h"
#include "sensor.h"

// global definitions
#define COUNT 10
#define FREQUENCY 50
#define MODE_DEMO 0x01
#define MODE_DATA 0x02

// modes
char mode;
void demo_mode();
void data_mode();

// initialization
void configure() {
	// turn off watchdog
    WDTCTL = WDTPW + WDTHOLD;
	// set frequency 1MHz
    BCSCTL1 = CALBC1_1MHZ;
  	DCOCTL = CALDCO_1MHZ;
	// set all pins off
    P1OUT = 0;
    P2OUT = 0;
}

// starting point
int main(void) {
	// set up
	mode = MODE_DEMO;
    configure();         
    configure_led();
    configure_timer();
    configure_sensor();
	// enable interruptions
	_BIS_SR(GIE);
	// main loop
	while (1);
}

// defined in timer.h
void on_timer_callback() {
	switch (mode) {
		case MODE_DEMO:
			demo_mode();
			break;
		case MODE_DATA: 
			data_mode();
			break;
	}
}

// display demo
char point;
char counter = 0;
char divider = FREQUENCY / COUNT;
void demo_mode() {
	point = counter / divider;
	display_point(point);
	counter ++;
	if (counter > FREQUENCY) {
		mode = MODE_DATA;
	}
}

// display sensor data
void data_mode() {
	float value = read_sensor();
	float inverted = 1 - value;
	char level = inverted * COUNT;
	display_level(level);
}
