#ENGR40M #ENGR #Stanford #Stanford-Winter-2022 #lecture-notes 
[[ENGR 40M Module 48 - Filters with Inductors|Prev]] | [[ENGR 40M Module 50 - Voltage Conversion - Buck Converter|Next]]
See [[ENGR 40M Course Reader.pdf|Reader 9.3]]
___
# Learning Objectives
- be able to solve for currents / voltages in inductor circuits
	- understand how to generate voltage above & below supplies
	- key: $\frac{V}{L} = \frac{di}{dt}$
- time behavior of LR circuits is exponential
	- time constant is $\frac{L}{R}$ (compared to $RC$ for capacitors)
___
# Inductor Circuits with LEDs
- pulses when inductors supply current: higher in voltage <-> shorter in width (because $\frac{di}{dt}$ is higher when $V$ is higher)
	- e.g., when inductor has to supply forward voltage of 2 or 3 LEDs instead of just 1
	- as the voltage across the inductor gets bigger, the amount of time that the inductor can supply that voltage *decreases*
		- same thing is true for inductor-resistor circuits -- this is why time constant = $L / R$
	- with no LEDs -- inductors can generate really large voltages to keep $i_L$ constant (~100V)
		- after ~100V supplied to one end of a transistor, it opens and provides a path

# RL Circuits
- if $i_L=0$ before the transistor turns on, it must remain $0$ after transistor turns off, because current through an inductor can't change instantaneously
- then: $\frac{V_{dd}}{L} = \frac{di}{dt}$
- time constant for RL circuits: $\Delta t = \frac{L}{R}$
	- for any current in the circuit, the voltage we generate will be proportional to $R$ -> the more voltage we generate the shorter the time
	- get an exponential for rising current
- inductors are kinda opposite to capacitors -- in RL circuits, current is continuous and you have voltage spikes; whereas in RC circuits, voltage is continuous and you have current spikes
	- **RL Circuits: current continuous**, voltage can spike
	- **RC Circuits: voltage continuous**, current can spike