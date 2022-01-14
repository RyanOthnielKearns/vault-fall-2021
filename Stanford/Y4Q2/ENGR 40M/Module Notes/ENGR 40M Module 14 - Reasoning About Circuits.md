#ENGR40M #ENGR #Stanford #Stanford-Winter-2022 #lecture-notes 
___
# Learning Goals
- use series + parallel combinations to reduce the circuit's complexity
- recognize voltage dividers

# Simplifying the Circuit
- look at **sub-circuits** and replace those components w/ simpler equivalents
	- reduce # of devices / nodes
- can still always solve using nodal analysis!

## Two Resistors in Series
$$R = R_1 + R_2$$
replace with a single resistor with *effective resistance* $R$
- current through devices is the same
- voltage across is the sum of voltages across

## Two Resistors in Parallel
$$\frac{1}{R} = \frac{1}{R_1}+\frac{1}{R_2}$$
$$R = \frac{R_1 * R_2}{R_1+R_2}$$
replace again with resistor with effective resistance $R$
- current across will be the sum of the currents across each in parallel
- voltage across each resistor will be the same

# Voltage Divider
- *any time you have two resistors in series*: what's the ratio of the voltage across just one versus the voltage across the total?
- assume we have current $i$
- what is $\frac{V_2}{V_1}$? where $V_1$ goes across $R_1$ and $V_2$ over $R_2$
	- $\frac{V_2}{V_1} = \frac{R_2}{R_1}$
	- and $V_{tot} = V_1 + V_2$
	- $\frac{V_2}{V_{tot}} = \frac{R_2}{R_1 + R_2}$
	- if there's a voltage source in the circuit with $v_s$:
$$V_{R_2} = v_s *\frac{R_2}{R_1 + R_2}$$
# Current Divider
- what is the ratio of currents?
- e.g. what is $\frac{i_{4k\Omega}}{i_{1k\Omega}}$? $\rightarrow\frac{1}{4}$
	- as my resistance goes up I get more voltage across me, but I get less current across me (current likes to go the easier route)
	- also if two resistors are in parallel, then $i = i_{1k\Omega}+i_{4k\Omega}$
		- $i_{1k\Omega}=i*\frac{4k\Omega}{4k\Omega+1k\Omega}$
		- generally:
$$i_{R_2} = i*\frac{R_1}{R_1 + R_2}$$