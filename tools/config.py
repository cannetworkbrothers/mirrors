"""Utils used for storing common functions"""

SIMULATION = False

#socket settings
TCP_IP = '127.0.0.1'
TCP_PORT = 9191
BUFFER_SIZE = 1024000

#COM port settings
COM_PORT = 'COM3'
BAUD_RATE = 56000
TIMEOUT = 0
RTSCTS = 2

# file names
LOG_FILE_NAME = "socket.log"
CAN_BUS_LOG_FILE_NAME = "can_bus.log"
NEW_CAN_MESSAGES_FILE_NAME = "last_can_bus.log"
