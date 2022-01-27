#Stanford #Stanford-Winter-2022 #CS #CS224N #machine-translation #deep-learning #NLP #attention #lecture-notes 
___
- explains the stuff for assignment 4 -- neural machine translation
	- due Thursday of next week, Feb. 3
	- hardest assignment coding-wise
	- try going to in-person OH!

# Pre-Neural Machine Translation
- before neural machine translation (circa 2014)

**Machine Translation**: translating sentence $X$ from one language (*source language*) to another (the *target langauge*)
- concurrent w/ foundational work on automata, formal languages, probability, information theory
- originally: codebreaking, and reading tables for operating artillery
	- so is MT just "codebreaking between languages"?
	- a lot happened before the term AI was coined (in 1956 by John McCarthy)

## 1990s-2010s: Statistical Machine Translation
- build big probabilistic translation model w/ statistics on language
- e.g. find best English sentence $y$ given French sentence $x$:
	- $\arg\max_y P(y\mid x)$
	- use Bayes rule: $\arg\max_y P(x\mid y)P(y)$
		- makes it easier to factorize this problem, under certain assumptions
		- translation model: models how words and phrases should be translated (the $P(x\mid y)$ component)
		- langauge model handles $P(y)$ (handles details of producing grammatically fluent English)
- we need a large amount of *parallel data* (e.g. the Rosetta stone)
	- lots of good government sources of parallel text (e.g. political ordinances from the EU, or Canadian government docs in French & English)
	- how to learn translation model from parallel corpus?
		- introduce *alignment variable* $a$ -- and learn $P(x, a\mid y)$
			- **alignment** = word-level correspondance between two pieces of text
			- goes wrong in some ways:
				- some words have no equivalent in the target language (called "spurious" words)
				- alignment can be many-one
				- alignment can be one-many (called a "fertile" word)
				- alignment can be many-many (phrase-level misalignment)
			- $a$'s are *latent variables* -- aren't explicitly specified in the data!
				- require use of special learning algorithms (e.g. Expectation-Maximization) for learning parameters of distributions
				- largely unsupervised -- inducing alignment variables

### Decoding for SMT
-  how to compute $\arg\max$?
- could enumerate every possible $y$ and calculate probability -- exponentially expensive!
- *answer*: assume *strong independence* between the language and translation models (the $P(x\mid y)$ and $P(y)$ components)
	- use dynamic programming!
	- called *decoding*
- we've learned *possible alignments* for words / phrases in the source language
	- start with empty translation, explore forward in search to fill out possible alignments
	- continue covering more and more of the source sentence
	- once you've completed coverage you have a candidate translation
- a lot of weight for choosing which candidate is correct comes down to the language model analyzing the probability of the translation $P(y)$

### In Summary
- huge research field
- best systems were extremely complex w/ lots of components
	- separately designed components, lots of feature engineering
	- lots of human effort to maintain (different systems for each language pair)

# Neural Machine Translation
- a way to do machine translation with *single end-to-end neural network*
- neural net architecture is called **sequence-to-sequence** (seq2seq) models
	1. run encoder RNN over source sentence
	2. pass encoding over to **Decoder RNN** (a language model that generates a target sentence, *conditioned on encoding*)
		- use final hidden state from encoding as starting hidden state for the decoder
- general notion is an **Encoder-Decoder** model
	- one model takes input & produces neural representation, and then second model produces output based on that representation
	- more general than just MT
		- summarization (long text -> short text)
		- dialogue (previous utterances -> next utterance)
		- parsing (input text -> output parse as a sequence)
		- code generation (natural language -> python code)
			- appears in OpenAI's Codex
	- specifically an example of a **conditional language model**
		- language model b/c the decoder is predicting the next word of target sentence $y$
		- conditional b/c predictions are conditioned on the source sentence $x$
		- directly calculates $P(y\mid x)$ using the chain rule, applying additional conditioning context at each step

