#ENGR40M #ENGR #Stanford #Stanford-Winter-2022 #lecture-notes 
___
See [[ENGR 40M Course Reader.pdf]] 6-6.3

# Learning Objectives
- our current device models don't involve time
	- give value of circuit at rest
- **capacitors**: affect how voltages change
	- model devices that store charge
	- current is the *derivative* of charge -- related to how voltages change (not the voltages themselves)

# Circuits without the time dimension
## Frequency
- can't tell difference in frequency
	- frequencies are related to changes in charge over time

## Logic gates
- delays in our logic gates aren't modeled!
- model says the low $\to$ high change is instantaneous. not correct!

# Capacitors
- models physical phenomenon
	- it takes *energy* to create a voltage difference between wires
	- takes some charge to create a voltage difference -- electric field btwn two objects
	- model this charge (creating a voltage difference) as a **capacitor**
		- can be implicit or explicit capacitance
- two-terminal device
![[capacitor.png]]
- relates *charge* to *voltage* (w/ linear relationship)
$$Q = CV$$
- charge = capacitance times voltage
	- charge $Q$ measured in Coulombs, capacitance $C$ measured in Farads
- always *charge neutral* like our other devices
	- stores $+Q$ on one lead and $-Q$ on the other lead
- *eventually*, current across the two sides of the device *goes to zero* (there's no actual physical connection between the two terminals)

## With Physics E&M
- models fact that energy stored in electric fields
- the closer the terminals are, the larger the capacitance
- to create voltage btwn terminals
	- plus charge collected on positive end
	- negative charge collected on negative end
- creates electric field per Gauss' law

## Capacitor types
- electrolytic
	- *polarized* -- you have to connect the $+$ side correctly (always connect $-$ to ground)
	- highest capacitance per unit volume
- tantalum
- ceramic
- mica
- higher voltage compliance / larger capacitance $\to$ larger size

## i-V for a capacitor
- generally don't like to work with $Q$
- current is charge flow: $i = \frac{dQ}{dt} = C\frac{dV}{dt}$
	- still a linear equation

## Capacitors store energy
- Power: $P_{\text{cap}} = i\cdot V = (C\frac{dV}{dt})V$
	- absorbs energy and stores it, and at a later time can provide that energy back (where $\frac{dV}{dt} < 0$)
- energy absorbed by the capacitor:
$$E=\int P\ dt = \int_0^V CV \ dV = \frac{1}{2}CV^2$$
	- no energy lost in an ideal capacitor

## Key Properties
$$E=\frac{1}{2}CV^2$$
$$P = \frac{d}{dt}E$$
- changing energy requires power
	- changing voltage quickly is hard! requires lots of current
	- capacitors prevent voltages from changing instantly
$$\frac{d}{dt}V = 0\to i = 0$$
- in this case, voltages aren't changing! meaning no current
	- meaning capacitor behaves like open circuit at that time
- for very small $\Delta t$, capacitors look like voltage sources
	- can supply very large currents
	- do not change their voltages ($V_{\text{cap}}$, not the node voltages that don't change)
- for very large $\Delta t$, capacitors look like open circuits