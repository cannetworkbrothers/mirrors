# just_received_messages = [1, 12, 11, 16, 3, 12, 12, 12, 23, 11, 12, 12, 43, 14, 16, 12, 18]
# print(just_received_messages)

# length_of_just_received = len(just_received_messages)
# is_array_changed = False
# if length_of_just_received > 1:
#     print("fff")
#     while True:
#         for key, value in enumerate(just_received_messages):
#             print(length_of_just_received)
#             if ((length_of_just_received - 1) > 1):
#                 print("bbb")
#                 for index in range(key + 1, len(just_received_messages)):
#                     print("key: ", key)
#                     print("index: ", index)
#                     if  value == just_received_messages[index]:
#                         del just_received_messages[key]
#                         is_array_changed = True
#                         break
#             if is_array_changed is True:
#                 break
#         if is_array_changed is True:
#             is_array_changed = False
#         else:
#             break
# print(just_received_messages)
n = 0xeff
base = 16
counter = 0
while n > base:
    n = n / base
    counter += 1

counter += 1
print(counter)