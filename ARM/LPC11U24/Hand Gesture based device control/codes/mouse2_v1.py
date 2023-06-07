import serial,glob
import pyautogui,pytweening
import os
x_max,y_max=pyautogui.size()
x,y=x_max/2,y_max/2
i=0
pyautogui.FAILSAFE = False
#open 
def scan():
	return glob.glob('/dev/ttyACM*')
    
def intial(x,y):
    print x,y
    pyautogui.moveTo(x,y,0)

def move_mouse(t):
    if t == 'N':
        pyautogui.moveRel(None,-10,0,pyautogui.easeInElastic)
	#pyautogui.moveRel(None,-10,0)
    elif t == 'E':
        pyautogui.moveRel(10,None,0,pyautogui.easeInElastic)
        #pyautogui.moveRel(10,None,0)
    elif t == 'S':
        pyautogui.moveRel(None,10,0,pyautogui.easeInElastic)
        #pyautogui.moveRel(None,10,0)
    elif t=='W':
        pyautogui.moveRel(-10,None,0,pyautogui.easeInElastic)
        #pyautogui.moveRel(-10,None,0)
    elif t=='4':   #left click
	pyautogui.click(button='left')	
    elif t=='6':   #right click
	pyautogui.click(button='right')
	

def media_cntrl(t):
	if t == 'u':
		os.system("totem --play-pause")
	elif t=='h':
		os.system("totem --volume-up")
	elif t=='l':
		os.system("totem --volume-down")
	elif t=='x':
		os.system("totem --fullscreen")
	#elif t=='x':
	#	os.system("totem --seek-fwd")
	#elif t=='v':
	#	os.system("totem --seek-bwd")
	#elif t=='n':
	#	os.system("totem --next")
	#elif t=='r':
	#	os.system("totem --previous")
print('press Ctrl-c to quit')

lt=scan()

#for i in lt:
	
#if('/dev/ttyACM0'== lt[i]):
#		st=lt[i]
#	else:
#		print 'port is not detected'
print lt

sr=serial.Serial(lt[0],38400,timeout=0)

while i == 0:
	#intial(x,y)
	t=sr.read(1)
	move_mouse(t)  
	media_cntrl(t)
