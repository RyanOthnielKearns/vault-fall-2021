#Stanford #Stanford-Winter-2022 #CS #CS224N #lecture-notes #NLP #neural-networks #deep-learning 
[[CS 224N Lecture 13 Slides - Integrating Knowledge in Language Models.pdf|lecture slides]]
___
# Lecture Plan
1. Recap of language models and what they know
2. Techniques to add knowledge to LMs
	1. Pretrained entity embeddings

# Recap: LMs
- **Language models** predict the next word given a sequence of text and compute the probability of a sequence
	- masked prediction tasks make it easy to leverage large amounts of text data, making it popular to generated **pretrained representations** of text

## What does a language model already know?
- why would we get things *factually incorrect*?
	- unseen facts: just not in the corpora at all
	- rare facts: LM hasn't seen enough examples during training to memorize
	- model sensitivity: fact could be phrased in a different way during training than seen in testing
- takeaway: LMs aren't *reliable* sources of facts

## Why do we want knowledge-aware LMs?
- pretrained representations can benefit downstream tasks that leverage knowledge
	- e.g. QA and relation extraction
- ultimately, can LMs *replace traditional knowledge bases*?
	- can query knowledge bases of this form using natural language instead of SQL
### Querying LMs as Knowledge Bases
- pretrain LM over unstructured text, query with natural language (instead of formal queries)

### Advantages of LMs over Traditional KBs
- no human annotations required -- can train on large unstructured text corpora
- LMs support more flexible querying via natural language

