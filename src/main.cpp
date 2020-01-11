#include <Arduino.h>
#include "board.h"
#include "turn_and_go.h"
#include "binserial.h"
// #include "lidar.h"
// #include "odometry.h"

int32_t distance = 300;

TurnAndGo turn_and_go;

void setup() {
    // Setup serial link
    Serial.begin(9600);
    while(!Serial);
    pinMode(LED_BUILTIN, OUTPUT);
    turn_and_go.translateFrom(distance);
}

void loop() {
    if (!turn_and_go.run()) {
        writeData(turn_and_go.getPosition(), sizeof(position_t));
        distance = -distance;
        turn_and_go.translateFrom(distance);
    }
}
