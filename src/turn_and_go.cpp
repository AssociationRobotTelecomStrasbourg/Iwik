#include "turn_and_go.h"

TurnAndGo::TurnAndGo(const float maximum_speed, const float acceleration) :
_stepper_config1(EN1, DIR1, STEP1, CS1, SDI, SDO, SCK),
_stepper_config2(EN2, DIR2, STEP2, CS2, SDI, SDO, SCK),
_stepper1(STEP1, DIR1), _stepper2(STEP2, DIR2), _position({0., 0., 0.}),
_state(STOP) {
	// The delays between SPI calls seem to be important for consistent behaviour
	// Driver Enables are at 1 (3V3) by default, i.e disabled, you need to pull them low to enable the drivers.
	delay(5);
	// Initialize SPI, set current to 600mA, and activate stealthchop for both drivers
	// Both drivers need to be initialized even if only one is used
	_stepper_config1.begin();
	_stepper_config2.begin();
	delay(5);

	_stepper_config1.SilentStepStick2130(current);
	_stepper_config2.SilentStepStick2130(current);
	delay(5);

	_stepper_config1.interpolate(interpolate);
	_stepper_config2.interpolate(interpolate);
	delay(5);

	_stepper_config1.microsteps(microstep);
	_stepper_config2.microsteps(microstep);
	delay(5);

	// Configure max speed and acceleration
	setAcceleration(acceleration);
	setMaximumSpeed(maximum_speed);

	_stepper1.setInverseRotation(true);

	// Turning on the driver
	digitalWrite(EN1, LOW);
	digitalWrite(EN2, LOW);
}

void TurnAndGo::goTo(const float x, const float y) {
	float delta_x = x - _position.x;
	float delta_y = y - _position.y;

	_angle = angleModulo(atan2f(delta_y, delta_x) - _position.theta);
	_distance = sqrtf(delta_x*delta_x + delta_y*delta_y);
}

void TurnAndGo::rotateTo(const float theta) {
	_angle = theta-_position.theta;
	_distance = 0;
}

void TurnAndGo::rotateFrom(const float delta_theta) {
	int32_t step = delta_theta * step_per_turn * center_distance / 2 / wheel_perimeter;

	stepFrom(-step, step);
	_state = ROTATE;
}

void TurnAndGo::translateFrom(const float distance) {
	int32_t step = distance * step_per_turn / wheel_perimeter;

	stepFrom(step, step);
	_state = TRANSLATE;
}

void TurnAndGo::stepFrom(const int32_t delta_step1, const int32_t delta_step2) {
	_stepper1.setTargetRel(delta_step1);
	_stepper2.setTargetRel(delta_step2*step_ratio);
	_controller.moveAsync(_stepper1, _stepper2);
}

void TurnAndGo::stop() {
	_controller.stopAsync();
	_state = BRAKE;
}

state_t TurnAndGo::run() {
	// State machine
	switch(_state) {
		case STOP:
			if (_angle != 0) {
				rotateFrom(_angle);
			}
			else if (_distance != 0) {
				translateFrom(_distance);
			}
			break;
		case ROTATE:
			if (!_controller.isRunning()) {
				_angle = 0;
				translateFrom(_distance);
				_state = TRANSLATE;
			}
			break;
		case TRANSLATE:
			if (!_controller.isRunning()) {
				_distance = 0;
				_state = STOP;
			}
			break;
		case BRAKE:
			if (!_controller.isRunning()) {
				_angle = 0;
				_distance = 0;
				_state = STOP;
			}
			break;
		default:
			break;
	}

	// Odometry
	_d_step1 = -_step1;
	_d_step2 = -_step2;
	_step1 = _stepper1.getPosition();
	_step2 = _stepper2.getPosition()/step_ratio;
	_d_step1 += _step1;
	_d_step2 += _step2;

	_position.x += (_d_step1+_d_step2)/2*cos(_position.theta)/(float)step_per_turn*wheel_perimeter;
	_position.y += (_d_step1+_d_step2)/2*sin(_position.theta)/(float)step_per_turn*wheel_perimeter;
	_position.theta += (-_d_step1+_d_step2)/(float)step_per_turn/center_distance*wheel_perimeter;
	
	return _state;
}

const position_t* TurnAndGo::getPosition() const {
	return &_position;
}

const float TurnAndGo::getMaximumSpeed() const {
	return _maximum_speed;
}

const float TurnAndGo::getAcceleration() const {
	return _acceleration;
}

void TurnAndGo::setPosition(const position_t* position) {
	_position = *position;
}

void TurnAndGo::setMaximumSpeed(const float maximum_speed) {
	int32_t step_maximum_speed = maximum_speed/wheel_perimeter*step_per_turn;
	_stepper1.setMaxSpeed(step_maximum_speed);
	_stepper2.setMaxSpeed(step_maximum_speed*step_ratio);
	_maximum_speed = maximum_speed;
}

void TurnAndGo::setAcceleration(const float acceleration) {
	uint32_t step_acceleration = acceleration/wheel_perimeter*step_per_turn;
	_stepper1.setAcceleration(step_acceleration);
	_stepper2.setAcceleration(step_acceleration*step_ratio);
	_acceleration = acceleration;
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
