#include "turn_and_go.h"

TurnAndGo::TurnAndGo() :
_stepper_config1(EN1, DIR1, STEP1, CS1, SDI, SDO, SCK),
_stepper_config2(EN2, DIR2, STEP2, CS2, SDI, SDO, SCK),
_stepper1(STEP1, DIR1), _stepper2(STEP2, DIR2), _position({0., 0., 0.}) {
	// The delays between SPI calls seem to be important for consistent behaviour
	// Driver Enables are at 1 (3V3) by default, i.e disabled, you need to pull them low to enable the drivers.
	delay(10);
	// Initialize SPI, set current to 600mA, and activate stealthchop for both drivers
	// Both drivers need to be initialized even if only one is used
	_stepper_config1.begin();
	_stepper_config2.begin();
	delay(10);

	_stepper_config1.SilentStepStick2130(600);
	_stepper_config2.SilentStepStick2130(600);
	delay(10);

	_stepper_config1.stealthChop(1);
	_stepper_config2.stealthChop(1);
	delay(10);

	// Configure max speed and acceleration
	_stepper1
		.setMaxSpeed(maximum_speed)
		.setAcceleration(acceleration)
		.setInverseRotation(true);

	_stepper2
		.setMaxSpeed(maximum_speed)
		.setAcceleration(acceleration);

	// Turning on the driver
	digitalWrite(EN1, LOW);
	digitalWrite(EN2, LOW);

}

void TurnAndGo::goTo(float x, float y) {
	float delta_x = x - _position.x;
	float delta_y = y - _position.y;

	float distance = sqrtf(delta_x*delta_x + delta_y*delta_y);
	float delta_theta = angleModulo(atan2f(delta_y, delta_x) - _position.theta);

	rotateFrom(delta_theta);

	translate(distance);
}

void TurnAndGo::rotateFrom(float delta_theta) {
	float step = delta_theta * 200 * 255 * center_distance / 2 / wheel_perimeter;

	_stepper1.setTargetRel(-step);
	_stepper2.setTargetRel(step);
	_controller.move(_stepper1, _stepper2);

	_position.theta += delta_theta;
}

void TurnAndGo::rotateTo(float theta) {
	rotateFrom(theta-_position.theta);
}

void TurnAndGo::translate(float distance) {
	float step = distance * 200 * 255 / wheel_perimeter;

	_stepper1.setTargetRel(step);
	_stepper2.setTargetRel(step);
	_controller.move(_stepper1, _stepper2);

	_position.x += distance * cos(_position.theta);
	_position.y += distance * sin(_position.theta);
}

const position_t& TurnAndGo::getPosition() const {
	return _position;
}

void TurnAndGo::setPosition(const position_t& position) {
	_position = position;
}

float angleModulo(float angle) {
	angle = fmodf(angle, 2 * M_PI);
	if (angle > M_PI) {
		return angle - 2 * M_PI;
	}
	if (angle < -M_PI) {
		return angle + 2 * M_PI;
	}
	return angle;
}
