#include <Arduino.h>
#include "TMC2130Stepper.h"
#include "protoPins.h"
#include <TMC2130Stepper.h>

TMC2130Stepper DRV2 = TMC2130Stepper(EN2, DIR2, STEP2, CS2, SDI, SDO, SCK);
TMC2130Stepper DRV1 = TMC2130Stepper(EN1, DIR1, STEP1, CS1, SDI, SDO, SCK);
bool dir = true;

void setup() {

	//The delays between SPI calls seem to be important for consistent behaviour

	digitalWrite(EN2, HIGH); //Disable output stage by default
	digitalWrite(EN1, HIGH);
	delay(100);
	//Initialize SPI, set current to 600mA, and activate stealthchop for both drivers
	//Both drivers need to be initialized even if only one is used
	DRV2.begin();
	DRV1.begin();
	delay(100);

	DRV2.SilentStepStick2130(600);
	DRV1.SilentStepStick2130(600);
	delay(100);

	DRV1.stealthChop(1);
	DRV2.stealthChop(1);
	delay(100);

	digitalWrite(EN2, LOW); //Turning on the output stage
	digitalWrite(EN1, LOW);

	delay(3000);
}

void loop() {

	//Rotating both motors alternatively in both directions every 2 seconds
	digitalWrite(STEP2, HIGH);
	digitalWrite(STEP1, HIGH);

	delayMicroseconds(10);

	digitalWrite(STEP2, LOW);
	digitalWrite(STEP1, LOW);

	delayMicroseconds(10);

	uint32_t ms = millis();
	static uint32_t last_time = 0;
	if ((ms - last_time) > 2000) {
		if (dir) {
			DRV2.shaft_dir(1);
			DRV1.shaft_dir(1);
		} else {
			DRV2.shaft_dir(0);
			DRV1.shaft_dir(0);
		}
		dir = !dir;
		last_time = ms;
	}
}
