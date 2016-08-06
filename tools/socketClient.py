#!/usr/bin/python           # This is client.py file

import socket               # Import socket module
import time
import random

s = socket.socket()         # Create a socket object
host = socket.gethostname() # Get local machine name
port = 9191                # Reserve a port for your service.

can_bus_messages = []
for x in range(1,151):
# while True
    out = ""
    can_id = random.randint(0, 0x7ff)
    if can_id > 0x7ff:
        out = "W"
    else:
        out = "S"
    can_id = str(hex(can_id))[2::]
    out = out + can_id
    data_byte = []
    for iterator in range(0, 8):
        temp_intereger = random.randint(0, 0xff)
        data_byte.append(str(hex(temp_intereger))[2::])
        out = out + "D" + data_byte[iterator]
    can_bus_messages.append(out)
    print((x -1), out)
start = time.time()
s.connect(('localhost', port))
while True:
    # s.send(b'W5eaffD0eaD1aeD20D30D42D5a0D6b1D7')
    time.sleep(0.01)
    s.send(bytearray(str.encode(can_bus_messages[random.randint(0, 149)])))
    print(time.time() - start)
    if (time.time() - start) > 60:
        break
    # print(s.recv(20))
s.close                     # Close the socket when done