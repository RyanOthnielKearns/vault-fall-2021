#ENGR40M #ENGR #Stanford #Stanford-Winter-2022 #lecture-notes 
[[ENGR 40M Module 40 - EKG - Bio-electrical Signals|Prev]] | [[ENGR 40M Module 42 - Op-Amps|Next]]
___
See [[ENGR 40M Course Reader.pdf]] 8 - 8.1

- takes small analog signal and turns it into a bigger signal

# Learning objectives
- model an amplifier
	- generates an output $A$ times larger than input voltage
- amplifiers need to have positive and negative power supplies
	- output always within these power supply voltages
	- to generate $+/-$ supplies, just move the reference voltage!
![[amplifier.png]]

# Amplifier requirements
we want $V_\text{out} = A\cdot V_\text{in}$
- amplifier needs to drive $V_\text{out}$
- output is connected to a resistor
	- so amplifier needs to supply power (energy to the resistor)
	- but transistors + other devices can't actually supply power on their own -- need a power supply to get power in
- also, tones will have positive and negative voltages
	- need positive and negative power sources (of roughly equivalent magnitude)

## Two Inputs
- often want to amplify a *voltage difference*
$$V_\text{out} = A\cdot(V_p - V_n)$$
- means amplifiers have ~5 terminals
	- +/- power supply
	- 1 output
	- 2 inputs (positive and negative inputs $V_p$ amd $V_n$)

## Amplifier Power Supply
- convenient to set the reference voltage *not* at the lowest voltage in the circuit, but rather in the *middle* of the power supply
	- just change what we call ground!
![[amplifier-power-supply.png]]
here select $F$ to be our ground / reference node
- ground is 2.5V below $A$ and 2.5V above $E$ (so $E$ has voltage -2.5V)

# Amplifier Model
- internally, has some *controlled voltage source* that creates a voltage proportional to the difference btwn the two inputs, and can drive current using this output
- power is *really* coming from the power supplies outside the amplifier
- remember: output voltage is limited (can't exceed the power supplies)
	- if your signal *wants to be bigger* than the power supply's, you'll get **clipping** (the output "saturates" at some maximum value)