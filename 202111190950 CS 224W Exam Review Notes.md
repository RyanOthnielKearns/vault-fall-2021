#CS #CS224W #Stanford #Stanford-Fall-2021 #exam 
___
# Agenda
1. Logistics / format / topics
2. Three specific topics to review

# Exam Prep
- see 2019 exam as an example of what the submission format looks like
- designed to take 110 minutes, then 10 minutes for uploading images
	- possible to not finish every question -- designed to be hard
	- spend 5-15 minutes on each question
		- points are distributed "quite evenly"
		- each question has a "what to submit" section for clarity
- types of questions
	- true / false with explanation
	- give examples of graphs
	- comparison of approaches
		- e.g. knowledge graph embeddings -- compare diff. types
		- pros and cons, expressivity, etc.
	- mathematical calculations / derivations
		- show your work in case you don't get the right answer
- none of the questions on their own are too hard -- not much deeper than what you've seen in lecture
	- good amount of material to get through (what makes it difficult)
		- budget your time carefully

## General Advice
- read through all the lecture slides carefully
- topics important for the exam
	- node centrality measures, PageRank
		- from earlier lectures
		- make sure you're comfortable w/ PageRank (entire lecture on it)
	- GNN model + design space
		- message, aggregation, update
			- be super comfortable with these three steps
			- several questions to do with this
	- knowledge graph embeddings, Query2Box, recommender systems (LightGCN)
		- review knowledge graph embeddings as they came up in the homework
- **exam covers lectures 1-15**
	- important: 2, 4, 6, 7, 8, 10, 11, 13
	- relatively unimportant: 1, 3, 5, 9, 12, 14
		- there might be miscellaneous questions
	- some exam questions might be quite similar to the homework

# Homework Review
## Homework 1, Q4.6
Message passing, aggregation, and update
- understand these steps + how to implement them for a new task
- in this question, use GNNs to execute BFS
- *what does the embedding represent?*
	- single-dimensional embeddings that are either 0 or 1
		- 1 means "visited" by BFS, 0 means not visited
		- be really clear on what the embeddings mean, as a first step
- *message*: "what is useful for the self-node to know from the neighbors?"
- *aggregate*: how do you aggregate over messages? max, mean, sum, etc.
- after you have your own embedding from previous layer + aggregated messages from neighbors --> how do you *update* your own embedding?
- advice: think about the perspective of the nodes in the graph
	- imagine you are a node in the graph: what info do you want to tell your neighbors (during BFS)?
		- "I have / haven't been visited by the BFS algorithm"
		- just pass your embedding to your neighors:
$$\text{message}_{v\rightarrow u}(h_v^{(k-1)}, e_{v,u})=h_v^{(k-1)}$$
- how should you aggregate over all messages?
	- from perspective of the node: want to know whether *any* of my neighbors have been visited
	- this means $\max$ aggregation
$$\text{aggregate}(\{\text{message}_{v\rightarrow u}, \forall v\in\mathcal{N}(u)\})=\max_{v\in\mathcal{N}(u)}\text{message}_{v\rightarrow u}$$
- update: don't forget to *self-link* to the previous embedding for node $u$
	- in BFS: I am visited if (1) I have been visited already, OR (2) any of my neighbors have been visited
	- an OR over two variables, which mathematically means max
$$\text{update}\big(h_u^{(k-1)},\text{aggregate}(\dots)\big) = \max\big(h_u^{(k-1)},\text{aggregate}(\dots)\big)$$
- remember that aggregation is over *neighbors* -- even though there may be a self-loop in the graph, don't always assume that $\text{aggregate}$ is going to include info from node $u$'s previous layer embedding

## Homework 2, Q3.1
on **knowledge graph embeddings** (comes up multiple times on the exam, so know really well)
- KGs = heterogeneous graphs w/ objects & relations
	- embed objects & relations into a low-dimensional embedding space
	- define embeddings for entities & relations, and come up with way to map from one entity to another (w/ high level goal that applying relation to "head" entity lands at "tail" entity's embedding)
		- can a given KG embedding handle certain patterns of relations? (symmetric, transitive, etc.)
- *common patterns* in knowledge graph embeddings
	- **symmetry**
	- **inverse**
	- **composition**
- KG method: **TransE**
	- given triplet $(h, l, t)$,  TransE learns embeddings to satisfy $\mathbf{h}+\mathbf{l}\approx\mathbf{t}$
	- symmetry: *cannot model*
		- would have $\mathbf{h}+\mathbf{l}\approx\mathbf{t}$ and $\mathbf{t}+\mathbf{l}\approx\mathbf{h}$
		- which only works if $\mathbf{l} = 0$ and $\mathbf{h} = \mathbf{t}$
			- this is a problem, since we want different entities to have different embeddings
				- $\mathbf{l} = 0$ is not so much a problem in itself; the real problem is $\mathbf{h} = \mathbf{t}$ -- if those entities had any *other* relations that we unique to just one, we wouldn't be able to tell them apart
	- *inverse*: can model this!
		- for two triplets $(h, r_1, t)$ and $(t, r_2, h)$, we can set the inverse relation by $\mathbf{r_1} = -\mathbf{r_2}$
	- *composition*: can model this
		- for triplets $(a, r_1, b)$, $(b, r_2, c)$, and $(a, r_3, c)$: set $\mathbf{r_3} = \mathbf{r_1}+\mathbf{r_2}$

## Miscellaneous Topics
### Erdos-Renyi Random Graphs
one of the earliest models of graph generation (probabilistic)
- *there will be a question about a generative model on the test, and you'll have to analyze the generation process*
- how to calculate *expected average node degree* $E[d]$?
	- key idea: sum over all of the possible edges in the graph and apply ER probability term $r$
	- $\frac{1}{2}\sum_{u\in V}\sum_{v\in V -\{u\}}$: if the graph is *undirected* (divide total edges by 2) and *irreflexive* (no self-loops) (remove $v$ from the inner sum)
	- ends up being $\binom{|V|}{2}\cdot r$ for expected number of edges
	- --> $\mathbb{E}[d] = \mathbb{E}\Big[\frac{2|E|}{|V|}\Big]$
		- in undirected graph, each edge in $E$ contributes to 2 degrees (1 for each node it connects)
	- $\mathbb{E}[d] = (|V|-1)\cdot r$