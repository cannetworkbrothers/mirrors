#!/usr/bin/python           # This is server.py file

import socket
import time

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
        file_obj.write(can_item + "\n")

log_file = open("socket.log", "w")
while True:    
    connection, address = s.accept()

    print('Connection address:', address)
    can_bus = []
    all_can_messages_during_last_period_of_time = []
    new_can_messages_during_last_period_of_time = []
    is_new_period = True
    is_first_run = True

    start_time = time.time()
    while True:
        data = connection.recv(BUFFER_SIZE)
        print("received data:", data)
        log_file.write(str("received data: ") + str(data, "cp1252") + "\n")
        if not data: 
            break
        data = data.decode('cp1252').encode('utf-8').decode('utf-8')
        if is_new_period:
            all_can_messages_during_last_period_of_time.append(data)
            is_new_period = False
        else:
            is_current_present = False
            for item_last_period in all_can_messages_during_last_period_of_time:
                if data == item_last_period:
                    is_current_present = True
                    break
            if is_current_present == False:
                all_can_messages_during_last_period_of_time.append(data)
        if (time.time() - start_time) > 3:
            start_time = time.time()
            print("Length of last messages: " + str(len(all_can_messages_during_last_period_of_time)))
            if is_first_run:
                is_first_run = False
                can_bus = all_can_messages_during_last_period_of_time
                print("New messages were found during last 3 seconds")
                log_file.write("New messages were found during last 3 seconds")
                print_can_mesasges(log_file, all_can_messages_during_last_period_of_time)
                all_can_messages_during_last_period_of_time = []
                new_can_messages_during_last_period_of_time = []
                is_new_period = True
            else:
                is_current_present = False
                for item_last in all_can_messages_during_last_period_of_time:
                    for item_from_all in can_bus:
                        if item_last == item_from_all:
                            is_current_present = True
                            break
                    if is_current_present == False:
                        new_can_messages_during_last_period_of_time.append(item_last)
                if new_can_messages_during_last_period_of_time != []:
                    print("New messages(" + str(len(new_can_messages_during_last_period_of_time))\
                        +  ") were found during last 3 seconds")
                    log_file.write("New messages(" + str(len(new_can_messages_during_last_period_of_time))\
                        +  ") were found during last 3 seconds")
                    for can_msg in new_can_messages_during_last_period_of_time:
                        can_bus.append(can_msg)
                    print_can_mesasges(log_file, new_can_messages_during_last_period_of_time)
                else:
                    print("No new messages during last 3 seconds")
                all_can_messages_during_last_period_of_time = []
                new_can_messages_during_last_period_of_time = []
                is_new_period = True
        # com_parser.get_can_messages(data.decode('cp1252').encode('utf-8').decode('utf-8'))
        # print("received data:", data)
        # connection.send(data)
    log_file.close()
    can_messages_file = open("can_bus.log", "w")
    print_can_mesasges(can_messages_file, can_bus)
    can_messages_file.close()
    connection.close()
