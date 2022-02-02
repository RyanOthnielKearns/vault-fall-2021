#ENGR40M #ENGR #Stanford #Stanford-Winter-2022 #lecture-notes 
___
- getting a *varying* voltage into the arduino!
	- uses `analogRead()` command

# Getting Input for our display
- from [[ENGR 40M Module 28 - Driving the LED Display]] we learned how to drive the display
- getting input depends on application
	- displaying music
	- build a game
	- etc. -- have to get that information into Arduino!

# Measuring Analog Voltage
pins A0 - A5 are the *analog pins* that can do this
- `int value = analogRead(measurePin);`
	- return value is just a number! how to relate to actual voltage?
		- $\text{value} = \frac{V_{\text{pin}}}{V_{DD}}*1024$
		- a 10-bit unsigned number
- `analogRead()` takes around $100\mu S$
	- which means we can only do it 10K times / sec. -- computer is not doing anything else on these reads!
	- need to also drive the display when this is happening -- break up the two tasks

# Analog Inputs
- joystick
	- two "wipers" that move along resistors between Vdd and Gnd
		- wipers read voltage based on how far along resistor it is -- basically building a voltage divider with the wiper
	- also a switch that's connected to ground when we push "Select" by holding down the joystick
- audio input

# Analog Output
- true arduino output is digital -- only Vdd or Gnd
- *but*: can change the percentage that output is high to produce an artificial "analog" output
	- this can change the perceived brightness of LEDs b/c human eyes are too slow to notice the blinking
	- e.g. if we delineate 8 timeslots with which to turn LED on/off, we have 8 different brightness levels