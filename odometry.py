from numpy import arctan2, pi

def angle_error(center_distance, distance_error):
    return arctan2(distance_error, center_distance)

def new_wheel_perimeter(old, distance_moved, distance_wanted):
    return old * distance_moved / distance_wanted

def new_center_distance(old, distance_error, angle_wanted):
    return old * angle_wanted / (angle_wanted + angle_error(old, distance_error))

wheel_perimeter = 21
distance_wanted = 1000
distance_moved = 995

print('New wheel perimeter: ' + str(new_wheel_perimeter(wheel_perimeter, distance_moved, distance_wanted)))

center_distance = 190
distance_error = -10
angle_wanted = 2*pi
print('New center distance: ' + str(new_center_distance(center_distance, distance_error, angle_wanted)))
