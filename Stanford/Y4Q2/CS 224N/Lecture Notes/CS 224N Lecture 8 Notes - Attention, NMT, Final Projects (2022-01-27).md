#Stanford #Stanford-Winter-2022 #CS #CS224N #deep-learning #neural-networks #attention #lecture-notes 
___
# Attention
## The sequence-to-sequence bottleneck problem
- information bottleneck: no matter how long first sentence is, we have to train a NN to store all useful info in final hidden state vector... b/c that's what passed over to decoder network
	- attention is a *more flexible way* of preserving information

## What is Attention?
- at each step of the decoder, use *direct connection* to the encoder plus the latest hidden state
- attention scores = dot product (similarity score or "attention score") between each decoder token and each hidden state of the encoder model
	- push attention scores through a softmax to get an **attention distribution**
	- then: construct *weighted average* of all of the encoder states based on the attention distribution
	- then: concatenate attention output with decoder output to form $\hat{y}_i$, the next decoder output word
		- sometimes we take the attention output and *also* feed it in to the decoder input

### In equations
- have decoder hidden states $h_i\in\mathbb{R}^h$
- decoder has hidden states $s_t\in\mathbb{R}^h$ at timestep $t$
- get attention scores $e^t$ for each step, each of which is $s_t^\top h_i$
- Attention distribution $\alpha^t$ for this step formed as $\alpha^t = \text{softmax}(e^t)$
- use attention distribution to get weighted average attention output $a^t$ for this timestep
	- $a = \sum_{i=1}^N\alpha_i\cdot h_i$

## Pros
- significantly improves NMT performance
	- allows decoder to focus on *certain parts* of the source
- provides a more "human-like" model of the MT process (you look at the entire sentence while translating...)
- also *solves the bottleneck problem* since decoder can just "look everywhere" in the encoder to get the information it needs
- helps solve the vanishing gradient problem
	- because shortcuts to faraway states
- provides *some* notion of **interpretability**
	- get a kind of soft **alignment** for free! between source and target sentences
	- but... some subsequent work has shown the picture more complex than this: not exactly an "alignment model"...

## Attention Variants
- we have some values (encoder hidden states) and a query
	- attention involves working out attention scores over the values, taking softmax to get distribution, then using distribution to get weighted sum that's the attention output
	- this is the standard recipe!
- variance: *how to compute attention scores*?
	1. basic dot-product
		- the simplest way
		- requires dimensionality of the encoder and decoder to be equal
	2. **multiplicative attention**
		- $e_i = s^\top W h_i$
		- sticking matrix in between query and values
			- "to work out similarity, only consider parts of the vectors, or otherwise handle the different dimensions in different ways"
		- potential flaw: lots of parameters in that $W$ matrix...
	3. **reduced-rank multiplicative attention**
		- $e_i = s^\top(U^\top V)h_i = (Us)^\top(Vh_i)$ for low-rank matrices $U$, $V$
		- these "transformation matrices" apply to the different hidden states
	4. **additive attention**
		- $e_i = v^\top\tanh(W_1h_1 + W_2s)\in\mathbb{R}$
		- really a single feed-forward neural net layer

### In other deep-learning domains
- can use in many other architectures (not just seq2seq) and on many other tasks (not just MT)!
- *more general definition*: given a set of vector values and a vector query, **attention** is a technique to compute the weighted sum of the values, dependent on the query
	- a "selective summary" of the information contained in the values
	- a way to obtain a *fixed-size representation* of an arbitrary-sized set of representations

# NMT: Still not solved!
- Lots of problems with out-of-domain vocabulary
- Gender biases picked up from training sets
- uninterpretable systems can do strange things, e.g. when given garbage inputs
	- this problem seems to be solved at Google Translate, though!
- overall today, excitement has largely moved to other tasks like QA, inference, natural language generation, etc.

# Assignment 4
- Cherokee-English machine translation!
	- extremely low-resource language pair
	- writing system is a syllabary of symbols for each CV unit (85 letters)
		- a lot of languages are consonant-vowel languages
		- but this one writes a syllable with one letter!

# Final Projects
- 43% of grade overall
- Perfectly fine to make use of existing code / frameworks
	- Expected to tell what of other people's stuff we're using -- graded in terms of "value-add"

## Two Options
1. Default final project (SQuAD question answering, with 2 sub-variants)
	1. A "build-it-yourself" question answering system to tackle SQuAD 2.0
		- using PyTorch starter code
		- good learning experience of building a neural net by yourself
			- but also a bit of a "historical" experience
	2. Building a robust QA system that works on different datasets & domains
		- starting point is a pre-trained LM (DistilBERT) -- work mainly on robustness methods
	- good to do if limited experience w/ research, don't have a clear idea of what to do, want lots of guidance & a goal
		- path to success is not something that looks kinda weak compared to what you could've done with the default one
1. Custom final project
	- must be proposed & approved

## Project Proposal
- due *Tuesday Feb 8, 3:15p*

## Project Milestone
- due *Thursday Feb 24, 3:15p*
- should be *halfway* done by then, with some initial results and a system that's working

## Finding Research Topics
Two basic starting points:
1. *Nails* approach: start with a domain / problem of interest and try to find good / better ways to address it
2. *Hammers* approach: start with a technical method / approach, and work out ways to extend or improve it, or apply it to new domains

### Project Types
1. An application / task of interest and explore how to approach / solve it effectively
	- often using an existing model
	- e.g. with a Kaggle / bake-off dataset
2. Implement a complex neural architecture & demonstrate performance on some data
3. Come up with a new / variant NN model / approach and explore the empirical success
4. Analysis project. Analyze the behavior of a model (how does it represent linguistic knowledge or certain phenomena?)
	- an "understanding" sort of paper
5. Rare theoretical project: show some interesting, non-trivial properties of a model type / data / data representation

### Where to look for interesting projects?
- ACL anthology for NLP papers
- Online preceedings for NeurIPS, ICML, ICLR, etc.
- Past cs224n projects on the class website
- Preprent servers like arXiv
- Look for an interesting problem in the real world!
	- Read Hal Varian: How to Build and Economic Model in Your Spare Time

# The Deep Learning Revival
- in the early days of "deep learning revival" (2010-2018), most work was on defining / exploring better architectures
	- e.g. slightly improving a summarization system by moving from basic attention to copying attention
- in 2019-2022, that approach is dead
	- it's hard to make these types of improvements by changing architectures
	- most work downloads a big pre-trained language model (which fixes the architecture)

## NLP in 2022
- `pip install transformers` by HuggingFace 🤗
- tutorial *next Friday* on how to use HuggingFace transformers!
- A lot of what is exciting now is problems that work within / around the world
- Evaluating / improving models for something other than just accuracy
	- Robustness to domain shift
- Bias, trustworthiness, etc.
- Scaling models up and down
	- Model pruning, model quantization, etc.
	- Building small yet performant models is big
		- Competitions like "Efficient QA"
- Looking to achieve more advanced functionalities
	- Compositionality, systematic generalization, fast learning (meta-learning), smaller problems w/ smaller amounts of data, training quicker, etc.
	- Look at BabyAI and gSCAN