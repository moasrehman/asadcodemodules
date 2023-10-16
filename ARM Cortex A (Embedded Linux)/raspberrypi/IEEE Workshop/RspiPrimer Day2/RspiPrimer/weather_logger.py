import os
import time
import urllib
import urllib2

os.system('sudo modprobe w1-gpio')
os.system('sudo modprobe w1-therm')

#base_dir = '/sys/bus/w1/devices/'
#device_folder = glob.glob(base_dir + '28*')[0]
#device_file = '/sys/bus/w1/devices/28-000007051b90/w1_slave'
device_file = '/sys/bus/w1/devices/28-000007057e9b/w1_slave'
#/sys/bus/w1/devices/28-000007053a72/w1_slave'
#/sys/bus/w1/devices/28-000007051b90

def read_temp_raw():
	f=open(device_file, 'r')
	lines=f.readlines()
	f.close()
	return lines

def read_temp():
	lines=read_temp_raw()
	while lines[0].strip()[-3:]!='YES':
		time.sleep(0.2)
		lines-read_temp_raw()
	equals_pos= lines[1].find('t=')
	if equals_pos!=-1:
		temp_string=lines[1][equals_pos+2:]
		temp_c=float(temp_string)/1000.0
		temp_f=temp_c*9.0/5.0+32.0
		return temp_c, temp_f

url = 'http://www.novy.space:9001'

#parameters to send
data = urllib.urlencode({'lat':'22.57','long':'88.36','temp':read_temp()})

#create a request
req = urllib2.Request (url, data)

#read and response
response = urllib2.urlopen(req)
print response
