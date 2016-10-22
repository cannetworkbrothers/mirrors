"""socket_client - reading data from CAM shield"""
#!/usr/bin/python           # This is client.py file

import socket               # Import socket module
import time
from threading import Thread

import config as config
from utils import generate_can_messages

class SocketClient(Thread):
    """docstring for SocketClient"""
    def __init__(self):
        Thread.__init__(self)

    def run(self):
        client_sock = socket.socket()         # Create a socket object

        can_bus_messages = generate_can_messages(501)
        start = time.time()
        client_sock.connect(('localhost', config.TCP_PORT))
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
