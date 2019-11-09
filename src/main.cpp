#include <Arduino.h>
#include "board.h"
#include "turn_and_go.h"
#include "lidar.h"
// #include "odometry.h"

Lidar lidar;

int32_t safety_distance = 200, dir = 1;

TurnAndGo turn_and_go;

void setup() {
    // Setup serial link
    Serial.begin(9600);
    pinMode(LED_BUILTIN, OUTPUT);
    // Wait before starting loop
	delay(5000);
}

void loop() {
    if (safety_distance > lidar.readDistance())
        turn_and_go.stopAsync();
    else if (!turn_and_go.isMoving()) {
        turn_and_go.translateFromAsync(dir*300);
        dir *= -1;
    }
}
