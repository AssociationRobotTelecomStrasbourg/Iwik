#include <Arduino.h>
#include "TMC2130Stepper.h"
#include "protoPins.h"

void setup() {
  pinMode(EN1, OUTPUT);
  pinMode(EN2, OUTPUT);

  digitalWrite(EN1, HIGH); //Turning off the output stage by default for safety
  digitalWrite(EN2, HIGH);
}

void loop() {
  // put your main code here, to run repeatedly:
}
