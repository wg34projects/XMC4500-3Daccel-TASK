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

integer1 = 0
integer2 = 0
integer3 = 0
integer4 = 0
i = 0

samples = 200

usbConnection = ["/dev/ttyUSB0", "/dev/ttyUSB1", "/dev/ttyUSB2", "/dev/ttyUSB3", "/dev/ttyUSB4"]

data.append([0 for i in range(samples)])
data.append([0 for i in range(samples)])
data.append([0 for i in range(samples)])

p = plotter(number_of_samples=[samples, samples, samples], total_plots=3, rows=1, cols=3, y_low_lim=-40000, y_high_lim=40000)

def stringCutter():

	global integer1, integer2, integer3, temperature, orientation

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
		temperature = integer4 * 2 + 6

	except AttributeError as Ae:
			
		pass

	except TypeError as Te:
			
		pass

	except Exception as e:
			
		pass

def graphOutput():

	global integer1, integer2, integer3, temperature, orientation

	while True:

		try:

			stringCutter()

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

def protocol(mode):

	global integer1, integer2, integer3, temperature, orientation

	try:
		
		while (1):

			temp = str(ser.readline().strip())

			if mode == 1:

				print(temp)

			elif mode == 0:

				stringCutter()
				print(orientation, "| X=", "{:>6}".format(integer1), "| Y=", "{:>6}".format(integer2), "| Z=", "{:>6}".format(integer3), "| T=", "{:>2}".format(temperature), "°C")

			else:

				print ("error")

	except KeyboardInterrupt:

		print("\nstop after keyboard interrupt\n")
		time.sleep(1)

@p.plot_self
def setval():

	p.lines[0][0].set_data(p.currentAxis[0], data[0])
	p.lines[1][0].set_data(p.currentAxis[1], data[1])
	p.lines[2][0].set_data(p.currentAxis[2], data[2])

def menu():

	while (1):

		try:
			
			print("")
			print("g for graph window and decoded protocol view")
			print("p for decoded protocol view")
			print("r for raw protocol view")
			print("")
			inputOutput = input("your choice > ")

			if (str(inputOutput) == "g"):	

				main()
				break

			elif (str(inputOutput) == "p"):
	
				protocol(0)
				break

			elif (str(inputOutput) == "r"):
	
				protocol(1)
				break

			else:

				print("g, p or r only, try again...")

		except:

			print("input error, try again...")
			pass
		
def main():

	thread.start_new_thread(graphOutput, ())
	p.set_call_back(setval)
	plotter.show()

if __name__ == "__main__":

	try:

		os.system('clear')
		print("")		
		print("Welcome to the Python - Matplotlib frontend")
		print("BEL3 Embedded Systems - Resch / Egermann")
		print("")
		print("0 for /dev/ttyUSB0")
		print("1 for /dev/ttyUSB1")
		print("2 for /dev/ttyUSB2")
		print("3 for /dev/ttyUSB3")
		print("4 for /dev/ttyUSB4")
		print("")

		while (1):

			try:

				inputUSB = input("your choice > ")

				if (int(inputUSB) >= 0 and int(inputUSB) < 4):	

					break

				else:
	
					print("range error, try again...")

			except:

				print("input error, try again...")
				pass
		
		ser = serial.Serial(usbConnection[int(inputUSB)], 115200)

		menu()

	except KeyboardInterrupt:

		print("\nstop after keyboard interrupt\n")
		time.sleep(1)
