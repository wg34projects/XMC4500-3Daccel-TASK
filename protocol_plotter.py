from plotcat import plotter
import sys
import os
import serial
import time

confirm = "g"

if sys.version_info[0] < 3:

	import thread

else:

	import _thread as thread

data = []
i = 0
samples = 2000

ser = serial.Serial('/dev/ttyUSB2', 115200)

p = plotter(number_of_samples=[samples, samples, samples], total_plots=3, rows=1, cols=3, y_low_lim=-40000, y_high_lim=40000)

data.append([0 for i in range(samples)])
data.append([0 for i in range(samples)])
data.append([0 for i in range(samples)])

def read_from_serial():

	while True:

		try:

			temp0 = str(ser.readline().strip())

			pos_f = temp0.index(',')

			orientation = temp0[3:6]
	
			temp1 = temp0[pos_f+1:]

			pos_s = temp1.index(',')
			integer1 = int(temp1[:pos_s])

			temp2 = temp1[pos_s+1:]

			pos_t = temp2.index(',')
			integer2 = int(temp2[:pos_t])

			temp3 = temp2[pos_t+1:]

			pos_e = temp3.index(',')
			integer3 = int(temp3[:pos_e])

			temp4 = temp3[pos_e+1:]
			pos_f = temp4.index('$')

			integer4 = int(temp4[:pos_f])
			temperature = integer4 * 2 + 10

			print(orientation, "| X=", "{:>6}".format(integer1), "| Y=", "{:>6}".format(integer2), "| Z=", "{:>6}".format(integer3), "| T=", "{:>2}".format(temperature), "°C")

			try:

				[data[0].append(integer1)]
				[data[0].pop(0)]
				[data[1].append(integer2)]
				[data[1].pop(0)]
				[data[2].append(integer3)]
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

def menu():

	global confirm

	os.system('clear')

	confirm = input("input g + ENTER for graph and only ENTER for values only")

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
