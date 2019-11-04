# Iwik
Sources for a prototype differential drive robot using two stepper motors driven by TMC2130 drivers by Trinamic

## Formation
- [ ] Odometry calibration
- [ ] Trace forms
- [ ] Lidar distance
- [ ] Follow hand
- [ ] Avoid obstacles

## Movement
### TMC2130Stepper
- [ ] Explore coniguration

### TurnAndGo
- [ ] Add backward option
- [ ] Add enable option
- [x] Add step_ratio odometry setting
- [ ] Add async function

#### Odometry calibration
1. Calibrate `step_ratio`
   1. Use `step_ratio_calibration()` in `setup()`
   2. Note the deviation
   3. Update `step_ratio`
	   - Anti-clockwise -> decrease
	   - Clockwise -> increase
2. Calibrate `wheel_perimeter`
   1. Use `wheel_perimeter_calibration()` in `loop()` followed by `delay(1000)`
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
   1. Use `center_distance_calibration()` in `setup()`
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
