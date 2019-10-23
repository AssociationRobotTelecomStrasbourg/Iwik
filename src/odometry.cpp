#include "odometry.h"

void step_ratio_calibration(TurnAndGo& turn_and_go, float distance) {
	turn_and_go.translateFrom(distance);
	turn_and_go.rotateFrom(M_PI);
	turn_and_go.translateFrom(distance);
	turn_and_go.rotateFrom(-M_PI);
}

void wheel_perimeter_calibration(TurnAndGo& turn_and_go, float distance) {
	turn_and_go.translateFrom(distance);
}

void center_distance_calibration(TurnAndGo& turn_and_go, uint16_t n_turn) {
	turn_and_go.rotateFrom(M_PI * n_turn);
}
