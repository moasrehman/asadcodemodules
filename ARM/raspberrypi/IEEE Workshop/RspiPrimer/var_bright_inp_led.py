from time import sleep
import RPi.GPIO as GPIO
GPIO.setmode(GPIO.BOARD)
GPIO.setup(13,GPIO.IN, pull_up_down = GPIO.PUD_DOWN)
GPIO.setup(23,GPIO.OUT)
p=GPIO.PWM(23,20)
p.start(50.0)
try:
	var = 0
        while True:
		#p.ChangeDutyCycle(50.0)
		#GPIO.output(23, True)
                '''if(GPIO.input(13)==1):
                        #print"key pressed"
			#GPIO.output(23, True)
			p.ChangeDutyCycle(a)
			GPIO.output(23, True)		 
			sleep(1)'''
		var = var + 1
		p.ChangeDutyCycle(var)
	        GPIO.output(23, True)
        	sleep(1)
		if (var>=99):
			while(var>=0):
                       		var = var - 1
				p.ChangeDutyCycle(var)
		                GPIO.output(23, True)
        		        sleep(1)

			'''p.ChangeDutyCycle(80.0)
                        GPIO.output(23, True)
			sleep(2)
			p.ChangeDutyCycle(70.0)
                        GPIO.output(23, True)
                        sleep(2)
			p.ChangeDutyCycle(60.0)
                        GPIO.output(23, True)
                        sleep(2)
			p.ChangeDutyCycle(50.0)
                        GPIO.output(23, True)
                        sleep(2)
		else:
			print("waiting for key")
			#GPIO.output(23, True)
			p.ChangeDutyCycle(20.0)
			GPIO.output(23, True)
			#sleep(2)
                        '''
except:
    pass
GPIO.cleanup()
