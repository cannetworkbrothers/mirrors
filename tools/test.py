import re
import copy

str_1 = "W12D12D12NS12"
str_2 = "W1"
str_3 = "S12D12D12N"
str_4 = "W12D12D12NS12"

if len(str_3) > 1:
    e = re.findall("[^W]*", str_3)
else:
    match = re.search("[W,S,N,1,2,3,4,5,6,7,8,9,0,a,b,c,d,D,e,f]", str_3)
    e = []
    e.append(match.string)
print(e)

for x in e:
    if x == "":
        e.remove(x)

print(e)

# match = re.search("[^W,S,N,1,2,3,4,5,6,7,8,9,0,a,b,c,d,D,e,f]", e[0])
# if match != None:
#     print("Hello")
temp = copy.copy(str(e[0]))
hello = re.findall("[^S,N]*", temp)
print("11111")
for val in hello:
    if val == "":
        hello.remove(val)
match = re.findall("[^D]*", hello[0])
print(match)

# e = ["", "asas", ""]
# e.remove("")

# print(e)
