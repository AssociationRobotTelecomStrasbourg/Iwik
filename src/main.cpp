#include <Arduino.h>
#include "board.h"
#include "turn_and_go.h"

TurnAndGo turn_and_go(500, 500);

void setup() {
	// Serial.begin(9600);
	delay(5000);
}

void loop() {
	// Serial.println(batteryVoltage());

	turn_and_go.goTo(500, 0);
	turn_and_go.goTo(0, 0);
	turn_and_go.rotateFrom(M_PI);
	delay(5000);
}
