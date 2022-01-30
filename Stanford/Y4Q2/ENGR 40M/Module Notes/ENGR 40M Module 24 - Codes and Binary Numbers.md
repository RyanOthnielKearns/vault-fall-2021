#ENGR40M #ENGR #Stanford #Stanford-Winter-2022 #lecture-notes 
___
[[ENGR 40M Course Reader.pdf]] 5 - 5.1

# Learning Objectives
- be able to represent positive integers as a collection of bits
- understand binary numbers as a type of code
- use two-complement notation, understand overflows

# Gates with binary signals
- wires can only transmit two values: 1/0, Vdd/Gnd, True/False
- 8 bits = 1 byte (ASCII char)
- 24 bits grouped to represent color (8 bits for R/G/B)
- 16, 32, or 64 bits grouped together to form integers
- place values: 1, 2, 4, 8, etc.

# Codes
- figuring out "good" codes is a big part of EE
	- security / cryptography
	- error correction (for transmitting data)
	- compression

# Modulo Arithmetic
- 4-bit numbers represent integers 0 - 15
- adding $8+8$: you get 16, but only represent the lower 4-bits of the binary number 10000 (which is 0000 = 0)
- all operations are modulo $2^N$, where $N$ is the number of bits

# Representing Negative Numbers
- create a sign / magnitude code
	- add one bit to be the sign bit? **sign-magnitude representation**
	- not what's done! if you built hardware this way, you'd have to look at the sign bits to do arithmetic
- instead: take advantage of modulo arithmetic
	- most-significant bit is the sign
		- 0XXX is a positive number
		- 1XXX is a *negative* number
		- so positive numbers are "normal" binary
		- negative numbers are chosen s.t. when added to $|N|$, a normal adder will give zero
			- -6 = 1010
			- -2 = 1110
			- -1 = 1111

## Generating a Two-Complement Number
1. take the number you want to make negative in binary
2. invert / complement each bit!
	- if you add these two numbers together, you'd get all 1's
3. add 1 to the complement to get the two-complement value

## `int`s and `uint`s
- `uint`s can only be positive
- hardware treats them the same way!
	- only difference is how the most significant bit is viewed
		- for `int`s, represents the sign

## Overflow
- for 4-bit integers, 7 + 1 = -8 (the maximum negative number we can represent)
- put special checks in software where overflow can occur
	- frequently with *timers*
![[binary-number-wheel.png]]