import copy

# str_from_socket = "W12eD0D2DaDb1D123WeaDaeD0D0D2WefDa0Db1D11eDeaDaeD0D0D2DaWeDb1D1"

class CanMessage():
    """docstring for CanMessage"""
    def __init__(self, can_id, is_extended, data):
        super(CanMessage, self).__init__()
        self.can_id = can_id
        self.is_extended = is_extended
        self.data = data   

def find_start_of_can_message(input_str, can_msg):
    """serach for 1st W/S and returns string after W/S or []"""
    iterator = 0
    is_start_of_can_message_found = False
    for char in input_str:
        iterator += 1
        if char == 'W' or char == 'S':
            input_str = input_str[iterator::]
            is_start_of_can_message_found = True
            if char == 'W':
                can_msg.is_extended = 1
            else:
                can_msg.is_extended = 0
            break
    if is_start_of_can_message_found is True:
        return input_str
    else:
        return []

def clear_can_message(can_msg):
    """C-like struct for storing CAN message"""
    can_msg.can_id = ""
    can_msg.is_extended = 0
    can_msg.data = []

def reset_wrong_chars(list_of_chars, position, can_msg):
    """clear all processed chars and return remaining valid string"""
    print("Detected wrong sequence of chars: ", end="")
    print(list_of_chars[(position-1)::])
    clear_can_message(can_msg)
    list_of_chars = list_of_chars[position::]
    list_of_chars = find_start_of_can_message(list_of_chars, can_msg)
    return list_of_chars

def get_can_messages(input_str):
    # print("Incoming str" + input_str)
    can_bus = []
    can_message = CanMessage("", 0, [])  
    is_id_flag = True
    data_number = ""
    input_sequence = list(input_str)
    input_sequence = find_start_of_can_message(input_str, can_message)
    while True:
        if len(input_sequence) == 0:
            break
        iterator = 0
        dlc = 0
        for char in input_sequence:
            iterator += 1
            if is_id_flag is True:
                if char in '0123456789abcdef':
                    can_message.can_id += char
                    continue
                elif char == 'D':
                    is_id_flag = False
                    dlc += 1
                    continue
                else:
                    # previous sequence is wrong
                    input_sequence = reset_wrong_chars(input_sequence, iterator, can_message)
                    is_id_flag = True
                    break
            else:
                if char in '0123456789abcdef':
                    data_number += char
                    continue
                elif char == 'D':
                    dlc += 1
                    can_message.data.append(data_number)
                    data_number = ""
                    continue
                elif char == 'W' or char == 'S':
                    #start of new can mesage, need to store previous
                    if can_message.can_id != "" and len(can_message.data) < 9:
                        can_bus.append(copy.copy(can_message))
                    else:
                        print("Detected wrong message: ", end="")
                        print(can_message.can_id, can_message.data)
                    clear_can_message(can_message)
                    is_id_flag = True
                    if char == 'W':
                        can_message.is_extended = 1
                    else:
                        can_message.is_extended = 0
                    data_number = ""
                    continue
                else:
                    # previous sequence is wrong
                    input_sequence = reset_wrong_chars(input_sequence, iterator, can_message)
                    break
        input_sequence = []
    if can_message.can_id != "" and len(can_message.data) < 9:
        if data_number != "":
            can_message.data.append(data_number)
        if dlc < 8:
            print(input_str)
        can_bus.append(can_message)
    else:
        print("Detected wrong message: ", end="")
        print(can_message.can_id, can_message.data)
    return can_bus

# if __name__ == '__main__':
#     CAN_BUS = []
#     CAN_BUS = main(str_from_socket)
#     for msg in CAN_BUS:
#         if msg.is_extended == 0:
#             print("Standard ", end="")
#         else:
#             print("Extended ", end="")
#         print(msg.can_id, msg.data)
