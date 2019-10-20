#ifndef TURN_AND_GO_H
#define TURN_AND_GO_H

#include <TeensyStep.h>

// Distance are in mm
const float wheel_perimeter = 236;
const float center_distance = 195;

struct position_t {
	float x, y, theta;
};

class TurnAndGo {
public:
	TurnAndGo(Stepper& stepper1, Stepper& stepper2, position_t& position);

	// Go to (x,y) in mm
	void goTo(float x, float y);

	// Rotate from delta_theta in rad
	void rotateFrom(float delta_theta);

	// Rotate to theta in rad
	void rotateTo(float theta);

	// Translate from distance in rad
	void translate(float distance);

private:
	Stepper& _stepper1, _stepper2;
	StepControl _controller;
	position_t _position;
};

// Return the angle between [-pi, pi)
float angleModulo(float angle);

#endif
