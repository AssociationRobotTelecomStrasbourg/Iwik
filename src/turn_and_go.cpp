#include "turn_and_go.h"

TurnAndGo::TurnAndGo(Stepper& stepper1, Stepper& stepper2, position_t& position) :
	_stepper1(stepper1), _stepper2(stepper2), _position(position) {

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
