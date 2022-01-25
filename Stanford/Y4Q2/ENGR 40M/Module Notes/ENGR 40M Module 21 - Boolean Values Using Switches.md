#ENGR40M #ENGR #Stanford #Stanford-Winter-2022 #lecture-notes 
___
See [[ENGR 40M Course Reader.pdf]] 4.2-4.3

# Learning Goals
Useless box as an introduction to digital logic
- signals (e.g. wires on the useless box) as "binary values" or "boolean signals"
- can perform primitive Boolean operations
- electrically controlled switches = **transistors**

# Useless Box Operation
- motor can be in 3 states: forward, reverse, off
	- voltage set by the position of two switches:
		- switch1: on or off
		- switch2: at limit or not at limit

# Circuits have 2 stable values
- **Vdd**: power supply voltage
- **Gnd**: reference or ground

- like a boolean value in software
	- electrical boolean values are still just *voltages on a circuit* -- can solve using nodal analysis or whatnot
	- **Logical 1**: voltage is high near Vdd
	- **Logical 0**: voltage is low near Gnd

# Simple Boolean Signal
- switch + a resistor
	- switch can be either *connected* or *not connected*
	- when is `Out` a logical one? look at whether voltage at `Out` is Vdd or Gnd
		- e.g. will be logical zero when there is a path from it to ground (if it's after resistor from power supply)