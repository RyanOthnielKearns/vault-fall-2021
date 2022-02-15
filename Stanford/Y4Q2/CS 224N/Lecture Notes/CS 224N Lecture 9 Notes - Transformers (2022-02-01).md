#Stanford #Stanford-Winter-2022 #CS #CS224N #deep-learning #neural-networks #lecture-notes #transformers
___
See [[CS 224N Lecture 9 Slides - Transformers (2022-02-01).pdf]]
# Announcements
- Assign4 due Feb. 8
- Assign5 due Feb. 17
- Final project proposal still due Feb. 8!

# Lecture Plan
1. Impact of Transformer architecture on NLP (and broadly)
2. From RNNs to Attention-Based NLP models
3. Understanding the Transformer model (how does it work?)
4. Drawbacks & variants of transformers

# Impact of Transformers
Is Attention All We Need? (==see "Attention is All You Need" paper & cite #TODO==)
- not quite!
- but transformers underpin virtually all SoTA in NLP
	- machine translation, document generation
- most now use **pre-training**
- also in *protein folding*! see AlphaFold2
	- also image classification and compiler optimization

## Scaling Laws
- OpenAI showed that transformer-based models improve smoothly as we increase training data, size, and compute
	- power-law relationship that shows no signs of slowing over multiple orders of magnitude so far!
		- will we eventually match or exceed human-level performance?

# From Recurrence (RNNs) to Attention-Based Models
- circa 2016, de facto strategy was to encode sentences using BiLSTM
	- define output as a sequence and let an LSTM generate it
	- use attention to allow "flexible access to memory"

## What's wrong with RNNs?
- linear interaction distance between tokens
	- RNNs are "unrolled" left-to-right
	- this encodes some useful properties like **linear locality**
	- *but*: takes $O($sequence length$)$ steps for distant word pairs to interact
		- hard for long-distance word pairs to interact!
- lack of *parallelizability*
	- forward & backward passes also have $O($sequence length$)$ unparallelizable operations
		- operations have to happen in sequence! *doesn't make good use of modern hardware* (GPUs / TPUs)
		- we could just increase batch sizes, but then we run into a memory problem with large batches of (large) sequences held in memory

##  Replacing Recurrence with (Self)-Attention
**attention**: treats each word representation as a query we can use to access relevant info about reps. of other words (a "set of values")
- **self-attention** is "encoder-encoder" or "decoder-decoder" attention: each word attends to each other word in a given input / output
	- we can stack many layers of this self-attention process
- advantages to RNNs
	- number of parallelizable operations does not increase w/ sentence length (instead with num. layers)
	- each "word" interacts w/ each other, so maximum interaction distance is $O(1)$
		- *but* quadratic compute per layer, b/c number of operations per layer is $O(n^2)$ in terms of the sequence length

# Understanding the Transformer Model
- pass pre-trained embeddings into attention

## Intuition
- think about as a "fuzzy, approximate hash table"
	- to look up a value, compute a query & compare w/ keys in the table
	- each query (in attention) maps to all keys to varying degrees
	- for each word $x_i$ calculate query, key, and value
		- $q_i = W^Q x_i$
		- $k_i = W^K x_i$
		- $v_i = W^V x_i$
		- so: $e_{ij} = q_i\cdot k_j$
		- $\alpha_{ij} = \text{softmax}(e_{ij})$ (normalized attention scores)
		- $\text{Output}_i = \sum_j\alpha_{ij}v_j$ (a weighted sum of values)
	- *and* all of the above computations can be vectorized using stacked inputs!
		- $\text{Output} = \text{softmax}(QK^T)V$

## Improving Attention
- no element-wise non-linearities, meaning self-attention is just re-averaging the value vectors!
	- solution: apply a feedforward layer to each output of attention
		- $m_i = \text{MLP}(\text{output}_i)$ where the multi-layer perceptron has weight+bias, ReLU, and then another weight+bias layer
- more layers!!!! but this presents prolems...

### Training for Deep Networks
#### 1. Residual Connections
- come from computer vision
- deep networks are surprisingly bad at learning the identity function!
	- this entails that these networks have super unstable learning
	- also means: if we pass "raw" embeddings straight through a layer to the next, effectively "skipping" the connection, model can learn better
- prevents the network from "forgetting" / "distorting" important information during the layer-level processing
- theory that these connections smooth the loss landscape and make training easier (==see Li et al., 2018 on a ResNet==)

#### 2. Layer Normalization
- difficult to train parameters of a given layer if the input from previous layer keeps shifting
	- reduce the variation from previous layers by normalizing each layer to zero mean + 1 stddev

#### 3. Scaled Dot-Product Attention
- following layer normalization from above -- the dot product of normalized vectors still takes on high variance, scaling with dimensionality $d_k$
	- mean of sum = sum of means (= 0 here)
	- variance of sum = sum of variances ($=d_k$ here)
- set the variance to 1 by dividing by $\sqrt{d_k}$

##  Issue: Order Invariance
- order *does* encode meaning in English! but it doesn't impact the naive transformer network at all
- *solution*: inject info through **positional encodings**
	- have embeddings that represent the positions in a sentence
	- position vectors $p_i\in\mathbb{R}^d$
	- just add the $p_i$ to our inputs to get the info into the self-attention block!
		- not totally clear why this works
		- to the query, key, and value vectors
	- use **sinusoidal position representations** -- concatenate sinusoidal functions of varying periods
		- maybe this works to extrapolate to longer sequences as the period restarts?
		- problem is these are not learnable
	- alternative: learn position representation vectors *from scratch*
		- learn matrix $p\in\mathbb{R}^{d\times T}$ and let each $p_i$ be a column
		- definitely can't extrapolate to indices outside $T$, but each position gets to be learned by the data
		- *most systems end up using this*

## Multi-Headed Attention
- intuition: what if there are multiple parts of the sentence to look at for each position in the output, instead of just one!
	- single-headed attention forces us to focus on singular positions at the expense of others
- define multiple attention "heads" through multiple $Q, K, V$ matrices
	- each is a "clear lens" for looking at the relationships between words, using different feature representation subspaces
	- $Q_l, K_l, V_l\in\mathbb{R}^{d\times \frac{d}{h}}$
		- $h$ is the number of attention heads and $l$ ranges from 1 to $h$
		- it's beneficial to learn multiple different representations, so in practice the signal carried backward will force representations (if initialized randomly) to diverge
			- ==by how much do they diverge? can that be quantified / can we calculate the number of heads that will be beneficial vs. when performance will start stalling? like using cosine similarity or something else?==
	- each head learns attention independently
		- outputs of all heads are concatenated!

### Decoder
**problem**: can the decoder "cheat" by looking ahead and "seeing the answer" to optimize a language model objective
- we need to use **masked multi-headed attention** to ensure we can't look at the future
	- just mask out attention to future words by setting attention scores there to $-\infty$
		- this works because we take the softmax, so score will be brought to 0 when summing
- also want to add a feed forward layer (with residual connections + layer norm)
	- add final linear layer to project embedings into a longer vector of length vocab size (*logits*)
	- add a final softmax, which turns this into a probabilty distribution of possible next words!

## Encoder-Decoder Attention
- looks very similar to what we saw [[CS 224N Lecture 8 Notes - Attention, NMT, Final Projects (2022-01-27)|last week]] -- attention across the encoder / decoder boundary
	- keys and values are drawn from the encoder (like a memory)
	- queries are drawn from the decoder

*decoder can't be parallelized which makes the inference time of transformers prohibitive at some big tech applications*

# What would we like to fix about the Transformer?
- quadratic compute in self-attention
	- only grew linearly with recurrent models
	- e.g. see Linformer (Wang et al., 2020) -- doing as well as the transformer without the quadratic increase in compute for sentence length
	- maybe local window attention, random interactions, etc. (see BigBird (Zaheer et al., 2021))
- better position representations

## Transformer modifications
From paper "Do Transformer Modifications Transfer Across Implementations and Applications?"
- seems like most modifications (except non-linearities) don't improve performance -- implying that transformer architecture is some kind of *local optimum* in terms of architectural performance on language tasks