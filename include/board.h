#ifndef BOARD_H
#define BOARD_H

#include <Arduino.h>

#define SCK 13
#define SDO 12
#define SDI 11
#define CS2 9
#define CS1 10
#define EN2 4 //Pulled high by default, drivers are disabled, must be pulled low to enable output stage
#define EN1 14
#define DIR2 23
#define DIR1 21
#define STEP2 22
#define STEP1 20
#define BATT_LVL A1 //Read ADC to get battery level, voltage division is 0.1287 (measured)

//Side header is as follows (from top to bottom) : GND SCL SDA 17-A3 16-A2 3V3
#define SCL 19 //Broken out I2C port on side header
#define SDA 18
#define IO1 17 //Free pins on the side header
#define IO2 16

// Return battery voltage
float batteryVoltage();

#endif
