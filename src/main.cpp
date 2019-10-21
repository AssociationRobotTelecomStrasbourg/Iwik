#include <Arduino.h>
#include "board.h"
#include "turn_and_go.h"

TurnAndGo turn_and_go;

void setup() {
	Serial.begin(9600);
	delay(1500);
}

void loop() {
	Serial.println(batteryVoltage());

	turn_and_go.goTo(1000, 0);
	turn_and_go.goTo(0, 0);
	delay(1000);
}
