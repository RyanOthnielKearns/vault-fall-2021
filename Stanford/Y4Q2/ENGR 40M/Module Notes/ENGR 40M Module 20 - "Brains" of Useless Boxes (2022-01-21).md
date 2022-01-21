#ENGR40M #ENGR #Stanford #Stanford-Winter-2022 #lecture-notes 
___
See [[ENGR 40M Course Reader.pdf]] 4.1.3

# Learning Objectives
- wiring up a useless box
	- so that the motor drives the finder to flip switch and return
- useless box as a finite state machine

# In a useless box
1. motor
	- can be in three different states
		1. forward -- driving the finger to turn the switch off
			- when toggle switch is on
			- regardless of limit switch
		2. reverse -- returning finger to box
			- when toggle switch is off
			- when limit switch is not touched
		3. stop
			- toggle switch is off
			- limit switch is touched
2. battery pack
3. two switches
	1. switch on top: the "toggle" switch
		- DPTP -- why?
			- need to reverse polarity across the motor -- change which terminals of the battery are connected to which side
			- need to be able to connect battery $+$ or $-$ across the motor
	2. the "limit" switch

# Practical matters: wiring
- discussed in lab / class!