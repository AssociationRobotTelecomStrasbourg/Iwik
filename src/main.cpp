#include <Arduino.h>
#include "board.h"
#include "turn_and_go.h"
#include "lidar.h"
#include "odometry.h"

Lidar lidar;
int32_t distance_read;
int32_t distance_wanted = 100;

TurnAndGo turn_and_go(500, 500);

void setup() {
    // Setup serial link
    Serial.begin(9600);

    // Wait before starting loop
	delay(5000);
}

void loop() {
	distance_read = lidar.readDistance();

	turn_and_go.translateFrom(distance_read-distance_wanted);
}
