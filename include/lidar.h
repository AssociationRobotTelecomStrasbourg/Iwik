#ifndef LIDAR_H
#define LIDAR_H

#include <VL53L0X.h>
#include <Wire.h>

// Lidar parameters
const uint16_t timeout = 500;

class Lidar {
public:
	// Initialize TurnAndGo
	Lidar();

	// Measure distance
	uint16_t readDistance();

private:
	VL53L0X vl;
};

#endif
