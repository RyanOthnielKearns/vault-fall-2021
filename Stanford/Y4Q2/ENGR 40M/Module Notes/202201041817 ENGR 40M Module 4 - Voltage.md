#ENGR40M #ENGR #Stanford #Stanford-Winter-2022 #lecture-notes 
___
**Voltage**: measures (electrical potential) energy difference of charge
- sum of voltages across any devices in a loop is 0
	- to do w/ conservation of energy

# Charge "as a fluid"
- current is fluid flow
- fluid in any object is constant
- fluid doesn't move unless it is pushed...
	- what pushes charge to make it move?  a *voltage source*

# Electrical Voltage
- **voltage**: a measure of potential energy per unit charge (between two points)
	- e.g. battery: net charge is zero, but voltage is ~1.5V (for alkaline, ~3.5V for lithium ion)
		- charge on higher energy side will flow through a conducting path to get to lower energy side
			- causes current (charge flowing through the wire)
	- Joules per Coulomb = **Volts**
	- only has meaning as a comparison (btwn two points in a circuit)
		- voltage "at a node" is undefined

## What is a battery?
A chemical pump for charge (electrons)
- pair of chemical reactions pump electrons from anode to cathode
- taking stored chemical energy and producing electrical power

## What does positive mean?
Need reference direction to determine the sign
- just like with current in [[202201041758 ENGR 40M Module 3 - Charge and Current#Labeling Measuring Current]]
- e.g., if you switch the leads on the meter, it will just happily report the opposite voltage from before
- in answers, make sure reference direction is established!

## Kirchhoff's Voltage Law (KVL)
- algebraic sum of the voltages for any closed path must be zero
	- if you go around the loop once, you better end up at the same place (in terms of voltage)
		- difference in potential energy from a node to itself should be zero
	- tricky, need to make sure reference directions for each device align
		- can reverse signs to make reference directions align
		- $- \rightarrow +$ means you *add* the voltage
- any path between two points on a circuit should lead to a consistent answer