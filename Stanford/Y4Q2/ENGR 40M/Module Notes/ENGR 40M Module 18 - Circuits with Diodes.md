#ENGR40M #ENGR #Stanford #Stanford-Winter-2022 #lecture-notes 
___
See [[ENGR 40M Course Reader.pdf|Reader]] section 2.5
# Learning objectives
- solving for voltages / currents is tricky (catch-22, which was discussed in [[ENGR 40M Lecture Notes (2022-01-19)]])
- no catch-22 in the graph method for solving

# Diode iV (review)
- diode looks like a voltage source w/ positive current (with $V = V_F$)
- diode looks like an open circuit / 0mA current source w/ voltages $< V_F$

# Approaches to solving diode circuits
## 1. Create i-V graph of the circuit
- can typically read the answer off the graph
- for components in series
	- for any current value (which will be the same across the series) add up all the voltages according to the i-V curve
	- series order doesn't affect the current!
	- with two diodes in series, if the sum of their voltages is less than the sum of their forward voltages, they're both going to be off
- then just see the voltage / current across the component you've drawn up a graph for, and find the corresponding current / voltage as plotted
## 2. Guess and check
- assume certain diodes are on or off:
	- replace "on" diodes with voltage sources of $V_F$
	- replace "off" diodes with current sources of 0mA
	- if current through the circuit is negative (in the "direction" of the diode), or voltage across diodes are $<V_F$, have to revisit & change assumptions
- strategy
	- assume all diodes are off first --> easy b/c it forces voltage drops across resistors to be zero
	- if you have diodes in parallel and you're going to try with just one of them on, *choose the diode with the lower $V_F$*