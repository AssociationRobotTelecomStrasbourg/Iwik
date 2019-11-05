#include <Arduino.h>
#include <Wire.h>
#include <VL53L0X.h>
#include "board.h"
#include "turn_and_go.h"
#include "odometry.h"

VL53L0X lidar;
int32_t distance_read;
int32_t distance_wanted = 100;

TurnAndGo turn_and_go(500, 500);

void setup() {
    // Setup serial link
    Serial.begin(9600);

    // Setup lidar
    Wire.begin(); // Initialize I²C
	lidar.init();
    lidar.setTimeout(500);
    lidar.setMeasurementTimingBudget(200000); // High accuracy setting

    // Wait before starting loop
	delay(5000);
}

void loop() {
	distance_read = lidar.readRangeSingleMillimeters();

	turn_and_go.translateFrom(distance_read-distance_wanted);
}
