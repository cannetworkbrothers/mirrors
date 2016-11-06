"""Utils used for storing common functions"""
import random

def generate_can_messages(number_of_messages):
    """to test - generate the CAN messages """
    messages_to_generate = []
    for msg_number in range(1, number_of_messages):
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
        messages_to_generate.append(out)
        print((msg_number -1), out)
    return messages_to_generate

def left_join_lists(left_lst, right_lst):
    """
    Join rigth 2D list to left 2D list
    """
    new_messages = []
    for right in right_lst:
        is_present = False
        for left in left_lst:
            if right == left:
                is_present = True
                break
        if is_present is False:
            left_lst.append(right)
            new_messages.append(right)
    return left_lst, new_messages
