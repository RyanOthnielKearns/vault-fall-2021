#CS #CS224W #Stanford #Stanford-Fall-2021 #lecture-notes 
2021-10-28
See [[Lecture 12 - Frequent Subgraph Mining with GNNs.pdf|slides]]
___
# Agenda
- last two lectures: **knowledge graphs** (completion and reasoning)
	- learn how to move from one point to another in the embedding space (e.g. TransE)
- today: *subgraph matching* and *motif discovery*
	- impose constraints on ordering (*order constraints* on embedding space)

# Subgraphs
- building blocks: have power to characterize / discriminate networks

## Subgraphs and Motifs
**Subgraph**
1. **Node-induced subgraph**: take subset of nodes and all edges induced by nodes
	- $G' = (V', E')$
	- $V'\subseteq V$
	- $E' = \{(u,v)\in E\ |\ u, v\in V'\}$ (a function of $V'$)
	- examples
		- Chemistry: functional groups
2. **Edge induced subgraph**: take subset of the edges and all corresponding nodes
	- knowledge graphs: relations

How to say that $G_1$ "is contained in" $G_2$? If $V'$ and $E'$ come from different graphs...

### Graph Isomorphism
graphs are *isomorphic* if there exists a *bijection* between nodes s.t. all edges are preserved
- $f : V_1\rightarrow V_2$
- $(u,v)\in E_1$ iff $(f(u),f(v))\in E_2$

We don't know if this is NP-hard, but there is no polynomial algorithm found for solving it

### Subgraph Isomorphism
$G_2$ is *subgraph isomorphic* to $G_1$ if some subgraph of $G_2$ is isomorphic to $G_1$
- this problem is NP-hard
- can use either the node-induced or edge-induced definition of subgraph

### Examples
- All connected, undirected graphs of size 4

### Motifs
"recurring, significant patterns of interconnections"
- **Pattern**: small subgraph
- **Recurring**: found many times
- **Significant**: more frequent than expected at random

Motifs are **induced subgraphs** (restricts which patterns of the motif count, see [[Lecture 12 - Frequent Subgraph Mining with GNNs.pdf|slides]] for example)

#### Why Needed?
- help us understand how graphs work
- help make predictions based on presence in dataset
- e.g.
	- feed-forward loops (found in neuron networks to neutralize "biological noise")
	- parallel loops (found in food webs)
	- single-input modules (found in gene control networks)

## Determining Motif Significance
To determine significance we need a **null-model** (a point of comparison, in statistics)
- *key idea*: subgraphs that occur in a real network much more often than a random network have functional significance

### How to define a random network?
#### Erdos-Renyi (ER) random graphs
- $G_{n,p}$: undirected graph on $n$ nodes where each edge $(u,v)$ appears iid with probability $p$
	- number of edges is a stochastic quality
	- what is significant in real networks is degree -- with ER random graphs, all nodes have about the same degree

#### Configuration Models
- to create a random graph with a given **degree sequence**
	1. nodes with spokes
	2. randomly pair up "mini-nodes"
		- might connect two nodes multiple times, or connect same node to itself... but the process is super fast!
	3. get resulting graphs
- used to create $G^{\text{rand}}$ with a degree sequence similar to a given real graph $G^{\text{real}}$

#### Edge-Switching Map
- start from a given graph $G$
- some $Q\cdot |E|$ times:
	- take a pair of edges at random and *exchange the endpoints*
- produces randomized graph with the exact same degree sequence

### Steps
1. Count motifs
2. Generate random graphs
3. Use statistical measures to evaluate motif significance (e.g. *Z-score*)

#### Z-Score
$Z_i$ captures statistical significance of motif $i$:
$$Z_i = (N_i^{\text{real}} - \bar{N}_i^{\text{rand}}) / \text{std}(N_i^{\text{rand}})$$
- $N_i^{\text{real}}$ is num. motif $i$ in real graph
- $\bar{N}_i^{\text{rand}}$ is average num. motifs in random graph instances

##### Network Significance Profile (SP)
$$SP_i = Z_i / \sqrt{\sum_j Z_j^2}$$
- a vector of normalized Z-scores
	- dimension depends on number of motifs considered
- $SP$ emphasizes relative significance of subgraphs
- networks from the same domain have the same significance profile

### Variations on Motif Concept
- directed vs. undirected
- colored vs. uncolored
- temportal and static motifs
- under-representation (*anti-motifs*)


# Neural Subgraph Representations
- one way to count subgraphs: exhaustively count all ways
	- kind of cumbersome!
	- can we use a neural network to identify faster?

## Subgraph Matching
- given large *target* graph, and connected *query* graph:
	- is the *query* graph a *subgraph* of the target?
- use GNN to predict subgraph isomorphism
	- intuition: exploit *geometric shape* of the embedding space to capture subgraph isomorphism

### Task
*binary prediction*: true if query is isomorphic to a subgraph of the target
- not worried about discovering the exact mapping, node-by-node
- decompose large target graph into small neighborhoods
- embed query graph, and neighborhoods, and for each neighborhood use embeddings to predict the subgraph relation

### Neural Architecture
1. Use **anchor node**
	- connect anchor nodes, then connect each other node and see if you maintain the same connections
	- recall *node-level frequency definition* in [[202111102213 CS 224W Lecture 12 Notes - Frequent Subgraph Mining with GNNs (2021-10-28)#Subgraph Frequency|Subgraph Frequency]]
	- use embeddings to decide isomorphism around nodes' neighborhoods
	- can also identify the corresponding *nodes* when we predict isomorphism
2. Use node-anchored **neighborhoods**
	- for each node in target graph, cut a piece that also has the anchor node --> neighborhoods around anchors
	- for each node in $G_T$: obtain $k$-hop neighborhood around the anchor
		- performed using BFS
	- embed the neighborhoods using a GNN (by computing the embeddings for the anchor nodes in their respective neighborhoods)
3. Use GNN to create embeddings for $u$ and $v$ -- predict if their neighborhoods are isomorphic

## Order Embedding Space
map graph $A$ to point $z_A$ in high-dim space, *non-negative* in all dimensions
- capture partial ordering (transitivity)
	- intuition: subgraph is to the "lower-left" of its supergraph (in 2D)
- $z_{A_1}\preccurlyeq z_{A_2}$ means element-wise less than

- subgraph isomorphism relationship is nicely encoded in this space
	- transivitiy
	- anti-symmetry: if two graphs are subgraphs of one another, they are isomorphic (and have same embedding point)
	- closure under intersection (graph of 1 node is always a subgraph of any graph -- embedding is $\mathbf{0}$)

### Order Constraint
- enforce ordering structure
- define loss function based on the **order constraint**: ideal order embedding property that reflects subgraph relationships
$$\forall_{i=1}^D z_q[i]\leq z_u[i]\text{ iff }G_Q\subseteq G_U$$
- GNN embeddings learned by minimizing a **max-margin** loss
	- margin: $E(G_q, G_t) = \sum_{i=1}^D(\max(0, z_q[i]-z_t[i]))^2$
		- we want $E(G_q, G_t)=0$ when $G_q$ is a subgraph of $G_t$, and $>0$ when not

## Training Neural Subgraph Matching
- construct training examples $(G_q, G_t)$ (half positive, half negative examples)
	- minimize margin for positive examples
	- minimize $\max(0, \alpha - E(G_q, G_t))$ for negative examples
		- prevents model from trivializing optimizing by just pushing all embeddings really far apart

## Subgraph Predictions
- if $E(G_q, G_t)<\varepsilon$ predict "True", else "False" (where $\varepsilon$ is a hyperparameter)
	- to check if $G_q$ is actually isomorphic to a subgraph of $G_t$, repeat for all nodes in $G_q$ as anchor

# Mining Frequent Subgraphs
finding size-$k$ motifs:
1. **enumerating** all size-$k$ motifs
	- soln.: use GNN to predict subgraph frequency
2. **counting** all occurrences

- computationally hard! NP-hard
	- solve w/ *representation learning*

## Subgraph Frequency
**Graph-level subgraph frequency** = number of unique subsets of nodes for which the subgraph induced by the nodes is isomorphic to the motif of interest
- Frequency of $G_Q$ in $G_T$ (query and target)

**Node-level subgraph frequency definition**: number of nodes in target graph for which some subgraph is isomorphic to the query graph and the node is present... ==look at slides for more precise definition==

## SPMiner
a neural model to identify frequent motifs

take input --> decompose --> encode --> search procedure (find frequent subgraphs by growing patterns)

**key benefit of order embeddings**: just embed a graph and ask "how many graphs are embedded to the top right of me?" --> these are supergraphs if we assume the ordering constraint
- estimate frequency of $G_Q$ by counting number of $G_{N_i}$ s.t. embeddings $z_{N_i}$ satisfy $z_Q\preccurlyeq z_{N_i}$

- SPMiner search procedure: start with a starting node $u$ in target graph and do "motif walk"
	- add an edge, embed that, and see where you move in the embedding space --> frequency of that new subgraph is the number of graphs embedded to the "top-right" of it
	- grow the motif to find larger frequent subgraphs!