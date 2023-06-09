import RPi.GPIO as GPIO
from time import sleep
GPIO.setmode(GPIO.BOARD)
GPIO.setup(23,GPIO.OUT)
GPIO.setup(11,GPIO.OUT)
GPIO.output(11,True)
GPIO.output(23,True)

try:
	while True:
		GPIO.output(11,True)
                GPIO.output(23,False)
		sleep(3)
		GPIO.output(11,False)
                GPIO.output(23,True)
                sleep(3)


except	KeyboardInterrupt :
    pass
GPIO.cleanup()

	
