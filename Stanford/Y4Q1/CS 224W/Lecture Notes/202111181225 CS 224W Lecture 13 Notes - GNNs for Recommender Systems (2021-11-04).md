#CS #CS224W #lecture-notes #Stanford #Stanford-Fall-2021 
See [[Lecture 13 - GNNs for Recommender Systems.pdf|slides]]
___
# Agenda
How to look at recommender systems as a graph problem
- all the big giants (Netflix, Amazon, Spotify) running recommender systems
	- --> personalized recommendation (a small number of all the total items) for each user
- modeled as a **bipartite graph** (*users* and *items* node types)

# Recommendation Task
- given: past user-item interactions
- task: predict new items for each user (in the future)
	- *link prediction* problem
- for $u\in U$, $v\in V$, we need score function $f(u,v)$
	- problem: can't evaluate score for *every* user-item pair
	- solution: 2-stage process
		1. **candidate generation**
			- based on user's activity, create user embedding
			- using user query embedding, perform a k-NN search of embedding space of items
			- send some number of items to the ranking algorithm
		2. **ranking**
			- rank items using $f$ (intended to be slower but more accurate)
			- result: top-$K$ recommendation
				- something like 10-100 items (much smaller than total num items)
				- evaluation metric: **Recall@K**

## Recall@K
- $P_u$: set of positive items
	- either hide 10% of what you know to test, or rely on temporal ordering (where future is "hidden" from you and you try to predict it, then check how accurate you were)
- $R_u$: recommended items
- **Recall@K** = $|P_u\cap R_u| / |P_u|$

## Notation
- $U$: users
- $V$: items
- $E$: set of user-item interaction pairs

## Score Function
real-valued scalar $score(u, v)$

## Embedding-Based Models
- parameterized function $f_\theta(\cdot,\cdot):\mathbb{R}^D\times\mathbb{R}^D\rightarrow\mathbb{R}$
	- score fxn = $f_\theta(\mathbf{u}, \mathbf{v})$
- also need encoders for user and item embeddings
- training objective: optimize model parameters for a high Recall@K
	- problem: vanilla Recall@K is *non-differentiable*
	- use *surrogate loss fxns* that are not differentiable
		1. Binary loss
		2. Bayesian Personalized Ranking (BPR) loss

achieved SoTA in recommender systems

### Binary Loss
- definite positive / negative edges ($E$ and $E_{\text{neg}}$)
- define sigmoid function $\sigma(x)\equiv\frac{1}{1+\exp(-x)}$
	- define binary classification loss using $\sigma(f_\theta(\mathbf{u}, \mathbf{v}))$ (see [[Lecture 13 - GNNs for Recommender Systems.pdf|slides]] for precise formulation)
- pushes scores for positive edges higher than negative edges (aligns w/ Recall@K)
	- problem: unnecessarily punishes the model prediction even if Recall@K is perfect
	- issue b/c binary loss is *non-personalized* ("all positives have to be ranked above all negatives" -- not distinguishing btwn different users)
	- we want surrogate loss fxn to be defined in a personalized mannar

### BPR Loss
- for each user $u^*\in U$, define *rooted* positive/negative edges
	- we want scores of $E(u^*)$ to be higher than $E_{\text{neg}}(u^*)$ (this aligns with the personalized manner of the recall@K metric)
	- also see [[Lecture 13 - GNNs for Recommender Systems.pdf|slides]] for precise formulation
-  mini-batch training: for each user sample single positive example and fixed num. negative examples
	-  average loss over users in the mini-batch
	-  $U_{\text{mini}}\subseteq U$

### Why do Embedding Models Work?
**Collaborative Filtering**
- recommend items by users by *collecting preferences of similar users*
	- similar users prefer similar items
- *how to capture similarity notion?*
	- embedding-based models can do this!
	- low-dim embeddings are forced to capture similarity between users/items to fit the data (b/c cannot memorize all the user-item links)

# GNNs for Recommender Systems
## Neural Graph Collaborative Filtering (NGCF)
- conventional collaborative filtering: shallow embeddings, no features for users/items (just interactions)
- shallow learnable embeddings $\mathbf{u},\mathbf{v}\in\mathbb{R}^D$
- score function is $\mathbf{z_u}^T\mathbf{z_v}$
- **neural collaborative filtering**: explicitly incorporate high-order graph structure
	- use GNN to generate graph-aware user/item embeddings ($\mathbf{h}_v^{(0)}$)
	- initial shallow embeddings are not graph-aware
	- because GNN propagate embeddings along bipartite graph, higher-order graph structure is captured in final embeddings ($\mathbf{h}_v^{(K)}$)