### Challenges
- hard to interpret why LMs produce certain answers (whereas KB has provenance)
- hard to **trust** (LM can produce realistic but incorrect answers) ( #trust )
- hard to modify (whereas KB is directly editable)

# Traditional Knowledge Bases
- knowledge base entries written as triples: (head, relation, tail)
- query using SQL

# Adding knowledge to LMs
## pretrained entity embeddings
- **entity linking**: link mentions in text to entities in KBs
	- mentions -> candidates
	- looking up words in a "word embedding dictionary" -- though phrasing may not be an exact string match, so a little harder
- **entity embeddings** are word embeddings for entities in a KB
	- can train via knowledge graph embedding methods (TransE, etc.)
		- or word-entity co-occurrence methods
	- how to incorporate when from *different embedding spaces* than the LM?
		- learn fusion layer $h$ to combine word + entity info
			- $h_j = F(W_tw_j + W_ee_k + b)$
				- $w_j$ is the embedding of word $j$ in a sequence of words
				- $e_k$ is corresponding entity embedding
				- alignment between words and entities in sentence s.t. projections map into the same vector space
### ERNIE
**Enhanced Language Representation with Informative Entities**
- *text encoder*: multi-layer bidirectional Transformer encoder over the sentence tokens
- *knowledge encoder*:
	- two self-attention layers (one for entities and one for token embeddings)
	- *fusion layer* to combine output of the two self-attention layers

#### How to train?
- joint pretraining w/ three tasks
	- masked language model + next sentence prediction (the BERT tasks)
	- **knowledge pretraining task (dEA)**
		- randomly mask some token-entity alignments and predict which entity should be linked to the given token
		- from evaluation: knowledge pretraining task is necessary to make the most use of pretrained entity embeddings

#### Strengths
- can combine entity + text info via fusion layers and knowledge pretraining
- improves performance on knowledge-intensive downstream tasks

#### Limitations
- needs to link each entity mention in input text to KB *in advance*
	- hard to get a good entity linker for just about any task we care about

### QAGNN / GreaseLM
- newer work out of Stanford NLP
- **key idea**: when adding entity embeddings to LM, *dynamically update* them together with neighbors / related entities in KB as well as in text
	- benefits:
		- robust to non-perfect entity-linking: include all entity candidates and let model figure out what to fuse
		- better contextualize knowledge, helpful for joint reasoning about text / knowledge

#### Model architecture
text encoded by language model, KG encoded by Graph Neural Network, then fused together for multiple rounds
- GNNs from #CS224W, especially [[Lecture 6 - Graph Neural Networks 1 - GNN Model.pdf]]
	- updates node representations through `AGGREGATE` and `COMBINE` steps to message vectors from their neighboring nodes
- fusion layer mixes together outputs from LM and GNN components

#### Evaluation
- outperform BERT-based methods / models on *knowledge-intensive QA tasks* (CommonsenseQA, OpenBooksQA, MedQA)
- qualitative results
	- grounding LM into KG allows models to learn **structured reasoning** (e.g. correct handling of negation via attention weights propagating through fusion layers)
		- see Kassner et al. 2020 on how vanilla LMs don't handle negation well
		- KG connection provides both *background knowledge* and a *scaffold for reasoning*

## use external memory
just give the model access to some external memory
### advantages
- can directly update facts in the external memory w/o retraining the model!
- also more interpretable (visible which fact in external memory the LM used to make prediction)

### KGLM (Logal et al. 2019)
builds a local KG as you iterate over the sequence
- **local KG** is a subset of the full knowledge graph with only entities relevant to the sequence so far
	- can provide a strong signal for predicting which word comes next
	- how can the LM decide whether to use the local KG or the traditional LM for predicting the next word?
		- instead of predicting next word directly, LM hidden states predict the *type* of the next word (of 3 classes)
			1. related entity (in local KG)
				- local KG represented using KG triples (parent entity, relation, tail entity)
				- which are the top scoring parent entities and relations (using embeddings + LM hidden state)? these should infer the solution to the word prediction (e.g. the tail entity in the relevant KG triple)
			2. new entity (not in local KG)
				- find top scoring entity in the full KG using LM hidden state and entity embeddings
				- predict next most likely token given the highest scoring entity + its aliases
			1. not an entity
				- just use standard LM prediction

#### Evaluation
- outperforms GPT-2 and AWS-LSTM on a fact completion task
	- predicts more specific tokens compare to GPT-2
- also supports modifying / updating facts!
	- modifying the KG triples has a direct change in the LM predictions

## modify training data
- requires no model architecture changes + no additional memory
- still an open question though as to whether this is always as effective as model changes

### Pretrained Encyclopedia: Weakly Supervised Knowledge-Pretrained Language Model (WKLM)
- **key idea**: train the model to distinguish between true and false knowledge
	- replace mentions in the text with mentions referring to different entities of the same type to create negative knowledge examples
		- e.g. "J.K. Rowling wrote Harry Potter" -> "J.R.R. Tolkein wrote Harry Potter"
		- model learns to predict which entities are true and which are false mentions in the sentence
		- use **entity replacement loss** (binary classification)
			- total loss is this plus standard masked language model loss
#### Evaluation
- improves over BERT and GPT-2 in fact completion tasks
- improves over ERNIE in downstream tasks
- ablation study shows effect of MLM and EntRep components
	- EntRep loss essential to outperforming BERT
	- MLM loss is essential for downstream task performance

### Learn inductive biases through masking
- can we do clever masking to help LM learn factual knowledge? (beyond training data corruption)
	- phrase + *entity masking* instead of just word or phrase masking -> **salient span masking**
	- outperforms span masking on QA / doc. retrieval tasks

# Evaluating Knowledge in LMs
## Probes
- **knowledge probing**: how much relational (commonsense / factual) knowledge is already in off-the-shelf LMs? (having been pretrained on different pretraining corpora)
	- evaluate knowledge present w/o more training
- manually construct set of "cloze" statements ("fill-in-the-blank") to test the model with
	- use KG triples and QA pairs from QA datasets
- compare unsupervised LMs to supervised relation extraction / QA systems
	- use **mean precision at 1 (P@1)** eval metric
- LAnguage Model Analysis (**LAMA**) Probe
- result: BERT struggles with N-to-M relation types
### Limitations of LAMA Probe
- hard to understand *why* models perform well
	- could just be memorizing word co-occurrence patterns rather than understanding or "recalling" knowledge
	- could just be identifying similarities between surface forms of the subject / object in cloze sentence
- sensitive to the phrasing of the statement
	- rephrasing the template might suddenly make LMs perform better

#### LAMA-UhHelpful Names (LAMA-UHN)
- remove examples that can be answered *without relational knowledge*
	- BERT may rely on surface forms of entities to make predictions, or spurious correlations like names as a prior for native language, nationality, etc.
- BERT's score drops to ~8% (pretty bad!)
	- but knowledge-enhanced E-BERT only suffers <1% drop in score
#### Develop better prompts to query knowledge in LMs
- LMs may fail on completion tasks due to query phrasing, even though they "know" the fact
	- due to the effect of pretraining text
- solution: generate more LAMA prompts by mining templates from Wikipedia / generating paraphrased prompts 
	- creates **ensemble prompts**, where LMs performance is averaged over different prompt phrasings for the same query
		- BERT improves ~7% when using the best-phrased prompts
	- small changes in query phrasing lead to large gains in performance -> research opportunity for robust LMs!

## Downstream Tasks
Knowledge-intensive downstream tasks
- evaluate the usefulness of knowledge-enhanced representations in downstream applications
- usually involves *finetuning* on downstream tasks like GLUE tasks
- common tasks:
	- relation extraction
	- entity typing
	- question answering
- knowledge-enhanced systems (ERNIE, KnowBERT) improve on SoTA for knowledge / entity extraction, and also entity typing