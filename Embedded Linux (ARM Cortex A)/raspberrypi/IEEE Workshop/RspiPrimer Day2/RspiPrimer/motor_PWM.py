import RPi.GPIO as GPIO
from time import sleep
GPIO.setmode(GPIO.BOARD)
GPIO.setup(23,GPIO.OUT)
GPIO.setup(11,GPIO.OUT)
GPIO.output(11,True)
GPIO.output(23,False)
p = GPIO.PWM(23,50)
p.start(0)
try:
	while (1):
		p.ChangeDutyCycle(1.0)
		sleep(1)
	        p.ChangeDutyCycle(10.0)
		sleep(1)
	        p.ChangeDutyCycle(20.0)
	        sleep(1)
        	p.ChangeDutyCycle(40.0)
	        sleep(1)
       		p.ChangeDutyCycle(60.0)
	        sleep(1)
	        p.ChangeDutyCycle(80.0)
	        sleep(1)
	        p.ChangeDutyCycle(100.0)
      		sleep(1)

except KeyboardInterrupt:
    pass
GPIO.cleanup()
