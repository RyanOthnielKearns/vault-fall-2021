#ENGR40M #ENGR #Stanford #Stanford-Winter-2022 #lecture-notes 
[[ENGR 40M Module 49 - Inductor Circuits|Prev]] | [[ENGR 40M Module 51 - Buck Converter|Next]]
See [[ENGR 40M Course Reader.pdf|Reader 9.4 - 9.5]]
___
- how to convert power coming in at one voltage into a power at a different voltage
	- and how to conserve energy

# Learning Objectives
- be able to convert voltages energy-efficiently
	- do this by feeding a pulse into an LC filter
		- since LC filters are ideally lossless, we can pass along all the 0 frequency voltage of the input
	- filter only passes the 0 frequency tone of the signal

# Problem
- laptop / tablet adapter generates ~12V, but internal battery is ~8V
	- processor w/in requires a Vdd ~1V
	- power is proportional to $V_{dd}^2$ -- lowering Vdd means lowering power
	- processors also dissipate 10 - 30W!
- so problem: convert 8V -> 1V without wasting a lot of energy

# Solution: Basic Buck Converter
driving a power inverter from a 12V supply
- turn transistors on and off, s.t. output $V_\text{out}$ is mostly low but becomes high for brief pulses
- represent "load" provided by the chip we're powering with a resistor
	- want to run 10A at 1V -> $R = 0.1\Omega$
- circuit just looks like a voltage divider: inductor, then capacitor-resistor in parallel
![[buck-converter-filter.png]]
- $Z_1 = Z_L$ and $Z_2 = Z_{C+R}$
	- at low frequencies, inductor behaves like a short and capacitor behaves like it's open -> easy to get signal through to $V_\text{out}$
- going to behave like a lowpass filter

## Frequency Components of Input
- 0 frequency tone of a pulse is some small average value for the pulse, which depends on the *duty cycle* (how often pulse is high)
	- voltage of pulse when high times duty cycle (% time high)
- $T = 5\mu\text{sec}$, meaning $F = 200 kHz$
	- if $t_1 = (5/12)\mu\text{sec}$ (duty cycle) then DC component $V_\text{avg} = 12V\frac{\frac{5}{12}}{5} = 1V$
	- if we attenuate all higher frequencies, we're left with this lower DC signal at 1V

## Impedance Analysis
$$\frac{V_\text{out}}{V_\text{in}} = \frac{Z_1}{Z_1 + Z_2}$$
$$Z_1 = j2\pi fL$$
$$\frac{1}{Z_2} = j2\pi fC + \frac{1}{R} = \frac{j2\pi fCR + 1}{R}$$
$$Z_2 = R\cdot\frac{1}{1 + j2\pi fC}$$
$$\frac{V_\text{out}}{V_\text{in}} = \frac{Z_1}{Z_1 + Z_2} = \frac{1}{1 + j2\pi f\frac{L}{R} + LC(j2\pi f)^2}$$
- so: a low pass filter, except it attenuates high frequencies as $\frac{1}{f^2}$
	- if basic frequency is 200 kHz, $LC(2\pi f)^2\approx 9500$
		- meaning output of 12V at 200 kHz ~ 1mV
- the cool thing: inductors / capacitors are "lossless", so we've done this conversion pretty much efficiently
	- also make $R$ of the two transistors really small
	- is this really possible? [[ENGR 40M Module 51 - Buck Converter|next time]] will get into it...