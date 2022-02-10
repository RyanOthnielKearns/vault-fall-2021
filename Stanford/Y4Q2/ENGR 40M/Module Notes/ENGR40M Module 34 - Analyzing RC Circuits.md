#ENGR40M #ENGR #Stanford #Stanford-Winter-2022 #lecture-notes 
___
See [[ENGR 40M Course Reader.pdf]] 6 - 6.3

- use this to find the delay of CMOS logic gates

# Learning Objectives
- compute $V(t)$ for simple RC circuits
	- know initial value, final value, and time constant
	- waveform will be an *exponential*
- use this to compute the delay of a CMOS logic gate
	- gate terminal of a MOS transistor is a capacitor
	- wires are also capacitors

# Capacitors and Logic Gate Speeds
- input from low to high $\to$ pMOS turns off, nMOS turns on $\to$ output goes high to low
	- without capacitance, output changes instantaneously when input changes
- inverter must drive a wire + gate terminals of other transistors
	- all of these objects have capacitance associated w/ them

## Gate of a MOS transistor
- a *capacitor between gate and source*
- this is why there is no DC current flowing through the gate
- to change the gate voltage, require a "current pulse", causing $\frac{d}{dt}V$
	- if current is zero ("floating") then $\frac{d}{dt}V = 0$, which is why the voltage stays at the same state it was at when you float the gate

## Real Wires have Capacitance
- takes some charge to change voltage of a wire
	- to make a wire higher potential energy, charge has to flow into the wire, making energy higher for the next charge flowing in

# CMOS Delay Model
## Input Rising
- capacitors at the pMOS & nMOS transistors, and also the wire to ground
- $i = C\frac{dV}{dt}$ -- only depends on voltage change!
	- so long as voltage difference between Vdd and Gnd is the same (e.g. 5V), current through capacitors connected to either Vdd or Gnd is the same
	- can just represent these two transistors using a single capacitor:
$$C = C_w + C_{g_1} + C_{g_2}$$
		- capacitance equal to the capacitance of the wire plus both gates' capacitance!
- output voltage right after input changes: 5V
- output settles at 0V
- how long will transition take?
	- first, with an RC circuit, you'll have the current $i_R = \frac{V_R}{R}$
		- and $i_C = -i_R$
	- current will tell you change in voltage over time, given capacitance $C$
	- $\Delta t \approx \frac{\Delta V}{\frac{dV}{dt}}\approx RC$
		- not quite, because shape of the curve is not linear: instead an exponential with time constant $RC$

## Input Falling
- output voltage right after input changes: 0V
- output settles at 5V

# Solving using Nodal Analysis
- for resistor-capacitor problems
	- better to solve for voltage across the resistor: that voltage is also the output voltage
	- Only one unknown voltage, $V_\text{out} = V_C$
$$\frac{V_\text{out}}{R_2} + C\frac{dV_\text{out}}{dt} = 0$$
$$\frac{dV_\text{out}}{dt} = -\frac{V_\text{out}}{R_2C}$$
- only function that is its own derivative is an *exponential*
$$V_\text{final} = V_\text{start}*e^{\frac{t}{R_2C}}$$
- this means that $e^{\frac{t}{R_2C}}$ is the time constant of the exponential

## Output Rising Transition
$$V_\text{out} = 5V - V_{R1}$$
- since resistor and (aggregated) capacitor now in series, $i_R = i_C$
$$\frac{V_{R1}}{R_1} = \frac{dV_\text{out}}{dt}\cdot C = -\frac{dV_{R1}\cdot C}{dt}\Longrightarrow V_{R1} = 5V\cdot e^{-\frac{t}{R1\cdot C}}$$

- in capacitor circuits, *voltages change slowly*, while *currents can change instantaneously*