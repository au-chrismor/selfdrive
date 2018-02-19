"""Set-up and execute the main loop"""
import RPi.GPIO as GPIO
import time

GPIO.setmode(GPIO.BOARD)
GPIO.setwarnings(False)

#Left motor input A
GPIO.setup(5,GPIO.OUT)
#Left motor input B
GPIO.setup(7,GPIO.OUT)
#Right motor input A
GPIO.setup(11,GPIO.OUT)
#Right motor input B
GPIO.setup(13,GPIO.OUT

while True:
    print('Rotating both motors in clockwise direction')
    GPIO.output(5,1)
    GPIO.output(7,0)
    GPIO.output(11,1)
    GPIO.output(13,0)
    time.sleep(1)

    print('Rotating both motors in anticlockwise direction')
    GPIO.output(5,0)
    GPIO.output(7,1)
    GPIO.output(11,0)
    GPIO.output(13,1)
    time.sleep(1)     
