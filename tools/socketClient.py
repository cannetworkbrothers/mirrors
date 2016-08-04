#!/usr/bin/python           # This is client.py file

import socket               # Import socket module
import time
import traceback

s = socket.socket()         # Create a socket object
host = socket.gethostname() # Get local machine name
port = 9191                # Reserve a port for your service.

s.connect(('localhost', port))
for x in range(1,10):
# while True:
	pass
	s.send(b'W5eaffD0eaD1aeD20D30D42D5a0D6b1D7')
	time.sleep(1)	
	# print(s.recv(20))
s.close                     # Close the socket when done