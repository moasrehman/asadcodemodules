from time import sleep
import RPi.GPIO as GPIO
GPIO.setmode(GPIO.BOARD)
GPIO.setup(13,GPIO.IN, pull_up_down = GPIO.PUD_DOWN)
GPIO.setup(23, GPIO.OUT)

def printFun(channel):
	print"Event occurred"
	GPIO.output(23,True)
	sleep(1)
	GPIO.output(23,False)

GPIO.add_event_detect(13, GPIO.FALLING, callback= printFun, bouncetime = 300)
#GPIO.add_event_detect(13, GPIO.RISING, callback= printFun, bouncetime = 300)
while True:
	GPIO.output(23,False)
	sleep(1)
