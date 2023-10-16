#project upload

#import modules
import urllib
import urllib2

#url to send data
url = 'http://www.novy.space:9001'

#parameters to send
data = urllib.urlencode({'lat':'22.57','long':'88.36','temp':'40'})

#create a request
req = urllib2.Request (url, data)

#read and response
response = urllib2.urlopen(req)
print response


