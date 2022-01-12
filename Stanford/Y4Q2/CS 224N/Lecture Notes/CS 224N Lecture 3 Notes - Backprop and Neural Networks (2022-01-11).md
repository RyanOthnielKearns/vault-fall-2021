#Stanford #Stanford-Winter-2022 #CS #CS224N #NLP #deep-learning #backpropagation #neural-networks
___
- rusty with calculus? this is the one week of the quarter where you *really* want to look at the readings...
	- mostly for this lecture: short guides for how to do matrix calculus
		- last one by Rumelhart et al. -- seminal paper for backpropagation (and only 3 pages!)
	- next class (thurs): mainly linguistics

# Common NLP Task: Named Entity Recognition (NER)
- *find* and *classify* names in text
	- e.g. person, location, date, ...
- uses
	- tracking mentions of particular entities in docs
	- question answering
	- sentiment analysis for a given entity

## Simple NER: window classification using binary logistic regression
- Classify each word in fixed *context window* of neighboring words
- using multiclass softmax classifier (binary softmax classifier for each class or "decision head")
- resulting vector $x_{\text{window}}=x\in\mathbb{R}^{5d}$ -- a column vector!

## Neural classification
- typical ML/stats: [[202201061516 CS 224N Lecture 2 Notes - Word Vectors, Word Senses, and Neural Network Classifiers (2022-01-06)#Classification review and notation|softmax classifier]]
	- learned params $\theta$ are just elements of $W$ -- *not* the input representation $x$, which has sparse symbolic features
	- cutting hyperplane will have a *linear decision boundary* (which can be limited)
- neural network classification is different!
	- both $W$ *and* distributed representations for $x$ are learned
	- formally, the word vectors $x$ re-represent the one-hot vectors (like "lookup" encodings) $e$ like level-1 embeddings: $x=Le$ (though this isn't something you actually do in code)
	- use deep networks that let us re-represent / compose the data multiple times, which gives *non-linear classification*
		- "nonlinear in terms of the input feature representations"
		- can capture more difficult data distributions
		- typically: non-linear w.r.t. the input representation, but linear w.r.t. the final layer of the classifier...?

### Simplest neural model
$$J_t(\theta) = \sigma(s) = \frac{1}{1+e^{-s}}$$
$$s = \mathbf{u}^T\mathbf{h}$$
$$\mathbf{h} = f(\mathbf{Wx}+\mathbf{b})$$
- $f$ = some element-wise non-linear function like logistic, tanh, ReLU, etc.
- $J_t(\theta)$ is the predicted model probability of the class $t$
- $\mathbf{u}$ is another parameterized vector that we learn during training
- $\mathbf{x}$ is the input

### Why non-linearities are needed
- neural networks ~ big function approximators
	- without non-linearities, deep neural networks could only do linear transforms
		- extra layers would just smush into a single linear transform: $W_1W_2x = Wx$
		- a 2-layer neural network with arbitrarily large hidden layer can approximate effectively any function you want -- but the problem is it's not good for learning
			- better for learning = making the network deeper -- allows for better (hierarchical) representations of natural classes we're trying to model

### Cross entropy loss
$$H(p,q) = -\sum_{c=1}^Cp(c)\log q(c)$$
- $p$ is the true probability distribution
	- assuming a ground truth is available, the true probability distribution is one-hot at the correct class
		- Meaning only term left is the negative log probability of the true class $y_i$: $-\log p(y_i | x_i)$ is the entire loss function
- $q$ is our computed model probability
- concept comes from **information theory**

# Computing Gradients
## Review: Stochastic Gradient Descent
$$\theta^{\text{new}} = \theta^{\text{old}} - \alpha\nabla_\theta J(\theta)$$
how to compute $\nabla_\theta J(\theta)$?
1. by hand
2. algorithmically, using **backpropagation**

## By Hand: Matrix Calculus
- "multivariable calculus is just single-variable calculus if you use matrices"
- *fully vectorized gradients*

### Gradients
- measure of slope

#### Jacobian Matrix: Generalization of the Gradient
- given a function with $m$ outputs and $n$ inputs:
	- its **Jacobian matrix** is an $m\times n$ matrix of partial derivatives

### Chain Rule
- for composition of one variable functions: **multiply the derivatives**:
	- $z = 3y$; $y=x^2\rightarrow \frac{dz}{dx} = \frac{dz}{dy}\frac{dy}{dx}$
- for multiple variables at once: just **multiply Jacobians**:
	- $\mathbf{h}=f(\mathbf{z})$; $\mathbf{z} = \mathbf{Wx} + \mathbf{b}\rightarrow \frac{\partial\mathbf{h}}{\partial\mathbf{x}} = \frac{\partial\mathbf{h}}{\partial\mathbf{z}}\frac{\partial\mathbf{z}}{\partial\mathbf{x}}$
	- $\frac{\partial}{\partial\mathbf{x}}(\mathbf{Wx}+\mathbf{b}) = \mathbf{W}$
	- $\frac{\partial}{\partial\mathbf{b}}(\mathbf{Wx}+\mathbf{b}) = \mathbf{I}$ (identity matrix)
	- $\frac{\partial}{\partial\mathbf{u}}(\mathbf{u}^T\mathbf{h}) = \mathbf{h}^T$ (a row vector)

#### Computing the gradient of our neural net
See our [[CS 224N Lecture 3 Notes - Backprop and Neural Networks (2022-01-11)#Simplest neural model|simplest neural model]]
- find $\frac{\partial s}{\partial\mathbf{b}}$:
$$\frac{\partial s}{\partial\mathbf{b}} = \frac{\partial s}{\partial\mathbf{h}}\frac{\partial\mathbf{h}}{\partial\mathbf{z}}\frac{\partial\mathbf{z}}{\partial\mathbf{b}}$$
$$= \mathbf{u}^T\text{diag}(f'(\mathbf{z}))\mathbf{I}$$
$$= \mathbf{u}^T\odot f'(\mathbf{z})$$
- because $\frac{\partial}{\partial\mathbf{z}}(f(\mathbf{z})) = \text{diag}(f'(\mathbf{z}))$
- $\odot$ means **Hadamard product**: element-wise multiplication to form a vector
- can reuse computations: consider $\frac{\partial s}{\partial\mathbf{W}}$:
$$\frac{\partial s}{\partial\mathbf{W}} = \frac{\partial s}{\partial\mathbf{h}}\frac{\partial\mathbf{h}}{\partial\mathbf{z}}\frac{\partial\mathbf{z}}{\partial\mathbf{W}}$$
- reuse the first two terms from the earlier solved equation!:
$$\delta=\frac{\partial s}{\partial\mathbf{h}}\frac{\partial\mathbf{h}}{\partial\mathbf{z}} = \mathbf{u}^T\odot f'(\mathbf{z})$$
- result of $\frac{\partial s}{\partial\mathbf{W}}$ is a $1\times nm$ Jacobian (if $\mathbf{W}\in\mathbb{R}^{n\times m}$)
	- super inconvenient to do the $\theta$ update then...
	- so leave pure math and use something called the **shape convention**: shape of the gradient = shape of the params!
$$\frac{\partial s}{\partial\mathbf{W}} = \delta^T\mathbf{x}^T$$
- the **outer product**
	- $\delta$ is the upstream gradient (called the "*error signal*")
	- this is hacky: the way to do it that makes the dimensions work out!
	- since each input goes to each output, you want to get the outer product
$$\begin{bmatrix}\delta_1\\\vdots\\\delta_n\end{bmatrix}\begin{bmatrix}x_1 & \dots & x_m\end{bmatrix}$$
#### Local Input Gradients
- $W_{ij}$ only contributes to $z_i$
	- e.g. $W_{23}$ only used to compute $z_2$, not $z_1$
- see slides for the math

#### Shape of the Derivatives
- the Jacobian form makes chain rule easy
- the shape convention makes SGD easy
	- we choose this -- want answers in a shape that works out
Two options for specific problems:
1. Use Jacobian as much as possible, and reshape to follow the shape convention at the end
2. Always follow the shape convention
	- look at dimensions and think a little, to figure out when to transpose / reorder terms
	- error message $\delta$ that arrives at a hidden layer should have same dimensionality as that hidden layer...

## Backpropagation
- taking derivatives and using the generalized / multivariate / matrix chain rule
- trick: reusing partially computed gradients as much as possible

### Computation Graphs
- represents our neural net equations as a graph
![[computation-graph.png]]
- source nodes: inputs ($\mathbf{x}$, $\mathbf{W}$, ...)
- interior nodes: operations ($\cdot$, $+$, ...)
- moving through the computation graph is called **forward propagation**
- going backwards along edges, passing gradients: **backpropagation**
	- at each node...
		- node receives the "upstream gradient"
		- goal is to work out the "downstream gradient" using the operator within the node
		- each node has a **local gradient** (grad of output w.r.t. input)
		- \[downstream gradient \] = \[ upstream gradient \] x \[ local gradient \]
		- one for each input (inward edge) in the computation graph
![[backprop.png]]
- what the final partial gradients tell us: how much will changing one of these variables change the ultimate value of what we compute?
	- when function has two partial gradients for two input terms, *sum* the partials (see slides, this is confusing)

#### Node Intuitions
- plus "distributes" the upstream gradient
- max "routes" the upstream gradient
- times "switches" the upstream gradient

#### Complexity
1. Fprop: visit nodes in *topological sort order*
2. Bprop:
	1. initialize output gradient = 1
	2. visit nodes in reverse order:
		1. compute gradient w.r.t. each node using gradient w.r.t. successors

- big O() complexity of Fprop / Bprop should be the same
	- this is if you reuse all possible work there is to reuse
- in general, nets have regular layer-structure, so we can just matrices and Jacobians

#### Automatic Differentiation
- gradient computation can be automatically inferred from the symbolic expression of the fprop
	- if each node type knows how to compute its output, and the gradient w.r.t. its inputs given the gradient w.r.t. its output
- modern DL frameworks (TF, PyTorch, etc.) do backprop for you but mainly leave layer / node writer to hand-calculate the local derivative
	- each node or layer reports what it's local gradient is
		- and then software package runs the overall backprop / chain rule
	- backing off from this idea of complete & total automatic differentiation

#### Implementations
```
class ComputationalGraph(object):
	def forward(inputs):
		for gate in self.graph.nodes_topologically_sorted():
			gate.forward()
		return loss

	def backward():
		for gate in reversed(self.graph.nodes_topologically_sorted()):
			gate.backward()
		return inputs_gradients
```
- have to write forward/backward pass for each `gate` ourselves...

# Why understand backprop?
- understanding how it works = crucial for debugging / improving models
- see Karpathy article in syllabus
- **exploding** and **vanishing gradients**