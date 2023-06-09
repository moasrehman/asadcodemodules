from time import sleep
import RPi.GPIO as GPIO
GPIO.setmode(GPIO.BOARD)
GPIO.setup(13,GPIO.IN, pull_up_down = GPIO.PUD_DOWN)
try:

	while(1):
		if(GPIO.input(13)==1):
			print"key pressed"

	sleep(2)

except:
    pass
GPIO.cleanup()
