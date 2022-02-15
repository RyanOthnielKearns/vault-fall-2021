#ENGR40M #ENGR #Stanford #Stanford-Winter-2022 #lecture-notes 
[[ENGR 40M Module 36 - Parallel and Series Capacitors|Prev]] | [[ENGR 40M Module 38 - Filters|Next]]
___
# Learning Objectives
- be able to convert output of impedance computations
	- into current / voltage waveforms
- understand that result will be $a + b*j$
	- has $\sin$ and $\cos$ components
- any sum of $\sin(x)$ and $\cos(x)$ can be represented by $A\sin(x +\phi)$

# Impedance
$$Z = \frac{V}{i} = \frac{1}{2\pi fC*j}$$
- can compute capacitor voltage given current and vice versa
$$i = V_\text{cap}*2\pi fC*j$$
- meaning?
$$V_\text{cap} = V_\text{in}*\sin(2\pi ft)$$
- $j$ means that we're phase-shifting the sine wave
	- in units $\frac{V\cdot F}{s}$, or otherwise $\frac{C}{s}$, which is just amps! (Coulombs / sec.)
	- current that goes through a capacitor is proportional to the frequency!
	- 
- $f$ is the frequency in Hz, or $s^{-1}$
- capacitance $C$ is in Farads $F$ (recall [[ENGR 40M Module 33 - Capacitance - Adding the Time Dimension#Capacitors]])

# Adding Sine and Cosine Waveforms
- $a + b*j$ means the waveform is sum of
	- sine wave with amplitude $a$
	- cosine wave with amplitude $b$
- always results in a sine wave
	- with phase shift between sin and cos ($+90^\circ$)
$$A\sin(2\pi f t+\phi) = a\sin(2\pi ft)+b\cos(2\pi ft)$$
- use the trick that this equation is true at all $t$
	- for $t = 0$, $\sin(0) = 0$ and $\cos(0)=1$
		- meaning $A\sin(\phi) = b$
	- for $t=\frac{1}{4f}$, $\sin$ is 1 and $\cos$ is 0 ($\cos(\frac{\pi}{2}) = 0$)
		- meaning $A\cos(\phi) = a$
- so $A=\sqrt{a^2 + b^2}$
	- when one term is much larger than the other, you can basically just ignore the smaller term (for amplitude only, not for phase)