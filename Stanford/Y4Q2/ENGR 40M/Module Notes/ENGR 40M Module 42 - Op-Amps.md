#ENGR40M #ENGR #Stanford #Stanford-Winter-2022 #lecture-notes 
[[ENGR 40M Module 41 - Introduction to Amplifiers|Prev]] | [[ENGR 40M Module 43 - Op-Amp Circuits|Next]]
___
See [[ENGR 40M Course Reader.pdf|Reader 8 - 8.1]]

# Learning Objectives
- analyze circuits w/ op-amps
- recognize *negative feedback* in a circuit
	- when op-amp is used with negative feedback: tries to force the voltage difference between inputs to 0
	- inputs don't take any current

# Amplifiers
want to make signals larger:
$$V_\text{out} = A\cdot V_\text{in}$$
- can we create a device for *any* gain $A$?

## Op-Amps
- needs $+/-$ supplies: $V_\text{out} = A(V_p - V_n)$
	- gain $A$ is *very large* (10K - 1M) -- this is much larger than we want
- has $V_p$ and $V_n$ input terminals, $+/-$ power supply, and 1 output terminal
- input currents $i_\text{in}, i_\text{out}\approx 0$
- output swing is limited:
![[op-amp-output-swing.png]]
- since our gain is so large, if we just use it directly the output will "saturate" basically immediately for nonzero + or - inputs
	- we need to *reduce the effective gain*
- output has *capacitance* to it -- meaning won't change instantly

## Negative Feedback
- build a circuit which subtracts $\alpha V_\text{out}$ from the input
	- generate an error input that we feed into the op-amp
	- generally $\alpha < 1$: so a device like a voltage divider can produce $\alpha V_\text{out}$ from $V_\text{out}$
	- $\text{err} = V_\text{in} - \alpha V_\text{out}$
		- eventually reaches a steady state where the error no longer affects the input (forces err to near 0, $\frac{V_\text{out}}{\sim 100k}$)
		- approximate the gain in the op-amp as infinite, and then err is actually 0
		- then: $V_\text{out} = \frac{V_\text{in}}{\alpha}$ -- meaning you can set the gain precisely by attenuating the signal to $\alpha$!

### Connecting $V_\text{out}$ directly to $V_-$
- implies $V_\text{out} - V_\text{in} = V_\text{err}$
	- $V_\text{err}\to 0$, therefore $V_\text{out} = V_\text{in}$

# Ideal Op-Amp Model
- infinite gain
	- will drive output voltage so that $v_p = v_n$
when used with negative feedback configuration
1. $v_p = v_n$ (no v oltage difference between input terminals)
2. $i_p = i_n = 0$ (no current into inputs)