#ifndef TURN_AND_GO_H
#define TURN_AND_GO_H

#include <TMC2130Stepper.h>
#include <TeensyStep.h>
#include "board.h"

// Distance are in mm
const float wheel_perimeter = 236;
const float center_distance = 195;

const uint8_t microstep = 16;
const uint32_t step_per_turn = 200*microstep;

const float maximum_speed = 1000; // Maximum speed without step loss in mm/s
const float acceleration = 1000; // Acceleration in mm/s^2

struct position_t {
	float x, y, theta;
};

class TurnAndGo {
public:
	// Initialize TurnAndGo
	TurnAndGo();

	// Go to (x,y) in mm
	void goTo(float x, float y);

	// Rotate from delta_theta in rad
	void rotateFrom(float delta_theta);

	// Rotate to theta in rad
	void rotateTo(float theta);

	// Translate from distance in rad
	void translate(float distance);

	// Move steppers from delta_steps
	void stepFrom(int32_t delta_step1, int32_t delta_step2);

	// Get position
	const position_t& getPosition() const;

	// Set position
	void setPosition(const position_t& position);

private:
	TMC2130Stepper _stepper_config1;
	TMC2130Stepper _stepper_config2;
	Stepper _stepper1, _stepper2;
	StepControl _controller;
	position_t _position;
};

// Return the angle between [-pi, pi)
float angleModulo(float angle);

#endif
