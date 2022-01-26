#Stanford #Stanford-Winter-2022 #CS #CS224N #NLP #deep-learning #RNNs
___
- **Language Modeling**: the most important concept in the course!
	- the whole of natural language processing has turned into clever use of language models
- **Recurrent Neural Nets (RNNs)**: used in assign4

# Neural Dependency Parsing
- continuing from [[CS 224N Lecture 4 Notes - Dependency Parsing (2022-01-13)|last time]]
- categorical features?
	- sparse, imcomplete, and expensive to compute...
	- instead: learn *dense* and *compact* feature representation and use that!

## Model Architecture
- from Chen and Manning 2014 (==to cite==)
- turn current parsed state into a neural input layer
	- first word in buffer, first part of speech, stack, ...
- pass through a hidden layer, then an output softmax layer
	- probabilities correspond to {Shift, Left-Arc, Right-Arc}
	- train using cross entropy loss backpropagated to the embeddings
- wins: distributed representations + non-linear classifier

## Evaluating Dependency Parsers
- for any sentence, put a parse on it that describes a set of dependencies
	- dependencies are a set of "claims" about which relations hold between which words
	- accuracy: looking just at arcs, $\text{acc} = \frac{\text{\# correct deps}}{\text{\# of deps}}$
		- called **Unlabeled Accuracy Score** or **UAS**
		- contrast with **Labeled Accuracy Score** or **LAS**, which also requires the relation predicted be correct

## Developments in transition-based neural dependency parsing
- bigger & deeper networks
- beam search
- global conditional random field (CRF)-style inference over decision sequence
- a lot of papers out of Google on this

## Graph-based dependency parsers
- compute a score for every possible dependency
	- need "contextual" representations of each word token
	- slows the algorithm down a lot: there are $n^2$ possible dependencies for a sentence of length $n$
- use MST algorithm to find the best parse after repeating for every word
	- not the same as just choosing each highest scoring individual edge

# Neural Networks cont.
## Regularization
- full loss functions include **regularization** over params in $\theta$
	- e.g. L1 and L2 regularlization
	- $\dots +\lambda\sum_k\theta_k^2$
- **overfitting**: extent that test error is higher than training error as model "power" increases
	- traditionally: regularizing features works to prevent this with lots of features / deep layers
	- nowadays: regularization *produces models that generalize well* when the model is "big"
		- *even though model is hugely overfit on the training data!*
		- you can keep on training on the same data, even after "overfitting", and model will continue to learn more general representations of the problem type
			- test set error will increase as in traditional overfitting theory, but further training will see test error decrease once again
				- **double descent** -- a lot of theoretical work happening in this area

## Dropout
- at training time, with weights in a particular layer, zero out half of them and use the rest of the weights forward to predict the training set
	- at the input layer, dropout is more like 10-15%
	- in internal (hidden) layers may drop out 50% each time, randomly
- model has to become good at predicting using different subsets of internal features / representations, without relying extensively on features co-occurring
	- result is a kind of middle ground between naive bayes (all features are independent) and logistic regression (all weights are set in context of others)
	- a form of model bagging, like an ensemble model

## Non-linearities
### Logistic (sigmoid)
- not a great nonlinearity internally
	- b/c all outputs are positive

### tanh
- hyperbolic tangent function
- just rescaled and shifted logistic, 2x as steep
- $\tanh(z) = 2\text{logistic}(2z)-1$
- $\tanh(z) = \frac{e^z - e^{-z}}{e^z + e^{-z}}$

### hard tanh
### ReLU
- rectified linear unit
- the first thing you should try when building a deep network: trains quickly, and performs well due to good gradient backflow
	- gradient: slope of 1 on the right side, 0 on the left
	- compare to tanh, where gradients at the extremes are really flat
- compare also to "Leaky ReLU" or "Parametric ReLU" (learn negative slope as a parameter in the model)

## Parameter Initialization
- absolutely essential to initialize weights to small random values
	- some limited circumstances where you don't initialize -- e.g. if the training and the model will cause weights to diverge correctly
	- but w/o initializing -- all weights will be symmetric -- you'll only be learning "1" parameter
- various traditional recipes for doing this
	- idea: make values small enough s.t. when you do `matmul`, values don't get too large / small
	- **Xavier initialization**: considers how many inputs / outputs there are to set initialization
		- $Var(W_i) = \frac{2}{n_{in}+n_{out}}$

## Optimizers
- normally you can do *just fine* using SGD -- if you're careful in setting the learning rate & decreasing it as training proceeds
- but lots of work on the correct approach to optimization! family of sophisticated "adaptive" optimizers that started with AdaGrad
	- AdaGrad
	- RMSprop
	- Adam (fairly good safe place to begin)
- generally these work by scaling the updates of different parameters differently, depending on their history of updates

# Language Modeling & RNNs
- probably the next three classes... *the heart of the class!*
- **Language Modeling**: a classification task of a different flavor -- predicting what word will come in a certain context
	- "the students opened their [blank]"
	- given sequence of words $x^{(1)},x^{(2)},\dots,x^{(t)}$ compute prob. dist. for next word $x^{(t+1)}$:
$$P(x^{(t+1)}\mid x^{(1)},x^{(2)},\dots,x^{(t)})$$
		- $x^{(t+1)}$ can be any word in the vocab $V$
	- can also think of language model as giving the probability of an entire piece of text
		- by chaining probabilities of each subsequent word, in the form above

## n-gram language models
- how to build them?
- 20-30 years of language models before people got into the neural ones
- before DL: use $n$-gram language model
	- **$n$-gram** = chunk of $n$ consecutive words
	- collect statistics of how often $n$-grams appear in lots of text, turn those into probabilities

### Some assumptions
- **Markov assumption**: $x^{(t+1)}$ depends only on the preceding $n-1$ words
- to get probability, take fraction $P(x^{(t+1)}\mid x^{(1)},x^{(2)},\dots,x^{(t)}) = \frac{P(x^{(1)},x^{(2)},\dots,x^{(t)}, x^{(t+1)})}{P(x^{(1)},x^{(2)},\dots,x^{(t)})}$

### Some problems
- **Sparsity problems**: if we've *never* seen some particular $n$-gram in the dataset, the probability has to be zero!
	- way this was previously solved: **smoothing**: add small $\delta$ to every count for each $w\in V$
	- what if context was *never* seen at all? then can't calculate the probability for any potential $w$ (equivalently $x^{(t+1)}$)
		- solution to this called **backoff**: just shorten the context until you get something with nonzero num. occurrences
- number of parameters going up *exponentially* in terms of $n$ in $n$-gram -- and this makes sparsity problems *worse*
	- also really inefficient to store all of these probabilities

### Generating text using $n$-gram language models
statistics on counting ~2 million words of text, with a trigram model, surprisingly learns a lot about the structure of language!
- grammatically / syntactically correct, maybe!
- but *incoherent* -- we need more than trigrams! but this increases the sparsity and model size problems...

## Neural Language Models
- we just learned to build a window-based neural classifier... can we just use these to build a neural language model?
	- as applied to Named Entity Recognition in [[CS 224N Lecture 3 Notes - Backprop and Neural Networks (2022-01-11)#Common NLP Task Named Entity Recognition NER|lecture 3]]
	- words / one-hot vectors -> concatenated word *embeddings* -> hidden layer -> softmax
		- softmax output layer will be a probability distribution across the vocabulary $V$ for what the next word $x^{(t+1)}$ is

### first attempt: Y. Bengio 2000/2003: "A Neural Probabilistic Language Model" ( #TODO ==to cite==)
- improvements
	- no sparsity problems!
	- don't need all $n$-grams stored
- problems
	- fixed-window size is *too small*
	- enlarging the window enlarges $W$ (maybe to prohibitively high levels)
	- *no symmetry* in how the input is processed (e.g. words $x^{(1)}$ and $x^{(2)}$ are processed completely independently with multiplication in weights $W$, so you can learn totally different params for the word "student" depending on which position it appears in in the window...)
		- ... we need a neural architecture to process *any input length*
			- which can provide a little *symmetry* in how words in context are processed

### Next attempt: Recurrent Neural Networks (RNNs)
- family of neural architectures
- tracks a hidden state $h^{(1)}, h^{(2)}, \dots$ that is multiplied to transition to the next state
- words / one-hot vectors -> word embeddings $\mathbf{e}^{(t)}$ -> hidden states $h^{(t)} = \sigma(W_hh^{(t-1)}+W_ee^{(t)}+b_1)$ -> output distribution $\hat{y}^{(t)} = \text{softmax}(Uh^{(t)}+b_2)\in\mathbb{R}^{|V|}$
	- nonlinearity $\sigma$ is most likely `tanh`
		- better than sigmoid b/c sigmoid would push everything into the positive realm, whereas `tanh` is centered around 0 which can just allow better learnability
	- $h^{(0)}$ is the initial hidden state
	- for recurrent neural network: doing the same transformation $W_h$ at each time step to get the hidden state
#### Advantages
- this model can use *an arbitrary amount of conditioning context*
	- and model size doesn't increase for longer input context
	- and weights are applied at every timestep, so there is symmetry in how inputs are processed!

#### Disadvantages
- recurrent computation is *slow*
	- the traditional advocacy for DL networks that they can compute hugely in parallel is just false here -- output is worked out sequentially
- in practice, it's difficult to access information from many steps back (after updating hidden states some number of times)
	- length of memory you can get from an RNN is about 7 items...

#### Training an RNN Language Model
- start with big corpus of text
- feed into RNN-LM, compute output distribution $\hat{y}^{(t)}$ for every step $t$ (given all prev. words so far)
- loss function (on step $t$) will be **cross-entropy** between predicted probability and next true word (which is one-hot)
	- so, negative log prob. assigned to the true word by the model
	- **"Teacher forcing"** -- reorient model towards the correct answer at each step $t$
$$J(\theta) = \frac{1}{T}\sum_{t=1}^TJ^{(t)}(\theta)$$
##### Backprop for RNNs
- how to compute gradient for $J^{(t)}(\theta)$ w.r.t hidden transformation matrix $W_h$?
	- pretend each matrix is independent, even though they're not (like we have different copies of them), and then just sum them all
$$\frac{\partial J^{(t)}}{\partial W_h} = \sum_{i=1}^t\frac{\partial J^{(t)}}{\partial W_h}|_{(i)}$$
	- these partial derivatives are different at each position $i$
	- this is the right answer b/c of the multivariable chain rule! the right thing to do w/ single variable functions composed into one is to add their components
	- algorithm is called the **Backpropagation through Time** algorithm (Werbos, 1998, *Neural Networks*)
		- some people do **truncated backprop through time** by just halting the backprop after some number of steps (like 7, the supposed max for how long RNN sequences can remember information...)


#### Generating text with an RNN Language Model
For [[CS 224N Lecture 6 Notes - Simple and LSTM Recurrent Neural Networks (2022-01-20)|next time...]]