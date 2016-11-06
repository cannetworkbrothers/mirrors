"""C
Parser of string that comes from COM port
string could be "", "D23", "D23W12" etc
Parser should return string started from W,S
"""
import re

def find_start_of_can_message(input_str):
    """serach for 1st W/S and returns string after W/S or []"""
    iterator = 0
    for char in input_str:
        if char == 'W' or char == 'S':
            input_str = input_str[iterator::]
            # print("start find: " + input_str)
            return input_str
        iterator += 1
    return ""

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
    # print("get_messages:: " + input_str)
    can_messages = []

    input_str = find_start_of_can_message(input_str)
    if input_str == "":
        return False, input_str, can_messages
    
    is_message_present_in_str = False
    while True:
        can_message_str = re.search(r"[S,W][\d,a,b,c,d,e,f]*(D[\d,a,b,c,d,e,f]*)*N", input_str)
        if can_message_str != None:
            #add found message
            is_message_present_in_str = True
            can_message_str = str(can_message_str.group(0))
            can_messages.append(can_message_str)
            #remove current message form string
            index = len(can_message_str)
            input_str = input_str[index::]
        else:
            return is_message_present_in_str, input_str, can_messages
