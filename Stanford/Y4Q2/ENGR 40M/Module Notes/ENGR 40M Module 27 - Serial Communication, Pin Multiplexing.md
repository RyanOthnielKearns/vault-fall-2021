#ENGR40M #ENGR #Stanford #Stanford-Winter-2022 #lecture-notes 
___
See [[ENGR 40M Course Reader.pdf]] 5.6

# Learning Objectives
- understand transmitting bits on a single wire
	- by transmitting sequentially in time
- common method uses CMOS transistors
	- instead, we'll use LEDs

# LED Array
- control 64 LEDs using just 16 wires!
- a "*pin problem*": occurs with lots of digital devices!
	- e.g. HD screens: 8M pixels, each is RGB
		- but HDMI cable only has 19 wires, but only 6 have data

# Solving the Pin Problem
- requires transmitting more than 1 bit per wire

## Serial Communication
- called "**time-division multiplexing**" or just multiplexing
- USB = universal *serial* bus
- have a string of memory cells, & load each memory cell at the "right" time
	- can build the memory cells using CMOS gates on the receiver -- a kind of integrated circuit
	- but: there are LEDs with this circuitry built in (DotStar, or NeoPixel LEDs)

## Our Pin Problem
- 64 lights requiring at least 64 bits to control their on/off individually
	- with 16 wires.. solve using "*optical persistence*"
		- turn LED on and off really fast, faster than humans can perceive the flickering
	- don't turn all lights on at once -- create a bunch of "time slots" and turn lights on sequentially in those time slots (eyes won't notice that they are actually staggered)

### Our LED Wiring Diagram
5V voltage source --> Vdd --> LED --> 100$\Omega$ resistor --> ground
- put switch between resistors and ground to have the ability to turn LEDs on and off
- can't just do one resistor if connecting LEDs in parallel
	- don't want brightness of LEDs to depend on whether other LEDs are on or not
- now for two rows: divide (stripe) time into two regions
	- during the "on" regions of time, top line is connected to Vdd
	- during "off" regions of time, bottom line is connected to Vdd
	- this only works because the devices are diodes: the line that's not connected becomes an open circuit