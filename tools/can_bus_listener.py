#!/usr/bin/python           # This is server.py file

import socket_client_COM
import socket_server_COM

# from threading import Thread

TCP_IP = '127.0.0.1'
TCP_PORT = 9191
BUFFER_SIZE = 1024000

def main():
    server_com = socket_server_COM.SocketServer(TCP_IP, TCP_PORT)

    clientThread = socket_client_COM.SocketClient()
    clientThread.setDaemon(True)
    clientThread.start()

    server_com.start_forever(BUFFER_SIZE)

if __name__ == '__main__':
    main()
