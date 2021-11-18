#CS #CS224W #lecture-notes #Stanford #Stanford-Fall-2021 
- 24 hour window on Friday, Nov 19th in which to take timed 3-hour exam
- Agenda
	- Traditional node embedding techniques
	- Graph neural networks
	- Knowledge graphs & reasoning
	- Generative models for graphs
- cs224w.stanford.edu
	- Slides posted there
- Reading: open source book called "Graph Representation Learning" by Will Hamilton
- Ed discussion forum on class website
- OH every day of the week, including on weekends
	- Virtual, Zoom links on course website, queues maintained
- Final grade
	- 3 homeworks
		- written, submitted through gradescope
	- Coding assignments: 5 Google Colab notebooks
		- Colab 0 is not graded -- tutorial, to get up to speed
		- Hands on coding experience for graph neural networks
	- Exam: 35%
	- Course project: 20%
	- 2 late periods per student
		- 1 late period used per assignment (except final project) == gives 4 extra days: Thursday (11:59pm) ==> Monday (11:59pm)
- Course project
	- Will have a default project, pre-specified
	- Will also have option to do custom project
	- Teams of 1, 2, and 3 -- 3-person teams are the best
- Tools
	- PyG (PyTorch Geometric)
	- GraphGym: platform for designing graph NNs
		- Hyperparam tuning, user customization etc.
	- Useful frameworks for final project!

# What is the course about?
## Graphs
Graphs: general language for describing and analyzing entities with relations/interactions
- graph vs. network: "a network is a natural graph"
	- social *networks*
	- graphs are a *representation* (relational structures)
- *How do we take advantage of the relational structure for better predictions?*
- Modern ML toolbox: able to process two very simple data types: 2D arrays (CV) and linear sequences (NLP)
	- Majority of problems can't be represented in one of these two formats
	- How do we develop much more generally applicable algorithms? For more complex domains?

Why is this hard?
- images / text: nice structure and starting point
- Graphs: no beginning reference point (fixed node ordering)
	- No spatial locality like grids, no fixed size, structure within the same graph can be quite different
	- Networks can be dynamic and have lots of complex relational features (incl. images and text)

Predictions: node labels, new links, generated graphs / subgraphs
- no feature engineering! can directly learn on top of the graph -- representation learned is optimal / tuned for given task
- representation learning: map nodes to $d$-dimensional embeddings s.t. similar nodes in network are embedded close together
	- $f: u\rightarrow\mathbb{R}^d$ (node to feature rep. embedding)
- Different types of tasks over graphs
	- on nodes
	- on edges ("link prediction task")
	- on subgraphs
	- on the entire graph