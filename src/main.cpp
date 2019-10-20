#include <Arduino.h>
#include <TMC2130Stepper.h>
#include <TeensyStep.h>
#include "protoPins.h"

TMC2130Stepper stepper_config1 = TMC2130Stepper(EN1, DIR1, STEP1, CS1, SDI, SDO, SCK);
TMC2130Stepper stepper_config2 = TMC2130Stepper(EN2, DIR2, STEP2, CS2, SDI, SDO, SCK);

Stepper stepper1(STEP1, DIR1);
Stepper stepper2(STEP2, DIR2);

StepControl controller;

uint32_t stepsPerSecond = 50000;
uint32_t stepsPerSecondSquared = 50000;
int32_t distance = 100000;

int8_t turn = 1;

void setup() {

	// The delays between SPI calls seem to be important for consistent behaviour
	// Driver Enables are at 1 (3V3) by default, i.e disabled, you need to pull them low to enable the drivers.

	delay(10);
	// Initialize SPI, set current to 600mA, and activate stealthchop for both drivers
	// Both drivers need to be initialized even if only one is used
	stepper_config1.begin();
	stepper_config2.begin();
	delay(10);

	stepper_config1.SilentStepStick2130(600);
	stepper_config2.SilentStepStick2130(600);
	delay(10);

	stepper_config1.stealthChop(1);
	stepper_config2.stealthChop(1);
	delay(10);

	// Configure max speed and acceleration
	stepper1
		.setMaxSpeed(stepsPerSecond)
		.setAcceleration(stepsPerSecondSquared)
		.setInverseRotation(true);

	stepper2
		.setMaxSpeed(stepsPerSecond)
		.setAcceleration(stepsPerSecondSquared);

	// Turning on the driver
	digitalWrite(EN1, LOW);
	digitalWrite(EN2, LOW);
}

void loop() {
	stepper1.setTargetRel(distance);
	stepper2.setTargetRel(distance);
	controller.move(stepper1, stepper2);

	stepper1.setTargetRel(-distance);
	stepper2.setTargetRel(-distance);
	controller.move(stepper1, stepper2);
}
