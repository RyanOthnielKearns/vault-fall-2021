#ENGR40M #ENGR #Stanford #Stanford-Winter-2022 #lecture-notes 
[[ENGR 40M Module 35 - Impedance - Analyzing RC Circuits with Sinewave Inputs|Prev]] | [[ENGR 40M Module 37 - Using Impedance|Next]]
___
See [[ENGR 40M Course Reader.pdf]] 6.6

finding $C_{\text{eff}}$
- different from resistors

# Learning Objectives
- effective capacitance of parallel capacitors *adds*
- effective capacitiance in series is proportional to $1/C$
- exact opposite for resistance!

# From equations:
for resistor:
$$I = \frac{V}{R}$$
for capacitor:
$$I = C*\frac{dV}{dt}$$
- directly related instead of inversely (as with resistor current)

# Two capacitors...
## in series
$$Z_{\text{eff}} = Z_1 + Z_2$$
impedence gets *higher*. this implies:
$$C_\text{eff} = \frac{C_1 C_2}{C_1 + C_2}$$more generally have:
$$\frac{1}{C_\text{eff}} = \frac{1}{C_1}+\frac{1}{C_2}+\frac{1}{C_3}+\dots$$
- recall $Z$ as impedance from [[ENGR 40M Module 35 - Impedance - Analyzing RC Circuits with Sinewave Inputs]]
## in parallel
inverse of the series case:
$$\frac{1}{Z_{\text{eff}}} = \frac{1}{Z_1} + \frac{1}{Z_2}$$
means:
$$C_\text{eff} = C_1 + C_2\ (+C_3+\dots)$$

*general reason*: because impedance $Z$ is proportional to $1/C$