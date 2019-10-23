#ifndef ODOMETRY_H
#define ODOMETRY_H

#include "turn_and_go.h"
#include <Arduino.h>

void step_ratio_calibration(TurnAndGo& turn_and_go, float distance);
void wheel_perimeter_calibration(TurnAndGo& turn_and_go, float distance);
void center_distance_calibration(TurnAndGo& turn_and_go, uint16_t n_turn);

#endif
