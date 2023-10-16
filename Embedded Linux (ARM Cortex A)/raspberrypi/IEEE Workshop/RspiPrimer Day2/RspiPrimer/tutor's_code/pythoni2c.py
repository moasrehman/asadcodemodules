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
    """Decode a 2x4bit BCD to a integer.
    """
    out = 0
    for d in (bcd >> 4, bcd):
        for p in (1, 2, 4 ,8):
            if d & 1:
                out += p
            d >>= 1
        out *= 10
    return out / 10
def _int_to_bcd(n):
    """Encode a one or two digits number to the BCD.
    """
    bcd = 0
    for i in (n // 10, n % 10):
        for p in (8, 4, 2, 1):
            if i >= p:
                bcd += 1
                i -= p
            bcd <<= 1
    return bcd >> 1


def _read(data):

        returndata = smbus.SMBus(twi).read_byte_data(addr, data)
        #print "addr = 0x%x data = 0x%x %i returndata = 0x%x %i " % (self._addr, data, data, returndata, _bcd_to_int(returndata))
        return returndata

sec=int(input("eneter sec: "))		
smbus.SMBus(twi).write_byte_data(addr,_REG_SECONDS,_int_to_bcd(sec))	
while True:
	
	print(_bcd_to_int(_read(0x00)))
	time.sleep(5) # delays for 5 seconds