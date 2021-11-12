#CS #CS224W #lecture-notes 
See [[Lecture 11 - Reasoning Over Knowledge Graphs.pdf|slides]]
# "Reasoning Over Knowledge Graphs"
2021-10-26
___
# Recap
- KG Completion Task: for given (head, relation), predict missing tail(s)

# Today
- **goal**: how to perform multi-hop reasoning over KGs?
	- how do we answer (complex) queries on a massive, incomplete KG?
		- *one-hop* queries: "here's a beginning entity + relation. Find tail"
			- **can formulate KG completion problems in this way**
		- *path* queries: start with an entity, traverse the relation, traverse relation from that entity, and tell us what entity you've got to
			- $v_a$ "anchor" entity
			- query $q$ represented by $q = (v_a, (r_1,\dots,r_n))$
				- to answer: start from anchor node, go across relation $r_1$, then $r_2$, $\dots$, until $r_n$
				- answers will be multiple nodes!
		- *conjunctive* queries: find node you can get to from multiple other nodes / relations
- *reasoning over knowledge graphs*

# KG Completion
Is link $(h, r, t)$ in the KG?

- issue w/ answering queries: *KGs incomplete and unknown*
	- many relations btwn entities are missing / incomplete
		- missing relations mean missing answers when asked queries
		- we cannot practically hope that it will ever be fully complete
			- cannot use KG completion -- result will be *dense*
			- *time complexity of traversing a dense KG*: exponential as fxn of length of path $L$: $O(d_\max^L)$
	- otherwise the "graph traversal" problem wouldn't have to be an ML task!
		- this of this as a prediction problem

# Predictive Queries Task
- *how to answer path-based queries over an incomplete knowledge graph*?
- **Predictive Queries**: impute missing relations "on the fly" when answering queries
	- Train the system, then be able to answer any path queries
	- Generalization of link prediction task