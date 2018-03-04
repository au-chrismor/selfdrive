import RPi.GPIO as GPIO
import time
def getInput(prompt):
	cmd = input(prompt + '> ')
	return cmd

def motorContext():
	state = True
	while state:
		command = getInput('motor')
		if command == 'help':
			print('Available commands:')
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

def sensorContext():
	state = True
	while state:
		command = getInput('sensor')
		if command == 'help':
			print('Available commands:')
			print('exit')
		elif command == 'exit':
			state = False

def trainContext():
	state = True
	while state:
		command = getInput('train')
		if command == 'help':
			print('Available commands:')
			print('exit')
		elif command == 'exit':
			state = False

def driveContext():
	state = True
	while state:
		command = getInput('drive')
		if command == 'help':
			print('Available commands:')
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
	command = getInput('')
	if command == 'help':
		print('Available contexts:')
		print('motor - Select the \'Motor\' context')
		print('sensor - Select the \'Sensor\' context')
		print('train - Select the \'Training\' context for camera module')
		print('exit')
	elif command == 'exit':
		state = False
	elif command == 'motor':
		motorContext()
	elif command == 'sensor':
		sensorContext()


