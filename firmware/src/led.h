/*
LED bar control.
level should be in range [0; 10]
*/

#ifndef HEADER_LED
#define HEADER_LED

void configure_led();
void display_level(char level);
void display_point(char level);

#endif // HEADER_LED