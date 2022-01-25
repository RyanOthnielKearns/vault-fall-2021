#Stanford #Stanford-Winter-2022 #ENGR40M #ENGR #lecture-notes 
___
# Q&A Today
- solving circuits with diodes by combining circuit i-V curves
- solving circuits w/ diodes by guess and check -- how to check if something is a contradiction?

# Diode Learning Objectives
- solving for voltages / currents in diode circuits is tricky
	- catch-22 -- need to know voltages / currents to know whether diodes are on or off, but also need to know diode statuses to get the voltages / currents!
	- guess and check
		- if you guess that diode is on, diode becomes a voltage source
			- $V = V_F$
			- if you then calculate that there is positive current flowing *into* the positive terminal of the diode (voltage source) -- meaning diode is *supplying power* -- this is incorrect, and diode must be off
		- if you guess that diode is off, diode becomes an open circuit
			- $V_d < V_F$, otherwise you made a mistake and the diode is actually on

*for class on Friday -- bring lab kit to Zoom because we'll be measuring switches and motors*

- our solar cells are 1W -- so should be getting around 7V and ~130mA in full sunlight

# Switches / Motors Learning Objectives
==TODO== modules :)

# Diode i-V (review)
- for positive current (Q1) the voltage is a straight vertical line
	- looks like a voltage source with voltage of $V_F$ (between 0.3V and 3V)
	- voltage fixed for any current
- for voltages $< V_F$, diode looks like it doesn't exist (*open circuit*)
	- or equivalently 0mA current source

## Solving using graphs
- resistors are lines through the origin with the slope indicating the resistance
- series combinations $\rightarrow$ add curves horizontally, changing voltage with the current held constant

## Solving via educated guess & check
- first assume diode is off: model as a 0mA current source
	- means 0A are flowing through other components in series with the diode
	- with a resistor with no current flowing through -- no voltage drop across it because of $V_R = i\cdot R\rightarrow V_R = 0$
	- so, is the voltage across the diode greater than $V_F$? If so, we've made a mistake and the diode must be on!