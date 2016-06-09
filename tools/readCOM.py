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
	return [random.randint(1, n),random.randint(1, 10*n)] 

def put_to_queue(q, v):
	q.put(v)

def main():
	readCOM()
	# test = []
	# q = Queue()
	# # s = set(test)
	# s = []
	# fout = open('test.txt', 'w')
	# repeated = 0
	# while True:
	# 	# initial_t = time.time()
	# 	read_value = reader(1000)
	# 	put_to_queue(q, read_value)
	# 	initial_t = time.time()
	# 	if read_value not in s:
	# 		# s.add(read_value)
	# 		s.append(read_value)
	# 	else:
	# 		repeated = repeated + 1
	# 		pass
	# 	if len(s) == 10000:
	# 		print(read_value, len(s), repeated)
	# 		return 0
	# 	print(round(time.time() - initial_t)*1000.0, read_value, len(s))
		# print(read_value, len(s))


if __name__ == "__main__":
	main()