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
