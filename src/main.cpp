#include <Arduino.h>
#include "board.h"
#include "turn_and_go.h"

TurnAndGo turn_and_go(500, 500);

void setup() {
	// Serial.begin(9600);
	delay(5000);
	turn_and_go.translateFrom(1000);
}

void loop() {
	// Serial.println(batteryVoltage());
	// delay(1000);
}
