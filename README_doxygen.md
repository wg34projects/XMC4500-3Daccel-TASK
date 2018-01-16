# XMC4500 acceleration sensor task - Werner Egermann, Helmut Resch - BEL3

| XMC uC Infineon |
|--------------------|
| ![alt text](../../pictures/xmc.png "XMC") |

# project description

## definition of task

https://cis.technikum-wien.at/documents/bel/3/ess/semesterplan/tasks/tasks.html

| screenshot task description |
|------------------------------------|
| ![alt text](../../pictures/taskdescriptionCIS.png "PWM calculations") |

## realized task

The realized task is generic and a "proof of concept" for possibilities with the **Adafruit LIS3DH Triple-Axis Accelerometer** sensor.

As described in the definition the task is split into 2 major parts, the uC software for the Infineon XMC4500 and the GUI for the PC realized with GTK-3 + C and Python 3 + Pygame + Matplotlib.

The uC software includes a simple (bidirectional) UART communication protocol, libraries + drivers for:

- I2C communication
- sensor communication
- servocontrol
- buttons + LED control

Raw data from the accelerometer, 6D position and statistics can be requested by the PC application. The values are shown on the GUI. The rotation angles for all 3 axes and the pitch and roll angle are calculated within the PC application and shown on the GUI, also a simple freefall detection is included.

Within the GUI a statistic package (sent sensor readings, data packages, errors) can be requested, the data can be logged to harddisk, triggers for acceleration can be set and various settings like:

- activating UART connection
- requesting data from sensors
- activating servos
- changing between measurement averaging and "thresholding" for servo 

can be done.

A simple wooden construction with 2 servos reflect the pitch and roll angle of the sensor. Details therefor find below (calculation of angles according documents from ST Microelectronics).

Both values are **calculated at the uC** and used to determine the PWM settings - find below more details.

BUTTON1 is used to switch on/off the servos and BUTTON2 is used to choose averaging / thersholding of sensor values for servo setting.

Buttons are **not "linked" direct at the uC** with the functions - the entry is sent to the GUI via the protocol and a control command is sent back to the uC.

LED1 represents the PWM "percentage" of one servo, LED2 is on when GUI and XMC are connected, and toggles according when data is requested by the GUI.

2 python scripts can be started from the GUI, one to show possibilities for sprite rotation with the pygame library and one to show a graph for the accelerations.

## communication protocol

A simple UART protocol has been implemented, all control can also be done via a terminal like CuteCom

| command PC to XMC | description |
| ----------------- | ----------- |
| #CON,             | connect to XMC - LED2 is ON |
| #END,             | disconnect XMC - LED2 is OFF |
| #REQ,             | request data package from XMC, this can be acceleration, statistics or buttonpress |
| #SER,n		    | turns servos ON |
| #SER,f		    | turns servos OFF |
| #AVG,p		    | servo average value averaging (PWM) |
| #AVG,a		    | servo average value thresholding (angle) |
| #STA,			    | request statistic package from XMC

<br>

| command XMC to PC | description |
| ----------------- | ----------- |
| #XXX,-16000,-16000,-16000$ | standard answer to #REQ, with raw values acceleration |
| #STA,      1000,  0,      5000$ | answer on #REQ, if #STA, was requested, sent packages, errors, sensor readings |
| #BUT,1$ | answer on #REQ, if Button1 has been pressed |
| #BUT,2$ | answer on #REQ, if Button1 has been pressed |

<br>

| screenshot cutecom |
|--------------------|
| ![alt text](../../pictures/cutecom.png "cutecom") |

## logging function

When data is transmitted and a description of logfile is given in the correct entry, the SAVE button will appear.

Data is stored in the attached format

