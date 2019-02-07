# Reference: http://www.movable-type.co.uk/scripts/latlong.html
# Translated from the Javascript into Python
import math

# Radius of the Earth is approximately 6,371Km
radius = 6371000

def calcDistance(startLat, startLong, endLat, endLong):
    startPhi = math.radians(startLat)
    endPhi = math.radians(endLat)
    deltaLat = math.radians((endLat - startLat))
    detalLong = math .radians((endLong - startLong))

    a = math.sin(deltaLat / 2) * math.sin(deltaLat / 2) + math.cos(startPhi) * math.cos(endPhi) * math.sin(detalLong / 2) * math.sin(detalLong / 2)
    c = 2 * math.atan2(math.sqrt(a), math.sqrt(1-a))
    dist = radius * c
    return dist

def calcBearing(startLat, startLong, endLat, endLong):
    y = math.sin(math.radians(endLong)-math.radians(startLong)) * math.cos(math.radians(endLat))
    x = math.cos(math.radians(startLat))*math.sin(math.radians(endLat)) - math.sin(math.radians(startLat))*math.cos(math.radians(endLat))*math.cos(math.radians(endLong)-math.radians(startLong))
    bearing = math.degrees(math.atan2(y, x))
    if bearing < 0:
        bearing = 360 + bearing
    return bearing

def calcMidPoint(startLat, startLong, endLat, endLong):
    ret = []
    bX = math.cos(math.radians(endLat)) * math.cos(math.radians(endLong)-math.radians(startLong))
    bY = math.cos(math.radians(endLat)) * math.sin(math.radians(endLong)-math.radians(startLong))
    midLat = math.degrees(math.atan2(math.sin(math.radians(startLat)) + math.sin(math.radians(endLat)), math.sqrt( (math.cos(math.radians(startLat))+bX)*(math.cos(math.radians(startLat))+bX) + bY*bY ) ))
    midLong = math.degrees(math.radians(startLong) + math.atan2(bY, math.cos(math.radians(startLat)) + bX))
    ret.append(midLat)
    ret.append(midLong)
    return ret

def calcDestination(startLat, startLong, bearing, distance):
    ret = []
    endLat = math.degrees(math.asin( math.sin(math.radians(startLat))*math.cos(distance/radius) + math.cos(math.radians(startLat))*math.sin(distance/radius)*math.cos(math.radians(bearing))))
    endLong = startLong + math.atan2(math.sin(math.radians(bearing))*math.sin(distance/radius)*math.cos(math.radians(startLat)), math.cos(distance/radius)-math.sin(math.radians(startLat))*math.sin(math.radians(endLat)))
    ret.append(endLat)
    ret.append(endLong)
    return ret

print('Distance={0} metres'.format(calcDistance(-33.864937, 151.210059, -33.720171, 151.027125)))
print('Bearing={0} degrees (mag)'.format(calcBearing(-33.864937, 151.210059, -33.720171, 151.027125)))
print('Midpoint={0}'.format(calcMidPoint(-33.864937, 151.210059, -33.720171, 151.027125)))
print('Destination={0}'.format(calcDestination(-33.864937, 151.210059, calcBearing(-33.864937, 151.210059, -33.720171, 151.027125), calcDistance(-33.864937, 151.210059, -33.720171, 151.027125))))

