import RPi.GPIO as GPIO
from time import sleep
GPIO.setmode(GPIO.BOARD)
GPIO.setup(23,GPIO.OUT)
p = GPIO.PWM(23,50)
p.start(50.0)
dc = 0
try:
	while True: 
		dc = dc+10
		p.ChangeDutyCycle(dc)
		if (dc ==100):
			dc = 0
		sleep(1)
except:
	GPIO.cleanup()
