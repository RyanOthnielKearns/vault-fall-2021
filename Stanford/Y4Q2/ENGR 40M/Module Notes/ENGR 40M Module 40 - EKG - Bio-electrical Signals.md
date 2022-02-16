#ENGR40M #ENGR #Stanford #Stanford-Winter-2022 #lecture-notes 
[[ENGR 40M Module 37 - Using Impedance|Prev]] | [[ENGR 40M Module 41 - Introduction to Amplifiers|Next]]
___
- important for the last lab we're going to do

# Learning Objectives
- you run off electrical signals
	- this is what causes your heart to beat, brain to operate etc.
	- ~100mV -- quite small!
	- this means safety is critical when doing bio-electrical measurements
		- need *double isolation* (at least) from 120V

# EKG Lab
non-invasive device that measures the electrical electricity of the heart using electrodes placed on the skin
- concepts required
	- amplifiers: circuit that makes small electrical signals bigger
	- impedance: use capacitors + filters, etc. to make the signal better
	- noise
	- safety
	- filters: impedance + amplifiers together to get gains greater than 1 (contrast with [[ENGR 40M Module 34 - Analyzing RC Circuits|RC filters]] that all have gains less than 1)

# You run on electricity
- nevers use electrical impulses (spikes)
	- muscles contract given these spikes
	- very small voltages

## Two issues with measuring bio-voltages
- nerve spikes are small: ~100mV, and you're not measuring them directly
	- on the order of 1mV being measured
	- need to build an amplifier with a gain of about 1000
- putting electricity in your body could alter the system (bad)
	- need to ensure we're not putting voltage or current *into* the biological system

## Electrical picture
- p-wave causes contraction of the atriums, pushing blood into ventricles
- QRS complex: ventricles pushing blood into the body
- t-wave: the "recovery" signal to the ventricles to relax after pushing

# Measuring Small Voltages
- Arduino has full-scale around 5V
	- produces a 10-bit answer (1024)
	- this means the least significant bit has to be $5V / 1000 = \sim 5mV$
- need something bigger than this before input to Arduino - use **amplifier**
	- use an **Operational Amplifier** (Op-Amp) specifically

# Safety
- current through the body is dangerous
- touching 110V hurts, but won't do permanent damage
	- because skin is not a good conductor (generally $\sim 1M\Omega$)
		- water makes the skin more conductive
	- means $110V / 1M\Omega = 110\mu A$, and it takes $mA$ to be dangerous
- ECG needs to make good skin contact -- insulation of the skin has gone away
	- *now* 100V could be fatal, because current can be higher

## Triple Isolation
1. Leads attached to the body have >100K resistors, limiting the max current
2. Electronics will run off a battery not directly connected to your laptop
3. Computer should be running off its own battery (not plugged into the wall)