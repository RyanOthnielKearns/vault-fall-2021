#ENGR40M #ENGR #Stanford #Stanford-Winter-2022 #lecture-notes 
___
- node voltages + linear equations to solve for unknown node voltages / currents
	- instead of plots! 😊

# Learning objectives
- solve for unknown nodal voltages
	- use KCL to generate linear equations, then solve

# General Solution Method
1. Label all nodes ($V_A, V_B, \dots$) after choosing a reference (ground) node
2. Label all device currents ($i_1$, $i_2$, $\dots$)
3. Write KCL equations for every node with unknown voltage
	- Sum of currents into each node must equal current out of node
4. Use device i-V to relate device currents to node voltages
	- also device equations, e.g. $i_R = V_R / R$
5. Solve remaining linear equations

- answers will be the same regardless of the references you choose for different devices' positive / negative terminals
	- just remember that current *always* flows into the positive terminal of the device!