#include "board.h"

float batteryVoltage() {
	float sum_voltage = 0;
	for (int i = 0; i < 10; i++)
		sum_voltage += analogRead(BATT_LVL);
	return sum_voltage/10./0.122/1023.*3.3;
}
