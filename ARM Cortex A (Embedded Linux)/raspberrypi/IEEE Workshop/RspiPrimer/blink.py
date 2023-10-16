from time import sleep
import RPi.GPIO as GPIO
GPIO.setmode(GPIO.BOARD)
GPIO.setup(16,GPIO.OUT)
GPIO.output(16,True)

try:
	while True:
		GPIO.output(16, False)
		sleep(2)
		GPIO.output(16, True)
		sleep(2)

except KeyboardInterrupt :
	pass
GPIO.cleanup()


