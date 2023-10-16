import serial

port = serial.Serial("/dev/ttyAMA0",baudrate=9600,timeout=3.0)

while True:
	port.write("\r\n Say something")
	rcv = port.read(10)
	port.write("\r\n You sent:"+repr(rcv))
