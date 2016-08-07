#!/usr/bin/python           # This is client.py file

import socket               # Import socket module
import time
import random

from threading import Thread

class SocketClient(Thread):
    """docstring for SocketClient"""
    def __init__(self):
        Thread.__init__(self)

    def run(self):
        client_sock = socket.socket()         # Create a socket object
        port = 9191                # Reserve a port for your service.

        can_bus_messages = []
        for msg_number in range(1, 501):
        # while True
            out = ""
            can_id = random.randint(0, 0x1fffffff)
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
            print((msg_number -1), out)
        start = time.time()
        client_sock.connect(('localhost', port))
        index = 0
        while True:
            # s.send(b'W5eaffD0eaD1aeD20D30D42D5a0D6b1D7')
            if index > 499:
                index = 0
            time.sleep(0.05)
            client_sock.send(bytearray(str.encode(can_bus_messages[index])))
            index += 1 
            # print(time.time() - start)
            if (time.time() - start) > 60:
                break
            # print(s.recv(20))
        client_sock.close() # Close the socket when done
