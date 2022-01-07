#ENGR40M #ENGR #Stanford #Stanford-Winter-2022 #lecture-notes 
___
- relating current / voltage as a plot, not an equation
- two more terms:
	1. **open circuit**: two nodes with nothing connecting them
	2. **short circuit**: two nodes connected by a wire (so actually just one node)

# All Electrical Device Models
- voltage / current relationship between three types of devices (voltage source, current source, and resistor)
- given unknown device, want to characterize it
	- use our DMM! together with a current source
	- can adjust the current to different levels
	- connect current source to device, forcing a certain current through the device (b/c in series)
	- then measure voltage across the unknown device with a meter
		- adjust current from -9mA to 9mA
		- say voltage is independent of current? $\rightarrow$ **voltage source**
		- say we get a linear relationship with positive slope, intersecting at the origin? $\rightarrow$ **resistor**
			- $R\cdot i = V$ (can calculate resistance of the resistor)
		- say we have a linear relationship with a positive x-intercept? $\rightarrow$ some new kind of device

# General Way to Represent the $i\iff V$ relation
- divide plot into four quadrants
	- Q1: $i+, V+$
		- any device in this quadrant *absorbs energy*
	- Q2: $i+, V-$
		- power is negative in this quadrant $\rightarrow$ devices here are *supplying* energy to the circuit
	- Q3: $i-, V-$
		- any device in this quadrant *absorbs* energy
	- Q4: $i-, V+$
		- power is negative in this quadrant $\rightarrow$ devices here are *supplying* energy to the circuit

## Devices in different quadrants
- **battery** intersects Q1 and Q4
	- in Q1, battery is charging
	- in Q4, battery is discharging (supplying energy)
- **current source**
	- note that $i_d$ is negative from standard reference direction $\rightarrow$ Q3 and Q4
	- Q4: current source is supplying energy to the circuit
	- Q3: current source is "charging"
- **resistor**
	- straight line with positive slope through the origin: strictly Q1 and Q3 $\rightarrow$ always absorbing energy
	- as current per unit voltage is going down, resistance is going up
- **open circuit**
	- you can have whatever voltage you want across it -- will have *no* current ($i = 0$)
	- two terminals are not connected together
	- one solution for what an unknown device could be
- **short circuit**
	- take any current you want, but has 0 voltage
	- a "0-value voltage source"
