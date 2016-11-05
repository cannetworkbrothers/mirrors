import re
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

def remove_empty_string(arr):
    """
    remove empty strings from the array
    """
    for item in arr:
        if item == "":
            arr.remove(item)
    return arr

def get_messages(input_str):
    """
    parse incoming string to CAN messages
    returns CAN messages and remaing part of string
    """
    return_str = ""
    return_list_of_messages = []
    can_message = []
    if len(input_str) > 1:
        can_members = re.findall("[^W]*", input_str)
    else:
        return input_str, return_list_of_messages
    remove_empty_string(can_members)
    # print(can_members)
    for item in can_members:
        if item == "":
            continue
        if item[-1] == "N":
            if item[0] == "S":
                can_message.append("S")
                match = re.findall("[^S,N]*", item)
            else:
                can_message.append("W")
                match = re.findall("[^N]*", item)
            remove_empty_string(match)
            match = re.findall("[^D]*", match[0])
            remove_empty_string(match)
            can_message += match
            return_list_of_messages.append(can_message)
        else:
            return item, return_list_of_messages
    return return_str, return_list_of_messages
