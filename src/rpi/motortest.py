"""Set-up and execute the main loop"""
import RPi.GPIO as GPIO
import time

GPIO.setmode(GPIO.BCM)
GPIO.setwarnings(False)

#Right motor input A
GPIO.setup(8,GPIO.OUT)
#Right motor input B
GPIO.setup(7,GPIO.OUT)

while True:
    print('Rotating motor forward direction')
    GPIO.output(8,GPIO.HIGH)
    GPIO.output(7,GPIO.LOW)
    time.sleep(2)
    GPIO.output(8,GPIO.LOW)
    time.sleep(1)

    print('Rotating motor reverse direction')
    GPIO.output(8,GPIO.LOW)
    GPIO.output(7,GPIO.HIGH)
    time.sleep(2)     
    GPIO.output(7,GPIO.LOW)
    time.sleep(1)

