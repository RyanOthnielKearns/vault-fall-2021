#ENGR40M #ENGR #Stanford #Stanford-Winter-2022 #lecture-notes 
___
- two devices in parallel: voltages the same, currents add
	- two resistors in parallel is a new resistor with lower resistance
- two devices in series: voltages add, currents the same
	- two resistors in series is a new resistor with higher resistance

# Parallel Devices
- same voltage
- currents of the devices in parallel *add*

## Current Source with Parallel Resistor
- current source with 1 mA
- resistor with 10K
- interpose the two $i-V$ diagrams; add vertically (because you're in parallel, current adds)
	- combined circuit has an $i-V$ characteristic resulting from adding the two curves

# Series Devices
- currents are the same
- voltages across the devices in series *add*

## Voltage Source and a Series Resistor
- 3V voltage source
- 10K resistor
- interpose the two $i-V$ diagrams again and this time add *horizontally* (because you're in series, voltage adds)

# Thevenin Equivalent Circuits
- all of these graphs are straight lines!
- any straight line $i-V$ graph can be modeled by a *single voltage source* and a *single resistor* in *series*

# Parallell and Series Resistors
- With one resistor, adding another resistor in parallel:
	- current has to increase $\rightarrow$ effective resistance is *always* smaller than either resistor
$$\frac{1}{R} = \frac{1}{R_1}+\frac{1}{R_2}$$
$$R = \frac{R_1R_2}{R_1+R_2}$$
	- still looks like a resistor in terms of $i-V$ characteristics
- How about adding another resistor in series?
	- voltage across each resistor will be the same or less (the sum of the device voltages)
	- current must go down $\rightarrow$ resistance is higher than either individual resistor
	- still looks like a resistor on $i-V$ diagram
$$R = R_1 + R_2$$