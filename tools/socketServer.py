#!/usr/bin/python           # This is server.py file

import socket
import time
import com_parser

TCP_IP = '127.0.0.1'
TCP_PORT = 9191
BUFFER_SIZE = 10240 

s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
s.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
s.settimeout(5.0)
s.bind((TCP_IP, TCP_PORT))
s.listen(1)

def print_can_mesasges(file_obj, can_array):
    for can_item in can_array:
        if can_item.is_extended == 0:
            file_obj.write("Stand.: ")
        else:
            file_obj.write("Exten.: ")
        file_obj.write(can_item.can_id + ", ")
        file_obj.write("DATA: ")
        for x in can_item.data:
            file_obj.write(x + " ")
        file_obj.write("\n")

log_file = open("socket.log", "w")
while True:    
    CONNECTION, ADDRESS = s.accept()

    print('Connection address:', ADDRESS)
    CAN_BUS = []
    CAN_BUS_LAST_PERIOD = []
    NEW_ITEMS = []
    IS_NEW_PERIOD = True
    IS_FIRST_RUN = True

    START_TIME = time.time()
    while True:
        DATA = CONNECTION.recv(BUFFER_SIZE)
        print("received data:", DATA)
        log_file.write(str("received data: ") + str(DATA, "cp1252") + "\n")
        if not DATA: 
            break
        CAN_BUS_CURRENT = com_parser.get_can_messages(\
            DATA.decode('cp1252').encode('utf-8').decode('utf-8'))
        for x in CAN_BUS_CURRENT:
            # print("CAN_BUS_CURRENT: " + x.can_id)
            log_file.write("CAN_BUS_CURRENT: " + x.can_id + "\n")
            for y in x.data:
                # print(y, end=" ")
                log_file.write(y + " ")
            log_file.write("\n")
        if IS_NEW_PERIOD:
            CAN_BUS_LAST_PERIOD = CAN_BUS_CURRENT
            IS_NEW_PERIOD = False
        else:
            is_current_present = False
            for item in CAN_BUS_CURRENT:
                for item_last_period in CAN_BUS_LAST_PERIOD:
                    if item.can_id == item_last_period.can_id and item.data == item_last_period.data:
                        is_current_present = True
                        break
                if is_current_present == False:
                    CAN_BUS_LAST_PERIOD.append(item)
        if (time.time() - START_TIME) > 3:
            START_TIME = time.time()
            print("Length of last messages: " + str(len(CAN_BUS_LAST_PERIOD)))
            if IS_FIRST_RUN:
                IS_FIRST_RUN = False
                CAN_BUS = CAN_BUS_LAST_PERIOD
                print("New messages were found during last 3 seconds")
                log_file.write("New messages were found during last 3 seconds")
                print_can_mesasges(log_file, CAN_BUS_LAST_PERIOD)
                CAN_BUS_LAST_PERIOD = []
                NEW_ITEMS = []
                IS_NEW_PERIOD = True
            else:
                is_current_present = False
                for item_last in CAN_BUS_LAST_PERIOD:
                    for item_from_all in CAN_BUS:
                        if item_last.can_id == item_from_all.can_id \
                            and item_last.data == item_from_all.data:
                            is_current_present = True
                            break
                    if is_current_present == False:
                        NEW_ITEMS.append(item_last)
                if NEW_ITEMS != []:
                    print("New messages(" + str(len(NEW_ITEMS))\
                        +  ") were found during last 3 seconds")
                    log_file.write("New messages(" + str(len(NEW_ITEMS))\
                        +  ") were found during last 3 seconds")
                    for can_msg in NEW_ITEMS:
                        CAN_BUS.append(can_msg)
                    print_can_mesasges(log_file, NEW_ITEMS)
                else:
                    print("No new messages during last 3 seconds")
                CAN_BUS_LAST_PERIOD = []
                NEW_ITEMS = []
                IS_NEW_PERIOD = True
        # com_parser.get_can_messages(data.decode('cp1252').encode('utf-8').decode('utf-8'))
        # print("received data:", data)
        # CONNECTION.send(data)
    log_file.close()
    can_messages_file = open("can_bus.log", "w")
    print_can_mesasges(can_messages_file, CAN_BUS)
    can_messages_file.close()
    CONNECTION.close()
