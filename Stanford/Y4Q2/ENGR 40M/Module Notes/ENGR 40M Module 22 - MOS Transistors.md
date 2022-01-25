#ENGR40M #ENGR #Stanford #Stanford-Winter-2022 #lecture-notes 
___
See [[ENGR 40M Course Reader.pdf]] 4.4

- electrically controlled switches -- control set by another electrical signal

# Learning Goals
- using nMOS transistors
- using pMOS transistors

- for this class...
	- using simple digital logic: boolean (binary) circuits
	- input / output voltages only either Gnd or Vdd

# MOSFETs / MOS Transistors
1. nMOS
	- 3 terminals: *drain*, *gate*, *source*
	- current flows in the drain, out the source
	- Gate is the control terminal for the switch
		- no current flows on it
		- but voltage on it controls whether drain and source are connected
		- gate doesn't actually connect to source / drain
	- current flowing from the drain to the source: $i_{ds}$
		- *source* of an nMOS transistor should always go directly or indirectly to *ground*
		- with ground on nMOS gate, no current flows (like a disconnected switch)
		- with logical 1 on nMOS gate, current flows (with some resistance)
	- acts like a series of a resistor together with a switch
		- has small resistance $R_{\text{on}}$
	- doesn't work so well if we want to connect our source to Vdd -- source has to go to Gnd
2. pMOS
	- "bubble" on the symbol for this device means "invert," e.g. the transistor is connected when the gate is low (not high, like nMOS)
	- 3 terminals: *drain*, *gate*, *source*
	- Current is different: in the source, out the drain
	- Gate is again the control terminal for the switch
		- no current flows on it
		- but voltage on it controls whether drain and source are connected
	- current flowing from source to drain ($i_{sd}$) is *positive* when the gate is at *ground* (voltage is 0)
		- gate voltage must be lower than source voltage

- pMOS and nMOS transistors are "complements" of each other