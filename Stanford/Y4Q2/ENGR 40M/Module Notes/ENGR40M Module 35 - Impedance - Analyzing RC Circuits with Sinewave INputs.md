#ENGR40M #ENGR #Stanford #Stanford-Winter-2022 #lecture-notes 
___
See [[ENGR 40M Course Reader.pdf]] 7.3

Handling tricky question from last video:
- Measure $V_\text{out}$ between a capacitor and resistor between $V_\text{in}$ and Gnd, when $V_\text{in}$ goes from 0V to 5V
this was solved in [[ENGR 40M Lecture Notes (2022-02-09)|class]]!

# Learning Objectives
- solve RC circuits without using differential equations
	- look at response of the circuit to *each tone*
- for sinewave input, **capacitor looks like a resistor**
	- resistance depends on the frequency of the tone
- effective resistance called **impedance**

# How to solve complex capacitor circuits?
- directly solving for the output w/ time/frequency graph
	- requires computer
	- output will be "another squiggly line"
- what about solving using *sinewaves*?
	- **superposition** to the rescue
		- add the results of all the sinewaves together -- result is the output waveform
	- start with *zero frequency tone* -- DC power supplied to circuit

## At Zero Frequency
- direct current analysis: capacitors have no current, so *ignore*
	- solve circuit using any method you like, after capacitors become open circuits

## Now look at different tones
- AC analysis
	- set all zero frequency sources to 0
	- drive input with *one tone* (a sinewave)
if circuit is driven with a sinewave input:
$$V_\text{in} = V_o\sin(2\pi ft)$$
- all voltages / currents in the circuit will also be *sinusoidal at the same frequency!*
	- with different amplitudes / phase shifts
	- if capacitor voltage is a fixed frequency sine wave, *we know what the current will be* -- it's just the *derivative*
$$i_\text{cap}=(2\pi fC)*V_o\sin(2\pi ft + 90^\circ)$$
- for this input, the capacitor acts like a resistor:
$$R_\text{eff}=\frac{V}{i}=\frac{1}{2\pi fC *j}$$
	- $j$ is the phase shift here

## Sinewave Driven Circuits
- all voltages / current also sinusoidal
- so just figure out amplitude of resulting sinewave (w/ potential phase shifts)
- becomes very similar to solving for DC voltages / currents, since these values don't change over time
- *analyze a circuit by looking at how it affects each tone*

# Impedance
- generalized notion of resistance for sinusoidal circuits:
$$R=\frac{V}{i} \Longrightarrow Z = \frac{V}{i} = \frac{1}{2\pi fC* j}$$