#ENGR40M #ENGR #Stanford #Stanford-Winter-2022 #lecture-notes 
___
See [[ENGR 40M Course Reader.pdf]] 5.6

# Learning Goals
- driving the 8x8 LED array we'll build
	- resistors on the $-$ lines in the array
	- pMOS transistor drives the $+$ lines in the array
- LEDs light up when the row / column in the LED matrix is logically *low*

# Designing our Board
- rows are the $+$ lines, connecting the positive sides of the diodes
	- can drive two rows high at the same time!
		- each $-$ wire thus drives at most 1 LED at any one time
- need to "drive" it to light up the lights
- $-$ lines are the bottoms of the columns, w/ resistors before ground
- series resistance is about $100\Omega$ total
	- $82\Omega$ from explicit resistor so effectively $\sim 20\Omega$ from pins

## Arduino limitations
- each pin drives around 40mA
	- arduino drives the $-$ wires directly, supported by the resistors that limit current
- whole chip must drive less than 200mA
	- more current than this means the wires become fuses

## Driving the $+$ wires
- need something to connect to Vdd; but doesn't need to drive to Gnd
	- can set up a pMOS transistor to drive from Vdd! One on each of the rows -- inputs of the gates go to the arduino
	- since using a pMOS, should drive 7 outputs HIGH and 1 output LOW, turning that one row of LEDs on