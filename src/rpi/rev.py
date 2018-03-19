"""Set-up and execute the main loop"""
import RPi.GPIO as GPIO
import time

GPIO.setmode(GPIO.BCM)
GPIO.setwarnings(False)

#Right motor input A
GPIO.setup(18,GPIO.OUT)
#Right motor input B
GPIO.setup(23,GPIO.OUT)

GPIO.output(18,GPIO.LOW)
GPIO.output(23,GPIO.HIGH)

