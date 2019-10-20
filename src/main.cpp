#include <Arduino.h>
#include "board.h"
#include "turn_and_go.h"

TurnAndGo turn_and_go;

void setup() {
	Serial.begin(9600);
	delay(3000);
}

void loop() {
	Serial.println(batteryVoltage());

	turn_and_go.goTo(100, -50);
	delay(500);

	turn_and_go.goTo(100, 50);
	delay(500);

	turn_and_go.goTo(-100, -50);
	delay(500);

	turn_and_go.goTo(-100, 50);
	delay(500);
}