## LightGCN
- observation from NGCF: shallow learnable embeddings are quite expressive
	- learned for every (user/item) node --> $O(ND)$ size
	- hard at scale! how to make it more actionable?
	- can you remove the GNN's learnable parameters?
- overview:
	1. adjacency matrix for bipartite graph $A$
		- $\mathbf{R}_{uv} = 1$ if user $u$ interacts with item $v$
	2. matrix formulation of GCN
		- refresher from earlier lecture!
		- each layer of GCN's aggregation:
			- $\mathbf{E}^{(k+1)}=\text{ReLU}(\mathbf{\tilde{A}}\mathbf{E}^{(k)}\mathbf{W}^{(k)})$
	3. simplification by removing non-linearity
		- remove the ReLU nonlinearity!
			- $\mathbf{E}^{(k+1)} = \mathbf{\tilde{A}}\mathbf{E}^{(k)}\mathbf{W}^{(k)}$
			- $\mathbf{E}^{(K)} = \mathbf{\tilde{A}}^{K}\mathbf{E}(\mathbf{W}^{(0)}\dots \mathbf{W}^{(k-1)})$
			- "diffusing node embeddings along the graph"
			- just apply $\mathbf{E}\gets\mathbf{\tilde{A}}\mathbf{E}$ $K$ times!
				- each matrix multiplication diffuses node embeddings to node neighbors (the 1-hop neighborhood)

### Multi-Scale Diffusion
$$\alpha_0 E^{(0)} + \dots + \alpha_K E^{(K)}$$
- $\alpha_0 E^{(0)}$ is a self connection (omitted from the definition of $\mathbf{\tilde{A}}$)
- coefficients $\alpha$ are hyperparameters
	- for simplicity, LightGCN uses a uniform coefficient $\alpha_k = \frac{1}{K+1}$

### Model Overview
Given:
- Adjacency matrix $\mathbf{A}$
- Initial learnable embedding matrix $\mathbf{E}$

Iteratively diffuse embedding matrix $\mathbf{E}$ using $\mathbf{\tilde{A}}$
- average embedding matrices at different scales to form final embedding
	- different from taking the embedding at the last layer! what we've used before

Score function will still be a dot product between the embedding of the user and embedding of the item

### Why does simple diffusion propagation work?
- diffusion directly encourages embeddings of similar users/items to be similar
	- intuition: similar users share lots of similar neighbors
- LightGCN simplifies NGCF by removing the learnable parameters of GNNs
	- learnable params are all in shallow input node embeddings
	- problem: the "cold start" scenario with new products (need to collect some initial signal)
	- diffusion propagation is just matrix-vector multiplication

## PinSAGE
motivation: P2P recommendations
- PinSAGE = "pin" embedding
	- works for fresh content (overcomes cold start problem)
	- key idea: borrow information from nearby nodes
	- can't just use image classification: makes mistakes for visually similar, semantically different things (soil vs. ground meat, tapestry vs. carpet)

### Scaling up
1. shared negative examples across users in mini-batch (not per unique user)
	- only sample negatives once per minibatch
2. hard negative examples
3. curriculum learning
4. mini-batching

### Model
- learn node embeddings s.t. distance between related node embeddings is smaller

#### Shared Negative Examples
- in BPR loss: had one positive example and multiple negative examples per user
	- using more negative examples improves performance, but is expensive
	- if we share negative examples across all users in minibatch, only need to generate $|V_{\text{neg}}|$ embeddings for negative nodes (instead of multiplied by $|U_{\text{mini}}|$)

#### Hard Negatives
- most negatives are "easy negatives", e.g. model does not require fine-grained representation to get them right
- a "**hard negative**" requires the model be more sophisticated
	- include more and more hard negative samples per each epoch (at $n$-th epoch, add $n-1$ hard negative items)
	- for each user, hard negatives are close to the user node but not actually connected in the graph
		- compute personalized page rank for user
		- sort items in descending order by PPR scores
		- randomly sample item nodes in, say, the 2000th - 5000th places (if total graph has billions of items) (this is very Pinterest specific...)

##### Distance Weighted Sampling
Sample negatives so that query-negative distaince is approximately $U[0.5, 1.4]$ (Wu et al., 2017)