#ENGR40M #ENGR #Stanford #Stanford-Winter-2022 #lecture-notes 
___
- precise representation of tones for signals

# Learning Objectives
- understand how to formally write a signal as a set of tones
	- the Fourier Transform

# Waveforms
- represented as summations of sines and cosines

# Fourier Series
- only work for repetitive signals
	- since sine waves repeat
- assuming signal repeats every $T$ seconds
	- lowest sine wave fitting within theis period has the period $T$

$$v(t) = a_0 + \sum_{n=1}^\infty\bigg( 
a_n\cos\frac{2n\pi t}{T} + b_n\sin\frac{2n\pi t}{T} \bigg)$$
- just enumerate every sine wave able to fit in the period

$$v(t) = \sum_{n=0}^\infty\bigg( 
a_n\cos\frac{2n\pi t}{T} + b_n\sin\frac{2n\pi t}{T} \bigg)$$
- when $n=0$: $a_o\cos 0 + b_o \sin 0 = a_o$
	- called the **zero frequency term**
- First term with $n=1$ is called the **fundamental frequency**
	- Every other wave that can fit evenly within the period is *harmonically related* to the fundamental frequency (some integer multiple of the fundamental)

# Frequency Domain Analysis
- understanding signals by decomposing them into tones will be very helpful when we consider circuits including capacitors