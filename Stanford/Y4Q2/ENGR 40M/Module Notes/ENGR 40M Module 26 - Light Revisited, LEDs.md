#ENGR40M #ENGR #Stanford #Stanford-Winter-2022 #lecture-notes 
___
See [[ENGR 40M Course Reader.pdf]] 2.6.2 - 2.6.3

- for the next lab where we build an LED display

# Learning Objectives
- what light is
	- why light is different colors
- how to use an LED in a circuit
	- characteristics of using a diode
	- different colored LEDs have different $V_F$s

# What is Light?
- electromagnetic wave
- generating light:
	- use heat (by heating a coil to the point it glows, emitting light)
		- super inefficient
	- use plasma (fluorescent light)
		- the color emitted is harsh, so needs to be coated
		- gas inside commonly contains mercury
	- using LEDs
		- most houses today use these

# Light measurements
in **lumens**
- standard 60W bulb is ~800 lumens
- illumination on a surface: **lux** (= lumens/m$^2$)
	- 300 lux in office settings
	- 32k - 100k lux in direct sunlight
- at green light (550nm), 680 lux = 1W/m$^2$
	- other frequencies require less lux for 1W/m$^2$

# Energy generation
- in some special cases (e.g. LEDs) can generate electricity with light striking a material
- each photon has a precise energy set by the wavelength of light: $E = hc/\lambda$
	- where $h$ is Planck's constant $6.6\times 10^{-34} J\cdot sec$
	- will be useful for calculating energy in eV (electron volts)
		- energy of photons near visible light range from ~1.2 eV (for infrafred) to 2.6 eV (for blue light)
		- so, photon comes in, finds a charge, gives positive energy to the charge, and allows that charge to be siphoned off the cell and moved around to produce electric energy

# LEDs
- devices like solar cells, operating in reverse: take electricity and generate light
- voltages that you have to give the carriers (voltage drop across diode) is *different* for different colors of light
	- consumes $V_F$ eV of energy: this energy can emit a photon depending on the value of $V_F$!
		- red LEDs take ~2V
		- blue LEDs take around ~3V
- should use external resistance to limit current
	- set around 30mA max (around 20 ideally)
		- so... resistance on order of $100\Omega$
			- Arduino pin has resistance around $30\Omega$
	- doesn't matter where in series, so long as it is in series
- *do not put LEDs in parallel* -- current will end up being weird
	- series connection is fine with a higher voltage source