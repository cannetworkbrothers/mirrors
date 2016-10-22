#!/usr/bin/python
"""
The main module of the CAN bus analyzer
"""
import sys
import socket_client
import socket_server
import config as config

# from threading import Thread

# TCP_IP = '127.0.0.1'
# TCP_PORT = 9191
# BUFFER_SIZE = 1024000

def main():
    """
    main function of CAN bus listener
    """
    server_com = socket_server.SocketServer(config.TCP_IP, config.TCP_PORT)

    client_thread = socket_client.SocketClient()
    client_thread.setDaemon(True)
    client_thread.start()

    server_com.start_forever(config.BUFFER_SIZE)

if __name__ == '__main__':
    try:
        main()
    except KeyboardInterrupt:
        sys.exit(0)
