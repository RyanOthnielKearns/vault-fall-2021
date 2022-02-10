#ENGR40M #ENGR #Stanford #Stanford-Winter-2022 #lecture-notes 
___
# Learning Objectives
- sound = pressure waves in the air
- can generate electircal signals from sound (and vice versa)
- understand what an audio recording "looks like"

# Sound
- hearing starts at around 20 - 30 Hz, to around 20k Hz
- electrical signals from sound system passed through an electromagnet attached to the spearker
	- causes the speaker to vibrate, creating sound waves

# Amplifiers
- devices that drive speakers
- amplifier power given in Watts -- e.g. 100W stereo ampliifer
	- speakers are generally $8\Omega$
		- means $\approx 30V$, solving using $P=i\cdot V = V^2 R$
- headphones are spec'd at lower power, typically around 30mW
	- higher resistance: $20\Omega$
	- voltage is then $+/- 0.8V$ (sound goes positive and negative)
		- close to what Arduino uses
		- analog voltage!

# Sound Sensors: Microphones
- sound pressure sensor, that converts to voltage vs. time plot