import math

declination = 0

def magHeading(x, y, z):
    heading = math.atan2(y, x) + declination
    # fix up sign so we don't go out of range
    if heading > (2 * math.pi):
        heading = heading - (2 * math.pi)
    
    if heading < 0:
        heading = heading + (2 * math.pi)

    # convert it to an angle
    angle = int(math.degrees(heading))

    return angle

    