#!/usr/bin/python
import serial, sys, struct, time, datetime

import numpy as np
import matplotlib.pyplot as plt
import matplotlib.animation as animation

accel_z = [ 0.00 ] * 100

def update_line(num, data, line):
    line.set_data(accel_z)
    return line,

if(len(sys.argv) < 5):
	print("Usage:")
	print("  ./read_data_text.py device_filename baud_rate output_filename record_time")

else:
	device_filename = sys.argv[1]
	ser = serial.Serial(device_filename, int(sys.argv[2]), timeout=1)
	ser.flushInput()


	fig1 = plt.figure()
	l, = plt.plot(accel_z)
	plt.xlim(0, 100)
	plt.ylim(-20, 20)
	plt.xlabel('x')
	plt.title('test')
	line_ani = animation.FuncAnimation(fig1, update_line, 25, fargs=(accel_z, l), interval=50, blit=True)

	# Find alignment
	last_millis = 0
	handle = open(sys.argv[3], "w")

	count = 0
	start_time = time.time()
	while start_time+int(sys.argv[4]) > time.time():
		s = ser.readline()
		if len(s.split(" ")) != 11:
			continue

		handle.write(s)
		count = count + 1

		s = s.split(" ")
		accel_z[count % 100] = float(s[3])

	print(accel_z)

	handle.close()
	ser.close()


