#Stanford #Stanford-Winter-2022 #CS #CS224N #NLP #deep-learning 
___
**Key goal**: should be able to read word embeddings papers by end of class

# Course Organization
- OH: 5:30 - 8:30pm on Nooks, M-F

# Review: Main idea of word2vec (from [[202201041517 CS 224N Lecture 1 Notes (2022-01-04)|previous lecture]])
- Start with random word vectors (2 per word)
- Iterate through each word position in corpus
- Try to predict surrounding words using word vectors: $P(o|c)$
- **Learning**: update vectors so probabilities (ability to predict actual surroundings) increase

- maximizes the objective function by putting similar words nearby in (high-dimensional) space
	- what about functional words like "a" or "the"?
		- in high-dimensional spaces you can actually be close to lots of things... quite unintuitive

## Parameters
- vectors for each word (one for outside (context), one for center)
	- Can have two matrices

## Computations
- model makes the same predictions are every position -- too simplistic!
	- bag of words model
	- but good enough to still work...

## Learning
- **(Stochastic) Gradient Descent** to minimize $J(\theta)$ by changing $\theta$
- Learning rate
	- Way too big: stochastic gradient descent will actually diverge...
	- Too big: things will still work... just inefficiently
	- Way too small: will learn too slowly

## Word2vec algorithm family
- weird detail that we have two different vectors per word
	- just done to make the math easier!
		- if using the same vector, you would sometimes have the same word present in the center and the context... then you have an $x^2$ term that you have to handle properly
		- Actually sharing the vector improves performance a little bit

### Two model variants
1. Skip-grams (SGs)
	- predict context ("outside") words given center word
2. Continuous Bag of Words (CBOW)
	- predict center word from (bag of) context words

### Negative Sampling
Naive softmax:
$$P(o|c)=\frac{\exp(u_o^Tv_c)}{\sum_{w\in V}\exp(u_w^Tv_c)}$$
- the normalization term (denominator) is computationally expensive -- ranges over whole vocabulary
- hence, implement with *negative sampling* (==will cover in HW2!==)
- **Main idea**: train binary logistic regressions for a true pair (center word paired with words in context window) versus several "noise" pairs (center word paired with random words)
	- "Noise contrastive estimation"
- From [[Mikolov et al. 2013, "Distributed Representations of Words and Phrases and their Compositionality".pdf]]
	- Overall objective fxn:
$$J_{\text{neg-sample}}(u_o, v_c, U) = -\log\sigma(u_o^Tv_c)-\sum_{k\in\{K\text{ sampled indices}\}}\log\sigma(-u_k^Tv_c)$$
- $\sigma$: the logistic function $\sigma(x) = \frac{1}{1+e^{-x}}$
	- Maps real number into probability between 0 and 1
- Maximizes the probability that a real outside word appears; minimize probability that random words appear around center word
- Trying to minimize negative term $-\log\sigma(u_o^Tv_c)$
- Because of the minus sign in $\log\sigma(-u_k^Tv_c)$, large values for these probabilities will be bad for the objective
- How to sample? Kind of based on frequency of the words themselves, but not quite
	- Sample with unigram distribution $U(w)$: $P(w)=U(w)^{3/4} / Z$
		- The power makes less frequent words be sampled slightly more often (hyperparameter)

#### Stochastic Gradients with Negative Sampling
- iteratively take gradients at each window
- have only at most $2m+1$ words plus $2km$ negative words (with negative sampling) -- meaning $\nabla_\theta J_t(\theta)$ is very sparse!
	- Not true of naive softmax, where we touch the whole vocabulary
	- Either need sparse matrix update operations to only update certain rows, or keep around a hash for word vectors
		- This is a particular issue for more advanced optimization methods in Adagrad family (e.g. Adam) -- don't work right when a lot of the rows in the weight matrix aren't being updated at all
		- Make sure you aren't passing large updates around!

# Why not capture co-occurrence counts directly?
- weird to iterate through whole corpus -- why not just accumulate statistics of what words appear next to each other?
	- build co-occurrence matrix $X$ $\rightarrow$ leading to "Latent Semantic Analysis" of words occurring in the same "documents"
		- whole document or window
		- dot products could give a rough similarity metric between pairs of words
		- vectors increase in size with the vocabulary, so impractical to store efficiently (also very sparse)
			- subsequent classification models have sparsity issues, meaning less robustness

## Classic method: dimensionality reduction on co-occurrence matrix $X$
- use SVD on $X$ $\rightarrow$ factorize into $U\Sigma V^T$ where $U$ and $V$ are orthogonal and $\Sigma$ is diagonal
	- classic linear algebra result
	- retain only largest $k$ singular values (top $k$ entries in diagonal of $\Sigma$)
		- gives us $\hat{X}$, the best rank-$k$ approximation of $X$ in terms of least squares
			- $k$ is heuristic: around 100, 200, 300...

## Other solutions for $X$
SVD doesn't work well on raw counts...

- scaling the counts in the cells can help a lot
	- function words (the, he, has) are too frequent, meaning syntax has too much impact (Zipfian distribution)
	- log frequencies, $\min(X, \sim 100)$, ignore the function words, ...
