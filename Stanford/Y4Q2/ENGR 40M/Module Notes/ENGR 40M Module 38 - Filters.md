#ENGR40M #ENGR #Stanford #Stanford-Winter-2022 #lecture-notes 
[[ENGR 40M Module 37 - Using Impedance|Prev]] | [[ENGR 40M Module 39 - Bode Plots and dB|Next]]
___
See [[ENGR 40M Course Reader.pdf]] 7.4

# Learning Objectives
- use impedance in this analysis
	- many interesting circuits are just voltage dividers
	- one "resistor" frequency dependent
- filters only allow certain tones to pass through

# RC Circuit from [[ENGR 40M Module 35 - Impedance - Analyzing RC Circuits with Sinewave Inputs|Module 35]]
- two elements, connected in series (capacitor + resistor)
- recall voltage divider:
$$V_\text{out} = V_\text{in}\cdot\frac{Z_2}{Z_1 + Z_2}$$
	- if we viewed the capacitor as a resistor, we'd have a voltage divider!

impedance of a capacitor is very high at low frequencies, very low low at higher frequencies
- at low frequency
	- impedance of capacitor is large
	- large attenuation
- at higher frequencies
	- impedance of capacitor is small
	- signals can pass through
- in a voltage divider, we're comparing the relative impedances of the resistor and the capacitor in the RC circuit
	- if $Z_2\gg Z_1$, gain will be 1
		- gain is $\frac{V_\text{out}}{V_\text{in}}$
		- $\gg$ here really is only around 2x
	- if $Z_1\gg Z_2$, gain will be $\frac{Z_2}{Z_1}$
	- *critical frequency* is when $Z_1 = Z_2$
$$f_o = \frac{1}{2\pi C R}$$
	- multiplying capacitance times resistance $RC$: get a unit in seconds $s$ -- total frequency $f_o$ is given in $s^{-1}$ or Hz

## RC Circuits can make other filters
- high pass filter
	- passes high frequencies, attenuates low frequencies (what we had in [[ENGR 40M Module 35 - Impedance - Analyzing RC Circuits with Sinewave Inputs]])
	- Vdd -> capacitor -> $V_\text{out}$ -> resistor -> Gnd
- low pass filter
	- resistor first after $V_\text{in}$, then $V_\text{out}$, then capacitor before Gnd
- putting the two together: low pass filter then a high pass filter connected to the low pass $V_\text{out}$
	- the only frequencies getting through to $V_\text{out}$ are low enough for the low-pass but high enough for the high pass
	- **band-pass filter**
	- just multiply the two equations for the two circuits