## How to train NMT model?
- get a big parallel corpus...
	- but now some work on "unsupervised NMT," data augmentation, etc.
	- lots of pairs of source sentences + target sentences
		- compute loss for each step in the decoder sequence
			- use **Teacher Forcing**: give model the correct decoded word of the sentence, and have it try and predict the next word $\hat{y}_i$ (then compute $J_i$ at this position)
			- then $J=\frac{1}{T}\sum_{t=1}^T J_t$
		- seq2seq then optimized as a *single system* -- losses backpropped all the way from the decoder through the encoder model as well
			- "end-to-end" backprop
			- learning word embeddings as we go also (as usual)

### Problems
- as encoder-decoders get longer and more complex, harder to have faith that backprop algorithm will *actually* work
- can use forget states with very low values to ensure information is preserved across long sentences -- but long sequences always an issue (can forget where you came from...)

## Multi-layer deep encoder-decoder machine translation networks
- multi-layer encoder builds up sentence meaning
	- allows network to learn *more complex representations*
	- lower RNNs should compute *lower-level features* (same with higher RNNs)
	- the higher performing ones are usually multi-layer
		- requires skip-connections / dense-connections to train deeper ones (e.g. 8 layers)
		- transformers by comparison are usually 12 / 14 layers
- **conditioning = bottleneck**

## Greedy Decoding
- decode each word in the target sentence by taking $\arg\max$ at each step of the decoder
	- corresponds to greedy search -- choosing highest prob. at each step
### Problems
- no way to undo decisions / recover!
	- how to fix?

## Exhaustive Search Decoding
- find the length $T$ translation $y$ that maximizes $\prod_{t=1}^T P(y_t\mid y_1,\dots,y_{t-1}, x)$
- could try computing *all* translation sentences
	- this doesn't give enough *constraint* to the search problem...

## Beam Search Decoding
- at each time-step of the decoding, keep track of $k$ most probable potential translations ("*hypotheses*")
	- $k$ is "beam size" (typically 5-10 in NMT)
	- each hypothesis $y_1,\dots,y_t$ has *score* with log probability $\sum_{i=1}^t\log P_{\text{LM}}(y_i\mid y_1,\dots,y_{t-1}, x)$
		- scores are negative -> higher the better
- not *guaranteed* to find optimal solution, but still efficient
- at each next step, we collapse back down to the beam size and only preserve top $k$ competing hypotheses
	- top scoring hypothesis at the end is our complete translated sentence

### When to stop beam searching?
- in greedy decoding you stop when hitting an `<END>` token
- in beam search, different hypotheses may produce end tokens at different timestamps
	- hypotheses are *complete* when reaching end tokens
		- *caveat*: do we just select the hypothesis with the highest score?
			- log-probability gets more and more negative with longer and longer sequences -- subset of the correct hypothesis will have higher prob. than whole correct hypothesis
			- fix: normalize by length -- choose one with best *average log probability by token*
				- language model is always under pressure to choose something short but well formed
	- usually continue until cutoff timestep $T$, or until we have $n$ completed hypotheses

## Advantages of NMT
- better performance
- more fluent
- better use of context / phrase similarities (compared to statistical MT)
	- better representations of the meanings of phrases (compared to the "phrase table" approach from statistical MT)
- single neural network optimized end-to-end (no subcomponents to be individually optimized)
- less human labor required: no feature engineering, and same method generalizes to all language pairs
- also way more compact -- phrase tables took up huge amounts of space
	- $n$-gram language models are also huge

## Disadvantages
- less interpretable / harder to debug
- more difficult to control
	- can't specify individual explicit rules for translation
	- concerns for safety! could translate weird / potentially toxic

## Evaluating NMT
- standard is an automatic way of doing evaluation
	- BLEU (**Bilingual Evaluation Understudy**)
		- proposed by IBM in the 1990s
		- have parallel text in your test set
			- what a human translator thought the translations should be
		- look at machine-generated translation and score for similarity by matching $n$-grams (typically up to 4)
		- also add a penalty for too-short system translations (because you're calculating precision only)
		- work out an *$n$-gram precision*
			- what % of words / phrases in the machine translation also appear in the human translation?
	- useful but imperfect!
		- there are many good ways to translate a sentence
		- good translations can still get poor BLEU scores due to low $n$-gram overlap

## Progress over time
- in the 2000s, people thought the way towards better accuracy was syntax-based SMT (e.g. using parse trees)
- neural MT systems started circa 2015, best systems by 2016 and onward