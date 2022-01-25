# Agenda
- covering lab for next week -- building the useless box!
	- switch, battery pack, motor, and second switch on the bottom

# Covering the pre-lab
- learning about what the components do & how to interact w/ them
- first switch: DPDT
```
---------
| 1 - 6 |
| 2 - 5 |
| 3 - 4 |
---------
```
- second switch: SPDT with a a default state (a "spring")
```
C - NO - NC
```
- limit switch is to turn the motor off when the arm has wholly retracted
	- so we only need to use two terminals: `C` and `NC`

## The motor
- face toward you so that two flat regions are facing you -- mark as positive the terminal that causes the motor to rotate clockwise (when you put the positive lead to it)
- when the motor was just running: should be around ~50 mA
	- when you try to stop the motor: can get ~0.5A (10 times more!)
	- converting electrical power to mechanical power -- more mechanical, physical work means it will require pulling more current

## Circuit design
- how to connect 4 components together so box does the right thing?

- next class: in class! Rm. 320-105