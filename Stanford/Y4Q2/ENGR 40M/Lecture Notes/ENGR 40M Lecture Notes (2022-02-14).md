#Stanford #Stanford-Winter-2022 #ENGR #ENGR40M #lecture-notes 
___
if we have an input voltage of the form
$$V_\text{in} = 2V\sin(2\pi\cdot1kHz\cdot t$$
and gain $\frac{V_\text{out}}{V_\text{in}} = 0.5$, what is the output signal?
- frequency's not going to change! gain ratio will just make output signal half the voltage
- so $V_\text{out} = 1V\sin(2\pi\cdot 1kHz\cdot t)$

if your input signal is a 1kHz sine wave of amplitude 1V, what's true about the output signal of a low pass filter?
- output will be a sinusoid
- output sinusoid will have frequency 1kHz
- output will not necessarily have amplitude 1V, since voltage divider behavior of the filter will affect the amplitude

*attenuating* a signal by 10 means the *gain* is 0.1 (it diminishes the signal strength)
- if we say the gain is $0.5j$ instead of just $0.5$ -- means the output is phase-shifted relative to the input
	- e.g. if $V_\text{in} = 1V\sin(2\pi\cdot 1kHz\cdot t)$ -> $V_\text{out} = 2V\cos(2\pi\cdot 1kHz\cdot t)$
	- otherwise you mostly just ignore $j$, except for this phase-shifting behavior

- adding a capacitor in parallel increases effective capacitance
- adding a capacitor in series decreases effective capacitance
	- from [[ENGR 40M Module 36 - Parallel and Series Capacitors]]

- impedence of two devices in series: sum!
	- $Z = Z_1 + Z_2$
- impedence of two devices in parallel:
	- $Z = \frac{Z_1Z_2}{Z_1 + Z_2}$
![[engr-2022-02-14.png]]
- get **filters** when we build voltage dividers w/ resistors and capacitors, since impedance of resistors is just $R$ as we see above
	- see [[ENGR 40M Module 38 - Filters]]