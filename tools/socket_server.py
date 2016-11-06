"""
Server - opens port and read the messages
"""
import socket
import time
import re
import com_parser
import config as config
import utils as utils

def log_messages_to_file(file_obj, can_array):
    """
    log CAN messages
    """
    for can_item in can_array:
        for item in can_item:
            file_obj.write(item)
        file_obj.write("\n")

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

    def listen(self, buffer_size):
        """
        main listener
        """
        invalid_pattern = "[^W,S,N,1,2,3,4,5,6,7,8,9,0,a,b,c,d,D,e,f]"
        log_file = open(config.LOG_FILE_NAME, "w")
        can_messages_file = open(config.CAN_BUS_LOG_FILE_NAME, "w")
        all_mesages_of_period_file = open(config.NEW_CAN_MESSAGES_FILE_NAME, "w")
        period_of_listening = 0
        current_str = ""
        while True:
            connection, address = self.sock.accept()

            print('Connection address:', address)
            can_bus = []
            all_mesages_of_period = []
            new_messages = []
            valid_str = False
            is_message_present = False
            number_of_new_messages = 0

            start_time = time.time()
            while True:
                data = connection.recv(buffer_size)
                received_data_string = data.decode('cp1252').encode('utf-8').decode('utf-8')
                match = re.search(invalid_pattern, received_data_string)
                if match != None:
                    current_str = ""
                    all_mesages_of_period = []
                    log_file.write(str("received trash\n"))
                    continue
                # print("received data:", received_data_string)
                # log_file.write(str("received data: ") + str(data, "cp1252") + "\n")
                current_str += received_data_string
                if valid_str:
                    #starts on W,S
                    is_message_present, current_str, recent_msg = com_parser.get_messages(current_str)
                else:
                    current_str = com_parser.find_start_of_can_message(current_str)
                    if current_str == "":
                        continue
                    else:
                        valid_str = True
                        is_message_present, current_str, recent_msg = com_parser.get_messages(current_str)
                if is_message_present:
                    # log_file.write("server::listen::parse return: " + current_str + "\n")
                    all_mesages_of_period, recent_msg = utils.left_join_lists(all_mesages_of_period, recent_msg)
                    if recent_msg != []:
                        can_bus, new_messages = utils.left_join_lists(can_bus, recent_msg)
                        number_of_new_messages += len(new_messages)
                if (time.time() - start_time) > 3:
                    start_time = time.time()
                    print("During last 3 seconds " + str(number_of_new_messages) + " new received")
                    print(can_bus)
                    open(config.CAN_BUS_LOG_FILE_NAME, "w").close()
                    can_messages_file = open(config.CAN_BUS_LOG_FILE_NAME, "w")
                    log_messages_to_file(can_messages_file, can_bus)
                    can_messages_file.close()

                    all_mesages_of_period_file.write("Period: " + str(period_of_listening) + "\n\n")
                    log_messages_to_file(all_mesages_of_period_file, all_mesages_of_period)
                    all_mesages_of_period_file.write("\n\n\n")
                    period_of_listening += 1
                    number_of_new_messages = 0
                    all_mesages_of_period = []
                    valid_str = False

