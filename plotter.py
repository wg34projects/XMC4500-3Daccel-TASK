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
i = 0
samples = 200

ser = serial.Serial('/dev/ttyUSB0', 115200)

p = plotter(number_of_samples=[samples, samples, samples], total_plots=3, rows=1, cols=3, y_low_lim=-40000, y_high_lim=40000)

data.append([0 for i in range(samples)])
data.append([0 for i in range(samples)])
data.append([0 for i in range(samples)])

def read_from_serial():

	while True:

		for i in range(3):

			try:

				temp = ser.readline()
				temp = int(temp)

				try:

					[data[i].append(temp)]
					[data[i].pop(0)]

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

def menu():

	os.system('clear')

	confirm = input("press a key to continue...")

def main():

	thread.start_new_thread(read_from_serial, ())
	p.set_call_back(setval)
	plotter.show()

if __name__ == "__main__":

	try:
	
		menu()
		main()

	except KeyboardInterrupt:

		print("\nstop after keyboard interrupt\n")
		time.sleep(1)