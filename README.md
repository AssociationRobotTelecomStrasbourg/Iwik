# Iwik
Sources for a prototype differential drive robot using two stepper motors driven by TMC2130 drivers by Trinamic

## Movement
### TMC2130Stepper
- [ ] Explore coniguration

### TurnAndGo
- [ ] Add backward option
- [ ] Add enable option
- [x] Add step_ratio odometry setting

#### Odometry calibration
1. Calibrate `step_ratio`
   1. Translate from a distance
   2. Note the deviation
   3. Update `step_ratio`
	   - Left -> decrease
	   - Right -> increase
2. Calibrate `wheel_perimeter`
   1. Translate from a distance
   2. Note the deviation
   3. Update `wheel_perimeter`
	   - Too short -> decrease
	   - Too far -> increase
	   - Or use the equation
```
new_wheel_perimeter = old_wheel_perimeter *
distance_moved / distance_wanted
```
3. Calibrate `center_distance`
   1. Rotate from
   2. Note the deviation
   3. Update `wheel_perimeter`
	   - Too short -> decrease
	   - Too far -> increase
	   - Or use the equation
```
new_center_distance = old_center_distance *
angle_wanted / angle_moved
```

## Detection
- [ ] Lidar
  - [ ] Find library
  - [ ] Test it

## Communication
- [ ] ESP01

## Installation
1. Clone the repository
2. Initialize submodule, `git submodule update --init`
