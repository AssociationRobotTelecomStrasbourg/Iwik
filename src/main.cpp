#include <Arduino.h>
#include "board.h"
#include "turn_and_go.h"
#include "binserial.h"
// #include "lidar.h"
// #include "odometry.h"

float distance = 100;

TurnAndGo turn_and_go;

void setup() {
    // Setup serial link
    // Serial.begin(9600);
    // while(!Serial);
    pinMode(LED_BUILTIN, OUTPUT);
}

void loop() {
    if (turn_and_go.run() == STOP) {
        delay(1000);
        // writeData(turn_and_go.getPosition(), sizeof(position_t));
        turn_and_go.goTo(distance, 0);
        distance = -distance;
    }
}
