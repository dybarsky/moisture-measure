/*
Soil moisture sensor control.
Read data is float in range [0; 1]
*/

#ifndef HEADER_SENSOR
#define HEADER_SENSOR

void configure_sensor();
float read_sensor();

#endif // HEADER_SENSOR