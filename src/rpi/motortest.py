"""Set-up and execute the main loop"""
import RPi.GPIO as GPIO
import time

GPIO.setmode(GPIO.BCM)
GPIO.setwarnings(False)

#Right motor input A
GPIO.setup(18,GPIO.OUT)
#Right motor input B
GPIO.setup(23,GPIO.OUT)

print('In main loop')
while True:
    print('Rotating both motors in clockwise direction')
    GPIO.output(18,GPIO.HIGH)
    GPIO.output(23,GPIO.LOW)
    time.sleep(1)
    GPIO.output(18,GPIO.LOW)

    print('Rotating both motors in anticlockwise direction')
    GPIO.output(18,GPIO.LOW)
    GPIO.output(23,GPIO.HIGH)
    time.sleep(1)     
    GPIO.output(23,GPIO.LOW)

