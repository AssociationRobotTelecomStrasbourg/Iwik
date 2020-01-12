#include <Arduino.h>
#include "board.h"
#include "turn_and_go.h"
#include "binserial.h"
// #include "lidar.h"
// #include "odometry.h"

int32_t distance = 100;

TurnAndGo turn_and_go;

void setup() {
    // Setup serial link
    Serial.begin(9600);
    while(!Serial);
    pinMode(LED_BUILTIN, OUTPUT);
    turn_and_go.goTo(distance, 0);
}

void loop() {
    if (turn_and_go.run() == STOP) {
        writeData(turn_and_go.getPosition(), sizeof(position_t));
        distance = -distance;
        turn_and_go.goTo(distance, 0);
    }
}
