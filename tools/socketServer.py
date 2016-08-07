#!/usr/bin/python           # This is server.py file

import socket
import time
import com_parser
import random #for client

from threading import Thread

TCP_IP = '127.0.0.1'
TCP_PORT = 9191
BUFFER_SIZE = 1024000 

class SocketServer(object):
    """docstring for SocketServer"""
    def __init__(self, ipaddress, tcp_port):
        super(SocketServer, self).__init__()
        self.ipaddress = ipaddress
        self.tcp_port = tcp_port
        self.sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        self.sock.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
        self.sock.settimeout(5.0)
        self.sock.bind((self.ipaddress, self.tcp_port))
        self.sock.listen(1)


    def print_can_mesasges(self, file_obj, can_array):
        for can_item in can_array:
            if can_item.is_extended == 0:
                file_obj.write("Stand.: ")
            else:
                file_obj.write("Exten.: ")
            file_obj.write(can_item.can_id + ", ")
            file_obj.write("data: ")
            for item in can_item.data:
                file_obj.write(item + " ")
            file_obj.write("\n")

    def start_forever(self, buffer_size):
        log_file = open("socket.log", "w")
        while True:    
            connection, address = self.sock.accept()

            print('Connection address:', address)
            can_bus = []
            all_messages_of_last_period = []
            new_messages_of_last_period = []
            is_new_period = True
            is_first_run = True

            start_time = time.time()
            while True:
                data = connection.recv(buffer_size)
                # print("received data:", data)
                log_file.write(str("received data: ") + str(data, "cp1252") + "\n")
                if not data: 
                    break
                just_received_messages = com_parser.get_can_messages(\
                    data.decode('cp1252').encode('utf-8').decode('utf-8'))
                # # debug
                # print("received")
                # for x in just_received_messages:
                #     print(x.can_id, end="")
                #     for y in x.data:
                #         print(y, end="")
                #     print("")
                # # debug
                length_of_just_received = len(just_received_messages)
                is_array_changed = False
                if length_of_just_received > 1:
                    while True:
                        length_of_just_received = len(just_received_messages)
                        for key, value in enumerate(just_received_messages):
                            if (length_of_just_received - 1) > 1:
                                for index in range(key + 1, length_of_just_received):
                                    if  value.can_id == just_received_messages[index].can_id and \
                                        value.data == just_received_messages[index].data:
                                        # print("deleted")
                                        del just_received_messages[key]
                                        is_array_changed = True
                                        break
                            if is_array_changed is True:
                                break
                        if is_array_changed is True:
                            is_array_changed = False
                        else:
                            break
                # # debug
                # print("duplicates removed: ")
                # for x in just_received_messages:
                #     print(x.can_id, end="")
                #     for y in x.data:
                #         print(y, end="")
                #     print("")
                # # debug
                for msg in just_received_messages:
                    # print("just_received_messages: " + x.can_id)
                    log_file.write("just_received_messages: " + msg.can_id + "\n")
                    for can_byte in msg.data:
                        # print(y, end=" ")
                        log_file.write(can_byte + " ")
                    log_file.write("\n")
                if is_new_period:
                    all_messages_of_last_period = just_received_messages
                    is_new_period = False
                else:
                    for item in just_received_messages:
                        is_current_present = False
                        for item_last_period in all_messages_of_last_period:
                            if  item.can_id == item_last_period.can_id and \
                                item.data == item_last_period.data:
                                is_current_present = True
                                break
                        if is_current_present is False:
                            all_messages_of_last_period.append(item)
                if (time.time() - start_time) > 3:
                    start_time = time.time()
                    print("Were received: " + str(len(all_messages_of_last_period)))
                    if is_first_run:
                        is_first_run = False
                        can_bus = all_messages_of_last_period
                        new_found = len(all_messages_of_last_period)
                        print(str(new_found) + \
                            " new messages were found during last 3 seconds")
                        log_file.write(str(new_found) + \
                            " new messages were found during last 3 seconds")
                        self.print_can_mesasges(log_file, all_messages_of_last_period)
                        all_messages_of_last_period = []
                        new_messages_of_last_period = []
                        is_new_period = True
                    else:
                        is_current_present = False
                        for item_last in all_messages_of_last_period:
                            for item_from_all in can_bus:
                                if item_last.can_id == item_from_all.can_id \
                                    and item_last.data == item_from_all.data:
                                    is_current_present = True
                                    break
                            if is_current_present is False:
                                new_messages_of_last_period.append(item_last)
                        if new_messages_of_last_period != []:
                            new_found = len(new_messages_of_last_period)
                            print(str(new_found) + \
                                " new messages were found during last 3 seconds")
                            log_file.write("New messages(" + str(len(new_messages_of_last_period))\
                                +  ") were found during last 3 seconds")
                            for can_msg in new_messages_of_last_period:
                                can_bus.append(can_msg)
                            self.print_can_mesasges(log_file, new_messages_of_last_period)
                        else:
                            print("No new messages during last 3 seconds")
                        all_messages_of_last_period = []
                        new_messages_of_last_period = []
                        is_new_period = True
                # com_parser.get_can_messages(data.decode('cp1252').encode('utf-8').decode('utf-8'))
                # print("received data:", data)
                # connection.send(data)
            log_file.close()
            can_messages_file = open("can_bus.log", "w")
            self.print_can_mesasges(can_messages_file, can_bus)
            can_messages_file.close()
            connection.close()

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


server_com = SocketServer(TCP_IP, TCP_PORT)

clientThread = SocketClient()
clientThread.setDaemon(True)
clientThread.start()

server_com.start_forever(BUFFER_SIZE)
