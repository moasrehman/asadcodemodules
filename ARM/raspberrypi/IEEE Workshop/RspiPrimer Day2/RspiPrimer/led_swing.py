import RPi.GPIO as GPIO
from time import sleep
GPIO.setmode(GPIO.BOARD)
GPIO.setup(23,GPIO.OUT)
p = GPIO.PWM(23,50)
p.start(50.0)
dc = 0
dd = 0
try:
	while True: 
		dc = dc+10
		p.ChangeDutyCycle(dc)
		if (dc ==100):
			dd = 1
			while (dd == 1)
				dc = dc -10
				if (dc == 0):
					dd = 0
		sleep(0.25)
except:
	GPIO.cleanup()
