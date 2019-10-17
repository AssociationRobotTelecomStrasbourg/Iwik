#include <Arduino.h>
#include <TMC2130Stepper.h>
#include <AccelStepper.h>
#include "protoPins.h"

TMC2130Stepper stepper_config1 = TMC2130Stepper(EN1, DIR1, STEP1, CS1, SDI, SDO, SCK);
TMC2130Stepper stepper_config2 = TMC2130Stepper(EN2, DIR2, STEP2, CS2, SDI, SDO, SCK);

AccelStepper stepper1(1, STEP1, DIR1);
AccelStepper stepper2(1, STEP2, DIR2);

uint32_t stepsPerSecond = 40000;
uint32_t stepsPerSecondSquared = 100000;
int32_t distance = 50000;

int8_t turn = 1;

void setup() {

	//The delays between SPI calls seem to be important for consistent behaviour
	//Driver Enables are at 1 (3V3) by default, i.e disabled, you need to pull them low to enable the drivers.

	delay(10);
	//Initialize SPI, set current to 600mA, and activate stealthchop for both drivers
	//Both drivers need to be initialized even if only one is used
	stepper_config1.begin();
	stepper_config2.begin();
	delay(10);

	stepper_config1.SilentStepStick2130(600);
	stepper_config2.SilentStepStick2130(600);
	delay(10);

	stepper_config1.stealthChop(1);
	stepper_config2.stealthChop(1);
	delay(10);

	stepper1.setMaxSpeed(stepsPerSecond);
	stepper2.setMaxSpeed(stepsPerSecond);

	stepper1.setAcceleration(stepsPerSecondSquared);
	stepper2.setAcceleration(stepsPerSecondSquared);

	digitalWrite(EN1, LOW); //Turning on the output stage
	digitalWrite(EN2, LOW);

	delay(3000);
}

void loop() {
	if (stepper1.distanceToGo() == 0 && stepper2.distanceToGo() == 0) {
		stepper1.move(-turn * distance);
		stepper2.move(turn * distance);
		turn *= -1;
	}
	stepper1.run();
	stepper2.run();
}
