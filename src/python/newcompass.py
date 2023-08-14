#! /usr/bin/python3
#
import smbus
from time import sleep
import math
Register_A = 0x00
Register_B = 0x01
Register_mode = 0x02

X_axis_H = 0x03
Z_axis_H = 0x05
Y_axis_H = 0x07
declination = -0.00669

def magnetometer_init():
	# Write to the configuration register A
	bus.write_byte_data(Device_Address, Register_A, 0x70)
	# Configuration Register B gain
	bus.write_byte_data(Device_Address, Register_B, 0xa0)
	# Select mode
	bus.write_byte_data(Device_Address, Register_mode, 0)

def read_raw_data(addr):
	# Read the raw 16-bit value
	high = bus.read_byte_data(Device_Address, addr)
	low = bus.read_byte_data(Device_Address, addr + 1)

	value = ((high << 8) | low)

	# To get signed value from module
	if value > 32768:
		value = value - 65536
	return value

bus = smbus.SMBus(2)
Device_Address = 0x1e

magnetometer_init()

print('Reading\tHeading\tAngle')
while True:
	# Read the raw data
	x = read_raw_data(X_axis_H)
	y = read_raw_data(Y_axis_H)
	z = read_raw_data(Z_axis_H)

	heading = math.atan2(y, x) + declination
	if heading > 2 * math.pi:
		heading = heading - 2 * math.pi
	if heading < 0:
		heading = heading + 2 * math.pi
	heading_angle = int(math.degrees(heading))

	print(heading_angle)
	sleep(1)



