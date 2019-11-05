#include "lidar.h"

Lidar::Lidar() {
	Wire.begin(); // Initialize I²C
	vl.init();
	vl.setTimeout(timeout);
	vl.setMeasurementTimingBudget(200000); // High accuracy setting
}

uint16_t Lidar::readDistance() {
	return vl.readRangeSingleMillimeters();
}
