import pygame
import sys
import os
import serial
import time
import math

temp0 = []
temp1 = []
temp2 = []
temp3 = []
temp4 = []

accelX = 0
accelY = 0
accelZ = 0
pitch = 0
roll = 0
i = 0

usbConnection = ["/dev/ttyUSB0", "/dev/ttyUSB1", "/dev/ttyUSB2", "/dev/ttyUSB3", "/dev/ttyUSB4"]

def stringCutter():

	global accelX, accelY, accelZ, orientation, pitch, roll

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

		pos_e = temp3.index('$')
		accelZ = int(temp3[:pos_e]) / 8190.0

		pitch = math.atan(accelX/(math.sqrt((accelY*accelY)+(accelZ*accelZ)))) * 180 / 3.141592654
		roll = math.atan(accelY/(math.sqrt((accelX*accelX)+(accelZ*accelZ)))) * 180 / 3.141592654

		pitch = round(pitch, 2)
		roll = round(roll, 2)

	except AttributeError as Ae:
			
		pass

	except TypeError as Te:
			
		pass

	except Exception as e:
			
		pass

class Roll(pygame.sprite.Sprite):

    def __init__(self):
        pygame.sprite.Sprite.__init__(self)
        self.imageMaster = pygame.image.load("../python/jetski_rotate.png")
        self.imageMaster = self.imageMaster.convert()
        self.image = self.imageMaster
        self.rect = self.image.get_rect()
        self.rect.center = (160, 240)
        self.dir = 0

    def update(self):
        oldCenter = self.rect.center
        self.image = pygame.transform.rotate(self.imageMaster, self.dir)
        self.rect = self.image.get_rect()
        self.rect.center = oldCenter

    def turnroll(self):

        global roll

        self.dir = roll

class Pitch(pygame.sprite.Sprite):

    def __init__(self):
        pygame.sprite.Sprite.__init__(self)
        self.imageMaster = pygame.image.load("../python/car_pitch.png")
        self.imageMaster = self.imageMaster.convert()
        self.image = self.imageMaster
        self.rect = self.image.get_rect()
        self.rect.center = (460, 240)
        self.dir = 0

    def update(self):
        oldCenter = self.rect.center
        self.image = pygame.transform.rotate(self.imageMaster, self.dir)
        self.rect = self.image.get_rect()
        self.rect.center = oldCenter

    def turnpitch(self):

        global pitch

        self.dir = pitch
		
def main():

	screen = pygame.display.set_mode((640, 480))	
	pygame.display.set_caption("BEL3 Acceleration Sensor Resch + Egermann")
	background = pygame.Surface(screen.get_size())
	background.fill((0, 0, 0))
	sprite1 = Roll()
	sprite2 = Pitch()
	allSprites = pygame.sprite.Group(sprite1)
	allSprites.add(sprite2)
	clock = pygame.time.Clock()
		
	keepGoing = True

	while keepGoing:

		stringCutter()

		print ("pitch = ", pitch, "°")
		print ("roll  = ", roll, "°")

		clock.tick(30)

		for event in pygame.event.get():

			if event.type == pygame.QUIT:

				keepGoing = False

		sprite1.turnroll()
		sprite2.turnpitch()
       
		allSprites.clear(screen, background)
		allSprites.update()
		allSprites.draw(screen)
		pygame.display.flip()

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

		pygame.init()

		main()

	except KeyboardInterrupt:

		print("\nstop after keyboard interrupt\n")
