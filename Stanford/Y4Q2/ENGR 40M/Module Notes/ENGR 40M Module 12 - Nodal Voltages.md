#ENGR40M #ENGR #Stanford #Stanford-Winter-2022 #lecture-notes 
___
- voltages between two nodes in a circuit
- define a reference node (ground) and define node voltages as potential difference (to the reference node)
- *device voltages*: voltage across a device (e.g. voltage across a battery is $1.5 V$)
- [[202201041817 ENGR 40M Module 4 - Voltage|voltage]] is the difference in potential between two nodes
	- so can choose a node as our reference
		- voltage difference between reference and reference is always 0
		- switching from device voltages to node voltages can reduce the number of unknown parameters in a circuit! since there are often fewer node voltages
		- pick node connected to the most devices as your reference

# Device Voltages from Node Voltages
- current through a device depends on device voltage
- device voltage is $V_a - V_b$ if device has $+$ terminal connected to node $a$, and $-$ terminal connected to node $b$

# Ground
- including special schematic symbols on a circuit
![[Davis_ground_1.jpeg]]
# Implicit Power Supplies
- using symbol $T$
	- symbol represents the voltage relative to ground
	- the $T$ on the circuit is the positive terminal; negative goes to ground
- label is the voltage
- sort of shorthand for a power supply