| epoch time | day | day | month | year | time HH.MM.SS.US | 6D diretion | accel X | accel Y | accel Z | angle X | angle Y | angle Z | pitch angle | roll angle |
|----------- | --- | --- | ----- | ---- | ---------------- | ----------- | ------- | ------- | ------- | ------- | ------- | ------- | ----------- | -----------|
| 1516031796 | Montag | 15 | Jänner | 2018 | 16:56:36.930526 | BOT | -0,283272 | 0,634921 | -0,650549 | -1,654695 | 3,710879 | -3,802356 | -17,308067 | 41,822962 |

## 6D direction description and calculation of angles

| tri-axis tilt sensing |
|-----------------------|
| ![alt text](../../pictures/tilt.png "tilt") |

<br>

| 6D positions |
|-----------------------|
| ![alt text](../../pictures/6D.png "6D") |

# XMC software

## folders and files

The code is located in the folders 

* /src/ - all C source files
* /inc/ - all C header files

Details find in section "Files" in the doxygen documentation and further details are commented inside the source code.

## description

The graph shows the app > library > driver structure of the uC source code.

| dependency graph |
|------------------|
| ![alt text](../../pictures/dependency_graph_XMC.png "XMC software") |

The graph shows the function calls of the uC source code.

| functions graph |
|-----------------|
| ![alt text](../../pictures/function_graph_uc.png "uC software") |

## settings for the hardware PWM and angle correction of sensor

| calculations for PWM signal servos and necessary settings for counter and prescaler |
|------------------------------------|
| ![alt text](../../pictures/PWM_servo_calc.png "PWM calculations") |

<br>

| calculation for angle correction sensor |
|-----------------------------------------|
| sensor „Resch“ shows pitch angle up to maximum 85° - other direction seems ok with minimum -89° |
| correction value linear from 0 to +85° >> 0 up to +4.5 >> pitch = pitch + pitch * (4.5/85) |
| after calibration of servo and correction of sensor the pulse length and the frequency are stable |

## used registers sensor

I2C adress sensor (7 bit) = 0x18

initialisation sensor

| description | function | register adress | remark |
| ----------- | -------- | --------------- | ------ |
| set ODR (turn ON device) | LIS3DH_SetODR(LIS3DH_ODR_100Hz) | CTRL_REG1 0x20 | operation mode 100 Hz chosen |
| set PowerMode | LIS3DH_SetMode(LIS3DH_NORMAL) | CTRL_REG4 0x20 and CTRL_REG4 0x23 | normal power mode chosen 10 bit |
| set Fullscale | LIS3DH_SetFullScale(LIS3DH_FULLSCALE_4) | CTRL_REG4 0x23 | 4g maximum range chosen |
| set axis Enable | LIS3DH_SetAxis(LIS3DH_X_ENABLE LIS3DH_Y_ENABLE LIS3DH_Z_ENABLE) | CTRL_REG1 0x20 | all axes active |


interrupt configuration sensor 6D

