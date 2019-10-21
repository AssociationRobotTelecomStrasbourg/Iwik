# Iwik
Sources for a prototype differential drive robot using two stepper motors driven by TMC2130 drivers by Trinamic

## Mouvement
- [ ] Explore TMC2130Stepper configuration
  - [x] Add constant stepper settings
  - [x] const steps/turn
  - [x] overload goto : goto(x,y,speed) and goto(x,y,speed,acceleration)
  - [x] TurnAndGo constructor : needs to be able to specify speed and acceleration in mm/s, and mm/s^2
  - [ ] Add backward option

## Detection
- [ ] Lidar
  - [ ] Find library
  - [ ] Test it

## Communication
- [ ] ESP01
