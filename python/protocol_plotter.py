from plotcat import plotter
import sys
import os
import serial
import time

if sys.version_info[0] < 3:

	import thread

else:

	import _thread as thread

data = []

temp0 = []
temp1 = []
temp2 = []
temp3 = []
temp4 = []

accelX = 0
accelY = 0
accelZ = 0
temp = 0
i = 0

samples = 50

usbConnection = ["/dev/ttyUSB0", "/dev/ttyUSB1", "/dev/ttyUSB2", "/dev/ttyUSB3", "/dev/ttyUSB4"]

data.append([0 for i in range(samples)])
data.append([0 for i in range(samples)])
data.append([0 for i in range(samples)])

p = plotter(number_of_samples=[samples, samples, samples], total_plots=3, rows=1, cols=3, y_low_lim=-2, y_high_lim=2, names='acceleration')

def stringCutter():

	global accelX, accelY, accelZ, temperature, orientation

	try:

		temp0 = str(ser.readline().strip())

		pos_f = temp0.index(',')

		orientation = temp0[3:6]
	
		temp1 = temp0[pos_f+1:]

		pos_s = temp1.index(',')
		accelX = int(temp1[:pos_s]) / 8190.0

		temp2 = temp1[pos_s+1:]

		pos_t = temp2.index(',')
		accelY = int(temp2[:pos_t]) / 8190.0

		temp3 = temp2[pos_t+1:]

		pos_e = temp3.index(',')
		accelZ = int(temp3[:pos_e]) / 8190.0

		temp4 = temp3[pos_e+1:]
		pos_f = temp4.index('$')

		temp = int(temp4[:pos_f])
		temperature = temp

	except AttributeError as Ae:
			
		pass

	except TypeError as Te:
			
		pass

	except Exception as e:
			
		pass

def graphOutput():

	global accelX, accelY, accelZ, temperature, orientation

	while True:

		try:

			stringCutter()

			print(orientation, "| X=", "{:>6.2}".format(accelX), "g | Y=", "{:>6.2}".format(accelY), "g | Z=", "{:>6.2}".format(accelZ), "g | T=", "{:>2}".format(temperature), "°C")

			try:

				[data[0].append(accelX)]
				[data[0].pop(0)]
				[data[1].append(accelY)]
				[data[1].pop(0)]
				[data[2].append(accelZ)]
				[data[2].pop(0)]

			except ValueError as Ve:

				pass

		except AttributeError as Ae:
			
			pass

		except TypeError as Te:
			
			pass

		except Exception as e:
			
			pass

@p.plot_self
def setval():

	p.lines[0][0].set_data(p.currentAxis[0], data[0])
	p.lines[1][0].set_data(p.currentAxis[1], data[1])
	p.lines[2][0].set_data(p.currentAxis[2], data[2])
		
def main():

	thread.start_new_thread(graphOutput, ())
	p.set_call_back(setval)
	plotter.show()

if __name__ == "__main__":

	try:

		if int(sys.argv[1]) == 16:

			inputUSB = 0

		if int(sys.argv[1]) == 17:

			inputUSB = 1

		if int(sys.argv[1]) == 18:

			inputUSB = 2

		if int(sys.argv[1]) == 19:

			inputUSB = 3

		if int(sys.argv[1]) == 20:

			inputUSB = 4

		ser = serial.Serial(usbConnection[int(inputUSB)], 115200)

		main()

	except KeyboardInterrupt:

		print("\nstop after keyboard interrupt\n")
