"""Set-up and execute the main loop"""
import RPi.GPIO as GPIO
import time

# Configure the basic params
GPIO.setwarnings(False)
GPIO.setmode(GPIO.BOARD)

# Right sensor
GPIO.setup(3, GPIO.IN)

# Left sensor
GPIO.setup(16, GPIO.IN, pull_up_down=GPIO.PUD_UP)

# Main loop
while True:
    r = GPIO.input(3)
    l = GPIO.input(16)

    if r == 0:
        print('Obstacle detected on right')
        time.sleep(0.1)
    elif l == 0:
        print('Obstacle detected on left')
        time.sleep(0.1)
