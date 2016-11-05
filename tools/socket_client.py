"""socket_client - reading data from CAM shield"""
#!/usr/bin/python           # This is client.py file

import sys
import socket               # Import socket module
import time
from threading import Thread

import serial
import config as config
from utils import generate_can_messages

class SocketClient(Thread):
    """docstring for SocketClient"""
    def __init__(self):
        Thread.__init__(self)

    def run(self):
        client_sock = socket.socket() # Create a socket object
        client_sock.connect(('localhost', config.TCP_PORT)) # Connect to the socket

        if config.SIMULATION:
            can_bus_messages = generate_can_messages(501)
            start = time.time()
            index = 0
            while True:
                if index > 499:
                    index = 0
                time.sleep(0.05)
                client_sock.send(bytearray(str.encode(can_bus_messages[index])))
                # client_sock.send(str(data.decode('cp1252').encode('utf-8').decode('utf-8')))
                index += 1 
                if (time.time() - start) > 60:
                    break
        else:
            ser = serial.Serial(config.COM_PORT, config.BAUD_RATE, \
                timeout=config.TIMEOUT, rtscts=config.RTSCTS)
            while True:
                data = ser.read()
                if data:
                    # sys.stdout.write(str(data.decode('cp1252').encode('utf-8').decode('utf-8')))
                    client_sock.send(data)

        client_sock.close() # Close the socket when done
