from mpl_toolkits.mplot3d import axes3d
import matplotlib.pyplot as plt
import serial

fig = plt.figure()
ax = fig.add_subplot(111, projection='3d')

X, Y, Z = [1, 2, 3, 4, 5, 6, 7, 8, 9, 10], [1, 2, 3, 4, 5, 6, 7, 8, 9, 10], [1, 2, 3, 4, 5, 6, 7, 8, 9, 10]

ax.plot_wireframe(X,Y,Z)

plt.show()

#import serial
#import numpy as np
#from matplotlib import pyplot as plt
#ser = serial.Serial('/dev/ttyUSB0', 115200)
# 
#plt.ion() # set plot to animated
# 
#ydata = [0] * 500
#ax1=plt.axes()  
# 
## make plot
#line, = plt.plot(ydata)
#plt.ylim([-40000.0,40000.0])
# 
## start data collection
#while True:  

#	data = ser.readline().rstrip() # read data from serial 
#	data = float(data)
#	print(data)
#	ydata.append(data)
#	del ydata[0]
#	line.set_xdata(np.arange(len(ydata)))
#	line.set_ydata(ydata)  # update the data
#	plt.draw() # update the plot


#"""
#ldr.py
#Display analog data from Arduino using Python (matplotlib)
#Author: Mahesh Venkitachalam
#Website: electronut.in
#"""

#import sys, serial, argparse
#import numpy as np
#from time import sleep
#from collections import deque

#import matplotlib.pyplot as plt 
#import matplotlib.animation as animation

#    
## plot class
#class AnalogPlot:
#  # constr
#  def __init__(self, strPort, maxLen):
#      # open serial port
#      self.ser = serial.Serial(strPort, 115200)

#      self.ax = deque([0.0]*maxLen)
#      self.ay = deque([0.0]*maxLen)
#      self.az = deque([0.0]*maxLen)
#      self.maxLen = maxLen

#  # add to buffer
#  def addToBuf(self, buf, val):
#      if len(buf) < self.maxLen:
#          buf.append(val)
#      else:
#          buf.pop()
#          buf.appendleft(val)

#  # add data
#  def add(self, data):
#      assert(len(data) == 3)
#      self.addToBuf(self.ax, data[0])
#      self.addToBuf(self.ay, data[1])
#      self.addToBuf(self.ay, data[2])

#  # update plot
#  def update(self, frameNum, a0, a1, a2):
#      try:
#          line1 = float(self.ser.readline().rstrip())
#          line2 = float(self.ser.readline().rstrip())
#          line3 = float(self.ser.readline().rstrip())

#          print(line1, line2, line3)
#          
#          data = [line1, line2, line3]

#          if(len(data) == 3):
#              self.add(data)
#              a0.set_data(range(self.maxLen), self.ax)
#              a1.set_data(range(self.maxLen), self.ay)
#              a2.set_data(range(self.maxLen), self.az)
#      except KeyboardInterrupt:
#          print('exiting')
#      
#      return a0, 

#  # clean up
#  def close(self):
#      # close serial
#      self.ser.flush()
#      self.ser.close()    

## main() function
#def main():
#  # create parser
#  parser = argparse.ArgumentParser(description="LDR serial")
#  # add expected arguments
#  parser.add_argument('--port', dest='port', required=True)

#  # parse args
#  args = parser.parse_args()
#  
#  #strPort = '/dev/tty.usbserial-A7006Yqh'
#  strPort = args.port

#  print('reading from serial port %s...' % strPort)

#  # plot parameters
#  analogPlot = AnalogPlot(strPort, 1000)

#  print('plotting data...')

#  # set up animation
#  fig = plt.figure()
#  ax = plt.axes(xlim=(0, 1000), ylim=(-1000, 1000))
#  a0, = ax.plot([], [])
#  a1, = ax.plot([], [])
#  a2, = ax.plot([], [])
#  anim = animation.FuncAnimation(fig, analogPlot.update, fargs=(a0, a1, a2), interval=10)

#  # show plot
#  plt.show()
#  
#  # clean up
#  analogPlot.close()

#  print('exiting.')
#  

## call main
#if __name__ == '__main__':
#  main()
