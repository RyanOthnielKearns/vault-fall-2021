#ENGR40M #ENGR #Stanford #Stanford-Winter-2022 #lecture-notes 
[[ENGR 40M Module 47 - Inductors - Another Time Dependent Element|Prev]] | Next
See [[ENGR 40M Course Reader.pdf|Reader 7.3]]
___
# Learning Objectives
- inductor - resistor circuits can also form filters
	- analyzed with impedance

# RL Filters
![[rl-filter.png]]
- $Z_2 = R$, and $Z_1 = j2\pi fL$
- $\frac{V_\text{out}}{V_\text{in}} = \frac{Z_2}{Z_1 + Z_2}$
	- simple voltage divider using impedance
- some intuition: expect at low frequencies, since inductor acts as a short, we'll have a gain of 1 (b/c $V_\text{in} = V_\text{out}$)
	- at high frequencies, inductor will be an open circuit, meaning gain will approach 0
	- so we're dealing with a low-pass filter
	- would expect corner frequency $f_c$ occurs when $Z_1\approx Z_2$, hence $R = 2\pi fL$
$$\frac{V_\text{out}}{V_\text{in}} = \frac{R}{R + j2\pi fL} = \frac{1}{1 + j2\pi f\frac{L}{R}}$$
$$f_c = \frac{1}{2\pi\frac{L}{R}}$$
$$\frac{V_\text{out}}{V_\text{in}} = \frac{1}{1 + j\frac{f}{f_c}}$$
- switching the components (inductor + resistor) gives a high pass
	- at low frequencies, inductor is a short, so $v_\text{out}$ is shorted to ground
	- at high frequencies, inductor is open, so $v_\text{out}$ is $v_\text{in}$, meaning gain is 1
$$\frac{V_\text{out}}{V_\text{in}} = \frac{j2\pi fL}{R + j2\pi fL} = \frac{j2\pi f\frac{L}{R}}{1 + j2\pi f\frac{L}{R}} = \frac{j\frac{f}{f_c}}{1 + j\frac{f}{f_c}}$$
$$f_c = \frac{1}{2\pi\frac{L}{R}}$$