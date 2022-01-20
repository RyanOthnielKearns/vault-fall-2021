#ENGR40M #ENGR #Stanford #Stanford-Winter-2022 #lecture-notes 
___
See [[ENGR 40M Course Reader.pdf]] 4 - 4.1.2

# Learning Objectives
- **switches**: new electrical devices that convert mechanical motion to an electrical charge
	- nomenclature: poles and throws
- **motors**: converts mechanical to electrical energy and vice versa

# Switches
- uses some mechanical change to change the conductivity between terminals
- "off" state: open circuit
- "on" state: short circuit

## Throws
- the number of different connections that are possible
- 1 (single throw: ST) or 2 (double throw: DT) most common

## Poles
- the number of different switches that are mechanically linked together
	- completely separate in terms of electrical connection
	- but the paths are coupled -- have to align
- 1 (single pole: SP) or 2 (double pole: DP) most common

- our red switch has 6 leads: meaning it must be a DPDT
	- put your DMM on resistance (or connectivity) mode to check which leads are which
	- top left lead is #1, which is the second throw of the first pole (top right on the diagram)
![[switch.png]]

## Switches with default positions
- throws are labeled $C\ (\text{common})\rightarrow NC\text{ (normally closed) } / NO\text{ (normally open)}$
- some switches stay in the position you set (light switches), and some switch back to a default position when not pressed (keyboards)

# Motors
- same thing as a generator
- has a mechanical output -- output affects the *current* and *voltage*
	- current depends on how much mechanical power (work) is being provided
	- larger load (mechanical work = force x distnace) requires more current
- can model by a *voltage source + a resistor*
	- voltage of the source depends on motor speed
		- $V_m = k\cdot rpm$ ($k$ is different for different motors)
	- force (torque) of the motor depends on the current

## ==these are answers to prelab questions==
- if you put your hand on the motor to try and stop it, the current through the device will *increase* due to the extra work being done to turn
- if you reverse the voltage polarity, motor will turn in the opposite direction