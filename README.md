# Iwik
Sources for a prototype differential drive robot using two stepper motors driven by TMC2130 drivers by Trinamic

## Mouvement
- [ ] Explore TMC2130Stepper configuration
  - [ ] Micro step configuration
  - [ ] Set current
  - [ ] const steps/turn
  - [ ] overload goto : goto(x,y,speed) and goto(x,y,speed,acceleration)
  - [ ] goto constructor : needs to be able to specify speed and acceleration in mm/s, and mm/s^2

## Detection
- [ ] Lidar
  - [ ] Find library
  - [ ] Test it

## Communication
- [ ] ESP01
