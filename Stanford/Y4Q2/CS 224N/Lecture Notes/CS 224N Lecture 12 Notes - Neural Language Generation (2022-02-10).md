#Stanford #Stanford-Winter-2022 #CS #CS224N #lecture-notes #NLP #neural-networks #deep-learning 
[[cs224n-2022-lecture12-generation-final.pdf|lecture slides]]
___
# Logistics
- next Thursday: first invited speaker
	- speaker will be remote, so class is live on Zoom that day
	- 1 reaction paragraph about thoughts on the lecture
- Monday, March 14 in the afternoon: *in-person*, *live* poster session for final project

## Final project advice
- publically available datasets are released with a train/dev/test structure
	- if there's no dev set, create one by splitting the training data!
		- point of the **dev set** is to measure progress and avoid overfitting -- must be independent set
			- be alert even to small overlaps
		- e.g. every 5 epochs or so, measure on dev set and see how well model is performing
		- too much dev set validation and you'll begin overfitting on your dev set: might help to have a second one!
	- fixed **test set** ensures that all models are assessed on the same gold data
	- weigh the usefulness of a larger one against the reduction of training set size
	- **cross-validation** helpful when not much data is available
	- we're *on the honor system* to only use test-set runs once development is complete
		- this means **use test set extremely few (ideally 1) time(s)**

### Getting your neural network to train
- neural networks want to learn!
	- if the network isn't learning, you're doing something to prevent it from doing so
	- can take a lot more time to figure out why model isn't working than it took to write the model in the first place

#### Experimental Strategy
- work *incrementally*
	- start w/ a simple model and get it to work
	- add bells & whistles one at a time and get model working at each step
- do initial runs on a tiny amount of data
	- 4-10 examples
		- maybe synthetic data is helpful here
	- you will see bugs more easily on a tiny dataset, and training is super quick
	- should make sure train accuracy is 100%
- model should achieve close to 100% / 0 loss on the full training data after optimization
	- overfitting on training data is *not* something to fear in deep learning: models are usually good because distributed representations share strength regardless of overfitting
- to get good generalization performance:
	- regularize until you don't overfit on dev data
		- **L2** or **early stopping**
		- most effective, generally: **generous dropout**
#### Details
- look at your data and collect summary statistics
- look at model's outputs and do **error analysis**
- find ways to examine / visualize internal representations and ensure they're sensible
	- attention distributions often visualizable
- tune hyperparameters, set smart learning rates, get correct initialization etc. -> important for success

### Finding data
- cool to collect your own data
	- "unsupervised" data approaches becoming more popular
	- websites that provide "annotations" like github stars, ratings etc. can be good sources of labels
- most people make use of existing and publically available datasets built by previous researchers
	- HuggingFace datasets
	- Paperswithcode datasets

# Agenda
1. What is NLG?
2. The simple neural NLG model / training algorithm
3. Decoding from NLG models
4. Training NLG models
5. Evaluating NLG systems
6. Ethical considerations

# What is NLG?
**NLP = NLU + NLG**
- natural language processing = understanding + generation
- traditionally, extremely lopsided, about 90% of work dedicated to NLU, 10% to NLG
- any task that requires language production for human consumption requires NLG
	- *coherent* and *useful* language for human use
- uses: machine translation, digital assistants (dialogue agents), summarization systems

# A simple neural NLG model
review of [[CS 224N Lecture 6 Notes - Simple and LSTM Recurrent Neural Networks (2022-01-20)|lecture 6]]
- autoregressive text-generation models take a sequence of tokens $\{y\}_{<t}$ and outputs next token $\hat{y}$
	- trained to maximize probability of the next token given the preceding words
	- classification task: predict the *actual word* from the training data
	- do this with **teacher forcing** -- reset to the ground truth at every timestep

## Decoding
- at inference time, algorithm defines a function to select a token from this distribution
$$\hat{y}_t = g(P(y_t\mid\{y_{<t}\}))$$
- where $g(\cdot)$ is the decoding algorithm
	- obvious choice is to greedily choose the highest probability next word
		- but we can do better!

### Improving on greedy methods
recall [[CS 224N Lecture 7 Notes - Machine Translation, Sequence-to-Sequence and Attention (2022-01-25)|lecture 7]] on NMT
- **argmax decoding** selects highest probability token
- **beam search** (from lecture 7) is still at heart a greedy algorithm, but with a wider exploration of candidates
#### Problems
- greedy methods get repetitive
	- why? negative log likelihood decreases through a repeat loop, with each successive iteration
	- how to reduce?
		- heuristic: penalize the repetition of $n$-grams
		- more advanced: maximize embedding distance, introduce **coverage loss** (preventing attention mechanism from attending to the same words), or an **unlikelihood objective** (penalizing likelihood of already-seen tokens)
		- but at heart: greedy methods are very much *not* the way humans generate language. you have to introduce low probability stuff to be interesting with you language generation

#### Random sampling
- sample randomly from the distribution of tokens! $\hat{y_t}\sim P(y_t=w\mid\{y\}_{<t})$
	- *problem*: vanilla sampling makes every token in the vocab an option...
	- even if most of the probability mass is over a limited set of options, the tail is *really heavy*...
	- many tokens are probably *really wrong* given the context
