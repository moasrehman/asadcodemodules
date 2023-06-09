from time import sleep
import RPi.GPIO as GPIO
GPIO.setmode(GPIO.BOARD)
GPIO.setup(13,GPIO.IN, pull_up_down = GPIO.PUD_DOWN)
GPIO.setup(16,GPIO.OUT)

try:

        while(1):
                if(GPIO.input(13)==1):
                        print"key pressed"
			GPIO.output(16, True)
		        sleep(2)
		else:
			print("waiting for key")
			GPIO.output(16, False)

except:
    pass
GPIO.cleanup()
