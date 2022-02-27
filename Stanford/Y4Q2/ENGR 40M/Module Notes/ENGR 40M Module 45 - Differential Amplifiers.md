#ENGR40M #ENGR #Stanford #Stanford-Winter-2022 #lecture-notes 
[[ENGR 40M Module 44 - Op-Amp Filters|Prev]] | [[ENGR 40M Module 46 - Noise & EKG Measurement Circuit|Next]]
See [[ENGR 40M Course Reader.pdf|8.3.2]]
___
# Learning objectives
- create an amplifier w/ two user inputs
	- differential amplifier
	- instrumentation amplifier

# Issue for ECG Measurement
- want to connect two leads to a person -> need to measure difference between L1 and L2
- all arrangements we've considered before only amplify the difference between $V_\text{in}$ and Gnd
	- now, we want $V_\text{in}^+$ and $V_\text{in}^-$
		- can't just connect one to Gnd, want them to be very similar to each other

# Differential Amplifier
- have $V_1$ and $V_2$, feeding into $R_1$ and $R_3$ respectively ![[differential-amplifier.png]]
- $R_2$ is the feedback resistor
- output voltage given by the difference between the two inputs, multiplied by the resistor ratio
- feedback equation:
$$V_p - V_n = 0$$
$$V_p = V_2\cdot\frac{R_4}{R_3+R_4} = V_2\cdot\frac{R_2}{R_1+R_2}$$
$$V_n = V_1\cdot\frac{R_2}{R_1 + R_2} + V_\text{out}\cdot\frac{R_1}{R_1 + R_2}$$
$$\Rightarrow V_2\cdot\frac{R_2}{R_1+R_2} - V_1\cdot\frac{R_2}{R_1 + R_2} - V_\text{out}\cdot\frac{R_1}{R_1 + R_2} = 0$$
$$\Rightarrow R_2(V_2 - V_1) = V_\text{out}R_1$$
## Problem: Resistance of Skin Contact Varies
- resistor from L1 and L2 to skin contact resistance
	- means $R_{1,\text{ effective}} = R_1 + R_{1,\text{ contact}}$...
	- a normal differential amp is thus not a good idea! won't get exact values for $R_1$ and $R_3$ to compare

## Solution: Instrumentation Amplifier
- a couple of op-amps, connected in a complicated way
	- used to build the amplifier for our ECG
![[instrumentation-amp.png]]
- $V_\text{in}^+$ and $V_\text{in}^-$ go to positive terminals of two different op-amps
- we can solve this amplifier using the "golden rules" and nodal analysis (from [[ENGR 40M Module 42 - Op-Amps]])
	- first write KCL for the $-$ input of the op-amp
	- then find output voltage that satisfies KCL when the $-$ voltage is equal to the $+$ voltage
$$v_o = \bigg(\frac{80k\Omega}{R_G}+5\bigg)(v_\text{in}^+ - v_\text{in}^-)+v_\text{ref}$$
- can set the gain by setting the value of $R_G$
	- if $R_G\to\infty$, gain will be 5V
	- setting $R_G$ smaller will increase the gain