#ENGR40M #ENGR #Stanford #Stanford-Winter-2022 #lecture-notes 
___
# Solar Cells
- provide power to an electrical circuit
- modeled as a diode in *parallel* with a current source
	- recall for [[202201061838 ENGR 40M Module 10 - Diodes|diodes]]: voltage source for positive circuit, open circuit otherwise
	- when light shines on the diode, it generates a current $\rightarrow$ model this by a current source, flowing from $+$ terminal of the whole device
- generate high voltages using series cells

## i-V characteristic
- diode plus current source (horizontal line below the x-axis)
	- take traditional i-V for a diode and move it down on the graph to where the current source is

### Open circuit measurement
*What is the voltage when zero current flows out of the device?*
$\rightarrow$ **Open Circuit Voltage**

- equal to the forward voltage of our diode ($V_F$)
- if there's no path for the current, all light-generated current must flow through the diode
	- KCL must hold, which is why $V_{\text{diode}} = V_F$

### Short circuit measurement
*What is the current when there is zero voltage across the device?*
$\rightarrow$ **Short Circuit Current**

- some amount of current generated by the current source modeled in parallel
- because the voltage across the diode is zero, all of the light-generating current flows out of the device

### Power
- no power at either the open circuit voltage or the short circuit current
- idealized model: operate at the corner where the current and voltage are both maximized
	- $P = V_{OC}\cdot i_{SC}$
		- voltage of the open circuit, current at the short circuit

- the spec of our solar cell: $6V, 1W$
	- this is a lot!
	- how to get such a large voltage? each diode contributes a voltage change of around $<0.5 V$
		- 12 solar cells stacked together, put in series w/ each other
		- another 12 solar cells put in parallel to the first stack
- all the cells get the same light, so the current sources are all the same
	- if one solar cell doesn't get enough light $\rightarrow$ that cell has a smaller current, which means the whole series of cells has a smaller current $\rightarrow$ less power!
	- current goes to the lowest current, which means if one cell is completely blocked you get 0 current across the whole series