# Iwik
Sources for a prototype differential drive robot using two stepper motors driven by TMC2130 drivers by Trinamic

## Movement
### TMC2130Stepper
- [ ] Explore coniguration

### TurnAndGo
- [ ] Add backward option
- [ ] Add enable option
- [ ] Add wheel_ratio odometry setting

#### Odometry calibration
1. Translate from a distance
2. Update the wheel perimeter with
```
new_wheel_perimeter = old_wheel_perimeter *
distance_moved / distance_wanted
```
3. Update the center distance with
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
