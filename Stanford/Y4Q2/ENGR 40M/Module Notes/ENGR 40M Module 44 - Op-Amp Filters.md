#ENGR40M #ENGR #Stanford #Stanford-Winter-2022 #lecture-notes 
[[ENGR 40M Module 43 - Op-Amp Circuits|Prev]] | [[ENGR 40M Module 45 - Differential Amplifiers|Next]]
See [[ENGR 40M Course Reader.pdf|Reader 8.3.3 - 8.3.4]]
___
Add capacitors to the resistors to build amplifiers w/ filters (amplification depends on frequency)

# Learning Objectives
- analyze op-amp circuits w/ capacitors using impedence
	- usually inverting amplifiers w/ capacitors
	- gain is just $-Z_2 / Z_1$

# Adding Capacitors
- call whole resistor + capacitor in parallel $Z_2$
- call resistor between voltage source and $-$ terminal $Z_1$
- then: $\frac{V_\text{out}}{V_\text{in}} = -\frac{Z_2}{Z_1}$
- $Z_1 = R_1$
$$Z_2 = \frac{1}{\frac{1}{R_2}+j2\pi fC_1}$$
- b/c a resistor and capacitor in parallel
means:
$$\frac{V_\text{out}}{V_\text{in}} = -\frac{R_2}{R_1}\cdot\frac{1}{1 + j\frac{f}{f_o}}$$
- as frequency increases, gain is going to decrease, until gain at high frequencies is 0
	- at really low frequencies, acts like a standard inverting amplifier with gain $-\frac{R_2}{R_1}$
	- this creates a low-pass filter

## Creating a high-pass filter
- want $Z_1\to\infty$ at low frequencies
	- so, want capacitor in the first element $Z_1$, in series with the resistor
$$Z_2 = R_2$$
$$Z_1 = R_1 + \frac{1}{j2\pi fC_1} = \frac{1+j2\pi fR_1C_1}{j2\pi fC_1}$$
# Designing more complex filters
- adding the capacitors requisite for both high-pass and low-pass gives you a **band-pass filter**
$$Z_1 = R_1 + \frac{1}{j2\pi fC_1} = \frac{1+j2\pi fR_1C_1}{j2\pi fC_1}$$
$$Z_2 = \frac{1}{\frac{1}{R_2}+j2\pi fC_1} = \frac{R_2}{1 + j2\pi fR_2 C_2}$$
