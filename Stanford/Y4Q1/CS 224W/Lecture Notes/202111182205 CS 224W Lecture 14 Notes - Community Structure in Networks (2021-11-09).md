#Stanford #Stanford-Fall-2021 #CS #CS224W #lecture-notes 
#networks #graphs #social-networks
See [[Lecture 14 - Community Structure in Networks.pdf|slides]]
___
# Agenda
- today: **Community Detection in Networks**
	- generally look at networks as "grouped" -- *clustering structure*
	- what led to this conceptual picture?

# Networks: Information Flow
- people are "embedded" in a network
- there are different links (*long* vs *short*) through which information flows
- Granovetter, PhD thesis from 1960
	- two perspectives on friendship:
		1. **structural** (spanning different parts of the network)
			- structurally embedded edges are also socially strong -- also non-structural edges (long-range edges) are socially weak
		2. **interpersonal** (either *strong* or *weak*)
	- *but*: long-range edges allow you to gather information from very different parts of the network (why acquaintances are better when seeking new jobs)
		- structurally-embedded edges are heavily redundant in terms of information access

## Triadic Closure
how communities (tightly-connected clusters of nodes) form
- networks *naturally evolve* via triadic closure
	- --> high **clustering coefficient**

## Testing on Real Data
**Edge Overlap**:
$$O_{ij} = \frac{|(N(i)\cap N(j))-\{i, j\}|}{|(N(i)\cup N(j))-\{i, j\}|}$$
- $N(i)$ = the neighborhood of node $i$ (set of neighbors)
- highly related to **edge weight** in practice! (a non-trivial observation)

# Network Communities
- given a network, *how do I discover clusters*? (automatically)
- example: Zachary's Karate club network
	- split of the club could be explained by a minimum cut in the network
- **communities**: sets of tightly connected nodes
- **modularity $Q$**
	- a measure of how well a network is partitioned into communities
	- given partitioning of network into disjoint groups $s\in S$: $Q\propto\sum_{s\in S}[(\text{\# edges within group } s) - (\text{expected \# edges within group } s)]$
		- in order to define expected # edges: need a null model

## Null Model: Configuration Model
given real graph $G$ with $n$ nodes and $m$ edges, construct rewired network $G'$ with same degree distribution / sequence
- expected # edges between nodes $i$ and $j$ with degrees $k_i$ and $k_j$: $k_i\cdot\frac{k_j}{2m}$
- $G'$ is a **multigraph** in this example

## Modularity
$Q\propto\sum_{s\in S}[(\text{\# edges within group } s) - (\text{expected \# edges within group } s)]$

Rewrite as:
$$Q(G,S)=\frac{1}{2m}\sum_{s\in S}\sum_{i\in s}\sum_{j\in s}(A_{ij}-\frac{k_ik_j}{2m})$$
- $\frac{1}{2m}$ normalizes s.t. $-1\leq Q\leq 1$
	- value of 1: super strong community structure
		- empirically we take 0.3 - 0.7 to indicate significant community structure
		- positive if number of edges within groups exceeds the expected number
	- value of 0: no community structure (what you'd expect from random configuration model)
	- value of -1: an "anti-community" structure where "groups" aren't connected but connect to the same ends of the network

# Louvain Algorithm
- finding partition that maximizes modularity is NP-hard, but there are heuristics!
- **Louvain**: greedy algorithm for community detection ($O(n\log n)$)
	- provides hierarchical communities (via **dendrogram**)
	- fast, rapid convergence, and high modularity input
	- each pass has 2 phases:
		1. modularity optimized by allowing local changes to node-community memberships (nodes allowed to change their communities if it increases modularity, hence "greedy")
		2. identified communities *aggregated* into super-nodes to build a new network
	- repeat iteratively until no increase of modularity is possible
	- considers graphs as *weighted*
		- as we aggregate, weights count num. edges in the original graph
	- initialize w/ each node in a *distinct* community
		- for each node:
			- compute modularity delta when putting node $i$ into same community of neighbor $j$ --> move to community with max $\Delta Q$
				- if node $i$ goes from community $D$ to $C$:
$$\Delta Q(D\rightarrow i\rightarrow C)=\Delta Q(D\rightarrow i)+\Delta Q(i\rightarrow C)$$
					- Modularity *within community* $Q(C)$ is large when most of the total links are within-community links (see [[Lecture 14 - Community Structure in Networks.pdf|slide called "Modularity Gain"]] for this)
		- notice that output depends on ordering
	- now: create **super-nodes** w/ aggregation --> *weighted* super-node network (with self-loops)
		- weight of "super-edges" will be number of original edges that span the members of each super-node
	- method also automatically determines the number of communities

# Detecting Overlapping Communities: AGM
1. Define generative model for graphs based on node community affiliations (community affiliation graph model = **AGM**)
2. Find best AGM that could have generated $G$ --> discovers communities

## Community Affiliation Graph Models (AGM)
bipartite graph of nodes and communities, where edges signify membership
- generative model: generate edges in the *actual* network using community membership
- nodes $V$, communities $C$, memberships $M$
- single parameter $p_C$ for each community $C$
	- nodes in community $C$ connect to each other w/ biased coin flip w/ probability $p_C$
	- nodes belonging to multiple communities have multiple coin flips!

### Flexibility
- can express a variety of community structures: non-overlapping, overlapping, nested / hierarchical, etc.

### Detecting Communities w/ AGM
- use network to generate the bipartite membership model $F$ (given the graph)
- graph fitting via **Maximum Likelihood Estimation**
	- efficiently calculate $P(G|F)$
	- then, maximize over $F$ (using gradient descent)
		- $\arg\max_F(P(G|F))$
$$P(G|F) = \prod_{(u,v)\in G}P(u,v)\prod_{(u,v)\not\in G}1-P(u,v)$$
- costly to compute: have to go over *all* pairs of nodes