| description | function | register adress | remark |
| ----------- | -------- | --------------- | ------ |
| set Interrupt Threshold | LIS3DH_SetInt1Threshold(20) | INT1_THS 0x32 | threshold 20 for 6D sensing |
| set Interrupt configuration (all enabled) | LIS3DH_SetIntConfiguration(LIS3DH_INT1_ZHIE_ENABLE LIS3DH_INT1_ZLIE_ENABLE LIS3DH_INT1_YHIE_ENABLE LIS3DH_INT1_YLIE_ENABLE LIS3DH_INT1_XHIE_ENABLE LIS3DH_INT1_XLIE_ENABLE ) | INT1_CFG 0x30 | 6D all axes |
| set Interrupt Mode | LIS3DH_SetIntMode(LIS3DH_INT_MODE_6D_POSITION | INT1_CFG 0x30 | enable 6D sensing |


data request from sensor

| description | function | register adress | remark |
| ----------- | -------- | --------------- | ------ |
| request 6D position interrupt | LIS3DH_Get6DPosition(&position) | INT1_SRC 0x31 | interrupt register 6D sensing |
| request raw acceleration data| LIS3DH_GetAccAxesRaw(&data) | OUT_X_L 0x28 OUT_X_H 0x29 OUT_Y_L 0x2A OUT_Y_H 0x2B OUT_Z_L 0x2C OUT_Z_H 0x2D | MSB and LSB of acceleration, concatenation results in 2's complement of acceleration |

## various defines in header files

Please refer to the comments inside the code of header files.

## external code

- lis3dh_driver.c and lis3dh_driver.h provided by ST Microelectronics
- xmc4500_i2c_lib.c and xmc4500_i2c_lib.h provided by FHTW
- xmc4500_uart_lib.c and xmc4500_uart_lib.h provided by FHTW
- debug_lib.c and debug_lib.h provided by FHTW
- Makefile provided by FHTW

Thanks for this support!

## testing

### Source code test with cppcheck, only minor comments, external code excluded

	cppcheck --enable=all --std=posix --std=c99 --force --template=gcc ./inc/3Daccel_app.h ./inc/3Daccel_out_driver.h ./inc/3Daccel_out_library.h ./inc/lis3dh_library.h ./inc/servo_driver.h ./inc/servo_library.h ./src/3Daccel_app.c ./src/3Daccel_out_driver.c ./src/3Daccel_out_library.c ./src/lis3dh_library.c ./src/servo_driver.c ./src/servo_library.c

	Checking inc/3Daccel_app.h ...
	1/12 files checked 0% done
	Checking inc/3Daccel_out_driver.h ...
	2/12 files checked 3% done
	Checking inc/3Daccel_out_library.h ...
	3/12 files checked 10% done
	Checking inc/lis3dh_library.h ...
	4/12 files checked 13% done
	Checking inc/servo_driver.h ...
	5/12 files checked 14% done
	Checking inc/servo_library.h ...
	6/12 files checked 16% done
	Checking src/3Daccel_app.c ...
	Checking src/3Daccel_app.c: DEBUG...
	7/12 files checked 30% done
	Checking src/3Daccel_out_driver.c ...
	8/12 files checked 38% done
	Checking src/3Daccel_out_library.c ...
	src/3Daccel_out_library.c:63: style: The scope of the variable 'ticks' can be reduced.
	src/3Daccel_out_library.c:65: style: The scope of the variable 'i' can be reduced.
	src/3Daccel_out_library.c:66: style: The scope of the variable 'smoothSignal1' can be reduced.
	src/3Daccel_out_library.c:66: style: The scope of the variable 'smoothSignal2' can be reduced.
	Checking src/3Daccel_out_library.c: DEBUG...
	9/12 files checked 70% done
	Checking src/lis3dh_library.c ...
	10/12 files checked 85% done
	Checking src/servo_driver.c ...
	11/12 files checked 96% done
	Checking src/servo_library.c ...
	12/12 files checked 100% done
	src/3Daccel_out_library.c:61: style: The function 'SysTick_Handler' is never used.
	:: information: Cppcheck cannot find all the include files (use --check-config for details)

### Source code test with splint, only minor comments, external code excluded

splint +posixlib -unrecog -standard +trytorecover -preproc -predboolint +matchanyintegral -exportlocal ./inc/3Daccel_app.h ./inc/3Daccel_out_driver.h ./inc/3Daccel_out_library.h ./inc/lis3dh_library.h ./inc/servo_driver.h ./inc/servo_library.h ./src/3Daccel_app.c ./src/3Daccel_out_driver.c ./src/3Daccel_out_library.c ./src/lis3dh_library.c ./src/servo_driver.c ./src/servo_library.c 

	Splint 3.1.2 --- 04 Aug 2017

	src/lis3dh_library.c: (in function initMEMSsensor)
	src/lis3dh_library.c:60:31: Function LIS3DH_SetAxis expects arg 1 to be
		LIS3DH_Axis_t gets enum { LIS3DH_X_ENABLE, LIS3DH_X_DISABLE,
		LIS3DH_Y_ENABLE, ..., LIS3DH_Z_DISABLE }:
		LIS3DH_X_ENABLE | LIS3DH_Y_ENABLE | LIS3DH_Z_ENABLE
	  Types are incompatible. (Use -type to inhibit warning)
	src/lis3dh_library.c: (in function configMEMSsensor)
	src/lis3dh_library.c:86:32: Function LIS3DH_SetInt1Threshold expects arg 1 to
		                           be u8_t gets int: 20
	src/lis3dh_library.c: (in function get6Dposition)
	src/lis3dh_library.c:136:37: Function LIS3DH_Get6DPosition expects arg 1 to be
		                            u8_t * gets uint8_t *: &position
	src/lis3dh_library.c: (in function getAxesRawData)
	src/lis3dh_library.c:206:37: Passed storage data contains 3 undefined fields:
		                            AXIS_X, AXIS_Y, AXIS_Z
	  Storage derivable from a parameter, return value or global is not defined.
	  Use /*@out@*/ to denote passed or returned storage which need not be defined.
	  (Use -compdef to inhibit warning)

	Finished checking --- 4 code warnings

2 functions in 3D_accel_out_driver.c had to be excluded for splint to avoid parse errors

	void outputInitXMC(void)
	{
		XMC_GPIO_CONFIG_t config_out;
		config_out.mode = XMC_GPIO_MODE_OUTPUT_PUSH_PULL;
		config_out.output_level = XMC_GPIO_OUTPUT_LEVEL_LOW;
		config_out.output_strength = XMC_GPIO_OUTPUT_STRENGTH_WEAK;
		XMC_GPIO_Init(LED1, &config_out);
	}

	void inputInitXMC()
	{
		XMC_GPIO_CONFIG_t config_in;
		config_in.mode = XMC_GPIO_MODE_INPUT_INVERTED_PULL_UP;
		XMC_GPIO_Init(BUTTON1, &config_in);
		XMC_GPIO_Init(BUTTON2, &config_in);
	}

# XMC hardware

## description

* /sensordocu/ - available documentation from ST Microelectronics

<br>

- sensor is connected via I2C and 3V3 to XMC, see lis3dh driver.c and lis3dh driver.h regarding used pins and hardware adress.

| sensor |
|--------|
| ![alt text](../../pictures/sensor.png "picture sensor") |

- XMC connector includes 4k7 pullup resistors for I2C, signal and power connections, terminal blocks for external 5V power source (for servos) and terminal blocks to connected signals and power.

| XMC connector |
|---------------|
| ![alt text](../../pictures/XMCconnector.png "XMC connector") |

- external power source

The servos are supplied by an external 5V power source.

| power |
|-------|
| ![alt text](../../pictures/power.png "power") |

- servos

Simple analog servos from Conrad used for the hardware.

| servos |
|--------|
| ![alt text](../../pictures/servo.png "servos") |

- big picture

Simple wooden construction for the servos.

| big picture |
|-------------|
| ![alt text](../../pictures/viewall.png "bigpicture") |

## testing

Oscilloscope screenshots of PWM signal.

| -90° / 0° | 0° | +90° / 180° |
|-----------|----|-------------|
| ![alt text](../../pictures/PWM3.png "PWM 3%") | ![alt text](../../pictures/PWM7.png "PWM 7%") | ![alt text](../../pictures/PWM12.png "PWM 12%") |

# PC GUI software

## folders and files

The code is located in the folders 

* /gtk_GUI/ - all GTK GUI C source and header files
* /python/ - all PYTHON scripts as mentiond in the description and all necessary pictures
* /pictures/ - all pictures for README.md file

Details find in section "Files" in the doxygen documentation and further details are commented inside the source code.

## description

Graph of all GUI function calls.

| functions graph |
|-----------------|
| ![alt text](../../pictures/function_graph_GUI.png "GUI software") |

## various defines in header files

Please refer to the comments inside the code of header files.

## GUI overview

| GUI overview after start |
|--------------------------|
| ![alt text](../../pictures/GUI_screenshot_start.png "GUI view start") |

| GUI description |
|-----------------|
| ![alt text](../../pictures/GUI_screenshot_commented.png "GUI view commented") |

(0) Highlights values which have to be set before connection...

(1) Connect...

(2) Start transmission...

GTK buttons are set active or inactive as needed, feel free to experiment!

## experimental freefall detection

Within the PC application a simple freefall detection, following the graph shown below is included.

| freefall algorithm  |
| ------------------- |
| ![alt text](../../pictures/freefall.png "freefall") |

## external code

- rs232.c and rs232.h provided by FHTW
- Makefile provided by FHTW

Again thanks!

### testing

For the GTK GUI only cppcheck done.

	cppcheck --enable=all --std=posix --std=c99 --force --template=gcc 3DacceltaskGUI.c 3DacceltaskGUI.h menucallbacks.c menucallbacks.h

	Checking 3DacceltaskGUI.c ...
	Checking 3DacceltaskGUI.c: __FreeBSD__;__linux__...
	1/4 files checked 25% done
	Checking 3DacceltaskGUI.h ...
	Checking 3DacceltaskGUI.h: __FreeBSD__;__linux__...
	2/4 files checked 29% done
	Checking menucallbacks.c ...
	menucallbacks.c:496: style: The scope of the variable 'mode' can be reduced.
	menucallbacks.c:499: style: The scope of the variable 'requestConnection' can be reduced.
	menucallbacks.c:568: style: The scope of the variable 'requestServoOn' can be reduced.
	menucallbacks.c:605: style: The scope of the variable 'requestAveragePWM' can be reduced.
	Checking menucallbacks.c: __FreeBSD__;__linux__...
	3/4 files checked 95% done
	Checking menucallbacks.h ...
	Checking menucallbacks.h: __FreeBSD__;__linux__...
	4/4 files checked 100% done
	:: information: Cppcheck cannot find all the include files (use --check-config for details)

# Conclusion

Interesting and demanding task - especially the GUI.

Statistic of source code - total 3177 code lines without external code as mentioned above.

	wc ./inc/3Daccel_app.h ./inc/3Daccel_out_driver.h ./inc/3Daccel_out_library.h ./inc/lis3dh_library.h ./inc/servo_driver.h ./inc/servo_library.h ./src/3Daccel_app.c ./src/3Daccel_out_driver.c ./src/3Daccel_out_library.c ./src/lis3dh_library.c ./src/servo_driver.c ./src/servo_library.c ./gtk_GUI/3DacceltaskGUI.c ./gtk_GUI/3DacceltaskGUI.h ./gtk_GUI/menucallbacks.c ./gtk_GUI/menucallbacks.h -l

	   17 ./inc/3Daccel_app.h
	   35 ./inc/3Daccel_out_driver.h
	   72 ./inc/3Daccel_out_library.h
	   43 ./inc/lis3dh_library.h
	   28 ./inc/servo_driver.h
	   22 ./inc/servo_library.h
	  191 ./src/3Daccel_app.c
	  116 ./src/3Daccel_out_driver.c
	  424 ./src/3Daccel_out_library.c
	  219 ./src/lis3dh_library.c
	  100 ./src/servo_driver.c
	   62 ./src/servo_library.c
	  372 ./gtk_GUI/3DacceltaskGUI.c
	   83 ./gtk_GUI/3DacceltaskGUI.h
	 1308 ./gtk_GUI/menucallbacks.c
	   88 ./gtk_GUI/menucallbacks.h
	 3180 insgesamt

# Improvements

- GUI GTK code enhancement with respect to memory leaks
- uC code enhancement for example with Interrupts instead of SysTick_Handler and Watchdog
- better and more stable hardware setup - for example with acrylic glas instead wooden construction
- better implementation of Python scripts start - end
- sometimes troubles when GUI is started via doubleklick in filemanager - environment path - install
- improving shutdown possibility with GTK shutdown signal (not working!?!)
- adding CTRL-C feature GUI
- including updated I2C driver as provided in CIS
- usage of the hardware freefall detection instead software solution
- ... and 1000 other ideas ...
