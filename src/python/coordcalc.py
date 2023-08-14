# Reference: http://www.movable-type.co.uk/scripts/latlong.html
# Translated from the Javascript into Python
import math

# Radius of the Earth is approximately 6,371Km
radius = 6371000

def calc_distance(start_lat, start_long, end_lat, end_long):
    start_phi = math.radians(start_lat)
    end_phi = math.radians(end_lat)
    delta_lat = math.radians((end_lat - start_lat))
    delta_long = math .radians((end_long - start_long))

    a = math.sin(delta_lat / 2) * math.sin(delta_lat / 2) + math.cos(start_phi) * math.cos(end_phi) * math.sin(delta_long / 2) * math.sin(delta_long / 2)
    c = 2 * math.atan2(math.sqrt(a), math.sqrt(1-a))
    dist = radius * c
    return dist

def calc_bearing(start_lat, start_long, end_lat, end_long):
    y = math.sin(math.radians(end_long)-math.radians(start_long)) * math.cos(math.radians(end_lat))
    x = math.cos(math.radians(start_lat))*math.sin(math.radians(end_lat)) - math.sin(math.radians(start_lat))*math.cos(math.radians(end_lat))*math.cos(math.radians(end_long)-math.radians(start_long))
    bearing = math.degrees(math.atan2(y, x))
    if bearing < 0:
        bearing = 360 + bearing
    return bearing

def calc_midpoint(start_lat, start_long, end_lat, end_long):
    ret = []
    b_x = math.cos(math.radians(end_lat)) * math.cos(math.radians(end_long)-math.radians(start_long))
    b_y = math.cos(math.radians(end_lat)) * math.sin(math.radians(end_long)-math.radians(start_long))
    mid_lat = math.degrees(math.atan2(math.sin(math.radians(start_lat)) + math.sin(math.radians(end_lat)), math.sqrt( (math.cos(math.radians(start_lat))+b_x)*(math.cos(math.radians(start_lat))+b_x) + b_y*b_y ) ))
    mid_long = math.degrees(math.radians(start_long) + math.atan2(b_y, math.cos(math.radians(start_lat)) + b_x))
    ret.append(mid_lat)
    ret.append(mid_long)
    return ret

def calc_destination(start_lat, start_long, bearing, distance):
    ret = []
    end_lat = math.degrees(math.asin( math.sin(math.radians(start_lat))*math.cos(distance/radius) + math.cos(math.radians(start_lat))*math.sin(distance/radius)*math.cos(math.radians(bearing))))
    end_long = start_long + math.atan2(math.sin(math.radians(bearing))*math.sin(distance/radius)*math.cos(math.radians(start_lat)), math.cos(distance/radius)-math.sin(math.radians(start_lat))*math.sin(math.radians(end_lat)))
    ret.append(end_lat)
    ret.append(end_long)
    return ret

print('Distance={0} metres'.format(calc_distance(-33.864937, 151.210059, -33.720171, 151.027125)))
print('Bearing={0} degrees (mag)'.format(calc_bearing(-33.864937, 151.210059, -33.720171, 151.027125)))
print('Midpoint={0}'.format(calc_midpoint(-33.864937, 151.210059, -33.720171, 151.027125)))
print('Destination={0}'.format(calc_destination(-33.864937, 151.210059, calc_bearing(-33.864937, 151.210059, -33.720171, 151.027125), calc_distance(-33.864937, 151.210059, -33.720171, 151.027125))))