- ramped windows that count closer words in the context window more
	- Word2vec uses a ramp like this
- use Pearson correlations instead of counts, then set negative values to 0?

# Semantic patterns in scaled vectors
- fixed vector additions can, e.g., get you from "drive" to "driver" etc.

# Moving towards GloVe
- two different literatures developing in parallel
	1. More psychology-oriented literature: LSA, HAL, COALS, etc. starting with co-occurrence matrices
		- fast training and efficient use of stats
		- to capture word sim.
		- disproportionate importance given to large counts (problems discussed in [[202201061516 CS 224N Lecture 2 Notes - Word Vectors, Word Senses, and Neural Network Classifiers (2022-01-06)#Other solutions for X]])
	2. "Neural-land": Skip-gram, CBOW, NNLM, etc.
- could you combine these two things to get the best of both worlds?
	- *ratios of co-occurrence probabilities can encode meaning components*
		- not enough to just look at the *size* of probabilities -- compare them with other probabilities, e.g. $\frac{P(x|\text{ice})}{P(x|\text{steam})}$ as shown in slides
		- how to capture?
			- **log-bilinear model**:
$$w_i\cdot w_j = \log P(i|j)$$
			- objective function:
$$J = \sum_{i, j = 1}^{V}f(X_{ij})(w_i^T\tilde{w}_j + b_i + \tilde{b}_j - \log X_{ij})^2$$
				- intercept terms $b_i$ and $\tilde{b}_j$ for both words
				- this is used to capture this property above: ratios of probabilities of word co-occurrences will be encoded in the embedding vectors

## Evaluating GloVe (and NLP in general)
- how do we evaluate word vectors?
- **Intrinsic** vs. **Extrinsic** evaluation

### Intrinsic evaluation
- on some specific / immediate subtask that's very related to what you just built
- like word similarity / analogy task
	- analogy task:
		- a:b::c:?
$$d = \arg\max_i\frac{(x_b - x_a + x_c)^T x_i}{\lvert\lvert x_b - x_a + x_c \rvert\rvert}$$
		- can't use input words as the answer
		- evaluation for GloVe:
			- good dimensionality is ~300 -- even doubling that to 600 has only marginal improvement
				- Zi Yun and Yuanyuan Shen 2018, "On the Dimensionality of Word Embedding" -- using matrix perturbation theory, fundamental bias-variance tradeoff in dimensionality selection for word embeddings
			- Wikipedia is *much* better than news text for learning semantic relations (which makes sense as it's an encyclopedia)
	- also comparatives / superlatives, relations like Company <> CEO, etc.
- very fast to compute and helps with simply understanding the system
- some doubt -- will these embeddings help us do *real* tasks?
- *example*: word vector distances and correlations w/ human judgements
	- word similiarities from psychology: datasets like [WordSim353](http://www.cs.technion.ac.il/~gabr/resources/data/wordsim353/)

### Extrinsic evaluation
- on a "real" (end-user) task (e.g. machine translation)
- takes a long time to compute accuracy
- if there are problems, do they reside in the subsystem you're evaluating or its interaction with other subsystems? not *exactly* what you're measuring...
	- if replacing exactly one subsystem with another improves accuracy, you're good!
- *example*: **Named Entity Recognition**: e.g. recognizing "*Chris Manning* lives in *Palo Alto*"
	- datasets like MUC7

# Word senses / word sense ambiguity
- most words have lots of meanings! (common words, and words existing for a long time)
	- -> Huang et al. 2012, "Improving Word Representations Via Global Context And Multiple Word Prototypes"
		- idea: cluster word windows around words, then retrain w/ each word assigned to multiple different clusters
			- bank$_1$, bank$_2$, etc.
			- if you don't do this, the representation of "bank" ends up as the weighted average of all the different representations -- not so much a problem in high dimensional space! even though it might look problematic in 2D projections
- Arora et al. 2018, "Linear Algebraic Structure of Word Senses, with Applications to Polysemy"
	- different senses of the word are in *linear superposition* (weighted sum) in standard word embeddings like word2vec
		- $v_{\text{pike}} = \alpha_1 v_{\text{pike}_1} + \alpha_2 v_{\text{pike}_2} + \dots$ where each $\alpha$ encodes the relative frequency of the sense
		- because of **sparse coding** you can actually put apart the different senses

# Classification review and notation
- **supervised learning**: training dataset consisting of samples
	- training data $\{x_i, y_i\}^N_{i=1}$
	- each $x_i$ is an input with dimension $d$
	- $y_i$ are labels (one of $C$ classes)
- learn parameters or weights so that we can divide the different classes
	- **traditional ML approach**: train softmax / log. reg. weights $W\in \mathbb{R}^{C\times d}$ to determine the decision boundary (hyperplane)
		- linear classifier so linear decision boundary
	- modern **deep learning / neural network** approach we've been covering is different
		1. more than that -- learn a good representation of our input data points (like word vectors) that will allow us to learn classification better
		2. traditionally in stats, word tokens etc. represented as indicator variables (localist representation), as opposed to our **distributed** representation (dense vector)
		3. for traditional stats, using shallow classifier like a linear classifier trying to cut high dimensional space w/ hyperplane --> deep learning is **non-linear classification**