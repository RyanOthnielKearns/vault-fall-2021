#ENGR40M #ENGR #Stanford #Stanford-Winter-2022 #lecture-notes 
[[ENGR 40M Module 42 - Op-Amps|Prev]] | [[ENGR 40M Module 44 - Op-Amp Filters|Next]]
See [[ENGR 40M Course Reader.pdf|Reader 8.2 - 8.3.1]]
___
# Learning Objectives
- recognize / analyze different op-amp circuits
	- non-inverting / inverting amplifiers
	- summing amplifiers

# Approach to solving Op-Amp Circuits
- check to make sure the *feedback is negative*
	- want feedback signal from output to eventually get to $-$ input
	- if not, stop!
- then: find output voltage that will make input difference 0
	- assume $V_n = V_p$
	- find $V_\text{out}$ s.t. KCL holds

## Another approach
find general feedback equation:
$$\beta V_\text{in} + \alpha V_\text{out} = \text{err}$$
- given error set to zero:
$$V_\text{out} = -\frac{\beta}{\alpha}V_\text{in}$$
# Types of Op-Amps
## Non-inverting amplifier
- voltage source goes directly into $+$ input terminal
- "non-inverting" b/c when $V_p$ is positive, $V_\text{out}$ is positive too

$$V_\text{out} = \frac{R_1 + R_2}{R_2}\cdot V_\text{in}$$
## Inverting amplifier
- both input *and* output connect to $-$ terminal, and $V_p$ goes to Gnd
- $V_p = 0$
- $V_n = V_\text{in}\cdot\frac{R_f}{R_s + R_f} + V_\text{out}\cdot\frac{R_s}{R_s + R_f}$ (resistor for feedback loop, and resistor between $-$ terminal and voltage source)
	- 2 voltage dividers
- now we assume that $V_n = 0$
$$V\text{out} = -V_\text{in}\cdot\frac{R_f}{R_s}$$
- gain equal to the ratio of those two resistors
- another way to solve:
	- $V_p = 0\to V_n = 0$
	- $\frac{V_\text{in}}{R_s} = i_1 = i_2 = \frac{0V - V_\text{out}}{R_f}$
		- $i_1$ flows from $R_s$ to $V_n$ node, and $i_2$ flows from $V_n$ into $R_f$
	- $V\text{out} = -V_\text{in}\cdot\frac{R_f}{R_s}$

## Summing Amplifier
- can have *two* input voltages to the $-$ terminal, $V_1$ and $V_2$
	- actually an inverting amplifier w/ multiple inputs
- $i_1 = \frac{V_1}{R_1}$
- $i_2 = \frac{V_2}{R_2}$
- $i_3 = i_1 + i_2$ (flowing into $V_n$ node)
$$V_\text{out} - R_f\bigg(\frac{V_1}{R_1} + \frac{V_2}{R_2}\bigg)$$

## Current-to-Voltage Converter
$$V_\text{out} = -i_s\cdot R_f$$

# Does Load Resistance Change the Output?
- e.g., adding a resistor between $V_\text{out}$ and Gnd
- does this change the result? *no*
	- b/c current flowing through that resistor doesn't change the output voltage at that output node