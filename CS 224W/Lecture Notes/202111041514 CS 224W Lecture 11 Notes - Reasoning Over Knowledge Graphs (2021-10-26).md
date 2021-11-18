#CS #CS224W #lecture-notes #Stanford #Stanford-Fall-2021 
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
	- Map queries into embedding space, *learn to reason* in that space
		1. query as single point in Euclidean space (answers are embedded "close" to the query)
		2. **Query2Box**: answers to query have to be contained within hyper-rectangle

## Traversing KG in Vector Space
- generalize *TransE* to multi-hop reasoning
	- translate $\mathbf{h}$ to $\mathbf{t}$ using $\mathbf{r}$ w/ score $f_r(h,t) = -\vert\vert \mathbf{h} + \mathbf{r} - \mathbf{t}\vert\vert$
	- query embedding $\mathbf{q} = \mathbf{h} + \mathbf{r}$
	- answer embedding $\mathbf{t}$ s.t. $f_q(t) = -\vert\vert \mathbf{q} - \mathbf{t}\vert\vert$
	- given path query $q = (v_a, (r_1,\dots,r_n))$ --> $\mathbf{q} = \mathbf{v_a} + \mathbf{r_1} + \dots + \mathbf{r_n}$
		- *embedding space reasoning only involves vector addition!* independent of # entities in the KG
		- e.g. "What proteins are *associated* with the adverse events *caused* by *Fulvestrant*?"
			- Fulvestrant --> Causes --> Assoc
			- Query: (e:Fulvestrant, (r:Causes, r:Assoc))
### Insights
1. Can train TransE to optimize knowledge graph completion objective ([[202110301845 CS 224W Lecture 10 Notes (2021-10-21)|Lecture 10]])
2. Can handle *compositional relations*, so we can use it to answer multi-hop queries using vector addition
	- TransR / DistE / ComplEx can't handle compositionality and so aren't good for compositional relations

## Conjunctive Queries
- what about *logical conjunction operators*?
- "What are drugs that cause shortness of breath and treat diseases associated with the protein ESR2?" (logical and)
- Traverse KG from *anchor nodes* --> take intersection of entities where different path queries end

1. each intermediate node represents a set of entities -- how to represent?
2. how to handle intersection operator in embedding space?

## Box Embeddings
- embed queries with **hyper-rectangles**
- $q = (Center(q), Offset(q))$
	- answers to queries are enclosed within the box
	- benefit: *intersection* of two boxes is well-defined!
			- "high-dimensional Venn diagrams"

### To learn:
1. Entity embeddings ($d|V|$ params)
2. Relation embeddings ($2d|R|$ params)
3. Intersection operator $f$

#### Projection Operator
$\mathcal{P}$ : Box $\times$ Relation $\rightarrow$ Box
- operator will be learned

#### Intersection Operator
$\mathcal{J}$ : Box $\times\dots\times$ Box $\rightarrow$ Box

### Score Function
How to define the score function $f_q(v)$?
- Given query box $\mathbf{q}$ and entity embedding (box) $\mathbf{v}$:
$$d_{box}(\mathbf{q}, \mathbf{v}) = d_{out}(\mathbf{q}, \mathbf{v}) + \alpha\cdot d_{in}(\mathbf{q}, \mathbf{v})$$
- $0<\alpha<1$
- intuition: if a point is enclosed within the box, the distance should be downweighted
	- $d_{out}$ is the distance from the point to a point on the border of the box
	- $d_{in}$ is the distance from the border of the box to the center of the box
	- these two decompose the total distance (sum to it)
	- L1 distance: "boxy"
		- we don't use circles because the intersection of two circles is not a circle (contra boxes)

## Extending to Union Operation
**conjunctive queries + disjunction** is called **existential positive first-order (EPFO)** queries
- *cannot embed in low dimensions!* union over arbitrary queries requires high-dimensional embeddings
	- 2 dimensions --> breaks down w/ 4 points (see [[Lecture 11 - Reasoning Over Knowledge Graphs.pdf|slides]])
	- given $M$ conjunctive queries with non-overlapping answers, need dimensionality $\Theta(M)$ to handle all OR queries
- key idea: take all unions out and only do union *at the last step!*
	- **disjunctive normal form** -- the disjunction (of the conjunctions) is done at the end
	- issue: translating into disjunctive normal form might increase the size of the query *exponentially*

# How to Train?
- similar to KG completion: given embedding, maximize score $f$ for positive answers ($f_q(v)$ for $v\in q$) and minimize for negative answers

## Trainable Params
- entity embeddings with $d|V|$ params
- relation embeddings with $2d|R|$ params
- intersection operator
- *how to achieve a query, answers, and negative answers?*
- *how to train params?*

## Training
1. Sample query from training graph, an answer, and a negative sample (entity as same type as $v$ but *not* answer)
	- query generation from **templates** (generate arbitrary query shapes)
	- in practice: you start from the answer and work backwards to generate a complex query
		- randomly pick one entity as the root node, work backwards to fulfill query template
2. Embed the query
3. Calculate both positive and negative scores
4. Optimize the loss $l$:
$$l = -\log\sigma(f_q(v))-\log(1-\sigma(f_q(v')))$$
- make $f_q(v)$ big and $f_q(v')$ small (close to 1, so 1-1, log of which is 0...)

### Example from `Query2Box`
"List male instrumentalists who play string instruments"
- String instrument -- instance of --> instruments -- played by --> players
- Male -- instance of --> males
- Then take the intersection

# Summary
- introduced answering predictive queries on large knowledge graphs
- *key idea*: embed queries by navigating the embedding space
	- embed query by composing learned operators
	- embedding of the query is close to its answers in ther embedding space