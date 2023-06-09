from time import sleep
import RPi.GPIO as GPIO
GPIO.setmode(GPIO.BOARD)
GPIO.setup(13,GPIO.IN,pull_up_down=GPIO.PUD_UP)

GPIO.setup(23,GPIO.OUT)
GPIO.output(23,1)
p=GPIO.PWM(23,50)
p.start(25.0)																																-	


def togglefun():
	print'event detected'
	p.stop()
	GPIO.output(23,1)
	sleep(2)
	GPIO.output(23,0)
	sleep(2)	
	p.start(25.0)

GPIO.add_event_detect(13,GPIO.FALLING,callback=togglefun,bouncetime=300)

try:
	while True:
		dc=input("what is the DutyCycle?")
		p.changeDutyCycle(dc)
		
		
except KeyboardInterrupt:
	GPIO.cleanup()