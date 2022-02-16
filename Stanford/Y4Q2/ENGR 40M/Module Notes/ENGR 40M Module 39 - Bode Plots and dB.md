#ENGR40M #ENGR #Stanford #Stanford-Winter-2022 #lecture-notes 
[[ENGR 40M Module 38 - Filters|Prev]] | [[ENGR 40M Module 40 - EKG - Bio-electrical Signals|Next]]
___
- improved way of plotting gain of circuit vs. frequency (Bode plots)
	- use measurement called dB

# Learning Objectives
- create log-log plot of gain vs. frequency (Bode plots)
	- mostly consist of straight lines
- express the gain of your circuit in dB ($= 20*\log(\text{gain})$)

# Problems w/ Frequency Plots
from [[ENGR 40M Module 38 - Filters]]
- bounds choice is critical -- the "region of interest" likely going to be very small & hard to read
- shape is hard to interpret ($1/x$? $1/x^2$? hard to say)

## Solutions
- each decade of frequency should be the same size
	- so that range isn't that critical for showing region of interest
	- this is exactly a log plot
- want constant gain to be easy to interpret
- want gain proportional to frequency
	- and also *inversely proportional*
	- more generally: $\text{gain} = kf^N$ should be representable

# Log-Log Plots
means any power of $f$ is a straight line:
$$\log(f^N) = N\log(f)$$
- proportional *and* inverse-proportional relationships show up as straight lines

also, each frequency decade takes up the same amount of space -- so plot limits won't easily shrink regions of interest

for plotting $\frac{1}{1+bj}$ - same plot as $1 + bj$ plotted upside down, because of log-log plot
- shows you visually that for $\sqrt{b^2+1}$ for low $b$, approximate as $1$, else for high $b$ approximate as $b$

## Low Pass Filters
$$\frac{V_\text{out}}{V_\text{in}} = \frac{1}{1+2\pi RCf*j}=\frac{1}{1+\frac{f}{145Hz}*j}$$
- here $\frac{1}{145Hz}$ is our time constant in seconds, given by $2\pi RC$ (from [[ENGR 40M Module 38 - Filters]])
- approximate low-pass curves with two straight lines: one at one, and another with slope $-1$, intersecting at the "**corner frequency**"

### Building Bode Plots
- looks like a straight line and a line that goes down
$$\frac{1}{1+\frac{f}{f_o}*j}$$

## High Pass Filters
$$\frac{V_\text{out}}{V_\text{in}} = \frac{2\pi RCf*j}{1+2\pi RCf*j}=\frac{\frac{f}{145Hz}*j}{1+\frac{f}{145Hz}*j}$$
- again approximate with two straight lines

### Building a High Pass from a Low Pass
$$\frac{\frac{f}{f_o}*j}{1+\frac{f}{f_o}*j} = \frac{f}{f_o}*j*\frac{1}{1+\frac{f}{f_o}*j}$$
- that right-most term is a low-pass
	- adding this to $\frac{f}{f_o}*j$ (which is a straight line with a positive slope $\frac{1}{f_o}*j$ on a log-log graph) using the properties of $\log$ shows the correct high-pass frequency response
		- adding 1 doesn't change anything because $\log 1 = 0$
		- 

## Band Pass Filters
$$\frac{V_\text{out}}{V_\text{in}}=\frac{\frac{f}{14.5Hz}*j}{(1+\frac{f}{145Hz}*j)(1+\frac{f}{14.5Hz}*j)}$$
- represent with two straight lines, with slopes 1 and -1

### Building a Band Pass Bode Plot
- includes a line with positive slope, intersecting 1 at $f_o$ of the high-pass component, then a straight line at 1 with 0 slope, then a line with negative slope starting at $f_o$ of the low-pass

# dB
- use of logarithmic scales to represent wide ranges
	- Bel is an order magnitude change in **power**
- logarithmic measure of power gain: $dB = 10*\log(\frac{\text{Power}_\text{out}}{\text{Power}_\text{in}})$
	- if power out is 1 and power in is 1, implies 0 dB
	- decreasing the power out means dB will be negative
		- e.g. decreasing power by a factor of 10 yields -10 dB
- power is proportional to $V^2$
	- so by voltage gain: 10x change in voltage is 100x change in power (20 dB change)
	- 6dB is a 2x change in voltage
	- for voltage: $dB = 20*\log(\text{Gain})$
		- 20dB per decade in voltage