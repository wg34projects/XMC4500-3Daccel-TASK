# XMC4500 acceleration sensor task - Werner Egermann, Helmut Resch - BEL3

## project description

### definition of task

https://cis.technikum-wien.at/documents/bel/3/ess/semesterplan/tasks/tasks.html

| screenshot task description |
|------------------------------------|
| ![alt text](../../pictures/taskdescriptionCIS.png "PWM calculations") |

### realized task

The realized task is generic and a "proof of concept" for some possibilities with
the chosen **Adafruit LIS3DH Triple-Axis Accelerometer**.

As described in the definition the task is split into 2 major parts, the uC 
software for the Infineon XMC4500 and the GUI for the PC realized with GTK-3 + C
and Python 3 + Pygame + Matplotlib.

The uC software includes a simple (bidirectional) UART communication protocol,
libraries + drivers for the I2C communication + sensor communication + servo
control + buttons + LED control.

The raw data from the accelerometer, the 6D position and statistics can be requested by
the PC application and the values are shown on the GUI. The rotation angles for all 
3 axes and the pitch and roll angle are calculated within the PC application and shown on the GUI.

Within the GUI a statistic package (sent data packages, errors) can be requested,
the data can be logged, triggers for acceleration can be set, a simple freefall
detection is included too.

2 python scripts can be started from the GUI, one to show possibilities for
sprite rotation with the pygame library and one to show a graph for the accelerations.

## XMC software

### folders and files

Therefore please refer to section "Files" in the doxygen documentation.

### description

| calculations for PWM signal servos and necessary settings for counter and prescaler |
|------------------------------------|
| ![alt text](../../pictures/PWM_servo_calc.png "PWM calculations") |

| calculation for angle correction sensor |
|-----------------------------------------|
| sensor „Resch“ shows pitch angle up to maximum 85° - other direction seems ok with minimum -89° |

### external code

- lis3dh_driver.c and lis3dh_driver.h provided by ST Microelectronics
- xmc4500_i2c_lib.c and xmc4500_i2c_lib.h provided by FHTW
- xmc4500_uart_lib.c and xmc4500_uart_lib.h provided by FHTW
- debug_lib.c and debug_lib.h provided by FHTW
- Makefile provided by FHTW

Thanks for this support!

### test

Source code test with cppcheck



#### oscilloscope screenshots PWM signal

| -90° / 0° | 0° | +90° / 180° |
|-----------|----|-------------|
| ![alt text](../../pictures/PWM3.png "PWM 3%") | ![alt text](../../pictures/PWM7.png "PWM 7%") | ![alt text](../../pictures/PWM12.png "PWM 12%") |

### comments

## XMC hardware

### schematic drawing

### description

### test

### comments

## PC GUI software

### folders and files

### descriptions

### provided software

### test

### comments
