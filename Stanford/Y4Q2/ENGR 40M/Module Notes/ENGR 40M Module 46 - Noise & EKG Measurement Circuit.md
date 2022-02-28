#ENGR40M #ENGR #Stanford #Stanford-Winter-2022 #lecture-notes 
[[ENGR 40M Module 45 - Differential Amplifiers|Prev]] | [[ENGR 40M Module 47 - Inductors - Another Time Dependent Element|Next]]
___
- world contains many signals besides the one you want to measure
	- minimize their effect on your measurement

# Learning Objectives
- understand how noise can enter your circuits
- reduce effect of noise on your EKG signals
	- mostly 60Hz power running through building, + DC offset

# ECG Measurement
- desire to measure: voltage difference between two probes (L1 and L2)
- many unwanted signals coupling into circuit
	- capacitive (stray E fields) and inductive (B fields)
	- how to prevent them from obscuring our signal?

## Noise protection for wires
- wires have "built-in" protection w/ outer jacket, braided shield, foil shield, dieletric coating
	- ensures that outer signals will have capacitance to the outer shield, rather than the inner signal
- making the noise "common mode" -- twist wires to each other, s.t. the *difference* between signals coupled together won't be that much

### Model of Capacitive Noise
- think of capacitance from a noise source (will be really big -- 120V, 60Hz)
	- *actual signal* is really small -- ~1mV
		- even if noise is attenuated by 1000x, still way bigger than our signal...
- try to make the effect of the capacitance to noise *treated the same* on both $V_{L1}$ and $V_{L2}$
	- that way, they can offset
- voltage at two outputs depends on both ECG, plus noise
	- want $V_{L1} - V_{L2}$ independent of noise

### Use Balanced Instrumentation Amplifier
- completely differential system, good for reducing coupled noise
- but **problem!** what sets $v_1$ and $v_2$ on the amplifier?
	- e.g., ECG voltages relative to the power supply of the amplifier
		- ECG sets the voltage difference
		- but the body is not connected to the power supply of the amplifier
			- not referenced to the chip's Gnd, powering the amplifier
			- this means amplifier won't work unless measured signal is between power supply
	- **solution**: add third lead L3 (connected to the person's leg) to set Gnd to the average of the human body
		- this is the industry standard for actual ECGs
	- **other solution**: put strong resistors between measured inputs and Gnd ("weak connection" to Gnd)
		- this unbalances the measurement a little bit, but more reliable for our setup in lab
# Circuit we will build
![[ecg-circuit.png]]
- will have resistors between $V_\text{in}^+$ and $V_\text{in}^-$ and Gnd (and also separate current-limiting resistors)
- set reference voltage of the amplifier (the lower-most wire) $V_\text{ref}\approx 0.5V$
	- since this is ~"ground", we can get measurements both above and below ground
- the op-amp filter configuration in the top right is a bandpass
	- why do we need a capacitor into the op-amp?

## Skin Voltage
- when you connect metal to your skin, small voltage forms
	- like a small battery
	- might produce voltage difference of ~10mV
	- e.g., if the conditions at the two electrodes are different, you can generate a voltage difference between the leads that might change slowly over time
		- depends on sweating, etc. other noisy biological signals
		- high-pass, b/c these signals will be changing at frequencies below 1Hz (heart operates at around 1Hz)
		- also affects the DC offset that will impact our measurements
	- what about the capacitor forming the low-pass filter above the op-amp?

## Main Source of Noise: 60Hz wall voltage
- main capacitave noise
- can be 1000x the signal
- differential circuit design filters most of it out, but there will be some noise getting through
- where should we put that 2nd corner frequency? can't just filter above 1Hz, b/c the voltage "spike" has higher harmonics than just 1Hz
	- probably >10Hz to resolve the spike