- solution to this: **top-$k$ sampling**
	- choose something randomly from the top of the probability distribution ($k = 5, 10, 20$)
	- issue: can get cut off too quickly or too slowly -- hard to get a $k$ reasonable for all examples
		- want higher $k$ for flatter probability distributions and lower for spikier distributions
- better: **top-$p$ (nucleus) sampling**
	- sample from all tokens in the top $p$ cumulative probability mass
	- this varies $k$ based on the uniformity of $P_t$
#### Softmax temperature
- apply a temperature hyperparameter $\tau$ to scale the "peakiness" of the probability distribution
$$P_t(y_t = w) = \frac{\exp(S_w/\tau)}{\sum_{w'\in V}\exp(S_{w'}/\tau)}$$
	- for $\tau > 1$, $P_t$ becomes more uniform (higher temperature)
	- for $\tau < 1$, $P_t$ becomes spikier
- not a decoding algorithm but rather something to move probability distributions around!

#### Other ways to re-balance probability distributions
- skipped in class... basically just look at real text to calibrate distributions

#### Re-Ranking
- decode ~10 candidate sequences, decide among these which ones are good / bad
- define a score to the approximate quality of sentences, then **re-rank** by this score
	- simplest score metric is **perplexity** (but be careful as this has a tendency to get repetitive)

 ### Takeaways
 - still a challenging problem in NLG
 - major realization from last couple years: not problems of our learned LM vocab, but rather with the decoding algorithm
	 - human language production is subtle! not captured super well by simple probability maximization
	 - different decoding algs. can inject the right kinds of biases to encourage certain properties of language generation

# Training NLG Models
maybe greedy decoders are bad because of how they're trained...
- **maximum likelihood estimation** *discourages diverse language generation*

## Unlikelihood Training
- given set of undesired tokens $\mathcal{C}$, lower their likelihood *in context*
- separate loss $\mathcal{L}_{UL}^t$ for unlikely tokens
	- $\mathcal{L}_{ULE}^t = \mathcal{L}_{MLE}^t + \alpha\mathcal{L}_{UL}^t$
	- train alongside with teacher forcing -- will encourage diverse vocabulary through training

## Exposure Bias
- maybe a problem with **teacher forcing**
	- when we use the model at runtime, the model is "on its own" -- never trained in its own feedback loop

### Scheduled sampling
- potential solution: with some probability $p$, decode a token and feed that as input, rather than the gold one
- increase $p$ over the course of training, allowing the model to venture out further with its own sequences
- improves in practice but has *weird training objectives*

### Dataset aggregation
- add sequences from your current model's generation to the training set at various intervals

### Sequence re-writing
- learn to retrieve a sequence from an existing corpus of human-written prototypes
	- learn to *edit* this retrieved sequence by adding / removing / modifying tokens in the prototype -- leading to a more "human-like" generation

### Reinforcement learning
- cast text generation model as a **Markov decision process**
	- state (model's representation of preceding context), actions (words that can be generated), policy (the decoder), and rewards
- difficult b/c of huge branching factor and search space
- need to work from some appropriate baseline -- can't just start from scratch w/ reward functions
	- can't get away from teacher forcing -- reward fxn requires cogent inputs

## Takeaways
- **diversity** is a huge issue
- **teacher forcing** remains the default way to train

# Evaluating NLG Models
1. Content overlap metrics
2. Model-based metrics
3. Human evaluations

- how to define a reward function for RL? use evaluation metric
	- BLEU score (machine translation)
	- ROUGE score (summarization)
	- CIDEr (image captioning)
	- SPIDEr (image captioning)
- improving these scores doesn't often improve the human-assessed quality...
- but there are other behaviors we can tie to rewards
	- sentence simplicity
	- temporal / tense consistency
	- paraphrasing
	- etc.

## Content overlap metrics
- calculate similarity score based on overlap btwn generated and gold-standard text
	- most commonly **$n$-gram word overlaps**
	- semantic overlap metrics (ideas, concepts, etc. appearing in generated text)

### $n$-gram overlap metrics
BLEU, ROUGE, METEOR, CIDEr
- not ideal for machine translation metrics -- definitely falling apart as NMT gets better
- work well b/c what you can produce in a MT setting is fairly limited
	- work really poorly when the space of viable outputs is larger (bad for summarization, worse for dialogue, terrible for story generation)

### Semantic overlap metrics
PYRAMID, SPICE, SPIDER
- come up w/ some concepts, semantic graph representation of the ideas, etc.

## Model-based metrics
use *learned representations* of words to compute semantic similarity

### Word distance functions
- **vector similarity**: embedding based similarity for semantic distance
- **word mover's distance**: measures similarity using word embedding similarity matching
- **BERTSCORE**: use pre-trained contextual embeddings from BERT and match words between candidate and gold-text

... these don't really work 😞
- very low correlation to human scoring

## Human evaluators
- automatic metrics fall short of matching human decisions
- >75% of ALCU submissions in 2019 used at least some human evaluation

# Ethical considerations
- Microsoft's Tay: within 24 hours started making toxic, racist, sexist comments
- language models learn harmful patterns from large language corpora