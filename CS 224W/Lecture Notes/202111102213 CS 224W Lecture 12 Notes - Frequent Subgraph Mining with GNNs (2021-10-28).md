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

==stopped here at 39:25==

# Neural Subgraph Representations
# Mining Frequent Subgraphs
## Subgraph Frequency
**Graph-level subgraph frequency** = number of unique subsets of nodes for which the subgraph induced by the nodes is isomorphic to the motif of interest
- Frequency of $G_Q$ in $G_T$ (query and target)

**Node-level subgraph frequency definition**: number of nodes in target graph for which some subgraph is isomorphic to the query graph and the node is present... ==look at slides for more precise definition==