# MotionSensor

Instructions for firmware installation:

Before starting, make sure that the battery is connected to the arduino and the arduino is connected to the computer with the USB cable. MAKE SURE that the battery is connected before you plug in the USB cable. Otherwise, the arduino will try to power the Adafruit Bluefruit module over USB, and that particular board requires too much power for this to be possible. Nothing will break if you end up forgetting to plug in the battery, but the arduino will start to act funny.

1) Download folders Adafruit_LSM9DS0_Library and Adafruit_Sensor, and put them in your arduino sketchbook/libraries directory. This directoy can be found in many different places, but for me it is in my home directory.

2) Download flora9dof.ino, and put that in your aduion sketchbook directory. Open the arduino IDE and load this sketch.

3) Hook up the arduino on the motion sensor device using a USB cable to your computer, and try to compile/upload the flora9dof.ino sketch.

4) To test that this worked, open the serial connection monitor and set the baud rate to either 9600 or 115200. Which one you will need to use will depend on how the jumpers are connected on the arduino, but you can try 9600 first and if the serial monitor spits out a bunch of garbage then try 115200 next.


Instructions for bluetooth installation:

Before beginning, again make sure that the battery is plugged into the arduino. The Adafruit Bluefruit module should light up. In the box of hardware, there should be a tiny bluetooth USB module, plug this into your computer. It is necessary to use this USB module, because it supports the latest version of bluetooth, and this version is what is required for the Adafruit Bluefruit module. If your laptop or whatever you're using happens to have the latest version of bluetooth, it may be possible to not use this USB bluetooth module.

If you are on linux, you should install the blueman bluetooth UI. Using blueman, try to discover the Arduino device. You may need to play around with blueman, but it should be possible to have blueman assign a serial port connection to the Adafruit Bluefruit module. On my machine, blueman assigns the module to /dev/rfcomm0 or /dev/rfcomm1. This serial device can be accessed like any other serial port. However, the bluefruit module is slow, and can only support a baud rate of 9600. Make sure that the headers on the arduino are set so that it will use the 9600 baud rate, otherwise the bluefruit module will just spit out a bunch of garbage over the serial connection.
