#Stanford #Stanford-Winter-2022 #CS #CS224N #deep-learning #neural-networks #lecture-notes #NLP 
___
# Lecture Plan
1. Review Transformer model
2. Brief note about subword modeling
3. Motivating model pretraining via word embeddings
4. Model pretraining
	1. Decoders
	2. Encoder
	3. Encoder-decoders
5. Very large models and in-context learning

# Review: Transformer Model
- word embeddings + position representations $\to$ multi-head attention (and residual self-connection)
	- into layer normalization, feed-forward network, and another residual layer + layer normalization step
		- do this step once for each layer
- decoder: word embeddings plus position representations $\to$ *masked* multi-head self-attention (no peeking into the future!)
	- $\to$ residual + layer norm.
	- final encoder block also passes into multi-head *cross*-attention between encoder & decoder
	- residual + layer norm, last feed-forward network, then final residual + layer norm

# Word Structure / Subword Models
- assume a fixed vocab of everything from training set
	- *novel* words seen at test time get the `<UNK>` token
	- this is a problem for english, but *much* worse for other languages (e.g. Swahili, which can conjugate verbs ~300 times)

## The byte-pair encoding algorithm
- **subword modeling** = reasoning about structure *below the word level* (parts of words, characters, even bytes)
	- at training / test time, each word split into sequence of known subwords
- **byte-pair encoding**: strategy for defining a subword vocabulary
	- start w/ vocab containing only characters and an "end-of-word" symbol
	- using corpus, find the most common pair of adjacent characters (e.g. "t,h") --> add subword "th" to the vocab
	- replace instances with pairs until you reach the desired vocab size
- today, similar method (`WordPiece`) used to form subword vocabs for large LMs

# Motivating Model Pretraining from Word Embeddings
## Word meaning & context
- core idea of **distributional semantics**: "You shall know a word by the company it keeps" (J.R. Firth, 1957)
	- motivated `word2vec`!
	- also: "The complete meaning of a word is always contextual" (Firth 1935)
		- "I record the record" -- we miss something by collapsing all of the meanings into one static word embedding

## Pretrained word embeddings
- issues to think about
	- training data we have for our downstream task must be sufficient to teach *all contextual aspects* of language
		- plus labeled data is expensive...
	- most parameters in network are randomly initialized!

## Pretraining whole models
- today: all parameters in NLP are initialized via **pretraining**
	- pretraining methods hide parts of the input from the model, and train the model to reconstruct those parts
		- learning language models is one common pretraining objective
- exceptionally effective for:
	- representations of language
	- param. initializations for strong NLP models
	- prob. distributions over language (LMs) that we can sample from

### What can we learn from reconstructing the input?
- can embody sentiment analysis tasks, knowledge graphs, spatial reasoning, pronoun-subject alignment, etc.
	- "All the value I got out of it was the sum total of the popcorn and drink. The movie was []"
	- "Iroh went to the kitchen. Zuko went to Iroh, and then left the []"

Model $p_\theta(w_t\mid w_{1:t-1})$, the probability of words given their past contexts
- lots of data (at least in English) for this task
- **pretraining through language modeling**: train a neural network to do language modeling, then save the parameters!

# Pretraining / Finetuning
- pretraining can improve NLP applications by serving as parameter initialization
1. Pretrain on language modeling
	- lots of text freely available to learn general things
2. Finetune on your task
	- not many labels, so must adapt to the task

# Model Pretraining in three ways
## Decoders
- language models
- nice to generate from, but can't condition on future words
- examples: GPT-2, GPT-3, LaMDA

### Pretraining Decoders
- ignore that the pretrained decoders are trained to model $p_\theta(w_t\mid w_{1:t-1})$
- **finetune** by training a classifier on the last word's hidden state
	- $y\sim Ah_T + b$
		- $A$ and $b$ are randomly initialized
	- gradients propagate back through whole network
- this is most helpful for tasks where the output is *sequential* and has vocab like that seen at pretraining time
	- e.g. dialogue tasks, summarizations

#### Generative Pretrained Transformer (GPT)
- how to format inputs to our decoder for finetuning tasks?
- special start token called `[EXTRACT]`
	- linear classifier is applied to the representation of the `[EXTRACT]` token -- consumes the output after this token
	- Start -> Text -> `[EXTRACT]` -> Transformer -> Linear layer
- two loss functions
	1. related to the text itself
	2. another related to language modeling (continuing to do pretrained objective task while finetuning)
- outperformed a lot of very handcrafted NLP systems at their own tasks they were crafted for

##### The effect of pretraining
- as more layers are transferred, performance improves on benchmark tasks (RACE, MultiNLI)

##### Increasingly convincing generations
- GPT-2 -> GPT-3

## Encoders
- get's bidirectional context, so can condition on future
- examples: BERT, RoBERTa

### What pretraining objective to use?
- encoders get bidirectional context so we can't do language modeling
- instead: replace some fraction of words with `[MASK]` token and predict those words
	- called **masked language modeling**
		- better learning task for fully connected networks like encoders

### BERT: Bidirectional Encoder Representations for Transformers
- Devlin et al. 2018
- predict a random 15% of (sub)word tokens
	- replace input word with `[MASK]` 80% of the time
	- replace with random token 10% of the time
	- leave input word unchanged 10% of the time (but still try to predict it!)

#### Unified Architecture
- minimal differences between pre-training architecture and fine-tuned version for each downstream task
- just use same architecture and add a different prediction head at the top

#### Pretraining
- pretraining input was two separate contiguous chunks of text
	- predict whether one chunk follows the other or was randomly sampled
- also a larger masked language modeling objective
- pretraining is expensive and impractical on a single GPU
	- pretrained with 64 TPU (special tensor processing hardware from Google) chips for 4 days
	- finetuning *is* practical (and common) on a single GPU

#### Extensions
RoBERTa, SpanBERT, etc.
- RoBERTa: mainly just train BERT for longer and remove the next-sentence prediction task
- SpanBERT: masking contiguous tokens makes for a more useful pretraining task

### Limitations of pretrained encoders
- if your task involves generating sequences, use a pretrained decoder
- BERT / other pretrained encoders don't naturally have nice autoregressive word generation performance

## Encoder-Decoders
- good parts of both!
- examples: Transformer, T5, Meena

### How to pretrain?
- could do something like language modeling
- slightly better: instead of masking out individual random words, replace small groups of contiguous words with single `[SENTINEL]` tokens
	- model doesn't know how many tokens it should generate for each sentinel
	- called **span corruption**
	- since this technically counts as language modeling, don't need to change underlying architecture

### T5
- can be pretrained to do trivia-style question-answering by retrieving the answer from its own parameter weights (not consulting a database or anything)

# Very Large Models and In-Context Learning
- interacting with pretrained models so far:
	1. Sample from distributions they define (e.g. by providing a prompt)
		- use them directly as a language model
	2. Fine-tune them on a task we care about and then take their predictions
- **in-context learning**: emergent behavior where very large LMs can learn w/o gradient steps simply from examples you provide within their contexts
	- in-context examples specify the task that's being performed
	- conditional distribution sort of "mocks" actually performing the task
	- still not very well understood theoretically