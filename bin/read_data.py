#!/usr/bin/python
import serial, sys, struct, time, datetime

device_filename = sys.argv[1]
ser = serial.Serial(device_filename, 9600, timeout=1)

# Find alignment
packet_size = 49
s = ser.read(100)
ser.read(packet_size - ((100 - s.find("start")) % packet_size))

last_millis = 0
handle = open("data/data_collect.dat", "w")

count = 0
start_time = time.time()
while start_time+1 > time.time():
	s = ser.read(49)
	data = struct.unpack("iffffffffff", s[5:])

	if(s[:5] != "start"):
		print("uh oh!", count)

	handle.write(str(datetime.datetime.now().microsecond))
	handle.write(" ")
	for j in range(0, 11):
		handle.write(str(data[j]))
		handle.write(" ")
	handle.write("\n")

	count = count + 1
	last_millis = data[0]

handle.close()
ser.close()
print("Done.")
print(count)
