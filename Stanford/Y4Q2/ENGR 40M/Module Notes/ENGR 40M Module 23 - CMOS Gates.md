#ENGR40M #ENGR #Stanford #Stanford-Winter-2022 #lecture-notes 
___
See [[ENGR 40M Course Reader.pdf]] 4.5

# Learning Objectives
- use MOS transistors to do logical operations
- tell whether a MOS circuit is a "good" logical circuit
- analyze the logical function of a MOS circuit

# What Makes a Good Logic Circuit?
- want the output value to be **boolean**
	1. meaning Out should *always* be driven to either Vdd or Gnd
	2. also: no direct connection between Vdd and Gnd
- pMOS transistors should be connected to Vdd
- nMOS transistors should be connected to Gnd

## To tell whether a circuit is good
- enumerate all different input value possibilities
	- build a truth table! input(s) could either be at Gnd (0) or Vdd (1)
	- based on the truth table we decide on the logical function being computed
- if the truth table is undefined (e.g. output is not driven to *either* Vdd or Gnd) for any combination of inputs, the circuit is *not* a good gate
	- same if there's ever a case where Vdd connects directly to Gnd
- input sometimes might be a signal and its complement

# Creating a circuit for a given logical function
1. First work out the truth table
2. Then figure out when we want Out = 0
	- with nMOS transistors, if we want out driven to ground when *either* $A$ or $B$ is on -- put two nMOS transistors in parallel
- finally, combine parts