#ENGR40M #ENGR #Stanford #Stanford-Winter-2022 #lecture-notes 
[[ENGR 40M Module 50 - Voltage Conversion|Prev]] | Next
See [[ENGR 40M Course Reader.pdf|Reader 9.5.1]]
___
- explain how it's possible to be energy-efficient in the 12V -> 1V power supply
	- using Buck Converter as a filter

# Learning Objectives
- how a Buck converter is energy efficient
	- current mostly comes from the inductor! not Vdd

# Current through Buck Converter
- suppose $V_\text{out} = 1V$, and $R = 0.1\Omega$ load
	- load current = 10A, meaning power from power supply @ 12V is ~10W (how is this possible??)
- inductor current: $V / L = di / dt$
	- biggest voltage across the inductor is when it's at 12V
	- during $t_1$ pulse which is $0.5\mu s$ -> $11V / 20\mu H = 0.55A/\mu s$
		- meaning current increases by only ~0.22A (because $\Delta t$ is small, $\Delta i$ is small too)

## Current Flow
- during $t_1$:
	- current flows from $V_{dd}$
		- extra voltage adds energy to the inductor
	- $10A\cdot 12V = 120W$ dissipated across the load-bearing resistor, but only for $\frac{1}{12}$th the cycle
- during $t_2$:
	- pMOS transistor is off
	- current flow from Gnd
	- inductor loses energy
	- $0W$ for the other $\frac{11}{12}$ of the cycle
- so $120W\cdot\frac{1}{12} + 0W\cdot\frac{11}{12} = 10W$
	- 110W being absorbed into the inductor, increasing its energy -> gives this out 10W at a time for 11x as long as it was charged (because it's charged at a higher power than it's discharged at)

### Inductor Current
during $t_1$:
$$\frac{di}{dt} = \frac{12V - V_\text{out}}{L}\Longrightarrow \Delta i_+ = t_1\frac{12V - V_\text{out}}{L}$$
during $t_2$:
$$\frac{di}{dt} = \frac{- V_\text{out}}{L}\Longrightarrow \Delta i_- = t_2\frac{- V_\text{out}}{L}$$
this means: if you don't know $\frac{t_1}{t_2}$ at the outset, you can calculate this based on $V_\text{out}$ (just set these equal)
$$\Delta i_+ = -\Delta i_-\Longrightarrow V_\text{out} = 12V *\frac{t_1}{t_1 + t_2}$$
- same result we got before, from filter analysis!
- **output voltage only depends on duty cycle**
	- doesn't depend on load current / value of $R$!
	- output is the "average" voltage created by inverter
	- Vdd times percentage of time output is high
	- *if* we included the resistance of the transistors / inductor in our model, we'd have some energy loss and some dependence between output voltage and current

## Simplifying Assumption
- assume output voltage is constant (1V)
	- assume this b/c the capacitor is big enough so that the capacitor can supply or absorb excess energy as needed