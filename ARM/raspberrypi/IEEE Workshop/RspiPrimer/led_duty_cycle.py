import RPi.GPIO as GPIO

GPIO.setmode(GPIO.BOARD)
GPIO.setup(23,GPIO.OUT)
p = GPIO.PWM(23,50)
p.start(50.0)
try:
	while True: 
		dc = input("enter your brightness:")
		p.ChangeDutyCycle(dc)
except:
	GPIO.cleanup()
