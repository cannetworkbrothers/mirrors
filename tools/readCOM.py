import serial
import sys
import time
import random
from multiprocessing import Process, Queue, Event

def readCOM():
	try:
		ser = serial.Serial('COM7', 57600, timeout=0, rtscts=2)
		while (True):
			b = ser.read()
			if b:
				sys.stdout.write(b.decode('cp1252').encode('utf-8').decode('utf-8'))
				sys.stdout.write(b)
	except serial.serialutil.SerialException:
		print("COM port is unpluged. Bye!") 

def writer(filename, n):
	with open(filename, 'w') as fout:
		for i in range(1000000):
			fout.write(str(1))

def reader(n):
	# 1st byte 0 0 0 S/E D3 L2 C1 C0
	# 2nd byte is inverse of 1st byte
	# n bytes of DATA
	output = 0b0
	rand = random.randint(0, 1)
	if rand == 1:
		output = output | 0b00001000
	else:
		output = output & 0b11110111
	output = output | 0b00000111
	items = []
	items.append(output)
	items.append(~output)
	for x in range(1, 9):
		items.append(random.randint(1, 3))
	# print(items)
	return items
	# return [random.randint(1, n),random.randint(1, 10*n)] 

def receiver()

def put_to_queue(q, v):
	q.put(v)

def main():
	# readCOM()
	test = []
	q = Queue()
	# s = set(test)
	s = []
	# fout = open('test.txt', 'w')
	new = 0
	initial_t = time.time()
	# for x in range(1, 80000):
	while True:
		# initial_t = time.time()
		read_value = reader(1000)
		put_to_queue(q, read_value)
		if read_value not in s:
			# s.add(read_value)
			s.append(read_value)
			new = new + 1
		if (time.time() - initial_t) < 3.0:
			# print(x)
			continue
		else:
			print(round(time.time() - initial_t), 'new ' + str(new), len(s))
			initial_t = time.time()
			new = 0

if __name__ == "__main__":
	main()