#!/usr/bin/python
import serial, sys, struct, time, datetime

if(len(sys.argv) < 5):
	print("Usage:")
	print("  ./read_data_text.py device_filename baud_rate output_filename record_time")

else:
	device_filename = sys.argv[1]
	ser = serial.Serial(device_filename, int(sys.argv[2]), timeout=1)
	ser.flushInput()

	# Find alignment
	last_millis = 0
	handle = open(sys.argv[3], "w")

	try:
		count = 0
		start_time = time.time()
		while start_time+int(sys.argv[4]) > time.time():
			s = ser.readline()
			if len(s.split(" ")) != 11:
				continue

			handle.write(s)
			count = count + 1
	except:
		pass


	handle.close()
	ser.close()

	print("Done.")
	print(count)

