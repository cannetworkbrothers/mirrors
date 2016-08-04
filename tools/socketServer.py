#!/usr/bin/python           # This is server.py file

import socket
import time
import com_parser

TCP_IP = '127.0.0.1'
TCP_PORT = 9191
BUFFER_SIZE = 10240 

s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
s.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
s.settimeout(30.0)
s.bind((TCP_IP, TCP_PORT))
s.listen(1)

while True:    
    conn, addr = s.accept()

    print('Connection address:', addr)
    CAN_BUS_LAST_PERIOD = []
    CAN_BUS = []
    recent_items = []
    new_items = []

    start_time = time.time()
    while True:
        data = conn.recv(BUFFER_SIZE)
        if not data: break
        CAN_BUS_CURRENT = com_parser.get_can_messages(data.decode('cp1252').encode('utf-8').decode('utf-8'))
        if len(CAN_BUS_LAST_PERIOD) == 0:
            CAN_BUS_LAST_PERIOD = CAN_BUS_CURRENT
        else:
            for item in CAN_BUS_CURRENT:
                for item_last_period in CAN_BUS_LAST_PERIOD:
                    if item.can_id != item_last_period.can_id or item.data != item_last_period.data:
                        recent_items.append(item)
                    else:
                        continue
            if recent_items != []:
                for can_msg_current in recent_items:
                    CAN_BUS_LAST_PERIOD.append(can_msg_current)
        if (time.time() - start_time) > 3:
            start_time = time.time()
            print("Length of last messages: " + str(len(CAN_BUS_LAST_PERIOD)))
            if len(CAN_BUS) == 0:
                CAN_BUS = CAN_BUS_LAST_PERIOD
                print("New messages were found during last 3 seconds")
                for can_msg in CAN_BUS:
                    if can_msg.is_extended == 0:
                        print("Standard ", end="")
                    else:
                        print("Extended ", end="")
                    print(can_msg.can_id, can_msg.data)
            else:
                for item_last in CAN_BUS_LAST_PERIOD:
                    for item_from_all in CAN_BUS:
                        if item_last.can_id != item_from_all.can_id or item_last.data != item_from_all.data:
                            new_items.append(item_last)
                        else:
                            continue
                if new_items != []:
                    print("New messages were found during last 3 seconds")
                    for can_msg in new_items:
                        CAN_BUS.append(can_msg)
                        if can_msg.is_extended == 0:
                            print("Standard ", end="")
                        else:
                            print("Extended ", end="")
                        print(can_msg.can_id, can_msg.data)
                else:
                    print("No new messages during last 3 seconds")
            CAN_BUS_LAST_PERIOD = []
            recent_items = []
            new_items = []
        # com_parser.get_can_messages(data.decode('cp1252').encode('utf-8').decode('utf-8'))
        # print("received data:", data)
        # conn.send(data)

    conn.close()