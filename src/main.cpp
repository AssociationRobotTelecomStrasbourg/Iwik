#include <Arduino.h>
#include "board.h"
#include "turn_and_go.h"
#include "odometry.h"

TurnAndGo turn_and_go(500, 500);

void setup() {
	// Serial.begin(9600);
	delay(10000);
	// wheel_perimeter_calibration(turn_and_go, 1000);
	center_distance_calibration(turn_and_go, 10)
}

void loop() {
	// Serial.println(batteryVoltage());

	// step_ratio_calibration(turn_and_go, 1000);
	// delay(1000);
}
