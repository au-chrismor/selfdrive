import RPi.GPIO as GPIO
import time

MSG_AVAILABLE_COMMANDS = 'Available commands:'
MSG_AVAILABLE_CONTEXTS = 'Available contexts:'


def get_input(prompt):
	cmd = input(prompt + '> ')
	return cmd


def motor_context():
	state = True
	while state:
		command = get_input('motor')
		if command == 'help':
			print(MSG_AVAILABLE_COMMANDS)
			print('fwd - Run motor forward')
			print('rev - Run motor backwards')
			print('stop - Stop motor')
			print('exit')
		elif command == 'fwd':
			GPIO.output(8, GPIO.HIGH)
			GPIO.output(7, GPIO.LOW)
		elif command == 'rev':
			GPIO.output(8, GPIO.LOW)
			GPIO.output(7, GPIO.HIGH)
		elif command == 'stop':
			GPIO.output(8, GPIO.LOW)
			GPIO.output(7, GPIO.LOW)
		elif command == 'exit':
			state = False


def sensor_context():
	state = True
	while state:
		command = get_input('sensor')
		if command == 'help':
			print(MSG_AVAILABLE_COMMANDS)
			print('exit')
		elif command == 'exit':
			state = False


def train_context():
	state = True
	while state:
		command = get_input('train')
		if command == 'help':
			print(MSG_AVAILABLE_COMMANDS)
			print('exit')
		elif command == 'exit':
			state = False


def drive_context():
	state = True
	while state:
		command = get_input('drive')
		if command == 'help':
			print(MSG_AVAILABLE_COMMANDS)
			print('exit')
		elif command == 'exit':
			state = False

state = True
print()
print('Diagnostic Shell')
GPIO.setmode(GPIO.BCM)
GPIO.setwarnings(False)
# Motor A
GPIO.setup(8, GPIO.OUT)
# Motor B
GPIO.setup(7, GPIO.OUT)
GPIO.output(8, GPIO.LOW)
GPIO.output(7, GPIO.LOW)


while state:
	command = get_input('')
	if command == 'help':
		print(MSG_AVAILABLE_CONTEXTS)
		print('motor - Select the \'Motor\' context')
		print('sensor - Select the \'Sensor\' context')
		print('train - Select the \'Training\' context for camera module')
		print('exit')
	elif command == 'exit':
		state = False
	elif command == 'motor':
		motor_context()
	elif command == 'sensor':
		sensor_context()


