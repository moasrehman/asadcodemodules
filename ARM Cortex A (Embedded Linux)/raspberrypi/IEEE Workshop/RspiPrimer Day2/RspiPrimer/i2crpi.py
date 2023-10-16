#python 12c
from datetime import datetime

import smbus
import time

_REG_SECONDS = 0x00
_REG_MINUTES = 0x01
_REG_HOURS = 0x02
_REG_DAY = 0x03
_REG_DATE = 0x04
_REG_MONTH = 0x05
_REG_YEAR = 0x06
_REG_CONTROL = 0x07

addr=0x68
twi=1

def _bcd_to_int(bcd):
	"""Decode a 2x4bit BCD to an integer.
	"""
	out = 0
	for d in (bcd>>4, bcd):
		for p in (1,2,4,8):
			if d & 1:
				out += p
			d>>=1
		out *= 10
	return out/10

def _int_to_bcd(n):
	"""Encode a one or two digits number to the bcd
	"""
	bcd = 0
	for i in (n//10, n%10):
		for p in (8,4,2,1):
			if i >= p:
				bcd += 1
				i -= p
			bcd <<= 1
		return bcd >> 1

def _read(data):
	returndata=smbus.SMBus(twi).read_byte_data(addr,data)
	#print "addr=0x%x data = 0x%x %i returndata = 0x%x%i"%(self_addr, data,data,returnd_bcd_to_int(returndata))
	return returndata

sec =int(input("enter sec: "))
min =int(input("enter min: "))
hrs =int(input("enter hours: "))
day =int(input("enter days: "))
smbus.SMBus(twi).write_byte_data(addr, _REG_SECONDS, _int_to_bcd(sec))
smbus.SMBus(twi).write_byte_data(addr, _REG_MINUTES, _int_to_bcd(min))
smbus.SMBus(twi).write_byte_data(addr, _REG_HOURS, _int_to_bcd(hrs))
smbus.SMBus(twi).write_byte_data(addr, _REG_DAY, _int_to_bcd(day))
while True:
	print("Seconds", _bcd_to_int(_read(0x00)))
	print("Minutes", _bcd_to_int(_read(0x01)))
	print("Hours", _bcd_to_int(_read(0x02)))
	print("Day",_bcd_to_int(_read(0x03)))

	time.sleep(5)# 5 sec delay


