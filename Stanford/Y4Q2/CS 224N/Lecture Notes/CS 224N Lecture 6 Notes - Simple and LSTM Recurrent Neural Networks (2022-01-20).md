#Stanford #Stanford-Winter-2022 #CS #CS224N #NLP #deep-learning #RNNs #LSTMs
___
# Lecture Plan
1. RNN language models, cont.
2. Other uses of RNNs
3. Exploding / vanishing gradients
4. LSTMs
5. Bidirectional / multi-layer RNNs

# Review: The Simple RNN Language Model
from [[CS 224N Lecture 5 Notes - Dependency Parsing II, Language Models and Recurrent Neural Networks|last time]]: recall flow: words / one-hot vectors -> word embeddings -> hidden states of previous words in the sequence -> softmax probability distribution for next work in the sequence

## Backpropagation for RNNs
- also from [[CS 224N Lecture 5 Notes - Dependency Parsing II, Language Models and Recurrent Neural Networks#Backprop for RNNs|last time]]
- each transition step $t$ uses the $W_h$ matrix -- these are all equal -- which is equivalent to separate "outward" branches, and gradients *sum* at outward branches
	- **backpropagation through time**

## Generating text with an RNN Language Model
- can use RNN-LM to generate text using **repeated sampling**
	- sampled output becomes next step's input (**autoregressive**)
- result? kinda funny, doesn't make sense, but *more* coherent than the $n$-gram language model output

# Evaluating Language Models
standard evaluation metric is **perplexity**
$$\prod_{t=1}^T\bigg(\frac{1}{P_{\text{LM}}(x^{(t+1)}\mid x^{(t)},\dots,x^{(1)})}\bigg)^{1/T}$$
- averaged inverse probabiliy of corpus, according to the language model, normalized by the number of words $T$
	- big is bad, small is good...
- equal to the *exponential of the cross-entropy loss* $J(\theta)$!
	- could just evaluate using the metric of entropy and say low entropy is good...
	- but easier to explain:
		- perplexity = 27 equivalent to rolling a 27-sided die and getting a 1 (if each side of die is equally probable)
		- also perplexity numbers are bigger and move more
- RNNs have greatly improved perplexity from ~100s to ~40 (2-layer LSTM-2048 called "Ours large" has perplexity = 39.8)

# Recap
**RNNs:**
- take sequential input of any size, and output next token in sequence
- $\neq$ language models! other applications
	- part-of-speech tagging, named entity recognition
	- sentence classification e.g. sentiment classification (a task involving a larger piece of text)
		- how to compute sentence encoding?
			- *basic way*: use final hidden state
			- *better way*: use element-wise max or mean of all hidden-states
	- more generally as a **language encoder module**
		- question answering, machine translation, etc.
		- e.g. one example for the default final project: building a Q&A system
			- RNN acts as a "question encoder", part of a larger neural system
	- to generate text (speech recognition, machine translation, summarization, etc.)
		- examples of *conditional language models* (machine translation covered in much more detail [[next class]])

## Terminology & look forward
- RNN we've seen so far is the simple/vanilla/**Elman RNN**
- later today: other flavors like **GRUs** and **LSTMs** (and **multi-layer RNNs**)

# Vanishing and Exploding Gradients
- RNNs in the way we've described aren't used often due to these problems... has to do w/ backprop

## Vanishing Gradients
- e.g. $\frac{\partial J^{(4)}}{\partial h^{(1)}}$? with a 4-layer RNN
	- $=\frac{\partial h^{(2)}}{\partial h^{(1)}}\times \frac{\partial J^{(4)}}{\partial h^{(2)}}$
	- $=\frac{\partial h^{(2)}}{\partial h^{(1)}}\times\frac{\partial h^{(3)}}{\partial h^{(2)}}\times\frac{\partial h^{(4)}}{\partial h^{(3)}}\times \frac{\partial J^{(4)}}{\partial h^{(4)}}$
		- if these partials are small, our gradient is going to *vanish* -- smaller and smaller gradient flow headed backwards through our network
		- we have a product of $W_h$ matrices in our total gradient -- if the elements are small, $W_h^l$ is exponentially more problematic for higher values of $l$
			- if the eigenvalues of $W_h$ are less than 1, $\frac{\partial J^{(i)}(\theta)}{\partial h^{(i)}}W_h^l\approx 0$ (for large $l$)
- see Pascanu et al. 2013, "On the difficulty of training recurrent neural networks" ( #TODO ==to cite==)
- *gradient signal from far away because it's **much smaller** than gradient signal from close-by*
	- signals are updated only w.r.t. near effects, not long-term ones
- the effect: can't capture long-term dependencies, just like you can't with a 4- or 5-gram model

## Exploding Gradients
- the opposite problem! if $W_h$ actually has large values, $W_h^l$ becomes massive for large $l$
	- this situation is actually just really unstable, whether exploding or vanishing...
- if gradient becomes too big, then SGD update step becomes too big
	- can cause **bad updates**: we can step too large and reach some weird place in the parameter space with large loss
	- worst case: might end up with `inf`s / `NaN`s in the network and will have to restart training

### Gradient Clipping
- standard fix
- if norm of gradient is greater than some threshold, scale it down before applying the SGD update
	- divide all gradients through by norm
	- in practice this works just fine -- must remember to clip gradients, but exploding gradients are easy problems to solve
	- even just clipping to some max element-wise would work, although it's cruder

## How to fix the vanishing gradient problem?
- we need to solve this to handle long-term dependencies
- it's too difficult to learn to preserve info. across many timestamps
- in vanilla RNN, hidden state is being constantly *overwritten*
	- what about an RNN with separate memory that can be *added to*, recording the history more explicitly?

# Long Short-Term Memory RNNs (LSTMs)
- kind of RNN (Hochreiter, Schmidhuber 1997) designed to fix the vanishing gradient problem
	- also Gers et al. 2000 (the "forget gate" introduced here)
- on step $t$ there is a hidden state $h^{(t)}$ and cell state $c^{(t)}$
	- both vectors of length $n$
	- cell stores the long-term information
	- LSTM can read, write, and erase information from the cell (conceptually like the RAM in a computer)
		- selection of what info is read/written/erased is controlled by three corresponding **gates**
			- gates are vectors of length $n$, that says say each dimension, how much should be read/written/erased
				- each element can be between open (1) and closed (0)
				- gates are *dynamic*: values computed dependant on current context
- start with sequence of inputs $x^{(t)}$
	- forget gate $f^{(t)}$, input gate $i^{(t)}$, and output gate $o^{(t)}$
		- which in previous cell state is forgotten, vs. which parts of new input content are written to the cell, vs which parts of the cell contribute to the output hidden state
		- non-linearity is a sigmoid so values between 0-1
	- to calculate a new cell, multiply using the input, output, and forget gate from the previous cell state
	- new hidden state takes `tanh` of cell state multiplied by the output gate
	- gates applied using element-wise (Hadamard) product $\circ$
	- $+$ operation is the key: to compute the new cell value, *add together* part of the old cell value plus what you've calculated from the latest input state
		- fundamentally different to simple RNN which has fundamenally *multiplicative* character
- also trained via backpropagation through time, w/ separate weight matrices for input, output, and forget gates ($W_{\{f, i,o\}}$ and $U_{\{f, i, o\}}$ and $b_{\{f, i, o\}}$ -- see slides...)
- typically strong incentives to just use the `lstm` modules provided in DL libraries -- Nvidia `lstm` is heavily optimized for `cuda` on modern GPUs

# Gated Recurrent Units (GRU)
- proposed by Cho et al. 2014 ( #TODO cite) as a simpler alternative to LSTMs
- two gates:
	- **update gate** $u^{(t)}$ controls which parts of hidden state are updated / preserved
	- **reset gate** $r^{(t)}$ controls which parts of hidden state are used to compute new content
- new hidden state content:
	- reset gate selects useful parts of prev. hidden state
	- this + current input computes new hidden content

# LSTMs vs. GRUs
- LSTMs are most commonly used, then GRUs
	- *good default choice* to produce a sequence model w/ long-term memory
	- switch to GRUs for speed + fewer parameters
	- LSTMs can store unboundedly large values in memory cell dimensions, and can learn relatively easily how to count
		- uses a single dimension as a counter
		- since GRUs use averaging on their update gate, there is no way to count like this

## How to LSTMs solve vanishing gradients?
- easier for the RNN to preserve info across many timestamps
	- if forget gate is set to 1 for a cell dimension (and input gate set to 0), then info of the cell is preserved indefinitely
	- in practice, means you get about 100 timestamps of info. preserved
- LSTM doesn't *guarantee* no vanishing/exploding gradients, but in practice it's much better about it
	- great real world success! SoTA results in everything circa 2013-2015
		- now (last 3-4 years) replaced largely by **transformers**

# Vanishing/exploding gradients outside of just RNNs
- really any deep network with lots of multiplications happening across many layers
	- but particularly pronounced for RNNs where there are long sequences w/ identical matrices

# Bidirectional & Multi-layer RNNs
## Motivation
- previously did "sentence encoding" using element-wise max / mean of hidden states
	- can think of hidden states as "contextual" representations of the words at that point in the sequence
	- important to use context from the *right* of the word as well as the left (as in the sentence in sentiment analysis, "The movie was *terribly* exciting!")
## Bidirectional RNNs
- run another LSTM from the back of the sentence to the beginning
	- then form concatenated hidden states from the hidden states from the Backward RNN + Forward RNN

## Multi-layer RNNs
- RNNs already "deep" in the dimension over timestamps
- make them deep in another dimension by applying additional RNNs ("stacked" RNNs)
	- take outputs of RNN 1 and feed them as inputs into RNN 2 (& continue taking outputs into inputs at higher levels)
	- high-performing RNNs are usually multi-layer like this
		- but not as deep as convolutional / feed-forward networks!
		- in practice, 2 layers makes for much higher performance, and then diminishing returns...

# Practical takeaways
1. LSTMs are powerful
2. Clip your gradients
3. Use bidirectionality when possible
4. Multi-layer RNNs are more powerful
	1. but you need skip connections when it gets deep