"""
Server - opens port and read the messages
"""
import socket
import time
import com_parser

LOG_FILE_NAME = "socket.log"
CAN_BUS_LOG_FILE_NAME = "can_bus.log"
NEW_CAN_MESSAGES_FILE_NAME = "last_can_bus.log"

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


    def log_messages_to_file(self, file_obj, can_array):
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
        log_file = open(LOG_FILE_NAME, "w")
        can_messages_file = open(CAN_BUS_LOG_FILE_NAME, "w")
        new_messages_file = open(NEW_CAN_MESSAGES_FILE_NAME, "w")
        period_of_listening = 0
        while True:
            connection, address = self.sock.accept()

            print('Connection address:', address)
            can_bus = []
            all_messages = []
            new_messages = []
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
                    all_messages = just_received_messages
                    is_new_period = False
                else:
                    for item in just_received_messages:
                        is_current_present = False
                        for item_last_period in all_messages:
                            if  item.can_id == item_last_period.can_id and \
                                item.data == item_last_period.data:
                                is_current_present = True
                                break
                        if is_current_present is False:
                            all_messages.append(item)
                if (time.time() - start_time) > 3:
                    start_time = time.time()
                    print("Were received: " + str(len(all_messages)))
                    if is_first_run:
                        is_first_run = False
                        can_bus = all_messages
                        new_found = len(all_messages)
                        print(str(new_found) + \
                            " new messages were found during last 3 seconds")
                        log_file.write(str(new_found) + \
                            " new messages were found during last 3 seconds")
                        self.log_messages_to_file(log_file, all_messages)
                        can_messages_file.close()
                        open(CAN_BUS_LOG_FILE_NAME, "w").close()
                        can_messages_file = open(CAN_BUS_LOG_FILE_NAME, "w")
                        self.log_messages_to_file(can_messages_file, can_bus)
                        new_messages_file.write("Period: " + str(period_of_listening) + "\n\n")
                        self.log_messages_to_file(new_messages_file, all_messages)
                        new_messages_file.write("\n\n\n")
                        period_of_listening += 1
                        all_messages = []
                        new_messages = []
                        is_new_period = True
                    else:
                        is_current_present = False
                        for item_last in all_messages:
                            for item_from_all in can_bus:
                                if item_last.can_id == item_from_all.can_id \
                                    and item_last.data == item_from_all.data:
                                    is_current_present = True
                                    break
                            if is_current_present is False:
                                new_messages.append(item_last)
                        if new_messages != []:
                            new_found = len(new_messages)
                            print(str(new_found) + \
                                " new messages were found during last 3 seconds")
                            log_file.write("New messages(" + str(len(new_messages))\
                                +  ") were found during last 3 seconds")
                            for can_msg in new_messages:
                                can_bus.append(can_msg)
                            self.log_messages_to_file(log_file, new_messages)
                            can_messages_file.close()
                            open(CAN_BUS_LOG_FILE_NAME, "w").close()
                            can_messages_file = open(CAN_BUS_LOG_FILE_NAME, "w")
                            self.log_messages_to_file(can_messages_file, can_bus)
                            new_messages_file.write("Period: " + str(period_of_listening) + "\n\n")
                            self.log_messages_to_file(new_messages_file, new_messages)
                            new_messages_file.write("\n\n\n")
                            period_of_listening += 1
                        else:
                            print("No new messages during last 3 seconds")
                        all_messages = []
                        new_messages = []
                        is_new_period = True
                # com_parser.get_can_messages(data.decode('cp1252').encode('utf-8').decode('utf-8'))
                # print("received data:", data)
                # connection.send(data)
            log_file.close()
            can_messages_file.close()
            open(CAN_BUS_LOG_FILE_NAME, "w").close()
            can_messages_file = open(CAN_BUS_LOG_FILE_NAME, "w")
            self.log_messages_to_file(can_messages_file, can_bus)
            can_messages_file.close()
            new_messages_file.close()
            connection.close()
