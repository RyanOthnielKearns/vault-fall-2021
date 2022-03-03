#ENGR40M #ENGR #Stanford #Stanford-Winter-2022 #lecture-notes 
[[ENGR 40M Module 51 - Buck Converter|Prev]]
See [[ENGR 40M Course Reader.pdf|Reader 9.6]]
___
# Learning Objectives
- you can run a buck converter backward
	- convert energy at lower voltage -> higher voltage

# Buck Converter
- voltage gain does not depend on current
- so instead, just replace $V_\text{out}$ at the top of the circuit, where $V_{dd}$ used to be!
	- replace load resistor $R$ with a voltage source, and get rid of the parallel capacitor
	- need to add a capacitor / resistor in parallel after $V_\text{out}$ because output will come in bursts, and we need to control the current

# Boost Converter
![[Screen Shot 2022-03-02 at 6.27.29 PM.png]]
- current flows from $+$ terminal of $V_\text{source}$
when nMOS device is on (at $t_2$), inductor has $+V_\text{source}$ across it and the current increases
- ramp rate for the inductor will be $V_\text{source} / L$
- power is being added to the inductor ($V_\text{source}*i_L$)
	- total energy added $\propto t_2\cdot i_L\cdot V_\text{source}$
- load current supplied by *capacitor* $C$

when pMOS device is on (at $t_1$):
- current flows up and through $R$ and $C$
- inductor has $V_\text{source} - V_\text{out}$ across it, so current decreases
- inductor is supplying power to the load resistor and the capacitor
	- energy supplied $\propto - (V_\text{out} - V_\text{source})\cdot i_L\cdot t_1$
total power delivered:
$$\frac{t_1\cdot V_\text{out}\cdot i_L}{t_1 + t_2}$$
- divide power supplied in by total time
$$-\Delta i_- = \Delta i_+\Rightarrow t_1\frac{V_\text{out} - V_\text{source}}{L} = t_2\frac{V_\text{source}}{L}\Rightarrow V_\text{out} = V_\text{source}\cdot \frac{t_1 + t_2}{t_1}$$
- the same answer we got before, but with the terms reversed

*cool thing about inductors*: available to absorb and transfer energy at later times without loss